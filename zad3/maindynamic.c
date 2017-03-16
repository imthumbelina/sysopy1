#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <sys/times.h>
#include <time.h>
 #include <sys/resource.h>
 #include <sys/time.h>
#include <dlfcn.h>

struct rusage rusage_start,rusage_end;
struct timeval user_start,user_end,system_start,system_end,real_start,real_end;
//long double user_sum, system_sum, real_sum;

void start_clock(){
 getrusage(RUSAGE_SELF,&rusage_start);
 gettimeofday(&real_start,NULL);
}
void end_clock(FILE*file){
 gettimeofday(&real_end,NULL);
 getrusage(RUSAGE_SELF,&rusage_end);

 user_start=rusage_start.ru_utime; //total amount of time spend in user mode
 user_end=rusage_end.ru_utime;
 system_start=rusage_start.ru_stime;
 system_end=rusage_end.ru_stime;
//  long double se = (system_end.tv_sec - system_start.tv_sec)*1000000L + system_end.tv_usec - system_start.tv_usec;
 fprintf(file,"system time %09ld mikrosekund \n",((system_end.tv_sec - system_start.tv_sec)*1000000L) + system_end.tv_usec - system_start.tv_usec);
 fprintf(file,"user time %09ld mikrosekund \n",((user_end.tv_sec - user_start.tv_sec)*1000000L+ user_end.tv_usec) - user_start.tv_usec);
 fprintf(file,"real time %09ld mikrosekund \n\n",((real_end.tv_sec - real_start.tv_sec)*1000000L + real_end.tv_usec) - real_start.tv_usec);


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

void creatingTree(void*handle,FILE*pfile){

  bool (*insert)(BSTNode**,char*,char*,char*,char*,char*,char*)=dlsym(handle,"insert");
  BSTNode* (*delete)(BSTNode*,char*)=dlsym(handle,"delete");


   char* error = dlerror();
    if (error != NULL) {
      fprintf(stderr, "%s\n", error);
   }

 fprintf(pfile,"Wstawianie do drzewa 10000 elementow\n" );
 start_clock();

 BSTNode**root=malloc(sizeof(BSTNode*));
 *root = NULL;

  for(int i=0;i<10000;i++){
    (*insert)(root,randstring(6),randstring(6),randstring(6),randstring(6),randstring(6),randstring(6));
  }

   end_clock(pfile);

   fprintf(pfile,"Dodawanie pojedynczego noda do drzewa 1000 elementowego\n");
   start_clock();
   (*insert)(root,randstring(6),randstring(6),randstring(6),randstring(6),randstring(6),randstring(6));
   end_clock(pfile);

}

void creatingTreePes(void*handle,FILE*pfile){

  bool (*insert)(BSTNode**,char*,char*,char*,char*,char*,char*)=dlsym(handle,"insert");
  BSTNode* (*delete)(BSTNode*,char*)=dlsym(handle,"delete");
  void (*deleteTree)(BSTNode*)=dlsym(handle,"deleteTree");

  BSTNode**root=malloc(sizeof(BSTNode*));
  *root = NULL;

  for(int i=0;i<5000;i++){
    (*insert)(root,"a","a","a","a","a","a");
  }
  (*insert)(root,"m","m","m","m","m","m");

  fprintf(pfile,"Usuwanie node z drzewa - wersja pesymistyczna\n");
  start_clock();
  *root=(*delete)(*root,"m");
  end_clock(pfile);

  fprintf(pfile,"Usuwanie node z drzewa - wersja optymistyczna\n");
  start_clock();
  *root=(*delete)(*root,"a");
  end_clock(pfile);

  fprintf(pfile, "Usuwanie całego drzewa\n");
  start_clock();
    (*deleteTree)(*root);
    end_clock(pfile);


}


void creatingList(void*handle,FILE*pfile){
   list_t*(*createList)(void)=dlsym(handle,"createList");

   void(*addNodeEnd)(list_t*,char*,char*,char*,char*,char*,char*);
   addNodeEnd=dlsym(handle,"addNodeEnd");
   fprintf(pfile,"Tworzenie 10000 elementowej listy\n");
   start_clock();
   list_t*list=createList();
   for(int i=0;i<1000;i++){
     (*addNodeEnd)(list,randstring(10),randstring(10),randstring(10),randstring(10),randstring(10),randstring(10));
  }

  end_clock(pfile);

 start_clock();
  (*addNodeEnd)(list,randstring(10),randstring(10),randstring(10),randstring(10),randstring(10),randstring(10));
  fprintf(pfile,"Dodawanie pojedynczego noda\n");
  end_clock(pfile);
//
}


void deleteFromList(void*handle,FILE*pfile){
  list_t*(*createList)(void)=dlsym(handle,"createList");
  void(*addNodeEnd)(list_t*,char*,char*,char*,char*,char*,char*);
  addNodeEnd=dlsym(handle,"addNodeEnd");
  void(*deleteContact)(list_t*,char*,char*)=dlsym(handle,"deleteContact");

  list_t*list=createList();
  fprintf(pfile,"Usuwanie z listy -wersja pesymistyczna\n");
  for(int i=0;i<1000;i++){
    addNodeEnd(list,"a","a","a","a","a","a");
  }
  addNodeEnd(list,"k","k","k","k","k","k");
  start_clock();
  deleteContact(list,"k","k");
  end_clock(pfile);
}

void rebuildList(void*handle,FILE*pfile){

  void(*addNodeEnd)(list_t*,char*,char*,char*,char*,char*,char*)=dlsym(handle,"addNodeEnd");
  list_t*(*createList)(void)=dlsym(handle,"createList");
  list_t*(*selection_sort)(list_t*,int)=dlsym(handle,"selection_sort");

  fprintf(pfile,"Sortowanie listy 1000 elementowej\n");

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

   void * handle;
   handle=dlopen("liblist.so", RTLD_LAZY);
   if(handle == NULL){
     printf("%s","Couldnt load lib");
   }
  FILE * pFile;
  pFile = fopen ("myfile.txt","a+");
  fprintf(pFile,"BIBLIOTEKA ŁADOWANA DYNAMICZNIE\n");
  fprintf(pFile,"IMPLEMENTATION TESTS\n");

  creatingTree(handle,pFile);
  creatingTreePes(handle,pFile);
  creatingList(handle,pFile);
  deleteFromList(handle,pFile);
  rebuildList(handle,pFile);
  fclose (pFile);
  dlclose(handle);


}
