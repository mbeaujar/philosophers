UNAME=$(shell uname)

CFLAGS = -Wall -Wextra -Werror

ifeq ($(UNAME), Linux)
	CFLAGS+=-lpthread
endif

NAME=philo
CC=clang
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
	@$(CC) $(CFLAGS) $(OBJS) -o $@

clean : 
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
