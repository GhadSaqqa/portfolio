// DocumentHandler.h
// Handles a collection of Doc-derived objects (like DecDoc or HexDoc)

#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template <typename T> //Template class for handling any Doc-like type (T = DecDoc, HexDoc, etc.)
class DocumentHandler { // create class called DocumentHandler which will manage the lists of documents
    vector<T*> docs; // Create vector T which will store pointers to T-type documents (DecDoc*, HexDoc*, etc.)

public:
    ~DocumentHandler() { // destructor to delete all stored documents to free memory
        for (auto doc : docs) delete doc; // delete each pointer 
    }

    // Add a new document to the list
    void addDocument(T* doc) {
        docs.push_back(doc); // add to the lsit --> push back used to increment and add
    }

    // Print all documents by calling their display() function
    void displayAll() const {
        for (const auto& doc : docs) // for loop through the docs
            doc->display(); // display () --> print each one 
    }

    // Check all then find and return the highest similarity score
    int maxSimilarity() const {
        cout << endl; // Add a blank line before the result
        // this will check all possible paris of document and thus finding which pair is most similar and what is the maximim similairty 
        int max = 0, docA = -1, docB = -1; // set max = 0 and for docA/B set = -1 as -1 represetns 'not found yet'
        for (size_t i = 0; i < docs.size(); ++i) { // for the frist document: start from 0, and the loop will compare each unique pair once
            for (size_t j = i + 1; j < docs.size(); ++j) { // nested loop and j os i+1 to avoird comparing the same document with itself
                int sim = docs[i]->similarity(*docs[j]); //since docs[i] and docs[j] are initially pointers, *docs[j] will derefecne the pointer so that the function gets a reference
                if (sim > max) { // if loop: if the pair has a higher similarity than before do the following:
                    max = sim;// save the new max to sim
                    docA = i;// rememebr which docA was used and save into i
                    docB = j;//rememebr which docB was used and save into j
                }
            }
        }

        cout << "Maximum Similarity: " << max; // display the max similarity
        if (docA != -1 && docB != -1) // if condtion used to make sure that the docA and docB found values (! is not) --> if docA AND docB are NOT equal to -1
            cout << ", the pair is: Doc " << docA + 1 << " and Doc " << docB + 1; // used +1 to avoid havong document called Doc0 therfore +1 to all documents
        cout << endl;

        return max; // return max value
    }

    // Now we have to return a new list of docs that is sotred by their summation values (low to high)
    static bool compareDocsBySum(T* a, T* b) { // made static to use in sort (doesn't need class instance)
        return a->summation() < b->summation(); // returns true if a's summation is less than b's
    // This causes the sort to arrange docs in ascending order by their summation() value
    }

    vector<T*> sortedBySummation() const {
        vector<T*> sorted = docs;  // Make a copy of the current document pointers
        sort(sorted.begin(), sorted.end(), compareDocsBySum);  // compareDocsBySum decides ordering by comparing summation() of two docs
         // sort() rearranges the pointers in 'sorted' based on compareDocsBySum function while sorted.begin() and sorted.end() define the range of elements to sort
    
        return sorted; // return sorted list
    }
};

#endif
