/*
 * Name: Bananannn
 * Description: This file implements a program to print the collisions 
 *              inside hash tables using two different hash functions.
 *              Then, compare and record in the FinalReport.pdf.
 */
#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include<fstream>
#include<string>

/*
 * Function name: main
 * function prototype: main( int argc, char** argv );
 * Description: create the program to compare two hush functions.
 * Input: 
 * min_size: The size of the dictionary 
 * dictfile: The name of the file to use
 */
int main(int argc, char** argv){
    if( argc != 3 ){
	std::cerr<< "missing certain input argument" <<std::endl;
        return 1;
    }
    std::string dictfile = argv[1];
    unsigned int num_words = atoi(argv[2]);
    unsigned int tablesize = 2*num_words;
    // First, for the 1st hash function:
    // open a certain dictionary
    std::ifstream hashstream;
    hashstream.open(dictfile);
    std::string line = "";
    std::vector<unsigned int> myVec;
    // Second, for the 2nd hash function:
    // open a certain dictionary
    std::ifstream hashstr;
    hashstr.open(dictfile);
    std::string line2 = "";
    std::vector<unsigned int> myVec2;
    
    for( unsigned int i = 0; i<tablesize; i++ ){
        myVec.push_back(0);
        myVec2.push_back(0);
    }
    for( unsigned int i = 0; i<num_words; i++ ){
        getline(hashstream, line);
        getline(hashstr, line2);
        if( hashstream.eof() || hashstr.eof() )
            break;
        /* 1st hash function (The upper one in thw website)
         * Website:http://research.cs.vt.edu/AVresearch/hashing/strings.php
         * Author: Virginia Tech Algorithm Visualization Research
         * Input: string and the tablesize
         * Output: unsigned int between 0 and table size.
         * Description: The function sums the ASCII values of the letters in
         * 		    a string. 
         */
        int sum = 0;
        int hash = 0;
        for(unsigned int i = 0; i<line.length(); i++){
            sum += line.at(i);
            hash = sum%tablesize;
        }
        myVec[hash] += 1;
        
        /*
         * 2nd hash function 
         * Website: https://stackoverflow.com/questions/2624192/good-hash-
         *          function-for-strings
         * Author: jonathanasdf
         * Input: string and the size of the table
         * ouput: the key which is between 0 and the table size
         * Description: hashs take values and multiply it by a prime number
         *              (the result might be more unique)
         */
        hash = 13;
        for(unsigned int i = 0; i<line2.length(); i++){
            hash = hash*23 + line2.at(i);
	    hash = hash%tablesize;
	}
	myVec2[hash] += 1; 
    }
    // Print the stats
    unsigned int max = 0;
    unsigned int max2 = 0;
    for( unsigned int i = 0; i<tablesize; i++ ){
        if( myVec[i] >= max ){
	    max  = myVec[i];
	}
        if( myVec2[i] >= max2 ){
            max2 = myVec2[i];
        }
    }
    // Create empty vectors to sort all the values in the previous vector
    std::vector<unsigned int> sorted;
    std::vector<unsigned int> sorted2;
    for( unsigned int i = 0; i<=max; i++ ){
        sorted.push_back(0);
        sorted2.push_back(0);
    }
    // Calculate the number of different number of hits
    for( unsigned int i = 0; i<tablesize; i++ ){
        sorted[myVec[i]] += 1;
        sorted2[myVec2[i]] += 1;
    }
    // print the data related to the first hash function
    std::cout<<"Printing the statistics for hashFunction1 with hash table size"
    << " " << tablesize << std::endl;
    std::cout<<"#hits   "<< "#slots receiving the #hits" << std::endl;
    for( unsigned int i=0; i<max+1; i++){
        if( sorted[i] != 0 ){
            std::cout<<i<< "        " << sorted[i] << std::endl;
        }
    }
    double average = 0;
    for( unsigned int i = 1; i<=max; i++){
        average += i*sorted[i]*(1+i)/2;
    }
    // print the average value
    average = average/(double)num_words;
    std::cout<<"The average number of steps for a successful search for hash"
    <<" 1 would be  "<< average << std::endl;
    // print the max
    std::cout<<"The worst case steps that would be needed to find a word is "
    << max << std::endl;

    // print the data related to the second hash function
    std::cout<<"Printing the statistics for hashFunction2 with hash table size"
    << " " << tablesize << std::endl;
    std::cout<<"#hits   "<< "#slots receiving the #hits" << std::endl;
    for( unsigned int i=0; i<max2+1; i++){
        if(sorted2[i] != 0 ){
            std::cout<<i<< "        " << sorted2[i] << std::endl;
        }
    }
    double aver = 0;
    for( unsigned int i = 1; i<=max2; i++){
        aver += i*sorted2[i]*(1+i)/2;
    }
    // print the average value
    aver = aver/(double)num_words;
    std::cout<<"The average number of steps for a successful search for hash"
    <<" 2 would be  "<< aver << std::endl;
    // print the max
    std::cout<<"The worst case steps that would be needed to find a word is "
    << max2 << std::endl;
}
