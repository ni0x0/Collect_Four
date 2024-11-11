CC = gcc
CFLAGS = -I./headers

SRC = src/main.c src/logic.c src/outp_functions.c src/user_interaction.c
EXEC = game.exe
OBJ = src/main.o src/logic.o src/outp_functions.o src/user_interaction.o

.PHONY: all clean

all: $(EXEC)
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del -f $(OBJ) $(EXEC)
