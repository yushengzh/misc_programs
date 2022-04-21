/*4.位图图像文件缩放
**涉及知识点：文件读写、结构体定义、内存管理、基本图像处理算法、命令行参数
*要求：
*编写一个程序，可以在命令行输入参数，完成指定文件的缩放，并存储到新文件，命令行参数如下
*zoom file1.bmp 200 file2.bmp
*第一个参数为可执行程序名称，第二个参数为原始图像文件名，第三个参数为缩放比例（百分比），第四个参数为新文件名
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

/*原图像的宽  原图像的高  每像素位数  新图像的宽  新图像的高  
 *原图像数据每行的字节数  新图像数据每行的字节数
 */
long IWidth,IHeight,biBitCount,INewWidth,INewHeight,ILineByte,INewLineByte;

int zoomnumInit;    
float zoomnum;

unsigned char *pIBuf; //原图像像素指针  
unsigned char *pINewBuf;//新图像像素指针

int ReadBmp(const char*);//查看原图像
int SaveBmp(const char*,unsigned char*,int,int,int);//保存放缩后图像
int Zoom(const char*,const char*);//放缩函数

int main(int argc,char** argv){
 zoomnumInit=atoi(argv[2]);//放缩比例 
 zoomnum=zoomnumInit*1.0/100.0;//整数-->浮点数
 Zoom(argv[1],argv[3]); //原图像-->放缩后的图像
 return 0; 	
}

int ReadBmp(const char* bmpName){
	FILE *fp=fopen(bmpName,"rb");//只读打开一个二进制文件,只允许读数据
	if(fp==0){ printf("打开文件失败\n");return 0;}
	fseek(fp,sizeof(BITMAPFILEHEADER),0);
	BITMAPINFOHEADER head;//位图信息头
	fread(&head,sizeof(BITMAPINFOHEADER),1,fp);
	IWidth = head.biWidth;//宽
	IHeight = head.biHeight;//高
	biBitCount = head.biBitCount;//一像素所占位数
	ILineByte = (IWidth *biBitCount/8+3)/4*4;//一个扫描行所占字节数
    pIBuf = (unsigned char*)malloc(sizeof(unsigned char)*ILineByte *IHeight);//定义一个矩阵用以存放原图像像素信息。pIBuf指向首地址
/*获取源文件像素信息。
 *接收地址pIBuf，单个元素大小1字节，元素个数每行字节数*行数，输入流fp
 */
	fread(pIBuf,1,ILineByte *IHeight,fp);
	return 1;
}

int SaveBmp(const char* bmpName,unsigned char *imgBuf,int width,int height,int biBitCount){
	if(!imgBuf)return 0;//假设没有像素数据传入，则函数返回
	INewLineByte = (width * biBitCount/8+3)/4*4;//计算新图像每行字节数。/4*4以保证是4的倍数
	FILE *fp = fopen(bmpName,"wb");//只写方式打开或新建一个二进制文件，只允许写数据
	if(fp == 0) return 0;
	BITMAPFILEHEADER fileHead;//位图文件头	(申请位图文件头结构变量，填写文件头信息)
	fileHead.bfType= 0x4d42;//bmp类型  0x42:=B  0x4d:=M
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ INewLineByte *height;
	fileHead.bfReserved1 = 0;//保留字
	fileHead.bfReserved2 = 0;//保留字
	fileHead.bfOffBits = 54;// 从文件头到像素数据的偏移
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	BITMAPINFOHEADER head;//位图信息头
	head.biBitCount = biBitCount;// 一像素所占的位数
	head.biClrImportant = 0;//此值为0时所有颜色都重要
	head.biClrUsed = 0;//BMP图像使用的颜色，0表示使用全部颜色
	head.biCompression = 0;//压缩方式，0表示不压缩
	head.biHeight = height;
	head.biPlanes =1;//目标绘图设备包含的层数，必须设置为1
	head.biSize = 40;//BITMAPINFOHEADER 大小 
	head.biSizeImage = ILineByte *height;//实际的位图数据占用的字节数 = 一个扫描行所占字节数 * 高度
	head.biWidth = width;
	head.biXPelsPerMeter = 0;//指定目标设备的水平分辨率
	head.biYPelsPerMeter = 0;//指定目标设备的垂直分辨率
	fwrite(&head,sizeof(BITMAPINFOHEADER),1,fp);//写入信息头
	fwrite(imgBuf,height * INewLineByte,1,fp);//写入像素数据
	fclose(fp);//关闭文件
	return 1;
}

int Zoom(const char* readPath,const char* address){
	ReadBmp(readPath);
	INewWidth = (int) (IWidth * zoomnum +0.5);//图宽缩放
	INewHeight = (int) (IHeight * zoomnum +0.5);//图高缩放
	ILineByte =(IWidth*biBitCount/8+3)/4*4;//一个扫描行所占字节数（原图）
	INewLineByte = (INewWidth * biBitCount/8+3)/4*4;//一个扫描行所占字节数（压缩后）
    pINewBuf = (unsigned char*)malloc(sizeof(unsigned char)*INewLineByte * INewHeight);

	long i;  //循环变量（像素在新图像中的坐标）     
	long j;
	long k;	//色彩选择，k=0时为蓝色，k=1时为绿色，k=2时为红色     
	long i0;	//像素在原图像中的坐标	  
	long j0;
	
	for(i = 0;i < INewHeight;i++){
			for(j = 0; j < INewWidth;j++)
				for(k=0;k<3;k++){ //k=0,1,2
					i0 = (int)(i/zoomnum+0.5); 
					j0 = (int)(j/zoomnum+0.5);
					int i1 = (int)i0;
					int i2 = i1 + 1;
					int j1 = (int)j0;
					int j2 = j1+1;
					double fx1 = i0 - i1;
					double fx2 = 1.0 - fx1;
					double fy1 = j0 - j1;
					double fy2 = 1.0 - fy1;
					double s1 = fx1 * fy1;
					double s2 = (1.0 - fx1) * fy1;
					double s3 = (1.0 - fx1)*(1.0 - fy1);
					double s4 = fx1*(1.0 - fy1);
/*
 *双线性内插值法
 */
					if((j0 >= 0) && (j0 < IWidth-1) && (i0 >=0)&& (i0 <IHeight-1)){
						*(pINewBuf+i*INewLineByte+j*3+k) = *(pIBuf+i2*ILineByte+j2*3+k)*s1
														   +*(pIBuf+i1*ILineByte+j2*3+k)*s2
														   +*(pIBuf+i1*ILineByte+j1*3+k)*s3
														   +*(pIBuf+i2*ILineByte+j1*3+k)*s4;
					}
					else{
						*(pINewBuf+i*INewLineByte+j*3+k)=255;
					}
				}
	}

	SaveBmp(address,pINewBuf,INewWidth,INewHeight,biBitCount);
	free(pINewBuf);
	return 1;
}
