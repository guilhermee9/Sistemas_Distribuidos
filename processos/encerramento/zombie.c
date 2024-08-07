#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
        /* Este é o processo filho. */
        exit(0);
    } else {
        /* Este é o processo pai. Dorme por um minuto. */
        sleep(60);
    }
    return 0;
}
