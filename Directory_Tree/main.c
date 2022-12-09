#include <stdio.h>
#include <stdlib.h>
#include "FileTree.h"

int main()
{
   AddDirectory("/home/bsy3/Workspace/Codeblocks/");
   AddDirectory("/home/bsy3/Workspace/gcc/");
   AddDirectory("");


   FindFile("main.c");
   RemoveAll();
   return 0;
}
