NAME=		minishell

VPATH=		src/						\
			src/parsing					\
			src/utils					\
			src/exec					\
			src/b_in					\
			src/signals

OBJDIR=		obj

INCDIR=		inc

SRC=		main.c						\
			parsing.c					\
			syntax_error.c				\
			init.c						\
			tokens.c					\
			env_var.c					\
			redirection.c				\
			heredoc.c					\
			checking.c					\
			parsing_utils.c				\
			init_utils.c				\
			exec.c						\
			env.c						\
			cd.c						\
			echo.c						\
			exit.c						\
			pwd.c						\
			unset.c						\
			export.c					\
			tools.c						\
			signals.c

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