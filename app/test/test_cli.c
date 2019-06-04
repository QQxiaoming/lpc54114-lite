#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS_CLI.h"


static BaseType_t prvUnameCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
    memset( pcWriteBuffer, 0x00, xWriteBufferLen );
    strcpy( pcWriteBuffer, "FreeRTOS" );

	return pdFALSE;
}


static const CLI_Command_Definition_t xUname =
{
	"uname",
	"\r\nuname :\r\nEchos uname in turn\r\n",
	prvUnameCommand,
	0
};


static BaseType_t prvEchoCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
    const char *pcParameter;
    BaseType_t xParameterStringLength;

    pcParameter = FreeRTOS_CLIGetParameter(pcCommandString,	1, &xParameterStringLength);

    configASSERT( pcParameter );

    memset( pcWriteBuffer, 0x00, xWriteBufferLen );
    strncat( pcWriteBuffer, pcParameter, ( size_t ) xParameterStringLength );

	return pdFALSE;
}


static const CLI_Command_Definition_t xEcho =
{
	"echo",
	"\r\necho <param> :\r\nEchos each in turn\r\n",
	prvEchoCommand,
	1
};


void vRegisterCLICommands( void )
{
	FreeRTOS_CLIRegisterCommand( &xUname );	
	FreeRTOS_CLIRegisterCommand( &xEcho );
}
