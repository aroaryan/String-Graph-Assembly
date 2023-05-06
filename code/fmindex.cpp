#include "fmindex.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "fmindex.h"

std::vector<std::string> rotate(std::string to_match){

   std::vector<std::string> out;

  for (uint i = 0; i < to_match.size(); ++i) {
    out.push_back(to_match.substr(i) + to_match.substr(0, i));
  }
  std::sort(out.begin(), out.end());
  return out;
}



FMIndex::FMIndex(std::string to_match, std::string a){


  std::sort(a.begin(), a.end()); 
  alpha = a;


  BWT = buildBWT(to_match);
  SA = SuffixArray(to_match);
  OT = OccurrenceTable(BWT);
}



std::vector<int> FMIndex::SuffixArray(std::string to_match){
  std::vector<int> sarray;

  std::vector<std::pair<std::string, int>> sufList;
  
  to_match = to_match + "$";
  uint tlen = to_match.size();

  for (uint i = 0; i < tlen; ++i){
    std::string t_suf = to_match.substr(i);
    sufList.push_back(make_pair(t_suf, i));
  }

  std::sort(sufList.begin(),sufList.end()); 

  for (uint i = 0; i < tlen; ++i){
      sarray.push_back(sufList[i].second);
  }

  return sarray;
}



std::string FMIndex::buildBWT(std::string to_match){

  std::string out;
  std::vector<std::string> rotation = rotate(to_match+'$'); 
  for (std::string s: rotation) {
    out += s[s.length()-1];
  }
  return out;
}



std::vector<std::vector<int>> FMIndex::OccurrenceTable(std::string to_match){
  std::vector<std::vector<int>> OT;


  uint alphabet_size = alpha.length();

  OT.resize(to_match.size(), std::vector<int>(alphabet_size, 0));

  for (uint i = 0; i < alphabet_size; i++) {
    if (alpha[i] == to_match[0]) OT[0][i]++;
    for (uint j = 1; j < to_match.size(); j++) {
      if (alpha[i] != to_match[j]) 
        OT[j][i] = OT[j-1][i];
      else 
        OT[j][i] =  OT[j-1][i] + 1;
    }
  }

  return OT;
}


std::pair<int, int> FMIndex::get_frange(std::string c, int s_rank, int e_rank){
  std::pair<int, int> out;

  std::string F;
  std::vector<std::string> rotations = rotate(destructBWT(BWT));
  for (uint i = 0; i < rotations.size(); i++) {
    F += rotations[i][0];
  }
  std::vector<int> occ;
  for (uint i = 0; i < F.length(); i++) {
    if (c[0] == F[i]) occ.push_back(i);
  }
  if (s_rank == (int) occ.size()) {
    out.first = occ[s_rank % occ.size()] + 1;
  }
  out.first = occ[s_rank] + 1;
  out.second = occ[e_rank] + 1;
  
  return out;
}

std::string FMIndex::destructBWT(std::string bwt){

  std::string out;
  std::vector<std::string> vec;
  for (auto s: bwt) {
    vec.push_back(std::string(1, s));
  }
  for (uint i = 0; i < vec.size(); ++i) {
    std::sort(vec.begin(), vec.end());
    for (uint j = 0; j < vec.size(); ++j) {
      vec[j] = bwt[j]+vec[j];
    }
  }
  for (auto s: vec) {
    if (s[s.size()-1] == '$')
      out = s;
  }
  
  return out.substr(1, out.size()-2);
}


std::pair<int, int> FMIndex::get_lrange(std::string c, int s_index, int e_index){
  std::pair<int, int> out;

  std::string L = BWT;

  for (uint i = 0; i < L.size(); i++) {
    if (c[0] == L[i] && (int) i < s_index) {
      out.first++;
    } 
    if ((int) i <= e_index && c[0] == L[i]) {
      out.second++;
    }
  }
  return out;
}



std::vector<int> FMIndex::search(std::string sequence){
  std::vector<int> outList;

  std::string c = sequence.substr(sequence.size()-1,1);

  int letter = alpha.find(c);
  

  if (letter == -1){
    outList.push_back(-1);
    return outList;
  }
  

  std::vector<int> F = OT.back();


  int s_rank = F[letter];
  int e_rank = -1; 
  if (letter + 1 <= (int) alpha.length()) {
    e_rank = F[letter + 1] - 1;
  } else {
    e_rank = F.size() - 1;
  }


  if (e_rank == -1){
    outList.push_back(-1);
    return outList;
  }


  std::pair<int,int> frange = get_frange(c, s_rank, e_rank);


  for(int i = sequence.size()-2; i >= 0; i--){
    c = sequence.substr(i,1);

    letter = alpha.find(c);


    std::pair<int,int> lrange = get_lrange(c, frange.first, frange.second);


    int numMatches = lrange.second - lrange.first + 1;


    if(numMatches <= 0){
      outList.push_back(-1);
      return outList;
    }


    frange = get_frange(c, lrange.first, lrange.second - 1);

    if( frange.first == -1 || frange.second == -1){
      outList.push_back(-1);
      return outList;
    }
  }


  for(int i = frange.first; i < frange.second + 1; ++i){
    outList.push_back(SA[i]);
  }

  return outList;
}


// std::vector<std::string> findMostRepeatedPatterns(const std::string& text, int n) {

//   // FMIndex fmi = FMIndex(text, text);

//     std::vector<std::string> lcs;
//     for (int i = 0; i < bwt.length(); i++) {
//         if (bwt[i] == '$') {
//             continue;
//         }
//         int j = i;
//         std::string substring = "";
//         while (bwt[j] != '$') {
//             substring += bwt[j];
//             j = occ(bwt[j], j) + C[bwt[j]];
//         }
//         lcs.push_back(substring);
//     }

//     // count the frequency of each LCS using the FM-Index
//     std::unordered_map<std::string, int> frequency;
//     for (const auto& pattern : lcs) {
//         int count = countOccurrences(pattern, fmIndex);
//         if (count > 1) {
//             frequency[pattern] = count;
//         }
//     }

//     // sort the LCS by frequency
//     std::vector<std::pair<std::string, int>> sortedPatterns(frequency.begin(), frequency.end());
//     std::sort(sortedPatterns.begin(), sortedPatterns.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
//         return a.second > b.second;
//     });

//     // output the top n most repeated patterns
//     std::vector<std::string> mostRepeatedPatterns;
//     for (int i = 0; i < n && i < sortedPatterns.size(); i++) {
//         mostRepeatedPatterns.push_back(sortedPatterns[i].first);
//         std::cout << sortedPatterns[i].first << ": " << sortedPatterns[i].second << std::endl;
//     }

//     return mostRepeatedPatterns;
// }
