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

void	aux_wall_2(char **m, int r, int c, t_game *game)
{
	if (r != 0 && c > 0 && m[r][c - 1] != '1' && r > 0 && 
		m[r][c] == '1' && m[r][c + 1] == '1' && m[r - 1][c] != '1')
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[0],
			game);
	else if (r != 0 && c < game->col - 1 && c > 0 && 
		m[r][c + 1] != '1' && m[r][c] == '1' &&
		m[r][c - 1] == '1' && m[r - 1][c] != '1')
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[2],
			game);
	else if (c < game->col - 1 && c > 0 && r > 0 && 
		m[r][c + 1] != '1' && m[r][c - 1] != '1' &&
		m[r][c] == '1' && m[r - 1][c] != '1')
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[36],
			game);
	else if (c < game->col - 1 && c > 0 && r > 0 && 
		m[r][c + 1] != '1' && m[r][c - 1] != '1' &&
		m[r][c] == '1' && m[r - 1][c] == '1' && m[r + 1][c] != '1')
		draw_block((c - game->pic) * BPX,
			(r - game->pil) * BPX, game->sprites->tr[35],
			game);
}
