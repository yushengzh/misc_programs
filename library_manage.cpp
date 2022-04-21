/*6.简单文件数据库-模拟图书馆管理系统
涉及知识点：文件读写、内存管理、结构体定义、基本数据结构、高级格式化输入输出
要求：
编写一个程序模拟图书管理系统。用户分为管理员和读者两类，
分别显示不同文本格式菜单，通过菜单项对应数字进行选择。
读者菜单包括借书、还书、查询等功能。
管理员菜单包括图书和读者信息录入、修改和删除。
图书信息至少应包括：编号、书名、数量，
读者信息至少应包括：编号、姓名、所借图书。
可根据图书名称或编号进行图书信息查询，可查询某本书现在被哪些读者借走。
命令行参数如下：
Libsim  –a(-u)  xxxx
第一个参数为可执行程序名称；
第二个参数为用户身份，-a表示管理员，-u表示读者；
第三个参数为用户名
*/          

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{ //图书信息至少应包括：编号、书名、数量
    char id[10]; //编号
    char title[101];//书名
    int num;//数量
    char borrowMan[100][10];
    int cnt = 0;//借阅人数
}book;
book books[1000];

typedef struct{//读者信息至少应包括：编号、姓名、所借图书。
    char id[10];
    char name[101];
    char bookName[10] ="";//借书
}reader;
reader readers[1000];

int countBook = 0;//书的编号
int countReader = 0;

void readerView(char *);
void adminView();
void borrowBook(char *);
void returnBook(char *);
void addBook();
void modBook();
void delBook();
void autoAddReader(char *);
void addReader();
void modReader();
void delReader();
void search();
void showAllbook();

char iden[2];
char name[10];

int main(int argc,char *argv[]){
    strcpy(name,argv[2]);
    system("cls");
    printf("*************************欢迎使用图书管理系统*************************\n");
    strcpy(iden,argv[1]);
    if(strcmp(iden,"-a")==0){//-a表示管理员
        adminView();
    }else if(strcmp(iden,"-u")==0){//-u表示读者
        readerView(name);//autoAddReader(name);
    }
    printf("*****************************您已退出！******************************\n");
    return 0;
}

void readerView(char *readerName){//读者菜单包括借书、还书、查询等功能。
    int n;
    printf("\n");
    printf("---------读者菜单:-----------\n");
    printf("1、借书;\n2、还书;\n3、查询.\n");
    printf("4、退出.\n");
    printf("--------------------\n");
    printf("输入序号:");
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        borrowBook(readerName);readerView(readerName);
    case 2:
        returnBook(readerName);readerView(readerName);
    case 3:
        search();readerView(readerName);
    case 4:printf("退出成功!");exit(0);break;
    default:
        printf("\n");
        printf("---------输入异常，请重新输入:-----------\n");
        printf("--------------------\n");
        printf("\n");
        readerView(iden);;
        break;
    }
}
void adminView(){//管理员菜单包括图书和读者信息录入、修改和删除。
    int m;
    printf("\n");
    printf("----------管理员菜单:----------\n");
    printf("1、读者信息录入;\n");
    printf("2、读者信息修改;\n");
    printf("3、读者信息删除;\n");
    printf("4、图书信息录入;\n");
    printf("5、图书信息修改;\n");
    printf("6、图书信息删除.\n");
    printf("7、展示所有图书信息\n");
    printf("8、退出.\n");
    printf("--------------------\n");
    printf("输入序号:");
    scanf("%d",&m);
    switch (m)
    {
    case 1:addReader();
        adminView();
    case 2:modReader();
        adminView();
    case 3:delReader();
        adminView();
    case 4:addBook();
       adminView();
    case 5:modBook();
        adminView();
    case 6:delBook();
        adminView();
    case 7:showAllbook();
        adminView();
    case 8:printf("退出成功!");exit(0);
    default:
    printf("\n");
    printf("-----------输入异常，请重新输入:-----------\n");
    printf("--------------------\n");
    adminView();
        break;
    }
}

/*借书*/
void borrowBook(char name[20]){
    FILE *fp;
    char bid[10];
    fp = fopen("library.txt","r");
    int booknum=0;
    while(!feof(fp)){
        	fscanf(fp,"%s %s %d\n",
				books[booknum].id,books[booknum].title,&books[booknum].num);
        	booknum++;
    }
    fclose(fp);

    countBook = booknum;
    showAllbook();
    printf("你想要借哪本书?请输入编号:");
    scanf("%s",bid);
    for(int i=0;i<countBook;i++){
        if(strcmp(bid,books[i].id)==0){
            books[i].num--;
            strcpy(books[i].borrowMan[books[i].cnt],name);
            books[i].cnt++;
        }
    }
    fp=fopen("library.txt","w");
    for(int i=0;i<countBook;i++){
        fprintf(fp,"%s %s %d\n",books[i].id,books[i].title,books[i].num);
    }
    fclose(fp);
    printf("借书成功!");
}


