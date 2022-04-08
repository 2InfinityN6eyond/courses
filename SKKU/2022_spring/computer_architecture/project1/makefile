CXX=g++
CXXFLAGS=-std=c++11
#add C++ source files here
SRCS=mips_sim.cc
TARGET=mips-sim
OBJS := $(patsubst %.cc,%.o,$(SRCS))
all: $(TARGET)

%.o:%.cc
	$(CXX) $(CXXFLAGS) $< -c -o $@
	
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	
.PHONY=clean

clean:
	rm -f $(OBJS) $(TARGET)
