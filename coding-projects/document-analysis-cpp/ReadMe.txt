CSCI291 - Assignment 2
Ghad Saqqa - 8049890


Type 'ls' to display all files in assignment 2 folder and they are:
- Doc.h --> Contains the abstract/base class Doc which is our blueprint for both DecDoc and HexDoc
- DecDoc.h --> Header file for DecDoc class which is for decimal documents
- DecDoc.cpp --> implementation of DecDoc class as this file generates decimal words, finds sum and similarity then stores them
- HexDoc.h --> Header file for HexDoc class which is for the hexadecimal documents
- HexDoc.cpp --> implementation of HexDoc class as this file generates decimal words, finds sum and similarity then stores them
- DocumentHandler.h --> template class that handles the lists if documents (either HexDoc or DecDoc) this couldve been with main but to be more organised and make help in debbuging if thers error, i pu it in its own file which really helped.
- main.cpp -->  Main program, it contains the full C++ code implementation of assignment 2 and handles input, output and calls the document handlers
- ReadMe.txt (this file) --> Explains the project structure and how to compile and run. 

In total there are 8 files 

How to Compile:
Different systems use different defualt C++ verstion so its better to specify which version we need
Since I'm using MAC, MAC compiler uses C++98 by defualt so you have to specify to use C++17:  

                g++ -std=c++17 main.cpp DecDoc.cpp HexDoc.cpp -o main

this will generate and exectuable file called 'main' using C++17

How to Run:
Use the following command format in your terminal:

                                        ./main num1 len1 thres num2 len2 pos

Where:
- num1: Number of DecDoc (decimal) documents to generate (>=0)
- len1: Number of 2-digit decimal words per DecDoc (>=0)
- thres: Similarity threshold for DecDoc comparison (>0)
- num2: Number of HexDoc (hexadecimal) documents to generate (>=0)
- len2: Number of 2-digit hexadecimal words per HexDoc (>=0)
- pos: Which digit (1 or 2) to compare for similarity in HexDoc (1 or 2)

ex.                                       ./main 5 6 10 6 7 2    
This will:
- Create 5 DecDocs with 6 numbers each and use a similarity threshold of 10
- Create 6 HexDocs with 7 hex values each compare using digit 2 in HexDoc similarity

However keep in mind that there are conditions that have to be followed for the code to run else a error message will be displayed which are:
- All numeric values must be greater than or equal to 0
- Threshold must be greater than 0
- Postion must be 1 or 2 only

Program Output:
The program displays:
- All DecDoc and HexDoc objects with their contents
- Maximum similarity between any two documents of each type (Dec and Hex)
- A sorted list of documents by their total value in ascending order

example simulation for assignment 2 (compiling, input lines and output)

ghad@192-168-1-13 Assignment 2 % g++ -std=c++17 main.cpp DecDoc.cpp HexDoc.cpp -o main     ) this is the first line which is compiler
ghad@192-168-1-13 Assignment 2 % ./main 5 6 10 6 7 2                                       ) second line which is our inputand obeys all conditions

) Sample output 
DecDoc Objects:         
DecDoc 1: ****  88  41  60  45  66  44 ****
DecDoc 2: ****  33  83  34  21  49  33 ****
DecDoc 3: ****  81  84  35  93  29  23 ****
DecDoc 4: ****  54  22  92  31  63  43 ****
DecDoc 5: ****  28  22  18  13  22  94 ****

Maximum Similarity: 13, the pair is: Doc 2 and Doc 3

DecDoc Sorted by Total Value:
DecDoc 5: ****  28  22  18  13  22  94 ****
DecDoc 2: ****  33  83  34  21  49  33 ****
DecDoc 4: ****  54  22  92  31  63  43 ****
DecDoc 1: ****  88  41  60  45  66  44 ****
DecDoc 3: ****  81  84  35  93  29  23 ****

------------------------------------------------------------

HexDoc Objects:
HexDoc 1: ^^^^  57  14  96  2F  EA  DF  F8 ^^^^
HexDoc 2: ^^^^  0B  54  04  A4  22  C2  01 ^^^^
HexDoc 3: ^^^^  33  7E  3D  26  83  B8  6E ^^^^
HexDoc 4: ^^^^  4C  34  E3  DD  99  C5  A3 ^^^^
HexDoc 5: ^^^^  9E  1C  31  16  EC  FA  86 ^^^^
HexDoc 6: ^^^^  EE  D5  06  D4  E4  73  04 ^^^^

Maximum Similarity: 9, the pair is: Doc 2 and Doc 6

HexDoc Sorted by Total Value:
HexDoc 2: ^^^^  0B  54  04  A4  22  C2  01 ^^^^
HexDoc 3: ^^^^  33  7E  3D  26  83  B8  6E ^^^^
HexDoc 5: ^^^^  9E  1C  31  16  EC  FA  86 ^^^^
HexDoc 1: ^^^^  57  14  96  2F  EA  DF  F8 ^^^^
HexDoc 6: ^^^^  EE  D5  06  D4  E4  73  04 ^^^^
HexDoc 4: ^^^^  4C  34  E3  DD  99  C5  A3 ^^^^

