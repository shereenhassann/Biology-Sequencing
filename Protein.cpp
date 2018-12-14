#include "Protein.h"
#include "Sequence.h"
#include "DNA.h"
#include "RNA.h"
#include <cstring>
#include <string>
#include <iostream>
#include "CodonsTable.h"
#include "RNA.h"
#include <fstream>

using namespace std;

Protein::Protein() :Sequence()  //default constructor
{
	type = Cellular_Function;
}
Protein::Protein( Protein& rhs )    //copy constructor
{
    char* Array = rhs.getSeq();
    int len = strlen( rhs.getSeq() );
    strcpy( this -> seq , Array );
    this -> type = rhs.type;
}
Protein::~Protein() //destructor
{
    delete[] seq;
}
Protein ::Protein ( char* seq , Protein_Type atype )    //parameterized constructor
{
    this -> seq = new char[strlen(seq) + 1];
    for(int i = 0 ; i < strlen(seq) ; i++ )
        this -> seq[ i ] = seq[ i ];
    type = atype;
}
void Protein::setType(int type) //set type by taking integer
{
	switch (type)
	{
	case 0:
		this->type = Hormon;
		break;

	case 1:
		this->type = Enzyme;
		break;

	case 2:
		this->type = TF;
		break;

	case 3:
		this->type = Cellular_Function;
		break;
	case 5:
		break;
	default:
		cout << "\nInvalid input.\n";
		break;
	}


}

int Protein::getType()
{
	return (this)->type;
}

