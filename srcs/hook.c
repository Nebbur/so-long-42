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

int	keydown_hook(int keycode, t_game *game)
{
	set_action(keycode, game);
	return (0);
}

int	keyup_hook(int keycode, t_game *game)
{
	if (keycode != 53 && keycode != 65307)
		unset_action(keycode, game);
	else
		close_hook(0, game);
	return (0);
}

int	close_hook(int keycode, t_game *game)
{
	ft_printf("keycode: %i\n", keycode);
	if (keycode == 0)
	{
		ft_printf("---------------------------------DEU FREE--------------------------------------------------------\n\n\n\n\n");
		free_to_all(game);
	}
	if (keycode == -16778064)
	{
		ft_printf("---------------------------------KEYCODE -1677--------------------------------------------------------\n\n\n\n\n");
		free_to_all(game);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

void	hook_register(t_game *game)
{
	mlx_hook(game->mlx_win, 17, 1L << 17, close_hook, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, keydown_hook, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, keyup_hook, game);
}
