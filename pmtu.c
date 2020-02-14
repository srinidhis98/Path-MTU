#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include "structures.h"
#include "connectsock1.h"

packet_data pkt;
table obj[4];

int port, id;
int mtu = 0;
 
packet_data packing_the_packet()
{
    char arr[] = "abcdefghijklmnopqrstuvwxyz";
    strcpy(pkt.msg, arr);
    pkt.len = strlen(pkt.msg);
    pkt.dest = 1;
    pkt.src = 3;
    pkt.mtu = 0;
    return pkt;
}

void initialise_table()
{
    obj[0].src_id = 1;
    obj[0].dest_id = 2; 
    obj[0].port = 9000;

    obj[1].src_id = 2;
    obj[1].dest_id = 3;
    obj[1].port = 9001;

    obj[2].src_id = 1;
    obj[2].dest_id = 3;
    obj[2].port = 9002;

    obj[3].src_id = 3;
    obj[3].dest_id = 4;
    obj[3].port = 9003;
}

// void printtable(){
//     for(int i=0; i<3; i++){
//         printf("Source ID\t Destination ID\t Port\n%d\t %d\t\t %d\n ",obj[i].src_id, obj[i].dest_id, obj[i].port);
//     }
// }

void send_data(int sock_fd, packet_data pkt)
{   
    
    printf("The data packet to be sent has the following:\n Data:%s\t Length of data:%d\t Destination ID:%d\t Source ID:%d\t MTU:%d\n ", pkt.msg, pkt.len, pkt.dest, pkt.src, pkt.mtu);
    int sret = send(sock_fd, &pkt, sizeof(pkt), 0);
    printf("Send() ret val: %d\n", sret);

}

packet_data receive_data(int sock_fd)
{
    int rret = recv(sock_fd, &pkt, sizeof(pkt), 0);
    printf("Receive() ret val: %d\n", rret);
    return pkt;
}

void getdetails()
{
    printf("Enter details\n ID\t Port number\n");
    scanf("%d\t %d", &id, &port);
}

int getMTU()
{
    printf("Enter the MTU value:\n");
    scanf("%d", &mtu);
    return mtu;
}

int main(){
    int choice = 0;
    int sock_fd = 0;
    int sock_fd1 = 0;
    int sret = 0; 
    int rret = 0;
    int i = 0;
    initialise_table();
    //printtable();
    printf("Printing the table in Main()\n");
    for(int i=0; i<4; i++){
        printf("Source ID\t Destination ID\t Port\n%d\t %d\t\t %d\n ",obj[i].src_id, obj[i].dest_id, obj[i].port);
    }
    char arr[100]="abcdefghijklmnopqrstuvwxyz";
    getdetails();
    printf("Enter a choice:\n1. Sender\n2. A hop\n");
    scanf("%d", &choice);
    switch(choice){
    case 1:
    {
        sock_fd = connect_socket(port);
        pkt = packing_the_packet();
        send_data(sock_fd, pkt);
        printf("Receiving response....\n");
        rret = recv(sock_fd, &pkt, sizeof(pkt), 0);
        printf("Receive() ret val: %d\n", rret);
        if (pkt.mtu != 0){
            pkt = fragment_data(pkt);
            printf("Fragmented data: %s\nData length: %d\n", pkt.msg, pkt.len);
        }
        send_data(sock_fd, pkt);
        receive_data(sock_fd);
        printf("%s\n", pkt.msg);
        break;  
    }   
    case 2:
    {
        int src = 0;
        mtu = getMTU();
        printf("The MTU is %d\n", mtu);
        sock_fd = bind_socket(port);
        receive_data(sock_fd);
        if (mtu < pkt.len){
            pkt.mtu = mtu;
            send(sock_fd, &pkt, sizeof(pkt), 0);
            receive_data(sock_fd);
            printf("The data packet received has the following:\n Data:%s\t Length of data:%d\t Destination ID:%d\t Source ID: %d\t MTU: %d\n", pkt.msg, pkt.len, pkt.dest, pkt.src, pkt.mtu);
        

        }
        // receive_data(sock_fd);
        // 
        
        if (pkt.dest == id){
            printf("The data packet received has the following:\n Data:%s\t Length of data:%d\t Destination ID:%d\t Source ID: %d\t MTU: %d\n", pkt.msg, pkt.len, pkt.dest, pkt.src, pkt.mtu);
            strcpy(pkt.msg, "Packet received");
            sret = send(sock_fd, &pkt.msg, sizeof(pkt.msg), 0);
            printf("Send ret val: %d\n",sret);
        }
        else if (pkt.dest != id) {
            for(i=0; i<4; i++) {
                if /*(*/(pkt.dest == obj[i].dest_id || pkt.dest == obj[i].src_id) /*&& pkt.src == id)*/{
                    break;
                }
                // else if (pkt.dest == obj[i].dest_id && pkt.src != id) {
                //     src = pkt.src;
                //     for (int j=0; j<4; j++) {

                //     }
                // }
            }
            printf("port num is: %d\n", obj[i].port);
            sock_fd1 = connect_socket(obj[i].port);
            send_data(sock_fd1, pkt);

            receive_data(sock_fd1);
            if (pkt.mtu < mtu) {
                pkt = fragment_data(pkt);
                printf("Fragmented data: %s\nData length: %d\n", pkt.msg, pkt.len);
            }
            send_data(sock_fd1, pkt);
            printf("Receiving Response....\n");
            receive_data(sock_fd1);
            if (pkt.src != id) {
                for (i=0; i<4; i++) {
                    if(pkt.src == obj[i].src_id || pkt.src == obj[i].dest_id){
                        break;
                    }
                }
                printf("port num is: %d\n", obj[i].port);
                send(sock_fd, &pkt.msg, sizeof(pkt.msg), 0);
            }

        } 
            break; 
    }
           
    } 
    return 0;
}
