/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_on_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	show_moves(t_game *game)
{
	char	*m;
	char	*debug_msg;
	int		color;

	color = 00110010 + decimal_para_binario(game->moves);
	m = ft_itoa(game->moves);
	debug_msg = ft_strjoin("MOVES: ", m);
	free (m);
	mlx_string_put(game->mlx, game->mlx_win, 30, 24, color, debug_msg);
	free (debug_msg);
}

void	show_life(t_game *game)
{
	char	*nl;
	char	*debug_msg;

	nl = ft_itoa(game->player->nl);
	debug_msg = ft_strjoin("LIFE:", nl);
	free (nl);
	mlx_string_put(game->mlx, game->mlx_win, 12, 43, 10110000, debug_msg);
	free (debug_msg);
}

void	show_coins(t_game *game)
{
	char	*c;
	char	*temp;
	char	*debug_msg;

	c = ft_itoa(game->player->col_collected);
	debug_msg = ft_strjoin("COIN:", c);
	free (c);
	c = ft_itoa(game->player->col_q);
	temp = ft_strjoin(debug_msg, "/");
	free (debug_msg);
	debug_msg = ft_strjoin(temp, c);
	free (temp);
	free (c);
	mlx_string_put(game->mlx, game->mlx_win, 52, 43, 10110000, debug_msg);
	free (debug_msg);
}

void	show_debug(t_game *game)
{
	show_moves(game);
	show_life(game);
	show_coins(game);
}

void	draw_block(int x, int y, void *sprite, t_game *game)
{
	if (x < -BPX || y < -BPX || x > WINDOW_WIDTH || y > WINDOW_HEIGHT)
		return ;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		sprite, x, y);
}
