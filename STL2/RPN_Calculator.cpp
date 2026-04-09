/*描述
Reverse Polish notation (or just RPN) by analogy with the related Polish notation, a prefix notation introduced in 1920 by the Polish mathematician Jan Łukasiewicz, is a mathematical notation wherein every operator follows all of its operands. It is also known as Postfix notation.

In Reverse Polish notation the operators follow their operands; for instance, to add three and four one would write "3 4 +" rather than "3 + 4". If there are multiple operations, the operator is given immediately after its second operand; so the expression written "3 − 4 + 5" in conventional infix notation would be written "3 4 − 5 +" in RPN: first subtract 4 from 3, then add 5 to that. An advantage of RPN is that it obviates the need for parentheses that are required by infix. While "3 − 4 * 5" can also be written "3 − (4 * 5)", that means something quite different from "(3 − 4) * 5", and only the parentheses disambiguate the two meanings. In postfix, the former would be written "3 4 5 * −", which unambiguously means "3 (4 5 *) −".

You were asked to design a simple RPN calculator, which will support the “+”, “-“, “*”, “/”(the absolute value of the divisor will not less then 10^-9) and “^”(power operator, if the base number b<=0, the exponential e must be a positive integer not greater than 10^9) operators. You can assume all the numbers during the calculation can fit into a double-precision floating point number.

In addition, our calculator has some memory. Each time we calculate an expression, the smallest number in the memory will be erased, and replace it with the value of the expression.

输入
The first line contains an integer n, which is the memory size of our calculator.


From the second line, we will give n numbers, which is the initial value of the memory. each line except last will have 10 numbers.


And then each line has a valid RPN expression we previously described, end with “=”, which is the command for calculation. Each term will no longer than 20 characters.

输出
For each expression, output the value of it in a line.
And then output an empty line to separate the two parts.
At last, output the all the numbers in memory, in increasing order, 10 numbers per line.

Each number should be formatted in scientific notation with 6 digits after decimal point and 2 digits of exponential, such like “%e” format string of printf() function in C. The numbers in a line should be separated by a space.*/
#include<iostream>
#include<vector>
#include<cmath>
#include<stack>
#include<sstream>
#include<string>
#include<algorithm>
using namespace std;
int main (){
    int k;cin>>k;
    vector<double> cache(k,0);
    for(int i=0;i<k;i++){cin>>cache[i];}
    stack<double> num;
    cin.ignore();
    string s;
    while(getline(cin,s)){
        if(s.empty()){continue;}
        stringstream ss(s);
        string temp;
        while(ss>>temp){
            if(temp=="="){
                printf("%e",num.top());
               // printf(" ");
                cout<<'\n';
                auto m=min_element(cache.begin(),cache.end());
                *m=num.top();
                num.pop();
            }
            else if(temp=="+"){
                double a=num.top();num.pop();
                double b=num.top();num.pop();
                num.push(b+a);
            }else if(temp=="-"){
                double a=num.top();num.pop();
                double b=num.top();num.pop();
                num.push(b-a);
            }else if(temp=="*"){
                double a=num.top();num.pop();
                double b=num.top();num.pop();
                num.push(b*a);
            }else if(temp=="/"){
                double a=num.top();num.pop();
                double b=num.top();num.pop();
                num.push(b/a);
            }else if(temp=="^"){
                double a=num.top();num.pop();
                double b=num.top();num.pop();
                num.push(pow(b,a));
            }
            else{
                num.push(stod(temp));
            }
        }
    }
    cout<<'\n';
    sort(cache.begin(),cache.end());
    int idx=0;
    for(int i=0;i<k;i++){
        if(i%10==0&&i!=0){cout<<'\n';}
        if(i%10==9){printf("%e",cache[i]);}
        else {printf("%e",cache[i]);printf(" ");}
    }
    return 0;
}