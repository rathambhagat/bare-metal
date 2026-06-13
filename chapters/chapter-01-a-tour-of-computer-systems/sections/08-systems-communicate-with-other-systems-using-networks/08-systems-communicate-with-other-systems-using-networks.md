# 1.8 Systems Communicate with Other Systems Using Networks

Up to this point, we have treated a system as an isolated collection of hardware and software. In practice, modern systems are often linked to other systems by **networks**.

## The Network as an I/O Device

From the point of view of an individual system, the network can be viewed as just another I/O device:

- When the system copies a sequence of bytes from main memory to the **network adapter**, the data flow across the network to another machine
- The system can read data sent from other machines and copy these data to its main memory

## Running `hello` Remotely with Telnet

Consider using the `telnet` application to run `hello` on a remote machine:

![Using telnet to run hello remotely over a network](./images/_page_20_Figure_0.jpeg)

**Figure 1.15 — Using telnet to run hello remotely over a network**

### The Five Steps

1. We type `hello` to the **telnet client** running on our local machine and hit Enter
2. The client sends the string to a **telnet server** on the remote machine
3. The telnet server passes the string to the **remote shell** program
4. The remote shell runs `hello` and passes the output line back to the telnet server
5. The telnet server forwards the output string across the network to the telnet client, which prints it on our local terminal

This type of **client-server** exchange is typical of all network applications, including email, instant messaging, the World Wide Web, FTP, and telnet.

With the advent of the Internet, copying information from one machine to another has become one of the most important uses of computer systems.
