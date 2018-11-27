SRC_client = src/client.c src/interface.c src/account.c
SRC_server = src/server.c src/account.c

TARGET_client = client
TARGET_server = server
all:
	gcc $(SRC_server) -o $(TARGET_server) -lpthread
	gcc $(SRC_client) -o $(TARGET_client)
clean:
	rm  $(TARGET_client)
	rm	$(TARGET_server)

