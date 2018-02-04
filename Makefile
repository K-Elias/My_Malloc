CC	=	gcc

NAME	= 	libmy_malloc.so

FILE	=	src/malloc.c 		\
		src/addlist.c		\
	  	src/tools.c		\
		src/init.c

OBJ	= 	$(FILE:.c=.o)

CFLAGS	+= 	-fpic -W -Wall -Wextra -Werror -I./include -lpthread

LIB	+=	 -shared

RM	= 	rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(LIB) $(OBJ)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
