#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "global.h"

LISTINFO* AllocateUsertype( )
{
	LISTINFO* pItem = (LISTINFO*)malloc( sizeof( LISTINFO ) );
	int* t = (int*)malloc( 2*sizeof( int ) );
	if( !t ) return NULL;
	memset( t, 0, 2*sizeof( int ) );
	pItem -> nKey = 0;
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
	int key1 = ((LISTINFO*)pItem1)->nKey;
	int key2 = ((LISTINFO*)pItem2)->nKey;
	if( key1==key2 ) return 0;
	if( key1>key2 ) return 1;
	return -1;
}
void PrintItem( LISTINFO* pItem )
{
	printf( "nKey: %d\tpTab: %d %d \n", pItem->nKey, pItem->pTab[0], pItem->pTab[1] );
}