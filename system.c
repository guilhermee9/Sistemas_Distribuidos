/********************************************************
* Faz parte da biblioteca padrão do C                   *
* Fácil de usar                                         *
* Cria um subprocesso rodando o shell padrão e passa o  *
* comando ao novo shell para execução
*********************************************************/

#include <stdlib.h>

int main ()
{
int return_value;
return_value = system ("ls -l /");
return return_value;
} 