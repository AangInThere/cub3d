/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aclose <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:53:28 by aclose            #+#    #+#             */
/*   Updated: 2020/11/09 16:53:29 by aclose           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char *g_identifier_textures[] = {"NO", "SO", "WE", "EA", "S"};

int	parse_texture(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (ft_strncmp(line, g_identifier_textures[i]
						, ft_strlen(g_identifier_textures[i])) == 0)
		{
			line += ft_strlen(g_identifier_textures[i]);
			skip_spaces(&line);
			if (!(cub->textures[i].filepath = ft_strtrim(line, " ")))
				return (cub->error_code = MALLOC_ERROR);
			break ;
		}
		i++;
	}
	return (0);
}

int	check_formatting_texture(char *line)
{
	int		i;
	t_bool	has_a_match;

	i = 0;
	has_a_match = FALSE;
	while (i < 5)
	{
		if (ft_strncmp(line, g_identifier_textures[i]
						, ft_strlen(g_identifier_textures[i])) == 0)
		{
			has_a_match = TRUE;
			line += ft_strlen(g_identifier_textures[i]);
			break ;
		}
		i++;
	}
	if (!has_a_match || *line != ' ')
		return (FORMATTING_TEXTURE);
	skip_spaces(&line);
	if (*line == '\0')
		return (-2);
	return (0);
}

int	load_textures(t_cub *cub)
{
	int			i;
	t_texture	*current_texture;

	i = 0;
	while (i < 5)
	{
		current_texture = &cub->textures[i];
		if ((current_texture->img.img_ptr =
				mlx_xpm_file_to_image(cub->mlx_ptr
										, current_texture->filepath
										, &current_texture->width
										, &current_texture->height)) == NULL)
			return (cub->error_code = LOADING_TEXTURES);
		if ((current_texture->img.addr =
				mlx_get_data_addr(current_texture->img.img_ptr
									, &current_texture->img.bits_per_pixel
									, &current_texture->img.line_length
									, &current_texture->img.endian)) == NULL)
			return (cub->error_code = MINILIBX_ERROR);
		i++;
	}
	return (0);
}
