#include "huffman-tree.cpp"
#include "constants.h"

// given a compressed binary string, convert it to the original string using the huffman tree
string inflate(const string &compressed, const tree *huffman_tree)
{ 
    string ans="";
    const tree* curr = huffman_tree;

    int len = compressed.length();
    for(int i=0; i<len; i++){
        if(compressed[i] == '0'){
            curr = curr->left;
        }else{
            curr = curr->right;
        }

        if(curr->left == nullptr && curr->right == nullptr){
            ans += curr->value;
            curr = huffman_tree;
        }

    }
    return ans;
 }

// Finding the encoding for a particular char
 void solve(tree* root, map<string,string>& ans, string& path){
        if(root==nullptr) return;
        if(root->left == nullptr && root->right == nullptr){
            if(!path.empty()) {
                // ans = {(root->left)->value, path};
                ans[root->value] = path;
            }
            return;
        }

        path.push_back('0');
        if(root->left) solve(root->left, ans, path);
        path.pop_back();    // backTrack

        path.push_back('1');
        if(root->right) solve(root->right, ans, path);
        path.pop_back();
    }

// given a string, compress it using the huffman tree and return the resulting binary string
string deflate(const string &buf, tree* &huffman_tree)
{ 
    string ans="";
    map<string, string> encoding;
    string path;
    solve(huffman_tree, encoding, path);

    for(int i=0; i<buf.length(); i++){
        string ch = "" + buf[i];
        ans += encoding[ch];
    }
    
    return ans;
}