NAME	= program

CC	= 

RM	= rm -f

SRCS	= 

OBJS	= $(SRCS:=.o)

CFLAGS = -I 
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME):
	$(MAKE) -C srv && mv srv/server .

server:
	$(MAKE) -C srv && mv srv/server .
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
