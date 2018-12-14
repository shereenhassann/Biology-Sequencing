#ifndef RNA_H
#define RNA_H

//#include "DNA.h"
//#include "Protein.h"
//#include "CodonsTable.h"
#include "Sequence.h"
#include <iostream>

using namespace std;

class Protein;
class DNA;
class CodonsTable;

enum RNA_Type {mRNA, pre_mRNA, mRNA_exon, mRNA_intron};

class RNA : public Sequence
{
  	private:
        RNA_Type type;
  	public:
 	 	// constructors and destructor
        RNA();
        RNA(char* seq, RNA_Type atype);
        RNA(RNA& rhs);
        ~RNA();
 	 	// function to be overridden to print all the RNA information
        void Print();
        RNA operator + ( RNA& rna );
        bool operator == ( RNA& rna );
        bool operator != ( RNA& rna );
        //void operator = ( RNA rna );

        void setType( int type );
        int getType();
        void getTypeChar();

        void LoadSequenceFromFile(string filename);
        void SaveSequenceToFile(string filename);

        friend ostream& operator << ( ostream& out , RNA& rna );
        friend istream& operator >> ( istream& in , RNA& rna );
 	 	// function to convert the RNA sequence into protein sequence
        // using the codonsTable object
        Protein ConvertToProtein( );
 	 	// function to convert the RNA sequence back to DNA
        DNA ConvertToDNA();
};

#endif // RNA_H
