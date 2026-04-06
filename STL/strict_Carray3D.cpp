#include <iostream>
#include <iomanip> 
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
// 在此处补充你的代码
public:
    T* data;
	int x,y,z;
	CArray3D(int a,int b,int c):x(a),y(b),z(c){data=new T [a*b*c];}
	~CArray3D(){delete[] data;}
	class dim1{
	public:
		int d0,x,y,z;
		CArray3D* father;
		dim1(int idx,CArray3D*t):d0(idx),father(t),x(t->x),y(t->y),z(t->z){};
		operator void* (){
			return &(father->data)[d0*y*z];
		}
		class dim2{
			public:
			int d0,d1,x,y,z;
			dim1* father;
			dim2(int a,dim1* f):d0(f->d0),d1(a),father(f),x(f->x),y(f->y),z(f->z){}
			operator void* (){
				return &(father->father->data)[d0*y*z+d1*z];
			}
			T& operator[](int idx){
				return (father->father->data)[d0*y*z+d1*z+idx];
			}
		};
		dim2 operator[](int idx){
			dim2 temp(idx,this);
			return temp;
		}
	};
	dim1 operator[](int idx){
		dim1 temp(idx,this);
		return temp;
	}
//
};

CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 4; ++j) {
			for(int k = 0; k < 5; ++k) 
				cout << a[i][j][k] << "," ;
			cout << endl;
		}
	}
}
void PrintB()
{
	for(int i = 0;i < 3; ++i) {
		cout << "layer " << i << ":" << endl;
		for(int j = 0; j < 2; ++j) {
			for(int k = 0; k < 2; ++k) 
				cout << b[i][j][k] << "," ;
			cout << endl;
		}
	}
}

int main()
{

	int No = 0;
	for( int i = 0; i < 3; ++ i ) {
		a[i];
		for( int j = 0; j < 4; ++j ) {
			a[j][i];
			for( int k = 0; k < 5; ++k )
				a[i][j][k] = No ++;
			a[j][i][i];	
		}
	}
	PrintA();
	memset(a[1],-1 ,20*sizeof(int));	
	memset(a[1],-1 ,20*sizeof(int));
	PrintA(); 
	memset(a[1][1],0 ,5*sizeof(int));	
	PrintA();

	for( int i = 0; i < 3; ++ i )
		for( int j = 0; j < 2; ++j )
			for( int k = 0; k < 2; ++k )
				b[i][j][k] = 10.0/(i+j+k+1);
	PrintB();
	int n = a[0][1][2];
	double f = b[0][1][1];
	cout << "****" << endl;
	cout << n << "," << f << endl;
		
	return 0;
}