CC			= clang++

SRC			= main.cpp

CFLAGS		= -Wall -Wextra -Werror -std=c++11 -g -o

RM			= rm -rf

NAME		= a_polite_conversation

LINKS		= -lreadline

all:		$(NAME)

$(NAME):
			$(CC) $(SRC) $(LINKS) $(CFLAGS) $(NAME)

clean:
			$(RM) $(NAME).dSYM

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re