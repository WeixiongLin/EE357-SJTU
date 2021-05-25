#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<pthread.h>
#include<map>

#define PORT "3490"
#define BACKLOG 20
#define LEN 100
#define MAX_CLIENT 20
using namespace std;

map<string,int> sockfd_table;

void *get_in_addr(struct sockaddr *sa){
    if(sa->sa_family == AF_INET){
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

static void * pthread(void *arg){
    char *ip_addr = (char *)arg;
    char buf[LEN];
    string client_ip = ip_addr;
    int new_fd = sockfd_table[client_ip];
    while(1){
        memset(buf,'\0',LEN);
        int recv_len = recv(new_fd,buf,LEN,0);

        // indicating server have received the message
        if(recv_len==0 || recv_len==-1){cout<<"Closed by remote side."<<endl; 
            close(sockfd_table[client_ip]);
            sockfd_table.erase(client_ip);
            break;
        }
        else {cout<<"Received:"<<buf<<endl;}

        string text = buf;
        string prefix = client_ip;
        string sent_message = prefix + " says: "+ text;
        
        int sendfd;
        // broadcast to other clients, excluding myself
        for(map<string,int>::iterator iter=sockfd_table.begin();iter!=sockfd_table.end();iter++){
            if(client_ip == iter->first)
                continue;
            sendfd = iter->second;
            cout<<sent_message<<endl;
            int bytes_sent = send(sendfd,sent_message.c_str(),sent_message.length(),0);
            cout<<"sent byte "<<bytes_sent<<" to "<<iter->first<<" with sockfd "<<iter->second<<endl;
        }
    }
    return NULL;
}


int main(int argc,char *argv[]){
    // create socket descriptor
    // this is the old way
    struct addrinfo hints,*res;
    int sockfd, client_num = 0;

    if(argc == 2) {
        fprintf(stderr, "usage: showip hostname\n");
        return 1;
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // refer to self.

    int status;
    if ((status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    ;
    // make a socket for listening
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        close(sockfd);
        perror("server: bind");
    }

    if(listen(sockfd, BACKLOG) == -1){
        perror("listen");
        exit(1);
    }

    cout<<"Waiting for connection"<<endl;

    while(1){
        // this loop is used for accepting new TCP connection
        //
        // accept an incoming connection
        // Structure large enough to hold any socket address
        struct sockaddr_storage their_addr;
        socklen_t addr_size = sizeof(their_addr);
        // new_fd is create for connection with the client
        int new_fd = accept(sockfd, (struct sockaddr*) &their_addr, &addr_size); 
        if(new_fd == -1){
            perror("accept");
            continue;
        }
        //get ip address
        char s[LEN];
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr*)&their_addr), s, sizeof s);
        string ip_addr = s;
        map<string,int>::iterator iter = sockfd_table.find(s);
        // add new_fd to sockfd
        if(iter==sockfd_table.end()){
            sockfd_table.insert(pair<string,int>(ip_addr, new_fd));
            cout<<"Server: got new connection from "<<ip_addr<<endl;
            // echo for acknowledge
            char text[] = "Acknowledge from server.";
            int byte_send = send(new_fd, text, strlen(text), 0);
            
            // create new thread for receiving any subsequent message.
            pthread_t tid;
            if ((pthread_create(&tid, NULL, pthread, s)) == -1){
                cout<<("create error!\n");
                return -1;
            }
            cout<<"Thread created."<<endl;
        }

    }

	return 0;
}
