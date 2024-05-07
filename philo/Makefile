NAME	=	philo

CC		=	cc

FLAG	=	-Wall -Wextra -Werror -g -O3 

# SANITIZER = -fsanitize=thread

C_FILE	=	philo.c \
			parse_init.c \
			utils.c \
			utils2.c \
			checks.c \
			threads.c \
			routine.c

OBJS	=	$(C_FILE:.c=.o)

.c.o:
			$(CC) $(FLAG) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re