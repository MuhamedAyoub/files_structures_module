#ifndef TOF_INCLUDED
#include <stdio.h>
#include <stdlib.h>
// declare the max length of the blocs table
#define max_table_length 10

// declare our record
typedef struct student
{
    int id;
    char name[20];
    int age;
    int grade;
} student;
typedef struct bloc
{
    student tab[max_table_length];
    int length;
} bloc;

typedef struct  header_file{
    int last_bloc;
} header_file;

typedef  struct TOF {
    FILE * F;
    header_file headerFile;
}TOF;

// basic operations
//@params file name of the path  , mode (a or n ) => FILE TYPE TOF
TOF *  OUVRIR(char *  file_name, char mode);

// close your file
void FERME(TOF * file);
// read bloc of  file using buffer
void LireDire(TOF * file, int bloc_number , bloc * buff);
//  write bloc of file using buffer
void EcrireDire(TOF * file, int bloc_number , bloc * buff);
void update_headerFile(TOF *file, int n);
// read the  number of blocs or last bloc
int read_headerFile(TOF * file);
void charge(TOF *p);
void AllocBloc (TOF *p);

void reorg(TOF *p, int vp);
void dichotomic_search( TOF * file, int id , int find , int i , int j );
void affichage(TOF *p);
#endif