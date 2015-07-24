all:
	@g++ main.cpp -o main -Wall -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -pthread -lX11 -std=c++11
	@rm -f *.o
	@echo make successful...
