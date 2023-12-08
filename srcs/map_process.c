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

// + 1 porque o resultado de game->cl / 2 arredonda 
//para o numero acima entao eu retiro esse acrescimo;

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
	j = -1;
	if (game->rl >= WINDOW_HEIGHT / BPX)
		game->pil = p->xy[0] - ((game->rl - 1) - 3); 
	else
		game->pil = 0;
	if (game->col >= WINDOW_WIDTH / BPX && p->xy[1] > game->cl * 0.5)
	{
		game->pic = p->xy[1] - game->cl * 0.5;
		if (game->pic > game->col - game->cl)
			game->pic = game->col - game->cl;
	}
	aux_process_map(i, j, game);
}
