#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmultichar"
TOF *  OUVRIR(char *  file_name, char mode) {
TOF * p = malloc(sizeof(TOF));
        if(mode == 'E' || mode == 'e' ) {
            p->F = fopen(file_name,'rb+');
            if(p->F == NULL) perror('Can\'t  read the file ');
            fread(& p->headerFile , sizeof(header_file), 1 , p->F);
        }
       else if(mode == 'N' || mode == 'n' ) {
           p->F = fopen(file_name,'wb+');
            if(p->F == NULL) perror('Can\'t  read the file ');
            p->headerFile.last_bloc = 0;
            fwrite(&p->headerFile, sizeof(header_file), 1,p->F);

        }
       return p;
}
// close the file
void FERME(TOF * file) {
    fseek(file->F,0L,SEEK_SET);
    fwrite(&file->headerFile, sizeof(header_file), 1,file->F);
    fclose(file->F);

}
// read the file from buffer
void LireDire(TOF * file, int bloc_number , bloc * buff) {

    fseek(file->F, sizeof(header_file) + (bloc_number - 1) * sizeof(bloc),SEEK_SET);
    fread(buff,sizeof(bloc),1,file->F);

}
// write the buffer content into the file
void EcrireDire(TOF * file, int bloc_number , bloc * buff) {
    fseek(file->F, sizeof(header_file) + (bloc_number - 1) * sizeof(bloc),SEEK_SET);
    fread(buff,sizeof(bloc),1,file->F);

}
// put a value in the header file
void update_header(TOF *file, int n) {
    file->headerFile.last_bloc = n;
}

int read_headerFile(TOF * file) {
    return file->headerFile.last_bloc;
}
void AllocBloc (TOF *file) {
    update_header(file, read_headerFile(file) + 1);
}

int random_int(int upper , int lower) {
    return rand() % (upper - lower) + lower;
}
// ----------- dicotomic searching ----------
void dichotomic_search( TOF * file, int id , int find , int i , int j ) {
 // declaration part
     int bi,bs,sup,inf;
     // boolean value
     int find2,stop;
     // buffer
     bloc * buff = NULL;
// program part
     // the file is already opened
    // la born inf ( num of first bloc)
     bi = 1;
     // sup born  (num of last bloc)
    bs = read_headerFile(file);
    // external searching
    find  = stop = find2  =  0;
    j = 1;
    while(bi <= bs && !find && !stop) {
        // le bloc du milieu entre bi et bs
        i = (bi + bs) / 2;
        LireDire(file,i,buff);
        if( id > buff->tab[1].id && id  <= buff->tab[buff->length - 1].id  ) {
            // internal searching in a bloc of file
            inf = 1; sup = buff->length;
            while(inf <= sup && !find  ) {
                // internal searching loop
                j = (inf + sup) / 2;
                if(id = buff->tab[j].id) find  = 1;
                else {
                    if(id < buff->tab[j].id) sup = j-1;
                    else inf = j+1;
                }
            }
            if(inf > sup) j = inf; // the end of internal search
            stop = 1;

        } else {
            if(id > buff->tab[1].id) bs = i-1;
            else bi = i + 1;
        }
    }
    if(bi > bs ) i = bi; j = 1;
    // the end
}



#pragma clang diagnostic pop