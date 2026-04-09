/*描述
写一个程序完成以下命令：
new id ——新建一个指定编号为id的序列(id < 10000)
add id num——向编号为id的序列加入整数
num merge id1 id2——如果id1等于id2,不做任何事，否则归并序列id1和id2中的数，并将id2清空
unique id——去掉序列id中重复的元素
out id ——从小到大输出编号为id的序列中的元素，以空格隔开

输入
第一行一个数n，表示有多少个命令( n＜＝２０００００)。以后n行每行一个命令。
输出
按题目要求输出。*/
#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

int main(){
    int n;string s;
    unordered_map<int,list<int>> H;
    cin>>n;
    while(n--){
        cin>>s;
        if(s=="new"){
            int id;cin>>id;
            H[id]=list<int>();
        }
        else if(s=="add"){
            int id,num;
            cin>>id>>num;
            H[id].push_back(num);
        }
        else if(s=="merge"){
            int id1,id2;
            cin>>id1>>id2;
            if(id1!=id2){
                H[id1].splice(H[id1].end(),H[id2]);
            }
        }
        else if(s=="unique"){
            int id;cin>>id;
            H[id].sort();
            H[id].unique();
        }
        else {
            int id;cin>>id;
            H[id].sort();
            for(auto i=H[id].begin();i!=H[id].end();i++){
                cout<<*i<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}