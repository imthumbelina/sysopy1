#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <sys/times.h>
#include <time.h>
 #include <sys/resource.h>
 #include <sys/time.h>

struct rusage rusage_start,rusage_end;
struct timeval user_start,user_end,system_start,system_end,real_start,real_end;


void start_clock(){
  getrusage(RUSAGE_SELF,&rusage_start);
  gettimeofday(&real_start,NULL);
}
void end_clock(FILE*pfile){
  gettimeofday(&real_end,NULL);
  getrusage(RUSAGE_SELF,&rusage_end);

  user_start=rusage_start.ru_utime; //total amount of time spend in user mode
  user_end=rusage_end.ru_utime;
  system_start=rusage_start.ru_stime;
  system_end=rusage_end.ru_stime;

  fprintf(pfile,"system time %09ld mikrosekund\n",((system_end.tv_sec - system_start.tv_sec)*1000000L) + system_end.tv_usec - system_start.tv_usec);
  fprintf(pfile,"user time %09ld mikrosekund\n",((user_end.tv_sec - user_start.tv_sec)*1000000L)+ user_end.tv_usec - user_start.tv_usec);
  fprintf(pfile,"real time %09ld mikrosekund\n\n",((real_end.tv_sec - real_start.tv_sec)*1000000L) + real_end.tv_usec - real_start.tv_usec);


}

char *randstring(int length) {
    static int mySeed = 25011984;
    char *string = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t stringLen = strlen(string);
    char *randomString = NULL;

    srand(time(NULL) * length + ++mySeed);

    if (length < 1) {
        length = 1;
    }

    randomString = malloc(sizeof(char) * (length +1));

    if (randomString) {
        short key = 0;

        for (int n = 0;n < length;n++) {
            key = rand() % stringLen;
            randomString[n] = string[key];
        }

        randomString[length] = '\0';

        return randomString;
    }
    else {
        printf("No memory");
        exit(1);
    }
}

void creatingTree(FILE*pfile){
  start_clock();
  BSTNode**root=malloc(sizeof(BSTNode*));
  *root = NULL;

  fprintf(pfile,"Tworzenie 1000 elementowego drzewa\n");
  for(int i=0;i<1000;i++){
    insert(root,randstring(6),randstring(6),randstring(6),randstring(6),randstring(6),randstring(6));
  }

  end_clock(pfile);

  fprintf(pfile,"Dodawanie pojedynczego noda do drzewa 1000 elementowego\n");
  start_clock();
  insert(root,randstring(6),randstring(6),randstring(6),randstring(6),randstring(6),randstring(6));
  end_clock(pfile);

}

void creatingTreePes(FILE*pfile){

  BSTNode**root=malloc(sizeof(BSTNode*));
  *root = NULL;



  for(int i=0;i<5000;i++){
    insert(root,"a","a","a","a","a","a");
  }
  insert(root,"m","m","m","m","m","m");

  fprintf(pfile,"Usuwanie node z drzewa - wersja pesymistyczna\n");
  start_clock();
  *root=delete(*root,"m");
  end_clock(pfile);

  fprintf(pfile,"Usuwanie node z drzewa - wersja optymistyczna\n");
  start_clock();
  *root=delete(*root,"a");
  end_clock(pfile);

  fprintf(pfile, "Usuwanie całego drzewa\n");
  start_clock();
    deleteTree(*root);
    end_clock(pfile);



}

void creatingList(FILE*pfile){

  fprintf(pfile,"Tworzenie listy 100000 elementowej\n");
  start_clock();
  list_t*list=createList();
  for(int i=0;i<10000;i++){
    addNodeEnd(list,randstring(10),randstring(10),randstring(10),randstring(10),randstring(10),randstring(10));
  }
  end_clock(pfile);

  start_clock();
  addNodeEnd(list,randstring(10),randstring(10),randstring(10),randstring(10),randstring(10),randstring(10));
  fprintf(pfile,"Dodawanie pojedynczego noda\n");
  end_clock(pfile);

}

void deleteFromEmptyList(FILE*pfile){
  fprintf(pfile, "Usuwanie z pustej listy - optymistyczne\n" );
  start_clock();
  list_t*list=createList();
  deleteContact(list,"a","b");
  end_clock(pfile);
}

void deleteFromList(FILE*pfile){

  fprintf(pfile,"Usuwanie z listy - wersja pesymistyczna\n");
  list_t*list=createList();
  for(int i=0;i<1000;i++){
    addNodeEnd(list,"a","a","a","a","a","a");
  }
  addNodeEnd(list,"b","b","b","b","b","b");
  start_clock();
  deleteContact(list,"b","b");
  end_clock(pfile);
}

void rebuildList(FILE*pfile){

  fprintf(pfile,"Przebudowywanie listy\n");
  list_t*list=createList();
  for(int i=0;i<1000;i++){
    addNodeEnd(list,randstring(10),randstring(10),randstring(10),randstring(10),randstring(10),randstring(10));
  }
  start_clock();
  list_t*sorted=createList();
  sorted=selection_sort(list,1);
  end_clock(pfile);
}

int main() {


  FILE * pfile;
  pfile = fopen ("myfile.txt","w");
  creatingTree(pfile);
  creatingTreePes(pfile);
  creatingList(pfile);
  deleteFromEmptyList(pfile);
  deleteFromList(pfile);
  rebuildList(pfile);

  fclose (pfile);


}
