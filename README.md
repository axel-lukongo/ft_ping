# Ft_ping

## To know :

This projet consist of implementing the `ping` commande in C language. `ping` is a command that allow us to test the accessibility of a machine through the IP address, it measure the response time using the package [ICMP](#what-is-a-icmp-protocole-).
So to realize this project we have to understand some main concepte, notably the the Socket, because this is what we will use to realize this project. 

### what is socket

A socket is a bidirectional endpoint use to communicate between 2 programs running on the network and to be more precise a socket it considered as a file in our system, and when i say file, i don't only mean a basic file as we know for exemple a file.txt, is bigger than that. I give you more precise about the file [here](#what-is-a-file-).

https://beej.us/guide/bgnet/html/#what-is-a-socket

#### What is a file ?

Everything is file on Linux, we use to ear that and that cool but it not really clear for most of us, so what that really mean ? A file is a fundamental unit of storage that contains data or information. In other words, a file it everything that we can read or write inside. Theire is many type of file, example: regular files, sockets, links, hardware devices. And we use a specific interface to manage files. But what is a [interface](#what-is-a-interface-) ?

#### What is a interface ?

In the Unix environement and operating system (OS), a interface is a group of functions/programs or rules that allow us to realize an action, among them theire is the I/O interface (Input/Output), this one content syscall like read(), write(), close() and it commonly use to manage files. So the socket use this interface as a regular files or hardware devices and go on...

#### What is a ICMP Protocole ?

 ICMP(Internet Control Message Protocol) is a set of communication rules that the devices use to report data transmision error through the network.

 