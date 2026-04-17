/*输入
多组数据
每组数据：
第一行是整数 n , 1 <= n < 20;
第二行是n个整数 k1,k2... kn,均在范围 [0,19]内。
第三行是 四个整数 i1,j1,k1,v1 。 0 <= i1,j1,k1 <= 19, v1值为0或1
第三行是 四个整数 i2,j2,k2,v2 。 0 <= i2,j2,k2 <= 19, v2值为0或1
输出
对每组数据，共输出3行，每行20位，每位为1或者0。最左边称为第0位
第一行： 第 k1,k2 ... kn位为1，其余位为0。
第二行： 将第一行中的第 i1,j1,k1位变为 v1,其余位不变
第三行： 将第二行中的第i2位和k2位变为v2，其余位不变*/
#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset 
{
	char a[bitNum/8+1];
	MyBitset() { memset(a,0,sizeof(a));};
	void Set(int i,int v) {
		char & c = a[i/8];
		int bp = i % 8;
		if( v ) 
			c |= (1 << bp);
		else 
			c &= ~(1 << bp);
	}
// 在此处补充你的代码
    struct inner_bits{
        int v;
        int idx;
        MyBitset* father;
        inner_bits(int a,int b,MyBitset* f){v=a;idx=b;father=f;}
        int operator=(int a){
            v=a;
            (*father).Set(idx,a);            
            return a;
        }
        friend ostream& operator <<(ostream&os,const inner_bits&a){
            os<<a.v;
            return os;
        }
        inner_bits& operator=(const inner_bits& a){
            *this=a.v;
            return *this;
        }
    };
    inner_bits operator[](int k){
        char c=a[k/8];
        int bias=k%8;
        int v=!!(c&(1<<bias));
        return inner_bits(v,k,this);
    }
//
void Print() {
		for(int i = 0;i < bitNum; ++i) 
			cout << (*this) [i];
		cout << endl;
	}

};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}