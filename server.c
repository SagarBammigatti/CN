#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<stdlib.h>
int main()
{
    char buf[100];
    int k;
    socklen_t len;
    int n=1,i;
    int sock_desc,temp_sock_desc;
    struct sockaddr_in server,client;

    
    //printf("Enter the number of times you want to Echo: ");
    //scanf("%d",&n);

    memset(&server,0,sizeof(server)); //memset()- fills a block of memory with particular value
    memset(&client,0,sizeof(client));

    sock_desc=socket(AF_INET,SOCK_STREAM,0);
	//IPv4=AF_INET 
	//AF_INET6 = IPv6
	//SOCK_STREAM = TCP
	//SOCK_DGRAM = UDP
    if(sock_desc==-1)
    {
        printf("Error in socket creation");
        exit(1);
    }

    server.sin_family=AF_INET;
   //which contains a code for the address family. It should always be set to the symbolic constant AF_INET
    server.sin_addr.s_addr=INADDR_ANY;
	// This field contains the IP address of the host. For server code, this will always be the IP address of the machine on which the server is running, and there is a symbolic constant INADDR_ANY which gets this address. 
    server.sin_port=3002;

    k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
//binds socket to address and port no.
    if(k==-1)
    {
        printf("Error in binding");
        exit(1);
    }
while(1){
    k=listen(sock_desc,20); //20 max no. of clients
    if(k==-1)
    {
        printf("Error in listening");
        exit(1);
    }

    len=sizeof(client);//VERY IMPORTANT
    temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,&len);
    if(temp_sock_desc==-1)
    {
        printf("Error in temporary socket creation");
        exit(1);
    }


    while(1)
    {
        k=recv(temp_sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Error in receiving");
            exit(1);
        }
	//for(i=0;i<n;i++)
        //{
	printf("Message got from client is : %s",buf);
	//}
//printf("loop dne");
 	k=send(temp_sock_desc,buf,100,0);
        if(k==-1)
        {
            printf("Error in sending");
            exit(1);
        }

       // printf("\nEnter data to be send to client: ");

       // fgets(buf,100,stdin);
        if(strncmp(buf,"end",3)==0)
            break;

      //  k=send(temp_sock_desc,buf,100,0);
      //  if(k==-1)
       // {
        //    printf("Error in sending");
       //     exit(1);
      //  }
    }
}
    close(temp_sock_desc);

    exit(0);
    return 0;
}


//http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
