/**
 * The entrypoint of the homework. Every initialization must be done here
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.h"
#include "friends.h"
#include "posts.h"
#include "feed.h"

/**
 * Initializez every task based on which task we are running
*/
void init_tasks(void)
{
	#ifdef TASK_1

	#endif

	#ifdef TASK_2

	#endif

	#ifdef TASK_3

	#endif
}

/**
 * Entrypoint of the program, compiled with different defines for each task
*/
int main(void)
{
	init_users();

	init_tasks();

	retea *rt = init_retea();

	char *input = (char *)malloc(MAX_COMMAND_LEN);

	while (1) {
		char *command = fgets(input, MAX_COMMAND_LEN, stdin);

		// If fgets returns null, we reached EOF
		if (!command)
			break;

		#ifdef TASK_1
		handle_input_friends(rt, input);
		#endif

		#ifdef TASK_2
		handle_input_posts(rt, input);
		#endif

		#ifdef TASK_3
		handle_input_feed(rt, input);
		#endif
	}

	free_retea(&rt);

	free(input);
	free_users();
	return 0;
}
