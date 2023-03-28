SRCS := $(wildcard *.cpp)
BINS := $(patsubst %.cpp, %, $(SRCS))

all: $(BINS)

% : $(SRCS)

.PHONY : clean
clean:
	-rm -f $(BINS)