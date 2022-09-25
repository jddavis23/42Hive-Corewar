/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchen <cchen@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:06:46 by cchen             #+#    #+#             */
/*   Updated: 2022/09/25 11:35:31 by caruychen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define NEWLINE "\n"
# define NEWLINE_C '\n'
# define WHITESPACE " \t\n\v\f\r"
# define TABSPACE " \t"

# include <stdbool.h>

typedef enum s_symtypes
{
	LA_unknown,
	LA_eof,
	LA_eol,
	LA_id,
	LA_num,
	LA_cmd,
	LA_com,
	LA_comma,
	LA_plus,
	LA_minus
}		t_symtypes;

typedef struct s_symbols
{
	bool		is_label;
	t_symtypes	type;
	t_vec		str;
	int			num;
}		t_symbols;

typedef struct s_lexer
{
	t_source	source;
	char		*next;
}			t_lexer;

void	lexer(t_lexer *lexer);
void	lexer_free(t_lexer *lexer);

/* Returns next symbol on the current source line. Sets errors if necessary
   and returns sym = sym.type = unknowwn if no valid symbol can be
   recognised */
void	lexer_getsym(t_lexer *lexer, t_symbols *sym);

#endif
