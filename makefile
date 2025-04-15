# Arturo Flores 
# CWID: 886352491 
# Spring 2025
# CPSC 485


CC = g++
CFLAGS = -Wall -g
SRCS = main.cpp edit_distance.cpp
OBJS = main.o edit_distance.o
TARGET = edit_distance

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.cpp edit_distance.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) 