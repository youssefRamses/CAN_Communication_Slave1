 /******************************************************************************
 *
 * Module: Det
 *
 * File Name: Det.h
 *
 * Description:  Det stores the development errors reported by other modules.
 *
 * Author: michael samir
 ******************************************************************************/

#ifndef DET_H
#define DET_H


/* Standard AUTOSAR types */
#include "Std_Types.h"

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
Std_ReturnType Det_ReportError( uint16 ModuleId,
                                uint8 InstanceId,
                                uint8 ApiId,
		                uint8 ErrorId );

#endif /* DET_H */
