/* Name: Lim Bing Qian Student ID: 20408309 */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define size 100

//visitor information structure
struct visitData{
char *SrNo;
char *ticketNo;
char *Name;
char *ID;
};

typedef struct ticket {
struct visitData visitor;
struct ticket *nextPtr;
}tick;

//functions prototypes
tick *addinfo(tick *previous,char* serial,char* ticketno,char* name,char* id); //insert visitor info
void printlist (); //print menu
void space (char* name); //change space to underscore
void printList(tick *start); //display linked list
void writeinto(tick startPtr); //write into ticket.txt
void searchname (tick* head,char* name); //search name
void searchid (tick* head,char* id); //search id
void searchticket (tick* head,char* tickt); //search ticketno
void stringtoupper(char *name); //change string to upper
void removenewline (char *arr, int length); //remove new line
void deleteid (tick** head,char* id); //delete visitor id
void deletename(tick** head,char* name); //delete visitor name
void deleteticket(tick** head,char* name); //delete visitor ticketno
void writedel(tick startPtr); //update ticket.txt file
int writevistotal(tick *start);
void writevcfile(int count);
FILE *ptroutfile;

int main ()
{
    //reset ticket.txt file everytime program runs 
    FILE *cfPtr=NULL;

    if ((cfPtr=fopen("ticket.txt","w"))==NULL)
    {
        puts("Error opening file");
    }

    fclose(cfPtr);

    tick *visitorinfo = NULL;
    tick *new = NULL;

    //variable for visitor count
    int viscount=0;

    //variables declaration for adding visitor's information
    int choice=0;
    int srno=0;
    char fullname[30],id[size],tempid[size],loi[size],ticketno[size],serial[size],tempname[size];

    //variables declaration for searching
    int searchchoice;
    char visitorname[size],visitortick[size],visitorid[size];

    //variables declaration for deleting
    int delchoice;
    char delid[size],delticket[size],delname[size];

    printlist(); //print menu 
    while(1)
    {
    int viscount = writevistotal(visitorinfo);
    writevcfile(viscount);
    printf("Input '8' to view menu again\n");
    puts(" ");
    printf("Your selection: ");
    scanf("%d",&choice);
    if (choice == 7)
    {
        printf("EXITING......");
        break;
    }

    switch (choice)
    {
        case 1:
        //Serial No
        srno = srno+1;
        sprintf(serial,"%02d",srno);

        //Full Name 
        printf("Enter Your Full Name:");
        scanf(" %[^\n]s",fullname);
        space(fullname);

        //ID 
        int cmp1,cmp2;
        char local[size] = "L";
        char inte[size] = "I";
        printf("enter your ID:");
        scanf("%s",tempid);
        
        printf("Are you a local visitor or international visitor? (L or I) ");
        scanf("%s",loi);
        cmp1 = strcmp(local,loi);
        cmp2 = strcmp(inte,loi);
        if (cmp1 == 0)
        {
            sprintf(id,"%s%s","IC",tempid);
        }
        else if (cmp2 == 0)
        {
            sprintf(id,"%s%s","PASS",tempid);
        }
        else 
        {
            printf("error selection");
        }

        //ticket
        int tempname;
        char temp[20]={0};
        char nametik[30];
        strcpy(nametik,fullname);
        tempname=strlen(fullname);
        if (tempname<6)
        {
            if (tempname==1)
                {
                memset(temp,' ',5);
                strcat(temp,nametik);
                strcpy(nametik,temp);
                }
                if (tempname==2)
                {
                memset(temp,' ',4);
                strcat(temp,nametik);
                strcpy(nametik,temp);
                }
                if (tempname==3)
                {
                memset(temp,' ',3);
                strcat(temp,nametik);
                strcpy(nametik,temp);
                }
                if(tempname==4)
                {
                memset(temp,' ',2);
                strcat(temp,nametik);
                strcpy(nametik,temp);
                }
                if(tempname==5)
                {
                memset(temp,' ',1);
                strcat(temp,nametik);
                strcpy(nametik,temp);
                }
            }

            char ticketnum[50]={0};
            char* ticketPtr=ticketnum;
            for(int i=0;i<6;i++)
            {
                int num=nametik[i];
                sprintf(ticketno,"%d",num);
                strcat(ticketPtr,ticketno);
            }
            char* srPtr=serial;
            strcat(ticketPtr,srPtr);




        if (visitorinfo == NULL)
        {
        visitorinfo = addinfo(NULL,serial,ticketPtr,fullname,id);
        new = visitorinfo;
        }
        else 
        {
            new = addinfo(new,serial,ticketPtr,fullname,id);
        }
        writeinto(*new);
        break;
        case 2:
        printf("Select to search a visitor's data by inputting their:\n\nticketno (1)\nname (2)\nID(3)\n");
        printf("Selection: ");
        scanf("%d",&searchchoice);
        
        switch(searchchoice)
        {
        case 1:
        printf("Enter visitor ticketno to search:");
        scanf("%s",visitortick);
        searchticket (visitorinfo,visitortick);
        break;
        case 2:
        fflush(stdin);
        searchname (visitorinfo,visitorname);
        break;
        case 3:
        printf("Enter visitor id to search: ");
        scanf("%s",visitorid);
        searchid (visitorinfo,visitorid);
        break;
        default:
        printf("error");
        break;
        }
        break;

        case 3:
        printf("Enter visitor's ticketno to delete:");
        scanf("%s",delticket);
        deleteticket(&visitorinfo,delticket);
        puts(" ");
        puts(" ");
        printList(visitorinfo);
        writedel(*visitorinfo);
        break;

        case 4:
        fflush(stdin);
        deletename(&visitorinfo,delname);
        puts(" ");
        puts(" ");
        printList(visitorinfo);
        writedel(*visitorinfo);
        break;

        case 5:
        printf("Enter visitor's ID to delete:");
        scanf("%s",delid);
        deleteid(&visitorinfo,delid);
        puts(" ");
        puts(" ");
        printList(visitorinfo);
        writedel(*visitorinfo);
        break;

        case 6:
        printList(visitorinfo);
        break;

        case 8:
        printlist();
        break;
        
        default:
        printf("This option is not available in menu\n\n");
        break; 
    }
    }
    

}

void printlist()
{
    printf("---------- Theme Park Booking System Menu ----------\n\n");
    printf("(1) Add a new visitor information\n");
    printf("(2) Search for visitor information\n");
    printf("(3) Delete visitor information based on ticket number\n");
    printf("(4) Delete visitor information based on fullname\n");
    printf("(5) Delete visitor information based on ID\n");
    printf("(6) Display total number of tickets sold\n");
    printf("(7) EXIT \n");
    puts(" ");
}

void space (char* name)
{
    for (int i=0; name[i] != '\0'; i++)
    {
        if (name[i] == ' ')
        {
            name[i] = '_' ;
        }
    }
}

tick *addinfo(tick *previous,char* serial,char* ticketno,char* name,char* id)
{

    tick *info = malloc(sizeof(tick));
    info->nextPtr = NULL;
    info->visitor.SrNo =strdup(serial);
    info->visitor.ticketNo = strdup(ticketno);
    info->visitor.Name = strdup(name);
    info->visitor.ID= strdup(id);

    if (previous != NULL)
    {
        previous->nextPtr = info;
    }

    printf("The information of the visitor %s is recorded \n\n",info->visitor.Name);
    ptroutfile=fopen("output.txt","a");
    fprintf(ptroutfile,"The information of the visitor %s is recorded \n\n",info->visitor.Name);
    fclose(ptroutfile);

    return info;
}

void printList(tick *start){
    tick *currentTicket = start;
    int count = 0;

    while(currentTicket != NULL)
    {
        count++;
        printf("%s %s %s %s\n",currentTicket->visitor.SrNo,currentTicket->visitor.ticketNo,currentTicket->visitor.Name,currentTicket->visitor.ID);
        currentTicket = currentTicket->nextPtr;
    }
    printf("Current total Visitors:%d\n",count);
}

void writeinto(tick startPtr)
{
    FILE *cfPtr=NULL;

    if ((cfPtr=fopen("ticket.txt","a+"))==NULL)
    {
        puts("Error opening file");
    }
    else
    {
        tick* ptr=&startPtr;
        while(ptr!=NULL)
        {
            fprintf(cfPtr,"%s %s %s %s\n",ptr->visitor.SrNo,ptr->visitor.ticketNo,ptr->visitor.Name,ptr->visitor.ID);
            ptr=ptr->nextPtr;
            printf("\nVisitor information stored\n");
        }
    }
    fclose(cfPtr);
}

void removenewline (char *arr, int length)
{			
    int i;
    for (i = 0; i < length; i++) { 
        if (arr[i] == '\n') {
            arr[i] = '\0';
            break;
        }
    }
}

void stringtoupper(char *name)
{
	int i;
    for(i=0;name[i];i++)  
    {
        if(name[i]>=97 && name[i]<=122)
        name[i]-=32;
 	}	
}

void searchname (tick* head,char* visname)
{
    printf("enter name to search:");
    fgets(visname,30,stdin);
    space(visname);
    stringtoupper(visname);
    removenewline (visname,30);

    tick* current=head;
    int cmpresult=0;
    char listupper[size];

    while (current!= NULL)
    {
        char tempName[30]="\0";
        strncpy(tempName,current->visitor.Name,strlen(current->visitor.Name));
        space(tempName);
        stringtoupper(tempName);
        //strcpy(listupper,current->visitor.Name);
        cmpresult = strcmp(tempName,visname);
        if (cmpresult==0)
        {
            printf("The following record of the visitor is found:\n\n");
            printf("%s %s %s %s\n",current->visitor.SrNo,current->visitor.ticketNo,current->visitor.Name,current->visitor.ID);
            ptroutfile=fopen("output.txt","a");
            fprintf(ptroutfile,"The following record of the visitor is found:\n %s %s %s %s\n\n",current->visitor.SrNo,current->visitor.ticketNo,current->visitor.Name,current->visitor.ID);
            fclose(ptroutfile);
        }
        current = current -> nextPtr;
    }
}

void searchid (tick* head,char* id)
{
    tick* current=head;

    int cmpresult=0;

    while (current!= NULL)
    {

        cmpresult = strcmp(current->visitor.ID,id);
        if (cmpresult==0)
        {
            printf("The following record of the visitor is found:\n\n");
            printf("%s %s %s %s\n",current->visitor.SrNo,current->visitor.ticketNo,current->visitor.Name,current->visitor.ID);
            ptroutfile=fopen("output.txt","a");
            fprintf(ptroutfile,"The following record of the visitor is found:\n %s %s %s %s\n\n",current->visitor.SrNo,current->visitor.ticketNo,current->visitor.Name,current->visitor.ID);
            fclose(ptroutfile);
        }
        current = current -> nextPtr;
    }
}

void searchticket (tick* head,char* tickt)
{
    tick* current=head;

    int cmpresult=0;

    while (current!= NULL)
    {
        cmpresult = strcmp(current->visitor.ticketNo,tickt);
        if (cmpresult==0)
        {
            printf("The following record of the visitor is found:\n");
            printf("%s %s %s %s\n",current->visitor.SrNo,current->visitor.ticketNo,current->visitor.Name,current->visitor.ID);
            ptroutfile=fopen("output.txt","a");
            fprintf(ptroutfile,"The following record of the visitor is found:\n%s %s %s %s\n\n",current->visitor.SrNo,current->visitor.ticketNo,current->visitor.Name,current->visitor.ID);
            fclose(ptroutfile);
        }
        current = current -> nextPtr;
    }
}

void deleteid (tick** head,char* id)
{
    tick *current=*head;
    tick *previous = *head;

    int cmpresult=-1;

    if (*head == NULL)
    {
        printf("list is already empty");
    }
    else if (strcmp(current->visitor.ID,id)==0)
    {
        printf("The visitor with ID: %s, information is deleted",current->visitor.ID);
        ptroutfile=fopen("output.txt","a");
        fprintf(ptroutfile,"The visitor with ID: %s, information is deleted\n\n",current->visitor.ID);
        fclose(ptroutfile);
        *head =current->nextPtr;
        free(current);
        current = NULL;
    }
    else 
    {
        while (strcmp(current->visitor.ID,id)!=0)
        {
            previous=current;
            current=current->nextPtr;
        }
        previous->nextPtr = current -> nextPtr;
       printf("The visitor with ID: %s, information is deleted",current->visitor.ID);
        ptroutfile=fopen("output.txt","a");
        fprintf(ptroutfile,"The visitor with ID: %s, information is deleted\n\n",current->visitor.ID);
        fclose(ptroutfile);
        free(current);
        current = NULL;
    }
}

