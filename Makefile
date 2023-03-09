NAME=		minishell

VPATH=		src/						\
			src/parsing					\
			src/exec					\
			src/b_in

OBJDIR=		obj

INCDIR=		inc

SRC=		main.c						\
			parsing.c					\
			parsing_utils.c				\
			init.c						\
			init_utils.c				\
			tokens_handler.c			\
			syntax_error.c				\
			redirection.c				\
			checking.c					\
			exec.c						\
			cd.c						\
			echo.c						\
			exit.c						\
			pwd.c						\
			unset.c						\
			export.c					\
			tools.c						\
			env.c

OBJ=		${addprefix ${OBJDIR}/,		\
			${SRC:.c=.o}}

INC=		${INCDIR}/minishell.h

LIB=		Libft/libft.a

CC=			cc

CFLAGS=		-Wall -Wextra

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