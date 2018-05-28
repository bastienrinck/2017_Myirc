NAME	= server

CC	= gcc

RM	= rm -f

SRCS	= ./client.c \
	  ./cmd_handler.c \
	  ./commands/cmd_join.c \
	  ./commands/cmd_list.c \
	  ./commands/cmd_msg_faccept.c \
	  ./commands/cmd_msg_fsend.c \
	  ./commands/cmd_names.c \
	  ./commands/cmd_nick.c \
	  ./commands/cmd_part.c \
	  ./commands/cmd_pass.c \
	  ./commands/cmd_ping.c \
	  ./commands/cmd_privmsg.c \
	  ./commands/cmd_quit.c \
	  ./commands/cmd_server.c \
	  ./commands/cmd_unknown.c \
	  ./commands/cmd_user.c \
	  ./parser.c \
	  ./poll_handler.c \
	  ./server.c	\
	  ../shared/client_socket.c \
	  ../shared/server_socket.c \
	  ../shared/socket.c \
	  ../shared/tools.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ../include
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
