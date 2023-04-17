#include "readFile.h"

using namespace std;

void readFile(std::string filename) {
    

    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        // 
    }

    string line;
    string sequence = "";
    while (getline(file, line)) {
        // ignore header line(s) starting with ">"
        if (line[0] == '@') {
            continue;
        }
        // cout << line << "\n";
        sequence += line;
    }

    cout << "Sequence: " << sequence << endl;
}
