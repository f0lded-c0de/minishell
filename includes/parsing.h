#ifndef PARSING_H
# define PARSING_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// enum
typedef enum	e_type {
	WORD,
	PIPE,
	OR,
	AND,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APP_OUT,
	PAR_OPEN,
	PAR_CLOSE,
}	t_type;

typedef enum	e_quote {
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

// struct
typedef struct	s_tkn {
	char			*str;
	t_type			type;
	struct s_tkn	*prev;
	struct s_tkn	*next;
}					t_tkn;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// tokenisation.c
t_tkn	*tokeniser(char *str);

// tokens.c
t_tkn	*tkn_new(char *str);
void	tkn_append(t_tkn **start, t_tkn *new);
void	tkn_free(t_tkn *tokens);

// pre_check.c
int	check_unclosed(char *str);

// is_charset.c
int		is_operator(char c);
int		is_double_operator(char c);
int		is_space(char c);

#endif
