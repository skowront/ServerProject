# ServerProject
This project implements a template for client - server application. </br>

## Overview
Main goal of the project is to simplify microsoft windows server - client interface to send() <-> recieve() functions so side functions are no longer required to run the application. </br>
The goal was achieved, but obviously also restricted the range this code may be used. </br>
However great advantage it gives is that from now on you may implement only application protocol layer and no longer struggle with buffers and sockets.


### Short Manual
The only important functions are in 
* server.cpp folder in server project:
  * void Server::OnDataRecieved() which handles incoming data
  * void Server::OnTick() which happens every server loop passes
* main.cpp folder in client project
  * int main() where there is the client action implementation
  
Currently there is a message communicator implemented.
