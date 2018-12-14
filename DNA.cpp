#include "DNA.h"
#include <iostream>
#include <cstring>
#include "RNA.h"
#include "Sequence.h"
#include <fstream>

using namespace std;

DNA::DNA() : Sequence() //default constructor
{
    type = promoter;
    startIndex = 5;
    endIndex = 3;
}
DNA ::DNA ( char* seq , DNA_Type atype )    //parameterized constructor
{
    this -> seq = new char[strlen(seq) + 1];
    for(int i = 0 ; i < strlen(seq) ; i++ )
        this -> seq[ i ] = seq[ i ];
    type = atype;
}

//copy constructor
DNA::DNA( DNA& rhs )
{
    char* Array = rhs.getSeq();
    int len = strlen( rhs.getSeq() );
    strcpy( this -> seq , Array );
    this -> type = rhs.type;
    this -> complementary_strand = rhs.complementary_strand;
    this -> startIndex =rhs.startIndex;
    this -> endIndex = rhs.endIndex;
}
void DNA::LoadSequenceFromFile(string filename) //load sequence from a file
{
	ifstream file;
	file.open(filename);
	if (file.fail())			//checking if opening file failed
	{
		cout << "\nError opening file.\n";
		return;
	}
    else{
        string line;

        while (!file.eof())			//printing the file data
        {
            getline(file, line);
            cout << line << endl;
        }
        file.close();
    }

}

void DNA::SaveSequenceToFile(string filename)
{
	string line;

	ofstream file;
	file.open(filename, ios_base::app);

	if (file.fail())		//checking if the file opened successfully
	{
		cout << "\nError opening file. \n";
		return;
	}
    file << "DNA :\n";
    switch (getType())  //put the type in the file
	{
	case 0:
		file << "Type: promoter\n";
		break;
	case 1:
		file << "Type: motif\n";
		break;
	case 2:
		file << "Type: tail\n";
		break;
	case 3:
		file << "Type: noncoding\n";
		break;
	}
    file << "DNA sequence :\n5 : ";
    file << this -> getSeq();
    file << " : 3\n";
    file << "Complementary strand : ";
    this -> BuildComplementaryStrand();
    file << this -> getCompStrand() -> getSeq();
    file <<"\n\n";
}
void DNA :: Print() //print DNA
{
    cout << "Sequence is: " << seq << endl;
    this -> BuildComplementaryStrand();
    cout << "Complementary strand is: " << ( *getCompStrand() ).getSeq() << endl;
	cout << "Type is: ";
    getTypeChar();
}

RNA DNA::ConvertToRNA() //change DNA to RNA
{
	RNA rna;
    char* temp = this -> seq;
	for (int i = 0 ; i < strlen( this -> seq ) ; i++)
	{
		if ( this -> seq[ i ] == 'T' )
		{
			temp[ i ] = 'U';
		}
	}
	rna.setSeq( temp );
	rna.setType(mRNA);
	return rna;
}

void DNA::setType( int type )   //set the type by taking an integer
{
	switch ( type )
	{
	case 0:
		this -> type = promoter;
		break;

	case 1:
		this -> type = motif;
		break;

	case 2:
		this -> type = tail;
		break;

	case 3:
		this -> type = noncoding;
		break;

	default:
		cout << "\nInvalid Type.\n";
		break;
	}
}

int DNA::getType() const
{
	return this -> type;
}

