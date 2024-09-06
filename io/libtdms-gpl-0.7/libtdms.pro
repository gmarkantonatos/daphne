TARGET        = tdms
TEMPLATE      = lib

MOC_DIR        = ./tmp
OBJECTS_DIR    = ./tmp
DESTDIR        = ./

CONFIG        += warn_on release
CONFIG        += staticlib
CONFIG        -= qt

INCLUDEPATH   += ./include

HEADERS       += ./include/*.h
HEADERS       += ./include/*.hh

SOURCES       +=./src/TdmsChannel.cpp\
				./src/TdmsGroup.cpp\
				./src/TdmsLeadIn.cpp\
				./src/TdmsMetaData.cpp\
				./src/TdmsObject.cpp\
				./src/TdmsParser.cpp\
				./src/TdmsSegment.cpp
