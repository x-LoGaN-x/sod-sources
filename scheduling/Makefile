CC := g++

# SRCS_PTH := $(wildcard *pthread*.cpp)
SRCS_PTH := $(wildcard *.cpp)
BINS_PTH := $(patsubst %.cpp, %, $(SRCS_PTH))
LDFLAGS_PTH := -lpthread

# SRCS_STD := $(wildcard *std*.cpp)
# BINS_STD := $(patsubst %.cpp, %, $(SRCS_STD))

all: $(BINS_PTH) $(BINS_OMP)

$(BINS_PTH) : $(SRCS_PTH)
	$(CC) $(LDFLAGS_PTH) -o $@ $@.cpp

# $(BINS_OMP) : $(SRCS_OMP)
# 	$(CC) $(CFLAGS_OMP) $(LDFLAGS_OMP) -o $@ $@.cpp

# $(BINS_STD) : $(SRCS_STD)

clean:
#	 -rm -f $(BINS_PTH) $(BINS_OMP)
	-rm -f $(BINS_PTH)

.PHONY : all clean