##
##
##
##

CC		=	gcc

NAME		=	libchelpers.so

_SRCS		=	join.c \
			list.c \
			btree.c \
			print_error_and_abort.c \
			split.c \
			xfunctions.c

SRCS		=	$(addprefix src/, $(_SRCS))

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-W -Wall -Wextra
CFLAGS		+=	-g
CFLAGS		+=	-I . -I include

AR		=	ar crs
RANLIB		=	ranlib
RM		=	rm -rf

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(AR) $(NAME) $(OBJS)
			$(RANLIB) $(NAME)

clean		:
			$(RM) $(NAME)

fclean		:	clean
			$(RM) $(OBJS)

re		:	fclean all

.PHONY		:	all clean fclean re
