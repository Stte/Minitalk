NAME		= libft.a
SERVER		= server
CLIENT		= client
SERVER_BONUS	= server_bonus
CLIENT_BONUS	= client_bonus

S			= src/
I			= inc/
LIBFT_I		= libft/inc

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -I$I -I$(LIBFT_I) -L. -lft

SERVER_SRC	= $S/server.c
CLIENT_SRC	= $S/client.c
SERVER_SRC_BONUS	= $S/server_bonus.c
CLIENT_SRC_BONUS	= $S/client_bonus.c

RM			= /bin/rm -f

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $< -o server

$(CLIENT): $(CLIENT_SRC) $(LIBFT)
	$(CC) $(CFLAGS) $< -o client

$(LIBFT):
	make -C $(LIBFT_DIR)
	cp $(LIBFT) $(NAME)

clean:

fclean: clean
	make fclean -C libft
	$(RM) $(SERVER)
	$(RM) $(CLIENT)
	$(RM) libft.a
	$(RM) $(SERVER_BONUS)
	$(RM) $(CLIENT_BONUS)

re:
	@make fclean
	@make all

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(CLIENT_SRC_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $< -o client_bonus

$(SERVER_BONUS): $(SERVER_SRC_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $< -o server_bonus
