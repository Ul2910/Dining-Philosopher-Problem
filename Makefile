NAME	= philo

SRCS	= philo.c helpers.c starter.c time_and_death.c cycle.c death_or_forks.c eat_sleep_think.c

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Wextra -Werror

%.o: %.c philo.h
	gcc -c ${CFLAGS} -I . $< -o ${<:.c=.o}

${NAME}: ${OBJS} philo.h
	ar rc libphilo.a ${OBJS}
	ranlib libphilo.a
	gcc ${CFLAGS} ${OBJS} -L. -lphilo -lpthread -o ${NAME}

all:	${NAME}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME} libphilo.a

re: fclean all

.PHONY:	all fclean clean re bonus








