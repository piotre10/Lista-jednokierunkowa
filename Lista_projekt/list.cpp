#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "global.h"

ListItem* CreateList( )
{
	return (ListItem*)calloc(1,sizeof(ListItem));
}
int InsertFront( ListItem* pList, LISTINFO* pInfo ) 
{
	return Insert( pList, pInfo );
}
int Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	if( !pAfter ) return 0;
	ListItem* pItem = (ListItem*)calloc( 1, sizeof( ListItem ) );
	if( !pItem ) return 0;
	pItem->pInfo = pInfo;
	pItem->pNext = pAfter->pNext;
	pAfter->pNext = pItem;
	return 1;
}
LISTINFO* RemoveFront( ListItem* pList )
{
	return Remove( pList );
}
LISTINFO* Remove( ListItem* pAfter )
{
	if( IsEmpty(pAfter) ) return NULL;
	ListItem* pTemp = pAfter->pNext;
	pAfter->pNext = pTemp->pNext;
	LISTINFO* pInfo = pTemp->pInfo;
	free( pTemp );
	return pInfo;

}
LISTINFO* Front( ListItem* pList )
{
	if( !pList ) return NULL;
	return pList->pNext->pInfo;
}
int IsEmpty( ListItem* pList )
{
	return !( pList && pList->pNext );
}
void ClearList( ListItem* pList, void ( *RemoveItem )( const void* ) )
{
	while( !IsEmpty(pList ))
	{
		RemoveItem( RemoveFront( pList ) );
	}
}
void RemoveList( ListItem** pList, void ( *RemoveItem )( const void* ) )
{
	ClearList( *pList, RemoveItem );
	free( *pList );
	*pList = NULL;
}
void SortList( ListItem* pList, int( *Compare )( const void*, const void* ) )
{
	ListItem* pFirst = pList;

	while( !IsEmpty(pFirst) )
	{
		ListItem* pMin = pFirst;
		ListItem* pCurr = pFirst;
		while(!IsEmpty(pCurr))
		{
			if( Compare( pMin->pNext->pInfo, pCurr->pNext->pInfo )==1 ) pMin = pCurr;
			pCurr = pCurr->pNext;
		}
		if( pFirst!=pMin )
		{
			pCurr = pMin->pNext->pNext;
			pMin->pNext->pNext = pFirst->pNext;
			pFirst->pNext = pMin->pNext;
			pMin->pNext = pCurr;
		}
		pFirst = pFirst->pNext;
	}
}
ListItem* Find( ListItem* pList, LISTINFO pItem, ListItem** pPrev, int( *Compare )( const void*, const void* ) )
{
	*pPrev = pList;
	while( !IsEmpty( *pPrev )&&( Compare( ( *pPrev )->pNext->pInfo, &pItem ) ) )
		*pPrev = ( *pPrev )->pNext;

	return ( ( *pPrev )->pNext ) ? ( *pPrev )->pNext : *pPrev = NULL;

}