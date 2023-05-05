
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Aryan Arora                Environment : ubuntu:latest               //
//  Date ......: 2023/05/01                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

#include "../code/readFile.h"
#include "../code/debruijn.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>


/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
// constexpr int kBoardWidth = 7;
// constexpr int kBoardHeight = 6;

// const in

bool checkRead(std::string& extracted_sequence, std::string& desired_sequence) {
    
    return extracted_sequence == desired_sequence;

}

bool checkInvalidChar(std::string& extracted_sequence) {
    for(char& ch: extracted_sequence) {
        // std::cout << ""
        if(! (ch == 'A' || ch == 'T' || ch == 'C' || ch == 'G')) return false;
    }

    return true;
}

// bool checkNodeEqual(Node& input, Node& output) {
//     REQUIRE(input.data == output.data);
//     REQUIRE(input.outgoingEdges.size() == output.outgoingEdges.size());
    

//     // REQUIRE(input.outgoingEdges)

// }

// void test_graph(std::unordered_map<std::string, Node>& input_graph, std::vector<Node>& desired_output) {
//     // REQUIRE(desired_output.size() == input_graph.size());

//     // for(Node& n: desired_output) {
//     //     REQUIRE(checkNodeEqual)
//     // }
//     // REQUIRE
// }

// bool 




// bool AreEqual(DiskType solution[][kBoardWidth],
//               DiskType student[][kBoardWidth]) {
//   for (int i = 0; i < kBoardHeight; ++i) {
//     for (int j = 0; j < kBoardWidth; ++j) {
//       if (solution[i][j] != student[i][j]) return false;
//     }
//   }
//   return true;
// }

// void DoDuplicate (DiskType solution[][kBoardWidth], DiskType student[][kBoardWidth]) {
//   for (int i = 0; i < kBoardHeight; ++i) {
//     for (int j = 0; j < kBoardWidth; ++j) {
//       student[i][j] = solution[i][j];
//     }
//   }
//   return;
// }


/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases ReadFile//
/////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("ReadFile - Check Invalid Characters", "[InvalidChar]") {
    ReadFile data;
    data.readsfiles("data/smallest.fasta");
    REQUIRE(checkInvalidChar(data.extracted_sequence));

    data.readsfiles("data/small.fasta");
    REQUIRE(checkInvalidChar(data.extracted_sequence));
}


TEST_CASE("ReadFile - Check All Data Loaded Medium", "[Data Size]") {

    ReadFile data;

    data.readsfiles("data/small.fasta");

    int preset_length = 151;
    int preset_size = 3214/2;

    size_t total_num_of_chars = preset_length * preset_size;

    REQUIRE(data.extracted_sequence.size() == total_num_of_chars);
}

TEST_CASE("ReadFile - Check Desired String Loaded", "[Data Size]") {
    ReadFile data;
    data.readsfiles("data/smallest.fasta");

    std::string desired= "AAAAAAAAAAACAAAAAAAAAAAAAAAAAACAAAAAAA";

    REQUIRE(checkRead(data.extracted_sequence, desired));

    ReadFile data2;
    data2.readsfiles("data/evensmaller.fasta");

    REQUIRE_FALSE(checkRead(data2.extracted_sequence, desired));
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases  De Bruijn Graph//
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("DeBruijn - kmer extraction", "[K-Mer Size]") {
    int test_kmer_size = 10;
    std::string test_file =  "data/smallest.fasta";

    DeBruijnGraph dbg;
    dbg.chopString(test_kmer_size, test_file);

    std::vector<std::string> desired = {  \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAC" , \
        "AAAAAAAACA" , \
        "AAAAAAACAA" , \
        "AAAAAACAAA" , \
        "AAAAACAAAA" , \
        "AAAACAAAAA" , \
        "AAACAAAAAA" , \
        "AACAAAAAAA" , \
        "ACAAAAAAAA" , \
        "CAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAA" , \
        "AAAAAAAAAC" , \
        "AAAAAAAACA" , \
        "AAAAAAACAA" , \
        "AAAAAACAAA" , \
        "AAAAACAAAA" , \
        "AAAACAAAAA" , \
        "AAACAAAAAA" , \
        "AACAAAAAAA" 
    }; 

    REQUIRE(desired.size() == dbg.kmers.size());

    for(size_t i = 0; i < dbg.kmers.size(); i++) {
        REQUIRE(dbg.kmers.at(i) == desired.at(i));
    }

    // REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));

    //   REQUIRE_NOTHROW(DropDiskToBoard(student, DiskType::kPlayer1, 0));
    //   REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -2), std::runtime_error);
}

TEST_CASE("DeBruijn - graph construction small", "[Graph Construction]") {

    //All possible nodes : CA, AC, AA

    //Repeats: 
    //CA -> AA : 2
    //AC -> AA : 2
    //AA -> AA : 30
    //AA -> AC : 2     


    // Node AA = { .data = "AA" };
    // Node AC = { .data = "AC" };
    // Node CA = { .data = "CA" };

    // Edge AAAA = {.incoming = AA, .outgoing = AA, .occurrences = 30};
    // Edge AAAC = {.incoming = AA, .outgoing = AC, .occurrences = 2};
    // Edge ACAA = {.incoming = AC, .outgoing = AA, .occurrences = 2};
    // Edge CAAA = {.incoming = CA, .outgoing = AA, .occurrences = 2};

    // AA.outgoingEdges.push_back(AAAA);
    // AA.outgoingEdges.push_back(AAAC);
    // AC.outgoingEdges.push_back(ACAA);
    // CA.outgoingEdges.push_back(CAAA);

    int test_kmer_size = 2;
    std::string test_file =  "data/smallest.fasta";

    DeBruijnGraph dbg;
    dbg.chopString(test_kmer_size, test_file);
    dbg.createGraph();

    std::map<std::string, size_t> Nodes;
    Nodes.insert({"AA", 2});
    Nodes.insert({"AC", 1});
    Nodes.insert({"CA", 1});

    for(auto& keyval: dbg.graph) {
        REQUIRE(keyval.second.outgoingEdges.size() == Nodes.at(keyval.first));
    }

    // REQUIRE(true == true);

}





// /////////////////////////////////////////////////////////////////////////////////////////////