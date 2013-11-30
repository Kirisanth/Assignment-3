//
//  objects.cpp
//  Assignment-3
//
//  Created by Meraj Patel on 11/29/2013.
//  Copyright (c) 2013 Kirisanth Subramaniam. All rights reserved.
//

#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>
#include "objects.h"


objects::objects(){
    org[0] = 0;
    org[1] = 0;
    org[2] = 0;
    
    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 0;
    
    norm[0] = 0;
    norm[1] = 0;
    norm[2] = 0;
    
};

void objects::normalizeDirection(){
    
}

void objects::rayPlaneTest(){
    
}

void objects::drawObjects(){
        if (objectType == 1){
            glutSolidCube(0.5);//draw sphere
        }
        else if (objectType == 2){
            glutWireCube(0.2);//draw cube
        }
        else {
            glEnable( GL_POINT_SMOOTH );
            glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glBegin(GL_POINTS);
			glVertex3f(0,0,0);//draw point
			glEnd();
        }
}
