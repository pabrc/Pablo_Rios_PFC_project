// (C) 2001-2013 Altera Corporation. All rights reserved.
// Your use of Altera Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Altera Program License Subscription 
// Agreement, Altera MegaCore Function License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Altera and sold by 
// Altera or its authorized distributors.  Please refer to the applicable 
// agreement for further details.


// $Id: //acds/rel/13.0sp1/ip/merlin/altera_irq_mapper/altera_irq_mapper.sv.terp#1 $
// $Revision: #1 $
// $Date: 2013/03/07 $
// $Author: swbranch $

// -------------------------------------------------------
// Altera IRQ Mapper
//
// Parameters
//   NUM_RCVRS        : 16
//   SENDER_IRW_WIDTH : 32
//   IRQ_MAP          : 0:14,1:13,2:4,3:2,4:0,5:1,6:5,7:11,8:7,9:8,10:9,11:10,12:3,13:12,14:15,15:6
//
// -------------------------------------------------------

`timescale 1 ns / 1 ns

module NIOSIImicro_irq_mapper
(
    // -------------------
    // Clock & Reset
    // -------------------
    input clk,
    input reset,

    // -------------------
    // IRQ Receivers
    // -------------------
    input                receiver0_irq,
    input                receiver1_irq,
    input                receiver2_irq,
    input                receiver3_irq,
    input                receiver4_irq,
    input                receiver5_irq,
    input                receiver6_irq,
    input                receiver7_irq,
    input                receiver8_irq,
    input                receiver9_irq,
    input                receiver10_irq,
    input                receiver11_irq,
    input                receiver12_irq,
    input                receiver13_irq,
    input                receiver14_irq,
    input                receiver15_irq,

    // -------------------
    // Command Source (Output)
    // -------------------
    output reg [31 : 0] sender_irq
);


    always @* begin
	sender_irq = 0;

        sender_irq[14] = receiver0_irq;
        sender_irq[13] = receiver1_irq;
        sender_irq[4] = receiver2_irq;
        sender_irq[2] = receiver3_irq;
        sender_irq[0] = receiver4_irq;
        sender_irq[1] = receiver5_irq;
        sender_irq[5] = receiver6_irq;
        sender_irq[11] = receiver7_irq;
        sender_irq[7] = receiver8_irq;
        sender_irq[8] = receiver9_irq;
        sender_irq[9] = receiver10_irq;
        sender_irq[10] = receiver11_irq;
        sender_irq[3] = receiver12_irq;
        sender_irq[12] = receiver13_irq;
        sender_irq[15] = receiver14_irq;
        sender_irq[6] = receiver15_irq;
    end

endmodule


