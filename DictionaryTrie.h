/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

/* 
 * Name: Bananannn
 * Description: This file implements a TST tree.
 */
#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include <queue>

class TSTNode;
class queue;
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  // create a pointer to the root of the ternary search tree
  TSTNode* root;

  /*
   * Do a post traversal, delete nodes
   */
  static void deleteAll( TSTNode* n );
  // overload the priority_queue's operator
};
// Add your own data members and methods here
// it is a class to construct the node of a ternary Search tree
class TSTNode{
  
  public:
    
    TSTNode* left;
    TSTNode* right;
    TSTNode* middle;
    TSTNode* parent;
    unsigned int frequency;
    bool isEnd;
    bool isVisited;
    bool isCount;
    std::string isWord;
    char const Data; // the data stored in the node is const

    /*
     * constructor
     * It initializes each node in the trie
     * The node with given data has no childern.
     */
    TSTNode(const char &data, unsigned int freq);

};

class compare{ 
public:
    bool operator() (TSTNode* n1, TSTNode* n2);
};
#endif // DICTIONARY_TRIE_H
