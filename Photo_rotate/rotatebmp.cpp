#include<fstream>
#include<vector>

using namespace std;

#pragma pack(push,1)
struct firsthead{
    uint16_t bfType; //固定为0X4D42,表示这是BMP文件
    uint32_t bfSize; //整个文件的大小（单位字节）
    uint16_t bfReserved1; //保留字段1，==0
    uint16_t bfReserved2; //保留字段2， ==0
    uint32_t bfOffBits; //像素数据偏移量，即从开头到像素数据的字节数
};
struct secondhead{
    uint32_t biSize;//固定为40，表示版本与自身大小
    int32_t biWidth;//宽度，像素
    int32_t biHeight;//高度，像素（正数代表第一行->底部，负数代表第一行->顶部）
    uint16_t biPlanes;//颜色平面数，固定为1，代表打包式储存
    uint16_t biBitCount;//每个像素的位数，决定图像颜色数量，真彩色为24，有1677万色
    uint32_t biCompression;//压缩类型，为0不压缩
    uint32_t biSizeImage;//像素数据的大小
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;//水平竖直分辨率
    uint32_t biClrUsed;//实际使用的颜色数，0代表全部颜色
    uint32_t biClrImportant;//重要的颜色数
};  
#pragma pack(pop)
int getRowSize(int width){
    return (width*3+3)/4*4;  //每个像素三字节，对4取模向上取整
}
int main(int argc,char* argv[]){ //argc一定等于3
    ifstream old(argv[1],ios::binary);
    ofstream newp(argv[2],ios::binary);
    firsthead first;
    secondhead second;
    //读取头
    old.read((char*)&first,sizeof(first));
    old.read((char*)&second,sizeof(second));
    //读取像素格式
    int width=second.biWidth;
    int height=second.biHeight;
    int oldRowSize=getRowSize(width);
    //读取像素数据,为了便于读入我们把二维矩阵展开成一行
    vector<unsigned char> oldPixel(oldRowSize*height);
    old.seekg(first.bfOffBits,ios::beg);//指针移动
    old.read((char*)oldPixel.data(),oldPixel.size());//.data返回起始位置指针
    //
    int newwidth=height;
    int newheight=width;
    int newRowSize=getRowSize(newwidth);
    vector<unsigned char>NewPixel(newRowSize*newheight,0);
    //旋转,注意实际上每个点内部BGR三原色的顺序不能变，所以用指针和[]运算符去赋值
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            unsigned char* oldidx=&oldPixel[x*3+y*oldRowSize];
            unsigned char* newidx=&NewPixel[(y)*3+(width-1-x)*newRowSize];
            newidx[0]=oldidx[0];
            newidx[1]=oldidx[1];
            newidx[2]=oldidx[2];
        }
    }
    //
    second.biWidth=newwidth;
    second.biHeight=newheight;
    second.biSizeImage=newRowSize*newheight;
    first.bfSize=first.bfOffBits+second.biSizeImage;
    //
    newp.write((char*)&first,sizeof(first));
    newp.write((char*)&second,sizeof(second));
    newp.write((char*)NewPixel.data(),NewPixel.size());
    //
    old.close();
    newp.close();
    return 0;
}