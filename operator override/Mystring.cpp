/*输入
多组数据，每组一行，是两个不带空格的字符串
输出
对每组数据，先输出一行，打印输入中的第一个字符串三次
然后再输出一行，打印输入中的第二个字符串三次*/
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
// 在此处补充你的代码
 MyString(const MyString& HatsuneMiku){
        if(HatsuneMiku.p){
            p=new char[strlen(HatsuneMiku.p)+1];
            strcpy(p,HatsuneMiku.p);
        }
        else
            p=NULL;
    }
    void Copy(const char* teto){
        if(p) delete[]p;
        if(teto){
            p=new char[strlen(teto)+1];
            strcpy(p,teto);
        }
        else
            p=NULL;
    }
    MyString& operator=(const char* Mika){
        if(p) delete[]p;
        if(Mika){
            p=new char[strlen(Mika)+1];
            strcpy(p,Mika);
        }
        else
            p=NULL;
        return *this;
    }
    MyString& operator=(const MyString& A){
        if(this==&A) return *this;
        if(p) delete[]p;
        if(A.p){
            p=new char[strlen(A.p)+1];
            strcpy(p,A.p);
        }
        else
            p=NULL;
        return *this;
    }
    friend ostream& operator<<(ostream& os,const MyString& s);
};
ostream&operator<<(ostream& os,const MyString& s){
    os<<s.p;
    return os;
//
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
		
	}
}