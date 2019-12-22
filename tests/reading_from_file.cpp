// reading_from_file.cpp
//
// This program shows you how to read from a file in C++
// 

#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;


int main() 
{ 
   // open a file in read mode
   ifstream infile;
   infile.open("../input_files/input_example.txt");
   	
   if (!infile.is_open()) {
      cout << "error opening the input file\n";
      exit(EXIT_FAILURE);
   }

   string line;
   while (getline(infile, line))
   {
    istringstream iss(line);
    int int1, int2, int3, int4;
    string string1;
    
    if (!(iss >> string1 >> int1 >> int2 >> int3 >> int4)) { break; } // error
    
    cout << string1 << " " << int1 << " " << int2 << " "
         << int3 << " " << int4 << endl;
    }

   // close the opened file.
   infile.close();

   return 0;
}
