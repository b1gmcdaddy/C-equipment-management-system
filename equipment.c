#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

typedef struct{
  char name[50];
  char secondName[50];
  char role[6];
  char password[50];
  char email[50];
  char status[50];
  int id;
} Users;

typedef struct {
  int id; 
  char name[50];
  char status[50];
  int quantity;
  char availability[50];
} Equipments;

typedef struct{
	int id;
	int quantity;
	char uName[50];	
	char eName[50];	
	char status[50];	
	char availability[50];	
}Borrowed;

typedef struct{
	int id;
	int quantity;
	char uName[50];	
	char eName[50];	
	char status[50];	
	char availability[50];	
}Returned;
//arrays used to store the values for the structs
Borrowed borrowed[100];
Returned returned[100];
Equipments equip[100];
Users users[100];
int records=0;
int erecords=0;
int brecords=0;
int rrecords=0;
int n;
char currentUser[50];

void addNewEquipment();
void head();
void showBorrowed();
void saveBorrowedData();
void saveReturnedData();
void editEquipment();
void login();
void approveReturned();
void deleteEquipment(char eName[50]);
void changeUserInfo(char role[6]);
void showRetruned();
void showEquipments();
int adminMenu();
void addNewStaff();
void returnBorrowed();
void saveEquipmentsData();
int staffMenu();
int accountManagement();
int readEquipments();
int manageStaff();
int userMenu();
void approveBorrowed();
void addBorrowed();
int readReturned();
int readBorrowed();
void changePassword(char password[10]);
void showUsers();
int readFile();
int firstPage();

//MAIN FUNCTION
int main(){
	char op;
	while(1){
	readFile();
	readEquipments();
	readBorrowed();
	readReturned();

    head();

	op=firstPage();
	if(op=='y' || op=='Y'){
		login();
		break;
	}
	else if(op=='n' || op=='N'){
		addNewStaff("OUser");	
		break;
	}
	else{
		system("cls");
	}
	}
    return 0;
}

//banner
void head() { 
	system("cls");
	system("COLOR 0B");
    printf("\n\t\t\t#############################################################################");
	printf("\n\t\t\t####################    TANGPUZ EQUIPMENT SYSTEM      #######################");
	printf("\n\t\t\t#############################################################################\n\n");
	
}
//first screen
int firstPage(){
	printf("Do you have an account?\nY-Yes\nN-No\nEnter an option: ");
	char opt;
	scanf("%c",&opt);
	return opt;
}

