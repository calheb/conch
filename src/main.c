#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void quit(void) {
  printf("exit\n");
  _exit(0);
}

void cd(char *path, char *cwd) {
  if (chdir(path) != 0) {
    printf("Error: cannot change directory.\n");
  } else {
    (void)getcwd(cwd, 811);
    setenv("PWD", cwd, 1);
  }
}

int main(void) {
  int max_input = 810;
  char input[811];
  const char delim[2] = " ";
  char *tokens[10];
  int token_count = 0;
  pid_t pid;
  char cwd[811];
  pid_t pids[5];
  int pid_count = 0;
  int i;

  while (1) {
    memset(input, 0, sizeof(input));
    (void)getcwd(cwd, sizeof(cwd));

    /*green text for the prompt, then  reset */
    printf("\n\x1b[32m%s$ ", cwd);
    printf("\x1b[0m");

    if (fgets(input, max_input, stdin) != NULL) {

      input[strcspn(input, "\n")] = '\0'; /* remove newline from the end */

      /* tokenize input into tokens */
      token_count = 0;
      tokens[token_count] = strtok(input, delim);
      if (tokens[token_count] == NULL)
        continue;
      token_count++;

      while (1) {
        tokens[token_count] = strtok(NULL, delim);
        if (tokens[token_count] == NULL)
          break;
        token_count++;
      }

      /* exit shell */
      if (strcmp(tokens[0], "exit") == 0)
        quit();

      /* showpid */
      if (strcmp(tokens[0], "showpid") == 0) {
        for (i = 0; i < pid_count; i++) {
          printf("%d\n", pids[i]);
        }
        continue;
      }

      /* cd */
      if (strcmp(tokens[0], "cd") == 0) {
        cd(tokens[1], cwd);
        continue;
      }

      /* command execution */
      if ((pid = fork()) == 0) { /* child: execute the command */
        execvp(tokens[0], tokens);
        printf("Error: Command could not be executed\n");
        return 1;
      } else { /* parent: wait for child to finish */
        waitpid(pid, NULL, 0);

        if (pid_count == 5) { /* full, replace the oldest pid and shift*/
          for (i = 0; i < 4; i++) {
            pids[i] = pids[i + 1];
          }
          pids[4] = pid;
        } else {
          pids[pid_count++] = pid;
        }
      }
    }
  }
  return 0;
}
