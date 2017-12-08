#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_PORT 8888
#define SERV_IP "127.0.0.1"

int main(int argc,char *argv[])
{
    if(argc<3)
    {
        printf("param err\n");
        return -1;
    }
    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET,SERV_IP,&addr.sin_addr);

    connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));

    char buf[1024] = {0};
    sprintf(buf,"username=%s&&password=%s",argv[1],argv[2]);

    uint32_t len = sizeof(uint32_t) * 2 + strlen(buf);

    uint32_t tmp = htonl(len);
    write(sockfd,&tmp,sizeof(tmp));

    tmp = htonl(2); //登录协议
    write(sockfd,&tmp,sizeof(tmp)); 

    tmp = 0;
    write(sockfd,&tmp,sizeof(tmp));

    write(sockfd,&buf,strlen(buf));

    static int x = 0;
    while(1)
    {
        memset(buf,0,sizeof(buf));
        read(sockfd,buf,sizeof(buf));
        char *p = buf;
        len = *(uint32_t *)p;
        len = ntohl(len);
        p= buf+4;
        tmp = *(uint32_t *)p;
        tmp = ntohl(tmp);
        p = buf+8;
        int u_id = *(uint32_t *)p;
        u_id = ntohl(u_id);
        printf("len = %d,protocol = %d,u_id = %d\n",len,tmp,u_id);
        if(tmp == 6)
        {
            memset(buf,0,sizeof(buf));
            strcpy(buf,"black");
            len = sizeof(uint32_t) * 2 + strlen(buf);
            len = htonl(len);
            write(sockfd,&len,sizeof(len));
            tmp = htonl(tmp);
            write(sockfd,&tmp,sizeof(tmp));
            u_id = htonl(u_id);
            write(sockfd,&u_id,sizeof(u_id));
            write(sockfd,buf,strlen(buf));
        }
        else if(tmp == 7)
        {
            memset(buf,0,sizeof(buf));
            sprintf(buf,"%d,%d",x,x);
            ++x;
            x %= 5;
            len = sizeof(uint32_t) * 2 + strlen(buf);
            len = htonl(len);
            write(sockfd,&len,sizeof(len));
            tmp = htonl(tmp);
            write(sockfd,&tmp,sizeof(tmp));
            u_id = htonl(u_id);
            write(sockfd,&u_id,sizeof(u_id));
            write(sockfd,buf,strlen(buf));

        }
        sleep(1);
    }

    close(sockfd);
    return 0;
}