//Main menu for administrator
int adminMenu(){
		int ch=0;
		head();
		printf("ADMINISTRATOR MAIN MENU");
		printf("\n1-Manage All Accounts\n");
		printf("2-Manage All Equipments\n");
		printf("3.Change Password\n");
		printf("0.END PROGRAM\n");
		printf("Choose what to do next => ");
		scanf("%d",&ch);
		return ch;
}
//Main Menu for staff
int staffMenu(){
		int ch=0;
		head();
		printf("STAFFS MAIN MENU");
		printf("\n1-All requests for borrowing\n");
		printf("2-All requests to return\n");
		printf("3-Change Password\n");
		printf("0-Exit\n");
		printf("\nChoose what to do next => ");
		scanf("%d",&ch);
		return ch;
}
//Main menu for OrdinaryUser
int userMenu(){
		head();
		int ch=0;
		head();
		printf("ORDINARYUSERS MAIN MENU");
		printf("\n1-Borrow Equipment\n");
		printf("2-Return Equipment\n");
		printf("3-Change Password\n");
		printf("Choose what to do next => ");
		scanf("%d",&ch);
		return ch;
}
//Administrator > Manage Equipments
int manageEquipment(){
	head();
	printf("\n21 List all Equipments\n");
	printf("22 Add New Equipment\n");
	printf("23 Edit Equipment\n");
	printf("24 Delete Equipment\n");
	printf("25 Go back level 1 up\n");
	printf("Choose what to do next: ");
	int op;
	scanf("%d",&op);
	return op;
}
//Administrator > Manage Accounts > Manage OUser
int manageOUser(){
	head();
	printf("\n121 List all OUser\n");
	printf("122 Edit OUser details\n");
	printf("123 Go back level 1 up\n");
	printf("Choose what to do next: ");
	int op;
	scanf("%d",&op);
	return op;
}
//Administrator > Manage Accounts > Manage Staff
int manageStaff(){
	head();
	printf("\n111 List all Staff\n");
	printf("112 Add new staff\n");
	printf("113 Edit staf details\n");
	printf("114 Go back level 1 up\n");
	printf("Choose what to do next: ");
	int op;
	scanf("%d",&op);
	return op;
}
//Registration for OrdinaryUsers
void addNewStaff(char ouser[100]){
	head();
	char fname[50],lname[50],email[50],password[50],rpassword[50],OUser[50];
	printf("\nRegister as an OrdinaryUser\n");
	printf("\nEnter First Name: ");
	scanf("%s",&fname);
	printf("Enter Last Name: ");
	scanf("%s",&lname);
	printf("Enter Email: ");
	scanf("%s",&email);
	printf("Enter password: ");
	scanf("%s",&password);
	printf("Re Enter password: ");
	scanf("%s",&rpassword);
	printf("\nWelcome: %s",fname);
	char status[50];
	strcpy(status,"Enable");  //default status of Ouser is enable
	if(strcmp(password,rpassword)==0){
		strcpy(OUser,ouser);
		FILE *fptr;
		fptr = fopen("users.txt","a+");
		fprintf(fptr,"\n%d,%s,%s,%s,%s,%s,%s",records+1,fname,lname,OUser,password,email,status);
		fclose(fptr);
		records++;
	}
	else{
		printf("Sorry password did not match");
	}
	getch();
}
//Administrator > Manage Equipments > Add Equipment
void addNewEquipment(){
	head();
	int equantity;
	char ename[50],estatus[50],eavailability[50];
	printf("\nEnter Equipment Name: ");
	scanf("%s",&ename);
	printf("Enter Equipment Status: ");
	scanf("%s",&estatus);
	printf("Enter Equipment Quantity: ");
	scanf("%d",&equantity);
	printf("Enter Equipment Availability: ");
	scanf("%s",&eavailability);
	printf("\nEquipment Added Successfully:");
		FILE *fptr;
		fptr = fopen("equipments.txt","a+");
		fprintf(fptr,"\n%d,%s,%s,%d,%s", erecords+1,ename,estatus,equantity,eavailability);
		fclose(fptr);
		erecords++;
}
//Staff > Approve Borrow Requests
void approveBorrowed(){
	printf("Enter the id of the equipment to approve: ");
	int id;
	scanf("%d",&id);
	for(int i=0;brecords;i++){
		if(id==borrowed[i].id)
		{
			char d[20];
			printf("Enter Y to approve or N to disapprove: ");
			scanf("%s",&d);
			if(strcmp(d,"Y")==0){
				printf("The product is approved for borrowing.");
				strcpy(borrowed[i].status,"Borrowed");
			}
			else{
				printf("The product borrow approval denied");
				strcpy(borrowed[i].status,"DeniedBorrow");
			}
			break;
		}
	}
	saveBorrowedData();
	getch();
}
//Staff > Approve Return Requests
void approveReturned(){
	printf("Enter the id of the equipment to approve: ");
	int id;
	scanf("%d",&id);
	for(int i=0;rrecords;i++){
		char d[20];
		if(id==returned[i].id)
		{
			printf("Enter Y to approve or N to disapprove: ");
			scanf("%s",&d);
			if(strcmp(d,"Y")==0){
				printf("The product has been returned successfully.");
				strcpy(returned[i].status,"Returned");
			}
			else{
				printf("The product return has been denied");
				strcpy(returned[i].status,"DeniedReturn");
			}
			break;
		}
	}
	saveReturnedData();
	getch();
}
//OUser > borrow equipment
void addBorrowed(){
	int iid,equantity,choice;
	printf("\nEnter ID to borrow: ");
	scanf("%d",&iid);
	FILE *fptr;
	fptr = fopen("borrowed.txt","a+");
	char ename[50],estatus[50],eavailability[50];
	for(int i=0;i<erecords;i++){
		if(iid==equip[i].id){
			strcpy(ename,equip[i].name);			
			strcpy(estatus,"Unapproved");	//default status is unapproved		
			strcpy(eavailability,equip[i].availability);			
			equantity=equip[i].quantity;			
			fprintf(fptr,"\n%d,%s,%s,%s,%d,%s",brecords+1,currentUser,ename,estatus,equantity,eavailability);
			printf("You would like to borrow a %s.", ename);
			printf("\nPlease wait for the staff to approve your application to borrow.");
			printf("\nYou can pick it up when approved.\n");
	
		}
	}
	brecords++;
	fclose(fptr);
}

