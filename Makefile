main: main.cpp
	g++ --std=c++17 defs.cpp scanner.cpp -o main main.cpp

o: main.cpp
	g++ --std=c++17 defs.cpp scanner.cpp -o main main.cpp

clean: 
	rm main
