# Concept decompositions for Large Sparse Text Data using Clustering
A project in data mining based on "Concept Decompositions for Large Sparse Text Data using Clustering.pdf" which can be found as part of this project. 

## Project Goals

- [x] extract words into matrix, reduce the matrix by removing function words (low-frequency words, high-frequency word with no important content and stopwords) 
- [x] create vector space model - use schemes txn or tfn to normalize document vectors
- [ ] partitioning of the document vectors into k disjoint clusters, get centroid for each cluster, normalize centroid/mean vector to get concept vector
- [ ] objective function - cluster quality
- [ ] spherical k-means algorithm


## Usage
### Word Extractor

Compile
```
g++ -std=c++11 extractor/main.cpp extractor/Porter_stemmer.c -o extract
```

Execute
```
./extract
```

### Extractor's Outputs

...can be found in extractor-output folder

output.txt contains human-readable list of all selected words, their occurances in documents and number of documents they apear in.

matlab_data.mtx contains a matlab .mtx format word-by-document matrix (+ additional column with count of row's elements greater than 0) to be read with mmread.

word-by-document_matrix.txt represents what its name implies, without any additional information.


