# include "bits/stdc++.h"
# include "deque-inheritance.cpp"

using namespace std;

int main (){
    int cap;
    cout << "Choose capacity: ";
    cin >> cap;
    // Test constructors and push
    Stack<int> st(cap);
    st.push_back(1);
    st.push_back(2);
    st.push_back(3);
    st.push_back(4);
    st.push_back(5);
    cout << st << endl;
    cout << "Size: " << st.get_size() << endl;
    cout << "Capacity: " << st.get_capacity() << endl;

    // Test copy constructor
    Stack<int> st2(st);
    cout << st2 << endl;
    cout << "Size: " << st2.get_size() << endl;
    cout << "Capacity: " << st2.get_capacity() << endl;

    // Test auto resize
    st.push_back(6);
    cout << st << endl;
    cout << "capacity: " << st.get_capacity() << endl;
    st.push_back(7);
    cout << "capacity: " << st.get_capacity() << endl;

    // Test pop and peek
    for (int i = 0; i < 5; i++) {
        cout << "Popped: " << st.pop_back() << endl;
        cout << "Peek: " << st.peek_back() << endl;
    }
    cout << st << endl;
    // Write similar tests for Stack and validate your implementation
}