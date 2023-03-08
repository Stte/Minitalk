NAME 		= libft.a
SERVER 		= server
CLIENT		= client

S			= src/
I			= inc/
LIBFT_I		= libft/inc

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -I$I -I$(LIBFT_I) -L. -lft

SERVER_SRC	= $S/server.c
CLIENT_SRC	= $S/client.c

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

re:
	@make fclean
	@make all
