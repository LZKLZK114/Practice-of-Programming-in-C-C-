/*输入
多组数据，每组数据是两个非负整数s和 n。s最多可能200位， n用int能表示
输出
对每组数据，输出6行，内容对应程序中6个输出语句
样例输入
99999999999999999999999999888888888888888812345678901234567789 12
6 6
样例输出
99999999999999999999999999888888888888888812345678901234567801
99999999999999999999999999888888888888888812345678901234567801
99999999999999999999999999888888888888888812345678901234567801
25
25
26
12
12
12
13
13
14*/
#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
// 在此处补充你的代码
 int num[MAX*2];
public:
    CHugeInt(char *HatsuneMiku){
        memset(num, 0, sizeof(num));
        int len=strlen(HatsuneMiku);
        for(int i=0;i<len;i++){
            num[i]=HatsuneMiku[len-1-i]-'0';
        }    
    }
    CHugeInt(int n){
         memset(num, 0, sizeof(num));
        int i=0;
        while(n){
            num[i++]=n%10;
            n/=10;
        }
    }
    CHugeInt operator+(const CHugeInt &b) {
        CHugeInt c(0);
        int carry=0;
        for(int i=0;i<MAX*2;i++){
            int sum=num[i]+b.num[i]+carry;
            c.num[i]=sum%10;
            carry=sum/10;
        }
        return c;
    }
    CHugeInt operator+(const int &b) {
        CHugeInt c(b);
        return *this+c;
    }
    friend CHugeInt operator+(const int &a,const CHugeInt &b){
        CHugeInt c(a);
        return c+b;
    }
    CHugeInt& operator+=(const int &b){
        *this=*this+b;
        return *this;
    }
    CHugeInt& operator++(){
        *this=*this+1;
        return *this;
    }
    CHugeInt operator++(int){
        CHugeInt temp=*this;
        *this=*this+1;
        return temp;
    }
    friend ostream& operator<<(ostream &out,const CHugeInt &a){
        int i=MAX*2-1;
        while(i>=0&&a.num[i]==0) i--;
        if(i==-1) out<<0;
        else{
            for(;i>=0;i--){
                out<<a.num[i];
            }
        }
        return out;
    }
//
};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}