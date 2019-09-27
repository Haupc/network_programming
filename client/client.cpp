#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int serverPort = 8899;
char* serverIp = "127.0.0.1";

char* clientMessages[3] = {"Hello server!", "What is your name?", "Bye"};

void initServPort(int argc, char *argv[]);

void initServIp(int argc, char *argv[]);

void init(int argc, char *argv[]);

void WriteBuff(char buff[], int nbytes);

void readData(char readBuff[], int sockfd);

void writeData(char writeBuff[], int sockfd);

int main(int argc, char* argv[])
{
    init(argc, argv);
    // Init socket
    int sockfd;
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket error");
        exit(1);
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);

    if (connect(sockfd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect error");
        exit(1);
    }
    
    // write , read
    char* writeBuff;
    char readBuff[512];
    int count = 0;
    while (count < 3)
    {
        writeBuff = clientMessages[count];
        writeData(writeBuff, sockfd);
        readData(readBuff, sockfd);
        count ++;
        usleep(200);
    }

    // close
    close(sockfd);
    return 0;
}

void initServPort(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "default server port is 8899" << endl;
    }
    else
    {
        if (serverPort = atoi(argv[1]) < 0)
        {
            cout << "fail to get port" << endl;
            return;
        }
        else
        {
            cout << "port is set to " << serverPort << endl;
        } 
    }
}

void initServIp(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "ServerIp is set to default at 127.0.0.1" << endl;
        return;
    }
    if (argc == 3)
    {
        serverIp = argv[2];
        cout << "Connecting to " << serverIp << endl;
        return;
    }
    

}

void init(int argc, char *argv[])
{
    initServPort(argc, argv);
    initServIp(argc, argv);
}

void WriteBuff(char buff[], int nbytes)
{
    for (int i = 0; i < nbytes; i++)
    {
        cout << buff[i];
    }
    cout << buff << endl;
    
}

void readData(char readBuff[], int sockfd)
{
    int nbytes;
    bzero(readBuff, sizeof(readBuff));
    if( (nbytes = read(sockfd, readBuff, sizeof(readBuff)) ) < 0)
    {
        perror("read error");
        exit(1);
    }
    cout << "Server: ";
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