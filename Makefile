CC = g++
IDIR = include
SDIR = src
ODIR = obj
BDIR = bin

LIBS = -L lib -l sfml-system -l sfml-window -l sfml-graphics

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

COMPFLAGS = -I $(IDIR) -g -std=c++11 -D _DEBUG -D UNICODE -D _UNICODE
LINKFLAGS = -g -mwindows

all: $(BDIR)/pembed.exe

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $< -o $@ $(COMPFLAGS) -c


$(BDIR)/pembed.exe: $(OBJ)
	$(CC) $^ -o $@ $(LINKFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
