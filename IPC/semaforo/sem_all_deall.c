#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

/* Devemos definir union semun nós mesmos. */
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    struct seminfo *buf;
};

/* Obtenha um ID de semáforo binário, alocando-o se necessário. */
int binary_semaphore_allocation(key_t key, int sem_flags) {
    return semget(key, 1, sem_flags);
}

/* Desalocar um semáforo binário. Todos os usuários devem ter terminado seu uso. Retorna -1 se falhar. */
int binary_semaphore_deallocate(int semid) {
    union semun ignored_argument;
    return semctl(semid, 0, IPC_RMID, ignored_argument);
}

int main() {
    key_t key = 1234; // Chave para o semáforo
    int semid = binary_semaphore_allocation(key, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        return 1;
    }
    printf("Semáforo alocado com ID: %d\n", semid);

    if (binary_semaphore_deallocate(semid) == -1) {
        perror("semctl");
        return 1;
    }
    printf("Semáforo desalocado.\n");

    return 0;
}
