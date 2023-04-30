#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ReadFile{
    public: 
    ReadFile() = default;
    void readsfiles(std::string fname);
    std::string extracted_sequence;
};
