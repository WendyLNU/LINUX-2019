#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <pthread.h>
#include <windowsx.h>
#include "chinese_chess.h"
#include "Server.h"
#include "Client.h"


#define WIDTH 600       //界面宽度
#define HEIGHT 600      //界面高度
#define ZERO_X 70       //棋盘左边界
#define ZERO_Y 70       //棋盘上边界
#define PIECE_BKCOLOR    RGB(195,163,109)   //棋子背景色
#define PIECE_WH 45        //棋盘每个格子的宽度和高度

HWND hwnd;               /* This is the handle for our window */
char* ots_ip;           //存储对方IP地址的字符串
int port;
bool is_connect_alive=false;        //是否连接到对方
Board * chess_board;          //棋盘
Server *server;
Client *client;
int chess_sx=-1;        //移动起始位置的数组坐标
int chess_sy=-1;
int chess_dx=-1;        //移动目标位置的数组坐标
int chess_dy=-1;




/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Chinese Chess");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow) {
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Chinese Chess"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               WIDTH,                 /* The programs width */
               HEIGHT,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0)) {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
//把数组坐标转换为界面坐标
void xy_to_pixel(int x,int y,int*pixelx,int *pixely) {
    *pixely=x*PIECE_WH+ZERO_Y;
    *pixelx=y*PIECE_WH+ZERO_X;
}
//把界面坐标转换为数组坐标
void pixel_to_xy(int pixelx,int pixely,int*x,int *y) {
    int r=PIECE_WH/2;
    *y=(pixelx-(ZERO_X-r))/PIECE_WH;
    *x=(pixely-(ZERO_Y-r))/PIECE_WH;
}
//以数组坐标画线
void draw_line(HDC hdc,int sx,int sy,int dx,int dy) {
    int psx,psy,pdx,pdy;
    xy_to_pixel(sx,sy,&psx,&psy);
    xy_to_pixel(dx,dy,&pdx,&pdy);
    MoveToEx (hdc, psx,psy, NULL) ;
    LineTo (hdc, pdx, pdy) ;
}
//以数组坐标画棋子
void paint_piece(HDC hdc,int x,int y,int color,int type) {
    static HBRUSH  piece_brush =CreateSolidBrush (PIECE_BKCOLOR);    //棋子的背景色
    if(type==0||color==BLANK)return ;
    int px,py;
    xy_to_pixel(x,y,&px,&py);
    int r=PIECE_WH/2;
    SelectObject (hdc,piece_brush ) ;
    SelectObject (hdc, GetStockObject (NULL_PEN)) ;
    Ellipse(hdc,px-r,py-r,px+r,py+r);
    char *text=new char[5];
    switch(type) {
    case JU:
        strcpy(text,"車");
        break;
    case MA:
        strcpy(text,"马");
        break;
    case XIANG:
        if(color==BLACK)strcpy(text,"象");
        else strcpy(text,"相");
        break;
    case SHI:
        strcpy(text,"士");
        break;
    case JIANG:
        if(color==BLACK)strcpy(text,"将");
        else strcpy(text,"帅");
        break;
    case PAO:
        if(color==BLACK)strcpy(text,"砲");
        else
            strcpy(text,"炮");
        break;
    case ZU:
        if(color==BLACK)strcpy(text,"卒");
        else
            strcpy(text,"兵");
        break;
    default:
        strcpy(text,"");
    }
    SetBkColor(hdc,PIECE_BKCOLOR);//设置文字背景色
    if(color==BLACK) {
        SetTextColor(hdc,RGB(0,0,0));       //设置文字颜色
    } else {
        SetTextColor(hdc,RGB(255,255,255));
    }
    TextOut (hdc, px-r/2, py-r/2,text , strlen("马")) ;
    delete text;
}

void* main_listen(void *) {
    server->listen_message();
    return 0;
}
//创建线程，使server开始监听
bool  start_listen() {
    pthread_t listen_p;
    int ret;
    ret= pthread_create( &listen_p,  NULL, main_listen,NULL ); //
    if( ret != 0 ) { //创建线程成功返回0
        //printf("pthread_create error:error_code=%d\n",ret );
        handle_error(THREAD_ERROR,true,true);
        return false;
    }
    return true;
}


void* chess_connect(void *) {
    client->connect_to_ots();  //client开始连接对方server，连接成功后返回
    InvalidateRect(hwnd,NULL,true);
}

void init() {
    server=new Server();//创建Server对象
    client=new Client(); //创建Client对象，
    start_listen();             //创建线程，server开始监听
    Sleep(1000);
    pthread_t connect_p;
    int ret;
    ret= pthread_create( &connect_p,  NULL, chess_connect,NULL); //
    if( ret != 0 ) { //创建线程成功返回0
        //printf("pthread_create error:error_code=%d\n",ret );
        handle_error(THREAD_ERROR,true,true);
        return ;
    }
}



/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static POINT mouse;
    static HDC hdc;
    static PAINTSTRUCT ps ;
    static int iofip=0;     //index of ots_ip
    switch (message) {                /* handle the messages */
    case WM_CREATE: {
        port=35536;
        ots_ip=new char[20];
        strcpy(ots_ip,"");
    }
    break;
    case WM_KEYDOWN://识别按键，显示输入的内容（对方IP地址）
        if(server!=NULL)break;
        if(wParam==13) {//如果是ENTER，则初始化server、client，并开始连接，连接成功后初始化board
            init();
            Sleep(100);
            InvalidateRect(hwnd,NULL,true);
        }
        if(wParam==VK_BACK) {//删除键
            if(iofip==0)return 0;
            iofip--;
            ots_ip[iofip]='\0';
        }
        if(wParam<106&&wParam>95) {//小键盘数字键
            wParam-=48;
        }
        if(wParam<58&&wParam>47) {//主键盘数字键
            ots_ip[iofip]='0'-48+wParam;
            iofip++;
            ots_ip[iofip]='\0';
        }
        if(wParam==110||wParam==229) {//小数点键，小键盘110，主键盘229
            ots_ip[iofip]='.';
            iofip++;
            ots_ip[iofip]='\0';
        }
        InvalidateRect(hwnd,NULL,true);
        break;
    case WM_PAINT: {
        static HBRUSH  bk_brush =CreateSolidBrush (RGB(240,240,240));    //棋子的背景色
        hdc=BeginPaint (hwnd,&ps) ;
        static HFONT hFont;
        LOGFONT lf;
        lf.lfHeight=PIECE_WH/2;
        lf.lfWidth=0;
        lf.lfEscapement=0;
        lf.lfOrientation=0 ;
        lf.lfWeight=5;
        lf.lfItalic=0 ;
        lf.lfUnderline=0 ;
        lf.lfStrikeOut=0 ;
        lf.lfCharSet=DEFAULT_CHARSET ;
        lf.lfOutPrecision=0 ;
        lf.lfClipPrecision=0 ;
        lf.lfQuality=0 ;
        lf.lfPitchAndFamily=0 ;
        lstrcpy (lf.lfFaceName, _T("楷体") );
        hFont = CreateFontIndirect (&lf) ;
        SelectFont(hdc,hFont);
        SelectObject(hdc,bk_brush);
        Rectangle(hdc,0,0,WIDTH,HEIGHT);
        SetBkColor(hdc,RGB(240,240,240));
        if(chess_board==NULL) {//显示输入的IP地址
            char tip[20]="请输入对方IP地址：";
            Rectangle(hdc,WIDTH/5,HEIGHT/2-10,WIDTH/5*4,HEIGHT/2+30);
            TextOut(hdc,WIDTH/5,HEIGHT/2-50,tip,strlen(tip));
            SetBkColor(hdc,RGB(240,240,240));
            TextOut(hdc,WIDTH/5+5,HEIGHT/2,ots_ip,strlen(ots_ip));
            if(server!=NULL) {             //board==NULL而server!=NULL表示正在连接过程中
                char tip[20]="正在连接......";
                SetBkColor(hdc,RGB(240,240,240));
                TextOut(hdc,WIDTH/5,HEIGHT/2+50,tip,strlen(tip));
            }
            EndPaint(hwnd,&ps);
            break;
        }
        char text[10]="你的颜色:";
        if(chess_board->get_color()==BLACK) {
            strcat(text," 黑");
        } else {
            strcat(text," 白");
        }
        TextOut (hdc, 5, 5,text , strlen(text)) ;
        int M=chess_board->get_M();
        int N=chess_board->get_N();
        //画棋盘
        for(int i=0; i<M; i++) {
            draw_line(hdc,i,0,i,N-1);
        }
        for(int i=0; i<N; i++) {
            draw_line(hdc,0,i,N/2,i);
        }
        for(int i=0; i<N; i++) {
            draw_line(hdc,N/2+1,i,N,i);
        }
        draw_line(hdc,0,3,2,5);
        draw_line(hdc,0,5,2,3);
        draw_line(hdc,9,3,7,5);
        draw_line(hdc,7,3,9,5);
        draw_line(hdc,4,0,5,0);
        draw_line(hdc,4,8,5,8);
        //画棋子
        for(int i=0; i<M; i++) {
            for(int j=0; j<N; j++) {
                paint_piece(hdc,i,j,chess_board->get_color(i,j),chess_board->get_type(i,j));
            }
        }
        EndPaint(hwnd,&ps);
    }
    break;
    case WM_LBUTTONUP: {
        if(chess_board==NULL)break;
        if(!chess_board->is_my_turn())break;//当前没轮到自己下棋
        GetCursorPos(&mouse);//获取鼠标的屏幕坐标
        ScreenToClient(hwnd,&mouse);//转换为界面坐标
        int x,y;
        pixel_to_xy(mouse.x,mouse.y,&x,&y);//转换为数组坐标
        if(chess_board->get_color(x,y)==chess_board->get_color()) {//点击的是自己的棋子
            chess_sx=x;
            chess_sy=y;
            break;
        }
        if(chess_sx==-1||chess_sy==-1) {//起始坐标未赋值且点击的不是自己的棋子，则break
            break;
        }
        chess_dx=x;
        chess_dy=y;
        if(chess_board->my_move_piece(chess_sx,chess_sy,chess_dx,chess_dy)) { //如果移动棋子合法
            client->send_message("move",chess_sx,chess_sy,chess_dx,chess_dy);   //向对方发送移子信息
            InvalidateRect(hwnd,NULL,true);
            if(chess_board->get_is_win()==WIN) {
                chess_board->init();//重新初始化棋盘，重下一盘
                MessageBox(hwnd,"你赢了","获胜！",NULL);
                InvalidateRect(hwnd,NULL,true);
            }
        }
        chess_sx=-1;
        chess_sy=-1;
        break;
    }
    case WM_DESTROY:
        if(server!=NULL)server->close();
        if(client!=NULL)client->close();
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
