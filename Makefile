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

server:
	$(MAKE) -C srv && mv srv/server .

client:
	echo "client pas encore fait"

$(NAME): server client

clean:
	$(MAKE) -C srv clean

fclean: clean
	$(RM) $(SRV)

re: fclean all

.PHONY: all clean fclean re
