/*5.	RLE压缩解压算法
涉及知识点：文件读写、位操作、内存管理、结构体定义、RLE算法、命令行参数
要求：编写一个程序，可以在命令行输入参数，完成指定文件的压缩解压
命令行参数如下：`rle  file1  –c(-d)  file2`
第一个参数为可执行程序名称，第二个参数为原始文件名，第三个参数为压缩或解压缩选项，第四个参数为新文件名
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
FILE *infile,*outfile;		 	/*定义全局变量*/
void compress(char *infilename,char *outfilename);/*压缩函数*/
void deCompress(char *infilename,char *outfilename);/*解压函数*/

int main(int argc,char **argv){
    char clone[2];strcpy(clone,argv[2]);
     if(strcmp(clone,"-c")==0){
        compress(argv[1],argv[3]);/*调用函数compress()压缩数据*/
	    fclose(infile);			/*关闭文件*/
	    fclose(outfile);
    }else if(strcmp(clone,"-d")==0){
        deCompress(argv[1],argv[3]);                   // 调用函数deCompress()解压数据
	    fclose(infile);		                           // 关闭文件
	    fclose(outfile);
    }
    return 0;
}

void compress(char *infilename,char *outfilename)/*压缩文件*/
{
	infile=fopen(infilename,"rb");
    register int len;
	char first,seq;
	first=fgetc(infile);   // 取得文件第一个字符
	seq=first;         // 将第一个字符赋值给seq
	len=1;                // 字符连续出现次数，长度初始化为1
	while(!feof(infile))			/*进行压缩*/
	{
		first=fgetc(infile);   // 取得文件的下一个字符
		if(first==seq)     // 文件上一个字符是否与当前字符相等
		{
			len++;            // 相等则连续长度加一
		}
		else
		{
			fputc(len,outfile);
			fputc(seq,outfile); // 不相等，则输出连续的长度和对应字符
			seq=first;       // 将不相等的第一个字符赋值给seq，开始下次长度计算
			len=1;              // 长度归一
		}
	}
	
}

void deCompress(char *infilename,char *outfilename)
{
	register int len;
	char first;
    infile=fopen(infilename,"rb");
    outfile=fopen(outfilename,"wb");
	while(!feof(infile))		                  // 解压文件
	{
		len=fgetc(infile);                    // 读取的时候前面的字符是出现的次数
		first=fgetc(infile);                   // 后面的是对应的字符
		for(int i=0;i<len;i++)
		{
			fputc(first,outfile);      // 按照压缩的规则依次“解压”：即是先读取该字符出现的次数，然后循环输出即可
		}
	}
}

