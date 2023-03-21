C = gcc
CFLAGS = -W -Wall
TARGET = mips-sim
OBJS = main.o mips_simulator.o

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(TARGET)
