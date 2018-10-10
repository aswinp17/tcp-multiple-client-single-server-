#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include <arpa/inet.h>
#include <string.h>
#define SERV_TCP_PORT 4000
int sockfd;
struct sockaddr_in serv_addr;
struct hostent *server;

struct messagebuffer{

char header[50];
char body[50];
char username[50];
}message;

void * clientsetup(char *name) {
       int sockfd;
       struct sockaddr_in serv_addr;
       struct hostent *server;
       //char buffer[4096];
       sockfd=socket(AF_INET,SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
       serv_addr.sin_port=htons(SERV_TCP_PORT);
       printf("\nReady for sending...");
       connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       strcpy(message.header,"logout");

  char ch;
  int i;
  int n = 0;
  printf("\nClient: ");
  printf("\nEnter  \n1)login\n2)logout\n ");
  scanf("%d",&i);
  strcpy(message.username,name);  
   
  if( i == 1) {
     strcpy(message.header,"login");
     send(sockfd,&message,sizeof(message),0);
     //sleep(1);
     recv(sockfd,&message,sizeof(message),0);
     //sleep(1);
     if(strcmp(message.header,"sendmessage") == 0)
          n = 1; 
     while(n){
         
        
       
          printf("\n%s enter message:  ",name);
          scanf(" %[^\t\n]s",message.body);
          send(sockfd,&message,sizeof(message),0);
          sleep(2);
          recv(sockfd,&message,sizeof(message),0);   
          printf("\nServerecho:  %s",message.body);
          
          printf("\n do you want to logout? ::: (y/n)");
          
          scanf("%s",&ch);
          
          if(ch == 'y' || ch == 'Y') {
             n = 0;
             strcpy(message.header,"logout");
             send(sockfd,&message,sizeof(message),0);
             close(sockfd);
             printf("\n ****logged out***");
             exit(0);
             }
     }
    }
    else {
         printf("\n ****logged out***");
         exit(0);    
    } 

}

int main(int argc,char*argv[])
{
     if(argc < 2) {
       printf("\n usage %s username\n",argv[0]);
       exit(0);
        }  
      
     clientsetup(argv[1]);
    //   messaging();
     
       return 0;
}

