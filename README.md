# Concept decompositions for Large Sparse Text Data using Clustering
A project in data mining. More info soon...

## Project Goals

- [x] extract words into matrix, reduce the matrix by removing function words (low-frequency words, high-frequency word with no important content and stopwords) 
- [x] create vector space model - use schemes txn or tfn to normalize document vectors
- [ ] partitioning of the document vectors into k disjoint clusters, get centroid for each cluster, normalize centroid/mean vector to get concept vector
- [ ] objective function - cluster quality
- [ ] spherical k-means algorithm


### How to use word-extractor

Navigate to word-extractor directory
```
cd word-extractor
```

Compile code
```
g++ -std=c++11 main.cpp -o m
```

Execute
```
./m
```

### Outputs

output.txt contains human-readable list of all selected words, their occurances in documents and number of documents they apear in.

matlab_data.mtx contains a matlab .mtx format word-by-document matrix to be read with mmread.


