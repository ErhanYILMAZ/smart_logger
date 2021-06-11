/*----------------------------------------------------------------------------/
/  FatFs - FAT file system module  R0.11                 (C)ChaN, 2015        /
/-----------------------------------------------------------------------------/
/ FatFs module is a free software that opened under license policy of
/ following conditions.
/
/ Copyright (C) 2015, ChaN, all right reserved.
/
/ 1. Redistributions of source code must retain the above copyright notice,
/    this condition and the following disclaimer.
/
/ This software is provided by the copyright holder and contributors "AS IS"
/ and any warranties related to this software are DISCLAIMED.
/ The copyright owner or contributors be NOT LIABLE for any damages caused
/ by use of this software.
/----------------------------------------------------------------------------*/

#include "ff.h"
#include "FATFS/fatfs.h"

#if _FS_REENTRANT

  extern FATFS_MUTEXINFO_t FATFS_MutexInfo[FATFS_VOLUMES];

  extern volatile osMutexId FATFS_MutexProtectId;

/*------------------------------------------------------------------------*/
/* Create a Synchronization Object                                        */
/*------------------------------------------------------------------------*/
/* This function is called in f_mount function to create a new
/  synchronization object, such as semaphore and mutex. When a zero is
/  returned, the f_mount function fails with FR_INT_ERR.
*/
int ff_cre_syncobj (	/* TRUE:Function succeeded, FALSE:Could not create due
							to any error */
	 BYTE vol,			/* Corresponding logical drive being processed */
	 _SYNC_t *sobj		/* Pointer to return the created sync object */
 )
 {
   uint32_t MutexCount = 0;
   int RetVal = -1;
   osStatus SemStatus;
   /* Check for available Mutexes. */
   /* Take Mutex */
   SemStatus = osMutexWait(FATFS_MutexProtectId,  osWaitForever);
   if (osOK == SemStatus)
   {
	 for (MutexCount=0; MutexCount<FATFS_VOLUMES; MutexCount++)
	 {
	   if(FATFS_MutexInfo[MutexCount].MutexStatus == FATFS_MUTEXSTATUS_FREE)
	   {
		 *sobj = FATFS_MutexInfo[MutexCount].MutexId;
		 /* Remove the allocated mutex from free list*/
		 FATFS_MutexInfo[MutexCount].MutexStatus =  FATFS_MUTEXSTATUS_BUSY;
		 RetVal =  (int)*sobj;
		 break;
	   }
	 }/* End of "for loop"*/
	 SemStatus = osMutexRelease (FATFS_MutexProtectId);
	 if (SemStatus != osOK)
	 {
	   RetVal = -1;
	 } /* End of "if (osOK != SemStatus)"*/
   } /* End of " if ((uint32_t)osOK != SemStatus)"*/
   return RetVal;
 }

 /*------------------------------------------------------------------------*/
 /* Delete a Synchronization Object                                        */
 /*------------------------------------------------------------------------*/
 /* This function is called in f_mount function to delete a synchronization
 /  object that created with ff_cre_syncobj function. When a zero is
 /  returned, the f_mount function fails with FR_INT_ERR.
 */

 int ff_del_syncobj (	/* TRUE:Function succeeded, FALSE:Could not delete due
							to any error */
	 _SYNC_t sobj		/* Sync object tied to the logical drive to be deleted*/
 )
 {
   uint32_t MutexCount = 0;
   for (MutexCount=0; MutexCount<FATFS_VOLUMES; MutexCount++)
   {
	 if(FATFS_MutexInfo[MutexCount].MutexId == sobj)
	 {
	   /* Remove the allocated mutex from free list*/
	   FATFS_MutexInfo[MutexCount].MutexStatus = FATFS_MUTEXSTATUS_FREE;
	 }
   }
   /* Return Status will be always 1 */
   return 1;
 }

 /*------------------------------------------------------------------------*/
 /* Request Grant to Access the Volume                                     */
 /*------------------------------------------------------------------------*/
 /* This function is called on entering file functions to lock the volume.
 /  When a zero is returned, the file function fails with FR_TIMEOUT.
 */

 int ff_req_grant (	/* TRUE:Got a grant to access the volume, FALSE:Could not
						get a grant */
	 _SYNC_t sobj	/* Sync object to wait */
 )
 {
   osStatus Status;
   int RetVal = 1;
   /* Wait till the Mutex becomes available  */
   Status = (int)osMutexWait(sobj, _FS_TIMEOUT);
   if (Status != osOK )
   {
	 RetVal = 0;
   }
   return RetVal;
 }

 /*------------------------------------------------------------------------*/
 /* Release Grant to Access the Volume                                     */
 /*------------------------------------------------------------------------*/
 /* This function is called on leaving file functions to unlock the volume.
 */

 void ff_rel_grant (
	 _SYNC_t sobj	/* Sync object to be signaled */
 )
 {
   osMutexRelease (sobj);
 }

#endif

#if _USE_LFN == 3	/* LFN with a working buffer on the heap */
/*------------------------------------------------------------------------*/
/* Allocate a memory block                                                */
/*------------------------------------------------------------------------*/
/* If a NULL is returned, the file function fails with FR_NOT_ENOUGH_CORE.
*/

void* ff_memalloc (	/* Returns pointer to the allocated memory block */
	UINT msize		/* Number of bytes to allocate */
)
{
  return malloc(msize);	/* Allocate a new memory block with POSIX API */
}


/*------------------------------------------------------------------------*/
/* Free a memory block                                                    */
/*------------------------------------------------------------------------*/

void ff_memfree (
	void* mblock	/* Pointer to the memory block to free */
)
{
  free(mblock);	/* Discard the memory block with POSIX API */
}

#endif
