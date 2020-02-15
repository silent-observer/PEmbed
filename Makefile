CC = g++
IDIR = include
SDIR = src
ODIR = obj
BDIR = bin

LIBS = -L lib -l sfml-system -l sfml-window -l sfml-graphics

_OBJ = main.o graph.o gui.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

COMPFLAGS = -I $(IDIR) -g -std=c++11 -D _DEBUG -D UNICODE -D _UNICODE
LINKFLAGS = -g

all: $(BDIR)/pembed.exe

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $< -o $@ $(COMPFLAGS) -c

$(ODIR)/graph.o: $(IDIR)/graph.hpp
$(ODIR)/gui.o: $(IDIR)/graph.hpp $(IDIR)/gui.hpp
$(ODIR)/main.o: $(IDIR)/graph.hpp $(IDIR)/gui.hpp

$(BDIR)/pembed.exe: $(OBJ)
	$(CC) $^ -o $@ $(LINKFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
