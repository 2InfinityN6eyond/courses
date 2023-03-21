CXX = g++
CXXFLAGS = -W -Wall -std=c++11 
TARGET = mips-sim
OBJS = main.o mips_sim.o

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(OBJS) $(TARGET)
