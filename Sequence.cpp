#include "Sequence.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// constructors and destructor
Sequence::Sequence()
{

}
Sequence::Sequence( int length )
{
    (this -> seq )= new char[ length ];

    for( int i = 0 ; i < length ; i++ )
    {
        seq[ i ] = 'A';
    }
}
Sequence::Sequence( Sequence& rhs )
{
    char* Array = rhs.getSeq();
    int len = strlen( rhs.getSeq() );
    strcpy( (this -> seq) , Array );
}
Sequence::~Sequence()
{
    delete[] seq;
}

//setter function for sequence.
void Sequence:: setSeq( char* s )
{
    int  len = strlen( s );
    this -> seq = new char[ len ];
    strcpy( this -> seq , s );
}
//getter function for sequence
char* Sequence:: getSeq() const
{
    return (seq);
}
/*bool Sequence :: operator != ( Sequence seq )
{
    if( ( *this ) == seq )
        return false;
    return true;
}
bool Sequence :: operator == ( Sequence seq )
{
    if( strlen(this -> seq) == strlen( seq.seq ) )
    {
        for( int i = 0 ; i < strlen( this -> seq ) ; i++ )
        {
            if( this -> seq[ i ] != seq.seq[ i ] )
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
Sequence Sequence :: operator + ( Sequence& seq )
{
    Sequence result;
    result.seq = new char [ strlen( this -> seq ) + strlen( seq.seq ) ];
    for( int i = 0; i < strlen( this -> seq ) ; i++ )
    {
        result.seq[ i ] = this -> seq[ i ];
    }
    for( int i = strlen( this -> seq ) , j = 0 ; i < strlen( seq.seq ) + strlen( this -> seq ) ; i++ , j++ )
    {
        result.seq[ i ] =  seq.seq[ j ];
    }
    return result;
}
*/
/**int LCS(char* s1,char* s2,int i  , int j )
{
    if(s1[i]=='\0' || s2[j] == '\0')
        return 0;
    else if(s1[i] == s2[j])
        return 1+LCS(s1 , s2 , i+1 , j+1);
    else
        return max(LCS(s1 , s2, i+1 , j),LCS(s1 , s2 , i , j + 1));
}*/
// friend function that will find the LCS (longest common
// subsequence) between 2 sequences of any type, according to
// polymorphism
char* Align( Sequence* s1 , Sequence* s2 )
{
    int** LCS = new int* [ strlen( s1 -> getSeq() ) + 1 ] ;
    for ( int i = 0 ; i < strlen( s1 -> getSeq() ) + 1 ; i++ )
    {
        LCS[ i ] = new int [ strlen( s2 -> getSeq() ) + 1 ];
    }
    for( int i = 0 ; i < strlen( s1 -> seq ) + 1 ; i++ )
    {
        for( int j = 0 ; j  < strlen( s2 -> seq ) + 1 ; j++ )
        {
             LCS[ i ][ j ] = 0;
        }

    }
    for( int i = 1  ; i <= strlen( s1 -> getSeq() ) ; i++ )
    {
        for( int j = 1  ; j <= strlen( s2 -> getSeq() ) ; j++)
        {
            if( s1 -> getSeq()[ i - 1 ] == s2 -> getSeq()[ j - 1 ] )
            {
                LCS[ i ][ j ] = 1 + LCS[ i - 1 ][ j - 1 ];
            }
            else
            {
                LCS[ i ][ j ] = max( LCS[ i - 1 ][ j ] , LCS[ i ][ j - 1 ] );
            }
        }
    }
    char * result = new char[ LCS[ strlen( s1 -> getSeq() ) ][ strlen( s2 -> getSeq() ) ] ];
    int i = strlen( s1 -> getSeq() ) , j = strlen( s2 -> getSeq() ) , k = 0;
    while( i != 0 && j!= 0 )
    {
        if( LCS[ i - 1 ][ j ] == LCS [ i ][ j ] )
        {
            i--;
        }
        else if( LCS[ i ][ j - 1 ] == LCS[ i ][ j ] )
        {
             j--;
        }
        else if( LCS[ i - 1 ][ j - 1 ] < LCS[ i ][ j ] )
        {
            result[ k ] = s1 -> getSeq()[ i - 1 ];
            i--;
            j--;
            k++;
        }
    }

    for ( int i = 0 ; i < strlen( s1 -> getSeq() ) + 1 ; i++ )
    {
        delete[] LCS[ i ];
    }
    delete[] LCS;

    char* temp = new char[ strlen( result ) ];
    for( int n = strlen( result ) - 1 , m = 0 ; n >= 0 ; n-- , m++  )
    {
        temp[ m ] = result[ n ];
    }
    result = temp;
    delete[] temp;

    return result;
}

