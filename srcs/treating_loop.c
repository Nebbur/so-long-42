/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	background(game_data *game)
{
	int	rows;
	int	cols;

	rows = -1;
	while (++rows < game->rl)
	{
		cols = -1;
		while (++cols < game->cl)
		{
			if (game->visible_map[rows][cols] == '0')
			{
				draw_block(cols * BPX,
					rows * BPX, game->sprites->bg[0],
					game);
			}
		}
	}
}

void	scroll(game_data *game)
{
	char	**m;
	int		r;
	int		c;

	r = 0;
	c = 0;
	m = game->visible_map;
	if (m[0][0] == '1')
		draw_block(c * BPX, r * BPX, game->sprites->s[0], game);
	else
		draw_block(c * BPX, r * BPX, game->sprites->s[2], game);
	if (m[0][1] == '1')
		draw_block(1 * BPX, r * BPX, game->sprites->s[1], game);
	else
		draw_block(1 * BPX, r * BPX, game->sprites->s[3], game);
}

void	item(game_data *game)
{
	t_sprites	*s;
	int			c;
	int			rows;
	int			cols;

	rows = -1;
	s = game->sprites;
	if (game->coin->current_frame == 9)
		game->coin->current_frame = 0;
	c = game->coin->current_frame;
	game->cont++;
	if (game->cont > 2)
	{
		game->coin->current_frame++;
		game->cont = 0;
	}
	scroll(game);
	while (++rows < game->rl)
	{
		cols = -1;
		while (++cols <= game->cl)
			if (game->visible_map[rows][cols] == 'C')
				draw_block (cols * BPX, rows * BPX, s->c[c], game);
	}
	scroll(game);
}
