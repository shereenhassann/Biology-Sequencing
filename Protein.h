#ifndef PROTEIN_H
#define PROTEIN_H
#include "Sequence.h"
//#include "DNA.h"
//#include "CodonsTable.h"
//#include "RNA.h"

using namespace std;

class DNA;
enum Protein_Type {Hormon, Enzyme, TF, Cellular_Function};
struct DNAArr{
    int sz;
    DNA* dna;
};
class Protein : public Sequence
{
  	private:
        Protein_Type type;
      public:
 	 	// constructors and destructor
 	 	Protein();
 	 	Protein(char * p);
 	 	~Protein();
 	 	Protein ( char* seq , Protein_Type atype );
        Protein( Protein& rhs );
 	 	void Print();
 	 	void setType(int type);
 	 	int getType();
 	 	void getTypeChar();

 	 	void LoadSequenceFromFile(string filename);
        void SaveSequenceToFile(string filename);

 	 	Protein operator + ( Protein& protein );
        bool operator == ( Protein& protein );
        bool operator != ( Protein& protein );
        //void operator = ( Protein protein );

        friend ostream& operator << ( ostream& out , Protein& protein );
        friend istream& operator >> ( istream& in , Protein& protein );

 	 	// return an array of DNA sequences that can possibly
                // generate that protein sequence
        DNAArr GetDNAStrandsEncodingMe( const DNA & bigDNA );
        ///int* getArraySize( const DNA & bigDNA );

};

#endif // PROTEIN_H
