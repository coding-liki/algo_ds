CXX := g++

CXXFLAGS := -std=c++20 -Wall

SRC_DIRS := $(wildcard */)

SRCS := $(wildcard $(addsuffix *.cpp,$(SRC_DIRS)))

BINS := $(patsubst %.cpp,%,$(SRCS))

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(BINS)
