/*                     s t r i n g 2 . c p p
 ~~~~~~~~~~~~~~~~~~~~~
 A C++ class definition that improves on the String type defined in
 String1.CPP.  Recall that implementation of the class String used an
 array of char to hold the characters in the String and a length field
 to keep track of the number of characters in the string.
 
 Several new member functions are now implemented, including
 
 =           :  Overloaded "=" that replaces Assign().
 
 <<          :  Overloaded "<<", that replaces Write()
 
 >>          :  Overloaded ">>", that reads a word from standard input.
 
 <           :  Compares two Strings to see if first is less than second.
 
 !=          :  Tests to see if two strings are different.
 
 ==          :  Tests to see if two strings are equal.
 
 +           :  Concatenates the characters in two strings
 
 NOTE: This is clearly a partial implementation of String, since many
 important operators remain to be written. These include
 >, <=, >=, +=, and pattern matching.
 = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =*/
#include <iostream>
#include <ctype.h>
using namespace std;

class String
{
	enum     { MAX_LENGTH = 254 };  // Max value of an unsigned char
    
	unsigned char Chr[MAX_LENGTH];  // Holds the chars in a String
    
	unsigned char Len;              // Current length of a String.
    
public:
    
	int Length() const             // "const" means data not changed by call
	{                              // When placed here is inline function
		return Len;
	}
    
	int MaxLength() const          // Gives access to max string length
	{
		return MAX_LENGTH;
	}
    
	String()                 // A constructor that initializes strings to null.
	{                        // Called automatically when a String declared
		Len = 0;
	}
    
	String(const char P[]);
    
	String& operator= (const char Source[]);
    
	int operator!=    (const String& Rhs);
    
	int operator== (const String& Rhs);
    
	int operator<     (const String& Rhs);
    
	String operator+  (const char Rhs[]);
    
	String operator+  (const String& Rhs);
    
	friend ostream& operator<< (ostream& Sout, const String &S);
    
	friend istream& operator>> (istream& In, String &S);
};

