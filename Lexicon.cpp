#include "Lexicon.h"

//LexNode methods

Lexicon::LexNode::LexNode(char letter) : data_(letter), isWord_(false)
{
	children_.resize(LETTERS_IN_ALPHABET);//initialize children vector to size 
}					      //of all letters in the alphabet

//Lexicon methods
Lexicon::Lexicon()
{
}

Lexicon::Lexicon(string lexFile)
{
	lexicon_.resize(LETTERS_IN_ALPHABET);//initialize lexicon to size of
	readIn(lexFile);		     //all letters in alphabet
}

Lexicon::~Lexicon(void)
{
//	clear();	
}

Lexicon& Lexicon::operator =(const Lexicon& rhs)
{
	if(&rhs != this)
	{	
		lexicon_ = rhs.lexicon_; //sense lexicon is just node pointers, we copy the pointers
	}
	return *this;	
}

Lexicon::Status Lexicon::wordStatus(string word)
{
	const char* charWord = word.c_str();		//convert word to char string
	Lexicon::Status retval = Lexicon::NOT_WORD;	//set retval to NOT_WORD
	int index = *charWord - A_IN_ASCII;		//find index
	if((*charWord) <= 'z' && (*charWord) >= 'a')
	{
		if(word.size() == 1)			//if a single letter is played
		{
			if(lexicon_[index] != NULL)	//check  if any words begin with that letter
			{
				retval = WORD_PREFIX;	//if so, return word prefix
			}
		}
		else if(lexicon_[index] != NULL)	//if a character exists at that index
		{
			findStatus(charWord, lexicon_[index], retval);//find the status of the word
		}
	}
	return retval;			
}

void Lexicon::findStatus(const char*& letter, LexNode*& pNode, Lexicon::Status& status)
{
	++letter;				//look at next letter 
	int index = *letter - A_IN_ASCII;	//find new index
	if(pNode->children_[index] != NULL)	//if that letter exists as a child of current node
	{
		++letter;			//move to next letter
		if((*letter) == '\000')		//if that letter is a null character
		{
			--letter;		//move to previous letter
			if(!pNode->children_[(*letter) - A_IN_ASCII]->isWord_)	//if child node is not a word
			{
				status = Lexicon::WORD_PREFIX;			//then its a word prefix
			}
			else
			{	
				status = Lexicon::WORD;				//otherwise its a word
			}
		}
		else				//if it isnt a null character
		{
			--letter;		//move to previous letter
			findStatus(letter, pNode->children_[index], status);//and recurse on it, and its parent node
		}
	}
	
}

void Lexicon::readIn(string lexicon)
{
	ifstream file(lexicon.c_str());
	
	string word;

	while(getline(file, word))//while we havent read in every word
	{
		lowerCaseConvert(word);
		const char* charWord = word.c_str();//convert word to char string
		pathConstruct(charWord);	    //construct path with that word	
		word = "";
	}
}

void Lexicon::pathConstruct(const char*& letter)
{
	char newLetter = *letter;
	int index = newLetter - A_IN_ASCII;//find index
	if(lexicon_[index] == NULL)	 //if a node doesnt exist at that index
	{
		lexicon_[index] = new LexNode(newLetter); //create a new node
	}
	pathConstruct(letter, lexicon_[index]);		//then continue constructing path
}

void Lexicon::pathConstruct(const char*& letter, LexNode*& pNode)
{
	++letter;					//look at next letter
	if(*letter != '\000')				//if that letter isnt null
	{
		int index = *letter - A_IN_ASCII;	//find index
		if(pNode->children_[index] == NULL)	//if a node doesn't exist at that index
		{
			pNode->children_[index] = new LexNode(*letter);//create a new one
		}
		pathConstruct(letter, pNode->children_[index]); 	//then recurse
	}
	else						//if we were looking at the last letter
	{
		pNode->isWord_ = true;			//then we have a word!
	}
}

//Convert word status to string
string Lexicon::toWord(const Lexicon::Status& status)
{
	string retval = "NOT_WORD";
	if(status == 1)
	{
		retval = "WORD";
	}
	else if(status == 2)
	{
		retval = "WORD_PREFIX";
	}
	return retval;
}

//converts string to lowerCase
void Lexicon::lowerCaseConvert(string& word)
{
        int i = 0;
        while(word[i])//while we havent reached the end of the word
        {
                word[i] = tolower(word[i]);//convert that character to lowercase
                ++i;
        }
}

/*//driver function for clear

void Lexicon::clear()
{
	for(int i = 0; i < LETTERS_IN_ALPHABET;++i)//for every spot in the lexicon_
	{
		clear(lexicon_[i]);
		delete [] lexicon_[i];		   //then delete the node pointer
	}
}

//helper function for clear
void Lexicon::clear(LexNode*& pNode)
{
	for(int i = 0; i < LETTERS_IN_ALPHABET;++i)//for every child map
	{
		if(pNode->children_[i] != NULL)    //if a child map exists in that spot
		{
			clear(pNode->children_[i]);//recurse into its child map
			delete *(pNode->children_[i]);//then delete this one
		}
	}
}*/