//Administrator > Manage Accounts
int accountManagement(){
	head();
	printf("\n11 Manage Staff\n");
	printf("12 Manage Ordinary User\n");
	printf("13 Go back 1 level up\n");
	printf("Choose what to do next => ");
	int op;
	scanf("%d",&op);
	return op;
}
//writes to equipments.txt
void saveEquipmentsData(){	
	FILE *fptr;
	fptr = fopen("equipments.txt","w");
	for(int i=0;i<erecords;i++){
		if(equip[i].quantity)
		{
			fprintf(fptr,"\n%d,%s,%s,%d,%s",i+1,equip[i].name,equip[i].status,equip[i].quantity,equip[i].availability);
		}
	}	
	fclose(fptr);
}
//writes to users.txt
void saveUsersData()
{	
	FILE *fptr;
	fptr = fopen("users.txt","w");
	for(int i=0;i<records;i++){
		fprintf(fptr,"%d,%s,%s,%s,%s,%s,%s\n",i+1,users[i].name,users[i].secondName,users[i].role,users[i].password,users[i].email,users[i].status);
	}	
	fclose(fptr);
}
//writes to borrowed.txt
void saveBorrowedData()
{	
	FILE *fptr;
	fptr = fopen("borrowed.txt","w");
	for(int i=0;i<brecords;i++)
	{
		fprintf(fptr,"%d,%s,%s,%s,%d,%s\n",i+1,borrowed[i].uName,borrowed[i].eName,borrowed[i].status,borrowed[i].quantity,borrowed[i].availability);
	}	
	fclose(fptr);
}
//writes to returned.txt
void saveReturnedData()
{	
	FILE *fptr;
	fptr = fopen("returned.txt","w");
	for(int i=0;i<rrecords;i++)
	{
		fprintf(fptr,"%d,%s,%s,%s,%d,%s\n",i+1,returned[i].uName,returned[i].eName,returned[i].status,returned[i].quantity,returned[i].availability);
	}	
	fclose(fptr);
}
//Admin change OUser info
void changeUserInfo(char role[6]){	
	int id;
	char fname[50],lname[50],email[50];
	printf("Enter the user id to change info: ");
	scanf("%d",&id);
	
	int check=0;
	for(int i=0;i<records;i++)
	{
		if((users[i].id==id) &&(strcmp(users[i].role,role)==0))
		{
			printf("Enter new first name: ");
			scanf("%s",&fname);
			printf("Enter new last name: ");
			scanf("%s",&lname);
			printf("Enter new email: ");
			scanf("%s",&email);
			strcpy(users[i].name,fname);
			strcpy(users[i].secondName,lname);
			strcpy(users[i].email,email);
			printf("\nUser info changed successfully!");
			check=1;
			getch();
		}
	}	
	if(check==0){
		printf("User not found");
	}
	else{
		saveUsersData();
	}
	getch();
}

