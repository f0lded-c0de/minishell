#include "minishell.h"

const char *type_to_str(t_tkn_type type)
{
	static const char *names[] = {
		"WORD", "PIPE", "OR", "AND",
		"RED_IN", "RED_OUT", "HEREDOC", "APP_OUT",
		"PAR_OPEN", "PAR_CLOSE"
	};

	if (type >= 0 && type <= PAR_CLOSE)
		return names[type];
	else
		return "UNKNOWN";
}

void print_token_list(t_tkn *head)
{
	while (head)
	{
		printf("Type : [%s]     Token: [%s]\n", type_to_str(head->type), head->str);
		head = head->next;
	}
}

void run_test(const char *input)
{
	printf("Input : \"%s\"\n", input);
	t_tkn *tokens = tokeniser((char *)input);
	print_token_list(tokens);
	printf("----\n");
	tkn_free(tokens);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	run_test("cd c(s)>f(dfj) || (fjd)<<eof (ks | dfh \"fhdslk )fjd\" )(djf ' fdkj \" (fjdk ') || (ddfjk)&&(jf) ");
	/* run_test("df( ')word' ) | test"); */
	/* run_test("< Makefile > outfile");                                      // Empty input */
	/* run_test("echo|tjek|ls");                                  // Single word */
	/* run_test("   ");                                   // Only spaces */
	/* run_test("ls -la /home/user");                     // Normal command */
	/* run_test("cat < infile > outfile");                // Redirections */
	/* run_test("echo hello | grep h");                   // Pipe */
	/* run_test("echo \"quoted string with $dollar\"");   // Double quotes with $ */
	/* run_test("echo 'single quoted | not pipe'");       // Single quotes */
	/* run_test("echo \"nested 'quotes' inside\"");       // Quotes inside quotes */
	/* run_test("echo 'nested \"quotes\" inside'");       // Quotes inside quotes (inverse) */
	/* run_test("ls|grep x|wc -l");                       // Multiple pipes */
	/* run_test("echo $HOME");                            // Variable expansion */
	/* run_test("echo \"unterminated double");            // Unterminated double quote */
	/* run_test("echo 'unterminated single");             // Unterminated single quote */
	/* run_test("echo hello; ls");                        // Unsupported semicolon */
	/* run_test("echo \\$USER");                          // Escaped dollar */
	/* run_test("echo< dk <<hef >dk <d(f he'llo)' >o)utfile>>outfile2");         // Multiple redirections */
	/* run_test("echo $?");                               // Special variable */
	/* run_test("echo 'a | b' | cat");                    // Pipe in quotes */

	return 0;
}
