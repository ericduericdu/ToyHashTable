#ifndef TOYS_H
#define TOYS_H

#include <string>

using namespace std;

const int BUCKETSIZE = 3;
const int KEYSIZE    = 6;
const int TABLESIZE  = 10;

class Toys
{
private:
    string toyName;
    int toyAge;
    double toyPrice;
    string toyAward;

public:
    Toys()
    {
        toyName = "Eric";
        toyAge = 100;
        toyPrice = 99.99;
        toyAward = "Cash Money";
    }

    Toys(string name, int age, double price, string award)
    {
        toyName = name;
        toyAge = age;
        toyPrice = price;
        toyAward = award;
    }

    void setName(string name)
        {toyName = name;}
    void setAge(int age)
        {toyAge = age;}
    void setPrice(double price)
        {toyPrice = price;}
    void setAward(string award)
        {toyAward = award;}

    string getName() const
        {return toyName;}
    int getAge() const
        {return toyAge;}
    double getPrice() const
        {return toyPrice;}
    string getAward() const
        {return toyAward;}
};

#endif
