/*输入
多组数据，每组一行，是整数 m 和 n
输出
先输出一行：
123
然后，对每组数据，输出两行，第一行是m,第二行是n*/
#include <iostream>
using namespace std;
class A {
public:
	int val;

	A(int
// 在此处补充你的代码
 m){val=m;}
    A(){val=123;}
    A& GetObj() {
        return *this;
    }
    A& operator = (int m) {
        val = m;
        return *this;
    }
private:
//
};
int main()
{
	int m,n;
	A a;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val<< endl;
	}
	return 0;
}