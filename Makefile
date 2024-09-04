FILES= gnl/get_next_line.c gnl/get_next_line_utils.c main.c

NAME= cub3d
CC= cc -Werror -Wall -Wextra #-g -fsanitize=address
MLX= MLX42/build/libmlx42.a -I"MLX42/include/MLX42/MLX42.h" -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
HEADER= -I"gnl/get_next_line.h"
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