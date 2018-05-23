##
## EPITECH PROJECT, 2018
## myftp
## File description:
## 
##

CC	=	gcc -g

RM	=	rm -f

NAME	=	client

SRC	=	main.c		\
		client.c

OBJ	=	$(SRC:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) -W -Wextra -Wall

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME) *.c~ *Makefile~ *.h~

re	:	fclean all
