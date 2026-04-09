//模仿一个栈去实现函数的递归
/*给定n个字符串（从1开始编号），每个字符串中的字符位置从0开始编号，长度为1-500，现有如下若干操作：

copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
add S1 S2：判断S1，S2是否为0-99999之间的整数，若是则将其转化为整数做加法，若不是，则作字符串加法，返回的值为一字符串。
find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
rfind S N：在第N个字符串中从右开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
reset S N：将第N个字符串变为S。
print N：打印输出第N个字符串。
printall：打印输出所有字符串。
over：结束操作。
其中N，X，L可由find与rfind操作表达式构成，S，S1，S2可由copy与add操作表达式构成。

输入
第一行为一个整数n（n在1-20之间）


接下来n行为n个字符串，字符串不包含空格及操作命令等。


接下来若干行为一系列操作，直到over结束。

输出
根据操作提示输出对应字符串。*/
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<stack>
using namespace std;
//约定第一个参数都传引用vector
string Mycopy(vector<string>& s,int n,int x,int l){
    return s[n].substr(x,l);
}
inline bool is_int(string& s){
    if(s.size()>5){return false;}
    else{
        int a=0;
        for(int i=0;i<s.size();i++){
            if(s[i]>'9'||s[i]<'0'){return false;}
        }
        return true;
    }
}
string Myadd(string&s1,string&s2){
    if(is_int(s1)&&is_int(s2)){
        int a=stoi(s1);int b=stoi(s2);
        return to_string(a+b);
    }
    else{return s1+s2;}
}
int Myfind(vector<string>& s,string&a,int n){
    auto t=s[n].find(a);
    if(t==string::npos){return s[n].size();}
    else{return t;}
}
int Myrfind(vector<string>&s,string&a,int n){
    auto t=s[n].rfind(a);
    if(t==string::npos){return s[n].size();}
    else{return t;}
}
void Myinsert(vector<string>&s,string&a,int n,int x){
    s[n].insert(x,a);
}
void Myreset(vector<string>&s,string&a,int n){
    s[n]=a;
}
void Myprint(vector<string>&s,int n){
    cout<<s[n]<<endl;
}
void Myprintall(vector<string>&s){
    for(int i=1;i<s.size();i++){
        cout<<s[i]<<endl;
    }
}
bool work_start(vector<string>&s){
    string o;
    getline(cin,o);
    if(o=="over"){return false;}
    stringstream ss(o);
    stack<string> order,repos;
    string temp;
    while(ss>>temp){order.push(temp);}
    while(!order.empty()){
        if(order.top()=="copy"){
            order.pop();
            string a,b,c;
            a=repos.top();repos.pop();
            b=repos.top();repos.pop();
            c=repos.top();repos.pop();
            repos.push(Mycopy(s,stoi(a),stoi(b),stoi(c)));
        }
        else if(order.top()=="add"){
            order.pop();
            string a,b;
            a=repos.top();repos.pop();
            b=repos.top();repos.pop();
            repos.push(Myadd(a,b));
        }
        else if(order.top()=="find"){
            order.pop();
            string a,b;
            a=repos.top();repos.pop();
            b=repos.top();repos.pop();
            repos.push(to_string(Myfind(s,a,stoi(b))));
        }
        else if(order.top()=="rfind"){
            order.pop();
            string a,b;
            a=repos.top();repos.pop();
            b=repos.top();repos.pop();
            repos.push(to_string(Myrfind(s,a,stoi(b))));
        }
        else if(order.top()=="insert"){
            order.pop();
            string a,b,c;
            a=repos.top();repos.pop();
            b=repos.top();repos.pop();
            c=repos.top();repos.pop();
            Myinsert(s,a,stoi(b),stoi(c));
        }
        else if(order.top()=="reset"){
            order.pop();
            string a,b;
            a=repos.top();repos.pop();
            b=repos.top();repos.pop();
            Myreset(s,a,stoi(b));
        }
        else if(order.top()=="print"){
            order.pop();
            string a;
            a=repos.top();repos.pop();
            Myprint(s,stoi(a));
        }
        else if(order.top()=="printall"){
            order.pop();
            Myprintall(s);
        }
        else{
            repos.push(order.top());
            order.pop();
        }
    }
    return true;
}
int main(){
    int n;cin>>n;
    vector<string> s(n+1);
    for(int i=1;i<=n;i++){cin>>s[i];}
    cin.ignore();
    while(work_start(s)){};
    return 0;
}