#include <stdlib.h>
#include <queue>
#include<unordered_map>
#include<map>
#include<string>
#include<vector>
#include <stdio.h>
#include <iostream>


using namespace std;

struct Node {
    char c;
    int count;
    struct Node *left;
    struct Node *right;
};
/*
for compare, I used https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator/48587737
for some help on how to use a compare in a priority queue. I was not sure how to set a comparitor for different items like nodes.
*/
class compare {
    public :
        bool operator()(Node* l_node, Node* r_node) {
            if(l_node->count > r_node->count) {
                return true;
            } 
            else {
                return false;
            }
        }
};
unordered_map<char,int> get_frequencies(string s);
Node* newNode(char new_c, int new_count, Node* l, Node* r);
Node* newNode(char new_c, int new_count);
Node* make_tree(string s);
void encode(string s, Node* n, unordered_map<char,string>& e);
void decode(string s, Node* n);



int main() {
    string s;
    cout << "enter string: ";
    
    getline(cin, s);
    Node* top = make_tree(s);

    unordered_map<char,string> e;
    encode("",top,e);

    string encoded_string = "";
    for(int i = 0; i < s.size(); i++) {
        encoded_string += e[s[i]];
    }
    cout << "encode table: " << endl;
    for(auto i: e) { //print encoded table
        cout << "character: " << i.first << ", code: " << i.second << endl;
    }
    cout << "encoded string:" << endl;
    cout << encoded_string << endl;
    cout << "decoded string: " << endl;
    decode(encoded_string,top);



}

unordered_map<char,int> get_frequencies(string s) {
    unordered_map<char,int> u;
    for(int i = 0; i < s.size(); i++) { //freq
        if(u.find(s[i]) != u.end()) {
            u[s[i]] += 1;
        }
        else {
            u[s[i]] = 1;
        }
    }
    return u;
}

Node* newNode(char new_char, int new_count, Node* l, Node* r) {
    Node* n = new Node();
    n->c = new_char;
    n->count = new_count;
    n->right = r;
    n->left = l;
    return n;
}

Node* newNode(char new_char, int new_count) {
    Node* n = new Node();
    n->c = new_char;
    n->count = new_count;
    n->right = nullptr;
    n->left = nullptr;
    return n;
}

Node* make_tree(string s) {
    Node* left;
    Node* right;
    Node* n;
    unordered_map<char,int> u = get_frequencies(s);
    priority_queue<Node*,vector<Node*>,compare> q;

    cout << "frequency table: " << endl;
    for(auto i: u) { // put things from the map into the queue
        cout << "character: " << i.first << ", frequency: " << i.second << endl;
        n = newNode(i.first,i.second);
        q.push(n);
    }

    while(q.size() > 1) { //make tree
        left = q.top();
        q.pop();
        right = q.top();
        q.pop();
        n = newNode('\0',left->count + right->count, left, right);
        q.push(n);
    }
    return q.top();
}

void encode(string s, Node* n, unordered_map<char, string>& e) {
    if(n == nullptr) {
        return;
    }
    if(n->c != '\0') {
        e[n->c] = s; //add code to e
        return;
    }
    encode(s + "0", n->left, e); //go left and add 0
    encode(s + "1", n->right, e); //go right and add 1
}

void decode(string s, Node* n) {
    Node* temp = n;
    for(int i = 0; i < s.size(); i) {
        while(temp->c == '\0') {
            if(s[i] == '0') { //if string shows 0, go left
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
            i++;
        }
        cout << temp->c;
        temp = n;
    }
    cout << endl;
}
