program: main.cpp maze.cpp game.cpp
	g++ -o maze main.cpp maze.cpp game.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -g

run: program
	./maze
