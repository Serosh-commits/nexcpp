//how to make a bank system using class concept
#include<iostream>
#include<string>
#include<time.h>
using namespace std;
class bank
{
    private:
    int id;
    int balance;
    public:
    string name;
    int in;
    int upi;
    void deposit(int amount)
    {     
        in+=amount;
        cout<<"the current balance is"<<in<<endl;        
    }
    void with(int amount)
    {
        in-=amount;
        cout<<"the current balance is"<<in<<endl;
    }
};
int main()
{
    int y;
    string n;
    int amount;
    int ch;
    cout<<"enter the name of the user"<<endl;
    cin>>n;
    cout<<"enter what do u want to do deposit(d) or withdraw(w)"<<endl;
    cin>>ch;
    bank user;
    srand(time(NULL));
    int x=rand();
    user.upi=x;
    user.name=n;
    user.in=1000;
    if(ch=1)
    {
        cout<<"enter the amount u want to deposit"<<endl;
        cin>>amount;
        user.deposit(amount);
    }
    else if(ch=0)
    {
        cout<<"enter the aamount u want to wihtdraw"<<endl;
        cin>>amount;
        user.with(amount);
    }
    else
    {
        cout<<"the total balance is"<<user.in<<endl;
    }
    return 0;
}
