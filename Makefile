NAME = philo
 
CFILES =	Phil/forks.c Phil/create.c Phil/mon.c \
			Phil/phil.c Phil/help.c
 
BONUS =		Phil_bonus/forks.c Phil_bonus/create.c Phil_bonus/help.c \
			Phil_bonus/mon.c Phil_bonus/philosophers.c
 
OBJECTS = $(CFILES:.c=.o)
 
OBJECTS_C = $(BONUS:.c=.o)
 
CC = gcc
 
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
 
$(NAME): $(OBJECTS) Phil/phil.h $(CFILES)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
 
bonus: $(OBJECTS_C) Phil_bonus/philosophers.h $(BONUS)
	$(CC) $(CFLAGS) $(OBJECTS_C) -o philo_bonus
 
clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_C)
 
fclean: clean
	rm -f $(NAME)
	rm -f philo_bonus

re: fclean all
 
call: all clean