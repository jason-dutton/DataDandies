main: main.o
	g++ -o main main.o -static

main.o: *.cpp 
	g++ -c main.cpp

run : main
	./main

check : main

distcheck : main

clean:
	rm main.o main
