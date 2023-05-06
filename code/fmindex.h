#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>

#include "./debruijn.h"

class FMIndex
{
    public:
        

        FMIndex(std::string to_match, std::string alpha);



        std::vector<int> SuffixArray(std::string to_match);



        std::string buildBWT(std::string to_match);
        std::string destructBWT(std::string to_match);


        std::vector<std::vector<int>> OccurrenceTable(std::string to_match);



        std::vector<int> search(std::string sequence);



        std::pair<int, int> get_frange(std::string c, int s_rank, int e_rank);


        std::pair<int, int> get_lrange(std::string c, int s_index, int e_index);

        std::string BWT; 
        std::string alpha; 
        std::vector<int> SA;
        std::vector<std::vector<int>> OT;

};

std::vector<std::string> rotate(std::string to_match);
int findChar(std::string alpha, std::string c);