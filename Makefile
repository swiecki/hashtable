CC = gcc
CFLAGS = -g -Wall -pthread
# main executable file first
TARGET = mthash
# object files next
OBJS = main.o hash.o
# header files next
DEPS = hash.h list.h
.PHONY : clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -pthread

.c.o: $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) *~

