CXX := g++

CXXFLAGS := -std=c++20 -Wall

SRC_DIRS := $(wildcard */)

SRCS := $(wildcard $(addsuffix *.cpp,$(SRC_DIRS)))

BINS := $(patsubst %.cpp,%,$(SRCS))

all: $(BINS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<


1_1:
	$(MAKE) -C 1_1
1_2:
	$(MAKE) -C 1_2
1_3:
	$(MAKE) -C 1_3
1_4:
	$(MAKE) -C 1_4
1_5:
	$(MAKE) -C 1_5

clean:
	rm -f $(BINS)
