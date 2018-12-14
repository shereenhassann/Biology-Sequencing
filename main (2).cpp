//Assignment four v1.0
//Dr. mohamed nasif
//sequencing for biologists
//Date: 3-12-2018
//Authors: Shereen Hassan      20170130
//         Salma Essam         20170115
//Version: 1.2

#include <iostream>
#include <cstring>
#include <string>
#include "Sequence.h"
#include "DNA.h"
#include "RNA.h"
#include "Protein.h"
#include "CodonsTable.h"

using namespace std;

int main()
{
    cout << "Ahlan ya user ya habibi.\n\n";
    cout << "\nWelcome to Biologists Sequencing Program.\n\n";
    char chooseSeqType;
    while( true )
    {
        cout << "\n-------------------------------------------------------\n\n";
        cout << "Please enter the type of sequence you want to use :\n\n1.DNA.\n2.RNA.\n3.Protein.\n4.End\n\n>> ";
        cin >> chooseSeqType;
        cout << endl;
        switch( chooseSeqType )
        {
            case '1':
                {

                    char DNAChoices;

                    bool DNAChoicesValid = false;
                    do{
                        cout << "Please choose the operation :\n\n1.Input DNA.\n2.Align 2 DNA sequences.\n";
                        cout << "3.Align 2 DNA sequences using Local LCS.\n4.Add 2 DNA sequences.\n";
                        cout << "5.Check if the 2 DNAs are equal.\n6.check of the 2 DNAs are not equal.\n7.Load from file.\n\n>> ";
                        cin >> DNAChoices;
                        cout << endl;
                        DNAChoicesValid = false;
                        switch( DNAChoices )
                        {
                        case '1':
                            {
                                DNA dna;
                                char DNAInput;
                                bool DNAInputValid = false;
                                cin >> dna;
                                cout << endl;
                                do
                                {
                                    DNAInputValid = false;
                                    cout << "Please choose what do you want to do next :\n\n1.Convert DNA to RNA.\n2.Convert DNA to Protein.\n";
                                    cout << "3.Print the complementary strand.\n4.Print DNA.\n5.Save DNA to a file.\n\n>> ";
                                    cin >> DNAInput;
                                    cout << endl;
                                    switch( DNAInput )
                                    {
                                    case '1':
                                        {
                                            RNA rna;
                                            rna = dna.ConvertToRNA();
                                            cout << rna;
                                            cout << endl;
                                            break;
                                        }
                                    case '2':
                                        {
                                            Protein protein;
                                            protein = dna.ConvertToRNA().ConvertToProtein();
                                            cout << protein;
                                            cout << endl;

                                            break;
                                        }
                                    case '3':
                                        {
                                            dna.BuildComplementaryStrand();
                                            cout << "The complementary strand is : " << (*dna.getCompStrand()).getSeq() << endl;
                                            break;
                                        }
                                    case '4':
                                        {
                                            dna.Print();
                                            cout << endl;
                                            break;
                                        }
                                    case '5':
                                        {
                                            string file;
                                            cout << "Please enter the name of the file file you want to save to :\n>> ";
                                            cin >> file;

                                            dna.SaveSequenceToFile( file );
                                            break;
                                        }
                                    default:
                                        {
                                            DNAInputValid = true;
                                            cout << "Invalid input.Please enter a valid input.\n\n";
                                            break;
                                        }

                                    }

                                }while(DNAInputValid);

                                break;
                            }
                        case '2':
                            {
                                Sequence * sequence1 = new DNA;
                                Sequence * sequence2 = new DNA;
                                DNA dna1;
                                DNA dna2;
                                cout << "Enter the 1st DNA :\n\n";
                                cin >> dna1;
                                cout << endl;
                                cout << "Enter the 2nd DNA :\n\n";
                                cin >> dna2;
                                cout << endl;
                                sequence1 = &dna1;
                                sequence2 = &dna2;
                                cout << "The result is : ";
                                cout << Align( sequence1 , sequence2 ) << endl;
                                delete sequence1;
                                delete sequence2;

                                break;
                            }
                        case '3':
                            {
                                Sequence * sequence1 = new DNA;
                                Sequence * sequence2 = new DNA;
                                DNA dna1;
                                DNA dna2;
                                cout << "Enter the 1st DNA :\n\n";
                                cin >> dna1;
                                cout << endl;
                                cout << "Enter the 2nd DNA :\n\n";
                                cin >> dna2;
                                cout << endl;
                                sequence1 = &dna1;
                                sequence2 = &dna2;
                                cout << "The result is : ";
                                cout << LocalAlign( sequence1 , sequence2 ) << endl;
                                delete sequence1;
                                delete sequence2;

                                break;
                            }
                        case '4':
                            {
                                DNA dna1;
                                DNA dna2;
                                DNA result;
                                cout << "Enter the 1st DNA :\n\n";
                                cin >> dna1;
                                cout << "Enter the 2nd DNA :\n\n";
                                cin >> dna2;
                                result = dna1 + dna2;
                                cout << result;
                                cout << endl;

                                break;
                            }
                        case '5':
                            {
                                DNA dna1;
                                DNA dna2;
                                cout << "Enter the 1st DNA :\n\n";
                                cin >> dna1;
                                cout << "Enter the 2nd DNA :\n\n";
                                cin >> dna2;
                                if( dna1 == dna2 )
                                {
                                    cout << "The 2 DNAs are equal.\n\n";
                                }
                                else
                                {
                                    cout << "The 2 DNAs are not equal.\n\n";
                                }

                                break;
                            }
                        case '6':
                            {
                                DNA dna1;
                                DNA dna2;
                                cout << "Enter the 1st DNA :\n\n";
                                cin >> dna1;
                                cout << "Enter the 2nd DNA :\n\n";
                                cin >> dna2;
                                if( dna1 != dna2 )
                                {
                                    cout << "The 2 DNAs are not equal.\n\n";
                                }
                                else
                                {
                                    cout << "The 2 DNAs are equal.\n\n";
                                }

                                break;
                            }
                        case '7':
                            {
                                DNA dna;
                                string file;
                                cout << "Please enter the name of the file you want to load from :\n>> ";
                                cin >> file;

                                dna.LoadSequenceFromFile( file );

                                break;
                            }
                        default:
                            {
                                DNAChoicesValid = true;
                                cout << "Invalid input.Please enter a valid input.\n\n";
                                break;
                            }
                        }
                    }while(DNAChoicesValid);

                    break;
                }

            case '2':
                {
                    char RNAChoices;

                    bool RNAChoicesValid = false;
                    do{
                        cout << "Please choose the operation :\n\n1.Input RNA.\n2.Align 2 RNA sequences.\n";
                        cout << "3.Align 2 RNA sequences using Local LCS.\n4.Add 2 RNA sequences.\n";
                        cout << "5.Check if the 2 RNAs are equal.\n6.check of the 2 RNAs are not equal.\n7.Load from file.\n\n>> ";
                        cin >> RNAChoices;
                        cout << endl;
                        RNAChoicesValid = false;
                        switch( RNAChoices )
                        {
                        case '1':
                            {
                                RNA rna;
                                char RNAInput;
                                bool RNAInputValid = false;
                                cin >> rna;
                                cout << endl;
                                do
                                {
                                    RNAInputValid = false;
                                    cout << "Please choose what do you want to do next :\n\n1.Convert RNA to DNA.\n2.Convert RNA to Protein.\n";
                                    cout << "3.Print RNA.\n4.Save RNA to a file.\n\n>> ";
                                    cin >> RNAInput;
                                    cout << endl;
                                    switch( RNAInput )
                                    {
                                    case '1':
                                        {
                                            DNA dna;
                                            dna = rna.ConvertToDNA();
                                            cout << dna;
                                            cout << endl;
                                            break;
                                        }
                                    case '2':
                                        {
                                            Protein protein;
                                            protein = rna.ConvertToProtein();
                                            cout << protein;
                                            cout << endl;

                                            break;
                                        }
                                    case '3':
                                        {
                                            rna.Print();
                                            cout << endl;
                                            break;
                                        }
                                    case '4':
                                        {
                                            string file;
                                            cout << "Please enter the name of the file file you want to save to :\n>> ";
                                            cin >> file;

                                            rna.SaveSequenceToFile( file );
                                            break;
                                        }
                                    default:
                                        {
                                            RNAInputValid = true;
                                            cout << "Invalid input.Please enter a valid input.\n\n";
                                            break;
                                        }

                                    }

                                }while(RNAInputValid);

                                break;
                            }
                        case '2':
                            {
                                Sequence * sequenceR1 = new RNA;
                                Sequence * sequenceR2 = new RNA;
                                RNA rna1;
                                RNA rna2;
                                cout << "Enter the 1st RNA :\n\n";
                                cin >> rna1;
                                cout << endl;
                                cout << "Enter the 2nd RNA :\n\n";
                                cin >> rna2;
                                cout << endl;
                                sequenceR1 = &rna1;
                                sequenceR2 = &rna2;
                                cout << "The result is : ";
                                cout << LocalAlign( sequenceR1 , sequenceR2 ) << endl;
                                delete sequenceR1;
                                delete sequenceR2;

                                break;
                            }
                        case '3':
                            {
                                Sequence * sequenceRNA1 = new RNA;
                                Sequence * sequenceRNA2 = new RNA;
                                RNA rnaAdd1;
                                RNA rnaAdd2;
                                cout << "Enter the 1st RNA :\n\n";
                                cin >> rnaAdd1;
                                cout << endl;
                                cout << "Enter the 2nd RNA :\n\n";
                                cin >> rnaAdd2;
                                cout << endl;
                                sequenceRNA1 = &rnaAdd1;
                                sequenceRNA2 = &rnaAdd2;
                                cout << "The result is : ";
                                cout << LocalAlign( sequenceRNA1 , sequenceRNA2 ) << endl;
                                delete sequenceRNA1;
                                delete sequenceRNA2;


                                break;
                            }
                        case '4':
                            {
                                RNA rna1 ;
                                RNA rna2 ;
                                RNA result;
                                cout << "Enter the 1st RNA :\n\n";
                                cin >> rna1;
                                cout << "Enter the 2nd RNA :\n\n";
                                cin >> rna2;
                                result = rna1 + rna2;
                                cout << result;
                                cout << endl;

                                break;
                            }
                        case '5':
                            {
                                RNA rna1;
                                RNA rna2;
                                cout << "Enter the 1st RNA :\n\n";
                                cin >> rna1;
                                cout << "Enter the 2nd RNA :\n\n";
                                cin >> rna2;
                                if( rna1 == rna2 )
                                {
                                    cout << "The 2 RNAs are equal.\n\n";
                                }
                                else
                                {
                                    cout << "The 2 RNAs are not equal.\n\n";
                                }

                                break;
                            }
                        case '6':
                            {
                                RNA rna1;
                                RNA rna2;
                                cout << "Enter the 1st RNA :\n\n";
                                cin >> rna1;
                                cout << "Enter the 2nd RNA :\n\n";
                                cin >> rna2;
                                if( rna1 != rna2 )
                                {
                                    cout << "The 2 RNAs are not equal.\n\n";
                                }
                                else
                                {
                                    cout << "The 2 RNAs are equal.\n\n";
                                }

                                break;
                            }
                        case '7':
                            {
                                RNA rna;
                                string file;
                                cout << "Please enter the name of the file you want to load from :\n>> ";
                                cin >> file;

                                rna.LoadSequenceFromFile( file );

                                break;
                            }
                        default:
                            {
                                RNAChoicesValid = true;
                                cout << "Invalid input.Please enter a valid input.\n\n";
                                break;
                            }
                        }
                    }while(RNAChoicesValid);

                    break;
                }
            case '3':
                {
                    char ProteinChoices;

                    bool ProteinChoicesValid = false;
                    do{
                        cout << "Please choose the operation :\n\n1.Input Protein.\n2.Align 2 Protein sequences.\n";
                        cout << "3.Align 2 Protein sequences using Local LCS.\n4.Add 2 Protein sequences.\n";
                        cout << "5.Check if the 2 Proteins are equal.\n6.check of the 2 Proteins are not equal.\n7.Load from file.\n\n>> ";
                        cin >> ProteinChoices;
                        cout << endl;
                        ProteinChoicesValid = false;
                        switch( ProteinChoices )
                        {
                        case '1':
                            {
                                Protein pr;
                                char ProteinInput;
                                bool ProteinInputValid = false;
                                cin >> pr;
                                cout << endl;
                                do
                                {
                                    ProteinInputValid = false;
                                    cout << "Please choose what do you want to do next :\n\n1.Get the DNA that give this Protein.\n2.Print Protein.\n";
                                    cout << "3.Save Protein to a file.\n\n>> ";
                                    cin >> ProteinInput;
                                    cout << endl;
                                    switch( ProteinInput )
                                    {
                                    case '1':
                                        {
                                            DNA big;
                                            DNAArr DNAArray;
                                            DNA* dnaArray;
                                            cout << "Please enter the big DNA : \n>> ";
                                            cin >> big;
                                            DNAArray = pr.GetDNAStrandsEncodingMe( big );
                                            int sz = DNAArray.sz;
                                            dnaArray = DNAArray.dna;
                                            for ( int i = 0; i < sz; i++ )
                                            {
                                                dnaArray[ i ].Print();
                                            }
                                            break;
                                        }


                                    case '2':
                                        {
                                            pr.Print();
                                            cout << endl;
                                            break;
                                        }
                                    case '3':
                                        {
                                            string file;
                                            cout << "Please enter the name of the file file you want to save to :\n>> ";
                                            cin >> file;

                                            pr.SaveSequenceToFile( file );
                                            break;
                                        }
                                    default:
                                        {
                                            ProteinInputValid = true;
                                            cout << "Invalid input.Please enter a valid input.\n\n";
                                            break;
                                        }

                                    }

                                }while(ProteinInputValid);

                                break;
                            }
                        case '2':
                            {
                                Sequence * sequence1 = new Protein;
                                Sequence * sequence2 = new Protein;
                                Protein p1;
                                Protein p2;
                                cout << "Enter the 1st DNA :\n\n";
                                cin >> p1;
                                cout << endl;
                                cout << "Enter the 2nd DNA :\n\n";
                                cin >> p2;
                                cout << endl;
                                sequence1 = &p1;
                                sequence2 = &p2;
                                cout << "The result is : ";
                                cout << Align( sequence1 , sequence2 ) << endl;
                                delete sequence1;
                                delete sequence2;

                                break;
                            }
                        case '3':
                            {
                                Sequence * sequenceP1 = new Protein;
                                Sequence * sequenceP2 = new Protein;
                                Protein pr1;
                                Protein pr2;
                                cout << "Enter the 1st Protein :\n\n";
                                cin >> pr1;
                                cout << endl;
                                cout << "Enter the 2nd Protein :\n\n";
                                cin >> pr2;
                                cout << endl;
                                sequenceP1 = &pr1;
                                sequenceP2 = &pr2;
                                cout << "The result is : ";
                                cout << LocalAlign( sequenceP1 , sequenceP2 ) << endl;
                                delete sequenceP1;
                                delete sequenceP2;

                                break;
                            }
                        case '4':
                            {
                                Protein pr1;
                                Protein pr2;
                                Protein result;
                                cout << "Enter the 1st Protein :\n\n";
                                cin >> pr1;
                                cout << "Enter the 2nd Protein :\n\n";
                                cin >> pr2;
                                result = pr1 + pr2;
                                cout << result;
                                cout << endl;

                                break;
                            }
                        case '5':
                            {
                                Protein pr1;
                                Protein pr2;
                                cout << "Enter the 1st Protein :\n\n";
                                cin >> pr1;
                                cout << "Enter the 2nd Protein :\n\n";
                                cin >> pr2;
                                if( pr1 == pr2 )
                                {
                                    cout << "The 2 Proteins are equal.\n\n";
                                }
                                else
                                {
                                    cout << "The 2 Proteins are not equal.\n\n";
                                }

                                break;
                            }
                        case '6':
                            {
                                Protein pr1;
                                Protein pr2;
                                cout << "Enter the 1st Protein :\n\n";
                                cin >> pr1;
                                cout << "Enter the 2nd Protein :\n\n";
                                cin >> pr2;
                                if( pr1 != pr2 )
                                {
                                    cout << "The 2 Proteins are not equal.\n\n";
                                }
                                else
                                {
                                    cout << "The 2 Proteins are equal.\n\n";
                                }

                                break;
                            }
                        case '7':
                            {
                                Protein pr;
                                string file;
                                cout << "Please enter the name of the file you want to load from :\n>> ";
                                cin >> file;

                                pr.LoadSequenceFromFile( file );

                                break;
                            }
                        default:
                            {
                                ProteinChoicesValid = true;
                                cout << "Invalid input.Please enter a valid input.\n\n";
                                break;
                            }
                        }
                    }while(ProteinChoicesValid);


                break;
                }
            case '4':
                {
                    cout << "\nThank you for using this program.\n\n";
                    return 0;
                }
            default:
                {
                    cout << "Invalid input.Please enter a valid input.\n\n";
                    break;
                }
        }
    }
    return 0;

}
