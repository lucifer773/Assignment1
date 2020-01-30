//tcp server workflow: socket creation-> binding the socket to the ip and port where it is should be listening to-->listening to that addresss and port--> accept the connection-->send or receive data

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>

int ssock1,sockC;

struct packet{
    char msg[200];
    int mtu;
};


int connectSocketA(){
    ssock1 = socket(AF_INET,SOCK_STREAM,0);
    //printf("%d",ssock1);
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9005);
    server_address.sin_addr.s_addr=INADDR_ANY;
    int bret=bind(ssock1,(struct sockaddr*)&server_address,sizeof(server_address) );
    //printf("%d",bret);
    int lret=listen(ssock1,10);
    //printf("%d",lret);
    int client_socket; 
    client_socket=accept(ssock1,NULL,NULL); 
    //printf("%d",client_socket);
    return client_socket;    

}


int connectSocketB(){
    //printf("In fn\n");
    sockC = socket(AF_INET,SOCK_STREAM,0);
    //printf("%d",sockC);

    struct sockaddr_in server_address1;
    server_address1.sin_family=AF_INET;
    server_address1.sin_port=htons(9000);
    server_address1.sin_addr.s_addr=INADDR_ANY;

    int con_stats= connect(sockC,(struct sockaddr *)&server_address1, sizeof(server_address1)); 
    if(con_stats==-1){
        printf("unsuccessful connection establishment");
    }
    return sockC;
    
}

int main(){
    
    char client_msg[1000]={0};
    char welcome[1000]="i am B";
    int valread;
    char buff[1024];
    
    // printf("In main\n");
    
    // printf("Returned from main\n");
    struct packet pkt,pkt1;
    printf("ENter data\n");
    scanf("%[^\n]s",pkt.msg);
    printf("%s",pkt.msg);
    pkt.mtu=100;
    
    int client_socket1=connectSocketA();
    valread=read(client_socket1,client_msg,1000);
   // printf("%d",valread);
    printf("Client's msg: %s\n",client_msg);
    printf("MTU of mine: %d",pkt.mtu);
    send(client_socket1,(void*)&pkt,sizeof(pkt),0);

    printf("Connecting with C\n");
    int client_socket2=connectSocketB();
    valread=read(client_socket2,client_msg,1000);
    printf("C's msg: %s",client_msg);
    int sret=send(client_socket2,welcome,sizeof(welcome),0);
    printf("%d",sret);

    if(read(client_socket2,(struct packet *)&pkt1,sizeof(pkt1))<0){
        printf("Error in receivinig packet");
    }else{
        printf("The received string :%s\n",pkt1.msg);
        printf("Received mtu is %d\n",pkt1.mtu);
        

    }




   
    close(ssock1); 
    close(client_socket2);
    
    return 0;

}