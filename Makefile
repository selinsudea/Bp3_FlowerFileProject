compile:program run
program:lib ana
	gcc proje1.o main.o -o program
lib:
	gcc -c proje1.c -o proje1.o
ana:
	gcc -c main.c -o main.o
run:
	program.exe