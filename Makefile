IDIR = ./include
SDIR = ./src
ODIR = ./obj
UDIR = ./ui

CC = gcc
CFLAGS = -I$(IDIR)

EXEC = threadville

_DEPS = map_utils.c
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(EXEC).o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS =

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(EXEC)
