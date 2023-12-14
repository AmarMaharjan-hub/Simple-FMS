#include<stdio.h>
#include<conio.h>
#include<process.h>
void add();
void view();
void search();
void deposit();
void withdraw();
void update();
void delete();
int checkId(int);
int checkPhone(int);
struct customer
{
	
	int id;
	char name[20];
	char address[20];
	int contact;
	int balance;
};

void main()
{
	int choice;
	printf("Welcome to Finance management system");
	printf("\n\n---press any key to continue---");
	getch();
	system("cls");
	while(1)
	{
		printf("\n::::MENU::::\n");
		printf("\n1. Add Account\n2. View Account\n3. Search Account\n4. Deposit\n5. Withdraw\n6. Update Account\n7. Delete Account\n8. Exit\n");
		printf("\nEnter your choice(1-8): ");
		scanf("%d",&choice);
		switch(choice)
		{		
			case 1:
				{
					char c;
					do
					{
					add();
					up1:
					printf("\nDo you want to add another record?(y/n)\n");
					scanf(" %c",&c);
					}
					while(c=='Y'||c=='y');
					if(c=='N'||c=='n')
					{
					break;
					}
					else
					{
						printf("\nInvalid Input.\nEnter 'Y' for yes, 'N' for no.\n\nPress any key to continue.\n\n");
						getch();
						system("cls");
						goto up1;
					}
				}
			case 2:
				{
					view();
					printf("\nPress any key to continue\n");
					getch();
					break;
				}
			case 3:
				{
					search();
					printf("\nPress any key to continue\n");
					getch();
					break;
				}
			case 4:
				{
					deposit();
					printf("\nPress any key to continue\n");
					getch();
					system("cls");
					break;
				}
			case 5:
				{
					withdraw();
					printf("\nPress any key to continue\n");
					getch();
					system("cls");
					break;
				}
			case 6:
				{
					update();
					printf("\nPress any key to continue\n");
					getch();
					system("cls");
					break;
				}
			case 7:
				{
					delete();
					printf("\nPress any key to continue\n");
					getch();
					system("cls");
					break;
				}
			case 8:
				{
					exit(0);
				}
			default:
				{
					system("cls");
					printf("Invalid input. Please enter a number between (1-8).\n");
					printf("Press Enter to continue.\n\n");
					getch();
					system("cls");
				}
		}
	}
}
void add()
{
	system("cls");
	struct customer s1;
	FILE *fp;
	int bal;
	fp=fopen("customer.dat","a+");
	if(fp==NULL)
	{
		printf("\ncouldn't create file");
	}
	do
	{
	printf("\nEnter id number of customer:\t");
	scanf("%d",&s1.id);
	}while(checkId(s1.id)==0);
	
	printf("\nEnter a name of customer:\t");
	fflush(stdin);
	scanf("%[^\n]",&s1.name);
	
	printf("\nEnter a address of customer:\t");
	fflush(stdin);
	scanf("%[^\n]",&s1.address);
	
	do
	{
	printf("\nEnter contact number of customer:\t");
	fflush(stdin);
	scanf("%d",&s1.contact);
	}while(checkPhone(s1.contact)==0);
	printf("\nEnter starting balance of customer:\t");
	fflush(stdin);
	scanf("%d",&s1.balance);
	
	bal=fwrite(&s1,sizeof(s1),1,fp);
	if(bal!=0)
	{
		printf("\nOne record added successfully");
	}
	else
	{
		printf("\nFailed to add record");
	}
	fclose(fp);
	// printf("add customer");
}
void view()
{
	system("cls");
	FILE *fp;
	struct customer s1;
	int result,counter=0;
	fp=fopen("customer.dat","r");
	if(fp==NULL)
	{
		printf("\nCouldn't open file");
	}
	while(fread(&s1,sizeof(s1),1,fp)==1)
	{
		counter=1;
		printf("\n name: %s",s1.name);
		printf("\n ID : %d",s1.id);
		printf("\n address : %s",s1.address);
		printf("\n Phone number: %d",s1.contact);
		printf("\n Balance: %d",s1.balance);
		printf("\n*************************");
	}
	if(counter==0)
	{
		printf("\nNo record found");
	}
	fclose(fp);
}
void search()
{
	system("cls");
	FILE *fp;
	struct customer s1;
	int id,flag=0,phn;
	char des=NULL;
	fp=fopen("customer.dat","r");
	if(fp==NULL)
	{
		printf("\nCouldn't open file");
	}
	else
	{
		up2:
		rewind(fp);
		printf("\nEnter the id of a customer: ");
		scanf("%d",&id);
		while(fread(&s1,sizeof(s1),1,fp)==1)
		{
			if(s1.id==id)
			{
				printf("\nName: %s\nAddress: %s\nContact: %d\nBalance :%d\n",s1.name,s1.address,s1.contact,s1.balance);
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
				up3:
				printf("\nSearch not found.\n\nThe identification number is incorrect.\n");
				printf("\nWould you like to try again(Y/N): ");
				fflush(stdin);
				scanf(" %c",&des);
				if(des=='Y'||des=='y')
				{
					system("cls");
					goto up2;
				}
				else if(des=='N'||des=='n')
				{
					printf("Go to the view section for more info.");
				}
				else
				{
					printf("\nInvalid Input.\nEnter 'Y' for yes, 'N' for no.\n\nPress any key to continue.\n\n");
					getch();
					system("cls");
					goto up3;
				}
		}
	}
	fclose(fp);
}
void deposit()
{
	system("cls");
	FILE *fp,*fpt;
	struct customer s1,s2;
	int flag=0,id;
	int add;
	fp=fopen("customer.dat","r");
	fpt=fopen("temp.dat","w");
	if(fp==NULL)
	{
		printf("\nCouldnt open file.\n");
	}
	else
	{
		printf("\nEnter identification no: ");
		scanf("%d",&id);
		
		while(fread(&s1,sizeof(s1),1,fp))
		{
			if(id==s1.id)
			{
				printf("\nName:%s\nBalance:%d\n",s1.name,s1.balance);
				printf("Enter your deposit amount: ");
				scanf("%d",&add);
				s2=s1;
				add+=s1.balance;
				flag=1;
				break;
			}
		}
		rewind(fp);
		if(flag==0)
		{
			printf("\nAccount not found.\n");
		}
		else
		{
			while(fread(&s1,sizeof(s1),1,fp))
			{
				if(s1.id!=id)
				{
					fwrite(&s1,sizeof(s1),1,fpt);
				}
			}
		
			fclose(fp);
			fclose(fpt);
			
			fp=fopen("temp.dat","a+");
			s2.balance=add;
			
			fwrite(&s2,sizeof(s2),1,fp);
			fclose(fp);
			fp=fopen("customer.dat","w");
			fpt=fopen("temp.dat","r");
			while(fread(&s1,sizeof(s1),1,fpt))
			{
				fwrite(&s1,sizeof(s1),1,fp);
			}
			printf("\nAmount deposited\nNew Balance:%d",s2.balance);
			fclose(fp);
			fclose(fpt);
		}
	}
}
void withdraw()
{
	system("cls");
	FILE *fp,*fpt;
	struct customer s1,s2;
	int flag=0,id;
	int sub;
	fp=fopen("customer.dat","r");
	fpt=fopen("temp.dat","w");
	if(fp==NULL)
	{
		printf("\nCouldnt open file.\n");
	}
	else
	{
		printf("\nEnter identification no: ");
		scanf("%d",&id);
		
		while(fread(&s1,sizeof(s1),1,fp))
		{
			if(id==s1.id)
			{
				printf("\nName:%s\nBalance:%d\n",s1.name,s1.balance);
				printf("Enter your withdrawing amount: ");
				scanf("%d",&sub);
				s2=s1;
				sub=s1.balance-sub;
				flag=1;
				break;
			}
		}
		rewind(fp);
		if(flag==0)
		{
			printf("\nAccount not found.\n");
		}
		else
		{
			while(fread(&s1,sizeof(s1),1,fp))
				{
					if(s1.id!=id)
					{
						fwrite(&s1,sizeof(s1),1,fpt);
					}
				}
			
			fclose(fp);
			fclose(fpt);
			
			fp=fopen("temp.dat","a+");
			s2.balance=sub;
			
			fwrite(&s2,sizeof(s2),1,fp);
			fclose(fp);
			fp=fopen("customer.dat","w");
			fpt=fopen("temp.dat","r");
			while(fread(&s1,sizeof(s1),1,fpt))
			{
				fwrite(&s1,sizeof(s1),1,fp);
			}
			printf("\nAmount withdrawn\nNew Balance:%d",s2.balance);
			fclose(fp);
			fclose(fpt);
		}
	}
}
void update()
{
	system("cls");
	FILE *fp,*fpt;
	struct customer s1,s2;
	int flag=0,id;
	fp=fopen("customer.dat","r");
	fpt=fopen("temp.dat","w");
	if(fp==NULL)
	{
		printf("\nCouldnt open file.\n");
	}
	else
	{
		printf("\nEnter identification no: ");
		scanf("%d",&id);
		
		while(fread(&s1,sizeof(s1),1,fp))
		{
			if(id==s1.id)
			{
				s2=s1;
				flag=1;
				break;
			}
		}
		rewind(fp);
		
		if(flag==0)
		{
			printf("\nAccount not found.\n");
		}
		else
		{
			while(fread(&s1,sizeof(s1),1,fp))
			{
				if(s1.id!=id)
				{
					fwrite(&s1,sizeof(s1),1,fpt);
				}
			}
			fclose(fp);
			fclose(fpt);
			
			fp=fopen("temp.dat","a");
			printf("Enter new address:");
			fflush(stdin);
			scanf(" %[^\n]",s2.address);
			
			do
			{
			printf("Enter new phone number:");
			fflush(stdin);
			scanf("%d",&s2.contact);
			}while(checkPhone(s2.contact)==0);
			
			fwrite(&s2,sizeof(s2),1,fp);
			fclose(fp);
			
			fp=fopen("customer.dat","w");
			fpt=fopen("temp.dat","r");
			
			while(fread(&s1,sizeof(s1),1,fpt))
			{
				fwrite(&s1,sizeof(s1),1,fp);
			}
			printf("\nOne record Updated.\n");
			fclose(fp);
			fclose(fpt);
		}
	}
}
void delete()
{
	system("cls");
	FILE *fp,*fpt;
	struct customer s1;
	int flag=0,id;
	fp=fopen("customer.dat","r");
	fpt=fopen("temp.dat","w");
	if(fp==NULL)
	{
		printf("\nCouldnt open file.\n");
	}
	else
	{
		printf("\nEnter identification no: ");
		scanf("%d",&id);
		
		while(fread(&s1,sizeof(s1),1,fp))
		{
			if(id==s1.id)
			{
				flag=1;
				break;
			}
		}
		rewind(fp);
		
		if(flag==0)
		{
			printf("\nAccount not found.\n");
		}
		else
		{
			while(fread(&s1,sizeof(s1),1,fp))
			{
				if(s1.id!=id)
				{
					fwrite(&s1,sizeof(s1),1,fpt);
				}
			}
			fclose(fp);
			fclose(fpt);
			fp=fopen("customer.dat","w");
			fpt=fopen("temp.dat","r");
			while(fread(&s1,sizeof(s1),1,fpt))
			{
				fwrite(&s1,sizeof(s1),1,fp);
			}
			printf("ACCOUNT DELETED.");
			fclose(fp);
			fclose(fpt);
		}
	}
}
int checkId(int id)
{
	FILE *fp;
	struct customer s1;
	int flag=1;
	fp=fopen("customer.dat","r");
	
	while(fread(&s1,sizeof(s1),1,fp))
	{
		if(s1.id==id)
		{
			printf("\nThe identification number is already in use.\n");
			flag=0;
		}
	}
	fclose(fp);
	return flag;
}
int checkPhone(int phone)
{
	FILE *fp;
	struct customer s1;
	int flag=1;
	fp=fopen("customer.dat","r");
	
	while(fread(&s1,sizeof(s1),1,fp))
	{
		if(s1.contact==phone)
		{
			printf("\nThe Phone number is already in use.\n");
			flag=0;
		}
	}
	fclose(fp);
	return flag;
}
