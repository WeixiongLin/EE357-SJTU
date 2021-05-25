#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<vector>
#define PORT "4490"
#define LEN 1000
using namespace std;

int sockfd;

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
        return &(((struct sockaddr_in6*)sa)->sin6_addr); 
}


static void * pthread(void *arg){
    struct addrinfo hints,*res;
    struct sockaddr_storage their_addr;
    char ip_addr[INET6_ADDRSTRLEN];
    socklen_t addr_len;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL,PORT,&hints,&res);
    // int sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    cout<<"Listener: waiting for recvfrom...\n";
    while(1){
        char buf[LEN];
        memset(buf,'\0',LEN);
        int recv_len = recvfrom(sockfd, buf, LEN, 0, (struct sockaddr*)&their_addr, &addr_len);
        if(recv_len==-1){
            perror("recvfrom");
            exit(1);
        }
        const char *add = inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr*)&their_addr), ip_addr, sizeof ip_addr);
        cout << "<<<" << ip_addr << " says:";
        cout << buf << endl;
        memset(buf,'\0',LEN);
    }
    return NULL;
} 



int main(){
    struct addrinfo hints, *res;
    string clients[]={"10.0.0.1", "10.0.0.2", "10.0.0.3", "10.0.0.4"};
    int num_clients = 4, len, bytes_sent;
    vector<struct sockaddr*> destaddrs;
    
    // 设置其他客户地址
    for(int i = 0; i < 4; i++){
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        getaddrinfo(clients[i].c_str(), PORT, &hints, &res);
        // sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
        // sockfds.push_back(sockfd);
        destaddrs.push_back(res->ai_addr);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, PORT, &hints, &res);
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(bind(sockfd, res->ai_addr, res->ai_addrlen)==-1){
        close(sockfd); perror("Listener:bind");
    }

    pthread_t tid;
    if ((pthread_create(&tid, NULL, pthread, NULL)) == -1){
        cout<<("create error!\n");
        return -1;
    }
    cout<<"Thread created."<<endl;

    // for user to input
    char text[LEN];
    strcpy(text, "Hello everyone!");
    len = strlen(text);
    do{
        for(int i = 0; i < 4; i++){
            struct sockaddr* ai_addr = destaddrs[i];
            bytes_sent = sendto(sockfd, text, len, 0, ai_addr, sizeof *ai_addr);
        }
        memset(text, '\0', LEN);
        cout<<">>>";
        cin.getline(text, LEN);
        len = strlen(text);
    } while(1);
    close(sockfd);

    return 0;
}

