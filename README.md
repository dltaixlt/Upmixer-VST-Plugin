## "Upmixer VST Plug-In"
In this repository I include all the C++ source code files, the JUCE library files and build files for MacOS Xcode IDE. Projucer project file also included.
This is a plug-in that I am currently developing for my Master's Thesis. It is an implementation of an up-mixing algorithm.


## How to use
In order to compile the plug-in, you will need to download and set up the [JUCE library and Projucer software](https://shop.juce.com/get-juce/download).
Then download and set up [Steinberg's VST3 SDK](https://www.steinberg.net/en/company/developers.html) into JUCE.

In order to just use the plug-in, simply copy the pre-build VST file from the "Builds" folder to your OS VST folder.
For MacOS users, copy the pre-build VST file to this path "~/Library/Audio/Plug-Ins/VST".
For Windows users, you have to build the ".dll" VST file.


## Description
The algorithm up-mixes 2 channel stereo signals for 5.1 surround reproduction.


## References
[1] [S. Kraft; U. Zölzer,
    "Time-Domain Implementation of a Stereo to Surround Sound Upmix Algorithm",
    Proceedings of the 19th International Conference on Digital Audio Effects (DAFx-16), 05/09/2017.](http://dafx16.vutbr.cz/dafxpapers/17-DAFx-16_paper_32-PN.pdf)

[2] [S. Kraft; U. Zölzer,
    "Low-complexity stereo signal decomposition and source separation for application in stereo to 3D upmixing",
    Audio Engineering Society 140th Convention, 26/05/2016.](http://www.aes.org/e-lib/browse.cfm?elib=18284)
    
[3] [S. Kraft; U. Zölzer,
    "Stereo Signal Separation and Upmixing by Mid-Side Decomposition in the Frequency-Domain",
    Proceedings of the 19th International Conference on Digital Audio Effects (DAFx-15), 03/12/2015.](https://www.ntnu.edu/documents/1001201110/1266017954/DAFx-15_submission_9.pdf)
    
[4] [E. Vickers,
    "Frequency-Domain Two- to Three-Channel Upmix for Center Channel Derivation and Speech Enhancement".
    Audio Engineering Society 127th Convention, 09/10/2009.](http://www.aes.org/e-lib/browse.cfm?elib=15112)