char* LocalAlign( Sequence* s1 , Sequence* s2 )
{
    int gap = -7;
    int Mismatch = -5;
    int match = 10;
    int** LCS = new int* [ strlen( s1 -> getSeq() ) + 1 ] ;
    for ( int i = 0 ; i < strlen( s1 -> getSeq() ) + 1 ; i++ )
    {
        LCS[ i ] = new int [ strlen( s2 -> getSeq() ) + 1 ];
    }
    for( int i = 0 ; i < strlen( s1 -> seq ) + 1 ; i++ )
    {
        for( int j = 0 ; j  < strlen( s2 -> seq ) + 1 ; j++ )
        {
             LCS[ i ][ j ] = 0;
        }

    }

    for( int i = 1  ; i <= strlen( s1 -> getSeq() ) ; i++ )
    {
        for( int j = 1  ; j <= strlen( s2 -> getSeq() ) ; j++)
        {
            if( s1 -> getSeq()[ i - 1 ] == s2 -> getSeq()[ j - 1 ] )
            {
                LCS[ i ][ j ] = match + LCS[ i - 1 ][ j - 1 ];
            }
            else
            {
                LCS[ i ][ j ] = max( LCS[ i - 1 ][ j ] + gap , LCS[ i ][ j - 1 ]  + gap );
                int tmp = 0;
                tmp = max( LCS[ i ][ j ] , LCS[ i - 1 ][ j - 1 ] + Mismatch );
                tmp = max( tmp , 0 );
                LCS[ i ][ j ] = tmp;

            }
        }
    }
    int maxVal = 0;
    int iMax = 0;
    int jMax = 0;
     for( int i = 0 ; i < strlen( s1 -> seq ) + 1 ; i++ )
    {
        for( int j = 0 ; j  < strlen( s2 -> seq ) + 1 ; j++ )
        {
            int tmp = 0;
            tmp = max( LCS[ i ][ j ] , maxVal );
            tmp = max( tmp , 0 );
            maxVal = tmp;
        }
    }
    for( int i = 0 ; i < strlen( s1 -> seq ) + 1 ; i++ )
    {
        for( int j = 0 ; j  < strlen( s2 -> seq ) + 1 ; j++ )
        {
          if( LCS[ i ][ j ] == maxVal )
          {
                iMax = i;
                jMax = j;
                break;
          }
        }
    }
    int i = iMax , j = jMax , k = 0 , counter = 0;
    while( LCS[ i ][ j ] != 0 )
    {
        int tmp = 0;
        maxVal = max(LCS[ i - 1 ][ j - 1 ] , LCS[ i - 1 ][ j ]);
        tmp = max(maxVal , LCS[ i ][ j - 1 ] );
        maxVal = tmp;
        if( maxVal == LCS[ i - 1 ][ j - 1 ] )
        {
            counter++;
            i--;
            j--;
        }
        else if( maxVal == LCS [ i - 1 ][ j ] )
        {
            i--;
        }
        else if( maxVal == LCS[ i ][ j - 1] )
        {
            j--;
        }
    }
    char * result = new char[ counter + 1];
    i = iMax , j = jMax , k = 0;
    while( LCS[ i ][ j ] != 0 )
    {
        int tmp = 0;
        maxVal = max(LCS[ i - 1 ][ j - 1 ] , LCS[ i - 1 ][ j ]);
        tmp = max(maxVal , LCS[ i ][ j - 1 ] );
        maxVal = tmp;
        if( maxVal == LCS[ i - 1 ][ j - 1 ] )
        {
            result[ k ] = s1 -> getSeq()[ i - 1 ];
            k++;
            i--;
            j--;
        }
        else if( maxVal == LCS [ i - 1 ][ j ] )
        {
            i--;
        }
        else if( maxVal == LCS[ i ][ j - 1] )
        {
            j--;
        }
    }
    for ( int i = 0 ; i < strlen( s1 -> getSeq() ) + 1 ; i++ )
    {
        delete[] LCS[ i ];
    }
    delete[] LCS;

    char* temp = new char[ strlen( result ) + 1];
    for( int n = strlen( result ) - 1 , m = 0 ; n >= 0 ; n-- , m++  )
    {
        temp[ m ] = result[ n ];
    }
    for(int i = 0 ; i < strlen(temp) ; i++ )
    {
        result[ i ]= temp[ i ];
    }
    result[ strlen(temp) ] = '\0';
    delete[] temp;

    return result;
}
