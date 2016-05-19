//Ryan Hayes
//Spring 2016
//Lexicon Class

#ifndef LEXICON_H
#define LEXICON_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;

class Lexicon
{
private:
	class LexNode{
	protected:
		friend class Lexicon;
	private:
		char data_;
		vector<LexNode*> children_;
		bool isWord_;
	public:
		LexNode(char letter);
		LexNode();
	};
public:
	enum {A_IN_ASCII = 97};
	enum {LETTERS_IN_ALPHABET = 26};
	enum Status{NOT_WORD, WORD, WORD_PREFIX};

	Lexicon();
	Lexicon(string lexFile);
	virtual ~Lexicon(void);
	
	Lexicon& operator =(const Lexicon& rhs);
	
	//driver function for word status
	Status wordStatus(string word);

	//converts statuses to strings
	static string toWord(const Status& status);

	//converts words to lowercase
	static void lowerCaseConvert(string& word);
private:
	//reads in a file for the lexicon
	void readIn(string lexicon);
	
	//used to construct words
	void pathConstruct(const char*& word);

	//helper function to construct words
	void pathConstruct(const char*& word, LexNode*& pNode);

	//helper function to determine word statuses
	void findStatus(const char*& letter, LexNode*& pNode, Status& status);

	//used by destructor to clear lexicon
//	void clear();
// 	void clear(LexNode*& pNode);	
private:
	vector<LexNode*> lexicon_;
};

#endif
