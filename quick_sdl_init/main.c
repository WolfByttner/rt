/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 22:11:41 by mwilk             #+#    #+#             */
/*   Updated: 2016/03/08 22:34:44 by mwilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#define WIN_X		1600
#define WIN_Y		900
#define KEB_KEY		e.key.keysym.sym

typedef struct      s_data
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Event		e;
	int				go;
}                   t_data;

static void		delay(unsigned int frameLimit)
{
	unsigned int	ticks;

	ticks = SDL_GetTicks();
	if (frameLimit < ticks)
		return ;
	if (frameLimit > ticks + 16)
		SDL_Delay(16);
	else
		SDL_Delay(frameLimit - ticks);
}

static void	draw(t_data *d)
{
	Uint32			rgb[3];
	int				x;
	int				y;

	x = -1;
	y = -1;
	rgb[0] = 50;
	SDL_RenderClear(d->rend);
	while (++y < WIN_Y)
	{
		rgb[0] += ((y + 10) * 2) % WIN_X;
		rgb[1] += ((y + 10) * 2) % WIN_X;
		rgb[2] += ((y + 10) * 2) % WIN_X;
		SDL_SetRenderDrawColor(d->rend, 0, rgb[0], rgb[1], rgb[2]);
		while (++x < WIN_X)
			SDL_RenderDrawPoint(d->rend, x, y);
		x = -1;
	}
	SDL_RenderPresent(d->rend);
	delay(1);
}


static int	init_SDL(t_data *d)
{
	(void)d;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return(-1);
	if (!(d->win = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN)))
		return (-1);
	if (!(d->rend = SDL_CreateRenderer(d->win, -1, SDL_RENDERER_ACCELERATED)))
		return (-1);
	return (0);
}

static int			clean_up(t_data *d, int ret)
{
	if (d->rend)
		SDL_DestroyRenderer(d->rend);
	if (d->win)
		SDL_DestroyWindow(d->win);
	SDL_Quit();
	return (ret);
}

static void		event(t_data *d)
{
	while (SDL_PollEvent(&d->e))
	{
		if (d->e.type == SDL_QUIT)
			d->go = 0;
		else if (d->e.type == SDL_KEYDOWN)
		{
			if (d->e.key.keysym.sym)
			{
				if (d->KEB_KEY == SDLK_ESCAPE)
					d->go = 0;
			}
		}
		break;
	}
}

int		main(int ac, char **av)
{
	t_data	d;

	(void)av;
	d.go = 1;
	if (ac == 2)
	{
		if (init_SDL(&d))
			return (clean_up(&d, -1));
		while (d.go)
		{
			event(&d);
			draw(&d);
		}
		return (clean_up(&d, 0));
	}
	return(0);
}
