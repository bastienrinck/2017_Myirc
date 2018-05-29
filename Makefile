##
## EPITECH PROJECT, 2018
## irc
## File description:
## Makefile
##

NAME	= irc

SRV	= server

CLI	= client

RM	= rm -f

all: $(NAME)

$(NAME): client server

server:
	$(MAKE) -C srv && mv srv/server .

client:
	$(MAKE) -C cli && mv cli/Gui ./$(CLI)

clean:
	$(MAKE) -C srv clean
	$(MAKE) -C cli clean

fclean: clean
	$(RM) $(SRV) $(CLI)

re: fclean all

.PHONY: all clean fclean re
