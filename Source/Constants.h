/*
  ==============================================================================

    Constants.h
    Created: 23 Jun 2015 2:00:04pm
    Author:  R00070693

  ==============================================================================
*/

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#define M_PI 3.14159265358979323846
#define TPI 2*M_PI
#define eps 0.0000000000001f
//#define WINDOW_SIZE 4096
//#define HOP_SIZE (WINDOW_SIZE / 4)
//#define NUM_SOURCES 3
//#define NUM_ITERS 100

const int WINDOW_SIZE = 4096;
const int HOP_SIZE = WINDOW_SIZE / 4;
const int NUM_SOURCES = 3;
const int NUM_ITERS = 10;

#endif  // CONSTANTS_H_INCLUDED
