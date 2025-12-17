#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath> 
#include <random> 
#include <chrono>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        // process from the back of string in groups of 6
        int idx= 4;
        int last = (int)k.size();
        while(last > 0 && idx>=0){
            int start = last -6;

            if(start < 0) start =0;
            unsigned long long value =0; // base-36 value
            int i = start;
            while (i < last){
                value = value *36ULL;
                value = value + (unsigned long long)letterDigitToNumber(k[i]);
                i= i+1;

            }
            w[idx]= value;
            last = start;
            idx= idx -1;
        }
        // combine rValues and w[i]
        unsigned long long hashValue =0;
        for(int i =0; i <5; i++){
            hashValue = hashValue + (unsigned long long)rValues[i] * (unsigned long long)w[i];
        }
        return (HASH_INDEX_T)hashValue;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        if(letter >= 'A' && letter <= 'Z'){ 
            letter = letter - 'A' + 'a'; // convert to lowercase
        }
        if (letter >= 'a' && letter <= 'z'){ // a = 0, z= 25
            HASH_INDEX_T value;
            value = (HASH_INDEX_T)(letter - 'a'); 
            return value;

        }
        else if (letter >= '0' && letter <= '9'){ // 0 = 26, 9= 35
            HASH_INDEX_T value;
            value = 26 + (HASH_INDEX_T)(letter - '0'); // 26 for '0'
            return value;
        }
        else {
            return 0;
        }


    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
