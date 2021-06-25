#include "global.h"
#include "list.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define SIZE 30

LISTINFO* AllocateUsertype( );
void FreeUsertype( const void* pItem );
int CompareUsertype( const void* pItem1, const void* pItem2 );
void PrintItem( LISTINFO* Item );
void PrintList( ListItem* pList );

int main( )
{
	ListItem* pList = CreateList( );
	if( !pList )
	{
		printf( "Error: Allocating list type went wrong \n" );
		return -1;
	}
	srand( (unsigned)time( NULL ) );
	for( int i = 0; i<SIZE; i++ )
	{
		LISTINFO* pInfo = AllocateUsertype( );
		if( !pInfo )
		{
			printf( "Error1: Allocating user type went wrong \n" );
			return -3;
		}
		pInfo->nKey = rand( )%50+1;
		pInfo->pTab[0] = i+1;
		InsertFront( pList, pInfo );
	}
	printf( "Starting list: \n" );
	PrintList( pList );

	SortList( pList, CompareUsertype );
	printf( "List after sorting: \n" );

	PrintList( pList );

	ListItem* pPrev = (ListItem*)calloc( 1, sizeof( ListItem ) );
	if( !pPrev )
	{
		printf( "Error1: Allocating list type went wrong \n" );
		return -2;
	}
	const int key_to_find = 20;
	const int key_to_insert = 30;
	LISTINFO* pInfo = AllocateUsertype( );
	if( !pInfo )
	{
		printf( "Error2: Allocating user type went wrong \n" );
		return -3;
	}
	pInfo->nKey = key_to_find;
	if( !Find( pList, *pInfo, &pPrev, CompareUsertype ) )
	{
		printf( "There is no such an item in the list \n" );
	}
	else
	{
		pInfo->nKey = key_to_insert;
		if( !Insert( pPrev, pInfo ) ) printf( "Error1: Insertion failed \n" );
		printf( "List after finding and inseritng \n" );
		PrintList( pList );
		pPrev = pPrev->pNext;
		Remove( pPrev );
	}
	ClearList( pList, FreeUsertype );
	pInfo = AllocateUsertype( );
	if( !pInfo )
	{
		printf( "Error3: Allocating user type went wrong" );
		return -3;
	}
	pInfo->nKey = 25;
	LISTINFO* pInfo2 = AllocateUsertype( );
	if( !pInfo2 )
	{
		printf( "Error4: Allocating user type went wrong" );
		return -3;
	}
	pInfo2->nKey = 230;
	if( !InsertFront( pList, pInfo ) ) printf( "Error2: Front insertion failed \n" );
	if( !InsertFront( pList, pInfo2 ) )printf( "Error3: Front insertion failed \n" );
	printf( "List at the end: \n" );
	PrintList( pList );
	RemoveList( &pList, FreeUsertype );
	return 0;
}

LISTINFO* AllocateUsertype( )
{
	LISTINFO* pItem = (LISTINFO*)calloc(1, sizeof( LISTINFO ) );
	int* t = (int*)calloc( 2, sizeof( int ) );
	if( !t ) return NULL;
	pItem->pTab = t;
	return pItem;
}
void FreeUsertype( const void* pItem )
{
	LISTINFO* pNew = (LISTINFO*)pItem;
	free( pNew->pTab );
	free( pNew );
}
int CompareUsertype( const void* pItem1, const void* pItem2 )
{
	if( ( (LISTINFO*)pItem1 )->nKey==( (LISTINFO*)pItem2 )->nKey ) return 0;
	if( ( (LISTINFO*)pItem1 )->nKey>( (LISTINFO*)pItem2 )->nKey ) return 1;
	return -1;
}
void PrintItem( LISTINFO* pItem )
{
	printf( "nKey: %d\tpTab: %d %d \n", pItem->nKey, pItem->pTab[0], pItem->pTab[1] );
}
void PrintList( ListItem* pList )
{
	printf( "####### List: #########\n" );
	for( int i = 1; ( pList = pList->pNext )!=NULL; i++ )
	{
		printf( "%d. Element: ", i );
		PrintItem( pList->pInfo );
	}
	printf( "########################\n" );
}