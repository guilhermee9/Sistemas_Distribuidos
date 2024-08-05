#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

/* Espera em um semáforo binário. Bloqueia até que o valor do semáforo seja positivo, então o decrementa em um. */
int binary_semaphore_wait(int semid) {
    struct sembuf operations[1];
    operations[0].sem_num = 0; // Usa o primeiro (e único) semáforo
    operations[0].sem_op = -1; // Decrementa em 1
    operations[0].sem_flg = SEM_UNDO; // Permite desfazer
    return semop(semid, operations, 1);
}

/* Incrementa um semáforo binário: incrementa seu valor em um. Este retorna imediatamente. */
int binary_semaphore_post(int semid) {
    struct sembuf operations[1];
    operations[0].sem_num = 0; // Usa o primeiro (e único) semáforo
    operations[0].sem_op = 1; // Incrementa em 1
    operations[0].sem_flg = SEM_UNDO; // Permite desfazer
    return semop(semid, operations, 1);
}

int main() {
    key_t key = 1234; // Chave para o semáforo
    int semid = semget(key, 1, 0666);
    if (semid == -1) {
        perror("semget");
        return 1;
    }

    printf("Esperando no semáforo...\n");
    if (binary_semaphore_wait(semid) == -1) {
        perror("semop - wait");
        return 1;
    }

    printf("Dentro da seção crítica.\n");
    sleep(2); // Simula seção crítica

    if (binary_semaphore_post(semid) == -1) {
        perror("semop - post");
        return 1;
    }
    printf("Semáforo liberado.\n");

    return 0;
}
