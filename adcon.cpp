//biggest code till lol;
#include<iostream>
#include<string.h>
#include<utility>//for std::move 
using namespace std;
class ent
{
    public:
    int x,y;
    string *crew;
    int size,i;
    ent (int n,string name):size(n)
    {
        if(n<0)
        {
            cout<<"invalid"<<endl;
        }
        else
        {
        crew=new string[n];
        for(i=0;i<n;i++)
        {
            //method to dynamically creating array or string use new
            string c=to_string(i);
            crew[i]=name+c;
            cout<<crew[i]<<endl;
        }
    }
    }
    ent (const ent& other):size(other.size),crew(nullptr)//copy constructor 
    {
            crew=new string[size];//method to dynamically creating array or string use new
            for(i=0;i<size;i++)
        {
            crew[i]=other.crew[i];
            cout<<crew[i]<<endl;
        }
    }
    ent (ent&& other) noexcept : crew(other.crew),size(other.size)//move constructor thsi uses && for ref 
    {
        other.crew=nullptr;
        other.size=0;
    }
    void display()
    {

        if(!crew)
        {
            cout<<"this is empty "<<endl;
            return;
        }
        else
        {
        for (int i = 0; i < size; i++) cout << crew[i] << " ";
        cout << endl;
        }
    }
~ent()//his is an destructor don't write it after the functions that is been used functions used before will not work
{
    cout<<"object destroyed"<<endl;
}
};
int main()
{
    
    int x;
    cout<<"enter the number of crew want to make";
    cin>>x;
    if(x<0)
    {
        cout<<"invlaid try something else"<<endl;
    }
    ent e(x,"crew");
    e.display();
    ent e1=e;//this is shallow constructor
    e1.display();
    ent e2=move(e);
    e.display();
    e2.display();
    e.~ent();
    return 0;
}