#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void sigchld_handler(int signo) {
    int status;
    pid_t child_pid = wait(&status);

    if (WIFEXITED(status)) {
        printf("Child process %d exited with status %d\n", child_pid, WEXITSTATUS(status));
    } else {
        printf("Child process %d terminated abnormally\n", child_pid);
    }
}

int main(int argc, char const *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        sleep(1);
        exit(2);
    } else if (pid > 0) {
        // Parent process
        signal(SIGCHLD, sigchld_handler); // Register SIGCHLD handler

        // Continue with parent process
        // ...

        // Sleep for a while to allow child process to finish
        sleep(2);
    }

    return 0;
}
