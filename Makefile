NAME=		minishell

VPATH=		src/

OBJDIR=		obj

INCDIR=		inc

SRC=		main.c


OBJ=		${addprefix ${OBJDIR}/,		\
			${SRC:.c=.o}}

INC=		${INCDIR}/pipex.h

LIB=		Libft/libft.a

CC=			cc

CFLAGS=		-Wall -Wextra -Werror

all:		${OBJDIR} ${NAME}

${NAME}:	${OBJ} ${INC}
			make -C Libft
			${CC} ${OBJ} ${LIB} -o ${NAME}

lib:
			make -C Libft

${OBJDIR}:
			mkdir -p obj

${OBJDIR}/%.o:	%.c ${INC} Makefile
			${CC} ${CFLAGS} -c $< -o $@


clean:
			rm -rf ${OBJDIR}
			make clean -C Libft

fclean:		clean
			${RM} ${NAME} libft.a
			make fclean -C Libft

re:			fclean all

.PHONY:		all clean fclean re