opt = -c -Wall -Wextra 

planificateur.exe : planificateur.o 
	gcc -o planificateur.exe planificateur.o	

planificateur.o : planificateur.c 
	gcc ${opt} planificateur.c

clean : 
	rm -f planificateur.o
	rm -f planificateur.exe

all : clean planificateur.exe 