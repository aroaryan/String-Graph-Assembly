#include "./readFile.h"

using namespace std;

void ReadFile::readsfiles(std::string filename) {
    

    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
    }

    string line;
    string sequence = "";
    // size_t i = 0;
    while (getline(file, line)) {
        // ignore header line(s) starting with ">"
        if (line[0] == '@') {
            continue;
        }
        // cout << line << "\n";
        sequence += line;

        // std::cout << i << "\n";
        // i++;
    }

    std::cout << "File Extracted \n";

    // cout << "Sequence: " << sequence << endl;
    extracted_sequence = sequence;
}
