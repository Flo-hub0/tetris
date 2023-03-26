
.SUFFIXES: .cpp

TARGET         = tetris
OBJECTS        = Field.o Piece.o Ipiece.o Spiece.o PieceFactory.o main.o
SOURCES        = $(OBJECTS:.o=.cpp)

CXX            = /opt/local/bin/g++
CXXFLAGS       = -Wall -I.
LDFLAGS        =
LIBS           =

.cpp.o: $<
	$(CXX) $(CPXXFLAGS) $(CXXFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean:
	rm -f ${TARGET} $(OBJECTS) $(OBJECTS:.o=.h~) $(OBJECTS:.o=.cpp~) Makefile~
