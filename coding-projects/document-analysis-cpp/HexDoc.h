// HexDoc.h
// Header file for HexDoc class - derived from Doc

#ifndef HEXDOC_H // same as before when declaring a header file, use if-function to check if there's already a class with this name
#define HEXDOC_H

#include "Doc.h" // include base class Doc as DecDoc is a derived class from it and we will be referring to Doc.h
#include <string>
using namespace std;

class HexDoc : public Doc { // Create class DecDoc which publicly inherits from Doc, gaining access to Doc's protected and public members
    static int idCounter; // Static ID tracker shared by all HexDoc objects to assign unique IDs by incrementing each time a new object is created; only one copy exists in memory
    int pos;// unlike decimal we will have pos rather than threshold so intiliase character position to compare during similarity check

    // Helper function to convert integer (0-15) to hex character
    static char hexChar(int val);

public:
    HexDoc(int len, int position); // constructor
    void display() const override; // display hex doc
    int summation() const override; // total value
    int similarity(const Doc& other) const override; // character position similarity
    // same in depth explanation of DecDoc
};

int HexToDec(const string& hex); // Helper function: Converts a hexadecimal string (e.g., "A3") to its decimal value

#endif // since we started the header file with ifndef, we need to end it with endif