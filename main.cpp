// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by

//Developer: Eric Du
//IDE: codeblocks

#include "HashTable.h"  // BST ADT
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
using namespace std;

void displayMenu();
void openFile  (ifstream &inputFile, ofstream &outputFile);
void closeFile (ifstream &inputFile, ofstream &outputFile);
void readData  (ifstream &inputFile, ofstream &outputFile, HashTable *hashPtr);
void searchKey (HashTable *hashPtr);
void showStats(HashTable *hashPtr);
void displayTable(HashTable *hashPtr);
void displayHash(HashTable *hashPtr);
int hash (string key);
void displayRejected();

int main()
{
    ifstream inputFile;
    ofstream outputFile;

    openFile(inputFile, outputFile);

    HashTable *hashPtr = new HashTable[TABLESIZE];

    readData(inputFile, outputFile, hashPtr);

    displayMenu();

    char userOption = 'O';
    while(toupper(userOption) != 'Q')
    {
        cout << "\nEnter Choice: ";
        cin  >> userOption;

        cin.clear();
        cin.ignore(1000, '\n');

        switch(toupper(userOption))
        {
            case 'S':searchKey(hashPtr);
                     break;

            case 'D':displayTable(hashPtr);
                     break;

            case 'P':displayHash(hashPtr);
                     break;

            case 'T':showStats(hashPtr);
                     break;

            case 'M':displayMenu();
                     break;
        }
    }

    displayRejected();

    delete []hashPtr;
    closeFile(inputFile, outputFile);
    return 0;
}

//*********************************
//opens file to read in data
//*********************************
void openFile(ifstream &inputFile, ofstream &outputFile)
{
    inputFile.open("toys.txt");

    if(!inputFile)
    {
        cout << "\ncannot obtain input file\n";
        exit(EXIT_FAILURE);
    }

    outputFile.open("rejected.txt");

    if(!outputFile)
    {
        cout << "\ncannot obtain first output file\n";
        exit(EXIT_FAILURE);
    }
}

//*********************************
//closes file when it is done with program
//*********************************
void closeFile(ifstream &inputFile, ofstream &outputFile)
{
    inputFile.close();
    outputFile.close();
}

//*********************************
//displays the menu for user to select from
//*********************************
void displayMenu()
{
    cout << "================================================\n"
         << "Please select an option using letter shortcuts.\n\n"
         << "S-Search unique key\n"
         << "D-Display List.\n"
         << "P-Print Hashed Table\n"
         << "T-Show Statistics.\n"
         << "M-Show Menu\n"
         << "Q-Quit Program.\n"
         << "================================================\n";
}

//*************************
//reads in the data from text file and stores in hash table
//*************************
void readData  (ifstream &inputFile, ofstream &outputFile, HashTable *hashPtr)
{
    string name;
    int age;
    double price;
    string award;

    while(getline(inputFile, name, ';'))
    {
        inputFile >> age;
        inputFile >> price;
        inputFile >> award;

        inputFile.ignore();

        Toys tempToy(name, age, price, award);

        hashPtr[hash(name)].appendToy(outputFile, tempToy);
    }
}

//*************************
//hash function to store in particular index
//*************************
int hash(string key)
{
    int charSum  = 0;

    for(int i = 0; i < KEYSIZE; i++)
        //charSum += toupper(key[i]);
        //charSum += tolower(key[i]);
        charSum += key[i];

    return charSum%TABLESIZE;
}

//*************************
//displays the content of the table
//*************************
void displayTable(HashTable *hashPtr)
{
    cout << "\n****************************************************************************\n"
         << "Name                                                  Age   Price     Award"
         << "\n****************************************************************************\n";
    for(int i = 0; i < TABLESIZE; i++)
        hashPtr[i].printTable();
}

void displayHash(HashTable *hashPtr)
{
    for(int i  = 0; i < TABLESIZE; i++)
        hashPtr[i].printHash(i);
}

//*************************
//prompts the user to search for a particular key
//*************************
void searchKey (HashTable *hashPtr)
{
    string lookupToy;
    cout << "Enter exact name of toy you wish to find information about (cap sensitive): ";
    getline(cin, lookupToy);

    hashPtr[hash(lookupToy)].lookupKey(lookupToy);
}

//*************************
//calculates the statistics
//*************************
void showStats(HashTable *hashPtr)
{
    int
    fullBuckets     = 0,
    emptyBuckets    = 0,
    nonEmptyBuckets = 0,
    totalIn1or2     = 0;

    double
    loadFactor, avgin1or2;

    for(int i = 0; i < TABLESIZE; i++)
    {
        if(hashPtr[i].getElementCount())
        {
            nonEmptyBuckets++;

            if(hashPtr[i].getElementCount() > 1)
            {
                totalIn1or2 += (hashPtr[i].getElementCount()-1);

                if(hashPtr[i].getElementCount() == BUCKETSIZE)
                    fullBuckets++;
            }
        }
        else
            emptyBuckets++;
    }

    loadFactor = (static_cast<double>(nonEmptyBuckets)/TABLESIZE) * 100;
    avgin1or2  =  static_cast<double>(totalIn1or2)/nonEmptyBuckets;

    cout << "Number of Collisions   : " << totalIn1or2  << endl
         << "Number of Full Buckets : " << fullBuckets  << endl
         << "Number of Empty Buckets: " << emptyBuckets << endl
         << "Load Factor            : " << loadFactor   << "%" << endl
         << "Avg # in Buckets 1 & 2 : " << avgin1or2    << endl;
}

//*************************
//displays the content of the rejected items
//*************************
void displayRejected()
{
    ifstream inputRejected;
    string name;
    string age;
    string price;
    string award;

    inputRejected.open("rejected.txt");

    if(!inputRejected)
        cout << "cannot contain rejected file";

    cout << "*****************\n"
         << "Rejected Items\n"
         << "*****************\n";

    while(getline(inputRejected, name))
    {
        cout << "Name : " << name  << endl;

        getline(inputRejected, age);
        cout << "Age  : " << age   << endl;

        getline(inputRejected, price);
        cout << "Price: " << price << endl;

        getline(inputRejected, award);
        cout << "Award: " << award << endl << endl;

        inputRejected.ignore();
    }

    inputRejected.close();
}
