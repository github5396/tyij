#include<iostream>
#include<string.h>      //header files
#include<fstream>
#include<iomanip>
#include<conio.h>

using namespace std;

class Details   //defining class 
{
	char name[50];
	char email[50];
	char pwd[20];
	char num[10];
	
	public:
		bool getData();
		void show_Data();
		bool validation(char a[],char b[]);
		bool email_checker(char a[]);
		//char* return_pwd();
};

bool Details::email_checker(char a[])  //email checker
{
	if(strcmp(this->email,a)==0)
	{
		return 0;
	}
	return 1;
}

bool valid_data(char a[]) //email checking of each object
{
	ifstream fs;
	Details obj;
	fs.open("datab.dat",ios::in);
	bool flag = false;
	while(fs.read(reinterpret_cast<char *> (&obj),sizeof(Details)))
	{
		if(obj.email_checker(a))
		{
			flag = true;
			break;
		}
	}
	fs.close();
	if(flag) return 1;
	else return 0;
}

bool Details::getData()    //taking the details of user
{
	cout<<"\n\nFill the Sign Up Form";
	cin.ignore();
	cout<<"\nEnter Your Name : ";
	cin.getline(name,50);
	cout<<"\nEnter E-mail : ";
	cin>>email;
	if(valid_data(email))
	{
		char cp[20];
		int t=0;
		cout<<"\nEnter Password : ";
		cin>>pwd;
		cout<<"\nEnter Confirm Password : ";
		cin>>cp;
		
		while(strcmp(pwd,cp)!=0)
		{
			cout<<"\nRenter password : ";
			cin>>pwd;
			cout<<"\nRenter confirm password : ";
			cin>>cp;
		}
		
		cout<<"\nEnter Mobile Number : ";
		cin>>num;
		
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Details::validation(char a[],char b[])    //checking the login details valid or not
{
	if(strcmp(this->email,a)==0 && strcmp(this->pwd,b)==0)
	{
		return 1;
	}
	return 0;
}

void Details::show_Data()   //Displaying data for Admin use
{
	cout<<"\nYour Name : "<<name;
	cout<<"\n\nYour E-mail : "<<email;
	cout<<"\n\nYour Password : "<<pwd;
	cout<<"\n\nYour Number : "<<num;
}


void create_account();
bool login_account(char a[],char b[]);
void Display_account();

void user()   //user menu
{
	char ch;
	do
	{
		char ch;
		cout<<"\n1.Login";
		cout<<"\n2.Register";
		cout<<"\n3.Exit as User";
		cout<<"\nEnter your Choice : ";
		cin>>ch;
		switch(ch)
		{
			case '1':
				char email[50];
				char pswd[50];
				cout<<"\n\nEnter E-mail : ";
				cin>>email;
				cout<<"\n\nEnter Password : ";
				cin>>pswd;
				Details obj;
				if(login_account(email,pswd))
				{
					cout<<"\n\n\t\tWELCOME";
					cout<<"\n\nLOGIN Successful\n\n";
				}
				else
				{
					cout<<"\n\n====Login Failed====";
					cin.ignore();
					cin.get();
				}
				break;
			
			case '2':
				create_account();
				break;
				
			case '3':
				return;
				break;
		}
	}while(ch!='3');
}

void admin()  //admin login 
{
	char user[10] = "admin";
	char upwd[10] = "admin123";
	char eadmin[10],epwd[10];
	cout<<"\nEnter Admin Name :  ";
	cin>>eadmin;
	cout<<"\nEnter Admin password : ";
	cin>>epwd;
	if(strcmp(user,eadmin)==0 && strcmp(upwd,epwd)==0)
	{
		char ch;
		do
		{
			char ch;
			cout<<"\n1.Display data";
			cout<<"\n2.Exit as Admin";
			cin>>ch;
			switch(ch){
				
				case '1':
					Display_account();
					break;
				case '2':
					return;
					break;
			}
		}while(ch!=2);
	}
	else
	{
		cout<<"\n\n\t\tInvalid Credentials\n\n";
		//admin();
	}
}


int main()   //main menu
{
	char ch;
	do
	{
		char ch;
		cout<<"\n1.User";
		cout<<"\n2.Admin";
		cout<<"\n3.exit";
		cout<<"\nEnter your choice : ";
		cin>>ch;
		
		switch(ch){
			
			case '1':
				user();
				break;
				
			case '2':
				admin();
				break;
			
			case '3':
				exit(0);
				break;
				
		}
	}while(ch!='3');
}

void create_account()  //creating new account and storing it in files
{
	ofstream fs;
	Details obj1;
	fs.open("datab.dat",ios::binary|ios::app);
	bool ch = obj1.getData();
	if(ch)
	{
		fs.write(reinterpret_cast<char *> (&obj1),sizeof(Details));
		fs.close();
		cout<<"\n\n====Account Created Successfully";
	}
	else
	{
		cout<<"\n\nAccount already exist with the given email";
	}
	cin.ignore();
	cin.get();
}
void Display_account()  displaying all the data from files
{
	ifstream fs;
	Details obj1;
	fs.open("datab.dat",ios::in);
	if(!fs)
	{
		cout<<"\n\n\t\tFile Not Fount";
		cin.ignore();
		cin.get();
		return;
	}
	
	while(fs.read(reinterpret_cast<char *> (&obj1),sizeof(Details)))
	{
		obj1.show_Data();
		cout<<"\n\n=================================\n"; 
	}
	fs.close();
	cin.ignore();
	cin.get();
}
bool login_account(char a[],char b[])    //validation for login credentilas
{
	Details obj1;
	ifstream fs;
	fs.open("datab.dat",ios::in);
	bool flag = false;
	while(fs.read(reinterpret_cast<char *> (&obj1),sizeof(Details)))
	{
		if(obj1.validation(a,b))
		{
			flag = true;
			break;
		}
	}
	fs.close();
	if(flag) return 1;
	else return 0;
	cin.ignore();
	cin.get();
}
