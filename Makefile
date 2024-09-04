FILES=	gnl/get_next_line.c gnl/get_next_line_utils.c \
		libft_utils/ft_arraylen.c libft_utils/ft_free_array.c libft_utils/ft_put.c libft_utils/ft_split.c libft_utils/ft_substr.c \

NAME= cub3d

CC= cc -Werror -Wall -Wextra #-g -fsanitize=address
HEADER= gnl/get_next_line.h include/cub3d.h

MLX= MLX42/build/libmlx42.a -I"MLX42/include/MLX42/MLX42.h" -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

RM= rm -rf
Green=\033[0;32m

.SILENT:

all :$(NAME)

$(NAME): $(FILES)
	$(CC) $(FILES) $(MLX) -o $(NAME)
	echo "$(Green)$(NAME) created"

clean:
	$(RM) $(NAME)
	echo "$(Green)Object files removed"