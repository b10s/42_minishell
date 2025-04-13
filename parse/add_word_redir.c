/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aenshin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:35:57 by aenshin           #+#    #+#             */
/*   Updated: 2025/04/13 19:08:19 by aenshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./parse.h"

//TODO err handle for NULL for calloc and ft_strdup
//NOTE free(*words) is enoug since char * we reuse in new_words
void	add_word(char ***words, char *w, int *wrd_cnt, int *wrd_max)
{
	char	**new_words;
	char	**words_ptr;
	int		i;

	i = 0;
	words_ptr = *words;
	if (*wrd_cnt == *wrd_max)
	{
		*wrd_max += 5;
		new_words = ft_calloc((*wrd_max + 1), sizeof(char *));
		while (words_ptr[i] != NULL)
		{
			new_words[i] = words_ptr[i];
			i++;
		}
		free(*words);
		*words = new_words;
		words_ptr = new_words;
	}
	i = 0;
	while (words_ptr[i] != NULL)
		i++;
	words_ptr[i] = ft_strdup(w);
	*wrd_cnt = *wrd_cnt + 1;
}

//TODO check null for calloc
void	add_reds(t_red ***reds, t_red *r, int *red_cnt, int *red_max)
{
	t_red	**new_reds;
	t_red	**reds_ptr;
	int		i;

	i = 0;
	reds_ptr = *reds;
	if (*red_cnt == *red_max)
	{
		(*red_max) += 5;
		new_reds = ft_calloc((*red_max) + 1, sizeof(t_red *));
		while (reds_ptr[i] != NULL)
		{
			new_reds[i] = reds_ptr[i];
			i++;
		}
		free(*reds);
		*reds = new_reds;
		reds_ptr = new_reds;
	}
	i = add_new_red(reds_ptr, r);
	if (i != 0)
		return ;
	else
		*red_cnt = *red_cnt + 1;
}

//TODO: do we want to exit on malloc allocation errors
// instead of propagating error?
// on exit we do not need to free() and take care of anythong else like
// opened files?
int	add_new_red(t_red **reds_ptr, t_red *r)
{
	int	i;

	i = 0;
	while (reds_ptr[i] != NULL)
		i++;
	reds_ptr[i] = ft_calloc(1, sizeof(t_red));
	if (reds_ptr[i] == NULL)
		exit(1);
	reds_ptr[i]->type = r->type;
	reds_ptr[i]->fname_or_delim = ft_strdup(r->fname_or_delim);
	if (reds_ptr[i]->fname_or_delim == NULL)
		return (1);
	return (0);
}
