#include<iostream>
#include<cstdlib>
#include<cstdbool>
#include<windows.h>
using namespace std;
class TicTacToe
{
private:
    //�ܰ��Ĵ�����������һ������������ģ��һ�У�һ����������ͬ�����
    int iWin[8][3]={{0,1,2},
                    {3,4,5},
                    {6,7,8},//���еļ��
                    {0,3,6},
                    {1,4,7},
                    {2,5,8},//���еļ��
                    {0,4,8},
                    {2,4,6}};//�ԶԽ��߼��
    //ö�پ���һ����������ͣ��ڳ��������ڱ��
    enum Players {Computer,Human,None,Drew}; //Computer,Human,None��ʾ�������ǵ��Ի�����,���ǵ�ǰλ��û�з�������
                                             //Compuer,Human,None,Drew��ʾ����Ӯ����Ӯ��δ��ʤ��ƽ������״̬
                                             //���ǣ�������������״̬�����ص�ʱ��Ҫô����һ��ö�����У�Ҫô����һ��ö������и�ֵ��������ܻ�����߼��ϵĶ�����
    int Person;//1���������棬0�����������
    //���̸���λ�õ�״̬
    int Field[9];
    //�������̸���λ�õ�״̬
    void Reset();
    //������Ϸͼ��
    void RePaint();
    //�жϺ���
    int Check_Field();
    //������ĺ���
    void Human_Play();
    //��������ĺ���
    void Computer_Play();
public:
    //���캯��
    TicTacToe();
    //����Ϸ
    void Play();
};
//���캯�����������������ѡ���������߻��ǵ�������
TicTacToe::TicTacToe()
{
    //�������0����������ߣ�1����������
    Person=rand()%2;
    //�������״̬
    Reset();
}
//�������̵ĺ���
void TicTacToe::Reset()
{
    int i;
    //������None��ʾ������������λ�ö�û������
    for(i=0; i<9; i++)
        Field[i]=None;
}
void TicTacToe::Play()//��Ϸ���庯��
{
    int status=None;//���״̬����ʼ�趨Ϊ�ɼ�������
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
            RePaint();//���ݵ��Ժ��˵������ػ�����
            status=Check_Field();//����Ƿ�����ж�˭��ʤ
            if(status!=None)//���ʤ���ѷ֣�����������Ϸ��ѭ��
                break;
            Person=(Person+1)%2;
        }
        if(status==Computer)
            cout<<"���Ի�ʤ��"<<endl;
        if(status==Human)
            cout<<"�����ʤ��"<<endl;
        if(status==Drew)
            cout<<"ƽ�֣�"<<endl;
        cout<<endl<<endl<<endl;
        cout<<"�Ƿ�����һ�֣�"<<endl;
        cout<<"����һ��(Y/y)"<<endl;
        cout<<"������(N/n)"<<endl;
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
//��Ϸ��ʼʱ�������̣�������ػ�����
void TicTacToe::RePaint()
{
    int x,y;//����̨�ĺ�������
    int nums=0;//���ڿ�������״̬�±�
    system("CLS");
    //����̨�Ĺ�꣬���ǿ������ƴ�ӡ��������ʲô�ط����֣����޸Ĵ�ӡ������
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
                if(Field[nums]==Computer)//����ǵ��Բ�����,�����ڿ���̨�ϵĹ���޸�ΪX����
                cout<<"X";
                if(Field[nums]==Human)//������˲����ģ������ڿ���̨�ϵĹ���޸�ΪO����
                cout<<"O";
            }
            nums++;
        }
    }
    //���ÿ���̨����λ�ã���ӡ���
    place.y=9
    hand=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hand,place);
}
//������̣��ж�ʤ��
int TicTacToe::Check_Field()
{
    int i=0,nums=0;
    //����������Լ��Խ���
    for(i=0;i<8;i++)
    {
        if(Field[iWin[i][0]]!=None&&Field[iWin[i][0]]==Field[iWin[i][1]]&&Field[iWin[i][1]]==Field[iWin[i][2])
            return Field[iWin[i][0]];
    }
    //���������ⶼû�з��ϵģ�����Ŀǰû��ʤ������ѭ�������������
    for(i=0;i<9;i++)
    {
        if(Field[i]!=None)
            nums++;
    }
    if(nums<9)//��ʾ����û�����������Լ�������
        return None;
    if(nums==9)//��ʾ�������������ǲ����ж�ʤ��
        return Drew;
}
//�˽�������ĺ���
void TicTacToe::Human_Play()
{

}
//���Խ�������ĺ���
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
//����������� �˻����ж���
enum players { Computer, Human, Draw, None };
//����Ӯ�������һ��һ�л����ǶԽ�
const int iWin[8][3] = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };

//--------------------------------------------------------------------------------------------------
//������Ϸ��
class ttt
{
public:
    //���췽��
    ttt()
    {
        //�ֵ�˭�ߣ����_p=1�����ߣ����������
        _p = rand() % 2;
        //������Ϊ�գ���ԭʼ״̬
        reset();
    }
    //��Ϸ����
    void play()
    {
        //res��ʾ���ս������ʼֵΪƽ��
        int res = Draw;
        //��ѭ��
        while( true )
        {
            //����3*3�ĸ���
            drawGrid();
            //�ڲ���ѭ��
            while( true )
            {
                //�ֵ�����
                if( _p ) getHumanMove();
                //�ֵ�������
                else getComputerMove();
                //���������˺͵����µ����ӣ�����3*3�����
                drawGrid();
                //�ж��������˭Ӯ
                res = checkVictory();
                //�����ǰ���״̬�Ѿ������жϳ���Ӯ�������ڲ���ѭ��
                if( res != None )
                    break;
                //������+1���ж���һ����˭��
                ++_p %= 2;
            }
            //���res��Human����ô��Ӯ��
            if( res == Human )
                cout << "CONGRATULATIONS HUMAN --- You won!";
            //���res��Computer����ô������
            else if( res == Computer )
                cout << "NOT SO MUCH A SURPRISE --- I won!";
            //ƽ��
            else
                cout << "It's a draw!";

            cout << endl << endl;

            string r;
            //�����Ƿ�����һ��
            cout << "Play again( Y / N )? ";
            cin >> r;
            //��ѡ������һ�֣����˳���Ϸ�����������ѭ��
            if( r != "Y" && r != "y" )
                return;
            //������+1,
            ++_p %= 2;
            //�������״̬
            reset();

        }
    }

private:
    //����ʼ��״̬����
    void reset()
    {
        for( int x = 0; x < 9; x++ )
            _field[x] = None;
    }
    //�ֱ�����ӽ��и�ֵ
    void drawGrid()
    {
        //����
        system( "cls" );
        //�������̨��Ļ��ʼ����
        COORD c = { 0, 2 };
        //���ÿ���̨���λ��
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );
        //��ֳ�ʼ״̬
        cout << " 1 | 2 | 3 " << endl;
        cout << "---+---+---" << endl;
        cout << " 4 | 5 | 6 " << endl;
        cout << "---+---+---" << endl;
        cout << " 7 | 8 | 9 " << endl << endl << endl;
        //���Ӽ�����
        int f = 0;
        for( int y = 0; y < 5; y += 2 ) //������
            for( int x = 1; x < 11; x += 4 ) //������
            {
                //��������Ѿ����ù�����������
                if( _field[f] != None )
                {
                    //���λ������
                    COORD c = { x, 2 + y };
                    //���ÿ���̨���λ��
                    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );//GetStdHandle������þ��
                    //�жϵ�ǰ�����ӵ����Ƿ�Ϊ���ԣ�����ǵ��Լ����X���������O
                    string o = _field[f] == Computer ? "X" : "O";
                    cout << o;
                }
                //���Ӹ���+1
                f++;
            }

        c.Y = 9;
        //���ÿ���̨���λ��
        SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), c );
    }
    //�жϵ�ǰ����Ƿ�����ж���Ӯ
    int checkVictory()
    {
        //�����һ��һ�л����ǶԽǣ���ô�ͱ�ʾ�Ѿ�Ӯ��
        for( int i = 0; i < 8; i++ )
        {
            if( _field[iWin[i][0]] != None &&
                    _field[iWin[i][0]] == _field[iWin[i][1]] && _field[iWin[i][1]] == _field[iWin[i][2]] )
            {
                //Ӯ��״̬���˻��ǵ���ȡ����_field[iWin[i][0]]��ֵ
                return _field[iWin[i][0]];
            }
        }
        //i��ʾ���Ӹ���
        int i = 0;
        for( int f = 0; f < 9; f++ )
        {
            //�����ǰ�����Ѿ������ӣ�i+=1
            if( _field[f] != None )
                i++;
        }
        //����Ѿ���9�����������ӣ���ô����һ��ƽ��״̬
        if( i == 9 )
            return Draw;
        //None��ʾ�����Լ��������ӣ�δ�ֳ�ʤ��
        return None;
    }
    //�˽���������
    void getHumanMove()
    {
        int m;
        cout << "Enter your move ( 1 - 9 ) ";
        //��ʼ��ѭ��
        while( true )
        {
            m = 0;
            //������Ҫ�µ����ӵĸ��ӱ��
            cin >> m;
            //�����m�������Ѿ������ʣ���ʾ����Ч����
            if( _field[m - 1] != None )
                cout << "Invalid move. Try again!" << endl;
            //����Ϊ��Ч���룬������ѭ��
            else
                break;
        }
        //����m�����ӱ��Ϊ���µ�����
        _field[m - 1] = Human;
    }
    //���Խ���������
    void getComputerMove()
    {
        //����һ��������Ҫ�µ����ӵĸ��ӱ��
        int move = 0;
        do
        {
            //���ȡ��һ��ֵ
            move = rand() % 9;
        }
        //ֻҪ���������û������
        while( _field[move] != None );
        //��Ӯ��״̬����ö��
        for( int i = 0; i < 8; i++ )
        {
            //try1��try2��try3��ʾ����Ӯ��3����������
            int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];
            //���try1��try2�Ѿ������ӣ����������ӵ������һ���ģ�����try3û������
            if( _field[try1] != None && _field[try1] == _field[try2] && _field[try3] == None )
            {
                //���ԻὫ��������try3���������
                move = try3;
                //���try1������ӵ������ǵ��ԣ���ô����Ӯ�ˣ���Ϸ����
                if( _field[try1] == Computer )
                    break;
            }
            //���try1��try3�Ѿ������ӣ����������ӵ������һ���ģ�����try2û������
            if( _field[try1] != None && _field[try1] == _field[try3] && _field[try2] == None )
            {
                //���ԻὫ��������try2���������
                move = try2;
                //���try1������ӵ������ǵ��ԣ���ô����Ӯ�ˣ���Ϸ����
                if( _field[try1] == Computer )
                    break;
            }
            //���try2��try3�Ѿ������ӣ����������ӵ������һ���ģ�����try1û������
            if( _field[try2] != None && _field[try2] == _field[try3] && _field[try1] == None )
            {
                //���ԻὫ��������try1���������
                move = try1;
                //���try2������ӵ������ǵ��ԣ���ô����Ӯ�ˣ���Ϸ����
                if( _field[try2] == Computer )
                    break;
            }
        }
        //����move�����ӱ��Ϊ�����µ�����
        _field[move] = Computer;

    }

    //�������������жϵ�ǰ�������˭
    int _p;
    //����״̬
    int _field[9];
};
//--------------------------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    //�����ʼ��
    srand( GetTickCount() );
    //���微����Ϸ��ʵ������tic
    ttt tic;
    //��ʼ������Ϸ
    tic.play();

    return 0;
}*/
