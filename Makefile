all: johnny_kash

johnny_kash: main.o prompt.o cd.o pwd.o echo.o ls.o pinfo.o
	gcc main.o prompt.o cd.o pwd.o echo.o ls.o pinfo.o -o johnny_kash

main.o: main.c
	gcc -c main.c

prompt.o: prompt.c prompt.h
	gcc -c prompt.c

cd.o: cd.c cd.h 
	gcc -c cd.c

pwd.o: pwd.c pwd.h 
	gcc -c pwd.c

echo.o: echo.c echo.h 
	gcc -c echo.c

ls.o: ls.c ls.h 
	gcc -c ls.c

pinfo.o: pinfo.c pinfo.h 
	gcc -c pinfo.c
