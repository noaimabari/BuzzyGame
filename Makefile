all: compile link

compile:
	g++ -I src/include -c BuzzyRevenge.cpp
link:
	g++ BuzzyRevenge.o -o BuzzyRevenge -L src/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio
