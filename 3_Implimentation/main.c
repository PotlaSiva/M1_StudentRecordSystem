
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct student{
    char ID[15];
    char name[20];
    char branch[20];
    char company[20];
    int salary;
};

struct student std;
void SetColor(int ForgC)
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     COORD coord = {0, 0};
     DWORD count;
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; 
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawRectangle(){
    int i, j;
    gotoxy(0,0);
    printf("%c",201);
    for(i = 1; i < 78; i++){
        gotoxy(i, 0);
        printf("%c",205);
    }
    gotoxy(78,0);
    printf("%c",187);
    for(i = 1; i < 25; i++){
        gotoxy(78, i);
        if(i == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    gotoxy(78, 25);
    printf("%c",188);
    for(i = 77; i > 0; i--){
        gotoxy(i,25);
        if(i == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    gotoxy(0,25);
    printf("%c",200);
    for(i = 24; i > 0; i--){
        gotoxy(0,i);
        if(i == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(i = 1; i < 78; i++){
        gotoxy(i,6);
        if(i == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(i = 7; i < 25; i++){
        gotoxy(35,i);
        printf("%c",186);
    }

}

void clearWindow(){
    int i,j;
    for(i = 37; i < 78; i++){
        for(j = 7; j < 25; j++){
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}

void window(){
    drawRectangle();
    gotoxy(28,2);
    SetColor(35);
    printf("STUDENT PLACEMENT ");
    gotoxy(16,3);
    printf("MALINENI LAKSHMI ENGINEERING COLLEGE, Guntur, AP");
    gotoxy(31,4);
    printf("PIN: 522017");
    gotoxy(25,24);
    SetColor(17);

}

void print_heading(const char st[]){
    SetColorAndBackground(31,28);
    gotoxy(45,8);printf("MLC : %s",st);
    SetColorAndBackground(17,15);
}

int compare(char id[]){
	FILE *fp;
    fp = fopen("record.txt","rb");
    struct student stu;
    while(fread(&stu,sizeof(stu),1,fp) == 1){
        if(strcmp(id,stu.ID) == 0){
            return 0;
        }
    }
    return 1;
}
void add_student(){
    clearWindow();
    print_heading("Add Record");
    int print = 37;
    FILE *fp;
    fp = fopen("record.txt","ab+");
    SetColor(45);
    if(fp == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        gotoxy(print,10);printf("ID: ");gets(std.ID);
        //here you can confirms the ID
        gotoxy(print,12);printf("Name: ");gets(std.name);
        gotoxy(print,14);printf("Branch: ");gets(std.branch);
        gotoxy(print,16);printf("Company name: ");gets(std.company);
        gotoxy(print,18);printf("Salary: ");scanf("%d",&std.salary);
        if (compare(std.ID)==1){
        	fwrite(&std, sizeof(std), 1, fp);
        	gotoxy(40,22); printf("The record is sucessfully added");
		}
		else{
			gotoxy(40,22); printf("ID already existed");
		}
		
        	
    }
    SetColor(28);
    fclose(fp);
    return;
}

void search_student(){
    clearWindow();
    print_heading("Search Record");
    SetColor(45);
    char s_id[15];
    int isFound = 0;
    gotoxy(37,10);printf("Enter ID to Search: ");fflush(stdin);
    gets(s_id);
    FILE *fp;
    fp = fopen("record.txt","rb");
    while(fread(&std,sizeof(std),1,fp) == 1){
        if(strcmp(s_id,std.ID) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        gotoxy(37,12);printf("The record is Found");
        gotoxy(37,14);printf("ID: %s",std.ID);
        gotoxy(37,15);printf("Name: %s",std.name);
        gotoxy(37,16);printf("Branch: %s",std.branch);
        gotoxy(37,17);printf("Company Name: %s",std.company);
        gotoxy(37,18);printf("Salary: %d",std.salary);
    }else{
        gotoxy(37,12);printf("Sory, No record found in the database");
    }
    SetColor(28);
    fclose(fp);
    return;
}

void mod_student(){
    clearWindow();
    print_heading("Modify Record");
    SetColor(45);
    char s_id[15];
    int isFound = 0, print = 37;
    gotoxy(37,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(s_id);
    FILE *fp,*temp;
    fp = fopen("record.txt","rb+");
    temp = fopen("temp.txt", "wb");
    
    while(fread(&std, sizeof(std),1,fp) == 1){
        if(strcmp(s_id, std.ID) == 0){
            fflush(stdin);
            gotoxy(print,12);printf("ID: ");gets(std.ID);
            gotoxy(print,14);printf("Name: ");gets(std.name);
            gotoxy(print,16);printf("Branch: ");gets(std.branch);
            gotoxy(print,18);printf("Company name: ");gets(std.company);
            gotoxy(print,20);printf("Salary: ");scanf("%d",&std.salary);
            fseek(fp, sizeof(std), SEEK_CUR);
            fwrite(&std,sizeof(std), 1, temp);
            isFound = 1;
        }
        else{
        	fwrite(&std,sizeof(std), 1, temp);
		}
    }
    if(!isFound){
        gotoxy(print, 12);printf("No Record Found");
    } 
	fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");
    SetColor(28);
    return;
}
void delete_student(){
    clearWindow();
    print_heading("Delete Record");
    SetColor(45);
    char s_id[15];
    int isFound = 0, print = 37;
    gotoxy(37,10);printf("Enter ID to Delete: ");fflush(stdin);
    gets(s_id);
    FILE *fp, *temp;
    fp = fopen("record.txt","rb");
    temp = fopen("temp.txt", "wb");
    while(fread(&std, sizeof(std),1,fp) == 1){
        if(strcmp(s_id, std.ID) == 0){
            continue;
        }
        else{
        	fwrite(&std,sizeof(std),1,temp);
		}
    }
    fclose(fp);
    fclose(temp);
    remove("record.txt");
    rename("temp.txt","record.txt");
    gotoxy(37,12);printf("The record is sucessfully deleted");
    SetColor(28);
    return;
}


void main_window(){
    int choice;
    SetColor(28);
    int x = 2;
    while(1){
        gotoxy(x,8);printf("1. Add Student");
        gotoxy(x,10);printf("2. Search Student");
        gotoxy(x,12);printf("3. Modify Student Record");
//        gotoxy(x,14);printf("4. Generate Marksheet");
        gotoxy(x,14);printf("4. Delete Student Record");
//        gotoxy(x,16);printf("6. Change password");
        gotoxy(x,16);printf("5. Exit");
        gotoxy(x,18);printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                add_student();
                break;
            case 2:
                search_student();
                break;
            case 3:
                mod_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                exit(0);
                break;
            default:
                break;
        }

    }

}

int main(){
    ClearConsoleToColors(17,15);
    SetConsoleTitle("Programming-technique.blogspot.com - Student Record System");
    window();
    main_window();
    return 0;
}
