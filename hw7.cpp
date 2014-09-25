/**********************************************************************

PROGRAMMER :  Chad Parnin
DATE       :  April 1, 2014
COMPILER   :  Visual C++ .NET
SOURCE FILE:  hw7.cpp

ACTION:     Read words from stdin (or file redirection and displays
			them in 3 columns.
			Uses String2.cpp, with overloading, to handle words.

NOTES :     The program does not handle correctly words longer than
			MAX_WORD_LENGTH. If such words are encountered, they
			are truncated.

			Only as many as MAX_WORD_COUNT words can be stored in
			Word[]- the array holding the words.

=====================================================================*/

#include <iostream>
#include <string.h>
#include "String2.cpp"  // String2 class
#include <iomanip>
#include <ctype.h>
using namespace std;

const int MAX_WORD_LENGTH = 254;

void WriteWords(String  Word[],
	int     Count[],
	int     TotalWordCount,
	int     DistinctWordCount);

void StoreWord(String  NewWord,
	String  Word[],
	int     Count[],
	int    &TotalWordCount,
	int    &DistinctWordCount,
	int     MaxWordCount);

/***************************  main  ***********************************/

int main(int argc, char * argv[])
{
	const int MAX_WORD_COUNT = 130;

	String NewWord,  // String class instance
		Word[MAX_WORD_COUNT + 1];  // array of Strings to hold each word

	int Count[MAX_WORD_COUNT + 1] = { 0 }, // Initialize array to zeros
		DistinctWordCount = 0,
		TotalWordCount = 0;

	cin >> NewWord;  // overloaded extraction

	while (NewWord.Length() != 0)  //  While NewWord is not null string (overloaded)
	{
		StoreWord(NewWord, Word, Count, TotalWordCount,
		DistinctWordCount, MAX_WORD_COUNT);

		cin >> NewWord;
	}

	WriteWords(Word, Count, TotalWordCount, DistinctWordCount);
    
    return 0;
}

/***************************  StoreWord   ********************************

DESCRIPTION:	Adds a String NewWord (of Chr[]) - holding up to
				MAX_WORD_LENGTH	characters) to the end of the array Word.

PARAMETERS:		
NewWord			   The String (array of char) to be added
Word               An array of Strings (char[MAX_WORD_LENGTH])
DistinctWordCount  The number of different words in the array
TotalWordCount     The total number of words in the file
MaxWordCount       The max number of words that can be stored
				   in the array Word.

If DistinctWordCount == MaxWordCount, the function is exited.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void StoreWord(String  NewWord,
	String  Word[],
	int     Count[],
	int    &TotalWordCount,
	int    &DistinctWordCount,
	int     MaxWordCount)
{
	int i = 0;
	int k = 0;

	while ((Word[k] < NewWord) && (k < DistinctWordCount))
		// compares first elements of each array to prepare for insertion
		++k;
	
	if (NewWord == Word[k])   // NewWord is already there
	{
		++Count[k];
		++TotalWordCount;
	}

	else if (DistinctWordCount < MaxWordCount) // Room for a new word
	{
		++DistinctWordCount;  // If this line reached, found new word
		++TotalWordCount;

		for (i = DistinctWordCount - 1; i > k; --i) // Make room for NewWord
		{                                             
			Word[i] = Word[i - 1];
			Count[i] = Count[i - 1];
		}
		Word[k] = NewWord; // Store NewWord in array
		Count[k] = 1;
	}
}

/***************************  WriteWords   ********************************

DESCRIPTION:  Writes the strings in the array Word to standard output.
			  The words are left justified. After WORDS_PER_ROW words have
			  been written a new line is started.

PARAMETERS:   
Word       An array of Strings (char[MAX_WORD_LENGTH])
WordCount  The number of words in the array

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void WriteWords(String  Word[],
	int     Count[],
	int     TotalWordCount,
	int     DistinctWordCount)
{
	const char *Header1 = "    Word          Count | ",
		*Header2 = "                        | ",
		*Separator = "   | ";

	const int WORD_FW = 17,
		COUNT_FW = 4,
		WORDS_PER_ROW = 3;

	int C;

	cout << "\n\n";

	if (TotalWordCount == 0)
		return;

	for (C = 1; C <= WORDS_PER_ROW; ++C)
		cout << Header1;
	cout << endl;

	for (C = 1; C <= WORDS_PER_ROW; ++C)
		cout << Header2;
	cout << endl;

	int N = 0;

	while (N < DistinctWordCount)
	{
		for (C = 1; C <= WORDS_PER_ROW && N < DistinctWordCount; ++C)
		{
			cout << setiosflags(ios::left) << setw(WORD_FW) << Word[N];
			cout << setiosflags(ios::right) << setw(COUNT_FW) << Count[N];
			cout << Separator;
			cout << resetiosflags(ios::right);
			++N;
		}
		cout << endl;
	}

	cout << "\nTotal    Word Count : " << TotalWordCount << endl;
	cout << "\nDistinct Word Count : " << DistinctWordCount << endl;
}