#include <iostream>
#include <queue>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
using namespace std;
const int MAX_KID=100;
const int MAX_Relationships = 99;
const int MAX_Family = 99;
const int DUMMY = 0;

class family;


/*--------------------relationship----------------------*/
class relationship{
public:
    int num;
    family *parent;
    family *marrige;
    relationship(int newnum = 0, family *newParent = nullptr, family *newMarrige=nullptr );
    ~relationship();
    void print();
};

relationship::relationship(int newnum, family *newParent, family *newMarrige){
    num = newnum;
    parent = newParent;
    marrige = newMarrige;
}

relationship::~relationship(){
}

void relationship::print(){
    cout<<"Person "<< num;
}

/*--------------------Family_Member----------------------*/
class family{
public:
    int num;
    relationship *husband;
    relationship *wife;
    relationship *kid[MAX_KID];
    int num_kid;
    family(int newNum = 0, relationship *husband = nullptr,  relationship *wife=nullptr);
    ~family();
    void addKid(relationship *kid[], int num_kid);
};

family::family(int newNum, relationship *newHusband, relationship *newWife){
    num = newNum;
    num_kid = 0;
}

family::~family(){
}

void family::addKid(relationship *newChildren[], int num_kids){
    if (num_kids > 0) {
        for (int i = num_kid, j = 0; i < MAX_KID && j < num_kids; i++, j++) {
            kid[i] = newChildren[j];
            num_kid++;
             // throw a error message if we maxed out the size of children[]
            if (num_kid>= MAX_KID) {
                //  cout << "Max number of children reached in family " << num << endl;
                 break;
            }
        }
    }
}            


/*--------------------Graph----------------------*/
class Graph{
public:
    int numPerson;
    int numFamily;
    bool kids_filled[MAX_Relationships + 1];
    bool family_filled[MAX_Family + 1];
    relationship* relationships[MAX_Relationships+1];
    family* families[MAX_Family+1];
    void Family(int Family_num, int husband_num, int wife_num, relationship *kid[],int num_kid);
    Graph();
    ~Graph();
};

Graph::Graph()
{
    numPerson = numFamily = 0;
    for(int i =0; i< MAX_Family+1; i++){
        auto f = new family;
        families[i]= f;
        families[i]->num = i;
    }
    for(int i =0; i< MAX_Relationships+1; i++){
        auto r = new relationship;
        relationships[i]= r;
        relationships[i]->num = i;
    }
}

Graph::~Graph()
{
}


void Graph::Family(int Family_num, int husband_num, int wife_num,relationship *kid[], int num_kid ){
    if(Family_num>DUMMY){
        families[Family_num]->husband = relationships[husband_num];
        families[Family_num]->wife = relationships[wife_num];
        relationships[husband_num]->marrige = families[Family_num];
        relationships[wife_num]->marrige = families[Family_num];
        families[Family_num]->addKid(kid,num_kid);
        for(int i = 0; i < num_kid; i++){
            kid[i]->parent = families[Family_num];
        }
        numFamily++;
        cout<<"Family "<<Family_num <<" has husband "<<husband_num<<", wife "<<wife_num;
        if(num_kid>0){
            cout<<", and children ";
            for(int i =0; i<families[Family_num]->num_kid; i++){
                cout<<families[Family_num]->kid[i]->num;
                if(i==families[Family_num]->num_kid-1)
                    cout<<"."<<endl;
                else
                    cout<<",";
            }
                
        }
        else
            cout<<", and children."<<endl;

        // family_filled.push_back(Family_num);
        family_filled[Family_num] = true;
    }
    else
        cout<<"invild";
}

/*--------------------SetType for union find---------------------*/
class Set{
public:
    int id; // 1 - 99: Person; 101 - 199: Families
    Set* parent;
    bool unionfind(int firstid, int secondin);
    Set(int newid = 0, Set *newparent = nullptr);
    ~Set();
};

Set::Set(int newid, Set *newparent){
    id = newid;
    parent = newparent;
}

Set::~Set()
{
}

Set* findbiggestsetid(Set* node){
    Set* curr = node;
    while (curr->parent != nullptr) curr = curr->parent;
    return curr;
}

/*-------------------creat family strcut--------------------------*/
int Family_Com (Graph *G, stringstream& command, string& token, const char delim, Set* setlist[], int newid){
    int family_num, husband_num, wife_num;
    int res_newid = newid;
    relationship* kid[MAX_KID];
    Set* r_set;
    Set* f_set;
    Set* newset;
    getline(command, token, delim); // token = familyID
    family_num= stoi(token);
    // Check if family num already exists
    if(G->family_filled[family_num]){
        cout << "\tFamily " << family_num << " has already been entered." << endl;
        return res_newid;
    }
    f_set = findbiggestsetid(setlist[family_num + MAX_Relationships + 1]);
    getline(command, token, delim); // token = DONT CARE
    getline(command, token, delim); // token = husbandID
    husband_num = stoi(token);
    getline(command, token, delim); // token = DONT CARE
    getline(command, token, delim); // token = wifeID
    wife_num = stoi(token);
    // Check if husband & wife already exists
    for(int i=0; i<MAX_Relationships+1; i++){
        if(G->family_filled[i]){
            if(husband_num > 0 && G->families[i]->husband->num == husband_num){
                cout << "\tHusband " << husband_num << " is already married." << endl;
                return res_newid;
            }
            if(wife_num > 0 && G->families[i]->wife->num == wife_num){
                cout << "\tWife " << wife_num << " is already married." << endl;
                return res_newid;
            }
        }
    }
    getline(command, token, delim); // token = DONT CARE
    int num_kid =0;
    while(getline(command, token, delim)){
        int kids = stoi(token);
        if(G->kids_filled[kids]){
            cout << "\tChild " << kids << " is already parented." << endl;
            return res_newid;
        }
        else G->kids_filled[kids] = true;
        kid[num_kid]=G->relationships[kids];
        num_kid++;
        getline(command, token, delim); // token = DONT CARE
        // Connect in sets
        r_set = findbiggestsetid(setlist[kids]);
        if(r_set->id != f_set->id){
            newset = new Set;
            newset->id = res_newid++;
            f_set->parent = newset;
            r_set->parent = newset;
            f_set = newset;
        }
    }
    G->family_filled[family_num] = true;
    G->Family(family_num,husband_num,wife_num,kid,num_kid);
    r_set = findbiggestsetid(setlist[husband_num]);
    if(r_set->id != f_set->id){
        newset = new Set;
        newset->id = res_newid++;
        f_set->parent = newset;
        r_set->parent = newset;
        f_set = newset;
    }
    r_set = findbiggestsetid(setlist[wife_num]);
    if(r_set->id != f_set->id){
        newset = new Set;
        newset->id = res_newid++;
        f_set->parent = newset;
        r_set->parent = newset;
        f_set = newset;
    }
    return res_newid;
}

