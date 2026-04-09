/*描述
为了迎接08年的奥运会，让大家更加了解各种格斗运动，facer新开了一家热血格斗场。格斗场实行会员制，但是新来的会员不需要交入会费，而只要同一名老会员打一场表演赛，证明自己的实力。

我们假设格斗的实力可以用一个正整数表示，成为实力值。另外，每个人都有一个唯一的id，也是一个正整数。为了使得比赛更好看，每一个新队员都会选择与他实力最为接近的人比赛，即比赛双方的实力值之差的绝对值越小越好，如果有两个人的实力值与他差别相同，则他会选择比他弱的那个（显然，虐人必被虐好）。

不幸的是，Facer一不小心把比赛记录弄丢了，但是他还保留着会员的注册记录。现在请你帮facer恢复比赛纪录，按照时间顺序依次输出每场比赛双方的id。

输入
第一行一个数n(0 < n <=100000)，表示格斗场新来的会员数（不包括facer）。以后n行每一行两个数，按照入会的时间给出会员的id和实力值。一开始，facer就算是会员，id为1，实力值1000000000。输入保证两人的实力值不同。

输出
N行，每行两个数，为每场比赛双方的id，新手的id写在前面。*/
//依旧神秘排序规则
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
struct person{
    int id;
    long long power;
    person(int a,long long b){id=a;power=b;}
    person(){id=0;power=0;}
    bool operator <(const person&a)const{
        return this->power<a.power;
    }
    long long operator -(const person&a){
        return (this->power)-a.power;
    }
};
int main(){
    int n;cin>>n;
    set<person> members;
    members.insert(person(1,1000000000));
    for(int i=0;i<n;i++){
        int opid;
        int a;long long b;
        cin>>a>>b;
        person t(a,b);
        auto it = members.lower_bound(t);
        if(it==members.begin()){
            opid=it->id;
        }
        else if(it==members.end()){
            --it;
            opid=it->id;
        }
        else{
            auto rit=it--;
            long long left=it->power;
            long long right=rit->power;
            if(right-b>=b-left){opid=it->id;}
            else{opid=rit->id;}
        }
        cout<<a<<" "<<opid<<endl;
        members.insert(t);
    }
    return 0;
}