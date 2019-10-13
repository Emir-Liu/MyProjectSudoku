#include <iostream>
#include <string.h>
#include <string>
#include <queue>
using namespace std;



int dat[9][9] =
{
{0,2,0,0,9,0,8,0,6},
{0,0,1,0,0,0,2,0,0},
{5,0,0,0,1,0,0,3,0},
{0,0,3,0,0,1,0,2,0},
{2,5,0,0,6,0,9,0,0},
{0,0,7,0,0,8,0,5,0},
{6,0,0,0,5,0,0,9,0},
{0,0,5,0,0,0,3,0,0},
{0,3,0,0,7,0,5,0,4},
};

//bool = 1 该行或者列或者区域已经存在哪个数字
int bool_lin[9];
int bool_col[9];
int bool_blo[9];

typedef struct node
{
    int i=-1,j=-1;
    int ans = 0;//默认为0，表示没有答案
    int bool_pro;//bool = 1 该单元格可能存在哪个数字
    int num_pro = -1;//该单元格有几个可能的数字,-1代表没有进行可能性检测
//    friend bool operator<(node a,node b)
//    {
//        return a.num_pro > b.num_pro;
//    }
}build_grid;
build_grid grid[9][9];
struct pcmp
{
    bool operator()(node *a,node *b)
    {
        return a->num_pro > b->num_pro;
    }
};
priority_queue<node *,vector<node*>,pcmp > grid_queue;

void input_date(int dat[9][9],int i,int k);
void lin_check(void);
void col_check(void);
void blo_check(void);
void grid_update(void);
void ans_check(void);
void write_bit(int *num,int place);
int check_num_bit(int num);
int check_bit_num(int num);
bool check_bit(int num,int place);
int get_num_block(int i, int j);


int main()
{
    printf("input:\n");
    for(int i = 0;i < 9;i++)
    {
        for(int k = 0;k < 9 ;k++)
        {
            input_date(dat,i,k);
            printf("%d " ,dat[i][k]);
        }
        printf("\n");
    }
    printf("\n");

    //lin_check();
    //col_check();
    //blo_check();

    int num_repeat = 0;
    do
    {
        num_repeat++;
        grid_update();
        while(!grid_queue.empty())
        {
            build_grid tmp = *(grid_queue.top());
            if(tmp.ans != 0)
            {
                grid_queue.pop();
            }
            else
            {
                break;
            }
        }
    }while(!grid_queue.empty());
    ans_check();
    printf("repeat times: %d\n",num_repeat);
    cout << "Hello world!" << endl;
    return 0;
}

void input_date(int dat[9][9],int i,int j)
{
    if(dat[i][j] != 0)
    {
        int num_block = get_num_block(i,j);
        write_bit(&bool_lin[i],dat[i][j]);
        write_bit(&bool_col[j],dat[i][j]);
        write_bit(&bool_blo[num_block],dat[i][j]);
        grid[i][j].i = i;
        grid[i][j].j = j;
        grid[i][j].ans = dat[i][j];
        write_bit(&grid[i][j].bool_pro,dat[i][j]);
        grid[i][j].num_pro = 1;
    }
}

void lin_check(void)
{
    printf("line check\n");
    for(int i = 0;i < 9;i++)
    {
        for(int j = 1; j <= 9 ;j++)
        {
            printf("%d ",check_bit(bool_lin[i],j));
        }
        printf("\n");
    }
    printf("\n");
}

void col_check(void)
{
    printf("col check\n");
    for(int i = 0;i < 9;i++)
    {
        for(int j = 1; j <= 9 ;j++)
        {
            printf("%d ",check_bit(bool_col[i],j));
        }
        printf("\n");
    }
    printf("\n");
}

void blo_check(void)
{
    printf("blo check\n");
    for(int i = 0;i < 9;i++)
    {
        for(int j = 1; j <= 9 ;j++)
        {
            printf("%d ",check_bit(bool_blo[i],j));
        }
        printf("\n");
    }
    printf("\n");
}

void grid_update(void)
{
//    printf("check grid pro\n");
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0;j < 9 ;j++)
        {
            if(grid[i][j].ans == 0)
            {
                build_grid tmp;
                tmp.i = i;
                tmp.j = j;
                tmp.bool_pro = ~(bool_blo[get_num_block(i,j)] | bool_lin[i] | bool_col[j]);
                tmp.num_pro = check_num_bit(tmp.bool_pro);
                if(tmp.num_pro == 1)
                {
                    tmp.ans = check_bit_num(tmp.bool_pro);
                    write_bit(&bool_blo[get_num_block(i,j)],tmp.ans);
                    write_bit(&bool_lin[i],tmp.ans);
                    write_bit(&bool_col[j],tmp.ans);
                }
                grid[i][j] = tmp;
                grid_queue.push(&grid[i][j]);
            }
//            for(int k = 1 ; k <= 9;k++)
//            {
//                printf("%d" ,check_bit(grid[i][j].bool_pro,k));
//            }
//            printf("  %d",grid[i][j].num_pro);
//            printf("\n");
        }
//        printf("\n");
    }
//    printf("\n");
}

void ans_check(void)
{
    printf("ans:\n");
    for(int i = 0;i < 9;i++)
    {
        for(int j = 0; j< 9 ;j++)
        {
            printf("%d ",grid[i][j].ans);
        }
        printf("\n");
    }
}

int get_num_block(int i, int j)
{
    return 3 * (i / 3) + j / 3;
}

//place start from 1
void write_bit(int *num,int place)
{
    *num = *num | (1 << (place - 1));
}

//place start from 1
bool check_bit(int num,int place)
{
    bool tmp = (num >> (place-1) ) & 1;
    return tmp;
}

int check_bit_num(int num)
{
    for(int i = 1; i <= 9 ;i++)
    {
        if(check_bit(num,i) == 1)
        {
            return i;
        }
    }
    return 0;
}

//check the num of 1
int check_num_bit(int num)
{
    int num_bit = 0;
    for(int i = 1;i <= 9;i++)
    {
        if(check_bit(num,i) == 1)
        {
            num_bit++;
        }
    }
    return num_bit;
}
