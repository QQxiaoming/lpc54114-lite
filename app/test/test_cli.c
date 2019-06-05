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
	"uname:\t\t\t\tEchos uname in turn\r\n",
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
	"echo <param>:\t\t\tEchos each in turn\r\n",
	prvEchoCommand,
	1
};


static BaseType_t prvPsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
	const char *const pcHeader = "Task                    State  Priority Stack	#\r\n*************************************************\r\n";

	strcpy( pcWriteBuffer, pcHeader );
	vTaskList( pcWriteBuffer + strlen( pcHeader ) );
	pcWriteBuffer[strlen(pcWriteBuffer)-2] = '\0';

	return pdFALSE;
}


static const CLI_Command_Definition_t xTaskPs =
{
	"ps",
	"\ps:\t\t\t\tshowing the state of each FreeRTOS task\r\n",
	prvPsCommand,
	0
};


void vRegisterCLICommands( void )
{
	FreeRTOS_CLIRegisterCommand( &xUname );	
	FreeRTOS_CLIRegisterCommand( &xEcho );
	FreeRTOS_CLIRegisterCommand( &xTaskPs );
}
