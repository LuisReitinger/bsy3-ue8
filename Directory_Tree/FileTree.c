///////////////////////////////////////////////////////////////////////
// Workfile:      FileTree.c
// Author:        Luis Reitinger
// Date:          06.12.2022
// Description:   Module for saving multiple directory-trees and
//                searching in them.
///////////////////////////////////////////////////////////////////////
#include "FileTree.h"
#include <string.h>
#include <dirent.h>
#include <ftw.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static short const OK = 0;

static char const * const cErrPathLength = "error: path too long\n";
static char const * const cErrEmptyList = "error: empty list\n";
static char const * const cErrNotFound = "error: directory to remove not found\n";
static char const * const cErrNullptr = "error: nullptr\n";
static char const * const cErrFTW = "error in ftw()\n";
static char const * const cSearchFile = "suche %s in %s:\n";

// struct for list node
struct TNode{
   char * directory;
   struct TNode * pNext;
};

// pointer for managing the list
static struct TNode * pHead = NULL;

// filename to search in directories
static char * file2search = "";

// creates a new node for the list
static struct TNode * MakeNode(char const * dir)
{
   // check for maximum length of directory
   if (strlen(dir) > MAXNAMLEN)
   {
      fputs(cErrPathLength, stderr);
      return NULL;
   }

   // allocate memory for new directory
   struct TNode* pNewNode = (struct TNode*)malloc(sizeof(struct TNode));

   // check if allocation was successful
   if (pNewNode != NULL)
   {
      pNewNode->directory = dir;
      pNewNode->pNext = NULL;
   }

   return pNewNode;
}

// searches the given directory
// returns the found node or NULL if not found
static struct TNode* Search(char const* dir)
{
   if (pHead != NULL)
   {
      struct TNode* pNode = pHead;

      // search for node
      while (pNode != NULL && strcmp(pNode->directory, dir) != OK)
      {
         pNode = pNode->pNext;
      }

      return pNode;
   }
   else
   {
      fputs(cErrEmptyList, stderr);
      return NULL;
   }
}

// finds the predecessor of the given node
static struct TNode* Predecessor(struct TNode const * const node)
{
   if (node != NULL)
   {
      struct TNode* pPred = pHead;

      while (pPred != NULL && pPred->pNext != node) {
         pPred = pPred->pNext;
      }
      return pPred;
   }
   else
   {
      fputs(cErrNullptr, stderr);
      return NULL;
   }
}

// compares given directory + filename to the file2search
// status is in this case redundant, but necessary for the function's interface
static int Compare(const char * filename, const struct stat * status, int flag)
{
   assert(filename != NULL && status != NULL);

   // find last entity of path
   char * pos = strrchr(filename, '/') + 1;

   if (strcmp(pos, file2search) == OK && // name matches
        flag == FTW_F)                       // found item is a file
   {
      printf("%s\n", filename);
   }

   // always return 0, since we want to continue searching for the file
   return OK;
}

// searches the given file in the directories
void FindFile(const char* fileName)
{
   if (fileName != NULL)
   {
      if (pHead != NULL)
      {
         // save filename we want to search
         file2search = fileName;

         // node for iterating through the list
         struct TNode* pNode = pHead;

         // iterate through list
         while (pNode != NULL)
         {
            // print output
            printf(cSearchFile, fileName, pNode->directory);

            // check if ftw was successful
            // '0' for full depth in directory
            if (ftw(pNode->directory, Compare, 0) != OK)
            {
               fputs(cErrFTW, stderr);
            }
            pNode = pNode->pNext;
         }
      }
      else
      {
         fputs(cErrEmptyList, stderr);
      }
   }
   else
   {
      fputs(cErrNullptr, stderr);
   }
}

void AddDirectory(char const* dir)
{
   struct TNode* pNewNode = MakeNode(dir);

   // check if creation was successful
   if (pNewNode != NULL)
   {
      // empty list
      if (pHead == NULL)
      {
         pHead = pNewNode;
      }
      else
      {
         struct TNode* pNode = pHead;
         struct TNode* pPrev = pHead;

         // find last node
         while (pNode != NULL)
         {
            pPrev = pNode;
            pNode = pNode->pNext;
         }

         pPrev->pNext = pNewNode;
      }
   }
}

void RemoveDirectory(char const* dir)
{
   struct TNode* pFound = Search(dir);

   if (pFound != NULL)
   {
      if (pFound == pHead)
      {
         pHead = pHead->pNext;
      }
      else
      {
         Predecessor(pFound)->pNext = pFound->pNext;
      }
      // free memory
      free(pFound); pFound = NULL;
   }
   else
   {
      fputs(cErrNotFound, stderr);
   }
}

void RemoveAll()
{
   if (pHead != NULL)
   {
      struct TNode* pNode = NULL;

      while (pHead != NULL)
      {
         pNode = pHead;
         pHead = pNode->pNext;

         // free memory
         free(pNode); pNode = NULL;
      }
   }
   else
   {
      fputs(cErrEmptyList, stderr);
   }
}
