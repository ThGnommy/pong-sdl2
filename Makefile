build:
	g++ -Wall -std=c++17 src/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o pong;

run:
	./pong

clean:
	rm pong