/******************** String(<string literal>) ***************************
 
 This constructor allows declarations of the form:
 
 String S("Hello world!"); or the equivalent
 String S = "Hello world!";
 
 Both declare and initializes a string S. The constructor supports
 initializing a string to any char pointer, so the following are
 also legal
 
 String S = A;         //  Where declaration of A is "char A[] = "
 String S = P;         //  Where declaration of P is "char* P"
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String::String(const char P[])
{
	int k = 0;
    
	while (k < MaxLength() && P[k] != 0)
	{
		Chr[k] = P[k];                           // Copy chars from P
		k++;
	}
    
	Len = k;
}

/***************************  operator=    ******************************
 
 This function gives us the ability to assign an "ordinary C string" to
 one of the strings in the String class. These null terminated C strings
 are of 3 varieties:
 
 1) string constants, i.e. pointers to an array of char stored
 somewhere in a program's memory space
 2) Arrays of char, i.e. constant pointers
 3) char *  pointer variables
 
 If S has is in our string class, this routine permits such things as
 
 S = "Hello!";
 S = A;         // where A has been declared:  "char A[8];"
 S = P;         // where P has been declared:  "char* P;"
 
 The function is written so that it supports assignments of the form
 
 S1 = S2 = "Hello";   // Equivalent to S1 = (S2 = "Hello");
 
 In order to do this, it is necessary for this function to return a
 value equal to the value just assigned to S2. C++ permits referencing
 the hidden "parameter" passed when a member function is called. The
 variable "this" is a pointer to the hidden parameter, so that "*this"
 is a reference to the value of the hidden parameter.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String& String::operator= (const char RightSide[])
{
	int k = 0;
    
	while (k < MaxLength() && RightSide[k] != 0)
	{
		Chr[k] = RightSide[k];     // Copy char from Rhs to Lhs.
		k++;
	}
	Len = k;
    
	return *this;   // Dereference "this", the pointer to left hand side
}

/**************************  operator!=  *********************************
 
 Returns a true if *this != Rhs. For example, if in main()
 the comparison "if ( S1 != S2 ) " is made, then *this is S1 and Rhs is S2.
 
 The const parameter Rhs is passed by reference so that a copy of Rhs
 need not be made upon entry to this function.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int String::operator!= (const String& Rhs)
{
	if (Len != Rhs.Len)    // Are not equal if lengths are different
		return 1;
    
	for (int k = 0; k < Len; ++k)   // If we find one different char
		if (Chr[k] != Rhs.Chr[k])     //  then strings are different
			return 1;
    
	return 0;   // If we got to this line, all chars are the same
}

/**************************  operator==  *********************************
 
 Returns a true if *this = Rhs. For example, if in main()
 the comparison "if ( S1 == S2 ) " is made, then *this is S1 and Rhs is S2.
 
 The const parameter Rhs is passed by reference so that a copy of Rhs
 need not be made upon entry to this function.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int String::operator== (const String& Rhs)
{
	if (Len != Rhs.Len)    // Are not equal if lengths are different
		return 0;
    
	for (int k = 0; k < Len; ++k)   // If we find one different char
		if (Chr[k] != Rhs.Chr[k])     //  then strings are different
			return 0;
    
	return 1;   // If we got to this line, all chars are the same
}

/**************************  operator<  **********************************
 
 Returns a true if Lhs < Rhs, i.e. if the left hand side of "<"
 comes after the right hand side using the usual rules for ordering.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int String::operator< (const String& Rhs)
{
	int k = 0;
    
	while (k < Len && k < Rhs.Len)  // while not at the end of either
		if (Chr[k] < Rhs.Chr[k])
			return 1;
		else if (Chr[k] > Rhs.Chr[k]) // Try to find different characters
			return 0;
		else
			++k;
    
    //  Assert: if this line reached one string is substring of the other
    //          or the strings are the same.
    
    return Len < Rhs.Len;  // True only Lhs is substring of Rhs
}

/***************************  operator>>  ********************************
 
 Overloads the input operator, >>, so that it works with strings.
 
 The standard convention for input via >> is used, namely
 
 skip whitespace
 read and store contiguous non-blanks
 stop when whitespace read or error occurs
 
 In effect then, this routine reads the next word (whitespace delimited)
 in the input stream. This is similar to the action of cin >> C_Str,
 where C_Str is a null terminated char array. However, unlike the
 standard char array word read, the read below is safe, and will not
 will not store chars beyond the end of the array.
 
 See comments above operator<< for more information on overloading I/O
 operators, including an explanation as to why this must be a friend.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
istream& operator>> (istream& In, String &S)
{
	char Ch;
    
	In >> Ch;          // Skip white space and punctuation
	if (In.eof())      // used to check to see if at end of file first
	{
		S.Len = 0;
		S.Chr[0] = 0;
		return In;
	}
    
	int  k = 0;
	while (!isspace(Ch) && k < S.MAX_LENGTH && In.good() &!In.eof()) //Read blank delimited "word"
	{
		S.Chr[k++] = Ch;         //  Store non-blank
		In.get(Ch);              //  Read next char
	}
    
	S.Len = k;
    
	return In;   //  Permits cascading of operator
}

/*************************** operator <<    *****************************
 
 This function overloads the << operator to give us output of objects
 in the String class. Overloading of this insertion or put to operator
 requires that one understand how expressions of the form
 
 a)  cout << "X = " << X or the equivalent b) (cout << "X = ") << X
 
 are evaluated. First, cout is an object in the class ostream that
 is associated with standard output. As is the case with most C++
 operators, an expression such as cout << "X = " has both a value
 and a side effect. The side effect of the operation is, of course,
 to send the string "X = " to the standard output stream. A careful
 inspection of the parenthesized expression b) above makes it clear that
 the value of the expression   cout << "X = "  must be an object  in
 ostream. This explains the return type of the overloaded operator
 << as defined below.
 
 Note also that one of the requirements of C++ is that an operator that
 belongs to a class must be associated with the class member to the left
 of the operator. In the case of the overloaded "<<" operator, the
 object to the left of "<<" is not a string member. This means we have
 a syntactic problem, one that can be solved by declaring operator<<
 to be a "friend" of the class. A friend function is not a member of a
 class, but it can reference the private fields of a class.
 
 The code below to do the output could be as simple as
 
 Sout.write(S.Chr, S.Len);
 
 but this will not work with the setw manipulator.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
ostream& operator<< (ostream& Sout, const String &S)
{
	char TempStr[S.MAX_LENGTH];
    
	int k = 0;
	for (k; k < S.Len; ++k)
		//Sout << S.Chr[k];
		TempStr[k] = S.Chr[k];          // Create copy of String
	
	TempStr[k] = 0;                   // Need null terminator for next line
    
	Sout << TempStr;                  // Support field width
    
	return Sout;                      // Support cascading of <<
}

/************************  operator+    **********************************
 
 Returns the concatenation of Strings A and B (passed by reference for
 reasons of efficiency).  If the maximum length of a string is exceeded,
 the extra characters are discarded.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String String::operator+ (const String& Rhs)
{
	String Temp;
	int    I = 0, k;
    
	Temp = *this;                     // Temp now has copy of left operand
	k = Temp.Len;
    
	while (I < Rhs.Len && k < Temp.MAX_LENGTH)
        
		Temp.Chr[k++] = Rhs.Chr[I++];  // Copy char from second string
    
	Temp.Len = k;                    // Adjust length
    
	return Temp;
}

/************************  operator+    **********************************
 
 Returns the concatenation of a String A and a ordinary C string B (i.e.
 a pointer). A typical invocation might be
 
 S = S + " ";
 
 If the maximum length of string A is exceeded, A is truncated. The
 routine assumes that P points to an area of memory holding a series of
 null terminated chars.
 
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
String String::operator+ (const char Rhs[])
{
	String Temp;
	int    I = 0, k;
    
	Temp = *this;          // Put left string in Temp
	k = Temp.Len;       // Start just past the end of Temp
    
	while (Rhs[I] != 0 && k < Temp.MAX_LENGTH)
        
		Temp.Chr[k++] = Rhs[I++];           // Copy next char from Rhs
    
	Temp.Len = k;                         // Temp now has k chars
    
	return Temp;
}