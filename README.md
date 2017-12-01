# Concept decompositions for Large Sparse Text Data using Clustering
A project in data mining based on "Concept Decompositions for Large Sparse Text Data using Clustering.pdf" which can be found as part of this project. 

## Project Goals

- [x] extract words into matrix, reduce the matrix by removing function words (low-frequency words, high-frequency word with no important content and stopwords) 
- [x] create vector space model - use schemes txn or tfn to normalize document vectors
- [x] partitioning of the document vectors into k disjoint clusters, get centroid for each cluster, normalize centroid/mean vector to get concept vector
- [x] objective function - cluster quality
- [x] spherical k-means algorithm


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

Execution output example
```
ignore stop words? [y/n] y
use Porter stemming? [y/n] y
ignore words of length less than: 3
ignore words that occur less than [ ] times in every file: 6


Data_Mining/Data_Mining.txt word count: 133405
Data_Mining/k-means.txt word count: 144552
Data_Mining/Pattern_Classification.txt word count: 397662
Data_Mining/Information_Retrieval.txt word count: 569597
Data_Mining/concepts_and_techniques.txt word count: 854364
Data_Mining/ML_tools.txt word count: 1048115
Lord_of_the_Rings/The_Hobbit.txt word count: 1146234
Lord_of_the_Rings/The_Fellowship_Of_The_Ring.txt word count: 1179197
Lord_of_the_Rings/The_Two_Towers.txt word count: 1338544
Lord_of_the_Rings/The_Return_Of_The_King.txt word count: 1476273
Analysis/conjugate-gradient.txt word count: 1478721
Analysis/pde.txt word count: 1512942
Computer_Science/Computer_Organization_and_Design.txt word count: 1901310
Computer_Science/Software_Engineering.txt word count: 2195939

TOTAL NUMBER OF WORDS: 15376855

number of chosen words: 6743
```

#### Extractor's Outputs

...can be found in extractor-output folder

output.txt contains human-readable list of all selected words, their occurances in documents and number of documents they apear in.

matlab_data.mtx contains a matlab .mtx format word-by-document matrix to be read with mmread.

word-by-document_matrix.txt represents what its name implies, without any additional information.

### Matlab
```
>> [A,n1,n2]=mainMatLab(2,50)
A =

   1
   1
   1
   1
   1
   1
   2
   2
   2
   2
   2
   2
   1
   1

n1 =  3.6677
n2 =  3.7010
```


