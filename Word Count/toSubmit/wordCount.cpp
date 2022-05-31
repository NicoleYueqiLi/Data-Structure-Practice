#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
using namespace std;
const int MAX_SIZE = 10000;

class HashNode{
public:
    int frequency;
    string words;
    HashNode* next;
    HashNode();
    ~HashNode();
    void print();
};

HashNode::HashNode()
{
    this->words = "";
    this -> frequency = 0;
    this->next = NULL; 
}

HashNode::~HashNode()
{
    if (next)
        delete next;
}
void HashNode::print(){
    cout << words <<": " << frequency << endl;
}


/*---------------------------------------------*/


class LinkedList
{    
public:
    int frequency;
    HashNode *head;
    LinkedList();
    ~LinkedList();  
    HashNode* search(string st);
    void insert(string st);
    void print();
};

LinkedList::LinkedList()
{
    head = NULL;
    frequency = 0;
}

LinkedList::~LinkedList()
{
    if(head != NULL)
        delete head;
}

HashNode* LinkedList::search(string st){
    HashNode* Node = head;
    //looking for st
    while (Node != NULL)
    {
       if (Node->words == st)
            return Node;

        else
            Node = Node->next;
       
    }
    //if string st didn't find
    return NULL;
}
void LinkedList::insert(string st){
    //check if need to add st to the list;
    HashNode* Node = search(st);
    //if we already have st; just add the frenquency;
    if(Node != NULL){
        frequency += 1;
        Node->frequency += 1;
    }
    //if we don't have, add it to the list
    else{
        HashNode* newHashNode = new HashNode;
        newHashNode->words = st;
        newHashNode->frequency = 1;
        newHashNode->next = head;
        head = newHashNode;
        frequency += 1;
    }
}
void LinkedList::print(){
    if(head == NULL)
        return;
    else{
        HashNode* H = head;
        while (H != NULL)
        {
            H->print();
        }
        
    }
}


/*---------------------------------------------------------------------*/



class HashTable
{
    public:  
        HashTable();
        ~HashTable();
        int HashFunction(string st);
        void insert(string st);
        void print();
        int findFrenquency(string st);
        LinkedList* Table[MAX_SIZE];
};

HashTable::HashTable(){
    for(int i = 0; i < MAX_SIZE; i++){
        LinkedList* newLinkedList = new LinkedList;
        Table[i] = newLinkedList;
    }
}

HashTable::~HashTable()
{
    for(int i = 0; i < MAX_SIZE; i++)
        delete Table[i];
}

int HashTable::HashFunction(string st){
    int sumCha = 0;
    for (int i = 0; i < st.size();i++){
        sumCha += st[i];
    }
    int inde= sumCha % MAX_SIZE;
    return inde;
}
void HashTable::insert(string st){
    Table[HashFunction(st)]->insert(st);
}
void HashTable::print(){
    for(int i =0; i< MAX_SIZE; i++){
        Table[i]->print();
    }
}
int HashTable::findFrenquency(string st){
    int charID = HashFunction(st);
    HashNode* CharNode = Table[charID]->search(st);
    return CharNode->frequency;
}
/*---------------QuickSort-------------------------*/
void swap(string array[], int index1, int index2) {
    // cant swap on same index
    if (index1 == index2)
        return;
    string holder;
    holder = array[index1];
    array[index1] = array[index2];
    array[index2] = holder;
} 

int partition(string array[], int left, int right, HashTable *f = nullptr) {
    int pivot = right, index = left;
    for (int i = left; i < right; i++) {
        if (f == nullptr){
            if (array[i].compare(array[pivot]) > 0) {
                swap(array, i, index);
                index++;
            }
        }
        else{
            if ((f->findFrenquency(array[i])) < (f->findFrenquency(array[pivot]))) {
                swap(array, i, index);
                index++;
            } 
        }
    }
    swap(array, index, pivot);
    return index;
}

void quickSort(string array[], int left, int right, HashTable *f = nullptr) {
    int pivot; 
    if (left < right) {
        pivot = partition(array, left, right, f);       
        quickSort(array, left, pivot - 1, f);
        quickSort(array, pivot + 1, right, f);
    }
} 

/*---------------------main function---------------------*/
int main(int argc, char** argv){
    string list[MAX_SIZE];
    ifstream file("data.txt"); //opening text file
    string line;
    string token;

    int count = 0;
    while(getline(file, line))
    {   
        for (int i = 0; i < line.size(); i++){
            if (ispunct(line[i])){
                line[i] = ' ';
            }
        }
        stringstream ss(line);
        string word;
        
        while (ss >> word){
            if (word.size() == 0) continue;
            list[count]=word;
            count++;
        }
    }
    file.close();
    quickSort(list,0,count - 1);
    HashTable *Hashing = new HashTable;
    for (int i = 0; i < count; i++)
    {
        Hashing->insert(list[i]);
    }
    string newList[MAX_SIZE];
    int j = 0;
    for(int i=count; i>= 0; i--){
        if(list[i]!=list[i+1]){
            cout<<list[i]<<" ";
            cout<<Hashing->findFrenquency(list[i])<<endl;
            newList[j] = list[i];
            j++;
        }  
    }
    
    quickSort(newList, 0, j - 1, Hashing);
    cout << endl;
    for(int i=j-1; i>= 0; i--){
        cout<<newList[i]<<" ";
        cout<<Hashing->findFrenquency(newList[i])<<endl;
    }
}

    
    
        
    

        
    


    
   
        
            



   


