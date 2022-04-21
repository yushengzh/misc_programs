/*6.���ļ����ݿ�-ģ��ͼ��ݹ���ϵͳ
�漰֪ʶ�㣺�ļ���д���ڴ�����ṹ�嶨�塢�������ݽṹ���߼���ʽ���������
Ҫ��
��дһ������ģ��ͼ�����ϵͳ���û���Ϊ����Ա�Ͷ������࣬
�ֱ���ʾ��ͬ�ı���ʽ�˵���ͨ���˵����Ӧ���ֽ���ѡ��
���߲˵��������顢���顢��ѯ�ȹ��ܡ�
����Ա�˵�����ͼ��Ͷ�����Ϣ¼�롢�޸ĺ�ɾ����
ͼ����Ϣ����Ӧ��������š�������������
������Ϣ����Ӧ��������š�����������ͼ�顣
�ɸ���ͼ�����ƻ��Ž���ͼ����Ϣ��ѯ���ɲ�ѯĳ�������ڱ���Щ���߽��ߡ�
�����в������£�
Libsim  �Ca(-u)  xxxx
��һ������Ϊ��ִ�г������ƣ�
�ڶ�������Ϊ�û���ݣ�-a��ʾ����Ա��-u��ʾ���ߣ�
����������Ϊ�û���
*/          

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{ //ͼ����Ϣ����Ӧ��������š�����������
    char id[10]; //���
    char title[101];//����
    int num;//����
    char borrowMan[100][10];
    int cnt = 0;//��������
}book;
book books[1000];

typedef struct{//������Ϣ����Ӧ��������š�����������ͼ�顣
    char id[10];
    char name[101];
    char bookName[10] ="";//����
}reader;
reader readers[1000];

int countBook = 0;//��ı��
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
    printf("*************************��ӭʹ��ͼ�����ϵͳ*************************\n");
    strcpy(iden,argv[1]);
    if(strcmp(iden,"-a")==0){//-a��ʾ����Ա
        adminView();
    }else if(strcmp(iden,"-u")==0){//-u��ʾ����
        readerView(name);//autoAddReader(name);
    }
    printf("*****************************�����˳���******************************\n");
    return 0;
}

void readerView(char *readerName){//���߲˵��������顢���顢��ѯ�ȹ��ܡ�
    int n;
    printf("\n");
    printf("---------���߲˵�:-----------\n");
    printf("1������;\n2������;\n3����ѯ.\n");
    printf("4���˳�.\n");
    printf("--------------------\n");
    printf("�������:");
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        borrowBook(readerName);readerView(readerName);
    case 2:
        returnBook(readerName);readerView(readerName);
    case 3:
        search();readerView(readerName);
    case 4:printf("�˳��ɹ�!");exit(0);break;
    default:
        printf("\n");
        printf("---------�����쳣������������:-----------\n");
        printf("--------------------\n");
        printf("\n");
        readerView(iden);;
        break;
    }
}
void adminView(){//����Ա�˵�����ͼ��Ͷ�����Ϣ¼�롢�޸ĺ�ɾ����
    int m;
    printf("\n");
    printf("----------����Ա�˵�:----------\n");
    printf("1��������Ϣ¼��;\n");
    printf("2��������Ϣ�޸�;\n");
    printf("3��������Ϣɾ��;\n");
    printf("4��ͼ����Ϣ¼��;\n");
    printf("5��ͼ����Ϣ�޸�;\n");
    printf("6��ͼ����Ϣɾ��.\n");
    printf("7��չʾ����ͼ����Ϣ\n");
    printf("8���˳�.\n");
    printf("--------------------\n");
    printf("�������:");
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
    case 8:printf("�˳��ɹ�!");exit(0);
    default:
    printf("\n");
    printf("-----------�����쳣������������:-----------\n");
    printf("--------------------\n");
    adminView();
        break;
    }
}

/*����*/
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
    printf("����Ҫ���ı���?��������:");
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
    printf("����ɹ�!");
}


/*����*/
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

    printf("����Ҫ���ı��飿������:");
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
                   printf("����ɹ�!");return ;
                }
            }
            
        }
    }
}

