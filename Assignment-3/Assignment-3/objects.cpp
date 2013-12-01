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
#include <math.h>


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
    
    translateX = 0;
    translateY = 0;
    translateZ = 0;
    
};

void objects::normalizeDirection(){
    
    float length;
    length = sqrt((dir[0]*dir[0]) + (dir[1] * dir[1]) + (dir[2] * dir[2]));
    norm[0] = dir[0]/length *-1;
    norm[1] = dir[1]/length *-1;
    norm[2] = dir[2]/length *-1;
    
}

void objects::drawObjects(){
        if (objectType == 1){
            glColor3f(0, 0.5, 0.5);
            glTranslatef(translateX, translateY, translateZ);
            glutSolidCube(0.5);//draw cube
        }
        else if (objectType == 2){
            glutSolidSphere(0.3, 15, 15);//draw cube
        }
        else {
            glEnable( GL_POINT_SMOOTH );
            glEnable( GL_BLEND );
            glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glBegin(GL_POINTS);
			glVertex3f(0,0,0);//draw point
			glEnd();
        }
    if (hit == true){
        glColor3f(1, 1, 1);
        glutWireCube(0.7);
    }
}

float objects::findDistance(int i){

   return -1 * (objectPointsForNormal[i][1][0]*objectPlaneNormal[i][0] + objectPointsForNormal[i][1][1]*objectPlaneNormal[i][1] + objectPointsForNormal[i][1][2]*objectPlaneNormal[i][2]);

}

float objects::normalMultiplyDirection(int i){
    return (objectPlaneNormal[i][0] *  norm[0] + objectPlaneNormal[i][1] * norm[1] + objectPlaneNormal[i][2] * norm[2]);
}

float objects::normalMultiplyOrgin(int i, float t){
    return  (-1* (objectPlaneNormal[i][0] * org[0] + objectPlaneNormal[i][1] * org[1] + objectPlaneNormal[i][2] * org[2] + findDistance(i)))/t;
}


