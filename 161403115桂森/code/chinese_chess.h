#ifndef CHINESE_CHESS_H_INCLUDED
#define CHINESE_CHESS_H_INCLUDED

#define JU 1
#define MA 2
#define XIANG 3
#define SHI 4
#define JIANG 5
#define PAO 6
#define ZU 7
#define BLANK 8 //空子

#define BLACK -1
#define WHITE 1

#define WIN 1
#define LOSE -1
class Board {
private:
    bool turn;   //是否轮到自己下棋
    int color;  //自己的颜色
    int M,N;        //棋盘行数、列数
    int **b;    //二维数组
    int is_win;     //是否胜利

    bool is_out(int x,int y) {//坐标是否出界
        return x>M||y>N||x<0||y<0;
    }

    bool is_same_color(int sx,int sy,int dx,int dy) {//源坐标与目的坐标是否是同一颜色
        return get_color(sx,sy)==get_color(dx,dy);
    }
    void swap_num(int & num1,int& num2) {//交换两个数
        num1+=num2;
        num2=num1-num2;
        num1=num1-num2;
    }
    int get_abs(int num) {//取得绝对值
        return num>=0?num:-num;
    }
    int num_of_not_blank_betweenn(int sx,int sy,int dx,int dy) {//返回在起始坐标和目的坐标之间棋子的个数
        if(!(sx==dx||sy==dy))return -1;
        int num=0;
        if(sy>dy)swap_num(sy,dy);
        if(sx>dx)swap_num(sx,dx);
        if(sx==dx) {
            for(int i=sy+1; i<dy; i++) {
                if(b[sx][i]!=BLANK)num++;
            }
        }
        if(sy==dy) {
            for(int i=sx+1; i<dx; i++) {
                if(b[i][sy]!=BLANK)num++;
            }
        }
        return num;
    }
    bool is_correct_move_JU(int sx,int sy,int dx,int dy) {
        return num_of_not_blank_betweenn(sx,sy,dx,dy)==0;
    }
    bool is_correct_move_MA(int sx,int sy,int dx,int dy) {
        int x=dx-sx,y=dy-sy;
        if(get_abs(x)==2&&get_abs(y)==1) {
            if(get_color(sx+x/2,sy)==BLANK)return true;//硌马蹄检测
        }
        if(get_abs(x)==1&&get_abs(y)==2) {
            if(get_color(sx,sy+y/2)==BLANK)return true;//硌马蹄检测
        }
        return false;
    }
    bool is_correct_move_XIANG(int sx,int sy,int dx,int dy) {
        int x=dx-sx,y=dy-sy;
        if(!(get_abs(x)==2&&get_abs(y)==2)) return false;
        if(get_color(sx+x/2,sy+y/2)==BLANK)return true;//硌象蹄检测
        return false;
    }
    bool is_correct_move_SHI(int sx,int sy,int dx,int dy) {
        int x=dx-sx,y=dy-sy;
        if(!(get_abs(x)==1&&get_abs(y)==1)) return false;
        if(dx<7)return false;
        if(dy<3||dy>5)return false;
        return true;
    }
    bool is_correct_move_JIANG(int sx,int sy,int dx,int dy) {
        int x=dx-sx,y=dy-sy;
        if(!((get_abs(x)==1&&get_abs(y)==0)||(get_abs(x)==0&&get_abs(y)==1))) return false;
        if(dx<7)return false;
        if(dy<3||dy>5)return false;
        for(int i=0; i<3; i++) {//明将检测
            if(get_type(i,dy)==JIANG) {
                if(num_of_not_blank_betweenn(dx,dy,i,dy)==0) return false;
                return true;
            }
        }
        return true;
    }
    bool is_correct_move_PAO(int sx,int sy,int dx,int dy) {
        int n=get_color(dx,dy)==BLANK?0:1;
        return num_of_not_blank_betweenn(sx,sy,dx,dy)==n;
    }
    bool is_correct_move_ZU(int sx,int sy,int dx,int dy) {
        if(dx>sx)return false;
        int x=dx-sx,y=dy-sy;
        if(get_abs(x)+get_abs(y)!=1)return false;
        if(sx>4&&get_abs(x)!=1)return false;//过河前只能向前走
        return true;
    }

