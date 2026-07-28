// Ghad Saqqa 8049890 - CSCI291 Assignment 2
// Main file that orchestrates document creation, display, similarity, and sorting
// Keeps all original comments intact while using modular class structure

#include <iostream>  // for cout, endl
#include <cstdlib>   // for atoi, srand, rand
#include <ctime>     // for time()
#include "Doc.h"        // Base document class
#include "DecDoc.h"     // Decimal document derived class
#include "HexDoc.h"     // Hexadecimal document derived class
#include "DocumentHandler.h"  // Template class to manage documents

using namespace std; // This means we don’t have to write the standard library names 'std::' every time  we need it(e.g., we can write cout instead of std::cout).


// Main Program Execution
int main(int argc, char* argv[]) {
    srand(time(0)); // Seed random once globally for consistent randomness

    if (argc != 7) {  // Check if the number of command line args is NOT equal to 7 (program name + 6 arguments)
        cout << "Usage: ./main num1 len1 thres num2 len2 pos\n"; // display error
        return 1;
    }

    // definfing what the command line is 
    int num1 = atoi(argv[1]); // Number of DecDocs to create 
    int len1 = atoi(argv[2]); // Length of each DecDoc
    int thres = atoi(argv[3]); // Threshold for similarity
    int num2 = atoi(argv[4]); // Number of HexDocs
    int len2 = atoi(argv[5]); // Length of each HexDoc
    int pos = atoi(argv[6]);  // Position to compare in HexDoc
    // atoi is ASCII to integer converter (string argument to integer) 
    // argv holds command line atguments as strings

    // Check if postion input is valid or not
    if (pos != 1 && pos != 2) {
        cout << "Position must be 1 or 2\n"; // eroor message
        return 1;// exit with error
    }

    // Validate non-negative and logical input values
    if (num1 <= 0 || len1 <= 0 || thres < 0 || num2 <= 0 || len2 <= 0) {
        cout << "Error: All numeric values must be 0 or more, and the threshold must be greater than 0.\n"; // Threshold must be positive because it's used in absolute difference
        return 1;
    }


    // Processing Decimal Documents adn displaying
    DocumentHandler<DecDoc> decHandler; //Create DocumentHandler for DecDoc type
    for (int i = 0; i < num1; ++i)
        decHandler.addDocument(new DecDoc(len1, thres)); // Create DecDoc and add to handler

    cout << "\nDecDoc Objects:\n"; // header for first output - DecDoc
    decHandler.displayAll(); // display all DecDoc objects
    decHandler.maxSimilarity();// display Maximum Similairty of DecDoc

    cout << "\nDecDoc Sorted by Total Value:\n";
    for (auto* doc : decHandler.sortedBySummation()) // Go over all DecDocs and sort by summation
        doc->display();// display DecDoc in order

  
    // Processing Hexadecimal Documents and displaying
 
    
    cout << "\n------------------------------------------------------------\n\n";
    
    // similar to before in DecDoc 
    DocumentHandler<HexDoc> hexHandler; // Create DocumentHandler for HexDoc type
    for (int i = 0; i < num2; ++i)
        hexHandler.addDocument(new HexDoc(len2, pos)); // Obtain the required input form input line and create HexDoc then add to handler
    cout << "HexDoc Objects:\n"; // header for the second output - HexDoc
    hexHandler.displayAll(); //display all HexDoc objects
    hexHandler.maxSimilarity();// display Maximum Similairty of HexDoc

    cout << "\nHexDoc Sorted by Total Value:\n";
    for (auto* doc : hexHandler.sortedBySummation()) // Go over all HexDocs and sort by summation
        doc->display(); // display hexDoc in order
        
    return 0;
}
