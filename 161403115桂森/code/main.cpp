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


#define WIDTH 600       //������
#define HEIGHT 600      //����߶�
#define ZERO_X 70       //������߽�
#define ZERO_Y 70       //�����ϱ߽�
#define PIECE_BKCOLOR    RGB(195,163,109)   //���ӱ���ɫ
#define PIECE_WH 45        //����ÿ�����ӵĿ�Ⱥ͸߶�

HWND hwnd;               /* This is the handle for our window */
char* ots_ip;           //�洢�Է�IP��ַ���ַ���
int port;
bool is_connect_alive=false;        //�Ƿ����ӵ��Է�
Board * chess_board;          //����
Server *server;
Client *client;
int chess_sx=-1;        //�ƶ���ʼλ�õ���������
int chess_sy=-1;
int chess_dx=-1;        //�ƶ�Ŀ��λ�õ���������
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
//����������ת��Ϊ��������
void xy_to_pixel(int x,int y,int*pixelx,int *pixely) {
    *pixely=x*PIECE_WH+ZERO_Y;
    *pixelx=y*PIECE_WH+ZERO_X;
}
//�ѽ�������ת��Ϊ��������
void pixel_to_xy(int pixelx,int pixely,int*x,int *y) {
    int r=PIECE_WH/2;
    *y=(pixelx-(ZERO_X-r))/PIECE_WH;
    *x=(pixely-(ZERO_Y-r))/PIECE_WH;
}
//���������껭��
void draw_line(HDC hdc,int sx,int sy,int dx,int dy) {
    int psx,psy,pdx,pdy;
    xy_to_pixel(sx,sy,&psx,&psy);
    xy_to_pixel(dx,dy,&pdx,&pdy);
    MoveToEx (hdc, psx,psy, NULL) ;
    LineTo (hdc, pdx, pdy) ;
}
//���������껭����
void paint_piece(HDC hdc,int x,int y,int color,int type) {
    static HBRUSH  piece_brush =CreateSolidBrush (PIECE_BKCOLOR);    //���ӵı���ɫ
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
        strcpy(text,"܇");
        break;
    case MA:
        strcpy(text,"��");
        break;
    case XIANG:
        if(color==BLACK)strcpy(text,"��");
        else strcpy(text,"��");
        break;
    case SHI:
        strcpy(text,"ʿ");
        break;
    case JIANG:
        if(color==BLACK)strcpy(text,"��");
        else strcpy(text,"˧");
        break;
    case PAO:
        if(color==BLACK)strcpy(text,"�h");
        else
            strcpy(text,"��");
        break;
    case ZU:
        if(color==BLACK)strcpy(text,"��");
        else
            strcpy(text,"��");
        break;
    default:
        strcpy(text,"");
    }
    SetBkColor(hdc,PIECE_BKCOLOR);//�������ֱ���ɫ
    if(color==BLACK) {
        SetTextColor(hdc,RGB(0,0,0));       //����������ɫ
    } else {
        SetTextColor(hdc,RGB(255,255,255));
    }
    TextOut (hdc, px-r/2, py-r/2,text , strlen("��")) ;
    delete text;
}

void* main_listen(void *) {
    server->listen_message();
    return 0;
}
//�����̣߳�ʹserver��ʼ����
bool  start_listen() {
    pthread_t listen_p;
    int ret;
    ret= pthread_create( &listen_p,  NULL, main_listen,NULL ); //
    if( ret != 0 ) { //�����̳߳ɹ�����0
        //printf("pthread_create error:error_code=%d\n",ret );
        handle_error(THREAD_ERROR,true,true);
        return false;
    }
    return true;
}


void* chess_connect(void *) {
    client->connect_to_ots();  //client��ʼ���ӶԷ�server�����ӳɹ��󷵻�
    InvalidateRect(hwnd,NULL,true);
}

