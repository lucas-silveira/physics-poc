CPPFLAGS = -Wall
CXXFLAGS = -std=c++17

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS), Linux)
    CXXFLAGS += -lsfml-graphics -lsfml-window -lsfml-system
endif

# Mac OS X
ifeq ($(detected_OS), Darwin)
    CXXFLAGS += -I/usr/local/Cellar/sfml/2.6.0/include -L/usr/local/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system
endif

all: build/app

build/app: main.cpp
	[ -d build ] || mkdir build
	g++ main.cpp -o build/app $(CPPFLAGS) $(CXXFLAGS)

clean:
	rm -rf build