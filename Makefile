CC=g++
CFLAGS=-c -Wall
SOURCES=src/main.cpp src/run/Runner.cpp src/model/Tree.cpp src/model/Noh.cpp src/model/Constants.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=avltree

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) ; $(CC) $(OBJECTS) -o $@

.cpp.o: ; $(CC) $(CFLAGS) $< -o $@

clean: ; rm $(OBJECTS)