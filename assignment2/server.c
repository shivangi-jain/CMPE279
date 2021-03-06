// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>
#define PORT 80
int main(int argc, char const *argv[]) 
{ 
      
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server";
    char fd_arg[3]; 

    //Here argc[0][2] is initialised to 12. I am using this value to make  
    //sure that only child executes this code. Any value could have been   
    //used in place of 12 but as I have passed 12 in exec, I am comparing with 	   //12.
    if(argv[0][2] == 12)
    {
        int fd = argv[0][1];
        valread = read( fd , buffer, 1024); 
        printf("%s\n",buffer ); 
        send(fd, hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	return 0; 
    }    
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    // Forcefully attaching socket to the port 80
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 80
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
	
    } 

    //dropping privilege part
    int n = fork();
    //Child 
    if(n == 0)
      {
	struct passwd *privuser;
	privuser = getpwnam("nobody");
	if(privuser == NULL)
	{
	    exit(EXIT_FAILURE);
	}
	int userid = setuid(privuser->pw_uid);
	printf("%d", userid);
	
	//fd_arg is to pass the socket descripter and also to pass a reference 		//value 12 , so that it can be compared and the code designated for 		//child can be executed.
        fd_arg[0] = new_socket;
        fd_arg[1] = new_socket;
        fd_arg[2] = 12;
	execl(argv[0], fd_arg, NULL);
      }

	
    //Parent
    else if(n > 0)
      {
	printf("process id  parent is %d", n);
	//Wait for the child process to finish
	wait(NULL);
      }
    return 0; 
} 
