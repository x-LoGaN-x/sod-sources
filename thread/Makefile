CC := g++

SRCS_PTH := $(wildcard *pthread*.cpp)
BINS_PTH := $(patsubst %.cpp, %, $(SRCS_PTH))
LDFLAGS_PTH := -lpthread

SRCS_OMP := $(wildcard *openmp*.cpp)
BINS_OMP := $(patsubst %.cpp, %, $(SRCS_OMP))
CFLAGS_OMP := -fopenmp
LDFLAGS_OMP := -lgomp

all: $(BINS_PTH) $(BINS_OMP)

$(BINS_PTH) : $(SRCS_PTH)
	$(CC) $(LDFLAGS_PTH) -o $@ $@.cpp

$(BINS_OMP) : $(SRCS_OMP)
	$(CC) $(CFLAGS_OMP) $(LDFLAGS_OMP) -o $@ $@.cpp

clean:
	-rm -f $(BINS_PTH) $(BINS_OMP)

.PHONY : all clean