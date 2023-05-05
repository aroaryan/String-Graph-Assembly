#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>

#include "./debruijn.h"

class FMI
{
    public:
        std::string BWT; 
        std::string alpha; 
        std::vector<int> SA;
        std::vector<std::vector<int>> OT;

        FMI(std::string T, std::string alpha, int sr = 1);
        std::vector<int> buildSA(std::string T);
        std::string buildBWT(std::string T);
        std::vector<std::vector<int>> buildOT(std::string T);
        std::vector<int> search(std::string P);
        std::pair<int, int> get_frange(std::string c, int s_rank, int e_rank);
        std::pair<int, int> get_lrange(std::string c, int s_index, int e_index);


};

std::vector<std::string> rotate(std::string T);
int findChar(std::string alpha, std::string c);