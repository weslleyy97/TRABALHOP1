#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int qntd;

int generate_random(int l, int r, int count) { //Esse função gera um numero aleatório entre 0 e r
    int i;
    for (i = 0; i < count; i++) {
        int rand_num = (rand() % (r - l + 1)) + l;
    return rand_num; 
   }
}

int somaN (int nZero, int delta) { //função para atualizar o n0 de acordo com o delta calculado
    int somaTotal = nZero + delta;
    return somaTotal;
}

int testePrimo(int numTeste){ //função para calcular se o número é primo ou não, retornando 1 caso seja primo.
    int y;
    for (y = 2; y <= numTeste - 1; y++) {
        if (numTeste % y == 0)
            return 0;
    }
    return 1;

}

int main(int argc, char* argv[]){
    int fd[2];
    printf("Entre a quantidade de números a serem gerados: ");
    scanf("%d", &qntd);  //leitura da quantidade de vezes que o número deve ser calculado
    if (pipe(fd) == -1){  //abertura do pipe e teste para verificar se tudo ocorreu bem  
        printf("Um erro ocorreu durante a abertura do pipe\n");
        return 1;
    }
    int id = fork(); //fork do processo e obtenção do id tanto do pai quanto do filho
    if (id != 0){ //processo pai
       close(fd[1]); //fechamento da ponta que não será utilizada.
       int podeSerPrimo;
       for (int i = 0; i < qntd; i++) {
           read(fd[0], &podeSerPrimo, sizeof(podeSerPrimo));
           if (1 == testePrimo(podeSerPrimo)) {
               printf("É primo: %d\n", podeSerPrimo);
           };                    
        }
        read(fd[0], &podeSerPrimo, sizeof(podeSerPrimo));
        if(podeSerPrimo == 0){
            printf("\nChecagem de primos terminada.");
        }
        close(fd[0]);
    }
    if (id == -1){
        printf("Um erro ocorreu durante o fork\n");
        return 2;
    }
    if ( id == 0){ //Processo filho
        int lower = 0, upper = 100, count = 1, nInic = 1, closed = 0;
        srand(time(0)); //hora atual como semente do numero aleatório
        int randomN = generate_random(lower, upper, count);
        printf("Aleatório gerado: %d\n", randomN);
        close(fd[0]);
        for (int i = 0; i < qntd; i++) {                    
            if (nInic == 1){
                write(fd[1], &nInic, sizeof(nInic));
                nInic = somaN(nInic, randomN); 
            } else {
                write(fd[1], &nInic, sizeof(nInic));
                nInic = somaN(nInic, randomN);
            }
        }
        write(fd[1], &closed, sizeof(closed));
        close(fd[1]);
    } 
    
}
