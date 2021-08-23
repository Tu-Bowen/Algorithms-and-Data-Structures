#include<iostream>
#include<cstdlib>
#include<cstdbool>
#include<windows.h>
using namespace std;
class TicTacToe
{
private:
    //很棒的处理方法，利用一个整型数组来模拟一行，一列有三个相同的情况
    int iWin[8][3]={{0,1,2},
                    {3,4,5},
                    {6,7,8},//对行的检测
                    {0,3,6},
                    {1,4,7},
                    {2,5,8},//对列的检测
                    {0,4,8},
                    {2,4,6}};//对对角线检测
    //枚举就是一类特殊的整型，在程序中用于标记
    enum Players {Computer,Human,None,Drew}; //Computer,Human,None表示操作的是电脑还是人,还是当前位置没有放置棋子
                                             //Compuer,Human,None,Drew表示电脑赢，人赢，未分胜负平局四种状态
                                             //谨记：当对事物描绘的状态发生重叠时，要么放在一个枚举体中，要么对另一个枚举体进行赋值，否则可能会产生逻辑上的二义性
    int Person;//1代表人在玩，0代表电脑在玩
    //棋盘各个位置的状态
    int Field[9];
    //重置棋盘各个位置的状态
    void Reset();
    //绘制游戏图表
    void RePaint();
    //判断函数
    int Check_Field();
    //人下棋的函数
    void Human_Play();
    //电脑下棋的函数
    void Computer_Play();
public:
    //构造函数
    TicTacToe();
    //玩游戏
    void Play();
};
//构造函数，利用随机数函数选择由人先走还是电脑先走
TicTacToe::TicTacToe()
{
    //随机数，0代表电脑先走，1代表人先走
    Person=rand()%2;
    //重置棋局状态
    Reset();
}
//重置棋盘的函数
void TicTacToe::Reset()
{
    int i;
    //在这里None表示的是棋盘所有位置都没有棋子
    for(i=0; i<9; i++)
        Field[i]=None;
}
void TicTacToe::Play()//游戏主体函数
{
    int status=None;//棋局状态，初始设定为可继续下棋
    char Continue;
    while(true)
    {
        RePaint();
        while(true)
        {
            if(person==1)
            {
                Human_Play();
            }
            else
            {
                Computer_Play();
            }
            RePaint();//根据电脑和人的输入重绘棋盘
            status=Check_Field();//检查是否可以判定谁获胜
            if(status!=None)//如果胜负已分，结束本轮游戏的循环
                break;
            Person=(Person+1)%2;
        }
        if(status==Computer)
            cout<<"电脑获胜！"<<endl;
        if(status==Human)
            cout<<"人类获胜！"<<endl;
        if(status==Drew)
            cout<<"平局！"<<endl;
        cout<<endl<<endl<<endl;
        cout<<"是否再玩一局？"<<endl;
        cout<<"再来一局(Y/y)"<<endl;
        cout<<"不玩了(N/n)"<<endl;
        cin>>Continue;
        if(Continue=='n'||Continue=='N')
            return;
        if(Continue=='y'||Continue=='Y')
        {
            Person=(Person+1)%2;
            Reset();
        }
    }
}
//游戏开始时绘制棋盘，输入后重绘棋盘
void TicTacToe::RePaint()
{
    int x,y;//控制台的横纵坐标
    int nums=0;//用于控制棋盘状态下标
    system("CLS");
    //控制台的光标，就是控制类似打印的内容在什么地方出现，和修改打印的内容
    COORD place= {0,0};
    HANDLE hand=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hand,place);
    cout << "| 1 | 2 | 3 |" << endl;
    cout << "|-----------|" << endl;
    cout << "| 4 | 5 | 6 |" << endl;
    cout << "|-----------|" << endl;
    cout << "| 7 | 8 | 9 |" << endl;
    cout<<endl<<endl<<endl;
    for(y=0;y<5;y=y+2)
    {
        for(x=1;x<13;x=x+4)
        {
            if(Field[nums]!=No)
            {
                hand=GetStdHandle(STD_OUTPUT_HANDLE);
                place={x,y};
                SetConsoleCursorPosition(hand,place);
                if(Field[nums]==Computer)//如果是电脑操作的,利用在控制台上的光标修改为X符号
                cout<<"X";
                if(Field[nums]==Human)//如果是人操作的，利用在控制台上的光标修改为O符号
                cout<<"O";
            }
            nums++;
        }
    }
    //设置控制台光标的位置，打印语句
    place.y=9
    hand=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hand,place);
}
//检查棋盘，判断胜负
int TicTacToe::Check_Field()
{
    int i=0,nums=0;
    //检查行与列以及对角线
    for(i=0;i<8;i++)
    {
        if(Field[iWin[i][0]]!=None&&Field[iWin[i][0]]==Field[iWin[i][1]]&&Field[iWin[i][1]]==Field[iWin[i][2])
            return Field[iWin[i][0]];
    }
    //如果上述检测都没有符合的，就是目前没有胜负，用循环检测整个棋盘
    for(i=0;i<9;i++)
    {
        if(Field[i]!=None)
            nums++;
    }
    if(nums<9)//表示棋盘没有满，还可以继续下棋
        return None;
    if(nums==9)//表示棋盘已满，但是不能判定胜负
        return Drew;
}
//人进行输入的函数
void TicTacToe::Human_Play()
{

}
//电脑进行输入的函数
void TicTacToe::Computer_Play()
{

}
int main()
{
    return 0;
}

















/*#include <windows.h>
#include <iostream>
#include <string>

//--------------------------------------------------------------------------------------------------
using namespace std;

//--------------------------------------------------------------------------------------------------
//定义四种情况 人机进行对弈
enum players { Computer, Human, Draw, None };
//可能赢的情况，一行一列或者是对角
const int iWin[8][3] = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };

//--------------------------------------------------------------------------------------------------
//井字游戏类
class ttt
{
public:
    //构造方法
    ttt()
    {
        //轮到谁走，如果_p=1，人走；否则电脑走
        _p = rand() % 2;
        //重新置为空，即原始状态
        reset();
    }
    //游戏函数
    void play()
    {
        //res表示最终结果，初始值为平局
        int res = Draw;
        //死循环
        while( true )
        {
            //给出3*3的格子
            drawGrid();
            //内层死循环
            while( true )
            {
                //轮到人走
                if( _p ) getHumanMove();
                //轮到电脑走
                else getComputerMove();
                //继续根据人和电脑下的棋子，画出3*3的棋局
                drawGrid();
                //判断人与电脑谁赢
                res = checkVictory();
                //如果当前棋局状态已经可以判断出输赢，跳出内层死循环
                if( res != None )
                    break;
                //计数器+1，判断下一个是谁走
                ++_p %= 2;
            }
            //如果res是Human，那么人赢了
            if( res == Human )
                cout << "CONGRATULATIONS HUMAN --- You won!";
            //如果res是Computer，那么人输了
            else if( res == Computer )
                cout << "NOT SO MUCH A SURPRISE --- I won!";
            //平局
            else
                cout << "It's a draw!";

            cout << endl << endl;

            string r;
            //输入是否还在玩一局
            cout << "Play again( Y / N )? ";
            cin >> r;
            //当选择不玩下一局，即退出游戏，跳出外层死循环
            if( r != "Y" && r != "y" )
                return;
            //计数器+1,
            ++_p %= 2;
            //重置棋局状态
            reset();

        }
    }

private:
    //棋局最开始的状态函数
    void reset()
    {
        for( int x = 0; x < 9; x++ )
            _field[x] = None;
    }
    //分别给格子进行赋值
    void drawGrid()
    {
        //清屏
        system( "cls" );
        //定义控制台屏幕初始坐标
        COORD c = { 0, 2 };
        //设置控制台光标位置
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );
        //棋局初始状态
        cout << " 1 | 2 | 3 " << endl;
        cout << "---+---+---" << endl;
        cout << " 4 | 5 | 6 " << endl;
        cout << "---+---+---" << endl;
        cout << " 7 | 8 | 9 " << endl << endl << endl;
        //棋子计数器
        int f = 0;
        for( int y = 0; y < 5; y += 2 ) //纵坐标
            for( int x = 1; x < 11; x += 4 ) //横坐标
            {
                //如果格子已经被用过，即有棋子
                if( _field[f] != None )
                {
                    //光标位置坐标
                    COORD c = { x, 2 + y };
                    //设置控制台光标位置
                    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );//GetStdHandle函数获得句柄
                    //判断当前下棋子的人是否为电脑，如果是电脑即输出X，否则输出O
                    string o = _field[f] == Computer ? "X" : "O";
                    cout << o;
                }
                //棋子个数+1
                f++;
            }

        c.Y = 9;
        //设置控制台光标位置
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );
    }
    //判断当前棋局是否可以判断输赢
    int checkVictory()
    {
        //如果有一行一列或者是对角，那么就表示已经赢了
        for( int i = 0; i < 8; i++ )
        {
            if( _field[iWin[i][0]] != None &&
                    _field[iWin[i][0]] == _field[iWin[i][1]] && _field[iWin[i][1]] == _field[iWin[i][2]] )
            {
                //赢的状态是人还是电脑取决于_field[iWin[i][0]]的值
                return _field[iWin[i][0]];
            }
        }
        //i表示棋子个数
        int i = 0;
        for( int f = 0; f < 9; f++ )
        {
            //如果当前格子已经有棋子，i+=1
            if( _field[f] != None )
                i++;
        }
        //如果已经有9个格子有棋子，那么就是一个平局状态
        if( i == 9 )
            return Draw;
        //None表示还可以继续下棋子，未分出胜负
        return None;
    }
    //人进行下棋子
    void getHumanMove()
    {
        int m;
        cout << "Enter your move ( 1 - 9 ) ";
        //开始死循环
        while( true )
        {
            m = 0;
            //输入想要下的棋子的格子编号
            cin >> m;
            //如果第m个格子已经有气质，表示是无效输入
            if( _field[m - 1] != None )
                cout << "Invalid move. Try again!" << endl;
            //否则为有效输入，跳出死循环
            else
                break;
        }
        //将第m个格子标记为人下的棋子
        _field[m - 1] = Human;
    }
    //电脑进行下棋子
    void getComputerMove()
    {
        //定义一个电脑想要下的棋子的格子编号
        int move = 0;
        do
        {
            //随机取得一个值
            move = rand() % 9;
        }
        //只要这个格子里没有棋子
        while( _field[move] != None );
        //对赢的状态进行枚举
        for( int i = 0; i < 8; i++ )
        {
            //try1、try2和try3表示可能赢的3个格子坐标
            int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];
            //如果try1和try2已经有棋子，并且下棋子的玩家是一样的，而且try3没有棋子
            if( _field[try1] != None && _field[try1] == _field[try2] && _field[try3] == None )
            {
                //电脑会将棋子下载try3这个格子上
                move = try3;
                //如果try1这个格子的棋子是电脑，那么电脑赢了，游戏结束
                if( _field[try1] == Computer )
                    break;
            }
            //如果try1和try3已经有棋子，并且下棋子的玩家是一样的，而且try2没有棋子
            if( _field[try1] != None && _field[try1] == _field[try3] && _field[try2] == None )
            {
                //电脑会将棋子下载try2这个格子上
                move = try2;
                //如果try1这个格子的棋子是电脑，那么电脑赢了，游戏结束
                if( _field[try1] == Computer )
                    break;
            }
            //如果try2和try3已经有棋子，并且下棋子的玩家是一样的，而且try1没有棋子
            if( _field[try2] != None && _field[try2] == _field[try3] && _field[try1] == None )
            {
                //电脑会将棋子下载try1这个格子上
                move = try1;
                //如果try2这个格子的棋子是电脑，那么电脑赢了，游戏结束
                if( _field[try2] == Computer )
                    break;
            }
        }
        //将第move个格子标记为电脑下的棋子
        _field[move] = Computer;

    }

    //计数器，用来判断当前的玩家是谁
    int _p;
    //格子状态
    int _field[9];
};
//--------------------------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    //随机初始化
    srand( GetTickCount() );
    //定义井字游戏的实例对象tic
    ttt tic;
    //开始进行游戏
    tic.play();

    return 0;
}*/
