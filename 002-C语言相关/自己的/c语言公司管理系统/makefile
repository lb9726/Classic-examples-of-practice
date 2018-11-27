company:./o/main.o ./o/Linklist.o ./o/logic.o ./o/ui.o ./o/boss.o ./o/manager.o ./o/salesmanager.o ./o/salesperson.o ./o/skillperson.o
	gcc ./o/main.o ./o/Linklist.o ./o/logic.o ./o/ui.o ./o/boss.o ./o/manager.o ./o/salesmanager.o ./o/salesperson.o ./o/skillperson.o -o company
./o/main.o:./1/main.c ./1/Linklist.h ./1/ui.h ./1/logic.h
	gcc -c ./1/main.c
	
./o/Linklist.o:./1/Linklist.c ./1/Linklist.h
	gcc -c ./1/Linklist.c
	
./o/logic.o:./1/logic.c ./1/logic.h
	gcc -c ./1/logic.c
	
./o/ui.o:./1/ui.c ./1/ui.h 
	gcc -c ./1/ui.c
	
./o/boss.o:./1/boss.c ./1/Linklist.h
	gcc -c ./1/boss.c
	
./o/manager.o:./1/manager.c ./1/Linklist.h
	gcc -c ./1/manager.c
	
./o/salesmanager.o:./1/salesmanager.c ./1/Linklist.h
	gcc -c ./1/salesmanager.c
./o/salesperson.o:./1/salesperson.c ./1/Linklist.h
	gcc -c ./1/salesperson.c
	
./o/skillperson.o:./1/skillperson.c ./1/Linklist.h
	gcc -c ./1/skillperson.c
	mv *.o ./o
clean:
	rm ./o/*.o
$
