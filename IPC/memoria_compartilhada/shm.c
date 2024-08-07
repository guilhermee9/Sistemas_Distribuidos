#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    int segment_id;
    char* shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size = 0x6400;

    /* Alocar o segmento de memória compartilhada */
    segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    /* Acoplar o segmento de memória compartilhada */
    shared_memory = (char*) shmat(segment_id, 0, 0);
    printf("Memória compartilhada acoplada no endereço %p\n", shared_memory);

    /* Determinar o tamanho do segmento */
    shmctl(segment_id, IPC_STAT, &shmbuffer);
    segment_size = shmbuffer.shm_segsz;
    printf("Tamanho do segmento: %d\n", segment_size);

    /* Escrever uma string no segmento de memória compartilhada */
    sprintf(shared_memory, "Olá, mundo.");

    /* Desacoplar o segmento de memória compartilhada */
    shmdt(shared_memory);

    /* Reacoplar o segmento de memória compartilhada, em um diferente endereço */
    shared_memory = (char*) shmat(segment_id, (void*) 0x5000000, 0);
    printf("Memória compartilhada reacoplada no endereço %p\n", shared_memory);

    /* Imprimir a string da memória compartilhada */
    printf("%s\n", shared_memory);

    /* Desacoplar o segmento de memória compartilhada */
    shmdt(shared_memory);

    /* Desalocar o segmento de memória compartilhada */
    shmctl(segment_id, IPC_RMID, 0);

    return 0;
}
