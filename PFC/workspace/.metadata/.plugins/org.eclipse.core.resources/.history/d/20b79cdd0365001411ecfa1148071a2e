#ifndef   __VI_PROTOCOL_H__
#define   __VI_PROTOCOL_H__

/*
 * File: VI_protocol.h
 * Date (last revision): 4/11/2014
 *
 * Description: header and definition of functions, structs, constants...
 *				of the associated file VI_protocol.c
 *
 */


//---------------------------------------------------------------------------
// Protocol's constants

// Client (PC) Commands
#define CMD_ACTIVATE_FREQ_METER 100
#define CMD_FREQ_REQUEST 101
#define CMD_NFREQ_NODES 102
#define CMD_AV_SIMPLE 103
#define CMD_AV_WEIGHTED 104
#define CMD_AV_EXP 105
#define CMD_ACTIVATE_FUNC_GEN 106
#define CMD_RAM_VALUES 107
#define CMD_FG_SQUARE 108
#define CMD_FG_NON_SQUARE 109
#define CMD_FG_CHANGE_FREQ 110
#define CMD_FG_CHANGE_TON 111
#define CMD_RESET 112

// Server (board) Commands
#define CMD_FREQ_ANSWER 113

//---------------------------------------------------------------------------
// VI_protocol (application protocol over UDP) to control the board's instrumentation
typedef struct VI_protocol
{
	int command;
	char data[36];
}VI_protocol_t;


//---------------------------------------------------------------------------
// Definition of Functions


#endif
