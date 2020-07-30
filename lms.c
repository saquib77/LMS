#include <windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>
HANDLE hStdout;
struct SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
};
#define RETURNTIME 15
char catagories[][30]={"COMPUTER SCIENCE","CIVIL","MECHANICAL","ELECTRONICS"};
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata();
int Modify_Book_record();
int  checkid(int);
int t(void);
void Password();
void issuerecord();
void loaderanim();
COORD coord ={0,0};
COORD max_res,cursor_size;
void adjustWindowSize(int left,int top,int x,int y){
    struct SMALL_RECT test;
    HANDLE hStdout;
    COORD coord;
    BOOL ok;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = x;
    coord.Y = y;
    test.Left = left;
    test.Top = top;
    test.Right = coord.X-1;
    test.Bottom = coord.Y-1;
    SetConsoleWindowInfo(hStdout, ok, &test);
}
void buffer_size(int x,int y){
    HANDLE wHnd;
    wHnd=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize;
    bufferSize.X=x;
    bufferSize.Y=y;
    SetConsoleScreenBufferSize(wHnd, bufferSize);
}
void gotoxy (int x, int y){
        coord.X = x; coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
FILE *fp,*ft,*fs;
int s;
char findbook;
char password[]={"saquib"};
struct students{
    int id;
    char name[20];
    char father_name[20];
    char rool_no[20];
    char st_class[8];
    int year;
    char mobile_no[14];
};
struct students gsrecord;
struct students chack_record;
struct meroDate{
    int mm,dd,yy;
};
struct books{
    int id;
    int st_id;
    char stname[20];
    char name[20];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;
void make_frame(int x,int x1,int y,int y1){
    int i;
    for(i=x+1;i<=x1-1;i++){
        gotoxy(i,y);
        printf("%c",196);
        gotoxy(i,y1);
        printf("%c",196);
    }
    for(i=y+1;i<=y1-1;i++){
        gotoxy(x,i);
        printf("%c",179);
        gotoxy(x1,i);
        printf("%c",179);
    }
    gotoxy(x,y);
    printf("%c",218);
    gotoxy(x,y1);
    printf("%c",192);
    gotoxy(x1,y1);
    printf("%c",217);
    gotoxy(x1,y);
    printf("%c",191);
}
void get_system_date(int *day,int *month,int *year){
    SYSTEMTIME st;
    GetSystemTime(&st);
    *day=st.wDay;
    *month=st.wMonth;
    *year=st.wYear;
}
void MSGinM(char *a,int y){
    gotoxy(42-(strlen(a)/2),y);
    printf("%s",a);
}
void line_V(int y,int y1,int x,int bands_type,int direction,int plus_y){
    int i;
    for(i=y;i<=y1;i++){
        gotoxy(x,i);
        printf("%c",179);
    }
    if(direction==117){
        gotoxy(x,y);
        if(bands_type==116)
            printf("%c",194);
        if(bands_type==112)
            printf("%c",197);
    }
    else if(direction==100){
        gotoxy(x,y1);
        if(bands_type==116)
            printf("%c",193);
        if(bands_type==112)
            printf("%c",197);
    }
    else if(direction==97){
        gotoxy(x,y);
        if(bands_type==116)
            printf("%c",194);
        if(bands_type==112)
            printf("%c",197);
        gotoxy(x,y1);
        if(bands_type==116)
            printf("%c",193);
        if(bands_type==112)
            printf("%c",197);
    }
    if(plus_y!=0){
        gotoxy(x,plus_y);
        printf("%c",197);
    }
}
int input_date(int *day1,int *month1,int *year1,int x,int y,int ex,int ey){
    int ch;
    int a,day=0,month=0,year=0,count=1,m,loop=0,i,j;
    m=x;
    gotoxy(x,y);
    printf("dd/mm/yyyy");
    restart:
    gotoxy(x,y);
    ch=getche();
    systemback:
    if(ch==-32){
        ch=getche();
        gotoxy(x,y);
        printf("%c",256);
    }
    if(ch>=48 && ch<=57){
        switch(ch){
        case 48:
            a=0;
            break;
        case 49:
            a=1;
            break;
        case 50:
            a=2;
            break;
        case 51:
            a=3;
            break;
        case 52:
            a=4;
            break;
        case 53:
            a=5;
            break;
        case 54:
            a=6;
            break;
        case 55:
            a=7;
            break;
        case 56:
            a=8;
            break;
        case 57:
            a=9;
            break;
        }
        if(count<=2){
            day=(day*10)+a;
            count++;
            x++;
            if(count==3){
                printf("/");
                x++;
            }
            if(count==3){
                    if(day>31 || day<1){
                                ch=8;
                                loop=1;
                                gotoxy(ex,ey);
                                printf("Invalid Day");
                                for(i=0;i<=100000000;i++);
                                for(i=ex;i<=ex+12;i++){
                                    gotoxy(i,ey);
                                    printf("%c",256);
                                    for(j=0;j<=10000000;j++);
                                }
                                goto systemback;
                    }
            }
            goto restart;
        }
        else if(count<=4){
            month=(month*10)+a;
            count++;
            x++;
            if(count==5){
                x++;
                printf("/");
            }
            if(count==5){
                if(month>12 || month<1){
                            ch=8;
                            loop=1;
                            gotoxy(ex,ey);
                            printf("Invalid Month");
                            for(i=0;i<=100000000;i++);
                            for(i=ex;i<=ex+12;i++){
                                gotoxy(i,ey);
                                printf("%c",256);
                                for(j=0;j<=10000000;j++);
                            }
                            goto systemback;
                }
            }
            if(count==5){
                if(day>28){
                    if(month==2){
                            ch=8;
                            loop=1;
                            gotoxy(ex,ey);
                            printf("Invalid Month");
                            for(i=0;i<=100000000;i++);
                            for(i=ex;i<=ex+12;i++){
                                gotoxy(i,ey);
                                printf("%c",256);
                                for(j=0;j<=10000000;j++);
                            }
                            goto systemback;
                    }
                }
                if(day>3){
                    if(month==4 || month==6 || month==9 || month==11){
                            ch=8;
                            loop=1;
                            gotoxy(ex,ey);
                            printf("Invalid Month");
                            for(i=0;i<=100000000;i++);
                            for(i=ex;i<=ex+12;i++)
                            {
                                gotoxy(i,ey);
                                printf("%c",256);
                                for(j=0;j<=10000000;j++);
                            }
                            goto systemback;
                    }
                }
            }
            goto restart;
        }
        else if(count<=8)
        {
            year=(year*10)+a;
            count++;
            x++;
            if(count==9)
            {
                if(year<2018)
                {
                            ch=8;
                            loop=3;
                            gotoxy(ex,ey);
                            printf("Invalid Year");
                            for(i=0;i<=100000000;i++);
                            for(i=ex;i<=ex+12;i++)
                            {
                                gotoxy(i,ey);
                                printf("%c",256);
                                for(j=0;j<=10000000;j++);
                            }
                            goto systemback;
                }
            }
            goto restart;
        }
        else
        {
            *day1=day;
            *month1=month;
            *year1=year;
            return 1;
        }
    }
    else if(ch==13)
    {
        if(day==0 || month==0 || year<2018)
        {
            gotoxy(x,y);
            printf("%c",256);
            goto restart;
        }
        *day1=day;
        *month1=month;
        *year1=year;
        return 1;
    }
    else if(ch==8)
    {
        gotoxy(x,y);
        printf("%c",256);
        if(count>1)
        {
            count--;
        }
        if(count>=5 && count<=8)
        {
            year=year/10;
        }
        if(count>=3 && count<=4)
        {
            month=month/10;
        }
        if(count>=1 && count<=2)
        {
            day=day/10;
        }
        if(count==4)
        {
            gotoxy(x,y);
            printf("%c",256);
            x--;
            gotoxy(x,y);
            printf("%c",256);
        }
        if(count==2)
        {
            gotoxy(x,y);
            printf("%c",256);
            x--;
            gotoxy(x,y);
            printf("%c",256);
        }
        if(x>m)
        {
            x--;
            gotoxy(x,y);
            printf("%c",256);
        }
        if(loop==0)
        goto restart;
        else
        {
            while(loop)
            {
                loop--;
                goto systemback;
            }
        }
    }
    else
    {
        gotoxy(x,y);
        printf("%c",256);
        goto restart;
    }
}
void line_H(int x,int x1,int y,int bands_type,int direction)
{
    int i;
    for(i=x;i<=x1;i++)
    {
        gotoxy(i,y);
        printf("%c",196);
    }
    if(direction==108)
    {
        gotoxy(x,y);
        if(bands_type==116)
            printf("%c",195);
        if(bands_type==112)
            printf("%c",197);
    }
    else if(direction==114)
    {
        gotoxy(x1,y);
        if(bands_type==116)
            printf("%c",180);
        if(bands_type==112)
            printf("%c",197);
    }
    else if(direction==97)
    {
        gotoxy(x,y);
        if(bands_type==116)
            printf("%c",195);
        if(bands_type==112)
            printf("%c",197);
        gotoxy(x1,y);
        if(bands_type==116)
            printf("%c",180);
        if(bands_type==112)
            printf("%c",197);
    }
}
int input_string(char *a,int lenth,int x,int y)
{
    int i=0;
    for(i=0;i<lenth;i++)
    {
        abc:
        gotoxy(x,y);
        a[i]=getche();
        if(a[i]==-32)
        {
            a[i]=getche();
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
		if(a[i]==27)
		{
			a[i]='\0';
			return 202;
		}
        if(a[i]==8)
        {
            if(i==0)
            {
                goto abc;
            }
            else
            {
            i--;
            x--;
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
            }

        }
        if((a[i]>='a' && a[i]<='z') || (a[i]>='A' && a[i]<='Z'))
        {

        }
        else if(a[i]==32 && i!=0 && a[i-1]!=' ')
        {

        }
        else if(a[i]==13 && i>=5)
        {
            a[i]='\0';
            return 1;
        }
        else
        {
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        x++;
    }
    a[i]='\0';
    return a;
}
int input_password(char *a,int lenth,int x,int y)
{
    int i=0,j;
    for(i=0;i<lenth;i++)
    {

        abc:
        gotoxy(x,y);
        a[i]=getche();
        if(a[i]==-32)
        {
            a[i]=getche();
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
		if(a[i]==27)
		{
			a[i]='\0';
			return 202;
		}
        if(a[i]!=8)
        {
            gotoxy(x,y);
            printf("*");
        }
        if(a[i]==8)
        {
            if(i==0)
            {
                goto abc;
            }
            else
            {
            i--;
            x--;
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
            }
        }
        if((a[i]>='a' && a[i]<='z') || (a[i]>='A' && a[i]<='Z') || (a[i]>=48 && a[i]<=57))
        {

        }
        else if(a[i]==33 || a[i]==64 || a[i]==35 || a[i]==36 ||a[i]==37 || a[i]==94 ||a[i]==38 || a[i]==42)
        {

        }
        else if(a[i]==13 && i>=8)
        {
            a[i]='\0';
            return;
        }
        else
        {

            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        x++;
    }
    a[i]='\0';
    return a;
}
int input_numbers(int *num,int lenth,int x,int y)
{
    int temp=0,i;
    char ch;
    for(i=1;i<=lenth;i++)
    {
        restart:
            gotoxy(x,y);
            ch=getche();
            if(ch==-32)
            {
                ch=getche();
                gotoxy(x,y);
                printf("%c",256);
                goto restart;
            }
            if(ch==27)
            {
                *num=0;
                return 202;
            }
            if(ch>=48 && ch<=57)
            {
                x++;
                temp=temp*10+(ch-48);
            }
            else if(ch==13 && temp>0)
            {
                *num=temp;
                return;
            }
            else if(ch==8)
            {
                if(i>1)
                {
                    temp=temp/10;
                    x--;
                    i--;
                }
                    gotoxy(x,y);
                    printf("%c",256);
                goto restart;
            }
            else
            {
                gotoxy(x,y);
                printf("%c",256);
                goto restart;
            }
    }
    *num=temp;
    return;
}
int input_Number_char(char *a,int lenth,int x,int y)
{
    int i=0;
    for(i=0;i<lenth;i++)
    {
        abc:
        gotoxy(x,y);
        a[i]=getche();
        if(a[i]==-32)
        {
            a[i]=getche();
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        if(a[i]==27)
        {
            a[i]='\0';
            return 202;
        }
        if(a[i]==8)
        {
            if(i==0)
            {
                goto abc;
            }
            else
            {
            i--;
            x--;
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
            }

        }
        if((a[i]>='a' && a[i]<='z') || (a[i]>='A' && a[i]<='Z'))
        {

        }
        else if(a[i]==32 && i!=0 && a[i-1]!=' ')
        {

        }
        else if(a[i]>=48 && a[i]<=57)
        {

        }
        else if(a[i]==13 && i>=1)
        {
            a[i]='\0';
            return 1;
        }
        else
        {
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        x++;
    }
    a[i]='\0';
    return a;
}
int input_mobile(char *a,int lenth,int x,int y)
{
    int i=0;
    for(i=0;i<lenth;i++)
    {
        abc:
        gotoxy(x,y);
        a[i]=getche();
        if(a[i]==-32)
        {
            a[i]=getche();
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
		if(a[i]==27)
		{
			a[i]='\0';
			return 202;
		}
        if(a[i]==8)
        {
            if(i==0)
            {
                goto abc;
            }
            else
            {
            i--;
            x--;
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
            }

        }
        if((a[i]>=48 && a[i]<=57))
        {

        }
        else if(a[i]==13 && i==10)
        {
            a[i]='\0';
            return 1;
        }
        else
        {
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        x++;
    }
    a[i]='\0';
    return a;
}
void add_student()
{
    int i;
    FILE *fp;
    make_frame(19,61,4,20);
	MSGinM("Enter the Information Below",5);
	line_H(19,61,6,'t','a');
	line_H(19,61,8,'t','a');
	line_H(19,61,10,'t','a');
	line_H(19,61,12,'t','a');
	line_H(19,61,14,'t','a');
	line_H(19,61,16,'t','a');
	line_H(19,61,18,'t','a');
	gotoxy(23,7);
	printf("Id          :");
	gotoxy(23,9);
	printf("Name        :");
	gotoxy(23,11);
	printf("Father Name :");
	gotoxy(23,13);
	printf("class       :");
	gotoxy(23,15);
	printf("Roll No.    :");
	gotoxy(23,17);
	printf("Year        :");
	gotoxy(23,19);
	printf("Mobile No.  :");
	i=input_numbers(&gsrecord.id,9,39,7);
	if(i==202)
	{
	    return 202;
	}
	i=chack_record_by_id(gsrecord.id);
	if(i==1)
    {
        MSGinM("Student Id Already Exist",22);
        getch();
        return 0;
    }
	i=input_string(gsrecord.name,18,39,9);
	if(i==202)
    {
        return 202;
    }
    i=input_string(gsrecord.father_name,18,39,11);
    if(i==202)
    {
        return 202;
    }
    fflush(stdin);
    i=input_Number_char(gsrecord.st_class,5,39,13);
    if(i==202)
    {
        return 202;
    }
    i=input_Number_char(gsrecord.rool_no,10,39,15);
    if(i==202)
    {
        return 202;
    }
    i=chack_student_rollnumber(gsrecord.st_class,gsrecord.rool_no);
    if(i==1)
    {
        MSGinM("Student Roll Number Already Exist",22);
        getch();
        return 0;
    }
    i=input_numbers(&gsrecord.year,5,39,17);
    if(i==202)
    {
        return 202;
    }
    i=input_mobile(gsrecord.mobile_no,10,39,19);
    if(i==202)
    {
        return 202;
    }
    i=chack_student_mobile(gsrecord.mobile_no);
    if(i==1)
    {
        MSGinM("Mobile Number Already Exist",22);
        getch();
        return 0;
    }
    fp=fopen("Student_record.dat","ab");
    if(fp==NULL)
    {
        MSGinM("An Error, New Record Cannot Add Try Again",22);
        return 404;
    }
    fwrite(&gsrecord,sizeof(struct students),1,fp);
    fclose(fp);
    MSGinM("Record Successfully Added",22);
    getch();
    return 1;
}
int chack_record_by_id(int id)
{
    FILE *fp;
    fp=fopen("Student_record.dat","rb");
    if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
    while(fread(&chack_record,sizeof(struct students),1,fp)>0)
    {
        if(id==chack_record.id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int chack_student_mobile(char *mobile)
{
    FILE *fp;
    fp=fopen("Student_record.dat","rb");
    if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
    while(fread(&chack_record,sizeof(struct students),1,fp)>0)
    {
        if(strcmp(mobile,chack_record.mobile_no)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int chack_student_rollnumber(char *roll_number,char *st_class)
{
    FILE *fp;
    fp=fopen("Student_record.dat","rb");
    if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
    while(fread(&chack_record,sizeof(struct students),1,fp)>0)
    {
        if(strcmp(roll_number,chack_record.rool_no)==0 && strcmp(st_class,chack_record.st_class)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int Remove_student_record(int id)
{
    FILE *fp,*temp;
    fp=fopen("Student_record.dat","rb");
    if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
    temp=fopen("temporary_Srecord.dat","wb");
    if(fp==NULL)
    {

        fclose(fp);
        fclose(temp);
        return 404;
    }
    while(fread(&gsrecord,sizeof(struct students),1,fp)>0)
    {
        if(gsrecord.id!=id)
        {
            fwrite(&gsrecord,sizeof(struct students),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    fp=fopen("Student_record.dat","wb");
    if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
    temp=fopen("temporary_Srecord.dat","rb");
    if(fp==NULL)
    {

        fclose(fp);
        fclose(temp);
        return 404;
    }
    while(fread(&gsrecord,sizeof(struct students),1,temp)>0)
    {
        fwrite(&gsrecord,sizeof(struct students),1,fp);
    }
    fclose(fp);
    fclose(temp);
    remove("temporary_Srecord.dat");
    return 1;
}
int Modify_student_record()
{
    FILE *fp,*temp;
    struct students mrecord;
    int id,i;
    make_frame(1,78,10,14);
    line_V(10,14,21,'t','a',0);
    gotoxy(3,12);
    printf("Enter Student Id");
    i=input_numbers(&id,9,23,12);
    if(i==202)
    {
        return 0;
    }
    i=chack_record_by_id(id);
    if(i==404)
    {
        MSGinM("Student Record List Empty Please Add New Record",16);
        getch();
        return 404;
    }
    if(i==0)
    {
        MSGinM("Record Not Found",16);
        getch();
        return 0;
    }
    system("cls");
    make_frame(19,61,4,20);
	MSGinM("Enter the Information Below",5);
	line_H(19,61,6,'t','a');
	line_H(19,61,8,'t','a');
	line_H(19,61,10,'t','a');
	line_H(19,61,12,'t','a');
	line_H(19,61,14,'t','a');
	line_H(19,61,16,'t','a');
	line_H(19,61,18,'t','a');
	gotoxy(23,7);
	printf("Id          :  %d",id);
	gotoxy(23,9);
	printf("Name        : ");
	gotoxy(23,11);
	printf("Father Name :");
	gotoxy(23,13);
	printf("class       :");
	gotoxy(23,15);
	printf("Roll No.    :");
	gotoxy(23,17);
	printf("Year        :");
	gotoxy(23,19);
	printf("Mobile No.  :");
	gsrecord.id=id;
	i=input_string(gsrecord.name,18,39,9);
	if(i==202)
    {
        return 202;
    }
    i=input_string(gsrecord.father_name,18,39,11);
    if(i==202)
    {
        return 202;
    }
    i=input_Number_char(gsrecord.st_class,5,39,13);
    if(i==202)
    {
        return 202;
    }
    i=input_Number_char(gsrecord.rool_no,10,39,15);
    if(i==202)
    {
        return 202;
    }
    i=input_numbers(&gsrecord.year,5,39,17);
    if(i==202)
    {
        return 202;
    }
    i=input_mobile(gsrecord.mobile_no,10,39,19);
    if(i==202)
    {
        return 202;
    }
    fp=fopen("Student_record.dat","rb");
    if(fp==NULL)
    {
        fclose(fp);
        MSGinM("An Error, You Cannot Modify Record Try Again",21);
        getch();
        return 404;
    }
    temp=fopen("temporary_Srecord.dat","wb");
    if(fp==NULL)
    {

        fclose(fp);
        fclose(temp);
        MSGinM("An Error, You Cannot Modify Record Try Again",21);
        getch();
        return 404;
    }
    while(fread(&mrecord,sizeof(struct students),1,fp)>0)
    {
        if(mrecord.id==id)
        {
            fwrite(&gsrecord,sizeof(struct students),1,temp);
        }
        else
        {
            fwrite(&mrecord,sizeof(struct students),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    fp=fopen("Student_record.dat","wb");
    if(fp==NULL)
    {
        fclose(fp);
        MSGinM("An Error, You Cannot Modify Record Try Again",21);
        getch();
        return 404;
    }
    temp=fopen("temporary_Srecord.dat","rb");
    if(fp==NULL)
    {

        fclose(fp);
        fclose(temp);
        MSGinM("An Error, You Cannot Modify Record Try Again",21);
        getch();
        return 404;
    }
    while(fread(&mrecord,sizeof(struct students),1,temp)>0)
    {
        fwrite(&mrecord,sizeof(struct students),1,fp);
    }
    fclose(fp);
    fclose(temp);
    remove("temporary_Srecord.dat");
    MSGinM("Record Successfully Modified",21);
    getch();
    return 1;
}
int View_all_student_record()
{
    FILE *fp;
    int x,y,flag=0;
    fp=fopen("Student_record.dat","rb");
    if(fp==NULL)
    {
        make_frame(31,53,10,14);
        MSGinM("No Record Found",12);
        getch();
        fclose(fp);
        return 404;
    }
    make_frame(1,78,0,2);
    MSGinM("All Students Record",1);
    y=3;
    while(fread(&chack_record,sizeof(struct students),1,fp)>0)
    {
        make_frame(1,78,y,y+8);
        gotoxy(5,y+1);
        printf("Id          : %d",chack_record.id);
        gotoxy(5,y+2);
        printf("Name        : %s",chack_record.name);
        gotoxy(5,y+3);
        printf("Father Name : %s",chack_record.father_name);
        gotoxy(5,y+4);
        printf("class       : %s",chack_record.st_class);
        gotoxy(5,y+5);
        printf("Roll No.    : %s",chack_record.rool_no);
        gotoxy(5,y+6);
        printf("Year        : %d",chack_record.year);
        gotoxy(5,y+7);
        printf("Mobile No.  : %s",chack_record.mobile_no);
        flag=1;
        y=y+9;
    }
    if(flag==0)
    {
        make_frame(31,53,10,14);
        MSGinM("No Record Found",12);
        getch();
        fclose(fp);
        return 0;
    }
    else
    {
        printf("\n\n Press Any Key To go Back Student Menu");
        getch();
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}
void manage_student_record()
{
    int id,i;
    restart:
        system("cls");
        make_frame(19,61,4,22);
        MSGinM("STUDENT MANAGEMENT",5);
        line_H(19,61,6,'t','a');
        gotoxy(25,8);
        printf("1. Add New Student   ");
        gotoxy(25,10);
        printf("2. Remove Student");
        gotoxy(25,12);
        printf("3. Search Student Record");
        gotoxy(25,14);
        printf("4. Edit Student Record");
        gotoxy(25,16);
        printf("5. View All student list");
        gotoxy(25,18);
        printf("6. Goto Main Menu");
        gotoxy(25,20);
        printf("7. Close Application");
        make_frame(19,61,23,25);
        gotoxy(21,24);
        printf("Enter You Choice : ");
        switch(getch())
        {
        case 27:
            return 1;
        case '1':
            system("cls");
            add_student();
            goto restart;
        case '2':
            system("cls");
            make_frame(1,78,10,14);
            line_V(10,14,21,'t','a',0);
            gotoxy(3,12);
            printf("Enter Student Id");
            i=input_numbers(&id,9,23,12);
            if(i==202)
            {
                goto restart;
            }
            i=chack_record_by_id(id);
            if(i==404)
            {
                MSGinM("Student Record List Empty Please Add New Record",16);
                getch();
                return 404;
            }
            if(i==0)
            {
                MSGinM("Record Not Found",16);
                getch();
                return 0;
            }
            if(i==1)
            {
                i=Remove_student_record(id);
                if(i==1)
                {
                    MSGinM("Record Succefully Removed",16);
                    getch();
                }
                if(i==404)
                {
                    MSGinM("An Error, Record Cannot Remove Try Again \2",16);
                }
                goto restart;
            }
            goto restart;
        case '3':
            system("cls");
            make_frame(1,78,10,14);
            line_V(10,14,21,'t','a',0);
            gotoxy(3,12);
            printf("Enter Student Id");
            i=input_numbers(&id,9,23,12);
            if(i==202)
            {
                goto restart;
            }
            i=chack_record_by_id(id);
            if(i==404)
            {
                MSGinM("Student Record List Empty Please Add New Record",16);
                getch();
                return 404;
            }
            if(i==0)
            {
                MSGinM("Record Not Found",16);
                getch();
                return 0;
            }
            if(i==1)
            {
                system("cls");
                make_frame(19,61,4,20);
                MSGinM("SEARCH RECORD",5);
                line_H(19,61,6,'t','a');
                line_H(19,61,8,'t','a');
                line_H(19,61,10,'t','a');
                line_H(19,61,12,'t','a');
                line_H(19,61,14,'t','a');
                line_H(19,61,16,'t','a');
                line_H(19,61,18,'t','a');
                gotoxy(23,7);
                printf("Id          : %d",chack_record.id);
                gotoxy(23,9);
                printf("Name        : %s",chack_record.name);
                gotoxy(23,11);
                printf("Father Name : %s",chack_record.father_name);
                gotoxy(23,13);
                printf("class       : %s",chack_record.st_class);
                gotoxy(23,15);
                printf("Roll No.    : %s",chack_record.rool_no);
                gotoxy(23,17);
                printf("Year        : %d",chack_record.year);
                gotoxy(23,19);
                printf("Mobile No.  : %s",chack_record.mobile_no);
                getch();
            }
            goto restart;
        case '4':
            system("cls");
            Modify_student_record();
            goto restart;
        case '5':
            system("cls");
            View_all_student_record();
            goto restart;
        case '6':
            return 111;
        case '7':
            exit(0);
        default:
            goto restart;
        }
}
void setcolor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
    {
        wColor=(csbi.wAttributes & 0xF0)+(ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut,wColor);
    }
}
int book_management()
{
    restart:
        system("cls");
        make_frame(19,61,2,20);
        MSGinM("BOOK MANAGEMENT",3);
        line_H(19,61,4,'t','a');
        gotoxy(25,6);
        printf("1. Add New Book   ");
        gotoxy(25,8);
        printf("2. Delete Book");
        gotoxy(25,10);
        printf("3. Search Book");
        gotoxy(25,12);
        printf("4. Edit Book Record");
        gotoxy(25,14);
        printf("5. View All Book list");
        gotoxy(25,16);
        printf("6. Goto Main Menu");
        gotoxy(25,18);
        printf("7. Close Application");
        make_frame(19,61,21,23);
        gotoxy(21,22);
        printf("Enter You Choice : ");
        switch(getch())
        {
        case '1':
            system("cls");
            addbooks();
            goto restart;
            break;
        case '2':
            system("cls");
            delete_book();
            goto restart;
            break;
        case '3':
            system("cls");
            search_book();
            goto restart;
            break;
        case '4':
            system("cls");
            Modify_Book_record();
            goto restart;
            break;
        case '5':
            system("cls");
            View_all_Book_record();
            goto restart;
            break;
        case '6':
            return 1;
            break;
        case '7':
            exit(0);
        case 27:
            return 1;
        default:
            MSGinM("Invalid Choice",24);
            getch();
            goto restart;
        }
}
int main()
{
    adjustWindowSize(0,0,80,26);
    buffer_size(80,3000);
    created_by();
    mainmenu();
    getch();
    return 0;
}
void mainmenu()
{
    SetConsoleTitleA("LIBRARY MANAGEMENT SYSTEM");
    restart:
    system("cls");
	int i;
	system("color e");
	make_frame(1,78,0,2);
	MSGinM("WELCOME TO LIBRARY MANAGEMENT SYSTEM",1);
	make_frame(19,61,8,22);
	MSGinM("MAIN MENU ",9);
	line_H(19,61,10,'t','a');
	gotoxy(25,12);
	printf("1. Book Management");
	gotoxy(25,14);
	printf("2. Book Transactions");
	gotoxy(25,16);
	printf("3. Student Management");
	gotoxy(25,18);
	printf("4. Close Application");
	line_H(19,61,20,'t','a');
	gotoxy(21,21);
	printf("Enter You Choice : ");
	print_date_time(19,61,3,7,41,21);
	switch(getch())
	{
    case '1':
        system("cls");
        book_management();
		goto restart;
		break;
	case '2':
		issuebooks();
		goto restart;
		break;
    case '3':
        system("cls");
		manage_student_record();
		goto restart;
	    break;
	case '4':
		exit(0);
		goto restart;
	    break;
    default:
		MSGinM("\aWrong Entry Please re-entered correct option  ",23);
		print_date_time(19,61,3,7,63,23);
		goto restart;
    }
}
void print_date_time(int x,int x1,int y,int y1,int cursor_podition_x,int cursor_position_y) // Print date and time using this function
{
    /*  Passing Arguments -
        First 4 Arguments for Drow A Rectangle and
        last 2 Arguments for cursor position.
        (x,x1,y,y1)-Arguments for Drow Box
        (cursor_podition_x,cursor_podition_y)-Corsor Position
    */
    setcolor(11);
    time_t s,val=1;
    struct tm *current;
    int day,month,year;
    make_frame(x,x1,y,y1);//make_frame(19,61,3,9);
	gotoxy(x+6,y+1);
	printf("Date  : ");
	gotoxy(x+6,y+3);
	printf("Time  : ");
	get_system_date(&day,&month,&year);
	gotoxy(x+16,y+1);
	printf("%d/%d/%d",day,month,year);
	while(!kbhit())
    {
        s=time(NULL);
        current=localtime(&s);
        gotoxy(x+16,y+3);
        switch(current->tm_hour)
        {
        case 13:
            printf("%02d",1);
            break;
        case 14:
            printf("%02d",2);
            break;
        case 15:
            printf("%02d",3);
            break;
        case 16:
            printf("%02d",4);
            break;
        case 17:
            printf("%02d",5);
            break;
        case 18:
            printf("%02d",6);
            break;
        case 19:
            printf("%02d",7);
            break;
        case 20:
            printf("%02d",8);
            break;
        case 21:
            printf("%02d",9);
            break;
        case 22:
            printf("%02d",10);
            break;
        case 23:
            printf("%02d",11);
            break;
        case 00:
            printf("%02d",12);
            break;
        }
        if(current->tm_hour>=1 && current->tm_hour<=12)
            printf("%02d:%02d:%02d",current->tm_hour,current->tm_min,current->tm_sec);
        else
            printf(":%02d:%02d",current->tm_min,current->tm_sec);
        if(current->tm_hour>=12 && current->tm_hour<=23)
        {
            setcolor(14);
            gotoxy(x+24,y+3);
            printf(" PM");
        }
        else
        {
            setcolor(14);
            gotoxy(x+24,y+3);
            printf(" AM");
        }
        gotoxy(cursor_podition_x,cursor_position_y);
        setcolor(11);
        delay(40);
    }
    setcolor(14);
}
void addbooks(void)    //funtion that add books
{
    int i;
    Abc:
	system("cls");
	make_frame(19,61,4,20);
	MSGinM("CATAGORIES",5);
	line_H(19,61,6,'t','a');
	gotoxy(25,7);
	printf("1. COMPUTER SCIENCE");
	gotoxy(25,9);
	printf("2. CIVIL");
	gotoxy(25,11);
	printf("3. MECHANICAL");
	gotoxy(25,13);
	printf("4. ELECTRONICS");
	gotoxy(25,19);
	printf("5. Back to main menu");
	make_frame(19,61,21,23);
	gotoxy(22,22);
	printf("Enter your Choice : ");
	input_numbers(&s,1,44,22);
	fflush(stdin);
    if(s>=1 && s<=6)
    {

    }
    else if(s==0)
    {
        mainmenu();
    }
    else if(s==7)
    {
        mainmenu();
    }
    else
    {
        MSGinM("Invalid Input  ",24);
        getch();
        goto Abc;
    }
	system("cls");
	fp=fopen("record.dat","ab+");
	if(getdata()==1)
	{
	a.cat=catagories[s-1];
	fseek(fp,0,SEEK_END);
	fwrite(&a,sizeof(a),1,fp);
	fclose(fp);
	MSGinM("The record is sucessfully Saved",21);
	make_frame(19,61,22,24);
	MSGinM("Save any more? (Y/N):",23);
	if(getch()=='n')
	    mainmenu();
	else
	    system("cls");
	    addbooks();
	}
	else
    {
        return 202;
    }
}
void issuebooks(void)  //function that issue books from library
{
    int t;
    int i;
    system("cls");
    make_frame(22,65,6,20);
    line_H(22,65,18,'t','a');
    line_H(22,65,8,'t','a');
    MSGinM("     Book Transactions",7);
    gotoxy(26,10);
    printf("1. Issue A Book");
    gotoxy(26,12);
    printf("2. View Issued Book");
    gotoxy(26,14);
    printf("3. Search Issued Book");
    gotoxy(26,16);
    printf("4. Submit Book");
    gotoxy(26,19);
    printf("Enter Your Choice : ");
    print_date_time(22,65,1,5,47,19);
    switch(getch())
    {
    case 27:
        return 0;
	case '1':  //issue book
	{
		system("cls");
		int c=0;
		char another='y';
		while(another=='y')
		{
			system("cls");
			MSGinM("Issue Book section",8);
			make_frame(1,78,10,14);
			gotoxy(3,12);
			printf("Enter The Book Id");
			line_V(10,14,23,'t','a',0);
			input_numbers(&t,9,25,12);
			fp=fopen("Bibek.dat","rb");
			fs=fopen("Issue.dat","ab+");
			if(checkid(t)==0) //issues those which are present in library
			{
			    system("cls");
			    make_frame(1,78,15,19);
			    gotoxy(3,16);
			    printf("Book Name   : %s",a.name);
			    gotoxy(3,17);
			    printf("Price       : %f",a.Price);
			    gotoxy(3,18);
			    printf("Rack Number : %d",a.rackno);
			    MSGinM("Issue Book To Student",5);

                make_frame(1,78,6,14);
                line_H(1,78,8,'t','a');
                line_H(1,78,10,'t','a');
                line_H(1,78,12,'t','a');
                line_V(6,8,24,'t','a',0);
                line_V(8,10,24,'t','a',8);
                line_V(10,12,24,'t','a',10);
                line_V(12,14,24,'t','a',12);
                gotoxy(3,7);
                printf("Enter Student Id");
                gotoxy(3,9);
                printf("Student Name");
			    fflush(stdin);
			    gotoxy(3,11);
                printf("Enter Issue Date");
                gotoxy(3,13);
                printf("Enter Submit Date");
                gotoxy(25,9);
                input_numbers(&a.st_id,9,26,7);
                i=chack_record_by_id(a.st_id);
                if(i==404)
                {
                    MSGinM("Student List Empty, Please Add Student Record",20);
                    getch();
                    return 0;
                }
                if(i==0)
                {
                    MSGinM("Record Does Not Found",20);
                    getch();
                    return 0;
                }
                if(i==1)
                {
                    strcpy(a.stname,chack_record.name);
                    gotoxy(26,9);
                    printf("%s",a.stname);
                }
                input_date(&a.issued.dd,&a.issued.mm,&a.issued.yy,26,11,37,20);
                input_date(&a.duedate.dd,&a.duedate.mm,&a.duedate.yy,26,13,37,20);
                fseek(fs,sizeof(a),SEEK_END);
                fwrite(&a,sizeof(a),1,fs);
                fclose(fs);
                MSGinM("Book Successfully Issued",20);
                c=1;
			}
			if(c==0)
			{
			gotoxy(10,11);
			MSGinM("No Record Found",15);
			getch();
			}
			make_frame(29,55,22,24);
			MSGinM("Issue any more(Y/N)",23);
			fflush(stdin);
			another=getch();
			fclose(fp);
		}

		break;
	}
	case '2':  //show issued book list
	{
		system("cls");
		int j=4;
		printf("*******************************Issued book list*******************************\n");
		gotoxy(2,2);
		printf("STUDENT Id    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
	       fs=fopen("Issue.dat","rb");
		while(fread(&a,sizeof(a),1,fs)==1)
		{

			gotoxy(2,j);
			printf("%d",a.st_id);
			gotoxy(18,j);
			printf("%s",a.cat);
			gotoxy(30,j);
			printf("%d",a.id);
			gotoxy(36,j);
			printf("%s",a.name);
			gotoxy(51,j);
			printf("%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy );
			gotoxy(65,j);
			printf("%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
			//struct dosdate_t d;
			//_dos_getdate(&d);
			gotoxy(50,25);
//			printf("Current date=%d-%d-%d",d.day,d.month,d.year);
			j++;

		}
		fclose(fs);
		gotoxy(1,25);
		returnfunc();
	}
	break;
	case '3':   //search issued books by id
	{
		system("cls");
		gotoxy(10,6);
		printf("Enter Book ID:");
		int p,c=0;
		char another='y';
		while(another=='y')
		{

			scanf("%d",&p);
			fs=fopen("Issue.dat","rb");
			while(fread(&a,sizeof(a),1,fs)==1)
			{
				if(a.id==p)
				{
					issuerecord();
					gotoxy(10,12);
					printf("Press any key.......");
					getch();
					issuerecord();
					c=1;
				}

			}
			fflush(stdin);
			fclose(fs);
			if(c==0)
			{
				gotoxy(10,8);
				printf("No Record Found");
			}
			gotoxy(10,13);
			printf("Try Another Search?(Y/N)");
			another=getch();
		}
	}
	break;
	case '4':  //remove issued books from list
	{
		system("cls");
		remove_book_from_issue_list();
		mainmenu();
	}
	break;
	default:
	MSGinM("\a   Wrong Entry \2",21);
    getch();
	issuebooks();
	break;
      }
      mainmenu();
}
int remove_book_from_issue_list()
{
    FILE *fp,*temp,*re;
    int i,id,flag=0,flag2=0;
    char ch,student_name[30];
    MSGinM("Enter The Book Id",8);
    make_frame(1,78,10,14);
    gotoxy(3,12);
    printf("Enter The Book Id");;
    line_V(10,14,23,'t','a',0);
    gotoxy(25,12);
    input_numbers(&id,9,25,12);
    fflush(stdin);
    fp=fopen("Issue.dat","rb+");
    if(fp==NULL)
    {
        MSGinM("An Error You Can Not Delete Book Try Again!",16);
        getch();
        fclose(fp);
        return 1;
    }

    while(fread(&a,sizeof(a),1,fp)>0)
    {
        flag2=0;
        if(a.id==id)
        {
            flag=1;
            system("cls");
            make_frame(1,78,8,14);
            line_H(1,78,10,'t','a');
            line_H(1,78,12,'t','a');
            line_V(8,10,24,'t','a',0);
            line_V(12,14,24,'t','a',0);
            line_V(10,12,24,'p','a',0);
            gotoxy(3,9);
            printf("The Book has Taken By");
            gotoxy(3,11);
            printf("Issued Date");
            gotoxy(3,13);
            printf("Returning Date");
            gotoxy(26,9);
            printf("%s",a.stname);
            gotoxy(26,11);
            printf("%d/%d/%d",a.issued.dd,a.issued.mm,a.issued.yy);
            gotoxy(26,13);
            printf("%d/%d/%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
            make_frame(25,59,17,19);
			MSGinM("Do You Want to Remove it?(Y/N)",18);
            ch=getch();
            for(i=25;i<=59;i++)
            {
                gotoxy(i,18);
                printf("%c",256);
                gotoxy(i,17);
                printf("%c",256);
                gotoxy(i,19);
                printf("%c",256);
            }
            if(ch=='y')
            {
                strcpy(student_name,a.stname);
                temp=fopen("record.dat","wb+");
                if(temp==NULL)
                {
                    MSGinM("An Error You Can Not Delete Book Try Again!",16);
                    getch();
                    fclose(fp);
                    fclose(temp);
                    return 1;
                }
                re=fopen("Issue.dat","rb+");
                if(re==NULL)
                {
                    MSGinM("An Error You Can Not Delete Book Try Again!",16);
                    getch();
                    fclose(fp);
                    return 1;
                }
                getch();
                while(fread(&a,sizeof(a),1,re)>0)
                {
                    if(strcmp(student_name,a.stname)==0 && a.id==id)
                    {
                        flag2=1;
                    }
                    else
                    {
                        fwrite(&a,sizeof(a),1,temp);

                    }
                }
                fclose(temp);
                fclose(re);
                temp=fopen("record.dat","rb+");
                re=fopen("Issue.dat","wb+");
                while(fread(&a,sizeof(a),1,temp)>0)
                {
                    fwrite(&a,sizeof(a),1,re);
                }
                fclose(temp);
                fclose(re);
                remove("record.dat");
                if(flag2)
                {
                    fclose(fp);
                    MSGinM("Book Successfully Remove From Issue List",16);
                }
                make_frame(29,56,17,19);
                MSGinM("Delete any more(Y/N)",18);
                ch=getch();
                if(ch=='y' || ch=='Y')
                {
                    fp=fopen("Issue.dat","rb+");
                    if(fp==NULL)
                    {
                        MSGinM("An Error You Can Not Delete Book Try Again!",16);
                        getch();
                        fclose(fp);
                        return 0;
                    }
                }
                else
                {
                    return 1;
                }
            }
        }
    }
    if(flag==0)
    {
        MSGinM("No Record Found",16);
        fclose(fp);
        getch();
        return 0;
    }
    return 1;
}
void returnfunc(void)
{
    {
	printf(" Press ENTER to return to main menu");
    }
    a:
    if(getch()==13) //allow only use of enter
    mainmenu();
    else
    goto a;
}
int getdata()
{
	int t;
	int i;
	make_frame(19,61,4,20);
	MSGinM("Enter the Information Below",5);
	line_H(19,61,6,'t','a');
	line_H(19,61,8,'t','a');
	line_H(19,61,10,'t','a');
	line_H(19,61,12,'t','a');
	line_H(19,61,14,'t','a');
	line_H(19,61,16,'t','a');
	line_H(19,61,18,'t','a');
	gotoxy(23,7);
	printf("Category  :  %s",catagories[s-1]);
	gotoxy(23,9);
	printf("Book ID   : ");
	gotoxy(23,11);
	printf("Book Name :");
	gotoxy(23,13);
	printf("Author    :");
	gotoxy(23,15);
	printf("Quantity  :");
	gotoxy(23,17);
	printf("Price     :");
	gotoxy(23,19);
	printf("Rack No   :");
	i=input_numbers(&t,9,36,9);
	if(i==202)
    {
        return 202;
    }
	fflush(stdin);
	if(checkid(t) == 0)
	{
		MSGinM("\aThe book id already exists\a",22);
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	i=input_string(a.name,18,36,11);
	if(i==202)
    {
        return 202;
    }
	fflush(stdin);
	i=input_string(a.Author,18,36,13);
    if(i==202)
    {
        return 202;
    }
	fflush(stdin);
	i=input_numbers(&a.quantity,9,36,15);
	if(i==202)
    {
        return 202;
    }
	fflush(stdin);
	gotoxy(36,17);
	scanf("%f",&a.Price);
	fflush(stdin);
    i=input_numbers(&a.rackno,9,36,19);
    if(i==202)
    {
        return 202;
    }
	fflush(stdin);
	return 1;
}
int checkid(int t)  //check whether the book is exist in library or not
{
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	return 0;  //returns 0 if book exits
      return 1; //return 1 if it not
}
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}
void Password(void) //for password option
{
    system("color a");
    created_by();
   system("cls");
   char d[25]="Password Protected";
   char ch,pass[30];
   int i=0,j;
   abc:
       system("cls");
       make_frame(28,54,6,8);
       MSGinM(d,7);
       make_frame(1,78,10,14);
       line_V(10,14,24,'t','a',0);
       gotoxy(3,12);
       printf("Enter Password");
       input_password(pass,11,26,12);
       if(strcmp(pass,password)==0)
       {
        Clear_buffer();
        make_frame(28,54,16,18);
        MSGinM("Login Successfull",17);
        MSGinM("Press any key to countinue.....",20);
        getch();
        mainmenu();
       }
       else
       {
           MSGinM("\aWarning!! Incorrect Password",16);
           getch();
           goto abc;
       }
}
void Clear_buffer()     //Function for clear Buffer
{
    while(kbhit())
    {
        getche();
    }
}
void issuerecord()  //display issued book's information
{
		 system("cls");
		 gotoxy(10,7);
		 printf("Student Id : %d",a.st_id);
		 gotoxy(10,8);
		 printf("The Book has taken by Mr. %s",a.stname);
		 gotoxy(10,9);
		 printf("Issued Date:%d-%d-%d",a.issued.dd,a.issued.mm,a.issued.yy);
		 gotoxy(10,10);
		 printf("Returning Date:%d-%d-%d",a.duedate.dd,a.duedate.mm,a.duedate.yy);
}
void loaderanim()
{
int loader;
system("cls");
gotoxy(20,10);
printf("LOADING........");
printf("\n\n");
gotoxy(22,11);
for(loader=1;loader<20;loader++)
{
delay(100);printf("%c",219);}
}
void created_by()          //Welcome Msg
{
    int i,x,x1;
    float load=3.4482;
    x=42;
    x1=42;
    setcolor(11);
    for(;x1<=54;x1++,x--)
    {
        system("cls");
        make_frame(x,x1,10,14);
        delay(20);
    }
    gotoxy(31,9);
    printf("Project Made  By Saquib Ahmed");
    MSGinM("Saquib Ahmed",12);
    MSGinM("   LOADING...",16);
    make_frame(27,57,17,19);
    for(i=28;i<=56;i++)
    {
        gotoxy(i,18);
        printf("%c",219);
        delay(20);
        gotoxy(41,20);
        printf("%.0f%c",load,37);
        load=load+3.4482;
    }
    getch();
}
int find_book_id(int t)  //check whether the book is exist in library or not
{
	FILE *fp;
	fp=fopen("Bibek.dat","rb");
	if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
	while(fread(&a,sizeof(a),1,fp)==1)
    {
        if(a.id==t)
        {
            fclose(fp);
            return 1;  //returns 1 if book exits
        }
    }
    fclose(fp);
	return 0;  //return 0 if it not
}
int find_book_by_name(char *name)  //check whether the book is exist in library or not
{
	FILE *fp;
	fp=fopen("Bibek.dat","rb");
	if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
	while(fread(&a,sizeof(a),1,fp)==1)
    {
        if(strcmp(name,a.name)==0)
        {
            fclose(fp);
            return 1;  //returns 1 if book exits
        }
    }
    fclose(fp);
	return 0;  //return 0 if it not
}
int delete_book()       // Delete Book From record
{
    system("cls");
    FILE *fp,*temp;
    int id,i;
    make_frame(33,50,7,9);
    MSGinM("Delete Book",8);
    make_frame(1,78,10,14);
    gotoxy(3,12);
    printf("Enter The Book Id");
    line_V(10,14,23,'t','a',0);
    i=input_numbers(&id,9,25,12);
    if(i==202)
    {
        return 202;
    }
    i=find_book_id(id);
    if(i==404)
    {
        MSGinM("No Record Found",16);
        getch();
        return 404;
    }
    if(i==0)
    {
        MSGinM("No Record Found",16);
        getch();
        return 404;
    }
    fp=fopen("Bibek.dat","rb");
    if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
    temp=fopen("temporary_Bookrecord.dat","wb");
    if(fp==NULL)
    {

        fclose(fp);
        fclose(temp);
        return 404;
    }
    while(fread(&a,sizeof(a),1,fp)>0)
    {
        if(a.id!=id)
        {
            fwrite(&a,sizeof(a),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    fp=fopen("Bibek.dat","wb");
    if(fp==NULL)
    {
        MSGinM("An Error, Book Does Not Removed",16);
        getch();
        fclose(fp);
        return 404;
    }
    temp=fopen("temporary_Bookrecord.dat","rb");
    if(fp==NULL)
    {
        MSGinM("An Error, Book Does Not Removed",16);
        getch();
        fclose(fp);
        fclose(temp);
        return 404;
    }
    while(fread(&a,sizeof(a),1,temp)>0)
    {
        fwrite(&a,sizeof(a),1,fp);
    }
    fclose(fp);
    fclose(temp);
    remove("temporary_Bookrecord.dat");
    MSGinM("Book Successfully Removed",16);
    getch();
    return 1;
}
void search_book()    //Search Book Record
{
    int i,id;
    char ch,book_name[20];
    reset:
        make_frame(22,63,8,14);
        make_frame(22,63,15,17);
        line_H(22,63,10,'t','a');
        MSGinM("Search Book By Id Or Book Name",9);
        gotoxy(27,11);
        printf("1. Search Book By Id");
        gotoxy(27,13);
        printf("2. Search Book Ny Name");
        gotoxy(25,16);
        printf("Enter You Choice : ");
        ch=getch();
        switch(ch)
        {
        case 27:
            return 0;
        case '1':
            system("cls");
            make_frame(1,78,10,14);
            line_V(10,14,23,'t','a',0);
            gotoxy(3,12);
            printf("Enter The Book Id");
            i=input_numbers(&id,9,25,12);
            if(i==202)
            {
                return 202;
            }
            i=find_book_id(id);
            if(i==404 || i==0)
            {
                MSGinM("No Record Found",16);
                getch();
                return 0;
            }
            else if(i==1)
            {
                system("cls");
                make_frame(19,61,4,20);
                MSGinM("SEARCH RECORD  ",5);
                line_H(19,61,6,'t','a');
                line_H(19,61,8,'t','a');
                line_H(19,61,10,'t','a');
                line_H(19,61,12,'t','a');
                line_H(19,61,14,'t','a');
                line_H(19,61,16,'t','a');
                line_H(19,61,18,'t','a');
                gotoxy(23,7);
                printf("Id          : %d",a.id);
                gotoxy(23,9);
                printf("Book Name   : %s",a.name);
                gotoxy(23,11);
                printf("Author Name : %s",a.Author);
                gotoxy(23,13);
                printf("Category    : %s",a.cat);
                gotoxy(23,15);
                printf("Quantity    : %d",a.quantity);
                gotoxy(23,17);
                printf("Rack Number : %d",a.rackno);
                gotoxy(23,19);
                printf("Price       : %.2f",a.Price);
                getch();
                return 1;
            }
        case '2':
            system("cls");
            make_frame(1,78,10,14);
            line_V(10,14,23,'t','a',0);
            gotoxy(3,12);
            printf("Enter Book Name");
            i=input_string(book_name,18,25,12);
            if(i==202)
            {
                return 202;
            }
            i=find_book_by_name(book_name);
            if(i==404 || i==0)
            {
                MSGinM("No Record Found",16);
                getch();
                return 0;
            }
            system("cls");
            make_frame(19,61,4,20);
            MSGinM("SEARCH RECORD  ",5);
            line_H(19,61,6,'t','a');
            line_H(19,61,8,'t','a');
            line_H(19,61,10,'t','a');
            line_H(19,61,12,'t','a');
            line_H(19,61,14,'t','a');
            line_H(19,61,16,'t','a');
            line_H(19,61,18,'t','a');
            gotoxy(23,7);
            printf("Id          : %d",a.id);
            gotoxy(23,9);
            printf("Book Name   : %s",a.name);
            gotoxy(23,11);
            printf("Author Name : %s",a.Author);
            gotoxy(23,13);
            printf("Category    : %s",a.cat);
            gotoxy(23,15);
            printf("Quantity    : %d",a.quantity);
            gotoxy(23,17);
            printf("Rack Number : %d",a.rackno);
            gotoxy(23,19);
            printf("Price       : %.2f",a.Price);
            getch();
            return 1;
        default:
            MSGinM("Invalid Choice",19);
            getch();
            goto reset;
       }

}
int View_all_Book_record()  //View All Book
{
    FILE *fp;
    int x,y,flag=0;
    fp=fopen("Bibek.dat","rb");
    if(fp==NULL)
    {
        fclose(fp);
        return 404;
    }
    make_frame(1,78,0,2);
    MSGinM("All Books Record",1);
    y=3;
    while(fread(&a,sizeof(a),1,fp)>0)
    {
        make_frame(1,78,y,y+8);
        gotoxy(5,y+1);
        printf("Category    : %s",a.cat);
        gotoxy(5,y+2);
        printf("Book Name   : %s",a.name);
        gotoxy(5,y+3);
        printf("Author Name : %s",a.Author);
        gotoxy(5,y+4);
        printf("Id          : %d",a.id);
        gotoxy(5,y+5);
        printf("Quantity    : %d",a.quantity);
        gotoxy(5,y+6);
        printf("Rack Number : %d",a.rackno);
        gotoxy(5,y+7);
        printf("Price       : %.2f",a.Price);
        flag=1;
        y=y+9;
    }
    if(flag==0)
    {
        make_frame(31,53,10,14);
        MSGinM("No Record Found",12);
        getch();
        fclose(fp);
        return 0;
    }
    else
    {
        printf("\n\n Press Any Key To go Back Main Menu");
        getch();
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}
int Modify_Book_record()    //Modify Book Record
{
    FILE *fp,*temp;
    struct books new_record;
    int id,i;
    make_frame(1,78,10,14);
    line_V(10,14,21,'t','a',0);
    gotoxy(3,12);
    printf("Enter Book Id");
    i=input_numbers(&id,9,23,12);
    if(i==202)
    {
        return 202;
    }
    i=find_book_id(id);
    if(i==404)
    {
        MSGinM("Book Record List Empty Please Add New Record",16);
        getch();
        return 404;
    }
    if(i==0)
    {
        MSGinM("Record Not Found",16);
        getch();
        return 0;
    }
    new_record.cat=a.cat;
    new_record.id=id;
    system("cls");
    make_frame(19,61,4,20);
	MSGinM("Enter the Information Below",5);
	line_H(19,61,6,'t','a');
	line_H(19,61,8,'t','a');
	line_H(19,61,10,'t','a');
	line_H(19,61,12,'t','a');
	line_H(19,61,14,'t','a');
	line_H(19,61,16,'t','a');
	line_H(19,61,18,'t','a');
	gotoxy(23,7);
	printf("Id          :   %d",new_record.id);
	gotoxy(23,9);
	printf("Book Name   : ");
	gotoxy(23,11);
	printf("Author Name :");
	gotoxy(23,13);
	printf("Category    :   %s",new_record.cat);
	gotoxy(23,15);
	printf("Quantity    :");
	gotoxy(23,17);
	printf("Rack Number :");
	gotoxy(23,19);
	printf("Price       :");
	i=input_string(new_record.name,18,39,9);
	if(i==202)
    {
        return 202;
    }
    i=input_string(new_record.Author,18,39,11);
    if(i==202)
    {
        return 202;
    }
    i=input_numbers(&new_record.quantity,9,39,15);
    if(i==202)
    {
        return 202;
    }
    i=input_numbers(&new_record.rackno,9,39,17);
    if(i==202)
    {
        return 202;
    }
    gotoxy(39,19);
    scanf("%f",&new_record.Price);
    if(i==202)
    {
        return 202;
    }
    fp=fopen("Bibek.dat","rb");
    if(fp==NULL)
    {
        fclose(fp);
        MSGinM("An Error, You Cannot Modify Record Try Again",21);
        getch();
        return 404;
    }
    temp=fopen("temporary_Modification.dat","wb");
    if(fp==NULL)
    {

        fclose(fp);
        fclose(temp);
        MSGinM("An Error, You Cannot Modify Record Try Again",21);
        getch();
        return 404;
    }
    while(fread(&a,sizeof(a),1,fp)>0)
    {
        if(a.id==id)
        {
            fwrite(&new_record,sizeof(a),1,temp);
        }
        else
        {
            fwrite(&a,sizeof(a),1,temp);
        }
    }
    fclose(fp);
    fclose(temp);
    fp=fopen("Bibek.dat","wb");
    if(fp==NULL)
    {
        fclose(fp);
        MSGinM("An Error, You Cannot Modify Record Try Again",21);
        getch();
        return 404;
    }
    temp=fopen("temporary_Modification.dat","rb");
    if(fp==NULL)
    {

        fclose(fp);
        fclose(temp);
        MSGinM("An Error, You Cannot Modify Record Try Again",21);
        getch();
        return 404;
    }
    while(fread(&a,sizeof(a),1,temp)>0)
    {
        fwrite(&a,sizeof(a),1,fp);
    }
    fclose(fp);
    fclose(temp);
    remove("temporary_Modification.dat");
    MSGinM("Record Successfully Modified",22);
    getch();
    return 1;
}