void objects::normalizePlane(){
    
    objectPlaneNormal[0][0] = objectVectorForNormal[0][0][1]*objectVectorForNormal[0][1][2] - objectVectorForNormal[0][0][2]*objectVectorForNormal[0][1][1];
    objectPlaneNormal[0][1] = objectVectorForNormal[0][0][2]*objectVectorForNormal[0][1][0] - objectVectorForNormal[0][0][0]*objectVectorForNormal[0][1][2];
    objectPlaneNormal[0][2] = objectVectorForNormal[0][0][0]*objectVectorForNormal[0][1][1] - objectVectorForNormal[0][0][1]*objectVectorForNormal[0][1][0] * -1;
    
    printf("\nright side normal = (%f,%f,%f)\n",objectPlaneNormal[0][0],objectPlaneNormal[0][1],objectPlaneNormal[0][2]);
    
    objectPlaneNormal[1][0] = objectVectorForNormal[1][0][1]*objectVectorForNormal[1][1][2] - objectVectorForNormal[1][0][2]*objectVectorForNormal[1][1][1];
    objectPlaneNormal[1][1] = objectVectorForNormal[1][0][2]*objectVectorForNormal[1][1][0] - objectVectorForNormal[1][0][0]*objectVectorForNormal[1][1][2];
    objectPlaneNormal[1][2] = objectVectorForNormal[1][0][0]*objectVectorForNormal[1][1][1] - objectVectorForNormal[1][0][1]*objectVectorForNormal[1][1][0];
    
    printf("\nleft side normal = (%f,%f,%f)\n",objectPlaneNormal[1][0],objectPlaneNormal[1][1],objectPlaneNormal[1][2]);
    
    objectPlaneNormal[2][0] = objectVectorForNormal[2][0][1]*objectVectorForNormal[2][1][2] - objectVectorForNormal[2][0][2]*objectVectorForNormal[2][1][1];
    objectPlaneNormal[2][1] = objectVectorForNormal[2][0][2]*objectVectorForNormal[2][1][0] - objectVectorForNormal[2][0][0]*objectVectorForNormal[2][1][2];
    objectPlaneNormal[2][2] = objectVectorForNormal[2][0][0]*objectVectorForNormal[2][1][1] - objectVectorForNormal[2][0][1]*objectVectorForNormal[2][1][0];
    
    printf("\ntop side normal = (%f,%f,%f)\n",objectPlaneNormal[2][0],objectPlaneNormal[2][1],objectPlaneNormal[2][2]);
    
    objectPlaneNormal[3][0] = objectVectorForNormal[3][0][1]*objectVectorForNormal[3][1][2] - objectVectorForNormal[3][0][2]*objectVectorForNormal[3][1][1];
    objectPlaneNormal[3][1] = objectVectorForNormal[3][0][2]*objectVectorForNormal[3][1][0] - objectVectorForNormal[3][0][0]*objectVectorForNormal[3][1][2] *-1;
    objectPlaneNormal[3][2] = objectVectorForNormal[3][0][0]*objectVectorForNormal[3][1][1] - objectVectorForNormal[3][0][1]*objectVectorForNormal[3][1][0];
    
    printf("\nbottom normal = (%f,%f,%f)\n",objectPlaneNormal[3][0],objectPlaneNormal[3][1],objectPlaneNormal[3][2]);
    
    objectPlaneNormal[4][0] = objectVectorForNormal[4][0][1]*objectVectorForNormal[4][1][2] - objectVectorForNormal[4][0][2]*objectVectorForNormal[4][1][1];
    objectPlaneNormal[4][1] = objectVectorForNormal[4][0][2]*objectVectorForNormal[4][1][0] - objectVectorForNormal[4][0][0]*objectVectorForNormal[4][1][2];
    objectPlaneNormal[4][2] = objectVectorForNormal[4][0][0]*objectVectorForNormal[4][1][1] - objectVectorForNormal[4][0][1]*objectVectorForNormal[4][1][0];
    
    printf("\nback right side normal = (%f,%f,%f)\n",objectPlaneNormal[4][0],objectPlaneNormal[4][1],objectPlaneNormal[4][2]);
    
    objectPlaneNormal[5][0] = objectVectorForNormal[5][0][1]*objectVectorForNormal[5][1][2] - objectVectorForNormal[5][0][2]*objectVectorForNormal[5][1][1];
    objectPlaneNormal[5][1] = objectVectorForNormal[5][0][2]*objectVectorForNormal[5][1][0] - objectVectorForNormal[5][0][0]*objectVectorForNormal[5][1][2];
    objectPlaneNormal[5][2] = objectVectorForNormal[5][0][0]*objectVectorForNormal[5][1][1] - objectVectorForNormal[5][0][1]*objectVectorForNormal[5][1][0];
    
    printf("\nback left side normal = (%f,%f,%f)\n",objectPlaneNormal[5][0],objectPlaneNormal[5][1],objectPlaneNormal[5][2]);
}


