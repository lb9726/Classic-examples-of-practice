company:main.o Linklist.o logic.o ui.o boss.o manager.o salesmanager.o salesperson.o skillperson.o
	gcc main.o Linklist.o logic.o ui.o boss.o manager.o salesmanager.o salesperson.o skillperson.o -o company
main.o:main.c Linklist.h ui.h logic.h
	gcc -c main.c
Linklist.o:Linklist.c Linklist.h
	gcc -c Linklist.c
logic.o:logic.c logic.h
	gcc -c logic.c
ui.o:ui.c ui.h 
	gcc -c ui.c
boss.o:boss.c Linklist.h
	gcc -c boss.c
manager.o:manager.c Linklist.h
	gcc -c manager.c
salesmanager.o:salesmanager.c Linklist.h
	gcc -c salesmanager.c
salesperson.o:salesperson.c Linklist.h
	gcc -c salesperson.c
skillperson.o:skillperson.c Linklist.h
	gcc -c skillperson.c
$
