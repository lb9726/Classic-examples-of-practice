MAIN:=main
OBJECT:= main.o company.o
CC:=g++
OPTION:=-g -Wall -L/usr/lib/mysql -lmysqlclient -Wunused-result

$(MAIN):$(OBJECT)
		$(CC) $^ $(OPTION) -o $@ $(OPTION)

%.o:%.c
		$(CC) -c $< -o $@ $(OPTION)

clean:
		rm -rvf $(MAIN) $(OBJECT)
