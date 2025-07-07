CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = programa

ifeq ($(OS),Windows_NT)
    RM = del /Q
    RMFLAGS =
    RMNULL = 2>nul
else
    RM = rm
    RMFLAGS = -f
    RMNULL = >/dev/null 2>&1
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo Cleaning up...
	-$(RM) $(RMFLAGS) src\*.o $(TARGET) processamento.log $(RMNULL) || true
