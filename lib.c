#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main_menu();
void add_book_info();
void read_book_info();
void read_author();
void list_title();
int book_count();
void book_sort();
 
FILE* fp;
 
struct Library {
    int accnum;
    char btitle[30];
    char author[30];
    float price;
} lib[50];
 
int main() {
    main_menu();
}

void main_menu() {
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
 
    switch (option) {
        case 1:
            add_book_info();
            break;
        case 2:
            read_book_info();
            break;
        case 3:
            read_author();
            break;
        case 4:
            list_title();
            break;
        case 5:
            bc = book_count();
            printf("The number of books is %d\n", bc);
            system("pause");
            main_menu();
        case 6:
            book_sort();
            break;
        default:
            exit(0);
    }
}
 
void add_book_info() {
    fp = fopen("lib.dat", "a");
 
    int i, newbookc;
 
    printf("Enter number of books to add\n");
    scanf("%d", &newbookc);
 
    for (i = 0; i < newbookc; i++) {
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
    main_menu();
}
 
void read_book_info() {
    int i = 0;
 
    fp = fopen("lib.dat", "r");
 
    while(fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) {
        i++;
    }
 
    int n = i;
 
    for (i = 0; i < n; i++) {
        printf("%5d %15s %15s %10f\n", lib[i].accnum, lib[i].btitle, lib[i].author, lib[i].price);
    }
 
    fclose(fp);

    system("pause");
    main_menu();
}
 
void read_author() {
    int i = 0;
    char auname[30];

    printf("Enter required author\n");
    scanf("%s", auname);

    fp = fopen("lib.dat", "r");
 
    while (fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) {
        if (!strcmp(lib[i].author, auname)) {
            printf("%15s %s %lf\n", lib[i].btitle, lib[i].author, lib[i].price);
        }
        i++;
    }
 
    fclose(fp);

    system("pause");
    main_menu();
}
 
void list_title() {
    int i, acc_num;
 
    printf("Enter accession number for book\n");
    scanf("%d", &acc_num);
 
    fp = fopen("lib.dat", "r");

    while (fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) {
        if (lib[i].accnum == acc_num) {
          printf("%10s\n", lib[i].btitle);
        }
    }
 
    fclose(fp);

    system("pause");
    main_menu();
}

int book_count()
{
    int i = 0;

    fp = fopen("lib.dat", "r");

    while(fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) {
        i++;
    }

    int n = i;

    return n;

    system("pause");
    main_menu();
}
 
void book_sort() 
{
    int i = 0, n = book_count();
    struct Library temp;
    
    fp = fopen("lib.dat", "r");
 
    while (fscanf(fp, "%d %s %s %f", &lib[i].accnum, lib[i].btitle, lib[i].author, &lib[i].price) != EOF) {
        i++;
    }
    
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (lib[j].accnum > lib[j + 1].accnum) {
                temp = lib[j];
                lib[j] = lib[j + 1];
                lib[j + 1] = temp;
            }
        }
    }
    
    for (i = 0; i < n; i++) {
        printf("%5d %15s %15s %10f\n", lib[i].accnum, lib[i].btitle,lib[i].author, lib[i].price);
    }

    fclose(fp);

    system("pause");
    main_menu();
}
