#include <stdio.h>
#include <stdlib.h>
#include "FileTree.h"

int main()
{
   // search for in empty list
   printf("=== Search in empty list: ===\n");
   FindFile("main.c");
   printf("\n");

   // remove non existent directory
   printf("=== remove non existent directory ===\n");
   RemoveDirectory("/home/");
   printf("\n");

   // remove-all from emtpy list
   printf("=== remove-all from empty list ===\n");
   RemoveAll();
   printf("\n");

   // add directories
   AddDirectory("/home/bsy3/Workspace/Codeblocks/");
   AddDirectory("/home/bsy3/Workspace/gcc/");

   // add empty directory
   AddDirectory("");

   // find file in all directories
   printf("=== find file in all directories ===\n");
   FindFile("main.c");
   printf("\n");

   // remove directory and search again
   printf("=== remove 2 directories and search again ===\n");
   RemoveDirectory("/home/bsy3/Workspace/gcc/");
   RemoveDirectory("");
   FindFile("main.c");
   printf("\n");

   // search for non-existent file
   printf("=== search for non-existent file ===\n");
   FindFile("adsf.x");
   printf("\n");

   // clear list
   RemoveAll();
   return 0;
}
