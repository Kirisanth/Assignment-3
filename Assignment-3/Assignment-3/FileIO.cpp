//
//  FileIO.cpp
//  Test
//
//  Created by Kirisanth Subramaniam on 2013-11-30.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#include "FileIO.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <typeinfo>

using namespace std;

FileIO::FileIO()
{
}

void FileIO::writeFile(string Data[], int size)
{
    // basic file operations
    ofstream myfile;
    myfile.open ("example.txt");
    
    for (int i = size - 1; i >= 0; i--) {
        
        //        myfile << Data[i] << " Writing this to a file.\n";
        myfile << Data[i] << "\n";
        
    }
    myfile.close();
}

void FileIO::readFile(string *x[], int size)
{
    string line;
    ifstream myfile ("example.txt");
    *x = new string[size];
    int i = size - 1;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            //            cout << line << endl;
            (*x)[i] = line;
            string text = (*x)[i];
            i--;
            //            double val = strtod(text.c_str(), NULL) + 2;
            //            printf("\n%f",val);
            string word;
            stringstream stream(line);
            while( getline(stream, word, ',') )
                cout << word << "\n";
            cout << "------------\n";
        }
        myfile.close();
        
        
        
        
    }
    else cout << "Unable to open file";
    
}

void FileIO::saveFile(objects x[], int size)
{
    // basic file operations
    ofstream myfile;
    myfile.open ("example.txt");
    
    for (int i = size - 1; i >= 0; i--) {
        
        //        myfile << Data[i] << " Writing this to a file.\n";
        myfile << x[i].changeDataToString() << "\n";
        
    }
    myfile.close();
}

void FileIO::loadFile(string *loadedString[], int size)
{
    string returnVal;
    string line;
    ifstream myfile ("example.txt");
//    *x = new string[size];
    int i = size - 1;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
//            cout << line << endl;
            (*loadedString)[i] = line;
//            string text = (*loadedString)[i];
            i--;
            //            double val = strtod(text.c_str(), NULL) + 2;
            //            printf("\n%f",val);
//            string word;
//            stringstream stream(line);
//            while( getline(stream, word, ',') )
//                cout << word << "\n";
//            cout << "------------\n";
            cout << (loadedString)[i];
//            cout << typeid(line).name();
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    
    cout << "good";
}

