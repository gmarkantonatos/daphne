####### Input directories

SRCDIR   = ./src/
INCDIR	 = ./include

####### Output directory

OBJDIR   = tmp/

####### Compiler, tools and options
CXX           = g++
CXXFLAGS      = -pipe -g -O2 -Wall
INCPATH       = -I. -I$(INCDIR)
LINK          = g++
AR            = ar cq
RANLIB        = ranlib -s
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

OBJECTS       = $(OBJDIR)TdmsChannel.o\
		$(OBJDIR)TdmsGroup.o\
		$(OBJDIR)TdmsLeadIn.o\
		$(OBJDIR)TdmsMetaData.o\
		$(OBJDIR)TdmsObject.o\
		$(OBJDIR)TdmsParser.o\
		$(OBJDIR)TdmsSegment.o\

TARGET        = libtdms.a

####### Build rules

first: dist all

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)
	-$(DEL_FILE) $(TARGET)
	$(AR) $(TARGET) $(OBJECTS)
	$(RANLIB) $(TARGET)

dist:
	@$(CHK_DIR_EXISTS) $(OBJDIR) || $(MKDIR) $(OBJDIR)

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core
	-$(DEL_FILE) $(TARGET)

####### Compile

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $^
