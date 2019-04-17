#SDL
SDL_MAIN_DOWNLOAD = https://www.libsdl.org/release/SDL2-2.0.8.tar.gz
SDL_IMAGE_DOWNLOAD = https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz


NAME = doom
SRC = main.c
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Wextra -Werror


INCLUDE =	-I ./include/ \
			-I ./sdl_image/SDL2_image-2.0.3/include/  \
			-I ./sdl_main/SDL2-2.0.8/include/

DSRC = ./source/
DOBJ = ./objet/
OBJS = $(addprefix $(DOBJ), $(OBJ))
SRCS = $(addprefix $(DSRC), $(SRC))


$(DOBJ)%.o:$(DSRC)%.c
	mkdir $(DOBJ) 2> /dev/null || true
	gcc -c $< -o $@ $(INCLUDE) $(FLAG)


all: lib $(NAME) 

$(NAME): $(OBJS)
	gcc -o $(NAME) $(OBJS)


clean:
	rm -rf $(OBJS)

fclean:clean
	rm -rf $(NAME)
	#rm -rf ./sdl_main/
	#rm -rf ./sdl_image/

re:fclean $(NAME)

.PHONY: all clean fclean re lib

lib: sdl_main sdl_image

sdl_main:
	@if [ -d "./sdl_main/" ]; then \
		echo "SDL (main) ==> Nothing to be done"; \
	else \
		mkdir sdl_main && \
		echo "SDL (main) ==> Downloading SDL" && \
		cd ./sdl_main && \
		curl -s $(SDL_MAIN_DOWNLOAD) -O && \
		echo "SDL (main) ==> Compilation SDL main" && \
		tar xzf SDL2-2.0.8.tar.gz && \
		cd SDL2-2.0.8 && \
		./configure --prefix=$(shell pwd)/sdl_main/SDL2-2.0.8 > /dev/null && \
		$(MAKE) > /dev/null &&  \
		$(MAKE) install > /dev/null && \
		echo "SDL (main) ==> DONE"; \
	fi


sdl_image:
	@if [ -d "./sdl_image/" ]; then \
		echo "SDL (image) ==> Nothing to be done"; \
	else \
		mkdir sdl_image && \
		echo "SDL (image) ==> Downloading SDL image" && \
		cd ./sdl_image && \
		curl -s $(SDL_IMAGE_DOWNLOAD) -O && \
		echo "SDL (image) ==> Compilation SDL image" && \
		tar xzf SDL2_image-2.0.3.tar.gz && \
		cd SDL2_image-2.0.3 && \
		./configure --prefix=$(shell pwd)/sdl_image/SDL2_image-2.0.3 --with-sdl-prefix=$(shell pwd)/sdl_main/SDL2-2.0.8  > /dev/null && \
		$(MAKE)  > /dev/null  &&  \
		$(MAKE) install > /dev/null  && \
		echo "SDL (image) ==> DONE"; \
	fi


norme:clear
		@echo "La norme\n";
			norminette $(SRC_Dir)

exe:
		./$(NAME)

clear:
		clear

line:clear
		find ./srcs -name '*.c' | xargs wc -l

tag:
		ctags -R .
