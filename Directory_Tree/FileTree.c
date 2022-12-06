///////////////////////////////////////////////////////////////////////
// Workfile:      FileTree.c
// Author:        Luis Reitinger
// Date:          06.12.2022
// Description:   Module for saving multiple directory-trees and
//                searching in them.
///////////////////////////////////////////////////////////////////////
#include "FileTree.h"

// struct for list node
typedef struct {
   char directory[MAX];
   TNode * pNext;
} TNode;
