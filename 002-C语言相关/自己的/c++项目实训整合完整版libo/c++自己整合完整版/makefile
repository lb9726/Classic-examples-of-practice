company:main.o data.o logic.o ui.o boss.o manager.o salemanager.o saleperson.o skillperson.o
	g++ main.o data.o logic.o ui.o boss.o manager.o salemanager.o saleperson.o skillperson.o -o company -lmysqlclient
	rm *.o
main.o:main.cc data.h ui.h logic.h
	g++ -c main.cc
data.o:data.cc data.h
	g++ -c data.cc
logic.o:logic.cc logic.h
	g++ -c logic.cc
ui.o:ui.cc ui.h 
	g++ -c ui.cc
boss.o:boss.cc data.h
	g++ -c boss.cc
manager.o:manager.cc data.h
	g++ -c manager.cc
salemanager.o:salemanager.cc data.h
	g++ -c salemanager.cc
saleperson.o:saleperson.cc data.h
	g++ -c saleperson.cc
skillperson.o:skillperson.cc data.h
	g++ -c skillperson.cc
$
