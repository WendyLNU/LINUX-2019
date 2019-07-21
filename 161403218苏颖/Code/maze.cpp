#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"maze.h"

#define MAX_ROW  12
#define MAX_COL  14

int maze[12][14] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1,
    1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
    1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1 ,0 ,0, 0 ,0 ,1 ,0 ,1 ,1,
    1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

void print_line()
{
    system("cls");
    printf("maze as follows' ■' represents the wall and the numbers represent the path\n");
    int i, j;
    for (i = 0; i < MAX_ROW; i++){
        for (j = 0; j < MAX_COL; j++)
            if (maze[i][j] == 1)       printf("■");
            else if (maze[i][j] >= 3){
                printf("%2d", maze[i][j] - 2);
                //if (i == MAX_ROW-2 && j == MAX_COL-2)  printf("★");
                //else                   printf("☆");       
            }    
            else  printf("  ");
            printf("\n");
        }
    printf("Arrived at the exit....\n");
}

void visit(mark p,int sign, PSeqStack S)
{
    Push_SeqStack(S,p);
    switch (sign)
    {
    case 1: p.col++; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向右
    case 2: p.row++; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向下
    case 3: p.col--; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向左
    case 4: p.row--; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向上
    }
}

int main()
{
    struct point p = { 1, 1 };
    maze[p.row][p.col] = 2;//遍历过的点设置为2
    PSeqStack S = Init_SeqStack();
    Push_SeqStack(S,p);
    while (!Empty_SeqStack(S))
    {
        Pop_SeqStack(S, &p);
        if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)
            break;
        if (p.col + 1 < MAX_COL - 1 && maze[p.row][p.col + 1] == 0)//向右
        {    
            visit(p, 1, S);
            continue;
        }
        if (p.row + 1 < MAX_ROW - 1 && maze[p.row + 1][p.col] == 0)//向下
        {
            visit(p, 2, S);
            continue;
        }
        if (p.col - 1 >= 1 && maze[p.row][p.col - 1] == 0)//向左
        {
            visit(p, 3, S);
            continue;
        }
        if (p.row - 1 >= 1 && maze[p.row - 1][p.col] == 0)//向上
        {
            visit(p, 4, S);
            continue;
        }//以上是对迷宫的四个方向进行操作
    }
    if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)//是否为出口
    {
        int count = GetLength_SeqStack(S)+3;//为了与迷宫0,1,2的区别所以基数要以3开始
        printf("Successfully found exit, reverse output path:\n");
        printf("(%d,%d)\n", p.row, p.col);
        maze[p.row][p.col] = count;
        while (!Empty_SeqStack(S))//按照前驱进行查找
        {
            count--;
            Pop_SeqStack(S, &p);
            maze[p.row][p.col] = count;
            printf("(%d,%d)\n", p.row, p.col);            
        }
        printf("Print path in 3 seconds ......\n");
        sleep(3);
        print_line();
    }
    else {
        printf("There is no way out.\n");
    }
    system("pause");
    return 0;
}
