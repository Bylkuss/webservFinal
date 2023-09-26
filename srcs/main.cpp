/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmorneau <jmorneau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:22:29 by dluna-lo          #+#    #+#             */
/*   Updated: 2023/08/09 14:58:57 by jmorneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Parsing.hpp"
#include "request/Req.hpp"


std::vector<std::pair<std::string, std::string> > Req::mime;

void Req::innitMime(void)
{
	std::string list(".aac audio/aac .abw application/x-abiword .arc application/octet-stream .avi video/x-msvideo .azw application/vnd.amazon.ebook .bin application/octet-stream .bmp image/bmp .bz application/x-bzip .bz2 application/x-bzip2 .csh application/x-csh .css text/css .csv text/csv .doc application/msword .docx application/vnd.openxmlformats-officedocument.wordprocessingml.document .eot application/vnd.ms-fontobject .epub application/epub+zip .gif image/gif .htm text/html .html text/html .ico image/x-icon .ics text/calendar .jar application/java-archive .jpeg image/jpeg .jpg image/jpeg .js application/javascript .json application/json .mid audio/midi .midi audio/midi .mpeg video/mpeg .mpkg application/vnd.apple.installer+xml .odp application/vnd.oasis.opendocument.presentation .ods application/vnd.oasis.opendocument.spreadsheet .odt application/vnd.oasis.opendocument.text .oga audio/ogg .ogv video/ogg .ogx application/ogg .otf font/otf .png image/png .pdf application/pdf .ppt application/vnd.ms-powerpoint .pptx application/vnd.openxmlformats-officedocument.presentationml.presentation .rar application/x-rar-compressed .rtf application/rtf .sh application/x-sh .svg image/svg+xml .swf application/x-shockwave-flash .tar application/x-tar .tif image/tiff .tiff image/tiff .ts application/typescript .ttf font/ttf .vsd application/vnd.visio .wav audio/x-wav .weba audio/webm .webm video/webm .webp image/webp .woff font/woff .woff2 font/woff2 .xhtml application/xhtml+xml .xls application/vnd.ms-excel .xlsx application/vnd.openxmlformats-officedocument.spreadsheetml.sheet .xml application/xml .xul application/vnd.mozilla.xul+xml .zip application/zip .3gp video/3gpp .3g2 video/3gpp2 .7z application/x-7z-compressed");
	std::vector<std::string> mf = split(list, ' ');

	for (size_t i = 0; i < mf.size(); i += 2)
		Req::mime.push_back(std::make_pair(mf[i], mf[i + 1]));
}


int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		std::cerr << "Error: only one or two input." << std::endl;
		return (1);
	}
	Parsing parsing;
	(void)parsing;
	(void)argv;

	if (argc == 2) {
		parsing.checkData(argv[1]);
		parsing.saveData(argv[1]);
		Req::innitMime();

		parsing.get_ref_server(0).initPorts();
		
		Location tmp = parsing.get_ref_server(0).get_location(0);
		
		while (1)
		{
			for (size_t i = 0 ;i < parsing.get_ref_server(0).get_listenners_size(); i++)
			{
				parsing.get_ref_server(0).get_listenners(i).run();
			}
		}
		
		// while (1) // infinite running for servers
		// 	for (size_t i = 0; i < parsing.get_server_size(); i++) // get each server
		// 		for (size_t j = 0; parsing.get_server(i).get_ports_size(); j++) // get each server's port
		// 				parsing.get_server(i).get_listenners(j).run();
				
		
		


		// AServer aserver;
		// std::vector<int> ports;
		// ports.push_back(8080);
		// ports.push_back(8081);
		// aserver.setPorts(ports);
		// // aserver.setPorts({8080, 8081});
		// aserver.start();
		
	} 
	else {
		parsing.saveData("run default");
		parsing.seeData();
	}



	
	return 0;
}

// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <cstdio>
// #include <cstdlib>
// #include <cstring>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <unistd.h>

// const int BUFFER_SIZE = 1024;

// void handleRequest(int clientSocket) {
//     char buffer[BUFFER_SIZE];

//     // Read Request from the client
//     memset(buffer, 0, BUFFER_SIZE);
//     int bytesRead = read(clientSocket, buffer, BUFFER_SIZE - 1);
//     if (bytesRead < 0) {
//         std::cerr << "Error reading from socket.\n";
//         return;
//     }

//     // Print the Request
//     std::cout << "--- Request ---\n";
//     std::cout << buffer << std::endl;

//     // Parse the Request to extract the HTTP method
//     std::istringstream RequestStream(buffer);
//     std::string httpMethod;
//     RequestStream >> httpMethod;

//     // Check the HTTP method
//     if (httpMethod == "POST") {
//         // Handle POST Request
//         std::string RequestBody;
//         std::string line;
//         while (std::getline(RequestStream, line) && line != "\r") {
//             RequestBody += line + "\n";
//         }

//         // Print the Request body
//         std::cout << "--- Request Body ---\n";
//         std::cout << RequestBody << std::endl;

//         // Prepare the response
//         std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
//         response += "<h1>POST Request Received!</h1><h1>Hello, World!</h1><h1>Hello, World!</h1>";
// 		// response += "<h1>Hello, World!</h1><pre>";
// 		response += RequestBody;
// 		// response += "</pre>"	"</body></html>";
		

//         // Send the response to the client
//         write(clientSocket, response.c_str(), response.length());
//     }
// 	else if (httpMethod == "GET") {
// 		// Handle GET Request
// 		std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
// 		response += "<h1>GET Request Received!</h1>";
// 		write(clientSocket, response.c_str(), response.length());
// 	}
// 	else {
//         // Unsupported HTTP method
//         std::string response = "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\n\r\n";
//         response += "<h1>405 Method Not Allowed</h1>";
//         write(clientSocket, response.c_str(), response.length());
//     }

//     // Close the client socket
//     close(clientSocket);
// }

// int main() {
//     int serverSocket, clientSocket;
//     struct sockaddr_in serverAddress, clientAddress;
//     socklen_t clientAddressLength;

//     // Create a socket
//     serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (serverSocket < 0) {
//         std::cerr << "Error creating socket.\n";
//         return 1;
//     }

//     // Bind the socket to a specific address and port
//     serverAddress.sin_family = AF_INET;
//     serverAddress.sin_addr.s_addr = INADDR_ANY;
//     serverAddress.sin_port = htons(8080);
//     if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
//         std::cerr << "Error binding socket.\n";
//         return 1;
//     }

//     // Listen for incoming connections
//     listen(serverSocket, 5);
//     std::cout << "Server listening on port 8080...\n";

//     while (true) {
//         // Accept a client connection
//         clientAddressLength = sizeof(clientAddress);
//         clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
//         if (clientSocket < 0) {
//             std::cerr << "Error accepting client connection.\n";
//             return 1;
//         }

//         // Handle the client Request
//         handleRequest(clientSocket);
//     }

//     // Close the server socket
//     close(serverSocket);

//     return 0;
// }
