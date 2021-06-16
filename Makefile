NAME=philo
CC=clang
CFLAGS= -Wall -Wextra -Werror
RM=rm -f 
HEADER=include

SRCS= source/init.c \
	source/main.c \
	source/mutex.c \
	source/gestion.c

OBJS= $(SRCS:.c=.o)

%.o : %.c 
	@$(CC) $(CFLAGS) -I$(HEADER) $< -c  -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(OBJS) -o $@

clean : 
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all