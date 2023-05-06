#include <iostream>
#include <fstream>
#include <string>

#include "code/readFile.h"
#include "code/debruijn.h"
#include "code/fmindex.h"
#include "code/needleman_wunsch.h"



using namespace std;

int main() {
    
    string filename;
    cout << "Enter the filename: ";
    getline(cin, filename);
    int kmer_length;
    cout << "Enter the length of the kmers: ";
    cin >> kmer_length;

    DeBruijnGraph dbg;
    dbg.chopString(kmer_length, filename);

    dbg.createGraph(); 

    std::cout << "GRAPH CREATED \n";

    dbg.formatGraph(); 

    dbg.outputGraph();

    // dbg.traversal();
    dbg.connectedComponents();


    std::string output_of_dbg = dbg.longestSequence();

    std::cout << "Longest Sequence: " << output_of_dbg << "\n";

    // FM

    // FMIndex to_construct = FMIndex (output_of_dbg, output_of_dbg);
    


    string f1 = "ACGT";
    string f2 = "ACGT";


    cout << needlemanWunschCost(f1, f2, 1.0, 1.0) << endl;




    // ReadFile data;
    // data.readsfiles(filename);



    
    
    return 0;
}
