UNAME=$(shell uname)

ifeq ($(UNAME), Linux)
	LIBRARY=-lpthread
endif
ifeq ($(UNAME), Darwin)
	LIBRARY=-Wall -Wextra -Werror
endif
NAME=philo
CC=clang
CFLAGS= -Wall -Wextra -Werror
RM=rm -f 
HEADER=include

SRCS= source/mutex.c \
	source/parsing.c \
	source/philo.c 

OBJS= $(SRCS:.c=.o)

%.o : %.c 
	@$(CC) $(CFLAGS) -I$(HEADER) $< -c  -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) $(LIBRARY) -o $@

clean : 
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