/*还书*/
void returnBook(char name[20]){
    FILE *fp;
    char bid[10];
    fp = fopen("library.txt","r");
    int booknum=0;
    while(!feof(fp)){
        	fscanf(fp,"%s %s %d\n",
				books[booknum].id,books[booknum].title,&books[booknum].num);
        	booknum++;
    }
    fclose(fp);
    countBook = booknum;
    showAllbook();

    printf("你想要还哪本书？输入编号:");
    scanf("%s",bid);

    for(int i=0;i<countBook;i++){
        if(strcmp(bid,books[i].id)==0){
            books[i].num++;
            for(int j=0;j<books[i].cnt;j++){
                if(strcmp(books[i].borrowMan[j],name)==0){
                   memset(books[i].borrowMan[j],0,sizeof(books[i].borrowMan[j]));
                   books[i].cnt--;
                   fp=fopen("library.txt","w");
                    for(int k=0;k<countBook;k++){
                    fprintf(fp,"%s %s %d\n",books[k].id,books[k].title,books[k].num);
                    }
                    fclose(fp);
                   printf("还书成功!");return ;
                }
            }
            
        }
    }
}

/*增加 书*/
void addBook(){
    char id[10],title[10];
    int num;
    FILE *fp;
    int booknum=countBook;
    
    fp = fopen("library.txt","a");
        printf("\n请按以下格式输入图书信息:编号(ID) 书名(Title) 数量(Num)\n");
        printf("请输入图书编号:");
        scanf("%s",books[booknum].id);
        printf("请输入图书书名:");
        scanf("%s",books[booknum].title);
        printf("请输入存书数量:");
        scanf("%d",&books[booknum].num);
        fprintf(fp,"%s %s %d\n",
            books[booknum].id,books[booknum].title,books[booknum].num);
        fclose(fp);
        booknum++;
        countBook = booknum;
        printf("图书增加成功!\n");
        adminView();
}

/*修改 书*/
void modBook(){
    FILE *fp;
    char btitle[10];
    
    fp = fopen("library.txt","r");
    int booknum=0;
    while(!feof(fp)){
        	fscanf(fp,"%s %s %d\n",
				books[booknum].id,books[booknum].title,&books[booknum].num);
        	booknum++;
    }
    fclose(fp);
    countBook = booknum;
    printf("你想修改哪本书？请输入ID或书名:");
    scanf("%s",btitle);
    for(int i=0;i<countBook;i++){
        if(strcmp(btitle,books[i].title)==0||strcmp(btitle,books[i].id)==0){
            printf("-----------------该书详情-----------------\n");
            printf("图书编号: %s \n",books[i].id);
            printf("图书书名:《%s》\n",books[i].title);
            printf("存书数量: %d 本\n",books[i].num);
            printf("-----------------分割线-----------------\n");
            printf("你想把图书书名变动为:");
            scanf("%s",books[i].title);
            printf("你想把图书数量变动为:");
            scanf("%d",&books[i].num);
        }
    }
    fp=fopen("library.txt","w");
    for(int i=0;i<countBook;i++){
        fprintf(fp,"%s %s %d\n",books[i].id,books[i].title,books[i].num);
    }
    fclose(fp);
    printf("修改成功!\n");
    printf("\n");
    adminView();
}

/*删除 书*/
void delBook(){
    FILE *fp;
    char btitle[10];
    
    fp = fopen("library.txt","r");
    int booknum=0;
    while(!feof(fp)){
        	fscanf(fp,"%s %s %d\n",
				books[booknum].id,books[booknum].title,&books[booknum].num);
        	booknum++;
    }
    fclose(fp);

    printf("你想删除哪本书？请输入ID或书名:");
    scanf("%s",btitle);
    for(int i=0;i<booknum;i++){
        if(strcmp(btitle,books[i].title)==0||strcmp(btitle,books[i].id)==0){
            for(int j=i;j<booknum-1;j++){
                books[j] = books[j+1];
            }
            booknum--;
        }
    }
    countBook = booknum;
    fp = fopen("library.txt","w");
    for(int i=0;i<booknum;i++){
        fprintf(fp,"%s %s %d\n",books[i].id,books[i].title,books[i].num);
    }
    fclose(fp);
    printf("\n删除成功!");
}

void autoAddReader(char* name){
    FILE *fp;
    int readernum=0;

    fp = fopen("readerData.txt","r");
    while(!feof(fp)){
        	fscanf(fp,"%s %s %s\n",
				readers[readernum].id,readers[readernum].name,readers[readernum].bookName);
        	readernum++;
    }
    fclose(fp);
    countReader = readernum;
    strcpy(readers[readernum].name,name);
    fp = fopen("readerData.txt","a");
    char id[10];
    itoa(readernum+1,id,10);
    strcpy(readers[readernum].id,id);
    fprintf(fp,"%s %s %s\n",readers[readernum].id,readers[readernum].name,readers[readernum].bookName);
    fclose(fp);
    readernum++;
    countReader = readernum;
}

