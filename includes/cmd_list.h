#ifndef CMD_LIST_H
# define CMD_LIST_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// enum
typedef enum	e_exec_type {
	SIMPLE,
	COMPOUND,
	PIPE_NODE,
	AND_NODE,
	OR_NODE
}	t_exec_type;

// struct
typedef struct	s_exec {
	void			*ptr;
	t_exec_type		type;
	struct s_exec	*left;
	struct s_exec	*right;
	int				fd_in;
	int				fd_out;
}					t_exec;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// tokenisation.c

#endif
