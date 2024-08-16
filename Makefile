# compiler
CC = clang

# compiler flags
CFLAGS = -Wall -Wextra -Werror

# output executable name
TARGET = KeyCheck.exe

# source file
SRCS = main.c

# required libraries
LIBS = -lshell32

# build target
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# remove prev version of .exe
clean:
	del $(TARGET)

# simplistic code execution (for testing)
run:
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)
	./KeyCheck.exe
