//First header file, for Doc class
#ifndef DOC_H // when declaring a header file, use if-function to check if there's already a class with this name
#define DOC_H

#include <vector>
#include <string>
// without these (libraries) functions wont be recognised by C++

using namespace std; // This means we don’t have to prefix standard library names with 'std::' every time (e.g., we can write cout instead of std::cout).

class Doc { // creating first class called Doc. This class is what both DeDoc and HexDoc will inherit from , meaning they will be based on this common class/interface.
    // Three parts in classes: public, private and protected.
    
    public: // Members can be accessed by code from anywhere --> no need to protect
    // Virtual functions let derived classes provide their own implementation.
    // "=0 " to keep empty and thus we have to provide info in inherent classes
        virtual void display() const = 0; // // display the document content with formatting (to be defined in derived classes)
        virtual int summation() const = 0; // sums the document's numerical values in decimal 
        virtual int similarity(const Doc& other) const = 0; // // Compares this document with another and returns a similarity score
        virtual ~Doc() {} // ~ before class name means its a DESTRUCTOR and is used to basically destory/delete derived objects to ensure proper cleanup for memory for future use and thus preventing memory leaks
    
    protected: // Members in protected can be can be directly accessed by objects of inherited/derived classes only (DecDoc and HexDoc), but not by arbitrary external objects.
        int id; // calling Unique document ID type integer
        vector<string> content; // Rather than array create a vector that will store strings. This will all to add/remove elemetns anytime and it will gorw/shrink autmatically accoring to input line and thus saving memory   
    // This allows DecDoc and HexDoc to access id and content, but protects them from unrelated code.
    };

    #endif // since we started the header file with ifndef, we need to end it with endif