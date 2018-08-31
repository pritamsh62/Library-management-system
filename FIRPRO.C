#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct book
{
   int bid;
   char title[100];
   char sub[30];
   char auth[100];
}b;
struct student
{
    int sid;
    char nm[100],isdt[30];
    int bid;

}s;
FILE *fp1,*fp2;
int authentication();
void inserbook();
void deletebook();
void modifybook();
void issubook();
void returnbook();
void viewbooks();
void searchtitle();
void searchauth();
void searchsub();
void main()
{
    int ch,f,ch1,ch2;
    clrscr();
    while(1)
    {
	printf("========WELCOME TO LIB SYSTEM=========");
	printf("\n1 for Admin\n 2 for Student\n3 for exit");
	printf("\nEnter you Choice:");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			 f=authentication();
			 if(f==1)
			 {
			   while(1){
			    printf("\nWelcome Admin\n\n\n1 for add new book\n2 for delete book\n 3 for modyfy book\n4 for issue book \n5 for return book\n 6 for view  issues book \n 7 for logout");
			    printf("\nEnter your choice:");
			    scanf("%d",&ch1);
			     switch(ch1)
			     {
					case 1:
						inserbook();
						break;
					case 2:
						deletebook();
						break;
					case 3:
						modifybook();
						break;
					case 4:
						issubook();
						break;
					case 5:
						returnbook();
						break;
					case 6:
						viewbooks();
						break;
					case 7:
						exit(0);
				}//sawitch
			     }//inner while
			 }//end if
			 else
			   printf("\n\nInvalid userid or passoword");
			  break;
		case 2:
			while(1)
			{
			    printf("\n 1.View Book details\n2.search bu titile\n3 search by author\n4 search by subject\n5 for exit\nEnter your choice:");
			    scanf("%d",&ch2);
			     switch(ch2)
				{
				case 1:
					viewbooks();
					break;
				case 2:
					searchtitle();
					break;
				case 3:
					searchauth();
					break;
				case 4:
					searchsub();
					break;
				case 5:
					exit(0);
			   }
			}

		  case 3:
			   exit(0);
	       }
	   }
    }//main
