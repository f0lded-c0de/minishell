#ifndef PARSING_H
# define PARSING_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
typedef enum	e_type {
	EMPTY,
	COMMAND,
	ARG,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APP_OUT,
	AND,
	OR,
	PIPE,
	PAR_OPEN,
	PAR_CLOSE
}	t_type;

typedef struct	s_tkn {
	char			*str;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_tkn;

#endif
