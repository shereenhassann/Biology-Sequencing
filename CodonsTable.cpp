#include "CodonsTable.h"
#include "Sequence.h"
#include "Protein.h"
#include "DNA.h"
#include "RNA.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
//default constructor
CodonsTable::CodonsTable()
{
	//ctor
}
//takes the codon file content
void CodonsTable::LoadCodonsFromFile(string codonsFileName)
{
    fstream codonFile;
    string t = "";
    char* temp = new char[ 5 ];
    codonFile.open(codonsFileName);
    if (!codonFile.is_open())
	{
		cout << "Error opening file";
		return;
	}
	else
	{
	    for( int i = 0 ; i < 64 ; i++ )
        {
            getline( codonFile , t );
            for( int  j = 0 ; j < t.length(); j++ )
            {
                temp[ j ] = t[ j ];
            }
            codons[ i ].value[ 0 ] = temp[ 0 ];
            codons[ i ].value[ 1 ] = temp[ 1 ];
            codons[ i ].value[ 2 ] = temp[ 2 ];
            codons[ i ].value[ 3 ] = '\0';
            codons[ i ].AminoAcid = temp[ 4 ];
        }
    }
}
//gets the amino acid of each codon
Codon  CodonsTable :: getAminoAcid( char * value )
{
    for ( int i = 0; i < 64; i++ )
    {
        bool flag = true;
        for ( int j = 0; j < 4 ; j++ )
        {
            if ( this -> codons [ i ].value[ j ] != value[ j ] )
            {
                flag = false;
            }
        }

        if ( flag )
        {
            return codons[ i ];
        }
    }

    Codon Invalid;
    for ( int i = 0; i < 4; i++ )
    {
        Invalid.value[i] = ' ';
    }
    Invalid.AminoAcid = ' ';

    return Invalid;
}
//if you want to change the content of the codon table
void CodonsTable :: setCodon(char * value, char AminoAcid, int index)
{
    for( int i = 0; i < 4 ; i++ )
        this->codons[ index ].value[i] = value[i];
    this->codons[ index ].value[ 4 ] = '\0';

    this->codons[ index ].AminoAcid = AminoAcid;
}

//destructor
CodonsTable:: ~CodonsTable()
{
	//dtor
}

