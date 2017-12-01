#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include "Porter_stemmer.h"
#include "txn.h"


int main() {

    /*==================================================================================================================
                                                    CONTAINERS
    ==================================================================================================================*/
    std::unordered_map<char, std::unordered_map<std::string, int*> > wordsMap;
    std::unordered_map<char, std::unordered_map<std::string, int*> >::iterator letter_iterator;
    std::unordered_map<std::string, int*>::iterator word_iterator;
    std::set<std::string> stop_words;

    /*==================================================================================================================
                                                    VARIABLES
    ==================================================================================================================*/
    std::string filename, word = "";
    int current_file=0, number_of_files, low, high, count, word_count=0, unique_words=0, l, all_words=0;
    char c;
    double** X;


    /*==================================================================================================================
                                              OPEN ALL FILES NEEDED
    ==================================================================================================================*/
    std::ofstream output_file("extractor-output/output.txt");
    if(!output_file.is_open())
    {
        std::cout << "unable to open output file." << std::endl << "Done." << std::endl;
        return 1;
    }
    std::ofstream matlab_file("extractor-output/matlab_data.mtx");
    if(!matlab_file.is_open())
    {
        std::cout << "unable to open matlab file." << std::endl << "Done." << std::endl;
        return 1;
    }
    std::ofstream wd_matrix("extractor-output/word-by-document_matrix.txt");
    if(!wd_matrix.is_open())
    {
        std::cout << "unable to open word-by-document matrix file." << std::endl << "Done." << std::endl;
        return 1;
    }
    std::ifstream stop_file("extractor-input/stop_words.txt");
    if(!stop_file.is_open())
    {
        std::cout << "unable to open stop words file." << std::endl << "Done." << std::endl;
        return 1;
    }
    // fill stop words set
    while(stop_file >> word) { stop_words.insert(word); }
    word = "";

    std::ifstream root_file("extractor-input/list_of_test_files.txt");
    if(!root_file.is_open())
    {
        std::cout << "unable to open root file." << std::endl << "Done." << std::endl;
        return 1;
    }

    // store number of files
    root_file >> number_of_files;
    // read empty line to start from the 2. line in the main algorithm
    getline(root_file, filename);


    /*==================================================================================================================
                                               EXAMINE USER PREFERENCES
    ==================================================================================================================*/
    char stopwords, stemming;
    int shortlength, lowfreq, highfreq;
    std::cout << std::endl << "ignore stop words? [y/n] ";
    std::cin >> stopwords;
    std::cout << "use Porter stemming? [y/n] ";
    std::cin >> stemming;
    std::cout << "ignore words of length less than: ";
    std::cin >> shortlength;
    std::cout << "ignore words that occur less than [ ] times in every file: ";
    std::cin >> lowfreq;
    std::cout << "ignore words that occur more than [ ] times in every file: ";
    std::cin >> highfreq;
    std::cout << std::endl;


    /*==================================================================================================================
                                                   MAIN ALGORITHM
    ==================================================================================================================*/
    while(getline(root_file, filename))
    {
        std::ifstream file("extractor-input/test_files/" + filename);
        if(!file.is_open())
        {
            std::cout << "unable to open " << filename << std::endl << "Done." << std::endl;
            return 1;
        }

        /*======================================== reading file char by char =========================================*/
        while (file.get(c)) {
            // append char to word until non alphabetic
            if(isalpha(c)) {
                c = tolower(c);
                word += c;
                continue;
            }
            if(word.empty()) continue;

            word_count++;

            // ignore stop words
            if(stopwords == 'y')
                if(stop_words.find(word) != stop_words.end()) {
                    word = "";
                    continue;
                }

            // ignore short words
            if(word.length() < shortlength) {
                word = "";
                continue;
            }

            /*======================================= stemming current word ==========================================*/
            if(stemming == 'y') {
                l = word.size();
                char* cstr = new char[l+1];
                std::copy(word.begin(), word.end(), cstr);
                cstr[l] = '\0';
                l = stem(cstr, 0, l-1);
                cstr[l+1] = '\0';
                word = cstr;
                delete[] cstr;
            }

            /*======================================= filling the hash table =========================================*/
            // try finding first letter container
            letter_iterator = wordsMap.find(word[0]);

            // if found
            if (letter_iterator != wordsMap.end()) {
                // try finding word
                word_iterator = letter_iterator->second.find(word);
                // if found
                if (word_iterator != letter_iterator->second.end()) {
                    // increment word occurance
                    word_iterator->second[current_file]++;
                } else {
                    // insert new word with 1 occurances
                    int *vs = (int*)malloc(number_of_files * sizeof(int));
                    for (int i=0; i<number_of_files; i++) vs[i] = 0;
                    vs[current_file] = 1;
                    letter_iterator->second[word] = vs;
                }

            } else {
                // create new letter container and insert word with 1 occurances
                int *vs = (int*)malloc(number_of_files * sizeof(int));
                for (int i=0; i<number_of_files; i++) vs[i] = 0;
                vs[current_file] = 1;
                std::unordered_map<std::string, int *> um;
                um[word] = vs;
                wordsMap[word[0]] = um;
            }

            word = "";
        }

        file.close();
        current_file++;

        std::cout << std::endl << filename << " word count: " << word_count;
        all_words += word_count;
    }

    root_file.close();
    std::cout << std::endl << std::endl << "TOTAL NUMBER OF WORDS: " << all_words;


    /*==================================================================================================================
                                                  CREATING OUTPUT
    ==================================================================================================================*/
    for(letter_iterator = wordsMap.begin(); letter_iterator != wordsMap.end(); letter_iterator++)
    {
        for(word_iterator = letter_iterator->second.begin(); word_iterator != letter_iterator->second.end(); word_iterator++) {
            // test if word has <xtimes occurances in every file
            low = 0;
            high = 0;
            count = 0;
            for(int j=0; j<number_of_files; j++) {
                if (word_iterator->second[j] < lowfreq)
                    low++;
                if (word_iterator->second[j] > highfreq)
                    high++;
                if(word_iterator->second[j] > 0)
                    count++;
            }
            if(low == number_of_files)
                continue;
            if(high == number_of_files)
                continue;

            // print to output file
            output_file << word_iterator->first << "  (" << count << " occurances)  ";
            for(int j=0; j<number_of_files; j++)
                output_file << word_iterator->second[j] << "  ";
            output_file << std::endl;

            unique_words++;
        }
    }

    output_file.close();
    std::cout << std::endl << std::endl << "number of chosen words: " << unique_words << std::endl << std::endl;


    X=(double**)malloc(unique_words*sizeof(double*));
    for(int i=0;i<unique_words;i++) X[i]=(double*)malloc(number_of_files*sizeof(double));
    /*==================================================================================================================
                                                CREATE MATRIX
    ==================================================================================================================*/
    int row=1;
    for(letter_iterator = wordsMap.begin(); letter_iterator != wordsMap.end(); letter_iterator++)
    {
        for(word_iterator = letter_iterator->second.begin(); word_iterator != letter_iterator->second.end(); word_iterator++) {
            // test if word has 1 occurance in every file
            low = 0;
            high = 0;
            count = 0;
            for(int j=0; j<number_of_files; j++) {
                if (word_iterator->second[j] < lowfreq)
                    low++;
                if (word_iterator->second[j] > highfreq)
                    high++;
                if(word_iterator->second[j] > 0)
                    count++;
            }
            if(low == number_of_files)
                continue;
            if(high == number_of_files)
                continue;

            // set matrix element value
            for(int j=0; j<number_of_files; j++)
		        X[row-1][j] = word_iterator->second[j];
            row++;
        }
    }


    /*==================================================================================================================
                                                   TXN NORMALIZATION
    ==================================================================================================================*/
    txn(X,unique_words,number_of_files);


    /*==================================================================================================================
                                           CREATE MATLAB WORD-by-DOCUMENT MATRIX
    ==================================================================================================================*/
    matlab_file << "%%MatrixMarket matrix coordinate real general" << std::endl;
    matlab_file << unique_words << " " << number_of_files << " " << unique_words*number_of_files << std::endl;

    for(int i=0; i<unique_words; i++) 
	    for(int j=0; j<number_of_files; j++)
                matlab_file << i+1 << " " << j+1 << " " << X[i][j] << std::endl;
    matlab_file.close();


    /*==================================================================================================================
                                             CREATE WORD-by-DOCUMENT MATRIX
    ==================================================================================================================*/
    for(int i=0; i<unique_words; i++) {
	    for(int j=0; j<number_of_files; j++)
                wd_matrix << X[i][j] << "  ";
	    wd_matrix << std::endl;
    }
    wd_matrix.close();


    for(int i=0; i<number_of_files; i++) free(X[i]);
    free(X);
    return 0;
}
