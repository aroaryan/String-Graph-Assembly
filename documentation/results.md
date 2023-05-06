
# Output of the algorithms

DeBruijn Graph Construction: We first read the file from the dataset and create a vector of substrings. 

Each node in this graph represents a kmer and the edge represents a overlap between the next kmer 



The Needleman-Wunsch algorithm is a algorithm used to align two sequences of nucleotides or amino acids. Its mostly used in bioinformatics to figure out optimal alignment of sequences. To do this optimally, it uses Dynamic Programming.

The algorithm works by creating a dynamic programming matrix that represents all possible alignments of the two sequences. Every cell represents the best alignment of those subindices within the string relative to the other. It takes a gap penalty and a match reward to calculate distance.

The algorithm starts by initializing the first row and column of the matrix with gap penalties. It then iteratively fills in the matrix by considering the three possible ways to extend a sequence alignment: by inserting a gap in one of the sequences, by inserting a gap in the other sequence, or by matching a pair of nucleotides or amino acids. The algorithm chooses the best option at each step based on a scoring system that takes into account the similarity of the aligned residues and the penalties for opening and extending gaps.

Once the matrix is filled, the optimal alignment can be determined by tracing back through the matrix from the bottom-right corner to the top-left corner. This generates a traceback path that represents the optimal alignment of the two sequences. Because of dynamic programming, we're able to return the `m`th at `n`th index of the dynamic programming matrix.


# Were we able to answer our leading question?

We were unable to completelty run our data 
