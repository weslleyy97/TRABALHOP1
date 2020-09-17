#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int estado = 1;

void handle_sigusr1(int sig){
    printf("Sinal SIGUSR1 recebido para não fazer nada...\n");
    return 1;
}

void handle_sigusr2(int sig){
    printf("Sinal SIGUSR2 recebido para não fazer nada...\n");
}

void handle_kill(int sig){
    printf("Sinal recebido, encerrar processo...\n");
    estado = 0;
}

int main(int argc, char* argv[]){
    int i = 1;
    int pidProcess = getpid();
    signal(10, handle_sigusr1);
    signal(11, handle_kill);
    signal(12, handle_sigusr2);
    while(estado == 1){
        printf("Aguardando o recebimento de um sinal...Meu ID de processo é: %d\n", pidProcess);
        sleep(10);
        }
    return 0;
}