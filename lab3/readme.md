# TCP version

client.cpp 和 server.cpp 

## Usage
g++ server.cpp -o server -lpthread

g++ client.cpp -o client -lpthread

<!-- sudo mn --custom lab3-topo.py --topo lab3topo -->

python hw1.py

xterm h1

xterm h2

xterm h3

xterm h4

在h1里运行server，其他三个运行client

# UDP version

udpclient.cpp

## Usage 

g++ udpclient.cpp -o udpclient -lpthread

g++ udpclient_filter.cpp -o udpclient_filter -lpthread


#### 旧的commit说明

"second ver, use process" 该版本使用fork导致sockfd查找表进程间不共享

"Finish TCP chat room" 该版本客户端和服务器一来一回创建了两条TCP连接，太傻了

#### 笔记
如果fd不手动close的话，创建新的socket操作系统会一直分配fd给进程，直至耗尽（打开文件数量上限）。

TCP我们需要多个socket，以服务器端来说，有三个主机来建立连接，因此socket要有3个。

UDP版本中，我们只需要创建一个socket，同时负责收/发的工作，因为是无连接的协议，收发到数据也就完成了一次通信，恢复原样。

TCP版本是可靠的、面向连接的服务，双方建立连接后可以双向通信，分别运行在一开始创建连接的端口。UDP版本源端口号和目的端口号可以是同一个，毕竟他们运行在
两台主机上。UDP协议里没有ip地址没关系，网络层将整个运输层报文封装到一个IP数据报中。

运输层的分解服务：主机上每个套接字能够分配一个端口号，当报文到达主机时，运输层检查报文段中目的端口号，并将其定向到对应的套接字，
报文段中的数据进入其所连接的进程。 TCP与UDP不同在于，TCP套接字是由四元组标识的，主机会用全部的4个值来定向到对应套接字，不同源IP或者源端口号将被定向到两个不同的套接字上。

UDP不bind端口号，则会随机为我们分配一个未使用的UDP端口，我们若想手动指定，就可以使用bind。
