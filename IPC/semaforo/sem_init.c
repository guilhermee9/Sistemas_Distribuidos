#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/* Devemos definir union semun nós mesmos. */
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *buf;
};

/* Inicializar um semáforo binário com o valor de um. */
int binary_semaphore_initialize(int semid) {
    union semun argument;
    unsigned short values[1];
    values[0] = 1;
    argument.array = values;
    return semctl(semid, 0, SETALL, argument);
}

int main() {
    key_t key = 1234; // Chave para o semáforo
    int semid = semget(key, 1, 0666);
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    if (binary_semaphore_initialize(semid) == -1) {
        perror("semctl");
        return 1;
    }
    printf("Semáforo inicializado.\n");

    return 0;
}
