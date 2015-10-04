CXX = g++

CXXFLAGS  = -Wall -g
LDFLAGS   = -lm -lGLEW `pkg-config --libs opencv`

PLATFORM_FLAGS =

BIN = avatar
SRC = $(wildcard src/*.cpp)

ifeq ($(shell uname -s), Darwin)
	CXX = clang++
	PLATFORM_FLAGS = -mmacosx-version-min=10.7 -D__MAC__
	LDFLAGS += -framework GLUT -framework OpenGL
endif

CXXFLAGS += $(PLATFORM_FLAGS)
CXXFLAGS += `pkg-config --cflags opencv`

all: avatar

avatar: src/avatar.o
	$(CXX) $(LDFLAGS) $^ -o avatar

debug: $(SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(BIN)

.PHONY: clean run

clean:
	rm -f $(wildcard src/*.o) $(BIN)

run: $(BIN)
	./$(BIN)
