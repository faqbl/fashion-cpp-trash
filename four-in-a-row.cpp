#include<iostream>
using namespace std;

int **a=new int*[6];//global variable to store the chessboard
//0 means empty,1 means player 1's chess,-1 means player 2's chess
int t=1,x=0,y=0;// t is the turn,x and y are the coordinates of the last placed chess
// x is the row index,y is the column index

void initiate()//initialize the chessboard,fill the whole array as 0
{
    for(int i=0;i<6;i++)
    {
        a[i]=new int[6];
    }
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
                a[i][j]=0;
        }
    }
}

int legal(char ch)//check if the input is valid
//if valid,return the row index of the chess to be placed,otherwise return -1
{
    if(ch>='1'&&ch<='6')
    {
        for(int i=5;i>=0;i--)
        {
            if(a[i][ch-'1']==0)
                return i;
        }
    }
        return -1;
}

bool not_over(int i,int j)//check if the coordinates are within the chessboard
{
    return i>=0&&i<6&&j>=0&&j<6;
}

void place(char ch)//place the chess on the board,if valid,update the coordinates and turn
{
    x=legal(ch),y=ch-'1';
    if(t%2)
        a[x][y]=1;
    else
        a[x][y]=-1;
    t++;//turn increse here to avoid turn increasing while the input is invalid
}

bool win1()//check if player 1 wins
{
    int i=x,j=y,z=0;//use i and j to represent x and y to start the check from the latest coordinate
    //use z as a counter
    while(not_over(i,j))
    {
        if(a[i][j]==1)
            z++;
        else
            break;
        i++;
    }
    if(z>=4)
        return true;//check the vertical direction,out of the gravity law,we just need to check the lower part
    z=0,i=x;//reset
    while(not_over(i,j))
    {
        if(a[i][j]==1)
            z++;
        else
            break;
        j++;
    }
    j=y-1;//check another direction but not include current coordinate because it has been counted above
    while(not_over(i,j))
    {
        if(a[i][j]==1)
            z++;
        else
            break;
        j--;
    }
    if(z>=4)
        return true;//check the horizontal direction
    z=0,j=y;
    while(not_over(i,j))
    {
        if(a[i][j]==1)
            z++;
        else
            break;
        i++,j++;
    }
    i=x-1,j=y-1;
    while(not_over(i,j))
    {
        if(a[i][j]==1)
            z++;
        else
            break;
        i--,j--;
    }
    if(z>=4)
        return true;//check the main diagonal direction
    z=0,i=x,j=y;
    while(not_over(i,j))
    {
        if(a[i][j]==1)
            z++;
        else
            break;
        i++,j--;
    }
    i=x-1,j=y+1;
    while(not_over(i,j))
    {
        if(a[i][j]==1)
            z++;
        else
            break;
        i--,j++;
    }
    if(z>=4)
        return true;//check the sub diagonal direction
    return false;
}

bool win2()//check if player 2 wins,use the same logic as win1
{
    int i=x,j=y,z=0;
    while(not_over(i,j))
    {
        if(a[i][j]==-1)
            z++;
        else
            break;
        i++;
    }
    if(z>=4)
        return true;
    z=0,i=x;
    while(not_over(i,j))
    {
        if(a[i][j]==-1)
            z++;
        else
            break;
        j++;
    }
    j=y-1;
    while(not_over(i,j))
    {
        if(a[i][j]==-1)
            z++;
        else
            break;
        j--;
    }
    if(z>=4)
        return true;
    z=0,j=y;
    while(not_over(i,j))
    {
        if(a[i][j]==-1)
            z++;
        else
            break;
        i++,j++;
    }
    i=x-1,j=y-1;
    while(not_over(i,j))
    {
        if(a[i][j]==-1)
            z++;
        else
            break;
        i--,j--;
    }
    if(z>=4)
        return true;
    z=0,i=x,j=y;
    while(not_over(i,j))
    {
        if(a[i][j]==-1)
            z++;
        else
            break;
        i++,j--;
    }
    i=x-1,j=y+1;
    while(not_over(i,j))
    {
        if(a[i][j]==-1)
            z++;
        else
            break;
        i--,j++;
    }
    if(z>=4)
        return true;
    return false;
}

bool tie()//check if the game is a tie by checking if the board is filled
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(a[i][j]==0)
                return false;
        }
    }
        return true;
}

void show()//display the current state of the chessboard
//O for player 1's chess,X for player 2's chess,_ for empty space
{
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<6;j++)
        {
            if(a[i][j]==1)
                cout<<"O ";
            else if(a[i][j]==-1)
                cout<<"X ";
            else
                cout<<"_ ";
        }
        cout<<endl;
    }
}

int main()
{
    initiate();
    show();//first of all,show the empty chessboard
    while(1)//use an unconditional loop to keep the game running until a player wins or a tie occurs
    {
        char ch;
        if(t%2)
            cout<<"Player 1 please input a number:";
        else
            cout<<"Player 2 please input a number:";//notice players to input their moves
        cin>>ch;//get a character as the input from the player
        if(legal(ch)==-1)//ask the player to input again until the input is valid
        {
            cout<<"Invalid input,please input again!"<<endl;
                continue;//turn shouldn't increase while the input is invalid
        }
        place(ch);//place the chess while the input is valid
        show();
        if(win1())
        {
            cout<<"Player 1 wins!"<<endl;
                break;
        }
        if(win2())
        {
            cout<<"Player 2 wins!"<<endl;
                break;
        }
        if(tie())
        {
            cout<<"Tie game."<<endl;
                break;
        }//announce the result of the game and exit the loop
    }
    for(int i=0;i<6;i++)
    {
        delete[] a[i];
    }
    delete[] a;//free the memory allocated for the chessboard
        return 0;
}
