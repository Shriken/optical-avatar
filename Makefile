CC = g++

CFLAGS = -Wall
PLATFORM_FLAGS =
DEBUGFLAGS = -g

PLATFORM_LIBS =

BIN = avatar
SRC = $(wildcard src/*.cpp)

ifeq ($(shell uname -s), Darwin)
	CC = clang++
	PLATFORM_FLAGS = -mmacosx-version-min=10.7 -D__MAC__
	PLATFORM_LIBS = -framework GLUT -framework OpenGL
endif

FLAGS = $(PLATFORM_FLAGS) $(CFLAGS)
LIBS = -lm $(PLATFORM_LIBS) -lGLEW

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

debug: $(SRC)
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(LIBS) $^ -o $(BIN)

.PHONY: clean run

clean:
	rm -f *.o $(BIN)

run: $(BIN)
	./$(BIN)
