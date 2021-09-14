NAME = philo
CC = gcc -pthread
FLAGS = 

SRCS = main.c philo_utils.c ft_free.c
OBJS = $(SRCS:.c=.o)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

all:
	@$(MAKE) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:  clean
	rm -rf $(NAME)

re: fclean all