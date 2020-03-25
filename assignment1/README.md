
Assignment 1 
Shivangi Jain (014508026)

The Assignment has 2 files namely client.c and server.c .
The starter code is a client server program. 
The server creates a socket, binds the port , listens and accepts the connection request from client.
The Server then reads the data from client and sends its own data.

Now, the task assigned is to do privilege separation. The server code has the privilege separation part added after the socket connection is 
done and before the data processing from the client. 
This is chosen as the point of privilege separation as after the socket is set up , the data needs to be accepted from the client into the buffer.
This is where the privilege needs to be reduced because we are now making access to the buffer array.
The privilege is dropped to a 'nobody' user and then the client data is processed.
