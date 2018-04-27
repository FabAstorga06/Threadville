IDIR = ./include
SDIR = ./src
ODIR = ./obj
UDIR = ./ui

CC = gcc
CFLAGS = -I$(IDIR)

EXEC = threadville

_DEPS = config.h constants.h control_methods.c \
  data_utils.c data.h functions.c generate_car.c \
     graph.c log_utils.c map_utils.c movement_bridges.c \
  mythread.c schedulers.c update_simulations.c \
		control_car.c
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
