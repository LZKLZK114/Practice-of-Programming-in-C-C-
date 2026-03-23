/*描述
程序填空产生指定输出

输入
无
输出
D::Fun
B::Fun
D::Fun
nBVal=2
nBVal=24
nDVal=8
B::Fun
nBVal=12
*/
#include <iostream>
using namespace std;
class B { 
	private: 
		int nBVal; 
	public: 
		void Print() 
		{ cout << "nBVal="<< nBVal << endl; } 
		void Fun() 
		{cout << "B::Fun" << endl; } 
		B ( int n ) { nBVal = n;} 
};
// 在此处补充你的代码
class D: public B{
    private:
        int dv;
    public:
        D(int a):B(a*3){dv=a;}
		void Fun(){cout<<"D::Fun"<<endl;}
		void Print(){cout << "nBVal="<< dv*3 << endl<<"nDVal="<<dv<<endl; }
};
//
int main() { 
	B * pb; D * pd; 
	D d(4); d.Fun(); 
	pb = new B(2); pd = new D(8); 
	pb -> Fun(); pd->Fun(); 
	pb->Print (); pd->Print (); 
	pb = & d; pb->Fun(); 
	pb->Print(); 
	return 0;
}