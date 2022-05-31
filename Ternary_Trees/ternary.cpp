#include <iostream>
#include <string>
using namespace std;


struct TernaryNode{
    bool complete;
    int ele1;
    int ele2;
    TernaryNode *left;
    TernaryNode *right;
    TernaryNode *mid;
};

//initiallize the TernaryNode
TernaryNode* newtree(){
    TernaryNode* temp = new TernaryNode;
    temp->complete = false;
    temp->ele1 = 0;
    temp->ele2 = 0;
    temp->left = nullptr;
    temp->mid = nullptr;
    temp->right = nullptr;
    return temp;
}

//root is subroot that data need to insert, data is the value will be add to the tree.
void insert(TernaryNode*& root, int data){
    //first case: no data in the tree
    if(root==nullptr){
        root =new TernaryNode;
        root->ele1 = data;
        root->left=nullptr;
        root->mid=nullptr;
        root->right=nullptr;

    }
    // second case: only have one element in the root or subroot
    else if (!root->complete){
        if(data <= root->ele1){
            root->ele2 = root->ele1;
            root->ele1 = data;
        }
        else
            root->ele2 = data;
        root->complete = true;
    }
    // third case: data smaller than the ele1, the data become left child
    else if(data <= root->ele1){
        insert(root->left,data);
    }

    //forth case: data bigger than the ele1 and smaller than the second one
    //the data become the mid child
    else if(data > root->ele1 && data < root->ele2){
        insert(root->mid,data);
    }

    //fifth case: data bigger than ele2, data become right child
    else if(data > root->ele2){
        insert(root->right,data);
    }
}

//print the result
void print_node(TernaryNode*& root){
    //check if there it include data
    if(root==NULL){
        return;
    }
    //check if the node has left child. If so, print left child
    if (root->left!=nullptr){
    cout<<"(";
    print_node(root->left);
    cout<<")"<<" ";
    }
    //print the first data
    cout<<root->ele1;
    //check if the node has middle child. If so, print middle child
    if (root->mid!=nullptr){
        cout << " (";
        print_node(root->mid);
        cout<<")"<<" ";
    }
    //check if there is two value. If so, print the seconde(larger) value
    if (root->complete)
        cout<<" " << root->ele2;
    //check if the node has right child. If so, print right child
    if (root->right!=nullptr){
        cout<<" (";
        print_node(root->right);
        cout<<")";
    }
}
//get the data from input and inset to the tree.
int main(int argc, char** argv){
    TernaryNode *root = nullptr;
    int n = stoi(argv[1]);
    int child;
    for (int i = 0; i<n; i++){
        cin>>child;
        insert (*&root, child);
    }
    print_node(root);
}