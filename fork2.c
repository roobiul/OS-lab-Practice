#include <stdio.h>
#include <unistd.h>
#include <string.h>
//Inter-Process Communication using fork()
int main() {
    char paragraph[500];
    pid_t pid = fork();

    if (pid > 0) { // Parent Process
        printf("Parent: Enter a paragraph:\n");
        scanf(" %[^\n]s", paragraph); // Read until newline
        printf("Parent: Input received.\n");
    } else if (pid == 0) { // Child Process
        sleep(1); // Wait for parent to input
        printf("\nChild: The parent process has received the input.\n");
    }
    return 0;
}