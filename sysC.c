#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<limits.h>
#include<netinet/in.h>
#include<strings.h>

int sock;

struct packet{
    char msg[200];
    int mtu;
};

int connectSocket(){
    //printf("Inside fn\n");
    sock= socket(AF_INET,SOCK_STREAM,0);
    //printf("%d",sock);
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9000);
    server_address.sin_addr.s_addr=INADDR_ANY;
    int bret=bind(sock,(struct sockaddr*)&server_address,sizeof(server_address));
    //printf("%d",bret);
    int lret=listen(sock,10);
    //printf("%d",lret);
    int client_socket;
    client_socket=accept(sock,NULL,NULL);
    //printf("%d",client_socket);
    return client_socket;
  }

int main(){
    char msg[1000]={0};
    //printf("In main\n");
    int client_socket=connectSocket();
    //printf("Returned from fn\n");
    char welcome[100]="hello i am C";

    send(client_socket,welcome,sizeof(welcome),0);
    //printf("%d",ret); 

    int valread=read(client_socket,msg,sizeof(msg));
    //printf("%d",valread);
    printf("B's msg: %s",msg);

    struct packet pkt;
    strcpy(pkt.msg,"sending msg in packet");
    pkt.mtu=120;
    printf("Sending packet\n");
    int sret=send(client_socket,(void*)&pkt,sizeof(pkt),0);
    printf("%d\t",sret);



    close(client_socket);
    return 0;
}