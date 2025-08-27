#ifndef TOKENS_H
# define TOKENS_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// enum
typedef enum	e_quote {
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

typedef enum	e_tkn_type {
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
}	t_tkn_type;

// struct
typedef struct	s_tkn {
	char			*str;
	t_tkn_type		type;
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

// check.c
int		check_unclosed(char *str);
void	check_syntax(t_tkn **head);

// is_charset.c
int		is_operator(char c);
int		is_double_operator(char c);
int		is_space(char c);

#endif
