//tcp client workflow : socket create--> connect--> recv-->close the socket


#include<stdio.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<limits.h>
#include<netinet/in.h> 

struct packet{
    char msg[200];
    int mtu;
};

int connectSocket(){
    int sock= socket(AF_INET,SOCK_STREAM,0); 
    printf("%d",sock);

    struct sockaddr_in server_address;
    server_address.sin_family =AF_INET;
    server_address.sin_port = htons(9005);
    server_address.sin_addr.s_addr = INADDR_ANY; 
    

    int con_stats= connect(sock,(struct sockaddr *)&server_address, sizeof(server_address)); 
    if(con_stats==-1){
        printf("unsuccessful connection establishment");
    }
    return sock;
}


int main(){
    
    
    int valread;
    char client_welcome[1000]="Hello from client.Send me the MTU";
    char server_msg[1000]={0};
    int pmtu=INT_MIN;
    int mtu1[2];
    int i;
    int mtuC=15;
    
    //char buff[1024];
    struct packet pkt;

    int sock=connectSocket();

    int s=send(sock,client_welcome,sizeof(client_welcome),0);
   // printf("%d sent....:)\n", s);
    if(read(sock,(struct packet *)&pkt,sizeof(pkt))<0){
        printf("Error in receivinig packet");
    }else{
        printf("The received string :%s\n",pkt.msg);
        printf("MTU of server is %d\n",pkt.mtu);
        

    }


     
    
    
    mtu1[0]=mtuC;
    mtu1[1]=pkt.mtu;
    
    
    

    if(mtu1[0]<mtu1[1]){
        pmtu=mtu1[0];

    }
    else{
        pmtu=mtu1[1];
    }
    printf("Path mtu is %d\n",pmtu);
    
   
  
    close(sock);




    return 0;
}