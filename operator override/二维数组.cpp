/*写一个二维数组类 Array2,使得下面程序的输出结果是：

0,1,2,3,

4,5,6,7,

8,9,10,11,

next

0,1,2,3,

4,5,6,7,

8,9,10,11,*/
#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
// 在此处补充你的代码
private:
    int row,col;
    int **dp;
public:
    Array2(){
        row=0;
        col=0;
        dp=nullptr;
    }
    Array2(int x,int y){
        row=x;
        col=y;
        dp=new int*[row];
        for(int i=0;i<row;i++){
            dp[i]=new int[col];
        }
    }
    int* operator [] (int x){
        return dp[x];
    }
    int operator () (int x,int y){
        return dp[x][y];
    }
    Array2& operator = (const Array2&a){
        if(this==&a){return *this;}
        if(!dp){
            for(int i=0;i<row;i++){
                delete [] dp[i];
            }
            delete [] dp;
            dp=nullptr;
        }
        row=a.row;
        col=a.col;
          dp=new int*[row];
        for(int i=0;i<row;i++){
            dp[i]=new int[col];
        }
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                dp[i][j]=a.dp[i][j];
            }
        }
        return *this;
    }
    ~Array2(){
        if(dp){
            for(int i=0;i<row;i++){
                delete [] dp[i];
            }
            delete [] dp;
            dp=nullptr;
        }
    }
//
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}