/*****************************************************************************/
/*                                                                           */
/*				   objdata.h				     */
/*                                                                           */
/*		 Handling object file data for the ld65 linker		     */
/*                                                                           */
/*                                                                           */
/*                                                                           */
/* (C) 1998-2011, Ullrich von Bassewitz                                      */
/*                Roemerstrasse 52                                           */
/*                D-70794 Filderstadt                                        */
/* EMail:         uz@cc65.org                                                */
/*                                                                           */
/*                                                                           */
/* This software is provided 'as-is', without any expressed or implied       */
/* warranty.  In no event will the authors be held liable for any damages    */
/* arising from the use of this software.                                    */
/*                                                                           */
/* Permission is granted to anyone to use this software for any purpose,     */
/* including commercial applications, and to alter it and redistribute it    */
/* freely, subject to the following restrictions:                            */
/*                                                                           */
/* 1. The origin of this software must not be misrepresented; you must not   */
/*    claim that you wrote the original software. If you use this software   */
/*    in a product, an acknowledgment in the product documentation would be  */
/*    appreciated but is not required.                                       */
/* 2. Altered source versions must be plainly marked as such, and must not   */
/*    be misrepresented as being the original software.                      */
/* 3. This notice may not be removed or altered from any source              */
/*    distribution.                                                          */
/*                                                                           */
/*****************************************************************************/



#ifndef OBJDATA_H
#define OBJDATA_H



/* common */
#include "coll.h"
#include "inline.h"
#include "objdefs.h"



/*****************************************************************************/
/*     	      	    	      	     Data		      		     */
/*****************************************************************************/



/* Values for the Flags field */
#define	OBJ_REF		0x0001 	       	/* We have a reference to this file */

/* Internal structure holding object file data */
typedef struct ObjData ObjData;
struct ObjData {
    ObjData*	     	Next;  		/* Linked list of all objects */
    unsigned            Name;  		/* Module name */
    unsigned            LibName;	/* Name of library */
    unsigned long       MTime;          /* Time of last modification */
    ObjHeader	 	Header;		/* Header of file */
    unsigned long  	Start;		/* Start offset of data in library */
    unsigned 	     	Flags;
    Collection          Files;		/* List of input files */
    Collection          Sections;  	/* List of all sections */
    Collection          Exports;       	/* List of all exports */
    Collection          Imports;   	/* List of all imports */
    Collection          DbgSyms;       	/* List of debug symbols */
    Collection          LineInfos;      /* List of line infos */
    unsigned            StringCount;    /* Count of strings */
    unsigned*           Strings;        /* List of global string indices */
    Collection          Assertions;     /* List of module assertions */
    Collection          Scopes;         /* List of scopes */
};



/* Collection containing used ObjData objects */
extern Collection       ObjDataList;



/*****************************************************************************/
/*     	      	    	      	     Code		  	   	     */
/*****************************************************************************/



ObjData* NewObjData (void);
/* Allocate a new structure on the heap, insert it into the list, return it */

void FreeObjData (ObjData* O);
/* Free an ObjData object. NOTE: This function works only for unused object
 * data, that is, ObjData objects that aren't used because they aren't
 * referenced.
 */

void FreeObjStrings (ObjData* O);
/* Free the module string data. Used once the object file is loaded completely
 * when all strings are converted to global strings.
 */

void InsertObjData (ObjData* O);
/* Insert the ObjData object into the collection of used ObjData objects. */

void InsertObjGlobals (ObjData* O);
/* Insert imports and exports from the object file into the global import and
 * export lists.
 */

unsigned MakeGlobalStringId (const ObjData* O, unsigned Index);
/* Convert a local string id into a global one and return it. */

const char* GetObjFileName (const ObjData* O);
/* Get the name of the object file. Return "[linker generated]" if the object
 * file is NULL.
 */

#if defined(HAVE_INLINE)
INLINE int ObjHasFiles (const ObjData* O)
/* Return true if the files list does exist */
{
    return (O != 0 && CollCount (&O->Files) != 0);
}
#else
#  define ObjHasFiles(O)       ((O) != 0 && CollCount (&(O)->Files) != 0)
#endif



/* End of objdata.h */

#endif





