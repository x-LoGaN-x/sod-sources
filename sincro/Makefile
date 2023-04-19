CC := g++

SRCS_MUTEX := $(wildcard *mutex*.cpp)
BINS_MUTEX := $(patsubst %.cpp, %, $(SRCS_MUTEX))
LDFLAGS_MUTEX := -lpthread
CFLAG_NO_MUTEX := -DLOCAL_MUTEX=false -DUSE_MUTEX=false
CFLAG_MUTEX := -DLOCAL_MUTEX=false -DUSE_MUTEX=true

SRCS_SEM := $(wildcard *semaphore*.cpp)
BINS_SEM := $(patsubst %.cpp, %, $(SRCS_SEM))
LDFLAGS_SEM := -lpthread
CFLAG_NO_SEM := -DLOCAL_MUTEX=false -DUSE_MUTEX=false
CFLAG_SEM := -DLOCAL_MUTEX=false -DUSE_MUTEX=true

SRCS_OMP := $(wildcard *openmp*.cpp)
BINS_OMP := $(patsubst %.cpp, %, $(SRCS_OMP))
CFLAGS_OMP := -fopenmp
LDFLAGS_OMP := -lgomp

SRCS_STD := $(wildcard *std*.cpp)
BINS_STD := $(patsubst %.cpp, %, $(SRCS_STD))

all: $(BINS_MUTEX) $(BINS_SEM) $(BINS_OMP)

$(BINS_MUTEX) : $(SRCS_MUTEX)
	$(CC) $(LDFLAGS_MUTEX) $(CFLAG_NO_MUTEX) -o $@ $@.cpp
	$(CC) $(LDFLAGS_MUTEX) $(CFLAG_MUTEX) -o $@_ok $@.cpp

$(BINS_SEM) : $(SRCS_SEM)
	$(CC) $(LDFLAGS_SEM) $(CFLAG_NO_SEM) -o $@ $@.cpp

$(BINS_OMP) : $(SRCS_OMP)
	$(CC) $(CFLAGS_OMP) $(LDFLAGS_OMP) -o $@ $@.cpp

$(BINS_STD) : $(SRCS_STD)

clean:
	-rm -f $(BINS_MUTEX) $(BINS_SEM) *_ok $(BINS_OMP)

.PHONY : all clean