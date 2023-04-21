#include <iostream>
#include <fstream>
#include <string>

#include "readFile.h"

using namespace std;

int main() {
    string filename;
    cout << "Enter the filename: ";
    getline(cin, filename);


    ReadFile data;
    data.readsfiles(filename);

    
    
    return 0;
}
