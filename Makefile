NAME		= 	libftprintf.a

LIBFT		=	libft

SRCS		=	main.c misc.c string_edition.c \
				flags/digit.c flags/dot_star.c \
				flags/minus.c flags/zero.c

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc

GFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

all: $(NAME)

$(NAME): $(OBJS)
				make -C $(LIBFT)
				cp $(LIBFT)/libft.a ./$(NAME)
				ar -rcs $(NAME) $(OBJS)

%.o: %.c
		$(CC) $(GFLAGS) -c $< -o $@ -I$(LIBFT) -I. 

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all fclean re


