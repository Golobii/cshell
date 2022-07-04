#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
  int fd[2];
  pipe(fd);

  char *buf = "echo y";
  write(fd[1], buf, sizeof buf);

  close(fd[1]);
  pid_t id;
  id = fork();

  if (id == 0) {
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    close(fd[0]);
    execlp("/bin/sh", "", NULL);
    exit(0);
  }

  // getchar();
  waitpid(id, NULL, 0);

  /* id = fork();
  if (id == 0) {
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    execlp("cowsay", "");
    return 0;
  }
  */
  // waitpid(id, &status, 0);
  return 0;
}