void DNA::getTypeChar() const   //get the string form of the type
{
    switch( getType() )
    {
    case 0:
        cout << "promoter" << endl;
        break;
    case 1:
        cout << "motif" << endl;
        break;
    case 2:
        cout << "tail" << endl;
        break;
    case 3:
        cout << "noncoding" << endl;
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
}

bool DNA :: operator == ( DNA& dna )    //check equality
{
    if( ( strlen(this -> seq) == strlen( dna.seq ) )  && ( this -> getType() == dna.getType() ) )
    {
        for( int i = 0 ; i < strlen( this -> seq ) ; i++ )
        {
            if( this -> seq[ i ] != dna.seq[ i ] )
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool DNA :: operator != ( DNA& dna )    //check not equal
{
    if( ( *this ) == dna )
        return false;
    return true;
}

DNA DNA :: operator + ( DNA& dna )  //add 2 DNA sequences
{

    char* seq1 = new char [ strlen( this -> seq ) + strlen( dna.seq ) + 1];
    seq1[ strlen( this -> seq ) + strlen( dna.seq ) ] = '\0';
    for( int i = 0 ; i <strlen( this -> seq ) + strlen( dna.seq ) ; i++ )
    {
        seq1[ i ] = 'A';
    }
    for( int i = 0 ; i < strlen( this -> seq ) ; i++ )
    {
        seq1[ i ] = this -> seq[ i ];
    }
    for( int i = strlen( this -> seq ) , j = 0 ; i < strlen( dna.seq ) + strlen( this -> seq ) ; i++ , j++ )
    {
        seq1[ i ] =  dna.seq[ j ];
    }
    DNA result(seq1 , this -> type); /// type need to be handled
    return result;

}

void DNA::setStartIndex( int start )
   {
       startIndex = start;
   }

int DNA::getStartIndex() const
{
    return startIndex;
}

void DNA::setEndIndex( int End )
{
    endIndex = End;
}

int DNA::getEndIndex() const
{
    return endIndex;
}

void DNA::BuildComplementaryStrand()    //builds the complementary strand of the DNA sequence
{
    char* seq1 = new char[ strlen( this -> getSeq() ) + 1];
    strcpy( seq1 , this -> getSeq() );
    seq1[ strlen( this -> getSeq() ) ] = '\0';
    for(int i = 0 ; i < strlen( this -> seq ) ; i++ )
    {
        if( this -> seq[ i ] == 'A' )
            seq1[ i ] = 'T';
        else if ( this -> seq[ i ] == 'T' )
            seq1[ i ] = 'A';
        else if ( this -> seq[ i ] == 'C' )
            seq1[ i ] = 'G';
        else if ( this -> seq[ i ] == 'G' )
            seq1[ i ] = 'C';
    }
    reverse( seq1 , seq1 + strlen( seq1 ) );
    this -> complementary_strand = new DNA;
    ( *complementary_strand ).setSeq( seq1 );
    (*complementary_strand).setType((this->getType()));
}

DNA* DNA::getCompStrand() const //get the complementary strand
{
    return ( complementary_strand ) ;
}

void DNA :: printComp() //print the complementary strand
{
    cout << *( complementary_strand )<<endl;
}
/*void DNA :: operator =( DNA dna )
{
    this -> seq = dna.seq;
    this -> type = dna.type;
    dna.BuildComplementaryStrand();
    this -> complementary_strand = dna.complementary_strand;
}*/
void validDNASeq( char* seq )   //check validity
{
    int check = 0;
    for( int i = 0 ; i < strlen( seq ) ; i++ )
    {
        if( seq[ i ] == 'A' || seq[ i ] == 'C' || seq[ i ] == 'G' || seq[ i ] == 'T' )
        {
            check++;
        }
    }
    if( check < strlen( seq ) )
    {
        throw 1 ;
    }
}
void validDNAChoice( char choice )  //check validity
{
    if( choice != '1' && choice != '2' && choice != '3' && choice != '4' )
    {
        throw 2;
    }
}
istream& operator >> ( istream& in , DNA& dna )     //input DNA
{
    char choice;
    cout << "Please choose the type of the DNA : \n\n1-promoter.\n2-motif.\n3-tail.\n4-noncoding.\n>> ";
    in >> choice;
    bool flag = false;
    do
    {
        try
        {
            validDNAChoice( choice );
            flag = false;
        }
        catch ( int n )
        {
            flag = true;
            cout << "Invalid input. Please choose 1, 2, 3, or 4 : \n>> ";
            in >> choice;
        }

    }while( flag );
    int choosen = int( choice  - '0' );
    dna.setType( choosen - 1 );
    cout << "Please enter the DNA strand : ";
    string strand;
    in >> strand;
    for( int i = 0 ; i < strand.length() ; i++ )
    {
        strand[ i ] = toupper( strand[ i ] );
    }
    char* str = new char[ strand.length() ];
    for(int i = 0 ; i < strand.length() ; i++ )
    {
        str[ i ] = strand[ i ];
    }
    flag = false;
    //Checking input validity
    do
    {
        try
        {
            validDNASeq( str );
            flag = false;
        }
        catch (int n )
        {
            flag = true;
            cout << "Invalid input. Please enter a valid strand : \n>> ";
            in >> strand;
            for( int i = 0 ; i < strand.length() ; i++ )
            {
                strand[ i ] = toupper( strand[ i ] );
            }
            str = new char[ strand.length() ];
            for(int i = 0 ; i < strand.length() ; i++ )
            {
                str[ i ] = strand[ i ];
            }
        }
    }while( flag );
    dna.setSeq( str );
	return in;
}
ostream& operator << ( ostream& out , DNA& dna )    //print DNA
{
    out << "Type is: ";
    dna.getTypeChar();
    out << "The DNA Sequence is: " << dna.getSeq() << endl;
    dna.BuildComplementaryStrand();
    out << "Complementary strand is: " << (*(dna.getCompStrand() )).getSeq() << endl;
	return out;
}
DNA::~DNA() //destructor
{
	delete[] seq;
}