    bool is_correct_move(int sx,int sy,int dx,int dy) {
        if(sx==dx&&sy==dy) {
            return false;
        }
        if(is_out(sx,sy)||is_out(dx,dy)) {
            return false;
        }
        if(get_color(sx,sy)!=color) {
            return false;
        }
        if(is_same_color(sx,sy,dx,dy)) {
            return false;
        }
        switch(get_type(sx,sy)) {
        case JU:
            return is_correct_move_JU(sx,sy,dx,dy);
        case MA:
            return is_correct_move_MA(sx,sy,dx,dy);
        case XIANG:
            return is_correct_move_XIANG(sx,sy,dx,dy);
        case SHI:
            return is_correct_move_SHI(sx,sy,dx,dy);
        case JIANG:
            return is_correct_move_JIANG(sx,sy,dx,dy);
        case PAO:
            return is_correct_move_PAO(sx,sy,dx,dy);
        case ZU:
            return is_correct_move_ZU(sx,sy,dx,dy);
        default:
            return false;
        }
    }

    void move_s_to_d(int sx,int sy,int dx,int dy) { //移动操作
        if(get_type(dx,dy)==JIANG) {    //如果目的棋子是将
            if(get_color(dx,dy)==color)set_win(LOSE);//如果是自己的将，则输
            else set_win(WIN);//如果是对方的将，则赢
        }
        b[dx][dy]=b[sx][sy];
        b[sx][sy]=BLANK;
        change_turn();
    }

    void init_pieces() {
        for(int i=0; i<M; i+=M-1) {//第一行和最后一行（即车马象士将士象马车）
            for(int index=0; index<N; index++) {
                if(index<N/2+1)b[i][index]=index+1;
                else b[i][index]=N-index;
            }
        }
        //卒所在的行
        for(int index=0; index<N; index+=2) {
            b[3][index]=ZU;
        }
        for(int index=0; index<N; index+=2) {
            b[6][index]=ZU;
        }
        b[2][1]=PAO;
        b[M-1-2][1]=PAO;
        b[2][N-1-1]=PAO;
        b[M-1-2][N-1-1]=PAO;
        int s,d;//存储起始行和终点行
        if(color==BLACK) {
            s=0;//从0行到M/2行，即棋盘上半部分
            d=M/2;
        } else {
            s=M/2;//棋盘下半部分
            d=M;
        }
        //从s行到d行，把非BLANK的值加BLANK，使小于BLANK的代表黑色棋，大于BLANK的代表白色棋
        for(int index=s; index<d; index++) {
            for(int j=0; j<N; j++) {
                if(b[index][j]!=BLANK) {
                    b[index][j]+=BLANK;
                }
            }
        }
    }

public:
    Board(int c) {
        color=c;
        M=10;
        N=9;
        b=new int*[M];
        for(int i=0; i<M; i++) {
            b[i]=new int[N];
        }
        init();
    }
    void init() {//棋盘初始化
        is_win=0;
        turn=color==BLACK?true:false;
        for(int i=0; i<M; i++) {
            for(int j=0; j<N; j++) {
                b[i][j]=BLANK;
            }
        }
        init_pieces();
    }
    int get_M() {
        return M;
    }
    int get_N() {
        return N;
    }
    int get_color() {//获取己方的颜色
        return color;
    }
    int get_color(int x,int y) {//获取棋盘某一坐标上棋子的颜色
        return b[x][y]>BLANK?WHITE:b[x][y]<BLANK?BLACK:BLANK;
    }
    int get_type(int x,int y) {//获取棋子类型（空、车、马、象、士、将、炮、卒）
        return b[x][y]!=BLANK?b[x][y]%BLANK:BLANK;
    }
    void set_win(int is) {
        is_win=is;
    }
    int get_is_win() {
        return is_win;
    }
    void change_turn() {
        turn=turn==true?false:true;
    }
    bool is_my_turn() {
        return turn;
    }
    void othside_move_piece(int sx,int sy,int dx,int dy) {//对方移子
        sx=M-1-sx;//先进行坐标转换，因对方视角与己方相反
        sy=N-1-sy;
        dx=M-1-dx;
        dy=N-1-dy;
        move_s_to_d(sx,sy,dx,dy);
    }
    bool my_move_piece(int sx,int sy,int dx,int dy) {       //己方主动移子
        if(!is_correct_move(sx,sy,dx,dy))return false;
        move_s_to_d(sx,sy,dx,dy);
        return true;
    }
};

#endif // CHINESE_CHESS_H_INCLUDED
