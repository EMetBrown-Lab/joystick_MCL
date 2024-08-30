CFLAGS += -O2 -Wall
TARGET = example
CC= g++

example : example.cpp
	$(CC) $(CFLAGS) -o $(TARGET) example.cpp -L. -lmicrodrive
clean :
	rm -f *~ *.o $(TARGET)

