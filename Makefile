CC			= clang++

SRC			= main.cpp

CFLAGS		= -Wall -Wextra -Werror -g -o

RM			= rm -f

NAME		= a_polite_conversation

LINKS		= -lreadline

all:		$(NAME)

$(NAME):
			$(CC) $(SRC) $(LINKS) $(CFLAGS) $(NAME)

clean:
			$(RM)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re