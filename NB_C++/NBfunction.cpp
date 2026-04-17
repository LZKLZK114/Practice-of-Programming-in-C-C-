/*lisp语言中有高阶函数的概念，即函数可以作为函数的参数，也可以作为函数的返回值。例如:

(define (f n)   (lambda (x) (+ x n)))

定义了一个函数f，该函数的返回值是另一个函数，假定称为g即 (lambda (x) (+ x n) 此函数功能是参数为x，返回值为x + n。 于是 ((f 7) 9)   如下执行

(f 7)以参数7调用f, f的返回值是g,n的值为7

((f 7) 9)等价于 (g 9)，即以参数9调用g。 因 n = 7, x = 9 ,因此(g 9)返回值为16

编写一个C++的通用函数模板f,使之能完成类似于lisp函数f的功能。 对于下面的程序，输出结果是

16
world hello!
world!*/
#include <iostream>
using namespace std;
template<class T,class U>
auto f(T a){
    return [a](U b)->U{return b+a;};
}
int main()
{
   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   
   return 0;    //world!
}