// (C) 2001-2012 Altera Corporation. All rights reserved.
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


// $Id: //acds/rel/12.1/ip/merlin/altera_merlin_router/altera_merlin_router.sv.terp#1 $
// $Revision: #1 $
// $Date: 2012/08/12 $
// $Author: swbranch $

// -------------------------------------------------------
// Merlin Router
//
// Asserts the appropriate one-hot encoded channel based on 
// either (a) the address or (b) the dest id. The DECODER_TYPE
// parameter controls this behaviour. 0 means address decoder,
// 1 means dest id decoder.
//
// In the case of (a), it also sets the destination id.
// -------------------------------------------------------

`timescale 1 ns / 1 ns

module nios_system_addr_router_001_default_decode
  #(
     parameter DEFAULT_CHANNEL = 2,
               DEFAULT_DESTID = 2 
   )
  (output [96 - 93 : 0] default_destination_id,
   output [16-1 : 0] default_src_channel
  );

  assign default_destination_id = 
    DEFAULT_DESTID[96 - 93 : 0];
  generate begin : default_decode
    if (DEFAULT_CHANNEL == -1)
      assign default_src_channel = '0;
    else
      assign default_src_channel = 16'b1 << DEFAULT_CHANNEL;
  end
  endgenerate

endmodule


module nios_system_addr_router_001
(
    // -------------------
    // Clock & Reset
    // -------------------
    input clk,
    input reset,

    // -------------------
    // Command Sink (Input)
    // -------------------
    input                       sink_valid,
    input  [107-1 : 0]    sink_data,
    input                       sink_startofpacket,
    input                       sink_endofpacket,
    output                      sink_ready,

    // -------------------
    // Command Source (Output)
    // -------------------
    output                          src_valid,
    output reg [107-1    : 0] src_data,
    output reg [16-1 : 0] src_channel,
    output                          src_startofpacket,
    output                          src_endofpacket,
    input                           src_ready
);

    // -------------------------------------------------------
    // Local parameters and variables
    // -------------------------------------------------------
    localparam PKT_ADDR_H = 67;
    localparam PKT_ADDR_L = 36;
    localparam PKT_DEST_ID_H = 96;
    localparam PKT_DEST_ID_L = 93;
    localparam ST_DATA_W = 107;
    localparam ST_CHANNEL_W = 16;
    localparam DECODER_TYPE = 0;

    localparam PKT_TRANS_WRITE = 70;
    localparam PKT_TRANS_READ  = 71;

    localparam PKT_ADDR_W = PKT_ADDR_H-PKT_ADDR_L + 1;
    localparam PKT_DEST_ID_W = PKT_DEST_ID_H-PKT_DEST_ID_L + 1;




    // -------------------------------------------------------
    // Figure out the number of bits to mask off for each slave span
    // during address decoding
    // -------------------------------------------------------
    localparam PAD0 = log2ceil(64'h8000000 - 64'h4000000);
    localparam PAD1 = log2ceil(64'h8040000 - 64'h8020000);
    localparam PAD2 = log2ceil(64'h8041000 - 64'h8040000);
    localparam PAD3 = log2ceil(64'h8042000 - 64'h8041000);
    localparam PAD4 = log2ceil(64'h8043000 - 64'h8042800);
    localparam PAD5 = log2ceil(64'h8043400 - 64'h8043000);
    localparam PAD6 = log2ceil(64'h8043440 - 64'h8043400);
    localparam PAD7 = log2ceil(64'h8043480 - 64'h8043440);
    localparam PAD8 = log2ceil(64'h80434a0 - 64'h8043480);
    localparam PAD9 = log2ceil(64'h80434b0 - 64'h80434a0);
    localparam PAD10 = log2ceil(64'h80434b8 - 64'h80434b0);
    localparam PAD11 = log2ceil(64'h80434c0 - 64'h80434b8);
    // -------------------------------------------------------
    // Work out which address bits are significant based on the
    // address range of the slaves. If the required width is too
    // large or too small, we use the address field width instead.
    // -------------------------------------------------------
    localparam ADDR_RANGE = 64'h80434c0;
    localparam RANGE_ADDR_WIDTH = log2ceil(ADDR_RANGE);
    localparam OPTIMIZED_ADDR_H = (RANGE_ADDR_WIDTH > PKT_ADDR_W) ||
                                  (RANGE_ADDR_WIDTH == 0) ?
                                        PKT_ADDR_H :
                                        PKT_ADDR_L + RANGE_ADDR_WIDTH - 1;
    localparam RG = RANGE_ADDR_WIDTH-1;

      wire [PKT_ADDR_W-1 : 0] address = sink_data[OPTIMIZED_ADDR_H : PKT_ADDR_L];

    // -------------------------------------------------------
    // Pass almost everything through, untouched
    // -------------------------------------------------------
    assign sink_ready        = src_ready;
    assign src_valid         = sink_valid;
    assign src_startofpacket = sink_startofpacket;
    assign src_endofpacket   = sink_endofpacket;

    wire [PKT_DEST_ID_W-1:0] default_destid;
    wire [16-1 : 0] default_src_channel;




    nios_system_addr_router_001_default_decode the_default_decode(
      .default_destination_id (default_destid),
      .default_src_channel (default_src_channel)
    );

    always @* begin
        src_data    = sink_data;
        src_channel = default_src_channel;

        src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = default_destid;
        // --------------------------------------------------
        // Address Decoder
        // Sets the channel and destination ID based on the address
        // --------------------------------------------------

        // ( 0x4000000 .. 0x8000000 )
        if ( {address[RG:PAD0],{PAD0{1'b0}}} == 28'h4000000 ) begin
            src_channel = 16'b000000000100;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 2;
        end

        // ( 0x8020000 .. 0x8040000 )
        if ( {address[RG:PAD1],{PAD1{1'b0}}} == 28'h8020000 ) begin
            src_channel = 16'b000000000010;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 1;
        end

        // ( 0x8040000 .. 0x8041000 )
        if ( {address[RG:PAD2],{PAD2{1'b0}}} == 28'h8040000 ) begin
            src_channel = 16'b000100000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 8;
        end

        // ( 0x8041000 .. 0x8042000 )
        if ( {address[RG:PAD3],{PAD3{1'b0}}} == 28'h8041000 ) begin
            src_channel = 16'b000000001000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 3;
        end

        // ( 0x8042800 .. 0x8043000 )
        if ( {address[RG:PAD4],{PAD4{1'b0}}} == 28'h8042800 ) begin
            src_channel = 16'b000000000001;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 0;
        end

        // ( 0x8043000 .. 0x8043400 )
        if ( {address[RG:PAD5],{PAD5{1'b0}}} == 28'h8043000 ) begin
            src_channel = 16'b000001000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 6;
        end

        // ( 0x8043400 .. 0x8043440 )
        if ( {address[RG:PAD6],{PAD6{1'b0}}} == 28'h8043400 ) begin
            src_channel = 16'b000000100000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 5;
        end

        // ( 0x8043440 .. 0x8043480 )
        if ( {address[RG:PAD7],{PAD7{1'b0}}} == 28'h8043440 ) begin
            src_channel = 16'b000000010000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 4;
        end

        // ( 0x8043480 .. 0x80434a0 )
        if ( {address[RG:PAD8],{PAD8{1'b0}}} == 28'h8043480 ) begin
            src_channel = 16'b010000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 10;
        end

        // ( 0x80434a0 .. 0x80434b0 )
        if ( {address[RG:PAD9],{PAD9{1'b0}}} == 28'h80434a0 ) begin
            src_channel = 16'b100000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 11;
        end

        // ( 0x80434b0 .. 0x80434b8 )
        if ( {address[RG:PAD10],{PAD10{1'b0}}} == 28'h80434b0 ) begin
            src_channel = 16'b001000000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 9;
        end

        // ( 0x80434b8 .. 0x80434c0 )
        if ( {address[RG:PAD11],{PAD11{1'b0}}} == 28'h80434b8 ) begin
            src_channel = 16'b000010000000;
            src_data[PKT_DEST_ID_H:PKT_DEST_ID_L] = 7;
        end

end


    // --------------------------------------------------
    // Ceil(log2()) function
    // --------------------------------------------------
    function integer log2ceil;
        input reg[65:0] val;
        reg [65:0] i;

        begin
            i = 1;
            log2ceil = 0;

            while (i < val) begin
                log2ceil = log2ceil + 1;
                i = i << 1;
            end
        end
    endfunction

endmodule


