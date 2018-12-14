#ifndef DNA_H
#define DNA_H
#include <iostream>
#include <algorithm>
#include "Sequence.h"

using namespace std;

class RNA;

enum DNA_Type{ promoter, motif, tail, noncoding };

class DNA : public Sequence
{
  	private:
        DNA_Type type;
        DNA *complementary_strand;
        int startIndex;
        int endIndex;
    public:
 	 	// constructors and destructor
        DNA();
        DNA( char* seq , DNA_Type atype );
        DNA( DNA& rhs );
        ///void setType( DNA_Type t );
        void setStartIndex( int start );
        int getStartIndex() const;
        void setEndIndex( int endd );
        int getEndIndex() const;
        DNA operator + ( DNA& dna );
        bool operator == ( DNA& dna );
        bool operator != ( DNA& dna );
        //void operator =( DNA dna );
        int getType() const;
        void getTypeChar() const;
        void setType( int type );

        void LoadSequenceFromFile(string filename);
        void SaveSequenceToFile(string filename);

        friend istream& operator >> ( istream& in , DNA& dna );
        friend ostream& operator << ( ostream& out , DNA& dna );



        ~DNA();
 	 	// function printing DNA sequence information to user
        void Print();
        // function to convert the DNA sequence to RNA sequence
        // It starts by building the complementary_strand of the current
        // DNA sequence (starting from the startIndex to the endIndex), then,
        // it builds the RNA corresponding to that complementary_strand.
        RNA ConvertToRNA();
 	 	// function to build the second strand/pair of DNA sequence
	    // To build a complementary_strand (starting from the startIndex to
        // the endIndex), convert each A to T, each T to A, each C to G, and
        // each G to C. Then reverse the resulting sequence.
        void BuildComplementaryStrand();
        DNA* getCompStrand() const;
        void printComp();
  };

#endif // DNA_H
