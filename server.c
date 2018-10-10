#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#define SERV_TCP_PORT 4000
int sockfd,newsockfd,clength;
struct sockaddr_in serv_addr,cli_addr;

struct messagebuffer{

char header[50];
char body[50];
char username[50];
}message;


void serversetup() {

       int sockfd,newsockfd,clength;
       struct sockaddr_in serv_addr,cli_addr;
       //char buffer[4096];
       sockfd = socket(AF_INET,SOCK_STREAM,0);
       serv_addr.sin_family= AF_INET;
       serv_addr.sin_addr.s_addr= INADDR_ANY;
       serv_addr.sin_port=htons(SERV_TCP_PORT);
       printf("\nStart");
       bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       printf("\nListening...");
       printf("\n");
       listen(sockfd,5);
       clength=sizeof(cli_addr);
       int pid;
       

       while(1) {
       newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
       //printf("\nAccepted");
       printf("\n");
        if (newsockfd < 0)
              error("ERROR on accept");
            pid = fork();
        if (pid < 0) {
              error("ERROR in new process creation");
            }
      if (pid == 0) { 
        int n = 0;       
      
        recv(newsockfd,&message,sizeof(message),0);
        if( strcmp(message.header,"login") == 0) {
            n = 1;
            strcpy(message.header,"sendmessage");
            strcpy(message.body ,"logged in ");
            send(newsockfd,&message,sizeof(message),0);
           }     
        while(n) {
               
             recv(newsockfd,&message,sizeof(message),0);
             
             if(strcmp(message.header,"sendmessage") == 0){ 
           
                 printf("\n%s :%s",message.username,message.body); 
                 printf("\n enter msg to %s :",message.username);
                 scanf("  %[^\t\n]s", message.body);
                 send(newsockfd,&message,sizeof(message),0);
              }   
              else if(strcmp(message.header,"logout") == 0){
                  close(newsockfd);
                  exit(0);
                }
             else
               ;         
           }
      } 
      else
         close(newsockfd);
     }
}               
    
  


int main(int argc,char**argv)
{
    

 serversetup();
 //servermessaging();
 
      
}
