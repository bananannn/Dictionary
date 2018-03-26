#include "util.h"
#include "DictionaryHashtable.h"
/* Name: Bananannn
 * Description: This file implements a hash table.
 */

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){
    // create a new unordered set
    unorderedSet = new std::unordered_set<std::string>();
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
    // get the return value from the insert 
    auto returnValue = unorderedSet->insert(word);
    // the second return value will indicate whether the word has been
    // inserted
    return returnValue.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
    // check whether the word can be found
    auto returnValue = unorderedSet->find(word);
    if( returnValue == unorderedSet->end() ){
        return false;
    }
    // if the word can be found then return true
    else{
        return true;
    }
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
    delete(unorderedSet);
}
