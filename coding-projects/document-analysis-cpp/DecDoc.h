// DecDoc.h
// Header file for DecDoc class - derived from Doc

#ifndef DECDOC_H
#define DECDOC_H

#include "Doc.h" // include base class Doc as DecDoc is a derived class from it and we will be referring to Doc.h
#include <string>
using namespace std;

class DecDoc : public Doc { // Create class DecDoc which publicly inherits from Doc, gaining access to Doc's protected and public members
    static int idCounter; // Static ID tracker shared by all DecDoc objects to assign unique IDs by incrementing each time a new object is created; only one copy exists in memory
    int threshold;        // Instance variable storing the similarity threshold specific to each DecDoc object

public: // Constructor: generates random two-digit decimal words using biased sampling
    DecDoc(int len, int thres); // creating constructor which will act as a blueprint to our class tellling the code what inputs will be used for this specific class
    void display() const override; // create a fucntion that will display content, const override is used to specify that a derived class's member function (DecDoc) is overriding a base class's virtual function (Doc)
    int summation() const override; // total sum function --> returns the sum of all 2-digit values in the document
    int similarity(const Doc& other) const override; // similarity comparison between this document's contetent o another and based on threshold
};

int sampleDigit(); // // Helper function declaration --> assists the main function in performing specific tasks ahead

#endif