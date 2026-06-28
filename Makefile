CXX          := g++
BASEFLAGS    := -std=c++23

DEBUGFLAGS   := -O0 -g
DEVFLAGS     := -O2 -DNDEBUG
RELEASEFLAGS := -O2 -DNDEBUG -static -Wall -Wextra -Wshadow -Wpedantic -Werror -Wduplicated-cond

ifdef FLAGS
BASEFLAGS += $(FLAGS)
endif

SRCS         := $(wildcard code/*.cpp)

RELEASE_OBJS := $(SRCS:code/%.cpp=obj/release/%.o)
DEV_OBJS   := $(SRCS:code/%.cpp=obj/dev/%.o)
DEBUG_OBJS   := $(SRCS:code/%.cpp=obj/debug/%.o)

.PHONY: all debug release dirs run lizard lizard_w clean

all: run

# ----- Builds -----

release: build/release.exe
dev:     build/dev.exe
debug:   build/debug.exe

run: dev
	time -f "%e s   %M KB" ./build/dev.exe $(PARAMS)

# ----- Linking -----

build/release.exe: $(RELEASE_OBJS) | build/
	time -f "%e s   %M KB" $(CXX) $(RELEASEFLAGS) $(BASEFLAGS) $^ -o $@

build/dev.exe: $(DEV_OBJS) | build/
	time -f "%e s   %M KB" $(CXX) $(DEVFLAGS) $(BASEFLAGS) $^ -o $@

build/debug.exe: $(DEBUG_OBJS) | build/
	time -f "%e s   %M KB" $(CXX) $(DEBUGFLAGS) $(BASEFLAGS) $^ -o $@

# ----- Compilation -----

obj/release/%.o: code/%.cpp | obj/release/
	time -f "%e s   %M KB" $(CXX) $(RELEASEFLAGS) $(BASEFLAGS) -c $< -o $@

obj/dev/%.o: code/%.cpp | obj/dev/
	time -f "%e s   %M KB" $(CXX) $(DEVFLAGS) $(BASEFLAGS) -c $< -o $@

obj/debug/%.o: code/%.cpp | obj/debug/
	time -f "%e s   %M KB" $(CXX) $(DEBUGFLAGS) $(BASEFLAGS) -c $< -o $@

# ----- Directories -----

dirs: build/ obj/release/ obj/dev/ obj/debug/

build/:
	mkdir -p build

obj/release/:
	mkdir -p obj/release

obj/dev/:
	mkdir -p obj/dev

obj/debug/:
	mkdir -p obj/debug

# ----- Tools -----

lizard:
	@lizard code/ -C20 -a7

lizard_w:
	@lizard code/ -C20 -a7 -w

# ----- Cleanup -----

clean:
	rm -f obj/debug/*.o obj/release/*.o build/*.exe
