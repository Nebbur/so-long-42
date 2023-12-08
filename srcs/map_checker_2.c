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

//• The map must be rectangular.
//• The map must be closed/surrounded by walls. If it’s not, 
//the program must return an error.

int	check_rows_cols(t_game *game)
{
	game->col = -1;
	while (game->map[++game->rows])
		;
	game->rows--;
	if (game->rows > 0)
		while (game->map[game->rows][++game->col] != '\0')
			;
	game->col--;
	if (game->col < 5 || game->rows < 3)
		return (1);
	return (0);
}

int	check_rectangular_map(t_game *game)
{
	int	rows;

	rows = -1;
	while (game->map[++rows])
		if (ft_strlen_get((const char *)game->map[0]) != \
		ft_strlen_get((const char *)game->map[rows]))
			return (1);
	return (0);
}

int	check_wall(t_game *game)
{
	int	col;
	int	rows;
	int	error;

	error = 0;
	col = -1;
	rows = -1;
	while (game->map[++rows])
	{
		col = -1;
		while ((rows == 0 || rows == game->rows) && ++col < game->col)
		{
			if (game->map[rows][col] != '1')
				error = 1;
		}
		if (game->map[rows][0] != '1' || game->map[rows][game->col - 1] != '1')
			error = 1;
	}
	if (error == 1)
		ft_printf("Error. Invalid wall.\n");
	return (error);
}

static void	aux_check_pce(int r_c[2], int *count, char c, \
t_game *game)
{
	int	*xy;

	xy = game->player->init_xy;
	if (c == 'E')
		xy = game->exit;
	if (game->map[r_c[0]][r_c[1]] == c)
	{
		*&xy[0] = r_c[0];
		*&xy[1] = r_c[1];
		*count += 1;
	}
}

//rows 0 - cols 1
//count player 0 - count exit 1
int	check_pce(t_game *game)
{
	int	r_c[2];
	int	cp_ce[2];

	r_c[0] = 0;
	cp_ce[0] = 0;
	cp_ce[1] = 0;
	while (game->map[++r_c[0]])
	{
		r_c[1] = 0;
		while (game->map[r_c[0]][++r_c[1]])
		{
			aux_check_pce(r_c, &cp_ce[0], 'P', game);
			aux_check_pce(r_c, &cp_ce[1], 'E', game);
			if (game->map[r_c[0]][r_c[1]] == 'C')
				game->player->col_q++;
		}
	}
	game->rows = r_c[0] - 1;
	if (cp_ce[0] != 1 || cp_ce[1] != 1)
		return (1);
	return (0);
}