void deleteticket(tick** head,char* ticket)
{
    tick *current=*head;
    tick *previous = *head;

    int cmpresult=-1;

    if (*head == NULL)
    {
        printf("list is already empty");
    }
    else if (strcmp(current->visitor.ticketNo,ticket)==0)
    {
        printf("The visitor with Ticket No.:%s, information is deleted",current->visitor.ticketNo);
        ptroutfile=fopen("output.txt","a");
        fprintf(ptroutfile,"The visitor with Ticket No.:%s, information is deleted\n\n",current->visitor.ticketNo);
        fclose(ptroutfile);
        *head =current->nextPtr;
        free(current);
        current = NULL;
    }
    else 
    {
        while (strcmp(current->visitor.ticketNo,ticket)!=0)
        {
            previous=current;
            current=current->nextPtr;
        }
        previous->nextPtr = current -> nextPtr;
        printf("The visitor with Ticket No.:%s, information is deleted",current->visitor.ticketNo);
        ptroutfile=fopen("output.txt","a");
        fprintf(ptroutfile,"The visitor with Ticket No.:%s, information is deleted\n\n",current->visitor.ticketNo);
        fclose(ptroutfile);
        free(current);
        current = NULL;
    }
}

void deletename(tick** head,char* name)
{
    printf("enter name to delete:");
    fgets(name,30,stdin);
    tick *current=*head;
    tick *previous = *head;
    tick *current2=*head;
    tick *previous2 = *head;
    int count=0;

    space(name);
    stringtoupper(name);
    removenewline (name,30);

    char tempName[30]="\0";
    strcpy(tempName,current->visitor.Name);
    space(tempName);
    stringtoupper(tempName);

    int cmpresult=-1;

    cmpresult = strcmp(tempName,name);

    if (*head == NULL)
    {
        printf("list is already empty");
    }
    else if (cmpresult==0)
    {
        printf("The visitor: %s information is deleted",current->visitor.Name);
        ptroutfile=fopen("output.txt","a");
        fprintf(ptroutfile,"The visitor: %s information is deleted\n\n",current->visitor.Name);
        fclose(ptroutfile);
        *head =current->nextPtr;
        free(current);
        current = NULL;
        
    }
    else 
    {

        while (cmpresult!=0)
        {
            previous=current;
            current=current->nextPtr;

            strcpy(tempName,current->visitor.Name);
            space(tempName);
            stringtoupper(tempName);
            cmpresult = strcmp(tempName,name);

        }
        previous->nextPtr = current -> nextPtr;
        printf("The visitor: %s information is deleted",current->visitor.Name);
        ptroutfile=fopen("output.txt","a");
        fprintf(ptroutfile,"The visitor: %s information is deleted\n\n",current->visitor.Name);
        fclose(ptroutfile);
        free(current);
        current = NULL;
        
    }
}

void writedel(tick startPtr)
{
    FILE *cfPtr=NULL;

    if ((cfPtr=fopen("ticket.txt","w"))==NULL)
    {
        puts("Error opening file");
    }
    else
    {
        tick* ptr=&startPtr;
        while(ptr!=NULL)
        {
            fprintf(cfPtr,"%s %s %s %s\n",ptr->visitor.SrNo,ptr->visitor.ticketNo,ptr->visitor.Name,ptr->visitor.ID);
            ptr=ptr->nextPtr;
        }
    }
    fclose(cfPtr);
}

int writevistotal(tick *start){
    tick *currentTicket = start;
    int count = 0;


    while(currentTicket != NULL)
    {
        count++;
        currentTicket = currentTicket->nextPtr;
    }
    
    return count;

}

void writevcfile(int count)
{
    FILE *ptr1=NULL;
    FILE *ptr2=NULL;

    char SrNo[20],ticketno[30],name[30],id[20];

    ptr1=fopen("ticket.txt","r");
    ptr2=fopen("temp.txt","w");

    fprintf(ptr2,"Total visitor : %d \n",count);
    while(fscanf(ptr1,"%s %s %s %s\n",SrNo,ticketno,name,id)==4)
    {
        if (strcmp(SrNo,"Total")==0)
        {
            printf("");
        }
        else
        {
            fprintf(ptr2,"%s %s %s %s\n",SrNo,ticketno,name,id);
        }
    }

    fclose(ptr1);
    fclose(ptr2);

    ptr1=fopen("ticket.txt","w");
    ptr2=fopen("temp.txt","r");

    while(fscanf(ptr2,"%s %s %s %s\n",SrNo,ticketno,name,id)==4)
    {
        fprintf(ptr1,"%s %s %s %s\n",SrNo,ticketno,name,id);
    }
    fclose(ptr1);
    fclose(ptr2);

    remove("temp.txt");
}






































