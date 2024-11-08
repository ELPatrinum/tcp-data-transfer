### Project Overview:
The Secure File Transfer (SFT) application provides a streamlined way to send and receive files between devices connected over a network. Built on a client-server architecture, it uses TCP to ensure reliable data transfer.

### Key Features:
1. **File Transmission**: The client sends a specified file to the server, which saves it locally. This is done by reading the file's content in chunks and sending each chunk over the socket.
2. **Network Communication**: 
   - The client and server communicate over a TCP connection, with the server listening on a specified IP and port.
   - The client initiates the connection, sending a file to the server upon successful connection.
3. **Error Handling**: 
   - The application performs error checking for socket creation, binding, file reading, and writing.
   - It provides user-friendly error messages to troubleshoot issues with network connectivity or file handling.

### Functions:
- `ft_send_file(FILE *fp, int sockfd)`: Reads a file in chunks and sends each chunk over the network to the server.
- `ft_client()`: Sets up the client-side socket, connects to the server, and sends the specified file using `ft_send_file`.
- `ft_write_file(int sockfd)`: Receives data from the client over the socket and writes it to a new file on the server.
- `ft_server()`: Sets up the server to listen on a specified IP and port, accepts a client connection, and initiates the file-saving process by calling `ft_write_file`.

### Usage:
1. **Server**: The server application listens for incoming client connections on a specific IP and port.
2. **Client**: The client connects to the server, specifies the file to transfer, and initiates the file transfer process.

### Potential Enhancements:
To improve security and reliability, future versions could include:
- **Data encryption**: To protect files during transmission.
- **Integrity checks**: To ensure that files are received without errors.
- **Authentication**: To verify that only authorized users can send/receive files.

### Summary:
This project serves as a foundation for secure file transfers, showcasing essential networking techniques in C. It provides a functional, extendable template for building more sophisticated file transfer applications with additional security and reliability measures.
