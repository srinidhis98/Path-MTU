#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

int connect_socket(int port)
{   printf("Port: %d", port);
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if (sock < 0) {
        printf("Sock val:%d\n",sock);
    }

    struct sockaddr_in server_add;
    server_add.sin_family = AF_INET;
    server_add.sin_port = htons(port);
    server_add.sin_addr.s_addr = INADDR_ANY;


    int con_stats = connect(sock,(struct sockaddr *)&server_add, sizeof(server_add)); 
    if (con_stats == -1) {
        printf("unsuccessful connection establishment,%d\n",errno);
        close(sock);
    }
    
    return sock;
    
}

int bind_socket(int port)
{
    //printf("In fun\n");
    printf("Port number: %d\n", port);
    int sock1 = socket(AF_INET, SOCK_STREAM, 0);
    printf("Sock connected:%d\n",sock1);
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port);
    server_address.sin_addr.s_addr=INADDR_ANY;
    int bret = bind(sock1, (struct sockaddr*)&server_address, sizeof(server_address) );
    if (bret < 0) {
        printf("Binding Val:%d\n",bret);
    }
    
    int lret=listen(sock1,10);
    if (lret  < 0) {
        printf("Listening val:%d\n",lret);
    }
    int client_socket; 
    client_socket = accept(sock1, NULL, NULL); 
    printf("Client_socket NUmber:%d\n",client_socket);
    return client_socket;    

}

packet_data fragment_data(packet_data arg1)
{
    int iter = 0;
    if (arg1.mtu != arg1.len && arg1.mtu != 0) { 
        printf("Fragmentation needed %d\n",arg1.mtu);
        for (; iter<arg1.len; iter++) {
            if (iter >=0 && iter < arg1.mtu) {

            }
            else {
                arg1.msg[iter]= '\0';
            }
        }
    }
    arg1.len = strlen(arg1.msg);
    //printf("Fragmennted data: %s\n",data);
    return arg1;
}
 