//Login screen
void login(){
	char uName[50],uPassword[50];
	head();
	printf("Login\n");
	printf("Enter your name: ");
	scanf("%s",&uName);
	printf("Enter your password: ");
	scanf("%s",&uPassword);
	for(int i=0;i<records;i++){
		if((strcmp(users[i].name,uName)==0) && (strcmp(users[i].password,uPassword)==0)){
			strcpy(currentUser,uName);
			if(strcmp(users[i].role,"admin")==0){    //activates admin main menu
				int opt=adminMenu();
				if(opt==1){

					int sop=accountManagement();
					if(sop==11){
						int ssop=manageStaff();
						if(ssop==111){
							
							showUsers("staff");    //input 111 to show staff users
					
						}
						else if(ssop==112){
							addNewStaff("staff");    //input 112 to add new staff
						}
						else if(ssop==113){
							showUsers("staff");        //input 113 to edit staff info
							changeUserInfo("staff");
						}
					}
					else if(sop==12){
						int ssop=manageOUser();
						if(ssop==121){
							showUsers("OUser");    //input 121 to display ordinary users
						}
						else if(ssop==122){
							showUsers("OUser");
							changeUserInfo("OUser");   //input 122 to edit ordinaryusers info
						}
					}
					else if(sop==13){
						adminMenu();
					}
				}
				else if(opt==2){
				
					int sop=manageEquipment();
					if(sop==21){
						showEquipments();      //display equipment list
					}
					else if(sop==22){
						addNewEquipment();    
					}
					else if(sop==23){
						editEquipment();
					}
					else if(sop==24){      //input 24 to delete equipment
						system("cls");
						head();
						showEquipments();
						printf("Enter the name of the equipment to be deleted: ");
						char na[50];
						scanf("%s",&na);
						deleteEquipment(na);
					}
				}
				else if(opt==3){      //change ADMIN password
					system("cls");
					head();
					printf("Enter your current password: ");
					char p[50];
					scanf("%s",&p);
					changePassword(p);

				}
				else if(opt==0){
					system("cls");
					exit(0);
				}
				else{
					printf("Wrong Input press any key to retry");
					getch();
				}
				
			}
			else if(strcmp(users[i].role,"staff")==0){    //activates staff main menu
				int opt=staffMenu();
				if(opt==1){
					showBorrowed();
					approveBorrowed();      
				}
				else if(opt==2){
					showRetruned();	
					approveReturned();
				}
				else if(opt==3){      //change STAFF user's password
					system("cls");
					head();
					printf("Enter your current password: ");
					char p[50];
					scanf("%s",&p);
					changePassword(p);
					changePassword("staff");
				}
			}
			else if(strcmp(users[i].role,"OUser")==0){    //activates OrdinaryUser main menu
				int opt=userMenu();
				if(opt==1){
					showEquipments();
					addBorrowed();
				}
				else if(opt==2){
					printf("List of all approved Borrowed Equipments");
					showBorrowed();
					returnBorrowed();
				}else if(opt==3){          //change OUser's password
					system("cls");
					head();
					printf("Enter your current password: ");
					char p[50];
					scanf("%s",&p);
					changePassword(p);
					changePassword("OUser");
				}
			}
			else{
				printf("Nothing found");
				getch();
			}
		}
	}
}
//reads users.txt
int readFile(){
  FILE *file;
  file = fopen("users.txt", "r"); 
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }
  int read = 0;
  do {
    read = fscanf(file,
                  "%d,%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]\n",
                  &users[records].id, 
                  users[records].name, 
                  users[records].secondName, 
                  users[records].role, 
                  users[records].password,
                  users[records].email,
                  users[records].status); 
    if (read == 7) records++;
    if (read != 7 && !feof(file)){
      printf("File format incorrect.\n");
      return 1;
    }
    if (ferror(file))
    {
      printf("Error reading file.\n");
      return 1;
    }
  } while (!feof(file));
  fclose(file);
}

//reads borrowed.txt
int readBorrowed(){
  FILE *file;
  file = fopen("borrowed.txt", "r"); 
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }
  int read = 0;
  do 
  {
    read = fscanf(file,
                  "%d,%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                  &borrowed[brecords].id, 
                  borrowed[brecords].uName, 
                  borrowed[brecords].eName, 
                  borrowed[brecords].status, 
                  &borrowed[brecords].quantity,
                  borrowed[brecords].availability); 
    if (read == 6) brecords++;
    if (read != 6 && !feof(file)){
      printf("File format incorrect.\n");
      return 1;
    }
    if (ferror(file)){
      printf("Error reading file.\n");
      return 1;
    }
  } while (!feof(file));
  fclose(file);
}

//reads returned.txt
int readReturned(){
  FILE *file;
  file = fopen("returned.txt", "r"); 
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }
  int read = 0;
  do 
  {
    read = fscanf(file,
                  "%d,%49[^,],%49[^,],%49[^,],%d,%49[^\n]\n",
                  &returned[rrecords].id,  
                  returned[rrecords].uName, 
                  returned[rrecords].eName, 
                  returned[rrecords].status, 
                  &returned[rrecords].quantity,
                  returned[rrecords].availability); 
    if (read == 6) rrecords++;
    if (read != 6 && !feof(file))
    {
      printf("File format incorrect.\n");
      return 1;
    }
    if (ferror(file))
    {
      printf("Error reading file.\n");
      return 1;
    }
  } while (!feof(file));
  fclose(file);
}

