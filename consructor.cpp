#include<iostream>
using namespace std;
class ent
{
    public :
    int X,Y;
    ent()//default constructor set by default 
    {
    }
    ent (int x,int y) //constructors with parameters
    {
        X=x;
        Y=y;
    }
    void print()
    {
        cout<<X<<endl<<Y<<endl;
    }
};
class log 
{
    private:
    log();//if u don't want to give a access to constructor hide it in private as i don't want to use this default constructer so i kept it in the private 
    public:
    int num;
    log (int x)
    {
        num=x;
        cout<<num<<endl;
    }
};
int main()
{
    
    log u(20);
    int i=0;
    int h,m;
    ent e;
    srand(time(NULL));
    while(i<20)
    {
        h=rand();
        m=rand();
        ent e(h,m);
        e.print();
        i++;
    }
    return 0;
}
