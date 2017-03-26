#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "Toys.h"

using namespace std;


class HashTable
{
private:
    Toys *object;
    int elementCount;

public:
    HashTable()
    {
        elementCount = 0;
        object = new Toys[BUCKETSIZE];
    }

    ~HashTable()
    {
        delete []object;
    }

    void appendToy(ofstream &outputFile, Toys toysIn);
    void printTable() const;
    void printHash(int index) const;
    void lookupKey(string key) const;

    int getElementCount() const
        { return elementCount; }
};

#endif
