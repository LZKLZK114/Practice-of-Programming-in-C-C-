/*描述
我们定义一个正整数a比正整数b优先的含义是：
*a的质因数数目（不包括自身）比b的质因数数目多；
*当两者质因数数目相等时，数值较大者优先级高。


现在给定一个容器，初始元素数目为0，之后每次往里面添加10个元素，每次添加之后，要求输出优先级最高与最低的元素，并把该两元素从容器中删除。

输入
第一行: num (添加元素次数，num <= 30)

下面10*num行，每行一个正整数n（n < 10000000).

输出
每次输入10个整数后，输出容器中优先级最高与最低的元素，两者用空格间隔。*/
#include<iostream>
#include<set>
#include<vector>
using namespace std;
int pre[10000001]={};
void precompute() {
    for (int i = 2; i <= 1e7; ++i) {
        if (pre[i] == 0) { // i 是质数
            for (int j = i+i; j <= 1e7; j += i) {
                pre[j]++; // 给 i 的所有倍数的质因数数目 +1
            }
        }
    }
}

int zys(int a){
    vector<int>A(a+1,0);
    vector<int> zs;
    for(int i=2;i<a;i++){
        if(A[i]==0){
            zs.push_back(i);
            for(int j=i;j<=a;j+=i){
                A[j]=1;
            }
        }
    }int cnt{};
    for(int z:zs){
        if(a%z==0){cnt++;}
    }
    return cnt;
}
struct Myint{
    int v;
    Myint(){};
    Myint(int a){v=a;}
    bool operator <(const Myint& a)const{//true则a优先
        int va=pre[a.v];int vv=pre[this->v];
        if(va>vv){return true;}
        else if(va==vv){
            return a.v>this->v;
        }
        else{return false;}
    }
};

int main(){
    precompute();
    int n;cin>>n;
    set<Myint> q;
    for(int i=0;i<n;i++){
        for(int j=0;j<10;j++){
            int a;cin>>a;Myint t(a);
            q.insert(t);
        }
        cout<<(--q.end())->v<<" "<<(q.begin())->v<<endl;
        q.erase(q.begin());
        q.erase((--q.end()));
    }

    return 0;
}