/*-------------------print the shortest path--------------------------*/
void printpath(int preds[], int target){
    int curr = target;
    int size = 0;
    int record[MAX_Relationships + MAX_Family];
    while(curr > 0){
        record[size] = curr;  
        curr = preds[curr];
        size++;
    }
    cout << "Relation: ";
    for(int i=size-1; i >= 0; i--){
        if(record[i] <= MAX_Relationships) cout << "person " << record[i];
        else cout << "family " << record[i] - MAX_Family - 1;
        if(i != 0) cout << " -> ";
    }
    cout << endl;

}
/*-------------------Breadth First Search--------------------------*/
void BFS(Graph* G, int id1, int id2){
    bool visited[MAX_Relationships + MAX_Family + 2];
    int preds[MAX_Relationships + MAX_Family + 2];
    int fid;
    int curr;
    // fill with false bools for visited[] and -1 for pred[]
    for (int i = 0; i < MAX_Relationships + MAX_Family + 2; i++) {
        visited[i] = false;
        preds[i] = -1;
    }
    // queue of nodes
    queue<int> todo;
    visited[id1] = true;
    todo.push(id1);
    while(!todo.empty()) {
        curr = todo.front();
        todo.pop();
        if(curr <= MAX_Relationships){
            if(G->relationships[curr]->marrige != nullptr){
                fid = G->relationships[curr]->marrige->num + MAX_Relationships + 1;
                if(fid > MAX_Relationships + 1 && !visited[fid]){
                    visited[fid] = true;
                    preds[fid] = curr;
                    todo.push(fid); 
                }
            }
            if(G->relationships[curr]->parent != nullptr){
                fid = G->relationships[curr]->parent->num + MAX_Relationships + 1;
                if(fid > MAX_Relationships + 1 && !visited[fid]){
                    visited[fid] = true;
                    preds[fid] = curr;
                    todo.push(fid);
                }
            }
        } else {
            if(G->families[curr - MAX_Family - 1]->husband != nullptr){
                fid = G->families[curr - MAX_Family - 1]->husband->num;
                if (fid > 0 && !visited[fid]) {
                    visited[fid] = true;
                    preds[fid] = curr;
                    todo.push(fid);
                    if (fid == id2) {
                        printpath(preds, id2);
                        return;
                    }
                }
            }
            if(G->families[curr - MAX_Family - 1]->wife != nullptr){
                fid = G->families[curr - MAX_Family - 1]->wife->num;
                if (fid > 0 && !visited[fid]) {
                    visited[fid] = true;
                    preds[fid] = curr;
                    todo.push(fid);
                    if (fid == id2) {
                        printpath(preds, id2);
                        return;
                    }
                }
            }
            for (int i = 0; i < G->families[curr - MAX_Family - 1]->num_kid; i++) {
                fid = G->families[curr - MAX_Family - 1]->kid[i]->num;
                if (fid > 0 && !visited[fid]) {
                    visited[fid] = true;
                    preds[fid] = curr;
                    todo.push(fid);
                    if (fid == id2) {
                        printpath(preds, id2);
                        return;
                    }
                }
            }
        }
        
    }
    return;
}



int main(int argc, char** argv){
    Graph* G = new Graph;
    string file_name = argv[argc-1];
    ifstream cin(file_name); //opening text file, get from makefile
    string line; 
    getline(cin, line, '\n');
    // tokenize the command
    stringstream command(line);
    string token;
    const char delim = ' ';

    // Construct sets for relationships and families
    Set* setlist[MAX_Relationships + MAX_Family + 2];
    int newid = MAX_Relationships + MAX_Family + 2;
    for(int i=0; i < MAX_Relationships + MAX_Family + 2; i++){
        Set* s = new Set;
        setlist[i] = s;
        setlist[i]->id = i;
    }
    // loop through the input file
    int rid1, rid2;
    while(getline(command, token, delim) && !cin.fail()) {
        if (toupper(token[0]) == 'F') {
            newid = Family_Com(G, command, token, delim, setlist, newid);
        } else if (toupper(token[0]) == 'R') {
            getline(command, token, delim); // token = rid1
            rid1 = stoi(token);
            getline(command, token, delim); // token = rid2
            rid2 = stoi(token);
            if(findbiggestsetid(setlist[rid1])->id == findbiggestsetid(setlist[rid2])->id){    
                BFS(G, rid1, rid2);
            } else {
                cout << rid1 << " and "<< rid2 << " are not related" << endl;
            }
            
        }
        getline(cin, line, '\n');
        // clear out stringstream object for reuse
        command.clear();
        command.seekg(0, ios::beg);
        command.str(line);
    }

}


