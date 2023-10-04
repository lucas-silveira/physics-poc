build/app: main.cpp
	[ -d build ] || mkdir build
	g++ -std=c++17 main.cpp -o build/app -I/usr/local/Cellar/sfml/2.6.0/include -L/usr/local/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -rf build