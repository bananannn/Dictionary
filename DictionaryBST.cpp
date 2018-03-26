#include "util.h"
#include "DictionaryBST.h"
/* 
 * Name: Bananannn
 * Description: This file implements a BST tree.
 */

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
    setOfWords = new std::set<std::string>();
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
    // if the word cannot be inserted successfully, 
    // return false (the second element in the return value
    // or we return true
    auto returnValue = setOfWords->insert(word);
    return returnValue.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
    auto returnValue = setOfWords->find(word);
    // return false if the find method cannot find the code
    if( returnValue == setOfWords->end() ){
        return false;
    }
    // return true if it can be found
    else{
        return true;
    }
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
    // delete the all the pointers we set in the class
    delete(setOfWords);
}
