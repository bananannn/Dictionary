#include "util.h"
#include "DictionaryTrie.h"
#include <queue>
#include <string>
#include <bits/stdc++.h>
/* 
 * Name: Bananannn
 * Description: This file implements a TST tree.
 */
using namespace std;
class priority_queue;
/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
    root = nullptr;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
    // find the length of the word and iterate every char
    int length = word.length();
    TSTNode* curr = root;
    unsigned int letterFreq = 0;
    if( word.length() <= 0 ){
        return false;
    }
    if( root == nullptr ){
        root = new TSTNode(word.at(0), 0);
	curr = root;
    }
    for( int i=0; i<length; i++){
        const char& letter = word.at(i);
        // update the current node with the letter
        // if the current node is null
        if( curr == nullptr ){ 
            if( i != (length-1) ){
                curr = new TSTNode(letter, letterFreq);
            }
            else{
                curr = new TSTNode(letter, freq);
                curr->isEnd = true;
                curr->isWord.append(word);
	        return true;
            }
        }
        // if the current node has an element
        else{
            // if the letter is smaller than the current node
            // update the left child of the curr node
            // or set left child to be the curr node
            if( word.at(i) < curr->Data ){
                if( curr->left == nullptr ){
                    curr->left = new TSTNode( letter,letterFreq );
                    curr->left->parent = curr;
		    curr = curr->left;
                    // If the character is the last one
                    // update its frequency and isEnd and isWord
                    if( i == (length-1) ){
			curr->frequency = freq;
			curr->isEnd = true;
                        curr->isWord.append(word);
			return true;
                    }
		    --i;
                }
		else{
                    // if the character exists
                    curr = curr->left;
                    if( curr->Data == word.at(i) ){
                        if( i == (length-1) ){
                            // if the word already exists
                            if( curr->isEnd == true ){
	                        if( curr->frequency < freq ){
			            curr->frequency = freq;
                                    curr->isWord.append(word);
	  	                }
			        return false;
			    }
			    // if it is a new word
			    else{
                                curr->isEnd = true;
                                curr->isWord.append(word);
                                curr->frequency = freq;
			        return true;
			    }
                        }
			
                    }
                    --i;
                }
            }
            // similarly,
            // update the right child or set curr node to be the right
            // child
            else if( word.at(i) > curr->Data ){
                if( curr->right == nullptr ){
                    curr->right = new TSTNode( letter, letterFreq );
		    curr->right->parent = curr;
                    curr = curr->right;
		    // if the character is the last character of a word
                    if( i == (length-1) ){
                        curr->isEnd = true;
                        curr->isWord.append(word);
                        curr->frequency = freq;
			return true;
                    }
		    --i;
	        }
                else{
                    curr = curr->right;
		    if( curr->Data == word.at(i) ){
    			// if the character is the last character of a word
                        if( i == (length-1) ){
                            if( curr->isEnd == true ){
   				// update the frequency and the isWord
	                        if( curr->frequency < freq ){
			            curr->frequency = freq;
                                    curr->isWord.append(word);
	  	                }
			        return false;
			    }
			    else{
				// update all the related data
				// if the character is the end of a word
                                curr->isEnd = true;
                                curr->isWord.append(word);
                                curr->frequency = freq;
			        return true;
			    }
		        }
			
                    }
		    --i;
                }
            }
            // If the current node is the same as the letter here
            else{
	        // std::cout<< word << word.at(i) << std::endl;
                if( i == (length-1) ){
                    if( curr != nullptr ){
			if( curr->isEnd == true ){
			    // if the curr is the end of a word,
			    // update the frequency by using the larger one
	                    if( curr->frequency < freq ){
			        curr->frequency = freq;
                                    curr->isWord.append(word); 
	  		    }
			    return false;
			}
			else{
			    // update all the related data
			    // if the character is the end of a word
			    curr->isEnd = true;
                            curr->isWord.append(word);
			    curr->frequency = freq; 
	                    return true;
			}
		    }
		    // update the curr->middle by the new node
                    else{
                        curr->middle = new TSTNode( letter, freq );
			curr->middle->parent = curr;
			curr->middle->isEnd = true;
                        curr->isWord.append(word);
			curr = curr->middle;
                        return true;
                    }
                }
                // update the middle node if the word has remaining letters
 		else{
                    if( curr->middle == nullptr ){
                        // if the node has no middle child, update all
                        // the remaining characters in the word at the middle
                        curr->middle = new TSTNode( word.at(i+1),letterFreq );
			curr->middle->parent = curr;
		        curr = curr->middle;
                    }
                    else{
                        curr = curr->middle;
                    }
            
                }
            }
        }
    }
    // if the for loop does not return the true boolean, it means the insert
    // fails or it is the new word inserted. So we return false at the end
    return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{   
    int length = word.length();
    // if the tree or the word is not valid, return false
    TSTNode* curr = root;
    if( root == nullptr){
	return false;
    }
    if( word.length() <= 0){
 	return false;
    }
    for( int i = 0; i<length; i++ ){
        char currChar = word.at(i);
        // if the current node is not null
        if( curr == nullptr ){
            return false;
        }
        while( curr->Data != currChar ){
	    // if the current data is smaller, search the right branch
            if( curr->Data < currChar ){
                curr = curr->right;
            }
            // if the current data is larger, search the left branch
            else if( curr->Data > currChar ){
                curr = curr->left;
            }
            if( curr == nullptr ){
               return false;
	    }
        }
            // search the middle branch
        if( curr != nullptr && i != length-1 ){
            curr = curr->middle;
        }
    } 
    // if we iterate every node successful without visiting null node,
    // we should be able to find the word
    // if the word end with the character, we return true
    if( curr != nullptr && curr->isEnd == true ){
        return true;
    }
    // otherwise, return false
    else{
        return false;
    }
}

