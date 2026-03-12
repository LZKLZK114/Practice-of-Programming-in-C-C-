/*输入
无
输出
3+4i
5+6i*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 在此处补充你的代码
Complex operator=(string s){
        string re,im;
        for(int j=0;j<s.size();j++){
            if(s[j]=='+'){
                re=s.substr(0,j);
                im=s.substr(j+1,s.size()-j-2);
                r=atof(re.c_str());
                i=atof(im.c_str());
                break;
            }
        }
        return *this;
    }
//
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}