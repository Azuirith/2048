all:
	g++ -Wall -Iinclude -Llibraries -o build/main source/*.cpp -lmingw32 -lSDL2main -lSDL2dll -lSDL2_imagedll -lSDL2
	build/main.exe