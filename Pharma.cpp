#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include<stdlib.h>
using namespace std;
 
class Medicine//base
{
	
	public:
	int num;
	char name[60];
	float pp, qnty, disc;
	
 
	void addmed()//medicines added to list
	{
		cout<<"\n\n\n\t\tHello Seller, fill in the below details to Add the medicine into the store\n"<<endl;
		cout<<"\n\n\tEnter Product Number:\t";
		cin>>num;
		cout<<"\n\tEnter Product Name:\t";
		cin>>name;
		cout<<"\n\tEnter Product Price:\t";
		cin>>pp;
		cout<<"\n\tEnter Discount (%):\t";
		cin>>disc;
	}
	
	void putupmed()//display list
	{
		cout<<"\n\n\tProduct Number:\t"<<num;
		cout<<"\n\tProduct Name:\t"<<name;
		cout<<"\n\tProduct Price:\t"<<pp;
		cout<<"\n\tDiscount:\t %"<<disc;
	}
	
	int prod()//used for files
	{
		return num;
	}
	
	float price()
	{
		return pp;
	}
	
	char* prodnme()
	{
		return name;
	}
	
	float discountp()
	{
		return disc;
	}
 
};
fstream file;//file object
Medicine med;//class object

 
class User : public Medicine
{
	
 public:
 	float tot=0;
	char custnm[30];
	int age, ph;
	
			void giveinfo()//patient details
		{
			cout<<"\n\n\tEnter Patient's Name:\t"<<endl;
			cin>>custnm;
			cout<<"\n\tEnter Age:\t"<<endl;
			cin>>age;
			cout<<"\n\tEnter Phone number:\t"<<endl;
			cin>>ph;
		}
		
		void dispinfo()//details putup
		{
			cout<<"\n\n\tName : "<<custnm<<endl;
			cout<<"\n\tAge : "<<age<<endl;
			cout<<"\n\tPhone No. : "<<ph<<endl;
		}
 	
