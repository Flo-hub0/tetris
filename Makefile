
.SUFFIXES: .cpp

TARGET         = tetris
OBJECTS        = Field.o Piece.o Ipiece.o Jpiece.o Lpiece.o Opiece.o Spiece.o Tpiece.o cube3.o menu2.o playing_window.o Zpiece.o PieceFactory.o main.o
SOURCES        = $(OBJECTS:.o=.cpp)
OBJDIR         = obj
SRCDIR         = src

CXX            = /opt/local/bin/g++
CXXFLAGS       = -Wall -I. -I/opt/local/include -I/opt/local/include/gtk-4.0 -I/opt/local/include/glib-2.0 -I/opt/local/lib/glib-2.0/include -I/opt/local/include/cairo -I/opt/local/include/pango -I/opt/local//include/pango-1.0 -I/opt/local/include/harfbuzz -I/opt/local/include/gdk-pixbuf-2.0 -I/opt/local/include/graphene-1.0 -I/opt/local/lib/graphene-1.0/include
LDFLAGS        =
LIBS           =

.cpp.o: $<
	$(CXX) $(CPXXFLAGS) $(CXXFLAGS) -c $<

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

clean:
	rm -f ${TARGET} $(OBJECTS) $(OBJECTS:.o=.h~) $(OBJECTS:.o=.cpp~) Makefile~
