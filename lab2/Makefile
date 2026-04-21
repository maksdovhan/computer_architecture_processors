CC=g++
CFLAGS=-c -Wall

all: calculator_app calculator.a

calculator_app: main.o calculator.a
	$(CC) main.o calculator.a -o calculator_app

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

calculator.o: calculator.cpp
	$(CC) $(CFLAGS) calculator.cpp

calculator.a: calculator.o
	ar -rcs calculator.a calculator.o

clean:
	rm -rf *.o calculator_app calculator.a
