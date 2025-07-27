# Networking Lab Programs in C

This repository contains a collection of fundamental networking concepts implemented in the C programming language. Each program is organized into its own directory and demonstrates a specific protocol, algorithm, or client-server architecture.

## Table of Contents

1.  [Client-Server Communication](#1-client-server-communication)
    * [TCP Client-Server](#client-server-tcp)
    * [UDP Client-Server](#client-server-udp)
    * [Concurrent Time Server (TCP)](#concurrent-time-server)
    * [File Server (TCP)](#file-server)
    * [Chat Server (TCP)](#chat-server)
2.  [Sliding Window Protocols](#2-sliding-window-protocols)
    * [Stop-and-Wait](#stop-n-wait)
    * [Go-Back-N](#go-back-n)
    * [Selective Repeat](#selective-repeat)
3.  [Routing Algorithms](#3-routing-algorithms)
    * [Distance Vector Routing](#distance-vector-routing)
    * [Link State Routing](#link-state-routing)
4.  [Congestion Control](#4-congestion-control)
    * [Leaky Bucket Algorithm](#leaky-bucket)

---

## 1. Client-Server Communication

### Client-Server TCP

* **Concept:** A basic client-server model using the Transmission Control Protocol (TCP). This ensures reliable, connection-oriented communication. The server listens for a single client, and they can exchange messages back and forth.
* **Files:** `client.c`, `server.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc client.c -o client_tcp
        gcc server.c -o server_tcp
        ```
    2.  **Run the server** in one terminal:
        ```bash
        ./server_tcp
        ```
    3.  **Run the client** in another terminal:
        ```bash
        ./client_tcp
        ```
    4.  Follow the prompts to send messages between the client and server.

### Client-Server UDP

* **Concept:** A basic client-server model using the User Datagram Protocol (UDP). This is a connectionless protocol that is faster than TCP but does not guarantee message delivery or order.
* **Files:** `client.c`, `server.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc client.c -o client_udp
        gcc server.c -o server_udp
        ```
    2.  **Run the server** in one terminal:
        ```bash
        ./server_udp
        ```
    3.  **Run the client** in another terminal:
        ```bash
        ./client_udp
        ```

### Concurrent Time Server

* **Concept:** A TCP server that provides the current time to multiple clients concurrently. It uses the `fork()` system call to create a new process for each client connection, allowing the main server process to handle new connections without waiting.
* **Files:** `client.c`, `server.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc client.c -o client_time
        gcc server.c -o server_time
        ```
    2.  **Run the server:**
        ```bash
        ./server_time
        ```
    3.  **Run one or more clients** from different terminals:
        ```bash
        ./client_time
        ```
    Each client will connect and receive the current time from the server.

### File Server

* **Concept:** A TCP-based server that sends the contents of a requested file to a client. The client specifies a filename, and the server reads the file and transmits it over the socket.
* **Files:** `client.c`, `server.c`, `test.txt`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc client.c -o client_file
        gcc server.c -o server_file
        ```
    2.  **Run the server:**
        ```bash
        ./server_file
        ```
    3.  **Run the client:**
        ```bash
        ./client_file
        ```
    4.  When prompted, enter the filename `test.txt`. The client will receive the file's content and save it as `retrieved.txt`.

### Chat Server

* **Concept:** A concurrent TCP chat server that allows multiple clients to connect and broadcast messages to each other. The server uses `fork()` to manage each client connection independently.
* **Files:** `client.c`, `server.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc client.c -o client_chat
        gcc server.c -o server_chat
        ```
    2.  **Run the server:**
        ```bash
        ./server_chat
        ```
    3.  **Run multiple clients** from different terminals:
        ```bash
        ./client_chat
        ```
    4.  Each client will be prompted for a name, and then messages can be exchanged.

---

## 2. Sliding Window Protocols

### Stop-n-Wait

* **Concept:** The simplest sliding window protocol where the sender sends one frame and waits for an acknowledgment (ACK) before sending the next. It simulates frame loss and timeouts.
* **Files:** `client.c`, `server.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc client.c -o client_snw
        gcc server.c -o server_snw
        ```
    2.  **Run the server:**
        ```bash
        ./server_snw
        ```
    3.  **Run the client:**
        ```bash
        ./client_snw
        ```
    The client will send frames one by one, waiting for an ACK for each.

### Go-Back-N

* **Concept:** A sliding window protocol where the sender can transmit a window of several frames before receiving an ACK. If an ACK is missed, the sender "goes back" and retransmits all frames from the last acknowledged frame onwards.
* **Files:** `client.c`, `server.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc client.c -o client_gbn
        gcc server.c -o server_gbn
        ```
    2.  **Run the server:**
        ```bash
        ./server_gbn
        ```
    3.  **Run the client:**
        ```bash
        ./client_gbn
        ```

### Selective Repeat

* **Concept:** An advanced sliding window protocol where the sender can also transmit a window of frames. However, the receiver can accept and buffer out-of-order frames. The sender only retransmits the specific frames that were lost or negatively acknowledged.
* **Files:** `client.c`, `server.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc client.c -o client_sr
        gcc server.c -o server_sr
        ```
    2.  **Run the server:**
        ```bash
        ./server_sr
        ```
    3.  **Run the client:**
        ```bash
        ./client_sr
        ```

---

## 3. Routing Algorithms

### Distance Vector Routing

* **Concept:** A decentralized routing algorithm where each router maintains a table of distances to all other routers. Routers periodically share their tables with their immediate neighbors, allowing them to update their own tables and find the shortest path based on the Bellman-Ford algorithm.
* **Files:** `dvr.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc dvr.c -o dvr
        ```
    2.  **Run the program:**
        ```bash
        ./dvr
        ```
    3.  Follow the prompts to enter the number of routers and the cost matrix. The program will then calculate and display the final routing tables for each router.

### Link State Routing

* **Concept:** A centralized routing algorithm where each router broadcasts its connectivity information (link states) to all other routers in the network. Each router then independently constructs a complete map of the network and uses Dijkstra's algorithm to calculate the shortest path to all destinations.
* **Files:** `lsr.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc lsr.c -o lsr
        ```
    2.  **Run the program:**
        ```bash
        ./lsr
        ```
    3.  Enter the number of routers, the adjacency matrix representing the network graph, and the source router. The program will output the shortest path from the source to all other routers.

---

## 4. Congestion Control

### Leaky Bucket

* **Concept:** An algorithm used for traffic shaping and congestion control. It models a bucket with a fixed capacity and a constant leak rate. Incoming packets are added to the bucket. If the bucket is full, new packets are discarded. Packets "leak" from the bucket at a steady rate, resulting in a smooth output traffic flow.
* **Files:** `leakyBucket.c`

* **How to Run:**
    1.  **Compile:**
        ```bash
        gcc leakyBucket.c -o leaky
        ```
    2.  **Run the program:**
        ```bash
        ./leaky
        ```
    3.  Enter the number of incoming packets at each step to see how the bucket fills and leaks.
