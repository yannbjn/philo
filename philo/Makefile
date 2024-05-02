NAME	=	philo

CC		=	cc

FLAG	=	-Wall -Wextra -Werror -O3 -pthread

# SANITIZER = -fsanitize=thread

C_FILE	=	philo.c \
			parse_init.c \
			utils.c \
			checks.c \
			thread_utils.c \
			routine.c \
			destroy_free.c

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