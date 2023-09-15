main: main.o
	g++ -o main main.o -static -O2 -funroll-loops

main.o: *.cpp 
	g++ -c main.cpp

run : main
	./main 4.txt output.txt

check : main

distcheck : main

clean:
	rm main.o main
