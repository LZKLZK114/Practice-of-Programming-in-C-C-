/*输入
无
输出
1. abcd-efgh-abcd-
2. abcd-
3.
4. abcd-efgh-
5. efgh-
6. c
7. abcd-
8. ijAl-
9. ijAl-mnop
10. qrst-abcd-
11. abcd-qrst-abcd- uvw xyz
about
big
me
take
abcd
qrst-abcd-*/
#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) //字符串长度
{	int i = 0;
	for(; s[i]; ++i);       //这里不会统计\0
	return i;
}
void strcpy(char * d,const char * s)//复制
{
	int i = 0;
	for( i = 0; s[i]; ++i)      //这里不会附加\0
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2)//比较
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {  //  不比较\0
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)//末尾拼接
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
// 在此处补充你的代码
private:
    char* s;
    int len;
public:
//带参构造
   MyString(const char* a){
    len = strlen(a);
    s= new char [len+1];
    strcpy(s,a);
   }
   //默认构造
   MyString(){
    len=0;
    s=new char {'\0'};
    }
   //拷贝构造
   MyString(const MyString& a){
    len=a.len;
    s=new char [len+1];
    strcpy(s,a.s);
   }
   //等于号重载，深度拷贝
   MyString& operator=(const MyString& a){
    if(this==&a){return *this;}
    len=a.len;
    s=new char [len+1];
    strcpy(s,a.s);
    return *this;
    }
    //析构函数
    ~MyString(){
        delete[]s;
    }
    //比较运算符重载
    friend bool operator<(MyString a,MyString b){
        if(strcmp(a.s,b.s)==-1){return true;}
        else return false;    
    }
    friend bool operator==(MyString a,MyString b){
        if(strcmp(a.s,b.s)==0){return true;}
        else return false;
    }
    friend bool operator>(MyString a,MyString b){
        if(strcmp(a.s,b.s)==1){return true;}
        else return false;
    }
    //流运算符重载
    friend ostream& operator<<(ostream&os,MyString a){
        os<<a.s;
        return os;
    }
    //加法重载，注意拼接需要重新分配内存
    MyString operator+(MyString a){
       char* temp=new char [a.len+len]{'\0'};
       strcpy(temp,s);
       strcat(temp,a.s);
       MyString T(temp);
       return T;
    }
    //[]重载
    char& operator[](int n){
        return (this->s)[n];
    }
   //+=重载,务必&
   MyString& operator+=(const char* a){
    MyString temp(a);
    *this=*this+temp;
    return *this;
   }
   //加法左操作数的重载
   friend MyString operator+(const char* s,MyString a){
    MyString temp(s);
    return temp+a;
   }
   //()重载
   char* operator()(int a,int b){
    char* q=new char [b+1]{'\0'};
    for(int i=a;i<a+b;i++){
        q[i-a]=s[i];
    }
    return q;
   }
//
};


int CompareString( const void * e1, const void * e2)//强制类型转化的比大小
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
    return 0;//后加的，防止编译器变黄警告
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}