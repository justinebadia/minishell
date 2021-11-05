#include "minishell.h"


int ms_find_close_quote(t_parser *parser, char quote)
{
	int	i;

	i = parser->index + 1;
	while (parser->str_line[i])
	{
		if (parser->str_line[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	ms_handle_quote(t_parser *parser)
{
	int i;
	
	i = 0;
	if (parser->state == S_QUOTE)
	{
		i = ms_find_close_quote(parser, '\'');
		if (i < 0)
			ms_error_quote(parser);
	}
	if (parser->state == D_QUOTE)
	{
		i = ms_find_close_quote(parser, '\"');
		if (i < 0)
			ms_error_quote(parser);
	}
	return (i);
}



// int	quote_counter(t_parser *parser, char quote)
// {
// 	int	i;
// 	int	quote_counter;

// 	i = parser->index - 1;
// 	quote_counter = 0;
// 	while (parser->str_line[i])
// 	{
// 		if (parser->str_line[i] == quote)
// 			quote_counter++;
// 		i++;
// 	}
// 	return (quote_counter);
// }


char *ms_remove_quote(char *str)
{
	int	i;
	int	j;
	char *temp;

	i = 0;
	j = ft_strlen(str) - 1;
	temp = ft_calloc(ft_strlen(str), sizeof(char));
	if (str[0] == '\'' || str[0] == '\"')  
		i++;
	while (i < j)
	{
		temp[i - 1] = str[i];
		i++;
	}
	return (temp);
}


bool is_quote(t_parser *parser, int i)
{
	if (parser->str_line[i] == '\'' || parser->str_line[i] == '\"')
		return (true);
	return (false);
}

bool is_quote_next(t_parser *parser, int i)
{
	if ((parser->str_line[i] == '\'' && parser->str_line[i + 1] == '\'') || 
		(parser->str_line[i] == '\"' && parser->str_line[i + 1] == '\"') || 
		(parser->str_line[i] == '\"' && parser->str_line[i + 1] == '\'') || 
		(parser->str_line[i] == '\'' && parser->str_line[i + 1] == '\"'))
		return (true);
	return (false);
}