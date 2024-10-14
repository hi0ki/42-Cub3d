CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f
SRCS	=	gnl/get_next_line.c gnl/get_next_line_utils.c \
			libft_utils/ft_arraylen.c libft_utils/ft_free_array.c libft_utils/ft_put.c libft_utils/ft_split.c libft_utils/ft_strtrim.c\
			libft_utils/ft_substr.c libft_utils/ft_strchr.c libft_utils/_strlen.c libft_utils/_strjoin.c libft_utils/ft_atoi.c libft_utils/ft_strcmp.c\
			parsing/start_parsing.c parsing/check_map.c parsing/che_map_utils.c parsing/utils.c\
			parsing/draw_map.c parsing/move_player.c \
			raycasting/raycasting_utils.c raycasting/raycasting.c \
			main.c 

MLX 	= 	MLX42/build/libmlx42.a -I"MLX42/include/MLX42/MLX42.h" -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
HEADER	= 	gnl/get_next_line.h include/types.h include/cub3d.h  
OBJS	=	$(SRCS:.c=.o)
NAME= cub3d

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re