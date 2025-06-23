#include "minishell.h"

void print_token_list(t_tkn *head)
{
	while (head)
	{
		printf("Token: [%s]\n", head->str);
		head = head->next;
	}
}

void run_test(const char *input)
{
	printf("Input : \"%s\"\n", input);
	t_tkn *tokens = tokenisation((char *)input);
	print_token_list(tokens);
	printf("----\n");
	tkn_free(tokens);
}

int main(void)
{
	run_test("< Makefile > outfile");                                      // Empty input
	run_test("echo|tjek|ls");                                  // Single word
	run_test("   ");                                   // Only spaces
	run_test("ls -la /home/user");                     // Normal command
	run_test("cat < infile > outfile");                // Redirections
	run_test("echo hello | grep h");                   // Pipe
	run_test("echo \"quoted string with $dollar\"");   // Double quotes with $
	run_test("echo 'single quoted | not pipe'");       // Single quotes
	run_test("echo \"nested 'quotes' inside\"");       // Quotes inside quotes
	run_test("echo 'nested \"quotes\" inside'");       // Quotes inside quotes (inverse)
	run_test("ls|grep x|wc -l");                       // Multiple pipes
	run_test("echo $HOME");                            // Variable expansion
	run_test("echo \"unterminated double");            // Unterminated double quote
	run_test("echo 'unterminated single");             // Unterminated single quote
	run_test("echo hello; ls");                        // Unsupported semicolon
	run_test("echo \\$USER");                          // Escaped dollar
	run_test("echo hello >outfile>>outfile2");         // Multiple redirections
	run_test("echo $?");                               // Special variable
	run_test("echo 'a | b' | cat");                    // Pipe in quotes

	return 0;
}
