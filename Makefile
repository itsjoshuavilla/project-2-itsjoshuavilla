# Makefile for Project 2 - Student Tracking

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = main
SRC = main.cpp
OUTFILE = student_info.dat

# Default target (compile)
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Run program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET) $(OUTFILE)
