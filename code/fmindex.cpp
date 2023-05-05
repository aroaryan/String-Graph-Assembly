#include "fmindex.h"

/**
 * @file fmi.cpp
 * Code to constructiong and searching a FM Index
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "fmindex.h"

std::vector<std::string> rotate(std::string T){

  std::vector<std::string> out;

  for(size_t i =0; i < T.size(); i++) {
    std::string push = T.substr(i) + T.substr(0, i);
    out.push_back(push);

  }
  std::sort(out.begin(), out.end());
  return out;
}




FMI::FMI(std::string T, std::string a, int sr){
  // sampleRate = sr; 
  alpha = a;


  std::sort(alpha.begin(), alpha.end()); 

  BWT = buildBWT(T);
  SA = buildSA(T);
  OT = buildOT(BWT);
}



FMI::~FMI()
{
    /* nothing unless you added more variables */
}


std::vector<int> FMI::buildSA(std::string T){
  std::vector<int> sarray;

  std::vector<std::string> sList1;
  std::vector<int> sList2;
  
  T = T + "$";

  for(size_t i = 0; i < T.length(); i++) {
    std::string T_suffix = T.substr(i);
    sList1.push_back(T_suffix);
    sList2.push_back(i);
  }

  std::vector<std::pair<std::string, int>> arr;

  for(size_t i = 0; i < T.length(); i++) {
    arr.push_back({sList1.at(i),sList2.at(i)});
  }

  std::sort(arr.begin(),arr.end()); 

  for (size_t i = 0; i < T.length(); i++){
      sarray.push_back(arr[i].second);
  }

  return sarray;
}



std::string FMI::buildBWT(std::string T){

  std::string out;

  std::vector<std::string> rota = rotate(T+'$');

  for (std::string alphas: rota) {
    out += alphas[alphas.length()-1];
  }

  return out;
}


std::vector<std::vector<int>> FMI::buildOT(std::string T){
  std::vector<std::vector<int>> OT;


  size_t a_size = alpha.length();

  OT.resize(T.size(), std::vector<int>(a_size, 0));

  for(size_t i = 0; i < a_size; i++) {
    if(alpha.at(i) == T.at(0)) {
      OT.at(0).at(i)++;
    }
    for(size_t j = 1; j < T.size(); j++) {
      if (alpha[i] == T[j]) {
        OT[j][i] =  OT[j-1][i] + 1;
      } 
      else {
        OT[j][i] = OT[j-1][i];
      }
    }
  }


  return OT;
}

/**
* FM Index First Range Search
* Gives the index start and end position for the character 
* (and rank range) being searched
* 
* @param c The character being looked up
* @param s_rank The starting rank being searched 
* @param e_rank The ending rank being searched 
*
* HINT: You will have to reconstruct F from the BWT or the OT
*/
std::pair<int, int> FMI::get_frange(std::string c, int s_rank, int e_rank){
  std::pair<int, int> out;

  //YOUR CODE HERE
  std::string franges;

  std::string decoded;
  std::vector<std::string> vector;


  for (auto s: BWT) {
    vector.push_back(std::string(1, s));
  }

  for (size_t i = 0; i < vector.size(); i++) {
    std::sort(vector.begin(), vector.end());
    for (size_t j = 0; j < vector.size(); j++) {
      vector[j] = BWT[j]+vector[j];
    }
  }

  for (auto s: vector) {
    if (s[s.size()-1] == '$')
      decoded = s;
  }
  
  decoded = decoded.substr(1, decoded.size()-2);


  std::vector<std::string> motor = rotate(decoded);

  for (size_t i = 0; i < motor.size(); i++) {
    franges += motor[i][0];
  }

  std::vector<int> occurences;
  for (size_t i = 0; i < franges.length(); i++) {
    if (c[0] == franges[i]) occurences.push_back(i);
  }


  out.first = occurences[s_rank] + 1;
  out.second = occurences[e_rank] + 1;
  
  return out;
}


std::pair<int, int> FMI::get_lrange(std::string c, int s_index, int e_index){

  std::pair<int, int> out;

  std::string L = BWT;

  for (size_t i = 0; i < BWT.length(); i++) {
    if (c[0] == L[i] && (int) i < s_index) {
      out.first++;
    } 

    if ((int) i <= e_index && c[0] == L[i]) {
      out.second++;
    }
  }

  return out;
}
