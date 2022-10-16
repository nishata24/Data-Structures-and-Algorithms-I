//  Created by Nishat Ahmed on 2021-04-15.
//  ECE-264 DSA I
//  Stacks and Queues
//  This program implements stacks and queues in a singly linked list through the use of an abstract base class named SimpleList.

#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

//parent class P stores pointers to the first and last elements of the list and the list's name
template <class P>
//SimpleList stores the value of and pointer to the next Node for every Node in the list
class SimpleList {
    class Node {
    public:
        P value;
        Node* next;
    };
protected:
    Node* head, *tail;
    string name;
public:
//constructor
    SimpleList(){
        head = NULL;
        tail = NULL;
    }
    string getname(){
        return name;
    }
    virtual void push(P a) = 0;
    virtual P pop() = 0;
//function removes first (or top) node from list and returns what it has stored
    P remove_startNode() {
        if (head != NULL) {
            P value;
            Node* tmp = new Node;
            tmp = head;
            head = head->next;
            value = tmp->value;
            delete tmp;
            return value;
        }
    }
// function adds a Node to the end of the list, given what to store
    void addNode_end(P a) {
        Node* tmp = new Node;
        tmp->value = a;
        tmp->next = NULL;
        if (head == NULL) {
            head = tmp;
            tail = tmp;
            tmp = NULL;
        }
        else {
            tail->next = tmp;
            tail = tmp;
        }
    }
//function adds a Node to the start of the list, given what to store
    void addNode_start(P a) {
        Node* tmp = new Node;
        tmp->value = a;
        tmp->next = head;
        head = tmp;
    }
//function checks if list is empty
    bool checklist() {
        if (head == NULL){
            return false;
        }
        else {
            return true;
        }
    }
};

//child class of SimpleList for lists classified as queues
template <class P>
class Queue: public SimpleList<P> {
public:
//constructor
    Queue(string a) {
        this->head = NULL;
        this->tail = NULL;
        this->name = a;
    }
//function adds Node to the end of list
    void push(P a) {
        this->addNode_end(a);
    }
//function returns and deletes Node at the start of the list
    P pop() {
        return this->remove_startNode();
    }
};

//child class of SimpleList for lists classified as stacks
template <class P>
class Stack: public SimpleList<P> {
public:
//constructor
    Stack(string a) {
        this->head = NULL;
        this->tail = NULL;
        this->name = a;
    }
//function adds Node to the start of list
    void push(P a) {
        this->addNode_start(a);
    }
//function returns and deletes Node at the start of the list
    P pop() {
        return this->remove_startNode();
    }
};

//Class for functions that read/print files
class Files {
    string infile, outfile;
    //all integer stacks and queues
    list<SimpleList<int>*>listSLi;
    //all double stacks and queues
    list<SimpleList<double>*>listSLd;
    //all string stacks and queues
    list<SimpleList<string>*>listSLs;
    
