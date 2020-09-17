#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]){
    int pidNumber;
    int signal, result, pidInt;
    printf("Entre com o n do processo: ");
    scanf("%d", &pidNumber);
    printf("Qual sinal deve ser enviado ao processo: ");
    scanf("%d", &signal);
    result = kill(pidNumber, signal);
    if (errno == EINVAL ){ //erros retirados da documentação da função kill
        printf("An invalid signal was specified.\n");
    }
    if (errno == EPERM){ 
        printf("The calling process does not have permission to send the signal to any of the target processes.\n");
    } 
    if (errno == ESRCH) {
        printf("The target process or process group does not exist. \n");
    }  
    if (result == -1){
        printf("Não foi possivel enviar o sinal ao numero de processo informado.");
        return 1; 
    } else {
        kill(pidNumber, signal);
        printf("Sinal %d enviado ao processo %d.", signal, pidNumber);
    }
    return 0;
}