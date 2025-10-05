#include "rle.h"

// Note: the implementation assumes the upper limit of frequency of
// any character doesn't crosses the limit of 2^gamma-1, it's upto tester

// Constructor
rle::rle(int gamma): gamma(gamma){}

// Convert integer to gamma-bit binary string
string rle::f(int i)
{ 
    string output = "";
    while(i){
        if(i&1) output = "1" + output;
        else output = "0" + output;
        i >>= 1;
    }
    int rem = gamma - output.length();
    while(rem>0) output = "0" + output;
    return output;
}

// Convert gamma-bit binary string to integer
int rle::g(string i)
{ 
    int val = 0;
    int curr = 1;
    for(int len = i.length()-1; len>=0; len--){
        val += (i[len]-'0')*curr;
        curr *= 2;
    }
    return val;
}

// Compress the input file
string rle::compress(string input_string)
{ 
    string compressed = "";
    bool flag = true;
    int i=0;
    int len = input_string.length();
    while(i<len){
        int cnt = 0;
        char bit = flag ? '0' : '1';
        while(i < len && input_string[i] == bit) {
            cnt++;
            i++;
        }
        compressed += f(cnt);
        flag = !flag;
    }

    return compressed; 
}

// Decompress the input file
string rle::decompress(string input_string)
{ 
    string decomp = "";
    int i=0;
    int len = input_string.length();
    bool flag = true;
    while(i<len){
        string curr = input_string.substr(i, gamma);
        int substrlen = g(curr);
        if(flag){
            while(substrlen-->0) decomp += "0";
        }else{
            while(substrlen-->0) decomp += "1";
        }
        flag = !flag;
        i += gamma;
    }
    return decomp; 
}