 	void filesave()
{
	file.open("medicine.dat",ios::out|ios::app);
	med.addmed();
	file.write((char*)&med,sizeof(Medicine));
	file.close();
	cout<<"\n\n\t\tProduct Created !!!";
	getchar();
}
 
void display()//files list
{
	system("cls");
	cout<<"\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **"<<endl;
	cout<<"\n\t\t\tMEDICINE LIST";
	cout<<"\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **"<<endl;
	file.open("medicine.dat",ios::in);
	while(file.read((char*)&med,sizeof(Medicine)))
	{
		med.putupmed();
		cout<<"\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **"<<endl;
		getchar();
	}
	file.close();
}

void medicinedisp()
{
	system("cls");
	file.open("medicine.dat",ios::in); 
	cout<<"\n\n\tMedicines\n";
	cout<<"\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **"<<endl;
	cout<<"\n\t\tNO.\t\t\tNAME\t\t\tPRICE\n";
	cout<<"\n  ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **"<<endl;
	while(file.read((char*)&med,sizeof(Medicine)))
	{
		cout<<"\t\t"<<med.prod()<<"\t\t"<<med.prodnme()<<"\t\t\t"<<med.price()<<endl;
	}
	file.close();
}

void plcord()//placeorder
{
		User::medicinedisp();
	int ord[50], qn[50], i=0;
	float at, dt;
	char ch;

	cout<<"\n\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **"<<endl;
	cout<<"\n\n\t\tPlace Order"<<endl;
	cout<<"\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **"<<endl;
	do
	{
		cout<<"\n\n\t\t\tEnter Product Number : \n\t\t"<<endl;
		cin>>ord[i];
		cout<<"\n\t\t\tQuantity:\t"<<endl;
		cin>>qn[i];
		i++;
		cout<<"\n  Enter 'Y' To Continue Buying"<<endl;
		cout<<"\n  Enter 'N' To Proceed to Billing"<<endl;
		cin>>ch;
		}while(ch=='y' ||ch=='Y');
	getchar();
	system("cls");
	giveinfo();
	dispinfo();
	cout<<"\n\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** BILL ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **\n";
	cout<<"\n\t\t\tNo.\tName\tQuantity\tPrice\tAmount\tDiscounted Price\n"<<endl;
	for(int x=0;x<=i;x++)
	{
		file.open("medicine.dat",ios::in);
		file.read((char*)&med,sizeof(Medicine));
		while(!file.eof())
		{	
			if(med.prod()==ord[x])
			{
				at=med.price()*qn[x];
				dt=at-(at*med.discountp()/100);
				cout<<"\n\t\t\t"<<ord[x]<<"\t"<<med.prodnme()<<"\t"<<qn[x]<<"\t"<<med.price()<<"\t"<<at<<"\t\t"<<dt;
				tot+=dt;
			}
			file.read((char*)&med,sizeof(Medicine));
		}
		file.close();
	}
	cout<<"\n\n\t\t\t\t\tTOTAL = "<<tot;
	payment();
	getchar();
}
void payment()
{
	int pay,z;
	char loc[30];
	
	 cout<<"\n\n\t\t\tCHOOSE MODE OF PAYMENT\n";
	 cout<<"\n\t\t\t1) Cash \n\t\t\t2) Card\n"; 
     cin>>pay;
	 cout<<"\n\t\t\tEnter Address For Delivery\n";
	 cin>>loc;
	 cout<<"\n\n\n\t\t\t\t\tORDER SUMMARY:\n";
	 cout<<"\n\n\t\tTOTAL BILL: "<<tot<<endl;  
     cout<<"\n\t\t\tMODE OF PAYMENT: \t";
        if(pay==1)
        {
        cout<<"\n\t\tCASH";
        }
        else
		{
        cout<<"\n\t\tCARD";
    	}
        cout<<"\n\t\tADDRESS :\t"; 
        cout<<loc<<endl;
        cout<<"\n\t\tHit 1 to COMFIRM\n"; 
		cin>>z;
        if(z==1)
        {
        cout<<"\n\t\t\t\t\tYour Order is PLACED !!\n";
        cout<<"\n\n\t\t\tWill reach to you soon"<<endl;
        }else 
      {
        cout<<"\n\t\t\t\t\tOrder Cancelled\n";
      }
        return;
}
};
 
 class Seller:public Medicine,public User
 {
 	public:
 	void modifymed()//modify medicine details
{
	int no;
	bool fnd=false;
	system("cls");
	cout<<"\n\n\t\t\tTo MODIFY the details, Enter";
	cout<<"\n\t\t\tProduct Number:\t";
	cin>>no;
	
	file.open("medicine.dat",ios::in|ios::out);
	while(file.read((char*)&med,sizeof(Medicine)) && fnd==false)
	{
		if(med.prod()==no)
		{
			med.putupmed();
			cout<<"\n\n\t\t\tEnter NEW Details : \t"<<endl;
			med.addmed();
			int pos=-1*sizeof(med);
			file.seekp(pos,ios::cur);
			file.write((char*)&med,sizeof(Medicine));
			cout<<"\n\n\t\t\t\tMedicine Details Modified !!!";
			fnd=true;
		}
	}
	file.close();
	if(fnd==false)
		cout<<"\n\n\t\t\tMedicine Not PRESENT !!!";
	getchar();
}
 
void remmed()//remove medicine details
{
	int no;
	system("cls");
	cout<<"\n\n\t\t\tTo REMOVE a medicine from the store, Enter";
	cout<<"\n\n\t\t\tProduct Number:\t";
	cin>>no;
	file.open("medicine.dat",ios::in|ios::out);
	fstream file1;
	file1.open("med.dat",ios::app);
	file.seekg(0,ios::beg);
	while(file.read((char*)&med,sizeof(Medicine)))
	{
		if(med.prod()!=no)
		{
			file1.write((char*)&med,sizeof(Medicine));
		}
	}
	file1.close();
	file.close();
	remove("medicine.dat");
	rename("med.dat","medicine.dat");
	cout<<"\n\n\t\t\t\tMedicine Details REMOVED !!!";
	getchar();
}
 	
void sellrchoice()
{
	system("cls");
	int chh;
	cout<<"\n\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **\n";
	cout<<"\n\t\t\tWelcome Seller";
	cout<<"\n\t\tCHOOSE";
	cout<<"\n\t\t1) Add Medicines to the store";
	cout<<"\n\t\t2) Display the Store's Medicine List ";
	cout<<"\n\t\t3) Modify Medicine List";
	cout<<"\n\t\t4) Delete Medicine from the list";
	cout<<"\n\t\t5) Exit !";
	cout<<"\n\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **\n";;
	cout<<"\n\n\tYou Choice : \t";
	cin>>chh;
	switch(chh)
	{
		case 1: system("cls");
				User::filesave();
				break;
				
		case 2: User::display();
				break;
				
		case 3: Seller::modifymed();
		break;
		
		case 4: Seller::remmed();
		        break;
				
		case 5: system("cls");
				break;
		
		default:sellrchoice();
	}
}
};
 
int main()
{
	system("cls");
	int chh;
	User us;
	Seller se;
	for(;;)//to run uptil number of iterations without any condition
	{
 
		cout<<"\n\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **\n";
		cout<<"\n\t\t\t\t\tWelcome To The Pharmacy";
		cout<<"\n\t\tChoose :";
		cout<<"\n\t\t1)USER Operations";
		cout<<"\n\t\t2)SELLER Opearations";
		cout<<"\n\t\t3)EXIT !!!\n";
		cout<<"\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **\n";
		cout<<"\n\tYour Choice : \t";
		cin>>chh;
		
		switch(chh)
		{
			case 1: system("cls");
					us.plcord();
					getchar();
					break;
					
			case 2: se.sellrchoice();
					break;
					
			case 3: 
					cout<<"\n\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **\n";
					cout<<"\n\n\t\t\t\t\tAll the medicines bought will remain best before 36months of mgf date";
					cout<<"\n\n\t\t\t\t\t\tMgf date : Dec 2020"<<endl;
					cout<<"\n\n\t\t\t\t\t\I WISH YOU GET WELL SOON !!";
					cout<<"\n\n\t\t\t\t\t\t\tTHANK YOU FOR VISITING !!!";
					cout<<"\n** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **\n";
					exit(0);
			
			default :cout<<"Invalid Input...Choose from above !!!\n";
		}
	}
	return 0;
}
