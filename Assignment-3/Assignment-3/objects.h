//
//  objects.h
//  Assignment-3
//
//  Created by Meraj Patel on 11/29/2013.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#ifndef __Assignment_3__objects__
#define __Assignment_3__objects__

#include <iostream>

class objects{
    public:
        double org[3];
        double dir[3];
        double norm[3];
        double rotationAngle;
        int objectType;
        int drawingMaterial; //indicate which choice made by user via integer
        double scaleFactor;
        objects();
        void normalizeDirection();
        void rayPlaneTest();
        void drawObjects();

};

#endif /* defined(__Assignment_3__objects__) */
