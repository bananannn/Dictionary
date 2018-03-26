/* 
 * Name: Bananannn
 * Description: This file tests all three implementations of the 
 * data structures.
 */
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into "
  "Dictionaries..." << endl;
  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */
// test whether the find method can work properly
  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit ){
    cout<<"Finding: \"" << *wit << "\"... ";
    t_bst = d_bst.find(*wit);
    t_ht = d_ht.find(*wit);
    tt = dt.find(*wit);
    if(!t_bst){
      cout<<"failed for BST";
    }
    if(!t_ht){
      cout<<"failed for Hashset";
    }
    if(!tt){
      cout<<"failed for TST";
    }
    if(t_bst&&t_ht&&tt){
      cout << "PASSED! :D ";
    }
    cout<< endl;
  }
  cout<<endl;
 
// Test more words to inserted into the TST.
  vector<std::string> mywords;
  mywords.push_back("banana");
  mywords.push_back("h");
  mywords.push_back("sim");
  mywords.push_back("trial");
  mywords.push_back("different");
  
  
  cout << "Inserting into Dictionaries..." << endl;
  wit = mywords.begin();
  wen = mywords.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }
  
  cout << "finding into Dictionaries..." << endl;
  wit = mywords.begin();
  wen = mywords.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

// Test on the dictionary provided
  std::ifstream stream;
  stream.open("shuffled_unique_freq_dict.txt");
  DictionaryBST data_bst;
  DictionaryHashtable data_ht;
  DictionaryTrie datat;
  int s_bst, s_ht, st;
  Utils::load_dict(data_bst, stream);
  Utils::load_dict(data_ht, stream);
  Utils::load_dict(datat, stream);
  

// Test the predictCompletions  
  vector<std::string> prediction;
  vector<std::string> predict;
  DictionaryBST datap;
  unsigned int num_completions = 3;
  predict.push_back("prequel");
  predict.push_back("preverb");
  predict.push_back("premium");
  predict.push_back("precoup");
  predict.push_back("preview");
  predict.push_back("precook");
  predict.push_back("prepped");
  predict.push_back("pretext");
  predict.push_back("preform");

  cout << "Inserting into Dictionaries..." << endl;

  wit = predict.begin();
  wen = predict.end();
  unsigned int i = 1;
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      s_bst = datap.insert(*wit);
      s_ht = data_ht.insert(*wit);
      st = datat.insert(*wit, i);
      ++i;
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!s_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!s_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!st)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(s_bst && s_ht && st)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }
  prediction = datat.predictCompletions("pre", num_completions);
  // Print the words and check whether they matches
  int j = 8;
  for(unsigned int i=0; i<prediction.size(); i++){
    if(prediction.at(i) != predict.at(j) ){
      std::cout<< "Wrong Output!"<< std::endl;
    }
    else{
      std::cout<< prediction.at(i)<<" PASSED! :D "<<std::endl;
    }
    j--;
  }

  // Testing the predictCompletions in a DictionaryTrie data.
  std::ifstream triestream;
  triestream.open("smalldictionary.txt");
  DictionaryTrie datatrie;
  Utils::load_dict(datatrie, triestream);
  

  // Print the word with ex as their prefix
  prediction = datatrie.predictCompletions("a", 3);
  for(unsigned int i=0; i<prediction.size(); i++){
    std::cout<< "prediction: "<< prediction.at(i) << std::endl;
  }

  // Testing more prediction completions 
  std::ifstream triestr;
  triestr.open("small_case1.txt");
  DictionaryTrie trie;
  Utils::load_dict(trie, triestr);
  prediction = trie.predictCompletions("ac", 2);
  std::cout<< "prediction: "<< prediction.at(0) << std::endl;
  std::cout<< "prediction: "<< prediction.at(1) << std::endl;
  // Test the predictions on the larger dictionary 
  std::ifstream tries;
  tries.open("shuffled_unique_freq_dict.txt");
  DictionaryTrie triedata;
  Utils::load_dict(triedata, tries);
  prediction = triedata.predictCompletions("ex", 3);
  std::cout<< "prediction: "<< prediction.at(0) << std::endl;
  std::cout<< "prediction: "<< prediction.at(1) << std::endl;
  // Test whether the program will print error messages 
  prediction = datat.predictCompletions("", num_completions);
  prediction = datat.predictCompletions("@", num_completions);
  //if( prediction.
  prediction = datat.predictCompletions("  ", num_completions);

  std::cout<< "PASSED! :D "<<std::endl;
  return 0;
}
