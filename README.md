In this commit I re-uploaded the full project with the complete implementation of the assignment. The project:
This repository contains a full implementation of Laboratory Work №4: “Process Synchronization”.

Project overview
The project demonstrates interprocess communication between multiple processes using a shared binary file as a message buffer.
Synchronization between processes is implemented to ensure correct and ordered message exchange.
The solution is implemented in C++ using WinAPI, without complex external dependencies, and fully follows the laboratory assignment requirements.

Project structure
The solution consists of two types of processes:

Receiver
Creates a binary file for message exchange.
Defines the maximum number of messages stored in the file.
Launches multiple Sender processes.
Waits for readiness signals from all Sender processes.
Processes console commands:
Read a message from the binary file.
Terminate execution.
Waits when a read command is issued while the file is empty.

Sender
Opens the shared binary file (file name is received via command line arguments).
Sends a readiness signal to the Receiver.
Processes console commands:
Send a message to the Receiver.
Terminate execution.
Waits when a write command is issued while the file is full.

Communication mechanism
Messages are transferred via a binary file.
Message length is limited to 20 characters.
Access to the file is synchronized.
Message exchange is organized as a circular FIFO queue:
Messages are read in the same order in which they were sent.
Multiple Sender processes are supported.

Key features
Interprocess synchronization.
FIFO message queue implemented via a binary file.
Blocking behavior for empty and full buffers.
Console-based control for both Sender and Receiver.
Full compliance with the original laboratory assignment.

How to run
Build the solution in Visual Studio.
Run the Receiver process.
Enter the file name and buffer size.
Enter the number of Sender processes.
Use console commands to send and read messages.
Terminate processes via console commands.
