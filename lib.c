#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainmenu();
void addbookinf();
void readbookinf();
void readauthor();
void listtitle();
int bookcount();
void arrangebookaccnum();
 
FILE* fp;
 
struct library 
{
    int accnum;
    char btitle[30];
    char author[30];
    float price;
} lib[50];
 
int main() 
{
    mainmenu();
}

void mainmenu()
{
    int option;
    int bc;

    printf("LIBRARY MENU\n");
    printf("Press 1 to add book info\n");
    printf("Press 2 to display book info\n");
    printf("Press 3 to display all books of a particular author\n");
    printf("Press 4 to list the title of specified book\n");
    printf("Press 5 to list the book count\n");
    printf("Press 6 to list books in order of accession number\n");
    printf("Press any other key to exit\n");
 
    scanf("%d", &option);
 
    switch (option) 
    {
        case 1:
            addbookinf();
            break;
        case 2:
            readbookinf();
            break;
        case 3:
            readauthor();
            break;
        case 4:
            listtitle();
            break;
        case 5:
            bc = bookcount();
            printf("The number of books is %d\n", bc);
            system("pause");
            mainmenu();
        case 6:
            arrangebookaccnum();
            break;
        default:
            exit(0);
    }
}
 
void addbookinf()  
{
    fp = fopen("lib.dat", "a");
 
    int i, newbookc;
 
    printf("Enter number of books to add\n");
    scanf("%d", &newbookc);
 
    for (i = 0; i < newbookc; i++) 
    {
        printf("Enter book access number\n");
        scanf("%d", &lib[i].accnum);
 
        printf("Enter book title\n");
        scanf("%s", lib[i].btitle);
 
        printf("Enter author\n");
        scanf("%s", lib[i].author);
 
        printf("Enter price\n");
        scanf("%f", &lib[i].price);

        fprintf(fp, "%5d %15s %15s %10f\n", lib[i].accnum, lib[i].btitle, lib[i].author, lib[i].price);
    }
 
    fclose(fp);

    system("pause");
    mainmenu();
}
 
void readbookinf() 
{
    int i = 0;
 
    fp = fopen("lib.dat", "r");
 
    while(fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) 
    {
        i++;
    }
 
    int n = i;
 
    for (i = 0; i < n; i++) 
    {
        printf("%5d %15s %15s %10f\n", lib[i].accnum, lib[i].btitle, lib[i].author, lib[i].price);
    }
 
    fclose(fp);

    system("pause");
    mainmenu();
}
 
void readauthor() 
{
    int i = 0;
    char auname[30];

    printf("Enter required author\n");
    scanf("%s", auname);

    fp = fopen("lib.dat", "r");
 
    while (fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) 
    {
        if (!strcmp(lib[i].author, auname)) 
        {
            printf("%15s %s %lf\n", lib[i].btitle, lib[i].author, lib[i].price);
        }
        i++;
    }
 
    fclose(fp);

    system("pause");
    mainmenu();
}
 
void listtitle() 
{
    int i, an;
 
    printf("Enter accession number for book\n");
    scanf("%d", &an);
 
    fp = fopen("lib.dat", "r");

    while (fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) 
    {
        if (lib[i].accnum == an) 
        {
          printf("%10s\n", lib[i].btitle);
        }
    }
 
    fclose(fp);

    system("pause");
    mainmenu();
}

int bookcount()
{
    int i = 0;

    fp = fopen("lib.dat", "r");

    while(fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) 
    {
        i++;
    }

    int n = i;

    return n;

    system("pause");
    mainmenu();
}
 
void arrangebookaccnum() 
{
    int i = 0, n = bookcount();
    struct library temp;
    
    fp = fopen("lib.dat", "r");
 
    while (fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) 
    {
        i++;
    }
    
    for (i = 0; i < n; i++) 
    {
        for (int j = 0; j < n - 1; j++) 
        {
            if (lib[j].accnum > lib[j + 1].accnum) 
            {
                temp = lib[j];
                lib[j] = lib[j + 1];
                lib[j + 1] = temp;
            }
        }
    }
    
    for (i = 0; i < n; i++) 
    {
        printf("%5d %15s %15s %10f\n", lib[i].accnum, lib[i].btitle,lib[i].author, lib[i].price);
    }

    fclose(fp);

    system("pause");
    mainmenu();
}
