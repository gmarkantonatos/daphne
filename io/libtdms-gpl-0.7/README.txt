libtdms GNU GPL v. 3.0
——————————————————————
AUTHOR: Ion Vasilief
——————————————————————
FEATURES: libtdms is a C++ library for reading National Instruments TDMS files (http://www.ni.com/white-paper/3727/en).
————————————————————————————————————————————————————————————————————————————————————————————————————
LICENSE: GNU GPL v. 3.0 for open source applications. 
	For commercial applications you need a commercial license from IONDEV SRL (http://iondev.ro).
————————————————————————————————————————————————————————————————————————————————————————————————————
CREDITS: libtdms is based on the "tdmsreader" project: https://github.com/shumway/tdmsreader
————————————————————————————————————————————————————————————————————————————————————————————————————
COMPILING: 
	On Unix-like systems (Linux, macOS, etc...) a Makefile for building a static version of the library is provided in the source archive. 
	All you need to type is: 
	$ make
	
	On Windows you may use the file Makefile.win. It was tested with the MinGW compiler. You need to type: 
	$ make -f Makefile.win
	
	For users that feel more comfortable using the qmake build system from Qt (https://www.qt.io/) we provide the libtdms.pro file. You need to type:
	$ qmake
	$ make
————————————————————————————————————————————————————————————————————————————————————————————————————
TESTING: a short demo application is provided in the “tdmsreader” folder of the source archive.
	In order to compile it on Unix-like systems type:
	$ cd tdmsreader
	$ make
	
	On Windows you may use the file Makefile.win. It was tested with the MinGW compiler. You need to type:
	$ cd tdmsreader
	$ make -f Makefile.win
	
	If you build on Windows using the Borland C++ compiler type:
	$ make -f Makefile.borland
	$ cd tdmsreader
	$ make -f Makefile.borland
	
	For users that feel more comfortable using the qmake tool from Qt we provide the tdmsreader.pro file. You need to type:
	$ cd tdmsreader
	$ qmake
	$ make
	
	You can get help about how to use tdmsreader by typing:
	$ tdmsreader -h
	
USE: tdmsreader -option your_file_name.tdms
	Options:
	-h: print help information and exit
	-p: display channel properties
	-s: store channel data values
	-v: verbose output
————————————————————————————————————————————————————————————————————————————————————————————————————
