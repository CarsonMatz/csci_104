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
        //size of the string
        unsigned int size = k.size();
        //w and a arrays initialized to 0
        unsigned long long w[5] = {0};
        HASH_INDEX_T a[6] = {0};
        //index of the string to work on
        int index = size - 1;
        //number of full groups of 6 letters
        unsigned int groups = size/6;
        //number of extra chars that don't fill a full group of 6
        unsigned int extras = size%6;
        //the sport in the w array
        unsigned int wSpot = 4;
        //while there are full groups of 6 still
        while(groups > 0){

            for(unsigned int i=0; i<6; i++){
                char c = tolower(k[index]);
                std::cout << c << " ";
                index--;
                a[i] = letterDigitToNumber(c);
                std::cout << a[i] << std::endl;
            }
            w[wSpot] = ((((((a[5]) *36+a[4]) *36+a[3]) *36+a[2]) *36+a[1]) *36+a[0]);
            wSpot--;
            groups--;
            /* for(int i=0; i<6; i++){
                std::cout << a[i] << std::endl;
            } */
        }
        std::cout << std::endl;
        if(extras > 0){
            for(unsigned int i=0; i<6-extras; i++){
                a[i] = 0;
            }
            //unsigned int startExtras = k.size()-extras;
            for(unsigned int i=5; i>=(6-extras); i--){
                char c = tolower(k[index]);
                std::cout << c << " ";
                index--;
                a[i] = letterDigitToNumber(c);
                std::cout << a[i] << std::endl;
            }
            w[wSpot] = ((((((a[0]) *36+a[1]) *36+a[2]) *36+a[3]) *36+a[4]) *36+a[5]);
        }
        for(int i=0; i<5; i++){
            std::cout << w[i] << std::endl;
        }
        //the values I got for the w[] array are going to be out of place
        //I start at w[0] and move through to w[4] but if the string is too short I need vals in w[4] not w[0]
        return (rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4]);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        //return value based on ASCII of letter
        HASH_INDEX_T val = 0;
        //if it's a number
        if(letter >= '0' && letter <= '9'){
            val = letter - 22;
        }
        //or a lowercase
        else if(islower(letter)){
            val = letter - 97;
        }

        return val;
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
