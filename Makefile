cc = cc
CFLAGS = -Wall -Werror -Wextra

CLIENT = client
SERVER = server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

all: $(CLIENT) $(SERVER)

$(CLIENT):
	$(CC) $(CFLAGS) -o $(CLIENT) client.c

$(SERVER):
	$(CC) $(CFLAGS) -o $(SERVER) server.c

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS):
	$(CC) $(CFLAGS) -o $(CLIENT_BONUS) client_bonus.c

$(SERVER_BONUS):
	$(CC) $(CFLAGS) -o $(SERVER_BONUS) server_bonus.c

clean:
	rm -f $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

fclean : clean

re: fclean all

.PHONY: all bonus clean fclean re