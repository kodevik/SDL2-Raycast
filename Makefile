all:
	g++ main.cpp src/include/engine.cpp src/include/levelmap.cpp src/include/player.cpp -o main -Isrc/include -Lsrc/lib -Lsrc/bin -lmingw32 -lSDL2main -lSDL2