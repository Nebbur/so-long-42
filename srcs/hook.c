/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	keydown_hook(int keycode, game_data *game)
{
	set_action(keycode, game);
	return (0);
}

int	keyup_hook(int keycode, game_data *game)
{
	if (keycode != 53 && keycode != 65307)
		unset_action(keycode, game);
	else
		close_hook(0, game);
	return (0);
}

int	close_hook(int keycode, game_data *game)
{
	if (keycode == 0)
		mlx_loop_end(game->mlx);
	return (0);
}

void	hook_register(game_data *game)
{
	mlx_hook(game->mlx_win, 17, 1L << 0, close_hook, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, keydown_hook, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, keyup_hook, game);
}
