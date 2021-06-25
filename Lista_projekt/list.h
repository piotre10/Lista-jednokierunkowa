#ifndef _LIST_MODULE_

#define _LIST_MODULE_
#include "global.h"

typedef struct tagListItem
{
	LISTINFO* pInfo;
	tagListItem* pNext;
}ListItem;

ListItem* CreateList( );
int InsertFront( ListItem* pList, LISTINFO* pInfo );
int Insert( ListItem* pAfter, LISTINFO* pInfo );
LISTINFO* RemoveFront(ListItem* pList );
LISTINFO* Remove( ListItem* pAfter );
LISTINFO* Front( ListItem* pList );
int IsEmpty( ListItem* pList );
void ClearList( ListItem* pList, void (*RemoveItem)( const void* ));
void RemoveList( ListItem** pList, void ( *RemoveItem )( const void* ) );
void SortList( ListItem* pList, int( *Compare )( const void*, const void* ) );
ListItem* Find( ListItem* pList, LISTINFO pItem, ListItem** pPrev, int(* Compare )( const void*, const void* ) );
#endif