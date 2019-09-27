#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int serverPort = 8899;

char* serverMessages[2] = {"Hello client", "My name is Haupc ! Nice to meet you!"};

void init(int argc, char *argv[]);

void WriteBuff(char buff[], int nbytes);

void readData(char readBuff[], int sockfd);

void writeData(char writeBuff[], int sockfd);

int main(int argc, char* argv[])
{
    init(argc, argv);
    // init socket
    int sockfd;
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        exit(1);
    }

    // bind port
    sockaddr_in sockaddr;
    bzero(&sockaddr, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(serverPort);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*) &sockaddr, sizeof(sockaddr)) < 0)
    {
        perror("bind error");
        exit(1);
    }
    
    // listen
    if (listen(sockfd, 10) < 0)
    {
        perror("listen error");
        exit(1);
    }

    // accept
    int newSockfd;

    // declare client
    sockaddr_in clientaddr;
    socklen_t client_socklen;

    client_socklen = sizeof(clientaddr);
    newSockfd = accept(sockfd, (struct sockaddr*) &clientaddr, &client_socklen);
    if (newSockfd < 0)
    {
        perror("accept error");
        exit(1);
    }
    
    // read, write
    char* writeBuff;
    char readBuff[512];
    int count = 0;

    while (count < 2)
    {
        writeBuff = serverMessages[count];
        readData(readBuff, newSockfd);
        count;
        usleep(200);
    }


}
    
void init(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "default port is 8899" << endl;
    }
    else
    {
        if (serverPort = atoi(argv[1]) < 0)
        {
            cout << "fail to set port";
            cout << "port is set to default at 8899" << endl;
            return;
        }
        else
        {
            cout << "port is set to " << serverPort << endl;
        } 
    }
}

void WriteBuff(char buff[], int nbytes)
{
    for (int i = 0; i < nbytes; i++)
    {
        cout << buff[i];
    }
    cout << strlen(buff) << buff << endl;
    
}

void readData(char readBuff[], int sockfd)
{
    int nbytes;
    // bzero(readBuff, sizeof(readBuff));
    if( (nbytes = read(sockfd, readBuff, sizeof(readBuff)) ) < 0)
    {
        perror("read error");
        exit(1);
    }
    cout << "Client: ";
    WriteBuff(readBuff, nbytes);
}

void writeData(char writeBuff[], int sockfd)
{
    int nbytes;
    if((nbytes = write(sockfd, writeBuff, sizeof(writeBuff))) < 0) 
    {
        perror("write error");
        exit(1);
    }
}