void addReader(){
    char id[10];
    FILE *fp;
    int readernum=0;
     fp = fopen("readerData.txt","r");
    
   while(!feof(fp)){
        	fscanf(fp,"%s %s %s\n",
				readers[readernum].id,readers[readernum].name,readers[readernum].bookName);
        	readernum++;
    }
    fclose(fp);

    fp = fopen("readerData.txt","a");
    printf("\n请按以下格式输入读者信息:编号(ID) 名字(Name) \n");
    printf("增加的读者编号为:");
    scanf("%s",readers[readernum].id);
    printf("增加的读者名字为:");
    scanf("%s",readers[readernum].name);
    fprintf(fp,"%s %s %s\n",
    readers[readernum].id,readers[readernum].name,readers[readernum].bookName);
    fclose(fp);
    readernum++;
    countReader = readernum;
    printf("读者增加成功!");
}

void modReader(){
    FILE *fp;
    char rtitle[10];
    
    fp = fopen("readerData.txt","r");
    int readernum=0;
    while(!feof(fp)){
        	fscanf(fp,"%s %s %s\n",
				readers[readernum].id,readers[readernum].name,readers[readernum].bookName);
        	readernum++;
    }
    fclose(fp);
    countReader = readernum;
    printf("你想修改哪个读者？请输入ID或名字:");
    scanf("%s",rtitle);
    countReader = readernum;
    for(int i=0;i<countReader;i++){
        if(strcmp(rtitle,readers[i].name)==0||strcmp(rtitle,readers[i].id)==0){
            printf("----------------该读者详情----------------\n");
            printf("读者编号: %s ",readers[i].id);
            printf("读者名字: %s ",readers[i].name);
            printf("所借的书: %s \n",readers[i].bookName);
            printf("-----------------分割线-----------------\n");
            printf("你想把名字变动为:");
            scanf("%s",readers[i].name);
            printf("你想把所借书名变动为:");
            scanf("%s",readers[i].bookName);
        }
    }
    fp=fopen("readerData.txt","w");
    for(int i=0;i<countReader;i++){
        fprintf(fp,"%s %s %s\n",readers[i].id,readers[i].name,readers[i].bookName);
    }
    fclose(fp);

    printf("修改成功!");
}
    
void delReader(){
    FILE *fp;
    char rtitle[10];
    
    fp = fopen("readerData.txt","r");
    int readernum=0;
    while(!feof(fp)){
        	fscanf(fp,"%s %s %s\n",
				readers[readernum].id,readers[readernum].name,readers[readernum].bookName);
        	readernum++;
    }
    fclose(fp);
    
    printf("你想删除哪个读者？请输入ID或名字:");
    scanf("%s",rtitle);
    for(int i=0;i<readernum;i++){
        if(strcmp(rtitle,readers[i].name)==0||strcmp(rtitle,readers[i].id)==0){
            for(int j=i;j<readernum-1;j++){
                readers[i] = readers[i+1];
            }
            readernum--;
        }
    }
    countReader = readernum;
    fp=fopen("readerData.txt","w");
    for(int i=0;i<readernum;i++){
        fprintf(fp,"%s %s %s\n",readers[i].id,readers[i].name,readers[i].bookName);
    }
    fclose(fp);

    printf("\n删除成功!");
}

void search(){
    char btitle[10];
    char bid[10];
    FILE *fp;
    fp = fopen("library.txt","r");
    int booknum=0;
    while(!feof(fp)){
        	fscanf(fp,"%s %s %d\n",
				books[booknum].id,books[booknum].title,&books[booknum].num);
        	booknum++;
    }
    fclose(fp);
    countBook = booknum;
    printf("你想查询哪本书？请输入ID或书名:");
    scanf("%s",btitle);
    for(int i=0;i<countBook;i++){
        if(strcmp(btitle,books[i].title)==0||strcmp(btitle,books[i].id)==0){
            printf("-----------------查询详情-----------------\n");
            printf("图书编号: %s \n",books[i].id);
            printf("图书书名:《%s》\n",books[i].title);
            printf("存书数量: %d 本\n",books[i].num);//12
            printf("借书人有:");
            for(int j=0;j<books[i].cnt;j++){
                if(strlen(books[i].borrowMan[j])!=0){
                    printf("%s ",books[i].borrowMan[j]);
                }
            }
            printf("\n");
            printf("-----------------查询结束-----------------\n");
            break;
        }
    }
    fp=fopen("library.txt","w");
    for(int i=0;i<countBook;i++){
        fprintf(fp,"%s %s %d\n",books[i].id,books[i].title,books[i].num);
    }
    fclose(fp);
}

void showAllbook(){
    book bookInfo[100];
    FILE *fp;
    fp = fopen("library.txt","r");
    int booknum=0;
    while(!feof(fp)){
        	fscanf(fp,"%s %s %d\n",
				books[booknum].id,books[booknum].title,&books[booknum].num);
        	booknum++;
    }
    fclose(fp);

    printf("-----------------所有书-----------------\n");
    for(int i=0;i<booknum;i++){
        printf("编号%s-书名《%s》-数量%d\n",books[i].id,books[i].title,books[i].num);//11
    }
     printf("-----------------分割线-----------------\n");
}