/*
 * Constructor 
 * It initializes each node in the trie
 * The node with given data has no childern.
 */
TSTNode::TSTNode(const char & data, unsigned int freq) : 
left(0), right(0), middle(0), frequency(freq), isEnd(false), isVisited(false), 
isCount(true), isWord(""), Data(data) {}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix,
 unsigned int num_completions)
{
    std::vector<std::string> words;
    // return an empty vector if the prefix is not valid
    if( prefix.length() == 0 || root == nullptr ){
        std::cout<<"Invalid Input. Please retry with correct input"<<std::endl;
        return words;
    }
    if( num_completions <= 0 ){
        std::cout<<"Invalid Input. Please retry with correct input"<<std::endl;
        return words;
    }
     if(prefix == " " || prefix == "  "){
        std::cout<<"Invalid Input. Please retry with correct input"
        <<std::endl;
        return words;
    }
        
    // find the given prefix
    // by applying similar code to the previous find function
    int length = prefix.length();
    TSTNode* curr = root;
    for( int i = 0; i<length; i++ ){
        const char& currChar = prefix.at(i);
        // if the current node is null
        if( curr == nullptr ){
            std::cout<<"Invalid Input. Please retry with correct input"
            <<std::endl;
            return words;
        }
        while( curr->Data != currChar ){
            //std::cout<<"print curr"<< curr->Data<<std::endl;
	    // if the current data is smaller, search the right branch
            if( curr->Data < currChar ){
                curr = curr->right;
            }
            // if the current data is larger, search the left branch
            else if( curr->Data > currChar ){
                curr = curr->left;
            }
            // if it cannot find the word, return the empty string
	    if( curr == nullptr ){
                std::cout<<"Invalid Input. Please retry with correct input"
		<<std::endl;
                return words;
	    }
        }
        // search the middle branch
        // If i == length-1, the curr is the last character of the prefix
        if( curr!= nullptr && i != length-1 ){ 
            curr = curr->middle;
        }
    }
    // search through the subtree rooted at the end of the prefix to find
    // the num_completion most likely completions of the prefix.
    //queue<TSTNode*> myQueue;
    std::queue<TSTNode*> myQueue;
    std::priority_queue<TSTNode*, std::vector<TSTNode*>, compare> priQueue;
    myQueue.push(curr);
    curr->isVisited = true;
    // put each word into queue and then pop it
    while( myQueue.empty() == false ){
        TSTNode* popEle = myQueue.front();
        myQueue.pop();
        // if the character is the terminated character
        // push it into the priority queue
        if( popEle->isEnd == true ){
            priQueue.push(popEle);
        }
        // check each of the child of the element popped
        if( popEle->left != nullptr && popEle->left->isVisited == false ){
            myQueue.push(popEle->left);
        }
        if( popEle->middle!=nullptr && popEle->middle->isVisited == false ){
            myQueue.push(popEle->middle);
        }
        if( popEle->right!=nullptr && popEle->right->isVisited == false ){
            myQueue.push(popEle->right);
        }
    }
    // Find the top num_completions many words that are the most frequent.
    for(unsigned int i=0; i<num_completions; i++){ 
        if(priQueue.empty() == true ){
            return words;
        }
        // for each of the word in the priority queue
        TSTNode* popPri = priQueue.top();
	priQueue.pop();
        words.push_back(popPri->isWord);
	/* std::string word;  // Old version: trace back to the curr(last word 
        in ptrfix)
        while( popPri != curr ){   // popPri->parent != curr ){	
            if(popPri->parent->left==popPri||popPri->parent->right==popPri ){
                popPri->parent->isCount = false;
            }
	    if( popPri->isCount == true ){
		word += popPri->Data;
	    }
	    popPri->isCount = true;
            popPri = popPri->parent;
        }
        // reverse the word after the prefix
        reverse(word.begin(), word.end());
        // add the prefix at the front and store the word
        std::string finalWord = prefix + word;
        words.push_back(finalWord); */ 
    }
    // return the words vector
    return words;
}              

/*
 *  return true if n1 is before n2
 */
bool compare::operator() (TSTNode* n1, TSTNode* n2){
    return n1->frequency < n2->frequency;
}
        
/* Destructor */
DictionaryTrie::~DictionaryTrie(){
    deleteAll(root);
}
/*
 * Do a post traversal, delete all nodes
 */
void DictionaryTrie::deleteAll(TSTNode* n){
    if( n == nullptr ){
        return;
    }
    deleteAll(n->left);
    deleteAll(n->middle);
    deleteAll(n->right);
    
    // delete the last element
    delete(n);
}