void init() {
    server=new Server();//����Server����
    client=new Client(); //����Client����
    start_listen();             //�����̣߳�server��ʼ����
    Sleep(1000);
    pthread_t connect_p;
    int ret;
    ret= pthread_create( &connect_p,  NULL, chess_connect,NULL); //
    if( ret != 0 ) { //�����̳߳ɹ�����0
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
    case WM_KEYDOWN://ʶ�𰴼�����ʾ��������ݣ��Է�IP��ַ��
        if(server!=NULL)break;
        if(wParam==13) {//�����ENTER�����ʼ��server��client������ʼ���ӣ����ӳɹ����ʼ��board
            init();
            Sleep(100);
            InvalidateRect(hwnd,NULL,true);
        }
        if(wParam==VK_BACK) {//ɾ����
            if(iofip==0)return 0;
            iofip--;
            ots_ip[iofip]='\0';
        }
        if(wParam<106&&wParam>95) {//С�������ּ�
            wParam-=48;
        }
        if(wParam<58&&wParam>47) {//���������ּ�
            ots_ip[iofip]='0'-48+wParam;
            iofip++;
            ots_ip[iofip]='\0';
        }
        if(wParam==110||wParam==229) {//С�������С����110��������229
            ots_ip[iofip]='.';
            iofip++;
            ots_ip[iofip]='\0';
        }
        InvalidateRect(hwnd,NULL,true);
        break;
    case WM_PAINT: {
        static HBRUSH  bk_brush =CreateSolidBrush (RGB(240,240,240));    //���ӵı���ɫ
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
        lstrcpy (lf.lfFaceName, _T("����") );
        hFont = CreateFontIndirect (&lf) ;
        SelectFont(hdc,hFont);
        SelectObject(hdc,bk_brush);
        Rectangle(hdc,0,0,WIDTH,HEIGHT);
        SetBkColor(hdc,RGB(240,240,240));
        if(chess_board==NULL) {//��ʾ�����IP��ַ
            char tip[20]="������Է�IP��ַ��";
            Rectangle(hdc,WIDTH/5,HEIGHT/2-10,WIDTH/5*4,HEIGHT/2+30);
            TextOut(hdc,WIDTH/5,HEIGHT/2-50,tip,strlen(tip));
            SetBkColor(hdc,RGB(240,240,240));
            TextOut(hdc,WIDTH/5+5,HEIGHT/2,ots_ip,strlen(ots_ip));
            if(server!=NULL) {             //board==NULL��server!=NULL��ʾ�������ӹ�����
                char tip[20]="��������......";
                SetBkColor(hdc,RGB(240,240,240));
                TextOut(hdc,WIDTH/5,HEIGHT/2+50,tip,strlen(tip));
            }
            EndPaint(hwnd,&ps);
            break;
        }
        char text[10]="�����ɫ:";
        if(chess_board->get_color()==BLACK) {
            strcat(text," ��");
        } else {
            strcat(text," ��");
        }
        TextOut (hdc, 5, 5,text , strlen(text)) ;
        int M=chess_board->get_M();
        int N=chess_board->get_N();
        //������
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
        //������
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
        if(!chess_board->is_my_turn())break;//��ǰû�ֵ��Լ�����
        GetCursorPos(&mouse);//��ȡ������Ļ����
        ScreenToClient(hwnd,&mouse);//ת��Ϊ��������
        int x,y;
        pixel_to_xy(mouse.x,mouse.y,&x,&y);//ת��Ϊ��������
        if(chess_board->get_color(x,y)==chess_board->get_color()) {//��������Լ�������
            chess_sx=x;
            chess_sy=y;
            break;
        }
        if(chess_sx==-1||chess_sy==-1) {//��ʼ����δ��ֵ�ҵ���Ĳ����Լ������ӣ���break
            break;
        }
        chess_dx=x;
        chess_dy=y;
        if(chess_board->my_move_piece(chess_sx,chess_sy,chess_dx,chess_dy)) { //����ƶ����ӺϷ�
            client->send_message("move",chess_sx,chess_sy,chess_dx,chess_dy);   //��Է�����������Ϣ
            InvalidateRect(hwnd,NULL,true);
            if(chess_board->get_is_win()==WIN) {
                chess_board->init();//���³�ʼ�����̣�����һ��
                MessageBox(hwnd,"��Ӯ��","��ʤ��",NULL);
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
