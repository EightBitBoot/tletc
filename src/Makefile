
LIBFLAGS = -lstdc++ -lm -lGL -lglfw -lGLEW

ifeq ($(no_ec), true)
DEFINES += -DNO_OPENGL_ERRORS
endif

CXXFLAGS += -ggdb $(DEFINES)
LDFLAGS = $(LIBFLAGS)

CXX := gcc

HEADER_FILES := $(wildcard *.h)
SRC_FILES := $(wildcard *.cpp)

OBJECTS := $(SRC_FILES:.cpp=.o)

.PHONY: run clean realclean

all: main

main: $(OBJECTS)
	$(CXX) $(OBJECTS) -o main $(LDFLAGS)

run: main
	@ echo ------RUNNING------
	@./main

deps.d: $(HEADER_FILES) $(SRC_FILES)
	@echo Building deps
	@echo $(OBJECTS:.o=.cpp) | xargs $(CXX) -MM > deps.d

-include deps.d

clean:
	rm -f *.o deps.d

realclean: clean
	rm -f main
