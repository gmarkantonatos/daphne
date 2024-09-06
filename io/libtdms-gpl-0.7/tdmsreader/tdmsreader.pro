TARGET        = tdmsreader

MOC_DIR        = ./tmp
OBJECTS_DIR    = ./tmp
DESTDIR        = ./

CONFIG        += release

CONFIG        -= qt
win32: CONFIG += console
macx:  CONFIG -= app_bundle

INCLUDEPATH   += ../include

HEADERS       += ../include/*.h
HEADERS       += ../include/*.hh

SOURCES       += main.cpp
SOURCES       += ../src/TdmsChannel.cpp\
				../src/TdmsGroup.cpp\
				../src/TdmsLeadIn.cpp\
				../src/TdmsMetaData.cpp\
				../src/TdmsObject.cpp\
				../src/TdmsParser.cpp\
				../src/TdmsSegment.cpp
