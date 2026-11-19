CC = gcc
CFLAGS = -Wall -Iinclude
FONTES = $(wildcard src/*.c)

# Linux / WSL
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Windows (MinGW / w64devkit / MSYS2)
ifeq ($(OS),Windows_NT)
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
endif

all: vampire-survivors-pif

vampire-survivors-pif: $(FONTES)
	$(CC) $(CFLAGS) $(FONTES) -o vampire-survivors-pif $(LIBS)

run: vampire-survivors-pif
	./vampire-survivors-pif

clean:
	rm -f vampire-survivors-pif vampire-survivors-pif.exe
