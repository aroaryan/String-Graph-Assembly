# String-Graph-Assembly
CS 225 Extreme Extra Credit Projects

## Project Summary

Our project attempts to reproduce the genome of the [S. Aureus](https://www.health.state.mn.us/diseases/staph/basics.html) bacteria. Sourcing the data from [National Library of Medcine's Sequence Read Archive](https://trace.ncbi.nlm.nih.gov/Traces/?view=run_browser&acc=SRR23718782&display=metadata). The data is proccesed and the De Bruijn Graph is constructed, all single weighted edges are removed and the graph is traversed. The FM-Index is constructed for the k-mers traversed through in the De Bruijn Graph. Now the  most repeating patterns are highlighted and extracted using the backward search algorithm. Finally, the generated string is compared to the output genome using the global alignment Needleman-Wunsch algorithm.

## Code

All code files can be found in the `code/` directory. To run the code:

1. Compile using `make exec`
2. Run using `./bin/exec`
3. Enter the data set to be used eg. `data/small.fasta`
4. Enter the length of k-mers to be used eg. `7`


There are a few test cases written to check the construction of the DeBruijnGraph and ReadFile method. `make tests` followed by `./bin/tests` can be used to test it. 

## Data

Our data is originally sourced from the [SRA Archive](https://trace.ncbi.nlm.nih.gov/Traces/?view=run_browser&acc=SRR23718782&display=metadata) available for download [here.](https://drive.google.com/file/d/1bQzdZBxWnnvsWqbHEWomO4qhNrn9c9wh/view?usp=sharing)

The data files on this repo are subsets of the original file.

1. `data/small.fasta`
2. `data/evensmaller.fasta`
3. `data/smallest.fasta` is **not** a subset of the original file and was updated throughout the project to test the functionality of the code.

## Output

The graph and the other data generated is also outputted to the `data/` directory. 
On running the program `data/outputgraph.txt` is generated. 

## Documents

Our signed contract and development log can be found in the `documents/` directory.

## Feedback

All feedback from our project mentor can be found in the `feedback/` directory.