/*���� ��*/
void addBook(){
    char id[10],title[10];
    int num;
    FILE *fp;
    int booknum=countBook;
    
    fp = fopen("library.txt","a");
        printf("\n�밴���¸�ʽ����ͼ����Ϣ:���(ID) ����(Title) ����(Num)\n");
        printf("������ͼ����:");
        scanf("%s",books[booknum].id);
        printf("������ͼ������:");
        scanf("%s",books[booknum].title);
        printf("�������������:");
        scanf("%d",&books[booknum].num);
        fprintf(fp,"%s %s %d\n",
            books[booknum].id,books[booknum].title,books[booknum].num);
        fclose(fp);
        booknum++;
        countBook = booknum;
        printf("ͼ�����ӳɹ�!\n");
        adminView();
}

/*�޸� ��*/
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
    printf("�����޸��ı��飿������ID������:");
    scanf("%s",btitle);
    for(int i=0;i<countBook;i++){
        if(strcmp(btitle,books[i].title)==0||strcmp(btitle,books[i].id)==0){
            printf("-----------------��������-----------------\n");
            printf("ͼ����: %s \n",books[i].id);
            printf("ͼ������:��%s��\n",books[i].title);
            printf("��������: %d ��\n",books[i].num);
            printf("-----------------�ָ���-----------------\n");
            printf("�����ͼ�������䶯Ϊ:");
            scanf("%s",books[i].title);
            printf("�����ͼ�������䶯Ϊ:");
            scanf("%d",&books[i].num);
        }
    }
    fp=fopen("library.txt","w");
    for(int i=0;i<countBook;i++){
        fprintf(fp,"%s %s %d\n",books[i].id,books[i].title,books[i].num);
    }
    fclose(fp);
    printf("�޸ĳɹ�!\n");
    printf("\n");
    adminView();
}

/*ɾ�� ��*/
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

    printf("����ɾ���ı��飿������ID������:");
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
    printf("\nɾ���ɹ�!");
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
    printf("\n�밴���¸�ʽ���������Ϣ:���(ID) ����(Name) \n");
    printf("���ӵĶ��߱��Ϊ:");
    scanf("%s",readers[readernum].id);
    printf("���ӵĶ�������Ϊ:");
    scanf("%s",readers[readernum].name);
    fprintf(fp,"%s %s %s\n",
    readers[readernum].id,readers[readernum].name,readers[readernum].bookName);
    fclose(fp);
    readernum++;
    countReader = readernum;
    printf("�������ӳɹ�!");
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
    printf("�����޸��ĸ����ߣ�������ID������:");
    scanf("%s",rtitle);
    countReader = readernum;
    for(int i=0;i<countReader;i++){
        if(strcmp(rtitle,readers[i].name)==0||strcmp(rtitle,readers[i].id)==0){
            printf("----------------�ö�������----------------\n");
            printf("���߱��: %s ",readers[i].id);
            printf("��������: %s ",readers[i].name);
            printf("�������: %s \n",readers[i].bookName);
            printf("-----------------�ָ���-----------------\n");
            printf("��������ֱ䶯Ϊ:");
            scanf("%s",readers[i].name);
            printf("��������������䶯Ϊ:");
            scanf("%s",readers[i].bookName);
        }
    }
    fp=fopen("readerData.txt","w");
    for(int i=0;i<countReader;i++){
        fprintf(fp,"%s %s %s\n",readers[i].id,readers[i].name,readers[i].bookName);
    }
    fclose(fp);

    printf("�޸ĳɹ�!");
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
    
    printf("����ɾ���ĸ����ߣ�������ID������:");
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

    printf("\nɾ���ɹ�!");
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
    printf("�����ѯ�ı��飿������ID������:");
    scanf("%s",btitle);
    for(int i=0;i<countBook;i++){
        if(strcmp(btitle,books[i].title)==0||strcmp(btitle,books[i].id)==0){
            printf("-----------------��ѯ����-----------------\n");
            printf("ͼ����: %s \n",books[i].id);
            printf("ͼ������:��%s��\n",books[i].title);
            printf("��������: %d ��\n",books[i].num);//12
            printf("��������:");
            for(int j=0;j<books[i].cnt;j++){
                if(strlen(books[i].borrowMan[j])!=0){
                    printf("%s ",books[i].borrowMan[j]);
                }
            }
            printf("\n");
            printf("-----------------��ѯ����-----------------\n");
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

    printf("-----------------������-----------------\n");
    for(int i=0;i<booknum;i++){
        printf("���%s-������%s��-����%d\n",books[i].id,books[i].title,books[i].num);//11
    }
     printf("-----------------�ָ���-----------------\n");
}