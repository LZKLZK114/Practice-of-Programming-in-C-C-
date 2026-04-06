#include <iostream>
using namespace std;
class MyCin
{
// 在此处补充你的代码
public:
    bool flag;
    MyCin(){flag=true;}
    MyCin& operator >>(int& t){
        cin>>t;
        if(t==-1) flag=false;
        return *this;
    }
    operator bool(){
        return flag;
    }
//
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}