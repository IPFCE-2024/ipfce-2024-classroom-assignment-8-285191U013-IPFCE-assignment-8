.PHONY: all configure build test clean

# Check if ninja is available
NINJA := $(shell command -v ninja 2> /dev/null)

# Set the generator to ninja if available, otherwise use make
ifeq ($(NINJA),)
GENERATOR := "Unix Makefiles"
else
GENERATOR := "Ninja"
endif

all: build

configure:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G $(GENERATOR)

build: configure
	cmake --build build

test: build
	./build/unit-tests

clean:
	rm -rf build
