/**********************************************************************

PROGRAMMER :
DATE       :
COMPILER   :  Visual C++ .NET
SOURCE FILE:  Assign7.cpp

ACTION:     Reads words from stdin and displays them in 3 columns.
See function ReadWord for the definition of a "word".
Reading from stdin input need to manual enter end of
file marker, ctrl-Z then enter.

NOTES :     The program does not handle correctly words longer than
MAX_WORD_LENGTH. If such words are encountered, they
are truncated.

Only as many as MAX_WORD_COUNT words can be stored in the
array holding the words.

=====================================================================*/

#include <iostream>
#include <string.h>
#include <iomanip>
#include <ctype.h>
using namespace std;

const int MAX_WORD_LENGTH = 254;

// The type definition below permits much easier prototyping of
// functions that pass arrays of strings.

typedef char String[MAX_WORD_LENGTH + 1]; //  + 1 for null terminator.

void ReadWord(String Word, int MaxLength);

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

int main(int argc, char* argv[])
{
	const  int MAX_WORD_COUNT = 130;

	String  NewWord,
		Word[MAX_WORD_COUNT + 1] = { "", "" };       // ALWAYS allow 1 extra slot!

	int     Count[MAX_WORD_COUNT + 1] = { 0 }, // Initialize array to zeros
		DistinctWordCount = 0,
		TotalWordCount = 0;

	ReadWord(NewWord, MAX_WORD_LENGTH);  //  Get the first word

	while (NewWord[0] != 0)            //  While NewWord is not null string
	{
		StoreWord(NewWord, Word, Count, TotalWordCount,
			DistinctWordCount, MAX_WORD_COUNT);

		ReadWord(NewWord, MAX_WORD_LENGTH);             //  Get the next word
	}

	WriteWords(Word, Count, TotalWordCount, DistinctWordCount);

	return 0;

}

/************************    ReadWord    *********************************

DESCRIPTION  Reads a word from standard input and stores in the array
Word.

For the purposes of this routine, a "word" is any
contiguous sequence of non-blank characters.

PARAMETERS   Word            An array of char.
MaxWordLength:  The maximum number of chars to store in
NewWord (not including the null terminator).
Chars beyond this number are discarded.

CALLS        cin.get and cin.good, both in the iostream library.
isspace from ctype file.

NOTE         Words longer than MaxWordLength are truncated.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void ReadWord(String  NewWord, int MaxWordLength)
{
	char Ch;
	int   K;

	cin >> Ch;     // Skip blanks, and get the first character of word

	K = 0;
	while (cin.good() && K < MaxWordLength && !isspace(Ch))  //  Store chars
	{
		NewWord[K++] = Ch;
		cin.get(Ch);
	}
	NewWord[K] = 0;                             //  Add null terminator

	while (cin.good() && !isspace(Ch))        //  Discard tail end of
		cin.get(Ch);                              //    long words
}

/***************************  StoreWord   ********************************

DESCRIPTION  Adds a string NewWord (holding up to MAX_WORD_LENGTH
characters) to the end of the array Word.

PARAMETERS   NewWord            The string (array of char) to be added
Word               An array of String (char[MAX_WORD_LENGTH])
DistinctWordCount  The number of different words in the array
TotalWordCount     The total number of word in the file
MaxWordCount       The max number of words that can be stored
in the array Word. If DistinctWordCount ==
MaxWordCount, the function is exited.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void StoreWord(String  NewWord,
	String  Word[],
	int     Count[],
	int    &TotalWordCount,
	int    &DistinctWordCount,
	int     MaxWordCount)
{
	int i, k = 0;

	while (strcmp(NewWord, Word[k]) > 0 && k < DistinctWordCount)
		++k;

	// Assert:  k is NewWord's correct position in the ordered array Word

	if (strcmp(NewWord, Word[k]) == 0)   // NewWord is already there
	{
		++Count[k];
		++TotalWordCount;
	}

	else if (DistinctWordCount < MaxWordCount) // Room for a new word
	{
		++DistinctWordCount;  // If this line reached, found new word
		++TotalWordCount;

		for (i = DistinctWordCount - 1; i > k; --i) // Make room for
		{                                             //  NewWord
			strcpy_s(Word[i], Word[i - 1]);
			Count[i] = Count[i - 1];
		}
		strcpy_s(Word[k], NewWord); // Store NewWord in array
		Count[k] = 1;
	}
}

/***************************  WriteWords   ********************************

DESCRIPTION  Writes the strings in the array Word to standard output.
The words are left justified. After WORDS_PER_ROW words have
been written a new line is started.

PARAMETERS   Word       An array of String (char[MAX_WORD_LENGTH])
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