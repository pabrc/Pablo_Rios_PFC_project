# -*- coding: utf-8 -*-
"""
Created on Wed Oct 29 11:34:19 2014

@author: Pablo

File: vi_protocol.py

Description: Contains the commands and functions (assemble and disassemble)
                of the VI_protocol

"""

import struct

# Client (PC) commands
CMD_ACTIVATE_FREQ_METER =   100   
CMD_FREQ_REQUEST        =   101         
CMD_NFREQ_NODES         =   102
CMD_AV_SIMPLE           =   103
CMD_AV_WEIGHTED         =   104
CMD_AV_EXP              =   105
CMD_ACTIVATE_FUNC_GEN   =   106
CMD_RAM_VALUES          =   107
CMD_FG_SQUARE           =   108
CMD_FG_NON_SQUARE       =   109
CMD_FG_CHANGE_FREQ      =   110
CMD_FG_CHANGE_TON       =   111
CMD_RESET               =   112

# Server (board) commands
CMD_FREQ_ANSWER         =   113



# Commands that are not associated to data in the data field of the protocol
command_empty = [CMD_ACTIVATE_FREQ_METER,
                 CMD_FREQ_REQUEST,
                 CMD_AV_SIMPLE,
                 CMD_AV_WEIGHTED,
                 CMD_AV_EXP,
                 CMD_ACTIVATE_FUNC_GEN,
                 CMD_FG_SQUARE,
                 CMD_FG_NON_SQUARE,
                 CMD_RESET]

# Commands that are associated to 1 data (4 bytes == int, float)
#   in the data field
command_1data = [CMD_NFREQ_NODES,
                 CMD_FG_CHANGE_FREQ,
                 CMD_FG_CHANGE_TON,
                 CMD_FREQ_ANSWER]
                 
# Command associated to the 36 values of the CCP's RAM                 
command_moredata = [CMD_RAM_VALUES]



def assemble_packet(fields):
    """Assenmble the packet:
        -------------------------------------
        | command |         data            |
        -------------------------------------
        
    command: command of the VI_protocol
    data: int, float or anything
    
    return: the packet (str) with a length of 40 bytes:
            command ->  4 bytes
            data    -> 36 bytes
    
    """
    
    if not fields:
        raise 'NoArguments' # the list is empty
        
    # fields[0] is the command
    # fields[1] is the num
    # fields[1-37] are the RAM values if command is CMD_RAM_VALUES
    packet = ""
    if fields[0] in command_empty:
        
        # Command + 36 zeros to fill all the packet (40 bytes)
        packet = struct.pack("!i", fields[0]) + str(bytearray(36))
        #print repr(packet)
        
    elif fields[0] in command_1data:
          
        # Command + num + 32 zeros to fill all the packet (40 bytes)
        #   num is sent as a 'unsigned long'== 'L'
        packet = struct.pack("!ii", fields[0], fields[1]) + str(bytearray(32))
        #print repr(packet)
        
    elif fields[0] in command_moredata:
        
        if len(fields) != 37:
            raise 'InvalidVIData'
            
        # Command + 36 values of the CCP's RAM
        packet = struct.pack("!i", fields[0])
        for i in range(1, 37):
            packet = packet + struct.pack("!B", fields[i])
        #print repr(packet)

    else:
        raise 'InvalidVICommand'
               
    return packet


def disassemble_packet(packet):
    """Disassemble the received packet (40 bytes)
    
    It returns a list with its content
    
    """
    
    # The only packet received by the server is the command CMD_FREQ_ANSWER
    fields = []
    
    # Command + frequency + 32 zeros
    fields = struct.unpack("!if32c", packet)
    
    return fields
    