    //read and write to the following files
    ifstream inputfile;
    ofstream outputfile;
    
public:
//functon checks all data is read from input file
    bool check_file_end() {
        if (inputfile.eof()) {
            return true;
        }
        else {
            return false;
        }
    }
//function asks user for input and output files
    void getfiles() {
        cout << "Please enter name of input file: ";
        cin >> infile;
        cout << "Please enter name of output file: ";
        cin >> outfile;
    }
//function opens input and output files
    void openfiles() {
        inputfile.open(infile);
        outputfile.open(outfile);
    }
//constructor
    Files() {
        getfiles();
        openfiles();
    }
//destructor
    ~Files() {
        inputfile.close();
        outputfile.close();
    }
//function reads commands and calls appropriate function based on command
    void read_command() {
        string command, name;
        int b = 0;
        inputfile>>command;
        inputfile>>name;
        if (name.substr(0,1) == "i") {
            b = 1;
        }
        else if (name.substr(0,1) == "d"){
            b = 2;
        }
        else {
            b = 3;
        }
        if (command == "create") {
            generate(b, name);
        }
        else if (command == "push") {
            push(b, name);
        }
        else if (command == "pop") {
            pop(b, name);
        }
    }
//function searches
    template <typename P>
    SimpleList<P>* Search(list<SimpleList<P>*>& typelist, string listname) {
        for (typename list<SimpleList<P>*>::iterator it = typelist.begin();       it != typelist.end(); ++it) {
            if (((*it)->getname()) == listname) {
                return *it;
            }
        }
        return nullptr;
    }
//function checks if list exists, if not a new list is generated
    void generate(int b, string name) {
        string list_type;
        inputfile >> list_type;
        outputfile << "PROCESSING COMMAND: create " << name << " " << list_type << "\n";
        if (b == 1) {
            SimpleList<int>* tmp = Search(listSLi, name);
            if (tmp != nullptr) {
                outputfile << "ERROR: This name already exists!\n";
            }
            else {
                SimpleList<int>* new_SLi;
                if (list_type == "queue") {
                    new_SLi = new Queue<int>(name);
                }
                else {
                    new_SLi = new Stack<int>(name);
                }
                listSLi.push_front(new_SLi);
            }
        }
        else if (b == 2) {
            SimpleList<double>* tmp = Search(listSLd, name);
            if (tmp != nullptr) {
                outputfile << "ERROR: This name already exists!\n";
            }
            else {
                SimpleList<double>* new_SLd;
                if (list_type == "queue") {
                    new_SLd = new Queue<double>(name);
                }
                else {
                    new_SLd = new Stack<double>(name);
                }
                listSLd.push_front(new_SLd);
            }
        }
        else {
            SimpleList<string>* tmp = Search(listSLs, name);
            if (tmp != nullptr) {
                outputfile << "ERROR: This name already exists!\n";
            }
            else {
                SimpleList<string>* new_SLs;
                if (list_type == "queue") {
                    new_SLs = new Queue<string>(name);
                }
                else {
                    new_SLs = new Stack<string>(name);
                }
                listSLs.push_front(new_SLs);
            }
        }
    }
//function finds list and calls its push function to add a new Node
    void push(int b, string name) {
        outputfile << "PROCESSING COMMAND: push " << name << " ";
        if (b == 1) {
            int value;
            inputfile >> value;
            outputfile << value << "\n";
            SimpleList<int>* tmp = Search(listSLi, name);
            if (tmp == nullptr) {
                outputfile << "ERROR: This name does not exist!\n";
            }
            else {
                tmp->push(value);
            }
        }
        else if (b == 2) {
            double value;
            inputfile >> value;
            outputfile << value << "\n";
            SimpleList<double>* tmp = Search(listSLd, name);
            if (tmp == nullptr) {
                outputfile << "ERROR: This name does not exist!\n";
            }
            else {
                tmp->push(value);
            }
        }
        else if (b == 3) {
            string value;
            inputfile >> value;
            outputfile << value << "\n";
            SimpleList<string>* tmp = Search(listSLs, name);
            if (tmp == nullptr) {
                outputfile << "ERROR: This name does not exist!\n";
            }
            else {
                tmp->push(value);
            }
        }
    }
//function finds list and calls its pop function to remove a Node
    void pop(int b, string name) {
        outputfile << "PROCESSING COMMAND: pop " << name << "\n";
        if (b == 1) {
            SimpleList<int>* tmp = Search(listSLi, name);
            if (tmp == nullptr) {
                outputfile << "ERROR: This name does not exist!\n";
            }
            else {
                if (tmp->checklist()) {
                    outputfile << "Value popped: " << tmp->pop() << "\n";
                }
                else {
                    outputfile << "ERROR: This list is empty!\n";
                }
            }
        }
        else if (b == 2) {
            SimpleList<double>* tmp = Search(listSLd, name);
            if (tmp == nullptr) {
                outputfile << "ERROR: This name does not exist!\n";
            }
            else {
                if (tmp->checklist()) {
                    outputfile << "Value popped: " << tmp->pop() << "\n";
                }
                else {
                    outputfile << "ERROR: This list is empty!\n";
                }
            }
        }
        else if (b == 3) {
            SimpleList<string>* tmp = Search(listSLs, name);
            if (tmp == nullptr) {
                outputfile << "ERROR: This name does not exist!\n";
            }
            else {
                if (tmp->checklist()) {
                    outputfile << "Value popped: " << tmp->pop() << "\n";
                }
                else {
                    outputfile << "ERROR: This list is empty!\n";
                }
            }
        }
    }
};

int main() {
    Files f1;
    //read entire file
    while (!f1.check_file_end()) {
        f1.read_command();
    }
    return 1;
}
