#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>
#include <cctype>
using namespace std;

class Trie
{
private:
	TrieNode* _root = nullptr;

protected:

public:
	Trie()
	{
		_root = new TrieNode{};
	}

	virtual ~Trie()
	{
		//TODO: clean up memory
	}

	//TODO: implement
	void addWord(const string& word)
	{
		TrieNode* node = _root;

		for (auto c : word)
		{
			if (node->hasChild(c) == 0)
			{
				node->setChild(c, new TrieNode());
			}
			node = node->getChild(c);
		}

		node->setChild('$', new TrieNode);
	}


	//TODO: implement

	vector<string> search(const string& word)
	{
		vector<string> wordsFound;

		TrieNode* node = _root;
		
		string tempWord = word;


		//iterate through the given word/prefix to search for
		//and find the node corresponding to the end
		//of the word/prefix.
		for (auto c : word)
		{	
			//if the current character has a child node to go to,
			//the node pointer is set to be that child node
			//and the next character in the prefix goes through the 
			//same test to go to a corresponding child.
			if (node->hasChild(c))
			{
				node = node->getChild(c);			
			}

			// if one of the characters in the prefix doesn't have
			//any child node to go to, the search stops and an
			//empty vector is returned.
			else
			{
				return wordsFound;
			}
		}	

		//if the end-node of the prefix has a sentinel child,
		//then the prefix is a complete word. The prefix in 
		//tempWord is then added to the vector of wordsFound.
		if (node->hasChild('$'));
		{
			wordsFound.push_back(tempWord);
		}
		

		//once the end-node for the prefix is the current node,
		//this function traverses all child nodes under the current
		//prefix end-node. 
		for (auto child : node->getChildren())
		{
			//if the current node has a sentinel character 
			//as a child, the current node is the last character
			//of a word. This means that tempWord is a complete word, so 			
			//tempWord is then added to the vector of words found.
			if (child.first == '$')
			{
				wordsFound.push_back(tempWord);
			}

			//if the current node does not have a sentinel
			//character as a child, the current node is not
			//the last character of a word. This starts a recursive 
			//function which will, in a similar fashion to what 
			//has been described above, concatenate all child-node
			//characters until a sentinel-character child is reached. 
			//Once a sentinel-character child is reached, the word
			//is complete and it is added to the wordsFound vector.
			else
			{
				searchHelper(word + child.first, wordsFound);
			}
		}

		return wordsFound;
	}

	void searchHelper(const string& word, vector<string>& wordsFound)
	{

		TrieNode* node = _root;

		string tempWord = word;

		for (auto c : word)
		{
			if (node->hasChild(c))
			{
				node = node->getChild(c);
			}
		}	

		for (auto child : node->getChildren())
		{
			if (child.first == '$')
			{
				wordsFound.push_back(tempWord);
			}

			else
			{
				searchHelper(word + child.first, wordsFound);
			}
		}
	}
};

#endif // !TRIE_H
