/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	aux_wall_4(char **m, int r, int c, t_game *g)
{
	if (c < g->col && c > 0 && r < g->rows && ((r == 0) || \
	(r > 0 && m[r - 1][c] == '1')) && (m[r][c + 1] == '1' || c == g->col - 1) \
	&& m[r][c - 1] == '1' && m[r + 1][c - 1] != '1' && \
	((m[r + 1][c + 1] == '1' || c == g->col - 1) && m[r][c - 2] == '1')
		&& m[r + 1][c] == '1')
		draw_block((c - g->pic) * BPX, (r - g->pil) * BPX, 
			g->sprites->tr[10], g);
	else if (c < g->col - 1 && c > 0 && r < g->rows && 
		((r == 0) || (r > 0 && m[r - 1][c] == '1')) &&
		m[r][c + 1] == '1' && m[r][c - 1] == '1' && m[r + 1][c] != '1')
		draw_block((c - g->pic) * BPX,
			(r - g->pil) * BPX, g->sprites->tr[7], g);
	else if (c < g->col - 1 && c > 0 && r < g->rows && m[r][c + 1] != '1'\
	&& m[r][c - 1] != '1' && m[r][c] == '1' && m[r - 1][c] == '1' && 
	m[r + 1][c] == '1')
		draw_block((c - g->pic) * BPX,
			(r - g->pil) * BPX, g->sprites->tr[34], g);
	else
	{
		draw_block((c - g->pic) * BPX,
			(r - g->pil) * BPX, g->sprites->tr[4], g);
	}
}

static void	aux_wall_3(char **m, int r, int c, t_game *g)
{
	if (c < g->col - 1 && c > 0 && r < g->rows \
	&& m[r][c - 1] == '1' && m[r + 1][c] == '1' && m[r + 1][c + 1] != '1'\
	&& m[r + 1][c - 1] != '1')
		draw_block((c - g->pic) * BPX,
			(r - g->pil) * BPX, g->sprites->tr[16], g);
	else if (c < g->col - 1 && c > 0 && r < g->rows && ((r == 0) || \
	(r > 0 && m[r - 1][c] == '1')) && m[r][c + 1] == '1'\
	&& m[r][c - 1] == '1' && m[r + 1][c - 1] == '1' && m[r + 1][c + 1] != '1' 
		&& m[r + 1][c] == '1')
		draw_block((c - g->pic) * BPX, (r - g->pil) * BPX, 
			g->sprites->tr[9], g);
	else if (c == 0 && (r > 0 && r < g->rows && \
		c < g->col - 1 && m[r][c + 1] == '1' && m[r + 1][c + 1] != '1' && 
		m[r][c + 2] != '1' && m[r - 1][c] == '1' && m[r + 1][c] == '1'))
		draw_block((c - g->pic) * BPX, (r - g->pil) * BPX, 
			g->sprites->tr[9], g);
	else if (c == g->col - 1 && r > 0 && r < g->rows && m[r][c - 1] == '1' && \
	m[r + 1][c] == '1' && m[r + 1][c - 1] != '1')
		draw_block((c - g->pic) * BPX, (r - g->pil) * BPX, 
			g->sprites->tr[10], g);
	else
		aux_wall_4(m, r, c, g);
}

static void	aux_wall_5(char **m, int r, int c, t_game *game)
{
	if ((c == 0) && ((m[r][c + 1] != '1') || (r > 0 && r < game->rows && \
	c < game->col - 1 && m[r][c + 1] != '1' && m[r][c - 1] == '1' && \
	m[r + 1][c - 1] == '1' && m[r - 1][c] == '1' && m[r + 1][c] == '1')))
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[5], game);
	else if (r > 0 && r < game->rows && c < game->col - 1 && \
	m[r][c + 1] != '1' && m[r][c - 1] == '1' && \
	m[r - 1][c] == '1' && m[r + 1][c] != '1')
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[6], game);
	else if (r > 0 && m[r][c] == '1' && m[r - 1][c] != '1')
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[1], game);
	else
		aux_wall_3(m, r, c, game);
}

static void	aux_wall(char **m, int r, int c, t_game *game)
{
	if ((c == 0 && r == game->rows && m[r - 1][c + 1] != '1') || \
	(c < game->col - 1 && c >= 0 && r > 0 && m[r - 1][c] == '1' && \
	m[r][c + 1] == '1' && m[r - 1][c + 1] != '1'))
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[11], game);
	else if ((c == game->col - 1 && r == game->rows && \
	m[r - 1][c - 1] != '1') || (c < game->col && c > 0 && r > 0 && c > 0 && \
		m[r - 1][c] == '1' && m[r][c - 1] == '1' && m[r - 1][c - 1] != '1'))
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[12], game);
	else if (r > 0 && r < game->rows && c > 0 && c < game->col - 1 && \
	m[r][c + 1] == '1' && m[r][c - 1] != '1' && m[r - 1][c] == '1' && \
	m[r + 1][c] != '1')
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[8], game);
	else if (c > 0 && m[r][c - 1] != '1' && ((m[r][c + 1] == '1') || \
	c == game->col - 1))
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[3], game);
	else
		aux_wall_5(m, r, c, game);
}

void	wall(t_game *game)
{
	char	**m;
	int		r;
	int		c;

	m = game->map;
	r = -1;
	scroll(game);
	while (m[++r])
	{
		c = -1;
		while (m[r][++c])
		{
			if (m[r][c] == '1')
			{
				aux_wall(m, r, c, game);
				aux_wall_2(m, r, c, game);
			}
			else if (c < game->col && m[r][c] == 'E')
				draw_block((c - game->pic) * BPX,
					(r - game->pil) * BPX, game->sprites->gt[0],
					game);
		}
	}
}
