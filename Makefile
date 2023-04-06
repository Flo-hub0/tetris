

.SUFFIXES: .cpp

vpath %.cpp src

SRCDIR         := src
OBJDIR         := build

TARGET         := tetris
SOURCES        := $(addprefix $(SRCDIR)/,Field.cpp Piece.cpp Ipiece.cpp Jpiece.cpp Lpiece.cpp Opiece.cpp Spiece.cpp Tpiece.cpp Zpiece.cpp PieceFactory.cpp main.cpp)
OBJECTS        := $(addprefix $(OBJDIR)/,Field.o Piece.o Ipiece.o Jpiece.o Lpiece.o Opiece.o Spiece.o Tpiece.o Zpiece.o PieceFactory.o main.o)

CXX            := /opt/local/bin/g++
CXXFLAGS       := -Wall -I$(SRCDIR)
LDFLAGS        :=
LIBS           :=

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h
	$(CXX) $(CPXXFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CPXXFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f ${TARGET} $(OBJECTS) $(SOURCES:.cpp=.h~) $(SOURCES:.cpp=.cpp~) Makefile~