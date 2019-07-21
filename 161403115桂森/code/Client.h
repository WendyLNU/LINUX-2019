#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <stdio.h>
#include <winsock2.h>

#include"chinese_chess.h"

//为字符串添加校验信息，对所有字符求和，模5之后转化为字符放在字符串最后
void client_check(char* r) {
    int len=strlen(r);
    int s=0;
    for(int i=0; i<len; i++) {
        s+=r[i];
    }
    r[len]=s%5+'0';
    r[len+1]='\0';
}
class Client {
private:
    SOCKET Client_Sock;
    SOCKADDR_IN server_addr;
    char sendBuf[20];
public:
    Client() {
        WSADATA wsa;
        /*初始化socket资源*/
        if (WSAStartup(MAKEWORD(1,1),&wsa) != 0) {
            handle_error(INIT_ERROR,true,true);
            return;   //代表失败
        }
        if((Client_Sock = socket(AF_INET, SOCK_STREAM, 0))==-1) {
            handle_error(INIT_ERROR,true,true);
            return;   //代表失败
        }
        server_addr.sin_addr.S_un.S_addr=inet_addr(ots_ip);
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(port);
        strcpy(sendBuf,"");
    }
    void connect_to_ots() {
        while(connect(Client_Sock,(SOCKADDR*)&server_addr,sizeof(SOCKADDR)) ==-1) {
            handle_error(CONNECT_ERROR,false,false);
            Sleep(100);
            //printf( "%d ", WSAGetLastError());
        }
        char rec[5];
        recv(Client_Sock,rec,4,0);
        if(strncmp(rec,"wron",4)==0) {  //收到wrong，说明对方所输入的IP不是己方IP
            MessageBox(hwnd,"对方输入的IP不是你\n程序将退出","错误",NULL);
            exit(-1);
        }
        //谁先连接谁是黑色
        //如果server已经收到连接，则说明是对方先连接自己，则自己应为白色，否则自己是黑色
        if(is_connect_alive) {
            chess_board=new Board(WHITE);
        } else {
            chess_board=new Board(BLACK);
        }
    }
    void close() {
        closesocket(Client_Sock);
        WSACleanup();
    }

    int send_message(char * message) {
        strcpy(sendBuf,message);
        client_check(sendBuf);
        int len;
        int try_time=0;
        while(true) {
            len=send(Client_Sock,sendBuf,strlen(sendBuf)+1,0);
            if(len!=(strlen(sendBuf)+1)) {
                handle_error(SEND_ERROR,false,false);
                //printf( "%d ", WSAGetLastError());
            }
            char rec[5];
            recv(Client_Sock,rec,4,0);
            if(strncmp(rec,"okok",4)==0) {//收到OK说明数据已经正确被对方收到
                break;
            }
            if(try_time>20) {   //尝试20次，数据仍无法正确送达，则退出
                handle_error(SEND_ERROR,true,true);
            }
            try_time++;
        }
        return len;
    }
    int send_message(const char * message,int sx,int sy,int dx,int dy) {
        char* message_temp=new char[20];
        sprintf(message_temp,"%s,%d,%d,%d,%d,",message,sx,sy,dx,dy);
        int len=send_message(message_temp);
        delete message_temp;
        return len;
    }
};


#endif // CLIENT_H_INCLUDED
