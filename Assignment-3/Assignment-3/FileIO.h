//
//  FileIO.h
//  Test
//
//  Created by Kirisanth Subramaniam on 2013-11-30.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#ifndef __Test__FileIO__
#define __Test__FileIO__

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "objects.h"


class FileIO
{
public:
    void writeFile(std::string Data[], int size);
    void readFile(std::string *x[], int size);
    void saveFile(objects x[], int size);
    void loadFile(std::string *loadedString[], int size);
    FileIO();
};


#endif /* defined(__Test__FileIO__) */
