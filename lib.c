//so, functions 1, 2 and 5 work but the rest do not

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void addbookinf();
void readbookinf();
void readauthor();
void listtitle();
int bookcount();
void arrangebookaccnum();

FILE *fp;

typedef struct library 
{
    int accnum;
    char btitle[30];
    char author[30];
    float price;
    bool isissued;
}libr;

int main()
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

    switch(option)
    {
        case 1: addbookinf(); break;
        case 2: readbookinf(); break;
        case 3: readauthor(); break;
        case 4: listtitle(); break;
        case 5:
            bc = bookcount();
            printf("The number of books is %d\n", bc);
            main();
            break;
        case 6: arrangebookaccnum(); break;
        default: return 0; break;
    }
}

void addbookinf() //note: the strings you input here can only be a single word, no spaces. didn't fix this cause didn't really need to
{
    fp = fopen("lib.dat", "a");

    int i, newbookc;
    libr lib[50];

    printf("Enter number of books to add\n");
    scanf("%d", &newbookc);

    for(i=0; i<newbookc; i++)
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

    main();
}

void readbookinf()
{
    int i = 0;
    libr lib[50];

    fp = fopen("lib.dat", "r");

    char buffer[200];
    fgets(buffer, 200, fp);

    while(!feof(fp))
    {
      libr* l = lib + i;
      sscanf(buffer, "%d %s %s %f", &l->accnum, l->btitle, l->author, &l->price);
      fgets(buffer, 200, fp);
      i++;     
    }
    
    int n = i;

    for(i=0; i < n; i++)
    {
      printf("%5d %15s %15s %10f\n", lib[i].accnum, lib[i].btitle, lib[i].author, lib[i].price);    
    } 
    
    //i didn't know how to read from a array of structures so i followed a tut here, so i dont really know how it works. the typedef in the struct declaration was also a part of it

    fclose(fp);
    
    main();
}

void readauthor()
{
    int i, bc;
    libr lib[50];
    char auname[30];

    printf("Enter required author\n");
    scanf("%s", auname);

    fp = fopen("lib.dat", "r");

    char buffer[200];
    fgets(buffer, 200, fp);

    while(!feof(fp))
    {
      libr* l = lib + i;
      sscanf(buffer, "%s", l->author);
      fgets(buffer, 200, fp);
      i++;
    }

    int n = i;

    for(i=0; i < n; i++)
    {
      if(lib[i].author==auname)
      {
        printf("%5d %15s %10f", lib[i].accnum, lib[i].btitle, lib[i].price);
      }
      printf("\n");     
    }
    
    fclose(fp);

    main();      
}

void listtitle()
{
    int i, an;
    libr lib[50];

    printf("Enter accession number for book\n");
    scanf("%d", &an);

    fp = fopen("lib.dat", "r");

    char buffer[200];
    fgets(buffer, 200, fp);

    while(!feof(fp))
    {
      libr* l = lib + i;
      sscanf(buffer, "%s", l->btitle);
      fgets(buffer, 200, fp);
      i++;
    }

    int n = i;

    for(i=0; i < n; i++)
    {
      if(lib[i].accnum==an)
      {
        printf("%s", lib[i].btitle);
      }  
    }

    fclose(fp);

    main();   
}

int bookcount()
{
    int i=0;
    libr lib[50];

    fp = fopen("lib.dat", "r");

    char buffer[200];
    fgets(buffer, 200, fp);

    while(!feof(fp))
    {
      libr* l = lib + i;
      sscanf(buffer, "%d %s %s %f", &l->accnum, l->btitle, l->author, &l->price);
      fgets(buffer, 200, fp);
      i++;     
    }
    
    int n = i;

    fclose(fp);

    return(n);
}

void arrangebookaccnum()
{
    int i, j, k;
    libr lib[50];
    libr temp;

    int bc = bookcount();

    fp = fopen("lib.dat", "r");

    char buffer[200];
    fgets(buffer, 200, fp);

    while(!feof(fp))
    {
      libr* l = lib + i;
      sscanf(buffer, "%d %s %s %f", &l->accnum, l->btitle, l->author, &l->price);
      fgets(buffer, 200, fp);
      i++;     
    }

    for(j=0; j<(bc-1); j++)
    {
      for(k=k+1; k<bc; k++)
      {
        if(lib[j].accnum > lib[k].accnum)
        {
          temp=lib[j];
          lib[j]=lib[k];
          lib[k]=temp;
        }
      }
    }    

    for(i=0; i < bc; i++)
    {
      printf("%5d %15s %15s %10f\n", lib[i].accnum, lib[i].btitle, lib[i].author, lib[i].price);    
    }

    fclose(fp);

    main();
}