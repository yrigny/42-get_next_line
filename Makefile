CC = cc

CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=9999

NAME = get_next_line

NAME_B = get_next_line_bonus

CFILES = main.c \
	 get_next_line.c \
	 get_next_line_utils.c

CFILES_B = main_bonus.c \
	   get_next_line_bonus.c \
	   get_next_line_utils_bonus.c

HEADER = get_next_line.h

HEADER_B = get_next_line_bonus.h

$(NAME): $(CFILES) $(HEADER)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME)

$(NAME_B): $(CFILES_B) $(HEADER_B)
	$(CC) $(CFLAGS) $(CFILES_B) -o $(NAME_B)

all: $(NAME)

bonus: $(NAME_B)

clean:
	rm -f $(NAME) $(NAME_B)

re:	clean all

.PHONY:	all bonus clean re
