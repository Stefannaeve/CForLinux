// list.h: Lession 7, exercise 3
//
//
#ifndef __LIST_H__
#define __LIST_H__

#define OK      0
#define ERROR   1

// The list type:

typedef unsigned char BYTE;

typedef struct _LIST {
   struct _LIST *pNext;
   struct _LIST *pPrev;
   int iSze;
   BYTE byBuf[];
} LIST;

// Prototypes - functions return OK or ERROR.

int InsertInList (LIST **ppHead, LIST **ppTail,  void *pvData, int iSze);
int AddToList (LIST **ppHead, void *pvData, int iSze);
int RemoveFromList (LIST **ppHead, LIST *pToDelete);

#endif // ndef __LIST_H__