void objects::setObjectPoints(float x, float y, float z){
    
    //for right face
    objectPointsForNormal[0][0][0] = 0.25 + x;
    objectPointsForNormal[0][0][1] = -0.25 + y;
    objectPointsForNormal[0][0][2] = 0.25 + z;
    
    objectPointsForNormal[0][1][0] = 0.25 + x;
    objectPointsForNormal[0][1][1] = 0.25 + y;
    objectPointsForNormal[0][1][2] = 0.25 + z;
    
    objectPointsForNormal[0][2][0] = -0.25 + x;
    objectPointsForNormal[0][2][1] = -0.25 + y;
    objectPointsForNormal[0][2][2] = 0.25 + z;
    
    //for vector 1
    objectVectorForNormal[0][0][0] = objectPointsForNormal[0][1][0] - objectPointsForNormal[0][0][0];
    objectVectorForNormal[0][0][1] = objectPointsForNormal[0][1][1] - objectPointsForNormal[0][0][1];
    objectVectorForNormal[0][0][2] = objectPointsForNormal[0][1][2] - objectPointsForNormal[0][0][2];
    
    //for vector 2
    objectVectorForNormal[0][1][0] = objectPointsForNormal[0][2][0] - objectPointsForNormal[0][0][0];
    objectVectorForNormal[0][1][1] = objectPointsForNormal[0][2][1] - objectPointsForNormal[0][0][1];
    objectVectorForNormal[0][1][2] = objectPointsForNormal[0][2][2] - objectPointsForNormal[0][0][2];
    
    
    //for left face
    objectPointsForNormal[1][0][0] = 0.25 + x;
    objectPointsForNormal[1][0][1] = -0.25 + y;
    objectPointsForNormal[1][0][2] = 0.25 + z;
    
    objectPointsForNormal[1][1][0] = 0.25 + x;
    objectPointsForNormal[1][1][1] = 0.25 + y;
    objectPointsForNormal[1][1][2] = 0.25 + z;
    
    objectPointsForNormal[1][2][0] = 0.25 + x;
    objectPointsForNormal[1][2][1] = -0.25 + y;
    objectPointsForNormal[1][2][2] = -0.25 + z;
    
    //for vector 1
    objectVectorForNormal[1][0][0] = objectPointsForNormal[1][1][0] - objectPointsForNormal[1][0][0];
    objectVectorForNormal[1][0][1] = objectPointsForNormal[1][1][1] - objectPointsForNormal[1][0][1];
    objectVectorForNormal[1][0][2] = objectPointsForNormal[1][1][2] - objectPointsForNormal[1][0][2];
    
    //for vector 2
    objectVectorForNormal[1][1][0] = objectPointsForNormal[1][2][0] - objectPointsForNormal[1][0][0];
    objectVectorForNormal[1][1][1] = objectPointsForNormal[1][2][1] - objectPointsForNormal[1][0][1];
    objectVectorForNormal[1][1][2] = objectPointsForNormal[1][2][2] - objectPointsForNormal[1][0][2];
    
    
    //for top face
    objectPointsForNormal[2][0][0] = 0.25 + x;
    objectPointsForNormal[2][0][1] = 0.25 + y;
    objectPointsForNormal[2][0][2] = 0.25 + z;
    
    objectPointsForNormal[2][1][0] = -0.25 + x;
    objectPointsForNormal[2][1][1] = 0.25 + y;
    objectPointsForNormal[2][1][2] = 0.25 + z;
    
    objectPointsForNormal[2][2][0] = -0.25 + x;
    objectPointsForNormal[2][2][1] = 0.25 + y;
    objectPointsForNormal[2][2][2] = -0.25 + z;
    
    //for vector 1
    objectVectorForNormal[2][0][0] = objectPointsForNormal[2][0][0] - objectPointsForNormal[2][1][0];
    objectVectorForNormal[2][0][1] = objectPointsForNormal[2][0][1] - objectPointsForNormal[2][1][1];
    objectVectorForNormal[2][0][2] = objectPointsForNormal[2][0][2] - objectPointsForNormal[2][1][2];
    
    //for vector 2
    objectVectorForNormal[2][1][0] = objectPointsForNormal[2][2][0] - objectPointsForNormal[2][1][0];
    objectVectorForNormal[2][1][1] = objectPointsForNormal[2][2][1] - objectPointsForNormal[2][1][1];
    objectVectorForNormal[2][1][2] = objectPointsForNormal[2][2][2] - objectPointsForNormal[2][1][2];
    
    
    //for bottom face
    objectPointsForNormal[3][0][0] = 0.25 + x;
    objectPointsForNormal[3][0][1] = -0.25 + y;
    objectPointsForNormal[3][0][2] = 0.25 + z;
    
    objectPointsForNormal[3][1][0] = -0.25 + x;
    objectPointsForNormal[3][1][1] = -0.25 + y;
    objectPointsForNormal[3][1][2] = 0.25 + z;
    
    objectPointsForNormal[3][2][0] = -0.25 + x;
    objectPointsForNormal[3][2][1] = -0.25 + y;
    objectPointsForNormal[3][2][2] = -0.25 + z;
    
    //for vector 1
    objectVectorForNormal[3][0][0] = objectPointsForNormal[3][0][0] - objectPointsForNormal[3][1][0];
    objectVectorForNormal[3][0][1] = objectPointsForNormal[3][0][1] - objectPointsForNormal[3][1][1];
    objectVectorForNormal[3][0][2] = objectPointsForNormal[3][0][2] - objectPointsForNormal[3][1][2];
    
    //for vector 2
    objectVectorForNormal[3][1][0] = objectPointsForNormal[3][2][0] - objectPointsForNormal[3][1][0];
    objectVectorForNormal[3][1][1] = objectPointsForNormal[3][2][1] - objectPointsForNormal[3][1][1];
    objectVectorForNormal[3][1][2] = objectPointsForNormal[3][2][2] - objectPointsForNormal[3][1][2];
    
    //for back right face
    objectPointsForNormal[4][0][0] = -0.25 + x;
    objectPointsForNormal[4][0][1] = 0.25 + y;
    objectPointsForNormal[4][0][2] = -0.25 + z;

    objectPointsForNormal[4][1][0] = -0.25 + x;
    objectPointsForNormal[4][1][1] = -0.25 + y;
    objectPointsForNormal[4][1][2] = -0.25 + z;
    
    objectPointsForNormal[4][2][0] = 0.25 + x;
    objectPointsForNormal[4][2][1] = -0.25 + y;
    objectPointsForNormal[4][2][2] = -0.25 + z;
    
    //for vector 1
    objectVectorForNormal[4][0][0] = objectPointsForNormal[4][0][0] - objectPointsForNormal[4][1][0];
    objectVectorForNormal[4][0][1] = objectPointsForNormal[4][0][1] - objectPointsForNormal[4][1][1];
    objectVectorForNormal[4][0][2] = objectPointsForNormal[4][0][2] - objectPointsForNormal[4][1][2];
    

    //for vector 2
    objectVectorForNormal[4][1][0] = objectPointsForNormal[4][2][0] - objectPointsForNormal[4][1][0];
    objectVectorForNormal[4][1][1] = objectPointsForNormal[4][2][1] - objectPointsForNormal[4][1][1];
    objectVectorForNormal[4][1][2] = objectPointsForNormal[4][2][2] - objectPointsForNormal[4][1][2];
    
    printf("\n VECTOR 1 back left side normal = (%f,%f,%f)\n",objectVectorForNormal[4][0][0],objectVectorForNormal[4][0][1],objectVectorForNormal[4][0][2]);
    printf("\n VECTOR 2 back left side normal = (%f,%f,%f)\n",objectVectorForNormal[4][1][0],objectVectorForNormal[4][1][1],objectVectorForNormal[4][1][2]);
    
    //for back left face
    objectPointsForNormal[5][0][0] = -0.25 + x;
    objectPointsForNormal[5][0][1] = 0.25 + y;
    objectPointsForNormal[5][0][2] = -0.25 + z;
    
    objectPointsForNormal[5][1][0] = -0.25 + x;
    objectPointsForNormal[5][1][1] = -0.25 + y;
    objectPointsForNormal[5][1][2] = -0.25 + z;
    
    objectPointsForNormal[5][2][0] = -0.25 + x;
    objectPointsForNormal[5][2][1] = -0.25 + y;
    objectPointsForNormal[5][2][2] = 0.25 + z;
    
    //for vector 1
    objectVectorForNormal[5][0][0] = objectPointsForNormal[5][0][0] - objectPointsForNormal[5][1][0];
    objectVectorForNormal[5][0][1] = objectPointsForNormal[5][0][1] - objectPointsForNormal[5][1][1];
    objectVectorForNormal[5][0][2] = objectPointsForNormal[5][0][2] - objectPointsForNormal[5][1][2];
    
    //for vector 2
    objectVectorForNormal[5][1][0] = objectPointsForNormal[5][2][0] - objectPointsForNormal[5][1][0];
    objectVectorForNormal[5][1][1] = objectPointsForNormal[5][2][1] - objectPointsForNormal[5][1][1];
    objectVectorForNormal[5][1][2] = objectPointsForNormal[5][2][2] - objectPointsForNormal[5][1][2];
    
    normalizePlane();
    
}
