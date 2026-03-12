/*程序填空，使其输出9 22 5*/
#include <iostream>
using namespace std;
class Sample {
public:
	int v;
// 在此处补充你的代码
 Sample(const Sample& txy){
        v=txy.v+2;
    }
    Sample(int dyz){v=dyz;}
    Sample() {v=0;}
    Sample operator=(int zyq){
        v=zyq;
        return *this;
    }
//
};
void PrintAndDouble(Sample o)
{
	cout << o.v;
	cout << endl;
}
int main()
{
	Sample a(5);
	Sample b = a;
	PrintAndDouble(b);
	Sample c = 20;
	PrintAndDouble(c);
	Sample d;
	d = a;
	cout << d.v;
	return 0;
}