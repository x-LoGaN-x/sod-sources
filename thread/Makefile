CC := g++

SRCS_PTH := $(wildcard *pthread*.cpp)
BINS_PTH := $(patsubst %.cpp, %, $(SRCS_PTH))
LDFLAGS_PTH := -lpthread

SRCS_OMP := $(wildcard *openmp*.cpp)
BINS_OMP := $(patsubst %.cpp, %, $(SRCS_OMP))
CFLAGS_OMP := -fopenmp
LDFLAGS_OMP := -lgomp

SRCS_STD := $(wildcard *std*.cpp)
BINS_STD := $(patsubst %.cpp, %, $(SRCS_STD))

all: $(BINS_PTH) $(BINS_OMP)

$(BINS_PTH) : $(SRCS_PTH)
	$(CC) $(LDFLAGS_PTH) -o $@ $@.cpp

$(BINS_OMP) : $(SRCS_OMP)
	$(CC) $(CFLAGS_OMP) $(LDFLAGS_OMP) -o $@ $@.cpp

$(BINS_STD) : $(SRCS_STD)

clean:
	-rm -f $(BINS_PTH) $(BINS_OMP)

.PHONY : all clean