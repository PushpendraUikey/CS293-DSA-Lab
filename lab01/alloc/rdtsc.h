#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <iostream>

// Header guards protect against double-inclusion of the file during compilation.
#ifndef DS_LAB_RDTSC_H  // the name is arbitrary, but should be unique
#define DS_LAB_RDTSC_H

/*
It defines functions and a class to measure very precise CPU time using the RDTSC 
(Read Time-Stamp Counter) instruction.
Useful for benchmarking small code snippets at CPU cycle level.

The RDTSC instruction reads the current value of the CPU's time-stamp counter, 
which counts the number of cycles since the last reset.

The CPUID instruction is used to serialize the instruction stream, ensuring that 
all previous instructions have completed before the RDTSC instruction is executed.

The stopRDTSCP function reads the time-stamp counter and then executes the CPUID 
instruction to serialize the instruction stream again.

The ClockCounter class provides a simple interface to measure the time taken by a code block in CPU cycles.

The startRDTSC function reads the time-stamp counter and CPUID instruction to ensure 
that the RDTSC instruction is executed in a serialized manner.

The stopRDTSCP function reads the time-stamp counter and then executes the CPUID instruction 
to serialize the instruction stream again.

The ClockCounter class provides a simple interface to measure the time taken by a code 
block in CPU cycles.
*/



// this __inline__ is old c style syntax similar to inline. Since we're measuring time of tiny code
// snippets, we want to avoid function call overhead.
static __inline__ unsigned long long startRDTSC (void) {
    unsigned cycles_low, cycles_high;
    asm volatile ("CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "%rbx", "%rcx", "%rdx");
    return (static_cast<unsigned long long>(cycles_high) << 32) | cycles_low;
}

static __inline__ unsigned long long stopRDTSCP (void) {
    unsigned cycles_low, cycles_high;
    asm volatile("RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax",
            "%rbx", "%rcx", "%rdx");
    return (static_cast<unsigned long long>(cycles_high) << 32) | cycles_low;
}

class ClockCounter {
public:
// When constructor runs, memory is already allocated, constructor just initializes the memory.
    ClockCounter() :
        ticktime(0) {
            //Constructor is part of building the object.
            // When the constructor body runs,
            // ➔ the object’s memory is already allocated.
            // ➔ so you can call member functions (like start()).
        start();
    }

    unsigned long long ticktime;

    void start() {
        ticktime = startRDTSC();
    }

    unsigned long long stop() {
        return stopRDTSCP() - ticktime;

    }
};

#endif
// end of protected block