//reads equipments.txt
int readEquipments(){
  FILE *file;
  file = fopen("equipments.txt", "r"); 
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }
  int read = 0;
  do 
  {
    read = fscanf(file,
                  "%d,%49[^,],%49[^,],%d,%49[^\n]\n",
				  &equip[erecords].id,
                  equip[erecords].name, 
                  equip[erecords].status, 
                  &equip[erecords].quantity, 
                  equip[erecords].availability);
    if (read == 5) erecords++;
    if (read != 5 && !feof(file)){
      printf("File format incorrect.\n");
      return 1;
    }
    if (ferror(file)){
      printf("Error reading file.\n");
      return 1;
    }
  } while (!feof(file));
  fclose(file);
}
//Admin > Manage Accounts > List all Ousers
void showUsers(char userRole[50]){
	
	system("cls");
	printf("ID\tFName\tLName\tRole\tPassword\tEmail\t\tStatus\n");
		for (int i = 0; i < records; i++){
			if(strcmp(userRole,users[i].role)==0){
			printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n",  
				users[i].id,
				users[i].name,
				users[i].secondName,
				users[i].role,
				users[i].password,
				users[i].email,
				users[i].status);
			}
		}
		printf("\n");
		getch();
}
//Admin delete equipment
void deleteEquipment(char eName[50])
{
	system("cls");
	head();
	int check=0;
	for(int i=0;i<erecords;i++){
		if(strcmp(equip[i].name,eName)==0){
			strcpy(equip[i].name,"");
			strcpy(equip[i].status,"");
			equip[i].quantity=0;
			strcpy(equip[i].availability,"");
			check=1;
		}
	}
	if(check==0){
		printf("\nItem not found\n");
	}
	else{
		printf("\nItem deleted successfuly\n\n");
		saveEquipmentsData();
	}
	getch();
}

//Admin List all equipments
void showEquipments(){
	head();
	printf("ID\tEqpName\tStatus\tQuantity\tAvailability\n");
		for (int i = 0; i < erecords; i++){
			printf("%d\t%s\t%s\t%d\t\t%s\n",  
				equip[i].id,
				equip[i].name,
				equip[i].status,
				equip[i].quantity,
				equip[i].availability);
		}
		printf("\n");
		getch();
		
}
// display borrowed list
void showBorrowed(){
	head();
	printf("ID\tUserName\tEqpName\tStatus\t\tQuantity\tAvailability\n");
		for (int i = 0; i < brecords; i++){
		
			printf("%d\t%s\t\t%s\t%s\t%d\t\t%s\n",  
				borrowed[i].id,
				borrowed[i].uName,
				borrowed[i].eName,
				borrowed[i].status,
				borrowed[i].quantity,
				borrowed[i].availability);
		}
		printf("\n");
		getch();
}
//display returned list
void showRetruned(){
	head();
	printf("ID\tEqpName\tStatus\t\tQuantity\tAvailability\n");
		for (int i = 0; i < rrecords; i++){
		
			printf("%d\t%s\t%s\t%d\t\t%s\n",  
				returned[i].id,
				returned[i].eName,
				returned[i].status,
				returned[i].quantity,
				returned[i].availability);
		}
		printf("\n");
		getch();
}
//change pass func for all users
void changePassword(char password[10]){
	int check=0;
	for(int m=0;m<records;m++){
		if(strcmp(users[m].password,password)==0){
			printf("Enter your new Password: ");
			char p[50];
			scanf("%s",&p);
			check++;
			strcpy(users[m].password,p);
			printf("Password changed successfully");
			break;
		}
	}
	saveUsersData();
}
//OUser return the borrowed equipment
void returnBorrowed(){
	printf("Enter the id to return equipment: ");
	int id;
	scanf("%d",&id);
	for(int i=0;i<brecords;i++){
		if(id==borrowed[i].id)
		{
			FILE *fptr;
			fptr = fopen("returned.txt","a+");
			strcpy(borrowed[i].status,"ReturnRequested");
			fprintf(fptr,"\n%d,%s,%s,%s,%d,%s",brecords,currentUser,borrowed[i].eName,borrowed[i].status,borrowed[i].quantity,borrowed[i].availability);
			printf("You would like to return %s.", borrowed[i].eName);
			fclose(fptr);
			brecords++;
		}
	}
	printf("\nPlease wait for the staff to approve your application to return the borrowed equipment.");
	getch();
}
//admin edit equipment info
void editEquipment()
{
	system("cls");
	head();
	showEquipments();
	printf("\nEnter equipment ID to change info: ");
	int id;
	scanf("%d",&id);
	int equantity;
	char ename[50],estatus[50],eavailability[50];
	int check=0;
	for(int i=0;i<erecords;i++)
	{
		if(equip[i].id==id)
		{
			printf("\nEnter new Equipment Name: ");
			scanf("%s",&ename);
			printf("Enter new Equipment Status: ");
			scanf("%s",&estatus);
			printf("Enter new Equipment Quantity: ");
			scanf("%d",&equantity);
			printf("Enter new Equipment Availability: ");
			scanf("%s",&eavailability);
			strcpy(equip[i].name,ename);
			strcpy(equip[i].status,estatus);
			equip[i].quantity=equantity;
			strcpy(equip[i].availability,eavailability);
			printf("Equipment info Changed successfully\n");
			saveEquipmentsData();
			check=1;
		}
		getch();
	}
}