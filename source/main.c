/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:39:37 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/07 17:58:11 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_display_video(SDL_Renderer *renderer);


char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *my_itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}

void	ft_init_window(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Window 2D",
							SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							960, 540, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_SOFTWARE);
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	//SDL_RenderClear(renderer);
	ft_display_video(renderer);
	SDL_Delay(9000);
}

SDL_Surface	*ft_load_tga_image(char *file_name)
{
	SDL_Surface		*image;

	image = NULL;
	image = IMG_Load(file_name);
	if (!image)
		printf("Erreur dans le chargement de l'image");
	return (image);
}

void	ft_display_video(SDL_Renderer *renderer)
{
	SDL_Surface		*image;
	SDL_Texture		*texture;
	SDL_Rect 		srcrect;
	SDL_Rect 		dstrect;
	char			*file_name;
	int			i;


	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 1920;
	srcrect.h = 1080;
	dstrect.x = 0;
	dstrect.y = 0;
	dstrect.w = 960;
	dstrect.h = 540;

    char *buffer;


	buffer = malloc(sizeof(char) * 20);

	i = 0;
	SDL_Delay(900);
	while (i < 65)
	{
		buffer = my_itoa(i, buffer);
		file_name = concat(buffer, ".png");
		file_name = concat("/tmp/test_blender/", file_name);
		printf("=%s\n", file_name);
		image = ft_load_tga_image(file_name);
		texture = SDL_CreateTextureFromSurface(renderer,image);
		SDL_RenderCopy(renderer,
				texture,
				&srcrect,
				&dstrect);
		SDL_FreeSurface(image);
		SDL_RenderPresent(renderer);
	SDL_Delay(90);
		i++;
	}
}

int		main(void)
{
	ft_init_window();
	printf("Hello\n");
	return (1);
}
