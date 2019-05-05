#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>

void *connectionHandler(void *sock)
{
    int socket_new = *(int*)sock;
    int read_size,i,k,len;
    char str[1024] , buffer[1024];
    //printf("I am your connection handler\n");
    strcpy(buffer, "Enter Something: \n");
    send(socket_new,buffer,strlen(buffer),0);

    do
    {
            memset(buffer,0,strlen(buffer));
            recv(socket_new,buffer,1024,0);
            if(strcmp(buffer,"exit")==0)
                    break;
            printf("%s\n",buffer);
            len=strlen(buffer);
            k=len-1;
            for(i=0;i<len;i++)
            {
                    str[i]=buffer[k];            
                    k--;
    }
        
        send(socket_new,str,strlen(str),0);
       for(i=0;i<len;i++)
        str[i]= '\0';
    }while(strcmp(buffer,"exit")!=0);
    
    close(socket_new);
}


int main(int argc, char *argv[])
{
    int socket_server, socket_new, port_number, threadValue;
    char buffer[1024];
    char str[1024];
    int len,k,i;
    struct sockaddr_in server_address;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    if (argc < 2) 
    {
       fprintf(stderr,"Error - Enter format(filename, port number)\n", argv[0]);
       exit(0);
    }
    port_number = atoi(argv[1]);

    socket_server= socket(AF_INET,SOCK_STREAM,0);
    
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(port_number);
    server_address.sin_addr.s_addr=inet_addr("130.191.166.3");
    //memset(server_address.sin_zero,'\0',sizeof server_address.sin_zero);
    
    bind (socket_server, (struct sockaddr*)&server_address, sizeof(server_address));


    if(listen(socket_server,5)==0)
            printf("Listening!\n");


    else
            printf("Error\n");


    addr_size= sizeof serverStorage;
    //socket_new=accept(socket_server,(struct sockaddr*)&serverStorage,&addr_size);
    //strcpy(buffer,"\nEnter string you want reversed or type exit: \n");
    //send(socket_new,buffer,strlen(buffer),0);
    
    pthread_t tid;
   
    while( (socket_new = accept(socket_server, (struct sockaddr*)&serverStorage, &addr_size)) )
    {
        printf("Connection accepted\n");
        //threadValue = pthread_create(&tid, NULL, myThreadFun, NULL);
    threadValue = pthread_create( &tid , NULL , connectionHandler , (void *)&socket_new);
    //printf("%i\n",pthread_self());
    //threadValue = pthread_join(tid, NULL);
    //printf("%i\n",threadValue);

        printf("Handler assigned\n");
    }


    return 0;
}