/*
  ==============================================================================

    STFT.cpp
    Created: 21 Oct 2018 2:06:23pm
    Author:  Dimitris Koutsaidis

  ==============================================================================
*/


#include "STFT.h"


STFT::STFT(int numSamps)
{
	numSamples = numSamps;
}


STFT::~STFT() {}


void STFT::initWindow(int windowType)
{
	if (windowType == HANN)
	{
		for (int i = 0; i < numSamples; i++)
        {
			window[i] = (float)(0.5*(1 - cos((2*M_PI*i) / (numSamples - 1))));
		}
	}
}


void STFT::applyWindowFunction(std::complex<float>* array)
{
	for (int i = 0; i < numSamples; i++)
	{
		array[i] *= window[i];
	}
}

