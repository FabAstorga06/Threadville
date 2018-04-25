IDIR = ./include
SDIR = ./src
ODIR = ./obj
UDIR = ./ui

CC = gcc
CFLAGS = -I$(IDIR)

EXEC = init

<<<<<<< HEAD
_DEPS =
=======
_DEPS = 
>>>>>>> 83500b02e40ef5e2446c42770461739dc431ea4a
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = $(EXEC).o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

LIBS = -lpthread -lm

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(EXEC)