int authentication()
{
      int t=0,i=0;
      char uid[30],pwd[30],ch;
      printf("Enter userid:");
      fflush(stdin);
      gets(uid);
      printf("Enter password:");
      fflush(stdin);
      do{
	 ch=getch();

	 if(ch==13)
	  break;
	 else
	 {
	   printf("*");
	   pwd[i]=ch;
	   i++;
	 }
	}while(ch!=13);
       pwd[i]=NULL;
     //  puts(pwd);
     if(strcmpi(uid,"admin")==0 && strcmpi(pwd,"123456")==0)
       t=1;
     return t;

}
void inserbook()
{
   int bid1=0;
   fp1=fopen("lib_book.dat","r");
   if(fp1!=NULL)
   {
      while(fread((char*)&b,sizeof(b),1,fp1)==1)
       bid1=b.bid;
   }
   bid1++;
   printf("\nNew bid is=%d",bid1);
   fclose(fp1);
   fp1=fopen("lib_book.dat","a");
   printf("\nEnter Book title:");
   fflush(stdin);
   gets(b.title);
   printf("\nEnter Subject:");
   fflush(stdin);
   gets(b.sub);
   printf("\nEnter Author:");
   fflush(stdin);
   gets(b.auth);
   b.bid=bid1;
   fwrite((char*)&b,sizeof(b),1,fp1);
   printf("\nBook inserted successfully");
   fclose(fp1);

}
void deletebook()
{
   int bid1;
   printf("\nEnter bid to delete:");
   scanf("%d",&bid1);
   fp1=fopen("lib_book.dat","r");
   fp2=fopen("lib_temp.dat","a");
   while(fread((char*)&b,sizeof(b),1,fp1))
   {
	if(b.bid!=bid1)
	 fwrite((char*)&b,sizeof(b),1,fp2);
   }
   fclose(fp1);
   fclose(fp2);
   remove("lib_book.dat");
   rename("lib_temp.dat","lib_book.dat");
   printf("\nRecord deleteed successfully");
}
void modifybook()
{
    char ch1,ch2,ch3,ch4;
    int bid1;
    fp1=fopen("lib_book.dat","r");
    while(fread((char*)&b,sizeof(b),1,fp1))
    {
	printf("\n%d\t%s\t%s\t%s",b.bid,b.title,b.sub,b.auth);
    }
    fclose(fp1);
    printf("\nDo you want to modify(y,n)");
    fflush(stdin);
    scanf("%c",&ch1);
    if(ch1=='y')
    {
	 printf("\nEnter bid to modify:");
	 fflush(stdin);
	 scanf("%d",&bid1);
	 fp1=fopen("lib_book.dat","r");
	 fp2=fopen("lib_temp.dat","a");
	 while(fread((char*)&b,sizeof(b),1,fp1))
	 {
		if(b.bid==bid1)
		{
			printf("\nModify Title(y,n)");
			fflush(stdin);
			scanf("%c",&ch2);
			if(ch2=='y')
			{
			   printf("Enter new title:");
			   fflush(stdin);
			   gets(b.title);
			}
			printf("\nModify Subject(y,n)");
			fflush(stdin)  ;
			scanf("%c",&ch3);
			if(ch3=='y')
			{
			   printf("\nEnter new subject:");
			   fflush(stdin);
			   gets(b.sub);
			}
			printf("\nModify author(y,n)");
			fflush(stdin);
			scanf("%c",&ch4);
			if(ch4=='y')
			{
				printf("\nEnter new author:");
				fflush(stdin);
				gets(b.auth);
			}
		}
		fwrite((char*)&b,sizeof(b),1,fp2);
	 }
	 fclose(fp1);
	 fclose(fp2);
	 remove("lib_book.dat");
	 rename("lib_temp.dat","lib_book.dat");
	 printf("\nRecord modified successfully:");
    }

}
void issubook()
{
    fp1=fopen("lib_issue.dat","a");
    printf("\nEnter Sid:");
    fflush(stdin);
    scanf("%d",&s.sid);
    printf("\nEnter Name:");
    fflush(stdin);
    gets(s.nm);
    printf("\nEnter Date:");
    fflush(stdin);
    gets(s.isdt);
    printf("\nEnter bid:");
    fflush(stdin);
    scanf("%d",&s.bid);
    fwrite((char*)&s,sizeof(s),1,fp1);
    printf("\nBook issued successfully");
    fclose(fp1);
}
void returnbook()
{
    int bid1,sid1;
    fp1=fopen("lib_issue.dat","r");
    fp2=fopen("lib_temp.dat","a");
    printf("\nEnter sid");
    fflush(stdin);
    scanf("%d",&sid1);
    printf("\nEnter bid:");
    fflush(stdin);
    scanf("%d",&bid1);
    while(fread((char*)&s,sizeof(s),1,fp1))
    {
	if(s.sid==sid1 && s.bid==bid1)
	{}
	else
	{
	   fwrite((char*)&s,sizeof(s),1,fp2);
	}
    }
    fclose(fp1);
    fclose(fp2);
    remove("lib_issue.dat");
    rename("lib_temp.dat","lib_issue.dat");
    printf("\nBook return successfully");
}
void viewbooks()
{
   int sid1;
   fp1=fopen("lib_issue.dat","r");
   printf("Enter sid:");
   fflush(stdin);
   scanf("%d",&sid1);
   while(fread((char*)&s,sizeof(s),1,fp1))
   {
	if(s.sid==sid1)
	{
		printf("\n%d\t%s\t%s\t%d",s.sid,s.nm,s.isdt,s.bid);
	}
   }
   fclose(fp1);

}
void searchtitle()
{
    char title1[30];
    fp1=fopen("lib_book.dat","r");
    printf("Enter Title to search:");
    fflush(stdin);
    gets(title1);
  while(fread((char*)&b,sizeof(b),1,fp1))
  {
	if(strcmpi(b.title,title1)==0)
	{
	   printf("\t%d\t%s\t%s\t%s",b.bid,b.title,b.sub,b.auth);
	}
  }
  fclose(fp1);

}
void searchauth()
{
char auth1[30];
    fp1=fopen("lib_book.dat","r");
    printf("Enter author to search:");
    fflush(stdin);
    gets(auth1);
  while(fread((char*)&b,sizeof(b),1,fp1))
  {
	if(strcmpi(b.auth,auth1)==0)
	{
	   printf("\t%d\t%s\t%s\t%s",b.bid,b.title,b.sub,b.auth);
	}
  }
  fclose(fp1);
}
void searchsub()
{
 char sub1[30];
    fp1=fopen("lib_book.dat","r");
    printf("Enter subject to search:");
    fflush(stdin);
    gets(sub1);
  while(fread((char*)&b,sizeof(b),1,fp1))
  {
	if(strcmpi(b.sub,sub1)==0)
	{
	   printf("\t%d\t%s\t%s\t%s",b.bid,b.title,b.sub,b.auth);
	}
  }
  fclose(fp1);
}
/*
bid   title   subject  author
b=1      ---     ----     ---
b=2     ----     ----      ---
*/