void Protein::getTypeChar() //get the string form of a type
{
    switch( getType() )
    {
    case 0:
        cout << "Hormon" << endl;
        break;
    case 1:
        cout << "Enzyme" << endl;
        break;
    case 2:
        cout << "TF" << endl;
        break;
    case 3:
        cout << "Cellular_Function" << endl;
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
}
void Protein::LoadSequenceFromFile(string filename)			//displaying the file content
{
	ifstream file;
	file.open(filename);
	if (file.fail())
	{
		cout << "\nError opening file.\n";
		return;
	}
    else{
        string line;
        while (!file.eof())
        {
            getline(file, line);
            cout << line << endl;
        }
        file.close();
    }

}

void Protein::SaveSequenceToFile(string filename)		//Saving the Protein to a file
{
	string line;

	ofstream file;
	file.open(filename, ios_base::app);

	if (file.fail())
	{
		cout << "\nError opening file. \n";
		return;
	}

	file << "Protein :\nProtein Type : ";
    switch( getType() )
    {
    case 0:
        file << "Hormon\n";
        break;
    case 1:
        file << "Enzyme\n";
        break;
    case 2:
        file << "TF\n";
        break;
    case 3:
        file << "Cellular_Function\n";
        break;
	}
    file << "Protein sequence : ";
    file << this -> getSeq();
    file <<"\n\n";
}
void Protein :: Print()
{
    cout << "Sequence is: " << seq << endl;
	cout << "Type is: ";
    getTypeChar();
}
bool Protein :: operator == ( Protein& protein )    //check equality
{
    if( ( strlen(this -> seq) == strlen( protein.seq ) ) && ( this -> getType() == protein.getType() ) )
    {
        for( int i = 0 ; i < strlen( this -> seq ) ; i++ )
        {
            if( this -> seq[ i ] != protein.seq[ i ] )
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Protein :: operator != ( Protein& protein )    //check not equal
{
    if( ( *this ) == protein )
        return false;
    return true;
}

Protein Protein :: operator + ( Protein& protein )  //add 2 protein sequences
{

    char* seq1 = new char [ strlen( this -> seq ) + strlen( protein.seq ) + 1];
    seq1[ strlen( this -> seq ) + strlen( protein.seq ) ] = '\0';
    for( int i = 0 ; i <strlen( this -> seq ) + strlen( protein.seq ) ; i++ )
    {
        seq1[ i ] = 'A';
    }
    for( int i = 0 ; i < strlen( this -> seq ) ; i++ )
    {
        seq1[ i ] = this -> seq[ i ];
    }
    for( int i = strlen( this -> seq ) , j = 0 ; i < strlen( protein.seq ) + strlen( this -> seq ) ; i++ , j++ )
    {
        seq1[ i ] =  protein.seq[ j ];
    }
    Protein result(seq1 , this -> type); /// type need to be handled
    return result;

}

// return an array of DNA sequences that can possibly
// generate that protein sequence

DNAArr Protein :: GetDNAStrandsEncodingMe( const DNA & bigDNA)  //gets all possible small sequences in the big DNA that makes the wanted protein
{

    char* smallDNA = new char[ (strlen( this->getSeq() )*3) + 1];
    smallDNA[ (strlen(getSeq()) * 3) ] = '\0';
    int k = 0;

    int arrSz = 0;
    int bigg = ( strlen( bigDNA.getSeq() ) );
    int obj = ( strlen( getSeq() ) );

    char* tmp = new char[ obj + 1 ];
    tmp[ obj ] = '\0';
    strcpy(tmp , this->getSeq());


    for( int i = 0 ; i < ( ( bigg ) - ( obj * 3 ) + 1 ) ; i++ )
    {
        for( int j = 0 ; j < (( obj ) * 3) ; j++ )
        {
            smallDNA [ k ] = bigDNA.getSeq()[ j + i ];
            k++;
        }

        k = 0;
        DNA small;
        small.setSeq( smallDNA );

        Protein p;
        p = small.ConvertToRNA().ConvertToProtein();
        char* tmp2 = new char[ obj + 1 ];
        tmp2[ obj ] = '\0';
        strcpy(tmp2 , p.getSeq());
        bool isflag = true;
        if ( strlen(tmp2) == strlen(tmp) )
        {
            int loop = strlen(tmp);
            for ( int i = 0; i < loop; i++ )
            {
                if ( tmp[i] != tmp2[i] ) { isflag = false; break; }
            }
        }
        else
        {
            isflag = false;
        }
        if( isflag )
        {
            arrSz++;
        }
    }



    DNA* dnaArr = new DNA [ arrSz ];
    int index = 0;
    for( int i = 0 ; i < ( ( bigg ) - ( obj * 3 ) + 1 ) ; i++ )
    {
       for( int j = 0 ; j < (( obj ) * 3) ; j++ )
        {
            smallDNA [ k ] = bigDNA.getSeq()[ j + i ];
            k++;
        }
        k = 0;
        DNA small;
        small.setSeq( smallDNA );
        Protein p;
        p = small.ConvertToRNA().ConvertToProtein();
        char* tmp2 = new char[ obj + 1 ];
        tmp2[ obj ] = '\0';
        strcpy(tmp2 , p.getSeq());
        bool isflag = true;
        if ( strlen(tmp2) == strlen(tmp) )
        {
            int loop = strlen(tmp);
            for ( int i = 0; i < loop; i++ )
            {
                if ( tmp[i] != tmp2[i] )
                {
                    isflag = false;
                    break;
                }
            }
        }
        else
        {
            isflag = false;
        }
        if( isflag )
        {
            dnaArr[ index++ ].setSeq( smallDNA );
            dnaArr[ index-1 ].BuildComplementaryStrand();
        }
    }
    DNAArr arrayStruct;
    arrayStruct.sz = arrSz;
    arrayStruct.dna = dnaArr;

    return arrayStruct;
}

/*void Protein :: operator = ( Protein protein )
{
    this -> seq = protein.seq;
    this -> type = protein.type;
}*/

void validProteinSeq( char* seq )   //check validity
{
    int check = 0;
    for( int i = 0 ; i < strlen( seq ) ; i++ )
    {
        if( seq[ i ] == 'K' || seq[ i ] == 'N' || seq[ i ] == 'T' || seq[ i ] == 'R' || seq[ i ] == 'S' || seq[ i ] == 'I'
           || seq[ i ] == 'M' || seq[ i ] == 'Q' || seq[ i ] == 'H' || seq[ i ] == 'P' || seq[ i ] == 'L' || seq[ i ] == 'E'
           || seq[ i ] == 'D' || seq[ i ] == 'A' || seq[ i ] == 'G' || seq[ i ] == 'V' || seq[ i ] == 'Y' || seq[ i ] == 'C'
           || seq[ i ] == 'W' || seq[ i ] == 'F' )
        {
            check++;
        }
    }
    if( check < strlen( seq ) )
    {
        throw 1 ;
    }
}

void validProteinChoice( char choice )  //check validity
{
    if( choice != '1' && choice != '2' && choice != '3' && choice != '4' )
    {
        throw 2;
    }
}

istream& operator >> ( istream& in , Protein& protein ) //input protein
{
    char choice;
    cout << "Please choose the type of the Protein : \n\n1-Hormon.\n2-Enzyme.\n3-TF.\n4-Cellular_Function.\n>> ";
    in >> choice;
    bool flag = false;
    do
    {
        try
        {
            validProteinChoice( choice );
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
    protein.setType( choosen - 1 );
    cout << "Please enter the Protein strand : ";
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
            validProteinSeq( str );
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
    protein.setSeq( str );
	return in;
}

ostream& operator << ( ostream& out ,Protein& protein ) //print protein
{
    out << "The type of your Protein is : " ;
    protein.getTypeChar();
    out << "Protein Sequence is: " << protein.getSeq() << endl;
    return out;
}
