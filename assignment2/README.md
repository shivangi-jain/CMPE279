This assignments uses fork + exec. fork + exec is used to create randomisation of address space layout in child and thus helps in thwarting attacks.

In server.c, a connection is accepted from the client. After this,  fork is done to create child and parent. The child drops the privilge and then calls the exec function. The socket descripter is passed so that child and parent can communicate.
Finally the child serves the request from client and console output shows that. 

