/*输入
多组数据，每组两个整数
输出
对每组数据，输出一行，就是输入的两个整数*/
#include <iostream> 
using namespace std;
class Point { 
	private: 
		int x; 
		int y; 
	public: 
		Point() { };
// 在此处补充你的代码
friend istream& operator>>(istream&is,Point&p){
        is>>p.x>>p.y;
        return is;
    }
    friend ostream& operator<<(ostream&os,const Point&p){
        os<<p.x<<","<<p.y;
        return os;
    }
//
}; 
int main() 
{ 
 	Point p;
 	while(cin >> p) {
 		cout << p << endl;
	 }
	return 0;
}