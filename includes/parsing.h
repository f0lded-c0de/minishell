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
	PIPE,
	AND,
	OR,
	PAR_OPEN,
	PAR_CLOSE
}	t_type;

typedef struct	s_token {
	char			*str;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

#endif
