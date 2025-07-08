# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -O0

# Assembler and flags
NASM = nasm
NASMFLAGS = -f elf64 -O3

# Files
NAME = tester
SRC_C = main.c
SRC_ASM = ft_strlen.s
OBJ_C = $(SRC_C:.c=.o)
OBJ_ASM = $(SRC_ASM:.s=.o)
OBJ = $(OBJ_C) $(OBJ_ASM)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re