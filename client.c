#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<netdb.h>

int main(int argc, char *argv[])
{
    int socket_client, port_number,i, counter=0;
    socklen_t sizeAddr;
    struct sockaddr_in server_address;
    struct hostent *server;
    char temp, buffer[1024];
    
    if (argc < 3) {
       fprintf(stderr,"Error - Enter format(filename, hostname, port number)", argv[0]);
       exit(0);
    }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
	fprintf(stderr, "ERROR, no such host\n");
	exit(0);
    }
    bzero((char *) &server_address, sizeof(server_address));
    
    port_number = atoi(argv[2]); //accepting the port number
    
    socket_client=socket(AF_INET,SOCK_STREAM,0); //creating the socket
    
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port_number);
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);    
    //server_address.sin_addr.s_addr=inet_addr("130.191.166.3");
    
    memset(server_address.sin_zero,'\0',sizeof server_address.sin_zero); //setting the server_address socket
    
    sizeAddr= sizeof server_address;
    connect(socket_client,(struct sockaddr *) &server_address,sizeAddr);
    recv(socket_client,buffer,1024,0); //receiving connection update from server
    printf("%s",buffer);

    do
    {
	  if(counter !=0)
	    {
		printf("\nEnter Something :\n");
             }
            counter++;
           memset(buffer,0,strlen(buffer));
 
	    i=-1;
   	    do
	    {
		i++;
   		//scanf("%c",&temp);
		fread(&temp,sizeof(char),1,stdin);
		//printf("%c",temp);
		if(temp=='\n')
			break;
	        buffer[i]=temp;

	    }while(temp!='\n');
	    //printf("%s\n", buffer);
            send(socket_client,buffer,strlen(buffer),0);
            if(strcmp(buffer,"exit")==0)
		break;
            memset(buffer,0,strlen(buffer));
            recv(socket_client,buffer,1024,0);
	    printf("wait, your string is getting reversed !!\n");
            for(i=1;i<=200000000;i++);
            fwrite(&buffer,sizeof(char),strlen(buffer),stdout);
            //printf("%s\n",buffer);
	    memset(buffer,0,strlen(buffer));
    }while(1);
         return 0;
}