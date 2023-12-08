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

int	check_file(char *map)
{
	int	fd;
	int	error;

	error = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		error = 1;
	map = ft_strrchr(map, '.');
	if (error == 0 && !map)
		error = 1;
	if (error == 0 && ft_strncmp(map, (const char *)".ber", 4) != 0)
		error = 1;
	if (error == 1)
		ft_printf("Error.\nThe file isn't valide\n");
	close (fd);
	return (error);
}

void	ft_clearlst(t_list **lst)
{
	t_list	*temp;
	t_list	*next;

	temp = *lst;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	*lst = NULL;
}

// Função para liberar a memória associada à lista de inimigos
void	free_enemy_list(t_list *enemy_list)
{
	t_enemy	*enemy;
	t_list	*current;
	t_list	*next;

	current = enemy_list;
	while (current != NULL)
	{
		enemy = (t_enemy *)(current->content);
		free(enemy);
		next = current->next;
		free(current);
		current = next;
	}
}

void	check_null(void **pointer)
{
	if (*pointer != NULL)
	{
		free(*pointer);
		*pointer = NULL;
	}
}

void	free_to_all(t_game *game)
{
	check_null((void **)&(game->img));
	check_null((void **)&(game->player));
	check_null((void **)&(game->enemies));
	check_null((void **)&(game->coin));
	destroy_sprites(game);
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->map != NULL)
		free_map(game->map);
	if (game->visible_map != NULL)
		free_map(game->visible_map);
}
