main: main.o
	g++ -o main main.o -static

main.o: *.cpp 
	g++ -c main.cpp

run : main
	./main -h

clean:
	rm main.o main
