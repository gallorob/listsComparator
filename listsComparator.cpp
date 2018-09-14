#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

const int ERROR_VALUE = 1;
const int OK_VALUE = 0;

int main(int argc, char *argv[]) {
    // error message if not launched correctly
    if(argc<3) {
        cerr << "ERROR: Use ./listsComparator list1.txt list2.txt [list3.txt ...]" << endl;
        return(ERROR_VALUE);
    }

    // vector of string vectors containing list of games
    vector<vector<string>> lists;
    ifstream infile;
    // minimum sized vector index
    int min_vect = 0;

    // input cycle
    for(int i=1; i<argc; i++){
        // get data from text file, line by line
        infile.open(argv[i]);
        vector<string> temp;
        for(string line; getline(infile, line);) {
            temp.push_back(line);
        }
        infile.close();
        // check whether this vector has the least amount of elements
        if(i>1 && lists[min_vect].size() > temp.size()) {
            min_vect = i-1;
        }
        // put into vector of vectors
        lists.push_back(temp);
    }

    cout << "[ITEMS FOUND IN COMMON]" << endl;

    // comparison cycle
    for(int i=0; i<lists[min_vect].size(); i++) {
        bool found = true;
        for(int j=0; j<lists.size(); j++) {
            // search game in every lists
            if(find(lists[j].begin(), lists[j].end(), lists[min_vect][i]) == lists[j].end()) {
                // if not found, skip to the next game
                found = false;
                break;
            }
        }
        if(found) {
            cout << lists[min_vect][i] << endl;
        }
    }

    return OK_VALUE;
}
