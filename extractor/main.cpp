#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include "Porter_stemmer.h"


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
    int current_file=0, number_of_files, check, count, word_count=0, unique_words=0, l;
    char c, *cstr;

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
            if(stop_words.find(word) != stop_words.end()) {
                word = "";
                continue;
            }
            // ignore short words
            if(word.length() < 3) {
                word = "";
                continue;
            }

            /*======================================= stemming current word ==========================================*/
            l=word.length();
            cstr = (char*)malloc(l*sizeof(char));
            strcpy(cstr, word.c_str());
            l = stem(cstr, 0, l-1);
            cstr[l+1] = '\0';
            word = cstr;

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
    }

    /*==================================================================================================================
                                               CREATING OUTPUT & MATRIX
    ==================================================================================================================*/
    for(letter_iterator = wordsMap.begin(); letter_iterator != wordsMap.end(); letter_iterator++)
    {
        for(word_iterator = letter_iterator->second.begin(); word_iterator != letter_iterator->second.end(); word_iterator++) {
            // test if word has 1 occurance in every file
            check = 0;
            count = 0;
            for(int j=0; j<number_of_files; j++) {
                if (word_iterator->second[j] < 5)
                    check++;
                if(word_iterator->second[j] > 0)
                    count++;
            }
            if(check == number_of_files)
                continue;

            // print to output file
            output_file << word_iterator->first << "  ";
            for(int j=0; j<number_of_files; j++) {
                output_file << word_iterator->second[j] << "  ";
                // print to wd_matrix file
                wd_matrix << word_iterator->second[j] << " ";
            }
            output_file << " -> " << count;
            output_file << std::endl;
            wd_matrix << std::endl;

            unique_words++;
        }
    }

    output_file.close();

    std::cout << std::endl << std::endl << "chosen words with length >=3 and occurance >=5 in at least one file: " << unique_words << std::endl;

    /*==================================================================================================================
                                                CREATE MATLAB MATRIX
    ==================================================================================================================*/
    matlab_file << "%%MatrixMarket matrix coordinate real general" << std::endl;
    matlab_file << unique_words << " " << number_of_files+1 << " " << unique_words*(number_of_files+1) << std::endl;

    int row=1;
    for(letter_iterator = wordsMap.begin(); letter_iterator != wordsMap.end(); letter_iterator++)
    {
        for(word_iterator = letter_iterator->second.begin(); word_iterator != letter_iterator->second.end(); word_iterator++) {
            // test if word has 1 occurance in every file
            check = 0;
            count = 0;
            for(int j=0; j<number_of_files; j++) {
                if (word_iterator->second[j] < 5)
                    check++;
                if(word_iterator->second[j] > 0)
                    count++;
            }
            if(check == number_of_files)
                continue;

            // print to matlab file
            for(int j=0; j<number_of_files; j++)
                matlab_file << row << " " << (j+1) << " " << word_iterator->second[j] << std::endl;
            matlab_file << row << " " << (number_of_files+1) << " " << count << std::endl;
            row++;
        }
    }

    return 0;
}