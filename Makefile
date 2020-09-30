all: johnny_kash

johnny_kash: main.o prompt.o cd.o pwd.o echo.o ls.o pinfo.o exec.o bg.o fg.o kjob.o handlers.o
	gcc main.o prompt.o cd.o pwd.o echo.o ls.o pinfo.o exec.o bg.o fg.o kjob.o handlers.o -o johnny_kash

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

exec.o: exec.c exec.h 
	gcc -c exec.c

bg.o: bg.c bg.h 
	gcc -c bg.c

kjob.o: kjob.c kjob.h 
	gcc -c kjob.c

fg.o: fg.c fg.h 
	gcc -c fg.c

handlers.o: handlers.c handlers.h 
	gcc -c handlers.c	
# run: *.c
# 	gcc -o run *.c
