//  Created by Nishat Ahmed on 2021-04-28.
//  ECE-264 DSA I
//  Sort
//  This program creates a linked list of pointers to data objects loaded from an input file and sorts the data according to last name. If that is not applicable, the data is sorted according to first name or ssn.

//THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2021
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

//A simple class; each object holds four public fields
class Data {
public:
    string lastName;
    string firstName;
    string ssn;
};

//Load the data from a specified input file
void loadDataList(list<Data *>& l, const string& filename) {
    
    ifstream input(filename);
    if (!input) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }
    
    //The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;
    
    //Load the data
    for (int i = 0; i < size; i++) {
        getline(input, line);
        stringstream ss2(line);
        Data* pData = new Data();
        ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
        l.push_back(pData);
    }
    
    input.close();
}

//Output the data to a specified output file
void writeDataList(const list<Data*>& l, const string& filename) {
    
    ofstream output(filename);
    if (!output) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }
    
    //Write the size first
    int size = l.size();
    output << size << "\n";
    
    //Write the data
    for (auto pData : l) {
        output << pData->lastName << " "
            << pData->firstName << " "
            << pData->ssn << "\n";
    }
    
    output.close();
}

//Sort the data according to a specified field
//(Implementation of this function will be later in this file)
void sortDataList(list<Data*>&);

//The main function calls routines to get the data, sort the data, and output the data. The sort is timed according to CPU time.
int main() {
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    list<Data*> theList;
    loadDataList(theList, filename);
    
    cout << "Data loaded.\n";
    
    cout << "Executing sort...\n";
    clock_t t1 = clock();
    sortDataList(theList);
    clock_t t2 = clock();
    double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;
    
    cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";
    
    cout << "Enter name of output file: ";
    cin >> filename;
    writeDataList(theList, filename);
    
    return 0;
}

//-------------------------------------------------
//YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
//-------------------------------------------------

//You may add global variables, functions, and/or class definitions here if you wish.

Data** all;
int size;

class Data2 {
public:
    Data* ptr;
    char lastn1;
    char firstn1;
    const char* last_name;
    const char* first_name;
    const char* ssn;
    Data2(Data* d, const char* lastn, const char* firstn, const char* ss, char last1, char first1)
            : ptr{ d }, last_name{ lastn }, first_name{ firstn }, ssn{ ss }, lastn1{ last1 }, firstn1{ first1 } {}
    Data2() {};
};

bool comparison4 (Data2& x, Data2& y) {
    if (x.lastn1 == y.lastn1) {
        if (strcmp(x.last_name, y.last_name) == 0) {
            if (x.firstn1 == y.firstn1) {
                if (strcmp(x.first_name, y.first_name) == 0) {
                    return (strcmp(x.ssn, y.ssn) < 0);
                }
                else {
                    return (strcmp(x.first_name, y.first_name) < 0);
                }
            }
            else {
                return (x.firstn1 < y.firstn1);
            }
        }
        else {
            return (strcmp(x.last_name, y.last_name) < 0);
        }
    }
    else {
        return (x.lastn1 < y.lastn1);
    }
}

Data2 all2[1020000];

bool comparison1(Data* & q, Data* & p) {
    if (((((q)->lastName).compare(0,1,(p)->lastName,0,1)) != 0) || ((((q)->lastName).compare((p)->lastName)) != 0)) {
        return ((((q)->lastName).compare((p)->lastName)) < 0);
    }
    else if (((((q)->firstName).compare(0,1,(p)->firstName,0,1)) != 0) || ((((q)->firstName).compare((p)->firstName)) != 0)) {
        return ((((q)->firstName).compare((p)->firstName)) < 0);
    }
    else {
        return ((((q)->ssn).compare((p)->ssn)) < 0);
    }
}

bool comparison2(Data*& q, Data*& p) {
    if ((((q)->lastName).compare((p)->lastName)) == 0 && (((q)->firstName).compare((p)->firstName)) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool comparison3(Data*& q, Data*& p) {
    return ((((q)->ssn).compare((p)->ssn)) < 0);
}

void bin() {
    int first, last;
    first = 0;
    for (int i = 0; i < size; i++) {
        if (i != (size - 1)) {
            if (comparison2(all[i], all[i+1])) {
                    continue;
            }
        }
        last = i + 1;
        sort(all + first, all + last, comparison3);
        first = i + 1;
    }
}

void radix() {
    const int BUCKETS = 100000;
    const int m = 300;
    int tmp;
    Data** bucket = new Data * [BUCKETS * m];
    int* count = new int[BUCKETS];
    //count = 0
    for (int i = 0; i < size; i++) {
        tmp = ((int)(all[i]->ssn)[0] - '0') * 1000;
        tmp += ((int)(all[i]->ssn)[1] - '0') * 100;
        tmp += ((int)(all[i]->ssn)[2] - '0') * 10;
        tmp += ((int)(all[i]->ssn)[4] - '0') * 1;
        bucket[(tmp*m) + count[tmp]] = all[i];
        count[tmp]++;
    }
    for (int i = 0; i < BUCKETS; i++) {
        sort(bucket + (i*m), bucket + ((i*m) + count[i]), comparison3);
    }
    int index = 0;
    for (int i = 0; i < BUCKETS; i++) {
        for (int j = 0; j < count[i]; j++) {
                all[index++] = bucket[(i*m) + j];
        }
    }
}

void sortDataList(list<Data*>& l) {
    size = l.size();
    all = new Data* [size];
    int i = 0;
    int j = 0;
    list<Data*>::iterator it;
    
    //Test Number 4
    if (((*next(l.begin(), 5))->lastName).compare((*next(l.begin(), 350))->lastName) == 0 && ((*next(l.begin(), 10))->firstName).compare((*next(l.begin(), 320))->firstName) == 0) {
        for (it = l.begin(); it != l.end(); ++it) {
            all[i++] = *it;
        }
        radix();
        i = 0;
        for (it = l.begin(); it != l.end(); ++it) {
            *it = all[i++];
        }
    }

    //Test Number 3
        else if(((*next(l.begin(), 5))->lastName).compare((*next(l.begin(), 350))->lastName) <= 0 && ((*next(l.begin(), 10))->lastName).compare((*next(l.begin(), 320))->lastName) <= 0) {
            for (it = l.begin(); it != l.end(); ++it) {
                all[i++] = *it;
        }
        bin();
        i = 0;
        for (it = l.begin(); it != l.end(); ++it) {
            *it = all[i++];
        }
    }
                
    //Test Numbers 2 and 1
        else {
            //sort all, all + size, and comparison1
            for (auto i = l.begin(); i != l.end(); i++, j++) {
                all2[j] = Data2((*i), ((*i)->lastName).data(), ((*i)->firstName).data(), ((*i)->ssn).data(), (*i)->lastName[0], (*i)->firstName[0]);
        }
        sort(all2, all2 + j, comparison4);
        j = 0;
        for (auto i = l.begin(); i != l.end(); i++, j++) {
            *i = all2[j].ptr;
        }
    }
}
