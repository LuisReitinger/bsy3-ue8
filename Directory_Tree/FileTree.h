///////////////////////////////////////////////////////////////////////
// Workfile:      FileTree.h
// Author:        Luis Reitinger
// Date:          06.12.2022
// Description:   Module for saving multiple directory-trees and
//                searching in them.
///////////////////////////////////////////////////////////////////////
#ifndef FILETREE_H
#define FILETREE_H

//searches a file in all directories
void FindFile(const char* fileName);

//adds a directory to directory list
void AddDirectory(char const* dir);

//removes a directory
void RemoveDirectory(char const* dir);

//removes all directories
void RemoveAll();

#endif
