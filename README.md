Server prints PID
Client takes two parameters:
	server PID
	string to send
Client sends a string to server
Once the string has been received, the server prints it and returns confirmation to client.

The communication between your client and your server has to be done only using
UNIX signals.
• You can only use these two signals: SIGUSR1 and SIGUSR2.
