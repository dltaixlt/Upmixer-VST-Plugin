/*
  ==============================================================================

    STFT.h
    Created: 21 Oct 2018 2:06:23pm
    Author: Dimitris Koutsaidis

  ==============================================================================
*/


#include "../JuceLibraryCode/JuceHeader.h"


class STFT
{

	enum windowType
	{
		HANN = 1
	};

public:

	/*
		Constructor
		input: number of samples in window (numSamples)
	*/
	STFT(int numSamps);
	~STFT();

	/*
		Initializes the window function
		Input: type of window; see windowType enum
		Output: none
	*/
	void initWindow(int type);

	/*
		Applies the window function to an array of real floats
		Input: array on which the fuction will be applied
		Output: none
	*/
	void applyWindowFunction(std::complex<float>* array);
	
private:

	// private variables/methods go here
	int numSamples;
	float window[2048];

};
