#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <map>
#include <set>
#include <iostream>
using std::cout, std::endl, std::string;
using std::map, std::set, std::pair, std::make_pair;



// a node of the huffman tree. Already written, observe what is going on.
class tree{
public:
    double freq=0;
    string value = "┐"; // ┐/0/1/character. for now we just use just ┐.
    tree *left = nullptr, *right = nullptr;
    
    tree(){}
    tree(char value): value(1, value){}// Here strings special constructor is
    // invoked to take n copies of a character and form a string: std::string(n,val)
    tree(tree *left): left(left){}
    tree(tree *left, tree *right): left(left), right(right){}
    
    static tree *merge_trees(tree *left, tree *right){
        return new tree(left, right);
    }

    void print(const string &prefix="", bool isLeftChild=false){
        cout << prefix << (prefix==""?"└──":(isLeftChild? "├─0":"└─1"));
        // cout << "value:" << value << "|" << endl;
        if (isLeaf()) cout << "─[" << value << "]" << endl; else cout << value << endl;
        if (left) left->print(prefix + (isLeftChild?"│  ":"   "), true);
        if (right) right->print(prefix + (isLeftChild?"│  ":"   "), false);
    }
    bool isLeaf() const{ return !(left || right); }
    void get_codes(map<char, string> &map_in_progress, const string &prefix="") const{
        if (left){
            if (left->isLeaf()) map_in_progress[left->value[0]] = prefix + "0";
            else left->get_codes(map_in_progress, prefix + "0");
        }
        if (right){ 
            if (right->isLeaf()) map_in_progress[right->value[0]] = prefix + "1";
            else right->get_codes(map_in_progress, prefix + "1");
        }
    }
    ~tree() {
        delete left; delete right;
    }
};

class Compare {
    public:
    bool operator()(const tree* lhs, const tree* rhs) const {
        return lhs->freq < rhs->freq;
    }
};

// this returns the huffman tree using passed map of character to frequency
tree *huffman(const map<char, double> &freq_map)
{ 
    set<tree*, Compare> st;
    
    for(auto& pt: freq_map){

        tree* temp = new tree(pt.first);    //// creating the leaf node
        tree* t = new tree(temp);       /// creating the freq node
        t->freq = pt.second;
        st.insert(t);
    }

    //// now since set has all the tree nodes
    while(st.size()>1){
        tree* right = *st.begin();
        st.erase(right);
        tree* left = *st.begin();
        st.erase(left);

        right->value = "1";
        left->value = "0";
        
        tree* root = new tree(left, right);
        root->freq = left->freq + right->freq;

        st.insert(root);
    }

    tree* root = *st.begin();

    return root; 
}

// compute the frequencies of characters in the string. For part 3, make sure to skip over backreferences and also set highest priority to the special character.
map<char, double> get_freqs(const string &buf) 
{
    map<char, double> mp;
    int len = buf.length();
    for(int i=0; i<len; i++){
        char c = buf[i];

        mp[c]++;
    }
    
    return mp; 
}

#endif