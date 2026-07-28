// HexDoc.cpp
// Implementation file for HexDoc class and hex conversion function

#include "HexDoc.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int HexDoc::idCounter = 0; // Initialise static counter

// Cpp inherently deals with decimal numbers therefore we would have to convert any hex number into decimal to further deal with
int HexToDec(const string& hex) { // const string --> input is a string (const to read only and not modify/protect the input) &hex is a reference to HexToDec --> basically another name to access this function
    return stoi(hex,nullptr, 16); // string to integer converter --> convert hex string to a integer of base 16 (hex to decimal)
}

// Helper to convert int 0-15 to hex char
char HexDoc::hexChar(int val) {
    return val < 10 ? '0' + val : 'A' + (val - 10); // hexChar()
    // Converts an integer value (0–15) to its corresponding hexadecimal character, specifically for 0–9 returns '0'–'9'; for 10–15 returns 'A'–'F'
}

// Constructor: creates len hex words (e.g., A3, 1F) with uniform sampling
// Constructor: HexDoc(int len, int position), create len hex words with uniform generating/sampling
// Each character is randomly sampled from 0–15 (i.e., hex digit 0–F) similar to 'threshold' in DecDoc the 'position' determines which character will be used for similarity comparison
HexDoc::HexDoc(int len, int position) : pos(position) {
    id = ++idCounter; // Assign a unique ID to this HexDoc
    for (int i = 0; i < len; ++i) {
        char c1 = hexChar(rand() % 16); //// Random first hex digit
        char c2 = hexChar(rand() % 16); //Random second hex digit
        content.push_back(string{c1, c2}); // Combine and store as string in content
    }
}

// Displays content framed with ^^^^
void HexDoc::display() const {
    cout << "HexDoc " << id << ": ^^^^ ";
    for (const auto& w : content)
        cout << " " << w << " ";
    cout << "^^^^\n";
}

// Sums up hexadecimal values converted to decimal
int HexDoc::summation() const {
    int sum = 0;
    for (const auto& w : content)
        sum += HexToDec(w); // convert and add
    return sum;
}

// Similarity: compares pos-th character in each word
int HexDoc::similarity(const Doc& other) const { 
    const HexDoc& h = static_cast<const HexDoc&>(other); //going from base calss Dec to derived class DecDoc 
    int sim = 0;
    for (const auto& w1 : content) {
        for (const auto& w2 : h.content) {
            if (w1[pos - 1] == w2[pos - 1]) // / Compare character at specified position
                ++sim;
        }// not much comments as similar to DecDoc
    }
    return sim; // Return total similarity count
}
