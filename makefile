CC = gcc
CFLAGS = -I./headers

SRC = src/main.c src/logic.c src/outp_functions.c src/user_interaction.c
OBJ = $(SRC:.c=.o)
EXEC = game.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(OBJ) $(EXEC)