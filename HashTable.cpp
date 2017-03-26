#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "HashTable.h"

using namespace std;

//*************************
//adds toy into the array while there is room
//*************************
void HashTable::appendToy(ofstream &outputFile, Toys toysIn)
{
    if(elementCount <= BUCKETSIZE-1)
    {
        object[elementCount].setName(toysIn.getName());
        object[elementCount].setAge(toysIn.getAge());
        object[elementCount].setPrice(toysIn.getPrice());
        object[elementCount].setAward(toysIn.getAward());

        elementCount++;
    }
    else
    {
        outputFile << toysIn.getName()  << endl
                   << toysIn.getAge()   << endl
                   << toysIn.getPrice() << endl
                   << toysIn.getAward() << endl << endl;

        cout << "Error! Bucket is full, cannot add " << toysIn.getName() << endl;
    }
}

//*************************
//prints the table without indents
//*************************
void HashTable::printTable() const
{
    for(int i = 0; i < elementCount; i++)
    {
        cout << left
             << setw(55) << object[i].getName()
             << setw(5)  << object[i].getAge()
             << setw(10) << object[i].getPrice()
             << setw(10) << object[i].getAward()
             << endl;
    }
}

//*************************
//prints the hash table with indents and index #
//*************************
void HashTable::printHash(int index) const
{
    cout << "========\n"
         << "Index " << index << endl
         << "========\n";

    cout << "Name : " << object[0].getName()  << endl
         << "Age  : " << object[0].getAge()   << endl
         << "Price: " << object[0].getPrice() << endl
         << "Award: " << object[0].getAward() << endl << endl;


    for(int a = 1; a < elementCount; a++)
    {
        cout << setw(10) << " " << object[a].getName()  << endl
             << setw(10) << " " << object[a].getAge()   << endl
             << setw(10) << " " << object[a].getPrice() << endl
             << setw(10) << " " << object[a].getAward() << endl << endl;
    }
    cout << endl;
}

//*************************
//searches the array for a particular product
//*************************
void HashTable::lookupKey(string key) const
{
    bool found = false;

    int i = 0;

    while(!found && i < elementCount)
    {
        if(object[i].getName() == key)
            found = true;
        else
            i++;
    }

    if(found)
    {
        cout << "Name : " << object[i].getName()  << endl
             << "Age  : " << object[i].getAge()   << endl
             << "Price: " << object[i].getPrice() << endl
             << "Award: " << object[i].getAward() << endl << endl;
    }
    else
        cout << "Item not found" << endl;
}
