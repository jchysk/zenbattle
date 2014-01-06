//
//  Common.h
//  SChart
//
//  Copyright 2011 Scott Logic Ltd. All rights reserved.
//

#ifndef SChartGL_Common
#define SChartGL_Common

// A shared struct. The JNI wrapper can fake this as an array of floats. :-0
typedef struct
{
    float zoomX, zoomY;
    float minX,  minY;
} SChartGLTranslation;

typedef struct
{
    float red;
    float green;
    float blue;
    float alpha;
} GLColour4f;

#endif
