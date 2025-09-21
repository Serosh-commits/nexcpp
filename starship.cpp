#include<iostream>
#include<string>
#include<time.h>
using namespace std;
class ship
{
    private:
    int shields;
    public:
    int pos;
    string name;
    //constructor and its types 
    ship (int x,string nam)
    {
        pos=x;
        name=nam;
        cout<<name<<endl<<pos<<endl;
    }
    
};
int main()
{
    string num;
    srand(time(NULL));
    int i=0,x;
        int ch=rand();
        cin>>num;
        ship(ch,num);
    return 0;
}