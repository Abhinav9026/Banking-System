//Headers Files
#include<iostream>  //provides basic output & input 
#include<fstream>  //for reading and writing from/to files
#include<cctype>  //for transforming individual character
#include<iomanip>  // for manipulating(Controlling) the output

using namespace std;

//Creating class 
class account{
    int acc_num;  
    char name[100];
    int deposit;
    char type;
    
    public:
        void create_account();  //function for get data from user
        void show_account() const; //function to show data on screen
        void modify(); //function to add new data
        void deposit_money(int); //function to add money and add balance to current ammount
        void withdraw(int); //function to withdraw money and subtract balance from current amount
        void report() const; //function to show data on tabular form
        int return_acc_num() const; //function to return account number
        int ret_depost() const; //function to return balance amount
        char re_type() const; //function to return the type of account
};

void account ::create_account(){
    cout << "\n Enter the account number : ";
    cin >> acc_num;
    cout << "\n\n Enter the name of the Account Holder ";
    cin.ignore();
    cin.getline(name, 100);
    cout << "\n\n Enter the type of the Account (C/S) : ";
    cin >> type;
    type = toupper(type);  //for converting in upper case letter
    cout << "Enter the Initial amount (>=1000 for Current(C) & >=500 for Saving(S) ) : ";
    cin >> deposit;
    cout << " \n\n Congrats...Account Successfully Created";
}

void account ::show_account() const {
    cout << "\nAccount Number : " << acc_num;
    cout << "\nAccount Holder Name : " << name;
    cout << "\nAccount Type : " << type;
    cout << "\nBalance Amoount : " << deposit;
}

void account ::modify(){
    cout << "\nAccount Number : " << acc_num;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance : ";
    cin >> deposit;
}

void account ::deposit_money(int x){
    deposit += x;
}

void account ::withdraw(int x) {
    deposit -= x;
}

void account ::report() const{
    cout << acc_num << setw(6) << " " << name << setw(6) << " " << type << setw(6) << deposit << endl;
}

int account ::return_acc_num() const {
    return acc_num;
}

int account ::ret_depost() const {
    return deposit;
}

char account ::re_type() const {
    return type;
}

//Declaring Functions
void write_accunt(); //function to write record in binary file
void display_sp(int); //function to display account details given by user
void modify_accunt(int); //function to modify record of file
void dlt_accunt(int);  //function to delete record of file
void displayAll();   //function to display all account details
void deposit_withdraw(int, int);  //function to deposit & withdrawing money from account

int main(){
    char ch;
    int account_num;

    cout << "\n\t BANK MANAGEMENT SYSTEM";

    do{
        system("cls");
        cout << " \n\tMain Menu : ";
        cout << " \n\t01 New Account ";
        cout << " \n\t02 Deposit Money ";
        cout << " \n\t03 Withdraw Money ";
        cout << " \n\t04 Balance Enquiry ";
        cout << " \n\t05 All Account Holder List";
        cout << " \n\t06 Close An Account";
        cout << " \n\t07 Modify An Account";
        cout << " \n\t08 Close";
        cout << " \n\n\n Choose Your Option(1-8)";
        cin >> ch;
        system("cls");   //clearing a screen
        switch (ch)
        {
        case '1':
            write_accunt();
            break;
        
        case '2':
            cout << "\n\n\t Enter the account number : ";
            cin >> account_num;
            deposit_withdraw(account_num, 1);
            break;
        
        case '3':
            cout << "\n\n\t Enter the account number : ";
            cin >> account_num;
            deposit_withdraw(account_num, 2);
            break;
        case '4':
            cout << "\n\n\t Enter the account number : ";
            cin >> account_num;
            display_sp(account_num);
            break;

        case '5':
            displayAll();
            break;

        case '6':
            cout<<"\n\n\tEnter The account No. : "; 
            cin>>account_num;
            dlt_accunt(account_num);
            break;

        case '7':
            cout<<"\n\n\tEnter The account No. : "; 
            cin>>account_num;
            modify_accunt(account_num);
            break;

        case '8':
            cout<<"\n\n\tThanks for using bank managemnt system";
			break;

        default:
            cout << " ";
            break;
        }
        cin.ignore(); //gnore or clear one or more characters from the input
        cin.get(); //reads characters from stdin and stores them until new line character found.

    } while (ch != '8');

    return 0;
}

//function to write in file
void write_accunt(){
    account ac;     //object of class
    ofstream outFile;   //ofstream to create file and write in that
    outFile.open("account.dat", ios::binary | ios::app);  //ios::binary-open in binary mode 
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

//function to display specific record from file
void display_sp(int n){
    account ac;
    bool flag = false;
    ifstream inFile;      //ifstream is use for reading input from file
    inFile.open("account.dat", ios::binary);
    if(!inFile){
        cout << "File could not open !! Press any key...";
        return;
    }
    cout << "\nBalance Details\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))) // used to convert a pointer of some data type into a pointer of another data type
    {
        if(ac.return_acc_num() == n){
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if(flag == false){
        cout << "\n\nAccount number does not exist";
    }
}

//function for modifying account
void modify_accunt(int n){
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if(!File){
        cout << "File could not be open !! Press any key...";
        return;
    }
    while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.return_acc_num()==n){
            ac.show_account();
            cout << "\nEnter the new details of accouny" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\nRecord updated";
            found = true;
        }
    }
    File.close();
    if(found==false){
        cout << "Record not found";
    }
}

//function for deleting account from file
void dlt_accunt(int n){
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))) {
        if(ac.return_acc_num() !=n){
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//functions for displaying all accounts
void displayAll() {
    account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();

}

//function for depositing & withdrawing amount from account
void deposit_withdraw(int n, int option) {
    int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false){
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.return_acc_num() == n){
            ac.show_account();
            if(option==1){
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
                ac.deposit_money(amt);
            }
            if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
                int bal = ac.ret_depost() - amt;
                if((bal<500 && ac.re_type() == 'S') || (bal<1000 && ac.re_type() == 'C')){
                    cout << "Insufficient Balance";
                }
                else{
                    ac.withdraw(amt);
                }
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\n\n Record Not Found ";
    }
}
