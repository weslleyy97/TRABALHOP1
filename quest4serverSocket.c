#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> 

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

//PROGRAMA SERVIDOR QUE GERA NÚMERO ALEATÓRIOS E ESCREVE NO SOCKET

int main(int argc, char* argv[]){
    int server_message = 0, randomNum = 1, delta, qntdNum;
    srand(time(NULL));
    //Criando o socket do servidor
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Configurando o endereço do servidor
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9004);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //Se conectando à porta configurada
    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    
    //criação do delta e da qntd de números a serem gerados
    printf("DELTA: %d\n", delta = generate_random(1,100,1));
    printf("Quantidade de números a serem enviados: %d\n", qntdNum = generate_random(1,10,1));

    listen(server_socket, 2);
    
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);
    for (int i = 0; i < qntdNum; i++){
        send(client_socket, &randomNum, sizeof(i), 0);
        randomNum = somaN(randomNum, delta);
        recv(client_socket,&server_message, sizeof(server_message), 0);
        if (server_message != 0){
            printf("É primo: %d\n",server_message);
        }
        if (i + 1 == qntdNum){
            int finalSocket = 0;
            send(client_socket, &finalSocket, sizeof(i), 0);
        }
    }        
    printf("Encerrando");
    return 0;
}