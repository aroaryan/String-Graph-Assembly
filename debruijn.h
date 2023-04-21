#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Node {
    string data;

}

class DeBruijnGraph {
    public :
    std::vector<string> kmers;
    void chopString(int kmer_length);
    // void 
}