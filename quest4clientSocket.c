#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> 

int testePrimo(int numTeste){ //função para calcular se o número é primo ou não, retornando 1 caso seja primo.
    int y;
    for (y = 2; y <= numTeste - 1; y++) {
        if (numTeste % y == 0)
            return 0;
    }
    return 1;

}

//Programa consumidor que testa se números lidos no socket são primos.


int main(int argc, char* argv[]){
    //criando socket
    int network_socket, estado = 1;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //Indicação do endereço para o socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = ntohs(9004);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //TRATAMENTO DE ERROS DURANTE A CONEXÃO COM O SOCKET
    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if (connection_status == -1){
        printf("Um erro ocorreu durante a conexão com socket.\n\n");
        return 1;
    }

    //Receber dados do servidor 
    int server_response;
    while(estado == 1){
        recv(network_socket, &server_response, sizeof(server_response), 0);
        if(testePrimo(server_response) == 1 && server_response != 0){
            printf("Enviando primo como resposta: %d\n", server_response);
            send(network_socket, &server_response, sizeof(server_response), 0);
        } else if (server_response == 0){
            estado = 0;
        } else{
            int naoPrimo = 0;
            send(network_socket, &naoPrimo, sizeof(naoPrimo), 0);
        }
        
    }
    printf("Au revoir!\n");
    close(network_socket);

    return 0;
}