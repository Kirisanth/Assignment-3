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
        double objectPlaneNormal[6][3];
        double objectPointsForNormal[6][3][3];
        double objectVectorForNormal[6][2][3];
        double spherePoints[3];
        double rotationAngle;
        double translateX = 0, translateY = 0, translateZ = 0;
        double rotateX = 0, rotateY = 0, rotateZ = 0;
        bool hit = false;
        int objectType;
        int drawingMaterial; //indicate which choice made by user via integer
        double scaleFactor;
        objects();
        void normalizeDirection();
        void normalizePlane();
        float normalMultiplyDirection(int i);
        float normalMultiplyOrgin(int i, float t);
        void drawObjects();
        void setObjectPoints(float x, float y, float z);
        void modifyRotationPoints(float rotX, float rotY, float rotZ, int angleChoice);
        void createObjectVectors();
        float findDistance(int i);
        void objectTranslateX(double x);
        void objectTranslateY(double y);
        void objectTranslateZ(double z);
        void objectRotateX(double x);
        void objectRotateY(double y);
        void objectRotateZ(double z);

};

#endif /* defined(__Assignment_3__objects__) */
