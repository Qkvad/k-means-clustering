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

Execution output example
```
ignore stop words? [y/n] y
use Porter stemming? [y/n] y
ignore words of length less than: 3
ignore words that occur less than [ ] times in every file: 5


Data_Mining/Data_Mining.txt word count: 133405
Data_Mining/k-means.txt word count: 144552
Data_Mining/Pattern_Classification.txt word count: 397662
Data_Mining/Information_Retrieval.txt word count: 569597
Lord_of_the_Rings/The_Fellowship_Of_The_Ring.txt word count: 602560
Lord_of_the_Rings/The_Two_Towers.txt word count: 761907
Lord_of_the_Rings/The_Return_Of_The_King.txt word count: 899636

chosen words with length >=3 and occurance >=5 in at least one file: 4932
```

#### Extractor's Outputs

...can be found in extractor-output folder

output.txt contains human-readable list of all selected words, their occurances in documents and number of documents they apear in.

matlab_data.mtx contains a matlab .mtx format word-by-document matrix (+ additional column with count of row's elements greater than 0) to be read with mmread.

word-by-document_matrix.txt represents what its name implies, without any additional information.

### Matlab
```
>> [A,n1,n2]=mainMatLab(3,100)
A =

   1   1   1   1   2   2   2   3   3

n1 =  2.5055
n2 =  2.8307
>>
```


