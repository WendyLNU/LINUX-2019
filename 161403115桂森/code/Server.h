#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include<stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <winsock2.h>
#include"chinese_chess.h"

#define INIT_ERROR 1
#define BIND_ERROR 2
#define LISTEN_ERROR 3
#define CONNECT_ERROR 4
#define SEND_ERROR 5
#define ACCEPT_ERROR 6
#define ALIVE_ERROR 7
#define THREAD_ERROR 8
int error_num;
extern HWND hwnd;
extern Board* chess_board;
extern char* ots_ip;
extern int port;
extern bool is_connect_alive;

//线程参数结构体
typedef struct server_args {
    SOCKET* Com_Sock;
    char * rebuf;
} server_args;
//校验检测，与客户端的添加校验是相反操作
//最后一位之前的所有字符相加取模后，如果等于最后一个字符，则校验通过
bool server_check(char * r) {
    int len=strlen(r);
    len--;
    int s=0;
    for(int i=0; i<len; i++) {
        s+=r[i];
    }
    if(r[len]==(s%5+'0')) {
        r[len]='\0';
        return true;
    }
    return false;
}
//错误处理，is_tell控制是否显示错误信息，is_exit控制是否退出程序
int handle_error(int err,bool is_tell,bool is_exit) {
    error_num=err;
    if(!is_tell)return error_num;
    char error[30]="";
    switch(error_num) {
    case INIT_ERROR:
        strcpy(error,"初始化错误");
        break;
    case BIND_ERROR:
        strcpy(error,"绑定端口错误");
        break;
    case LISTEN_ERROR:
        strcpy(error,"监听错误");
        break;
    case ACCEPT_ERROR:
        strcpy(error,"接受连接错误");
        break;
    case CONNECT_ERROR:
        strcpy(error,"无法连接");
        break;
    case ALIVE_ERROR:
        strcpy(error,"连接已断开");
        break;
    case THREAD_ERROR:
        strcpy(error,"线程无法创建");
        break;
    case SEND_ERROR:
        strcpy(error,"发送错误");
    }
    char error_message[50];
    strcpy(error_message,"错误：");
    strcat(error_message,error);
    if(is_exit)strcat(error_message,"\n程序将退出。");
    MessageBox(hwnd,error_message,"错误",MB_OK);
    if(is_exit)exit(0);
    return error_num;
}
void* handle_message(void*ar) {
    server_args * serarg=(server_args * )ar;
    char *recv=serarg->rebuf;
    SOCKET* CommandSock=serarg->Com_Sock;
    if(server_check(recv)) {//校验通过发送okok（OK），不通过发送noto（NOTOK）
        send(*CommandSock,"okok",4,0);
    } else {
        send(*CommandSock,"noto",4,0);
        return ar;
    }
    if(strncmp(recv,"move",4)==0) {
        char * pch;
        //将recvBuf以逗号拆分
        pch = strtok (recv,",");
        pch = strtok (NULL,",");
        int xys[4];
        int index=0;
        while (pch != NULL) {
            xys[index]=atoi(pch);//char* 转换为int
            index++;
            pch = strtok (NULL, ",");
        }
        chess_board->othside_move_piece(xys[0],xys[1],xys[2],xys[3]);
        if(chess_board->get_is_win()==LOSE) {
            chess_board->init();//如果输了，则重新初始化棋盘，再下一盘
            MessageBox(hwnd,"你输了","失败！",NULL);
        }
        InvalidateRect(hwnd,NULL,true);
    }
    delete recv;
}
class Server {
private:
    SOCKET Server_Sock;
    SOCKADDR_IN server_addr;
    SOCKADDR_IN client_addr;
    char recvBuf[20];

public:
    Server() {
        WSADATA wsa;
        /*初始化socket资源*/
        if (WSAStartup(MAKEWORD(1,1),&wsa) != 0) {
            handle_error(INIT_ERROR,true,true);
            return;
        }

        if((Server_Sock = socket(AF_INET, SOCK_STREAM, 0))==-1) {
            handle_error(INIT_ERROR,true,true);
            return;
        }
        ZeroMemory((char *)&server_addr,sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);           /*本地监听端口*/
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /*有IP*/

        if(bind(Server_Sock,(struct sockaddr *)&server_addr,sizeof(server_addr))==-1) {
            handle_error(BIND_ERROR,true,true);
            return;
        }
        if(listen(Server_Sock,5)==-1) { //其中第二个参数代表能够接收的最多的连接数
            handle_error(LISTEN_ERROR,true,true);
            return;
        }
        strcpy(recvBuf,"");
    }

    void listen_message() {
        int len=sizeof(SOCKADDR);
        while(true) {
            SOCKET Command_Sock  = accept(Server_Sock, (SOCKADDR*)&client_addr,&len);
            if(Command_Sock == INVALID_SOCKET) {
                closesocket(Command_Sock);
                handle_error(ACCEPT_ERROR,false,false);
                continue;
            }
            if(client_addr.sin_addr.s_addr!=inet_addr(ots_ip)) {//如果接收的socket不是预期的对方的，则发送wron，继续等待
                send(Command_Sock,"wron",4,0);
                closesocket(Command_Sock);
                continue;
            }
            send(Command_Sock,"righ",4,0);
            is_connect_alive=true;
            while(true) {
                if(recv(Command_Sock,recvBuf,20,0)<=0) {//recv返回小于等于0的值，则连接已断开
                    handle_error(ALIVE_ERROR,true,true);
                    closesocket(Command_Sock);
                    close();
                    return ;
                }
                char *rbuf=new char[20];
                strcpy(rbuf,recvBuf);
                server_args serarg;
                serarg.Com_Sock=&Command_Sock;
                serarg.rebuf=rbuf;
                pthread_t handle_m;
                int ret;
                ret= pthread_create( &handle_m,  NULL, handle_message,&serarg); //
                if( ret != 0 ) { //创建线程成功返回0
                    // printf("pthread_create error:error_code=%d\n",ret );
                    handle_error(THREAD_ERROR,true,true);
                    return ;
                }
                strcpy(recvBuf,"");
            }
            closesocket(Command_Sock);
        }
    }
    void close() {
        closesocket(Server_Sock);
        WSACleanup();
    }
};


#endif // SERVER_H_INCLUDED
