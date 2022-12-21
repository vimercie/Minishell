NAME=		minishell

VPATH=		src/						\
			src/parsing					\
			src/exec

OBJDIR=		obj

INCDIR=		inc

SRC=		main.c						\
			init.c						\
			parsing.c					\
			parsing_utils.c				\
			exec.c


OBJ=		${addprefix ${OBJDIR}/,		\
			${SRC:.c=.o}}

INC=		${INCDIR}/minishell.h

LIB=		Libft/libft.a

CC=			cc

CFLAGS=		-Wall -Wextra -Werror

all:		${OBJDIR} ${NAME}

${NAME}:	${OBJ} ${INC}
			make -C Libft
			${CC} ${OBJ} ${LIB} -lreadline -o ${NAME}

lib:
			make -C Libft

${OBJDIR}:
			mkdir -p obj

${OBJDIR}/%.o:	%.c ${INC} Makefile
			${CC} ${CFLAGS} -c $< -o $@


clean:
			make clean -C Libft
			rm -rf ${OBJDIR}

fclean:		clean
			make fclean -C Libft
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re