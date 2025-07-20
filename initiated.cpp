#include<iostream>
#include<iomanip>//for setw and setfill
#include<unistd.h>//for usleep
#include<conio.h>//for _kbhit and cin.get
#include<cstdlib>//for exit
using namespace std;
class Time//class to handle time countdown
{
    private:
        int hour,minute,second;//attributes to store hours,minutes,and seconds
    public:
        Time():hour(0),minute(0),second(0){}//initialize
        Time(int h,int m,int s):hour(h),minute(m),second(s){}//set
        ~Time(){}//destructor
        void notice()
        {
            cout<<"Please input three numbers to represent hours,minutes and seconds,while counting down,press any botton to stop:"<<endl;
        }
        void run()
        {
            second--;
            if(second<0)//if seconds reach below 0,reduce minute
            {
                second=59;
                minute--;
                if(minute<0)//if minutes reach below 0,reduce hour
                {
                    minute=59;
                    hour--;
                    if(hour<0)//if hours reach below 0,halt
                    {
                        cout<<endl<<"Time out!";
                        exit(0);
                    }
                }
            }
        }
        void sleep()//sleep for 1 second to simulate countdown
        {
            usleep(1000000);//sleep for 1 second
            cout<<'\r';//return to the beginning of the line to cover the previous output
            cout<<flush;//flush the output buffer to ensure the display is updated
        }
        void stop()
        {
            if(_kbhit())//if any botton is pressed
                cin.get();//consume the input to prevent it from being processed again
        }
        void display()//show the current time in HH:MM:SS format
        {
            cout<<fixed<<setw(2)<<setfill('0')<<hour<<":"
                <<fixed<<setw(2)<<setfill('0')<<minute<<":"
                <<fixed<<setw(2)<<setfill('0')<<second;
        }
};

int main()
{
    int h,m,s;
    Time t;
    t.notice();
    cin>>h>>m>>s;
    t=Time(h,m,s);
    while(1)//when the countdown is not finished,continue to loop
    {
        t.display();
        t.run();
        t.sleep();
        t.stop();
    }
        return 0;
}