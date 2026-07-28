// DecDoc.cpp
// This is the implementation file for the DecDoc class and the helper function sampleDigit()

#include "DecDoc.h" // Include the header file for DecDoc class definition
#include <iostream> 
#include <cstdlib>  // For rand()
#include <cmath>    // For abs()
using namespace std;

int DecDoc::idCounter = 0; 
//Initilaise static ID tracker shared by all DecDoc objects to assign unique IDs by incrementing each time a new object is created; only one copy exists in memory

// Helper Function: sampleDigit()
// this will generate a single digit (0–9) based on the given probability distribution in specification as each number has a different probability of being selcected:
// [0:5%, 1:10%, 2:15%, 3:20%, 4:10%, 5:10%, 6:10%, 7:5%, 8:10%, 9:5%]

int sampleDigit() { // function declared in DecDoc.h 
    double r = (double)rand() / RAND_MAX; // Generate a random decimal number between 0 and RAND_MAX however dividng the output by RAND_MAX will result in a decimal number 'r' that is between 0 and 1

    // Return digit according to cumulative probability thresholds
    if (r < 0.05)         return 0;  // 5% chance
    else if (r < 0.15)    return 1;  // 10% (0.05 to 0.15)
    else if (r < 0.30)    return 2;  // 15% (0.15 to 0.30)
    else if (r < 0.50)    return 3;  // 20% (0.30 to 0.50)
    else if (r < 0.60)    return 4;  // 10% (0.50 to 0.60)
    else if (r < 0.70)    return 5;  // 10% (0.60 to 0.70)
    else if (r < 0.80)    return 6;  // 10% (0.70 to 0.80)
    else if (r < 0.85)    return 7;  // 5%  (0.80 to 0.85)
    else if (r < 0.95)    return 8;  // 10% (0.85 to 0.95)
    else                  return 9;  // 5%  (0.95 to 1.00)
}

// Constructor: DecDoc(int len, int thres)
// Generates a document made of 'len' input that is 2-digit numbers, where each digit is generated using sampleDigit() based on biased probability (established above)
//'thres' is the similarity threshold used for comparison later

DecDoc::DecDoc(int len, int thres) : threshold(thres) { // Creating constructor DecDoc from class DecDoc
    id = ++idCounter; // assign unique ID to this document, ++ used to increment eveytime a new value has passed thus ensuring each value has a unique id 

    for (int i = 0; i < len; ++i) { // Create a 2-digit word by combining two sampled digits 
        string word = to_string(sampleDigit()) + to_string(sampleDigit()); // // randomly select two digits based on probability distribution and combine as string (based on sampleDigit)
        content.push_back(word); // this will add the new two digiti string word to the content of vector. push.back adds/pushes the new element to the end of the vecotr and thus growing the vector
    }
}

// display() function 
// Displaying/printing the document ID and its content
// surround the output with **** 
// 
void DecDoc::display() const { // Displaying fucntion for the DecDoc class to print its ids and contents
    cout << "DecDoc " << id << ": **** "; // example output --> DecDoc 1: **** 23 23 61 54 52 37 ****
    for (const auto& w : content) // Loop through each word in content
        cout << " " << w << " ";// print space then word and follow it by a second space
    cout << "****\n"; // close **** frame and start a new line for next DecDoc id
}

// summation()
// This will add up all 2-digit decimal values that were previuoly stored in the content vector
// Converts each string to integer using stoi() --> stirng to integer
int DecDoc::summation() const { //Summation fucntion for DecDoc class
    int sum = 0; // initilaise  sum = 0
    for (const auto& w : content) 
        sum += stoi(w); // convert the string of respective loop to integer and add
    return sum; // return the total sum 
}

// similarity()
// Compares this document to another DecDoc and counts how many values differ by less than or equal to input 'threshold'
// For each pair (this.value, other.value), if abs difference <= threshold, count it
int DecDoc::similarity(const Doc& other) const {
    const DecDoc& d = static_cast<const DecDoc&>(other); // going from base calss Dec to derived class DecDoc 
    int sim = 0; // similarity counter
    for (const auto& w1 : content) {  // Loop through each 2-digit word in this DecDoc's content
        for (const auto& w2 : d.content) {  // Loop through each 2-digit word in the other DecDoc's content
            if (abs(stoi(w1) - stoi(w2)) <= threshold) // Convert both strings to int, compare if absolute difference is within  the input threshold
                ++sim; // if within threshold, count it as similar and increment
        }
    }
    return sim; // Return total similarity count
}
