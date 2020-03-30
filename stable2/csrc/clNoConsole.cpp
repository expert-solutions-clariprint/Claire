/***********************************************************************/
/**  microCLAIRE                                       Yves Caseau     */
/**  clConsole.cpp.in                                                  */
/**  Copyright (C) 1994-99 Yves Caseau. All Rights Reserved.           */
/**  cf claire.h                                                       */
/***********************************************************************/

#include <claire.h>
#include <Kernel.h>
#include <Core.h>


// this is our main function
int main(int argc, char *argv[]) {
	if (startClaire(argc, argv) == 0)
		return 1;
	return 0; }
