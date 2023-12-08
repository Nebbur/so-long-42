/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c	                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	dist_two_points(int from_y, int to_y, t_game *game)
{
	int	i;

	i = 0;
	from_y--;
	while (++from_y != to_y)
		i++;
	return (i);
}

void	player_position_onthemap(t_game *game)
{
	t_player	*p;

	p = game->player;
}

// + 1 porque o resultado de game->cl / 2 arredonda 
//para o numero acima entao eu retiro esse acrescimo;
void	aux_find_pic(t_game *game, int pic, int trigger)
{
	t_player	*p;
	int			l;

	p = game->player;
	if (trigger == 1)
		l = game->cl;
	else
		l = game->rl;
	if (game->cl % 2 != 0)
		pic = p->xy[1] + 0 - ((l * 0.5) + 1);
	else
		pic = p->xy[1] + 0 - (l * 0.5);
}

void	aux_process_map(int i, int j, t_game *game)
{
	if (game->pil < 0 || game->rl < WINDOW_HEIGHT / BPX)
		game->pil = 0;
	if (game->pic < 0 || game->cl < (WINDOW_WIDTH / BPX) - 1)
		game->pic = 0;
	if (game->rl >= game->rows)
	{
		game->rl = game->rows;
		if (game->pil < 0)
			game->pil = 0;
	}
	if (game->pil > (game->rows + 1) - game->rl)
		game->pil = (game->rows + 1) - game->rl;
	if (game->cl >= game->col)
		game->cl = game->col;
	i = -1;
	while (game->visible_map[++i])
	{
		j = -1;
		while (++j < game->cl)
			game->visible_map[i][j] = game->map[game->pil + i][game->pic + j];
		game->visible_map[i][j] = '\n';
	}
}

//(game->rl - 1 porque o rl comeca em 1 sendo que o pil comeca em 0)
void	process_map(t_game *game)
{
	t_player	*p;
	int			i;
	int			j;

	game->pic = -1;
	game->pil = -1;
	p = game->player;
	i = -1;
	if (game->rl >= WINDOW_HEIGHT / BPX)
		game->pil = p->xy[0] - ((game->rl - 1) - 3); 
	else
		game->pil = 0;
	aux_find_pic(game, game->pil, 0);
	aux_find_pic(game, game->pic, 1);
	if (game->col >= WINDOW_WIDTH / BPX && p->xy[1] > game->cl * 0.5)
	{
		game->pic = p->xy[1] - game->cl * 0.5;
		if (game->pic > game->col - game->cl)
			game->pic = game->col - game->cl;
	}
	else if (!(p->xy[1] > game->cl * 0.5))
		aux_find_pic(game, game->pic, 1);
	aux_process_map(i, j, game);
}
