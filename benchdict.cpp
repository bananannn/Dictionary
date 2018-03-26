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
 * Name: Bananannn
 * Description: This file implements timers for all three different data
 * types. Then, compare and record in the FinalReport.pdf.
 */

/*
 * Function name: main
 * function prototype: main( int argc, char** argv );
 * Description: create the program to calculate the time of different
 *              trees when finding 100 unexist words.
 * Input: 
 * min_size: The minimum size of the dictionary 
 * step_size: The step size( how much to increase during each iteration)
 * num_iterations: The number of iterations( how much times of increasing)
 * dictfile: The name of the file to use
 */
int main(int argc, char** argv){
    if( argc != 5 ){
	std::cerr<< "missing certain input argument" <<std::endl;
        return 1;
    }
    // get all the input arguments
    unsigned int min_size = std::stoi(argv[1]);
    unsigned int step_size = std::stoi(argv[2]);
    unsigned int num_iterations = std::stoi(argv[3]);
    std::string dictfile = argv[4];
    Timer timer;
    // create new trees for each of the data structure
    DictionaryBST bstTree;
    DictionaryTrie trieTree;
    DictionaryHashtable hashTree;
    // use the iostream to store the words into the trees
    std::ifstream stream;
    stream.open(dictfile);
    long long averageBST = 0;
    long long averageTrie = 0;
    long long averageHash = 0;
    unsigned int repeat = 50; 
    // for the dictionary class DictionaryBST 
    std::cout<<"DictionaryBST"<<std::endl;
    for( unsigned int i=0; i<num_iterations; i++){
        stream.seekg(0, stream.beg);
        Utils::load_dict(bstTree, stream, min_size+i*step_size);
        // Read and compute the time used to read the next 100 words
        for( unsigned j = 0; j<repeat; j++ ){
            // for the BST
	    std::string line = "";
            for( int k = 0; k<100; k++){ 
                getline(stream, line);
		if(stream.eof()){
                    // If there are fewer than min_size+i*step_size words
                    // print an error message
                    std::cout<< "Error: not enough words!" << std::endl;
		    break;
		}
                // calculate the time used to find for 20*100 words 
	        timer.begin_timer();
		bstTree.find(line);
                averageBST += timer.end_timer();
	    }
	}
        averageBST = averageBST/repeat;
        std::cout<<(min_size+i*step_size)<<'\t'<<averageBST<<std::endl;
    }
    //bstTree.~DictionaryBST();
    
    // for the dictionary class DictionaryHashtable
    std::cout<<"DictionaryHashtable"<<std::endl; 
    for( unsigned int i=0; i<num_iterations; i++){
        stream.seekg(0, stream.beg);
        Utils::load_dict(hashTree, stream, min_size+i*step_size);
        // Read and compute the time used to read the next 100 words
        for( unsigned j = 0; j<repeat; j++ ){
            // for the BST
	    std::string line = "";
            for( int k = 0; k<100; k++){ 
                getline(stream, line);
		if(stream.eof()){
                    // If there are fewer than min_size+i*step_size words
                    // print an error message
                    std::cout<< "Error: not enough words!" << std::endl;
		    break;
                }
                // calculate the time used to find for 20*100 words 
	        timer.begin_timer();
		hashTree.find(line);
                averageHash += timer.end_timer();
	    }
	}
        averageHash = averageHash/repeat;
        std::cout<<(min_size+i*step_size)<<'\t'<<averageHash<<std::endl;
    }
    //hashTree.~DictionaryHashtable(); 
    
    // for the dictionary class DictionaryTrie 
    std::cout<<"DictionaryTrie"<<std::endl; 
    for( unsigned int i=0; i<num_iterations; i++){
        stream.seekg(0,stream.beg);
        Utils::load_dict(trieTree, stream, min_size+i*step_size);
        // Read and compute the time used to read the next 100 words
        for( unsigned j = 0; j<repeat; j++ ){
            // for the TST
	    std::string line = "";
            for( int k = 0; k<100; k++){ 
                getline(stream, line);
		if(stream.eof()){
                    // If there are fewer than min_size+i*step_size words
                    // print an error message
                    std::cout<< "Error: not enough words!" << std::endl;
		    break;
		}
                // calculate the time used to find for 20*100 words 
	        timer.begin_timer();
		trieTree.find(line);
                averageTrie += timer.end_timer();
	    }
	}
        averageTrie = averageTrie/repeat;
        std::cout<<(min_size+i*step_size)<<'\t'<<averageTrie<<std::endl;
    }
    //trieTree.~DictionaryTrie();
    stream.close(); 
}
        
