#include <pthread.h>
#include <stdio.h>
/* Computa sucessivos números primos (bastante ineficientemente). Retorna o
N-ésimo número primo, onde N é o valor apontado por *ARG. */
void* compute_prime (void* arg)
{
 int candidate = 2;
 int n = *((int*) arg);
 while (1) {
 int factor;
 int is_prime = 1;
/* Testa se é primo por sucessivas divisões. */
 for (factor = 2; factor < candidate; ++factor)
 if (candidate % factor == 0) {
 is_prime = 0;
 break;
 }
/* Este é o primo que estavamos procurando? */
 if (is_prime) {
 if (--n == 0)
/* Retorna o número primo desejado como o valor de retorno da thread. */
 return (void*) candidate;
 }
 ++candidate;
 }
 return NULL;
}
int main ()
{
 pthread_t thread;
 int which_prime = 5000;
 int prime;
/* Inicie a computação da thread, até o 5000º número primo. */
pthread_create (&thread, NULL, &compute_prime, &which_prime);
/* Faça algum outro trabalho aqui... */
/* Espere a thread do número primo completar e pegue o resultado. */
 pthread_join (thread, (void*) &prime);
/* Imprima o maior número primo computado. */
printf("O %dº número primo é %d.\n", which_prime, prime);
 return 0;
}
