CXX = g++
CXXFLAGS = -Wall -std=c++11 -g
TARGET = theatre_db
OBJS = main.o theatre.o database.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp database.h list.h theatre.h
	$(CXX) $(CXXFLAGS) -c main.cpp

theatre.o: theatre.cpp theatre.h
	$(CXX) $(CXXFLAGS) -c theatre.cpp

database.o: database.cpp database.h list.h theatre.h
	$(CXX) $(CXXFLAGS) -c database.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
