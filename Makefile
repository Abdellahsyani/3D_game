NAME = cube

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB_DIR = libft
LIB = $(LIB_DIR)/libft.a

SRC =  raycast/draw_tex.c raycast/handle_keys.c raycast/init_game.c raycast/run_game.c raycast/calc.c raycast/walls.c parsing/pars_map.c  parsing/check_map.c parsing/check_space.c \
		parsing/fill_image.c parsing/flor_rof.c parsing/ft_valid_id.c parsing/utils.c parsing/fill_map.c main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIB):
	@make -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -Lmlx -lmlx -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIB_DIR)
	rm -f $(OBJ)

fclean: clean
	make fclean -C $(LIB_DIR) 
	rm -f $(NAME)

re: fclean all
