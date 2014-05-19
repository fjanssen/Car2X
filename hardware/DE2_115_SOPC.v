//megafunction wizard: %Altera SOPC Builder%
//GENERATION: STANDARD
//VERSION: WM1.0


//Legal Notice: (C)2014 Altera Corporation. All rights reserved.  Your
//use of Altera Corporation's design tools, logic functions and other
//software and tools, and its AMPP partner logic functions, and any
//output files any of the foregoing (including device programming or
//simulation files), and any associated documentation or information are
//expressly subject to the terms and conditions of the Altera Program
//License Subscription Agreement or other applicable license agreement,
//including, without limitation, that your use is for the sole purpose
//of programming logic devices manufactured by Altera and sold by Altera
//or its authorized distributors.  Please refer to the applicable
//agreement for further details.

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU0_jtag_debug_module_arbitrator (
                                           // inputs:
                                            CPU0_data_master_address_to_slave,
                                            CPU0_data_master_byteenable,
                                            CPU0_data_master_debugaccess,
                                            CPU0_data_master_latency_counter,
                                            CPU0_data_master_read,
                                            CPU0_data_master_write,
                                            CPU0_data_master_writedata,
                                            CPU0_instruction_master_address_to_slave,
                                            CPU0_instruction_master_latency_counter,
                                            CPU0_instruction_master_read,
                                            CPU0_jtag_debug_module_readdata,
                                            CPU0_jtag_debug_module_resetrequest,
                                            clk,
                                            reset_n,

                                           // outputs:
                                            CPU0_data_master_granted_CPU0_jtag_debug_module,
                                            CPU0_data_master_qualified_request_CPU0_jtag_debug_module,
                                            CPU0_data_master_read_data_valid_CPU0_jtag_debug_module,
                                            CPU0_data_master_requests_CPU0_jtag_debug_module,
                                            CPU0_instruction_master_granted_CPU0_jtag_debug_module,
                                            CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module,
                                            CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module,
                                            CPU0_instruction_master_requests_CPU0_jtag_debug_module,
                                            CPU0_jtag_debug_module_address,
                                            CPU0_jtag_debug_module_begintransfer,
                                            CPU0_jtag_debug_module_byteenable,
                                            CPU0_jtag_debug_module_chipselect,
                                            CPU0_jtag_debug_module_debugaccess,
                                            CPU0_jtag_debug_module_readdata_from_sa,
                                            CPU0_jtag_debug_module_reset_n,
                                            CPU0_jtag_debug_module_resetrequest_from_sa,
                                            CPU0_jtag_debug_module_write,
                                            CPU0_jtag_debug_module_writedata,
                                            d1_CPU0_jtag_debug_module_end_xfer
                                         )
;

  output           CPU0_data_master_granted_CPU0_jtag_debug_module;
  output           CPU0_data_master_qualified_request_CPU0_jtag_debug_module;
  output           CPU0_data_master_read_data_valid_CPU0_jtag_debug_module;
  output           CPU0_data_master_requests_CPU0_jtag_debug_module;
  output           CPU0_instruction_master_granted_CPU0_jtag_debug_module;
  output           CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module;
  output           CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module;
  output           CPU0_instruction_master_requests_CPU0_jtag_debug_module;
  output  [  8: 0] CPU0_jtag_debug_module_address;
  output           CPU0_jtag_debug_module_begintransfer;
  output  [  3: 0] CPU0_jtag_debug_module_byteenable;
  output           CPU0_jtag_debug_module_chipselect;
  output           CPU0_jtag_debug_module_debugaccess;
  output  [ 31: 0] CPU0_jtag_debug_module_readdata_from_sa;
  output           CPU0_jtag_debug_module_reset_n;
  output           CPU0_jtag_debug_module_resetrequest_from_sa;
  output           CPU0_jtag_debug_module_write;
  output  [ 31: 0] CPU0_jtag_debug_module_writedata;
  output           d1_CPU0_jtag_debug_module_end_xfer;
  input   [ 18: 0] CPU0_data_master_address_to_slave;
  input   [  3: 0] CPU0_data_master_byteenable;
  input            CPU0_data_master_debugaccess;
  input            CPU0_data_master_latency_counter;
  input            CPU0_data_master_read;
  input            CPU0_data_master_write;
  input   [ 31: 0] CPU0_data_master_writedata;
  input   [ 18: 0] CPU0_instruction_master_address_to_slave;
  input            CPU0_instruction_master_latency_counter;
  input            CPU0_instruction_master_read;
  input   [ 31: 0] CPU0_jtag_debug_module_readdata;
  input            CPU0_jtag_debug_module_resetrequest;
  input            clk;
  input            reset_n;

  wire             CPU0_data_master_arbiterlock;
  wire             CPU0_data_master_arbiterlock2;
  wire             CPU0_data_master_continuerequest;
  wire             CPU0_data_master_granted_CPU0_jtag_debug_module;
  wire             CPU0_data_master_qualified_request_CPU0_jtag_debug_module;
  wire             CPU0_data_master_read_data_valid_CPU0_jtag_debug_module;
  wire             CPU0_data_master_requests_CPU0_jtag_debug_module;
  wire             CPU0_data_master_saved_grant_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_arbiterlock;
  wire             CPU0_instruction_master_arbiterlock2;
  wire             CPU0_instruction_master_continuerequest;
  wire             CPU0_instruction_master_granted_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_requests_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_saved_grant_CPU0_jtag_debug_module;
  wire    [  8: 0] CPU0_jtag_debug_module_address;
  wire             CPU0_jtag_debug_module_allgrants;
  wire             CPU0_jtag_debug_module_allow_new_arb_cycle;
  wire             CPU0_jtag_debug_module_any_bursting_master_saved_grant;
  wire             CPU0_jtag_debug_module_any_continuerequest;
  reg     [  1: 0] CPU0_jtag_debug_module_arb_addend;
  wire             CPU0_jtag_debug_module_arb_counter_enable;
  reg              CPU0_jtag_debug_module_arb_share_counter;
  wire             CPU0_jtag_debug_module_arb_share_counter_next_value;
  wire             CPU0_jtag_debug_module_arb_share_set_values;
  wire    [  1: 0] CPU0_jtag_debug_module_arb_winner;
  wire             CPU0_jtag_debug_module_arbitration_holdoff_internal;
  wire             CPU0_jtag_debug_module_beginbursttransfer_internal;
  wire             CPU0_jtag_debug_module_begins_xfer;
  wire             CPU0_jtag_debug_module_begintransfer;
  wire    [  3: 0] CPU0_jtag_debug_module_byteenable;
  wire             CPU0_jtag_debug_module_chipselect;
  wire    [  3: 0] CPU0_jtag_debug_module_chosen_master_double_vector;
  wire    [  1: 0] CPU0_jtag_debug_module_chosen_master_rot_left;
  wire             CPU0_jtag_debug_module_debugaccess;
  wire             CPU0_jtag_debug_module_end_xfer;
  wire             CPU0_jtag_debug_module_firsttransfer;
  wire    [  1: 0] CPU0_jtag_debug_module_grant_vector;
  wire             CPU0_jtag_debug_module_in_a_read_cycle;
  wire             CPU0_jtag_debug_module_in_a_write_cycle;
  wire    [  1: 0] CPU0_jtag_debug_module_master_qreq_vector;
  wire             CPU0_jtag_debug_module_non_bursting_master_requests;
  wire    [ 31: 0] CPU0_jtag_debug_module_readdata_from_sa;
  reg              CPU0_jtag_debug_module_reg_firsttransfer;
  wire             CPU0_jtag_debug_module_reset_n;
  wire             CPU0_jtag_debug_module_resetrequest_from_sa;
  reg     [  1: 0] CPU0_jtag_debug_module_saved_chosen_master_vector;
  reg              CPU0_jtag_debug_module_slavearbiterlockenable;
  wire             CPU0_jtag_debug_module_slavearbiterlockenable2;
  wire             CPU0_jtag_debug_module_unreg_firsttransfer;
  wire             CPU0_jtag_debug_module_waits_for_read;
  wire             CPU0_jtag_debug_module_waits_for_write;
  wire             CPU0_jtag_debug_module_write;
  wire    [ 31: 0] CPU0_jtag_debug_module_writedata;
  reg              d1_CPU0_jtag_debug_module_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_CPU0_jtag_debug_module;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_CPU0_data_master_granted_slave_CPU0_jtag_debug_module;
  reg              last_cycle_CPU0_instruction_master_granted_slave_CPU0_jtag_debug_module;
  wire    [ 18: 0] shifted_address_to_CPU0_jtag_debug_module_from_CPU0_data_master;
  wire    [ 18: 0] shifted_address_to_CPU0_jtag_debug_module_from_CPU0_instruction_master;
  wire             wait_for_CPU0_jtag_debug_module_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~CPU0_jtag_debug_module_end_xfer;
    end


  assign CPU0_jtag_debug_module_begins_xfer = ~d1_reasons_to_wait & ((CPU0_data_master_qualified_request_CPU0_jtag_debug_module | CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module));
  //assign CPU0_jtag_debug_module_readdata_from_sa = CPU0_jtag_debug_module_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU0_jtag_debug_module_readdata_from_sa = CPU0_jtag_debug_module_readdata;

  assign CPU0_data_master_requests_CPU0_jtag_debug_module = ({CPU0_data_master_address_to_slave[18 : 11] , 11'b0} == 19'h42800) & (CPU0_data_master_read | CPU0_data_master_write);
  //CPU0_jtag_debug_module_arb_share_counter set values, which is an e_mux
  assign CPU0_jtag_debug_module_arb_share_set_values = 1;

  //CPU0_jtag_debug_module_non_bursting_master_requests mux, which is an e_mux
  assign CPU0_jtag_debug_module_non_bursting_master_requests = CPU0_data_master_requests_CPU0_jtag_debug_module |
    CPU0_instruction_master_requests_CPU0_jtag_debug_module |
    CPU0_data_master_requests_CPU0_jtag_debug_module |
    CPU0_instruction_master_requests_CPU0_jtag_debug_module;

  //CPU0_jtag_debug_module_any_bursting_master_saved_grant mux, which is an e_mux
  assign CPU0_jtag_debug_module_any_bursting_master_saved_grant = 0;

  //CPU0_jtag_debug_module_arb_share_counter_next_value assignment, which is an e_assign
  assign CPU0_jtag_debug_module_arb_share_counter_next_value = CPU0_jtag_debug_module_firsttransfer ? (CPU0_jtag_debug_module_arb_share_set_values - 1) : |CPU0_jtag_debug_module_arb_share_counter ? (CPU0_jtag_debug_module_arb_share_counter - 1) : 0;

  //CPU0_jtag_debug_module_allgrants all slave grants, which is an e_mux
  assign CPU0_jtag_debug_module_allgrants = (|CPU0_jtag_debug_module_grant_vector) |
    (|CPU0_jtag_debug_module_grant_vector) |
    (|CPU0_jtag_debug_module_grant_vector) |
    (|CPU0_jtag_debug_module_grant_vector);

  //CPU0_jtag_debug_module_end_xfer assignment, which is an e_assign
  assign CPU0_jtag_debug_module_end_xfer = ~(CPU0_jtag_debug_module_waits_for_read | CPU0_jtag_debug_module_waits_for_write);

  //end_xfer_arb_share_counter_term_CPU0_jtag_debug_module arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_CPU0_jtag_debug_module = CPU0_jtag_debug_module_end_xfer & (~CPU0_jtag_debug_module_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //CPU0_jtag_debug_module_arb_share_counter arbitration counter enable, which is an e_assign
  assign CPU0_jtag_debug_module_arb_counter_enable = (end_xfer_arb_share_counter_term_CPU0_jtag_debug_module & CPU0_jtag_debug_module_allgrants) | (end_xfer_arb_share_counter_term_CPU0_jtag_debug_module & ~CPU0_jtag_debug_module_non_bursting_master_requests);

  //CPU0_jtag_debug_module_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_jtag_debug_module_arb_share_counter <= 0;
      else if (CPU0_jtag_debug_module_arb_counter_enable)
          CPU0_jtag_debug_module_arb_share_counter <= CPU0_jtag_debug_module_arb_share_counter_next_value;
    end


  //CPU0_jtag_debug_module_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_jtag_debug_module_slavearbiterlockenable <= 0;
      else if ((|CPU0_jtag_debug_module_master_qreq_vector & end_xfer_arb_share_counter_term_CPU0_jtag_debug_module) | (end_xfer_arb_share_counter_term_CPU0_jtag_debug_module & ~CPU0_jtag_debug_module_non_bursting_master_requests))
          CPU0_jtag_debug_module_slavearbiterlockenable <= |CPU0_jtag_debug_module_arb_share_counter_next_value;
    end


  //CPU0/data_master CPU0/jtag_debug_module arbiterlock, which is an e_assign
  assign CPU0_data_master_arbiterlock = CPU0_jtag_debug_module_slavearbiterlockenable & CPU0_data_master_continuerequest;

  //CPU0_jtag_debug_module_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign CPU0_jtag_debug_module_slavearbiterlockenable2 = |CPU0_jtag_debug_module_arb_share_counter_next_value;

  //CPU0/data_master CPU0/jtag_debug_module arbiterlock2, which is an e_assign
  assign CPU0_data_master_arbiterlock2 = CPU0_jtag_debug_module_slavearbiterlockenable2 & CPU0_data_master_continuerequest;

  //CPU0/instruction_master CPU0/jtag_debug_module arbiterlock, which is an e_assign
  assign CPU0_instruction_master_arbiterlock = CPU0_jtag_debug_module_slavearbiterlockenable & CPU0_instruction_master_continuerequest;

  //CPU0/instruction_master CPU0/jtag_debug_module arbiterlock2, which is an e_assign
  assign CPU0_instruction_master_arbiterlock2 = CPU0_jtag_debug_module_slavearbiterlockenable2 & CPU0_instruction_master_continuerequest;

  //CPU0/instruction_master granted CPU0/jtag_debug_module last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU0_instruction_master_granted_slave_CPU0_jtag_debug_module <= 0;
      else 
        last_cycle_CPU0_instruction_master_granted_slave_CPU0_jtag_debug_module <= CPU0_instruction_master_saved_grant_CPU0_jtag_debug_module ? 1 : (CPU0_jtag_debug_module_arbitration_holdoff_internal | ~CPU0_instruction_master_requests_CPU0_jtag_debug_module) ? 0 : last_cycle_CPU0_instruction_master_granted_slave_CPU0_jtag_debug_module;
    end


  //CPU0_instruction_master_continuerequest continued request, which is an e_mux
  assign CPU0_instruction_master_continuerequest = last_cycle_CPU0_instruction_master_granted_slave_CPU0_jtag_debug_module & CPU0_instruction_master_requests_CPU0_jtag_debug_module;

  //CPU0_jtag_debug_module_any_continuerequest at least one master continues requesting, which is an e_mux
  assign CPU0_jtag_debug_module_any_continuerequest = CPU0_instruction_master_continuerequest |
    CPU0_data_master_continuerequest;

  assign CPU0_data_master_qualified_request_CPU0_jtag_debug_module = CPU0_data_master_requests_CPU0_jtag_debug_module & ~((CPU0_data_master_read & ((CPU0_data_master_latency_counter != 0))) | CPU0_instruction_master_arbiterlock);
  //local readdatavalid CPU0_data_master_read_data_valid_CPU0_jtag_debug_module, which is an e_mux
  assign CPU0_data_master_read_data_valid_CPU0_jtag_debug_module = CPU0_data_master_granted_CPU0_jtag_debug_module & CPU0_data_master_read & ~CPU0_jtag_debug_module_waits_for_read;

  //CPU0_jtag_debug_module_writedata mux, which is an e_mux
  assign CPU0_jtag_debug_module_writedata = CPU0_data_master_writedata;

  assign CPU0_instruction_master_requests_CPU0_jtag_debug_module = (({CPU0_instruction_master_address_to_slave[18 : 11] , 11'b0} == 19'h42800) & (CPU0_instruction_master_read)) & CPU0_instruction_master_read;
  //CPU0/data_master granted CPU0/jtag_debug_module last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU0_data_master_granted_slave_CPU0_jtag_debug_module <= 0;
      else 
        last_cycle_CPU0_data_master_granted_slave_CPU0_jtag_debug_module <= CPU0_data_master_saved_grant_CPU0_jtag_debug_module ? 1 : (CPU0_jtag_debug_module_arbitration_holdoff_internal | ~CPU0_data_master_requests_CPU0_jtag_debug_module) ? 0 : last_cycle_CPU0_data_master_granted_slave_CPU0_jtag_debug_module;
    end


  //CPU0_data_master_continuerequest continued request, which is an e_mux
  assign CPU0_data_master_continuerequest = last_cycle_CPU0_data_master_granted_slave_CPU0_jtag_debug_module & CPU0_data_master_requests_CPU0_jtag_debug_module;

  assign CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module = CPU0_instruction_master_requests_CPU0_jtag_debug_module & ~((CPU0_instruction_master_read & ((CPU0_instruction_master_latency_counter != 0))) | CPU0_data_master_arbiterlock);
  //local readdatavalid CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module, which is an e_mux
  assign CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module = CPU0_instruction_master_granted_CPU0_jtag_debug_module & CPU0_instruction_master_read & ~CPU0_jtag_debug_module_waits_for_read;

  //allow new arb cycle for CPU0/jtag_debug_module, which is an e_assign
  assign CPU0_jtag_debug_module_allow_new_arb_cycle = ~CPU0_data_master_arbiterlock & ~CPU0_instruction_master_arbiterlock;

  //CPU0/instruction_master assignment into master qualified-requests vector for CPU0/jtag_debug_module, which is an e_assign
  assign CPU0_jtag_debug_module_master_qreq_vector[0] = CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module;

  //CPU0/instruction_master grant CPU0/jtag_debug_module, which is an e_assign
  assign CPU0_instruction_master_granted_CPU0_jtag_debug_module = CPU0_jtag_debug_module_grant_vector[0];

  //CPU0/instruction_master saved-grant CPU0/jtag_debug_module, which is an e_assign
  assign CPU0_instruction_master_saved_grant_CPU0_jtag_debug_module = CPU0_jtag_debug_module_arb_winner[0] && CPU0_instruction_master_requests_CPU0_jtag_debug_module;

  //CPU0/data_master assignment into master qualified-requests vector for CPU0/jtag_debug_module, which is an e_assign
  assign CPU0_jtag_debug_module_master_qreq_vector[1] = CPU0_data_master_qualified_request_CPU0_jtag_debug_module;

  //CPU0/data_master grant CPU0/jtag_debug_module, which is an e_assign
  assign CPU0_data_master_granted_CPU0_jtag_debug_module = CPU0_jtag_debug_module_grant_vector[1];

  //CPU0/data_master saved-grant CPU0/jtag_debug_module, which is an e_assign
  assign CPU0_data_master_saved_grant_CPU0_jtag_debug_module = CPU0_jtag_debug_module_arb_winner[1] && CPU0_data_master_requests_CPU0_jtag_debug_module;

  //CPU0/jtag_debug_module chosen-master double-vector, which is an e_assign
  assign CPU0_jtag_debug_module_chosen_master_double_vector = {CPU0_jtag_debug_module_master_qreq_vector, CPU0_jtag_debug_module_master_qreq_vector} & ({~CPU0_jtag_debug_module_master_qreq_vector, ~CPU0_jtag_debug_module_master_qreq_vector} + CPU0_jtag_debug_module_arb_addend);

  //stable onehot encoding of arb winner
  assign CPU0_jtag_debug_module_arb_winner = (CPU0_jtag_debug_module_allow_new_arb_cycle & | CPU0_jtag_debug_module_grant_vector) ? CPU0_jtag_debug_module_grant_vector : CPU0_jtag_debug_module_saved_chosen_master_vector;

  //saved CPU0_jtag_debug_module_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_jtag_debug_module_saved_chosen_master_vector <= 0;
      else if (CPU0_jtag_debug_module_allow_new_arb_cycle)
          CPU0_jtag_debug_module_saved_chosen_master_vector <= |CPU0_jtag_debug_module_grant_vector ? CPU0_jtag_debug_module_grant_vector : CPU0_jtag_debug_module_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign CPU0_jtag_debug_module_grant_vector = {(CPU0_jtag_debug_module_chosen_master_double_vector[1] | CPU0_jtag_debug_module_chosen_master_double_vector[3]),
    (CPU0_jtag_debug_module_chosen_master_double_vector[0] | CPU0_jtag_debug_module_chosen_master_double_vector[2])};

  //CPU0/jtag_debug_module chosen master rotated left, which is an e_assign
  assign CPU0_jtag_debug_module_chosen_master_rot_left = (CPU0_jtag_debug_module_arb_winner << 1) ? (CPU0_jtag_debug_module_arb_winner << 1) : 1;

  //CPU0/jtag_debug_module's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_jtag_debug_module_arb_addend <= 1;
      else if (|CPU0_jtag_debug_module_grant_vector)
          CPU0_jtag_debug_module_arb_addend <= CPU0_jtag_debug_module_end_xfer? CPU0_jtag_debug_module_chosen_master_rot_left : CPU0_jtag_debug_module_grant_vector;
    end


  assign CPU0_jtag_debug_module_begintransfer = CPU0_jtag_debug_module_begins_xfer;
  //CPU0_jtag_debug_module_reset_n assignment, which is an e_assign
  assign CPU0_jtag_debug_module_reset_n = reset_n;

  //assign CPU0_jtag_debug_module_resetrequest_from_sa = CPU0_jtag_debug_module_resetrequest so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU0_jtag_debug_module_resetrequest_from_sa = CPU0_jtag_debug_module_resetrequest;

  assign CPU0_jtag_debug_module_chipselect = CPU0_data_master_granted_CPU0_jtag_debug_module | CPU0_instruction_master_granted_CPU0_jtag_debug_module;
  //CPU0_jtag_debug_module_firsttransfer first transaction, which is an e_assign
  assign CPU0_jtag_debug_module_firsttransfer = CPU0_jtag_debug_module_begins_xfer ? CPU0_jtag_debug_module_unreg_firsttransfer : CPU0_jtag_debug_module_reg_firsttransfer;

  //CPU0_jtag_debug_module_unreg_firsttransfer first transaction, which is an e_assign
  assign CPU0_jtag_debug_module_unreg_firsttransfer = ~(CPU0_jtag_debug_module_slavearbiterlockenable & CPU0_jtag_debug_module_any_continuerequest);

  //CPU0_jtag_debug_module_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_jtag_debug_module_reg_firsttransfer <= 1'b1;
      else if (CPU0_jtag_debug_module_begins_xfer)
          CPU0_jtag_debug_module_reg_firsttransfer <= CPU0_jtag_debug_module_unreg_firsttransfer;
    end


  //CPU0_jtag_debug_module_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign CPU0_jtag_debug_module_beginbursttransfer_internal = CPU0_jtag_debug_module_begins_xfer;

  //CPU0_jtag_debug_module_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign CPU0_jtag_debug_module_arbitration_holdoff_internal = CPU0_jtag_debug_module_begins_xfer & CPU0_jtag_debug_module_firsttransfer;

  //CPU0_jtag_debug_module_write assignment, which is an e_mux
  assign CPU0_jtag_debug_module_write = CPU0_data_master_granted_CPU0_jtag_debug_module & CPU0_data_master_write;

  assign shifted_address_to_CPU0_jtag_debug_module_from_CPU0_data_master = CPU0_data_master_address_to_slave;
  //CPU0_jtag_debug_module_address mux, which is an e_mux
  assign CPU0_jtag_debug_module_address = (CPU0_data_master_granted_CPU0_jtag_debug_module)? (shifted_address_to_CPU0_jtag_debug_module_from_CPU0_data_master >> 2) :
    (shifted_address_to_CPU0_jtag_debug_module_from_CPU0_instruction_master >> 2);

  assign shifted_address_to_CPU0_jtag_debug_module_from_CPU0_instruction_master = CPU0_instruction_master_address_to_slave;
  //d1_CPU0_jtag_debug_module_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_CPU0_jtag_debug_module_end_xfer <= 1;
      else 
        d1_CPU0_jtag_debug_module_end_xfer <= CPU0_jtag_debug_module_end_xfer;
    end


  //CPU0_jtag_debug_module_waits_for_read in a cycle, which is an e_mux
  assign CPU0_jtag_debug_module_waits_for_read = CPU0_jtag_debug_module_in_a_read_cycle & CPU0_jtag_debug_module_begins_xfer;

  //CPU0_jtag_debug_module_in_a_read_cycle assignment, which is an e_assign
  assign CPU0_jtag_debug_module_in_a_read_cycle = (CPU0_data_master_granted_CPU0_jtag_debug_module & CPU0_data_master_read) | (CPU0_instruction_master_granted_CPU0_jtag_debug_module & CPU0_instruction_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = CPU0_jtag_debug_module_in_a_read_cycle;

  //CPU0_jtag_debug_module_waits_for_write in a cycle, which is an e_mux
  assign CPU0_jtag_debug_module_waits_for_write = CPU0_jtag_debug_module_in_a_write_cycle & 0;

  //CPU0_jtag_debug_module_in_a_write_cycle assignment, which is an e_assign
  assign CPU0_jtag_debug_module_in_a_write_cycle = CPU0_data_master_granted_CPU0_jtag_debug_module & CPU0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = CPU0_jtag_debug_module_in_a_write_cycle;

  assign wait_for_CPU0_jtag_debug_module_counter = 0;
  //CPU0_jtag_debug_module_byteenable byte enable port mux, which is an e_mux
  assign CPU0_jtag_debug_module_byteenable = (CPU0_data_master_granted_CPU0_jtag_debug_module)? CPU0_data_master_byteenable :
    -1;

  //debugaccess mux, which is an e_mux
  assign CPU0_jtag_debug_module_debugaccess = (CPU0_data_master_granted_CPU0_jtag_debug_module)? CPU0_data_master_debugaccess :
    0;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU0/jtag_debug_module enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_granted_CPU0_jtag_debug_module + CPU0_instruction_master_granted_CPU0_jtag_debug_module > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_saved_grant_CPU0_jtag_debug_module + CPU0_instruction_master_saved_grant_CPU0_jtag_debug_module > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU0_data_master_arbitrator (
                                     // inputs:
                                      CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa,
                                      CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa,
                                      CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa,
                                      CPU0_data_master_address,
                                      CPU0_data_master_byteenable,
                                      CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave,
                                      CPU0_data_master_granted_CPU0_jtag_debug_module,
                                      CPU0_data_master_granted_CPU0_memory_s1,
                                      CPU0_data_master_granted_Comms_memory_s1,
                                      CPU0_data_master_granted_Comms_mutex_rx_s1,
                                      CPU0_data_master_granted_Comms_mutex_tx_s1,
                                      CPU0_data_master_granted_pio_LED_s1,
                                      CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave,
                                      CPU0_data_master_qualified_request_CPU0_jtag_debug_module,
                                      CPU0_data_master_qualified_request_CPU0_memory_s1,
                                      CPU0_data_master_qualified_request_Comms_memory_s1,
                                      CPU0_data_master_qualified_request_Comms_mutex_rx_s1,
                                      CPU0_data_master_qualified_request_Comms_mutex_tx_s1,
                                      CPU0_data_master_qualified_request_pio_LED_s1,
                                      CPU0_data_master_read,
                                      CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave,
                                      CPU0_data_master_read_data_valid_CPU0_jtag_debug_module,
                                      CPU0_data_master_read_data_valid_CPU0_memory_s1,
                                      CPU0_data_master_read_data_valid_Comms_memory_s1,
                                      CPU0_data_master_read_data_valid_Comms_mutex_rx_s1,
                                      CPU0_data_master_read_data_valid_Comms_mutex_tx_s1,
                                      CPU0_data_master_read_data_valid_pio_LED_s1,
                                      CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave,
                                      CPU0_data_master_requests_CPU0_jtag_debug_module,
                                      CPU0_data_master_requests_CPU0_memory_s1,
                                      CPU0_data_master_requests_Comms_memory_s1,
                                      CPU0_data_master_requests_Comms_mutex_rx_s1,
                                      CPU0_data_master_requests_Comms_mutex_tx_s1,
                                      CPU0_data_master_requests_pio_LED_s1,
                                      CPU0_data_master_write,
                                      CPU0_data_master_writedata,
                                      CPU0_jtag_debug_module_readdata_from_sa,
                                      CPU0_memory_s1_readdata_from_sa,
                                      CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa,
                                      Comms_memory_s1_readdata_from_sa,
                                      Comms_mutex_rx_s1_readdata_from_sa,
                                      Comms_mutex_tx_s1_readdata_from_sa,
                                      clk,
                                      d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer,
                                      d1_CPU0_jtag_debug_module_end_xfer,
                                      d1_CPU0_memory_s1_end_xfer,
                                      d1_Comms_memory_s1_end_xfer,
                                      d1_Comms_mutex_rx_s1_end_xfer,
                                      d1_Comms_mutex_tx_s1_end_xfer,
                                      d1_pio_LED_s1_end_xfer,
                                      pio_LED_s1_readdata_from_sa,
                                      reset_n,

                                     // outputs:
                                      CPU0_data_master_address_to_slave,
                                      CPU0_data_master_irq,
                                      CPU0_data_master_latency_counter,
                                      CPU0_data_master_readdata,
                                      CPU0_data_master_readdatavalid,
                                      CPU0_data_master_waitrequest
                                   )
;

  output  [ 18: 0] CPU0_data_master_address_to_slave;
  output  [ 31: 0] CPU0_data_master_irq;
  output           CPU0_data_master_latency_counter;
  output  [ 31: 0] CPU0_data_master_readdata;
  output           CPU0_data_master_readdatavalid;
  output           CPU0_data_master_waitrequest;
  input            CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  input   [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa;
  input            CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;
  input   [ 18: 0] CPU0_data_master_address;
  input   [  3: 0] CPU0_data_master_byteenable;
  input            CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave;
  input            CPU0_data_master_granted_CPU0_jtag_debug_module;
  input            CPU0_data_master_granted_CPU0_memory_s1;
  input            CPU0_data_master_granted_Comms_memory_s1;
  input            CPU0_data_master_granted_Comms_mutex_rx_s1;
  input            CPU0_data_master_granted_Comms_mutex_tx_s1;
  input            CPU0_data_master_granted_pio_LED_s1;
  input            CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave;
  input            CPU0_data_master_qualified_request_CPU0_jtag_debug_module;
  input            CPU0_data_master_qualified_request_CPU0_memory_s1;
  input            CPU0_data_master_qualified_request_Comms_memory_s1;
  input            CPU0_data_master_qualified_request_Comms_mutex_rx_s1;
  input            CPU0_data_master_qualified_request_Comms_mutex_tx_s1;
  input            CPU0_data_master_qualified_request_pio_LED_s1;
  input            CPU0_data_master_read;
  input            CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave;
  input            CPU0_data_master_read_data_valid_CPU0_jtag_debug_module;
  input            CPU0_data_master_read_data_valid_CPU0_memory_s1;
  input            CPU0_data_master_read_data_valid_Comms_memory_s1;
  input            CPU0_data_master_read_data_valid_Comms_mutex_rx_s1;
  input            CPU0_data_master_read_data_valid_Comms_mutex_tx_s1;
  input            CPU0_data_master_read_data_valid_pio_LED_s1;
  input            CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave;
  input            CPU0_data_master_requests_CPU0_jtag_debug_module;
  input            CPU0_data_master_requests_CPU0_memory_s1;
  input            CPU0_data_master_requests_Comms_memory_s1;
  input            CPU0_data_master_requests_Comms_mutex_rx_s1;
  input            CPU0_data_master_requests_Comms_mutex_tx_s1;
  input            CPU0_data_master_requests_pio_LED_s1;
  input            CPU0_data_master_write;
  input   [ 31: 0] CPU0_data_master_writedata;
  input   [ 31: 0] CPU0_jtag_debug_module_readdata_from_sa;
  input   [ 31: 0] CPU0_memory_s1_readdata_from_sa;
  input            CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  input   [ 31: 0] Comms_memory_s1_readdata_from_sa;
  input   [ 31: 0] Comms_mutex_rx_s1_readdata_from_sa;
  input   [ 31: 0] Comms_mutex_tx_s1_readdata_from_sa;
  input            clk;
  input            d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer;
  input            d1_CPU0_jtag_debug_module_end_xfer;
  input            d1_CPU0_memory_s1_end_xfer;
  input            d1_Comms_memory_s1_end_xfer;
  input            d1_Comms_mutex_rx_s1_end_xfer;
  input            d1_Comms_mutex_tx_s1_end_xfer;
  input            d1_pio_LED_s1_end_xfer;
  input   [ 31: 0] pio_LED_s1_readdata_from_sa;
  input            reset_n;

  reg     [ 18: 0] CPU0_data_master_address_last_time;
  wire    [ 18: 0] CPU0_data_master_address_to_slave;
  reg     [  3: 0] CPU0_data_master_byteenable_last_time;
  wire    [ 31: 0] CPU0_data_master_irq;
  wire             CPU0_data_master_is_granted_some_slave;
  reg              CPU0_data_master_latency_counter;
  reg              CPU0_data_master_read_but_no_slave_selected;
  reg              CPU0_data_master_read_last_time;
  wire    [ 31: 0] CPU0_data_master_readdata;
  wire             CPU0_data_master_readdatavalid;
  wire             CPU0_data_master_run;
  wire             CPU0_data_master_waitrequest;
  reg              CPU0_data_master_write_last_time;
  reg     [ 31: 0] CPU0_data_master_writedata_last_time;
  reg              active_and_waiting_last_time;
  wire             latency_load_value;
  wire             p1_CPU0_data_master_latency_counter;
  wire             pre_flush_CPU0_data_master_readdatavalid;
  wire             r_0;
  wire             r_1;
  //r_0 master_run cascaded wait assignment, which is an e_assign
  assign r_0 = 1 & (CPU0_data_master_qualified_request_CPU0_jtag_debug_module | ~CPU0_data_master_requests_CPU0_jtag_debug_module) & (CPU0_data_master_granted_CPU0_jtag_debug_module | ~CPU0_data_master_qualified_request_CPU0_jtag_debug_module) & ((~CPU0_data_master_qualified_request_CPU0_jtag_debug_module | ~CPU0_data_master_read | (1 & ~d1_CPU0_jtag_debug_module_end_xfer & CPU0_data_master_read))) & ((~CPU0_data_master_qualified_request_CPU0_jtag_debug_module | ~CPU0_data_master_write | (1 & CPU0_data_master_write))) & 1 & (CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave | ~CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave) & ((~CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave | ~(CPU0_data_master_read | CPU0_data_master_write) | (1 & ~CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa & (CPU0_data_master_read | CPU0_data_master_write)))) & ((~CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave | ~(CPU0_data_master_read | CPU0_data_master_write) | (1 & ~CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa & (CPU0_data_master_read | CPU0_data_master_write)))) & 1 & (CPU0_data_master_qualified_request_CPU0_memory_s1 | ~CPU0_data_master_requests_CPU0_memory_s1) & (CPU0_data_master_granted_CPU0_memory_s1 | ~CPU0_data_master_qualified_request_CPU0_memory_s1) & ((~CPU0_data_master_qualified_request_CPU0_memory_s1 | ~(CPU0_data_master_read | CPU0_data_master_write) | (1 & (CPU0_data_master_read | CPU0_data_master_write)))) & ((~CPU0_data_master_qualified_request_CPU0_memory_s1 | ~(CPU0_data_master_read | CPU0_data_master_write) | (1 & (CPU0_data_master_read | CPU0_data_master_write)))) & 1 & (CPU0_data_master_qualified_request_Comms_memory_s1 | ~CPU0_data_master_requests_Comms_memory_s1) & (CPU0_data_master_granted_Comms_memory_s1 | ~CPU0_data_master_qualified_request_Comms_memory_s1) & ((~CPU0_data_master_qualified_request_Comms_memory_s1 | ~(CPU0_data_master_read | CPU0_data_master_write) | (1 & (CPU0_data_master_read | CPU0_data_master_write)))) & ((~CPU0_data_master_qualified_request_Comms_memory_s1 | ~(CPU0_data_master_read | CPU0_data_master_write) | (1 & (CPU0_data_master_read | CPU0_data_master_write)))) & 1;

  //cascaded wait assignment, which is an e_assign
  assign CPU0_data_master_run = r_0 & r_1;

  //r_1 master_run cascaded wait assignment, which is an e_assign
  assign r_1 = (CPU0_data_master_qualified_request_Comms_mutex_rx_s1 | ~CPU0_data_master_requests_Comms_mutex_rx_s1) & (CPU0_data_master_granted_Comms_mutex_rx_s1 | ~CPU0_data_master_qualified_request_Comms_mutex_rx_s1) & ((~CPU0_data_master_qualified_request_Comms_mutex_rx_s1 | ~CPU0_data_master_read | (1 & ~d1_Comms_mutex_rx_s1_end_xfer & CPU0_data_master_read))) & ((~CPU0_data_master_qualified_request_Comms_mutex_rx_s1 | ~CPU0_data_master_write | (1 & CPU0_data_master_write))) & 1 & (CPU0_data_master_qualified_request_Comms_mutex_tx_s1 | ~CPU0_data_master_requests_Comms_mutex_tx_s1) & (CPU0_data_master_granted_Comms_mutex_tx_s1 | ~CPU0_data_master_qualified_request_Comms_mutex_tx_s1) & ((~CPU0_data_master_qualified_request_Comms_mutex_tx_s1 | ~CPU0_data_master_read | (1 & ~d1_Comms_mutex_tx_s1_end_xfer & CPU0_data_master_read))) & ((~CPU0_data_master_qualified_request_Comms_mutex_tx_s1 | ~CPU0_data_master_write | (1 & CPU0_data_master_write))) & 1 & (CPU0_data_master_qualified_request_pio_LED_s1 | ~CPU0_data_master_requests_pio_LED_s1) & (CPU0_data_master_granted_pio_LED_s1 | ~CPU0_data_master_qualified_request_pio_LED_s1) & ((~CPU0_data_master_qualified_request_pio_LED_s1 | ~CPU0_data_master_read | (1 & ~d1_pio_LED_s1_end_xfer & CPU0_data_master_read))) & ((~CPU0_data_master_qualified_request_pio_LED_s1 | ~CPU0_data_master_write | (1 & CPU0_data_master_write)));

  //optimize select-logic by passing only those address bits which matter.
  assign CPU0_data_master_address_to_slave = CPU0_data_master_address[18 : 0];

  //CPU0_data_master_read_but_no_slave_selected assignment, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_read_but_no_slave_selected <= 0;
      else 
        CPU0_data_master_read_but_no_slave_selected <= CPU0_data_master_read & CPU0_data_master_run & ~CPU0_data_master_is_granted_some_slave;
    end


  //some slave is getting selected, which is an e_mux
  assign CPU0_data_master_is_granted_some_slave = CPU0_data_master_granted_CPU0_jtag_debug_module |
    CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave |
    CPU0_data_master_granted_CPU0_memory_s1 |
    CPU0_data_master_granted_Comms_memory_s1 |
    CPU0_data_master_granted_Comms_mutex_rx_s1 |
    CPU0_data_master_granted_Comms_mutex_tx_s1 |
    CPU0_data_master_granted_pio_LED_s1;

  //latent slave read data valids which may be flushed, which is an e_mux
  assign pre_flush_CPU0_data_master_readdatavalid = CPU0_data_master_read_data_valid_CPU0_memory_s1 |
    CPU0_data_master_read_data_valid_Comms_memory_s1;

  //latent slave read data valid which is not flushed, which is an e_mux
  assign CPU0_data_master_readdatavalid = CPU0_data_master_read_but_no_slave_selected |
    pre_flush_CPU0_data_master_readdatavalid |
    CPU0_data_master_read_data_valid_CPU0_jtag_debug_module |
    CPU0_data_master_read_but_no_slave_selected |
    pre_flush_CPU0_data_master_readdatavalid |
    CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave |
    CPU0_data_master_read_but_no_slave_selected |
    pre_flush_CPU0_data_master_readdatavalid |
    CPU0_data_master_read_but_no_slave_selected |
    pre_flush_CPU0_data_master_readdatavalid |
    CPU0_data_master_read_but_no_slave_selected |
    pre_flush_CPU0_data_master_readdatavalid |
    CPU0_data_master_read_data_valid_Comms_mutex_rx_s1 |
    CPU0_data_master_read_but_no_slave_selected |
    pre_flush_CPU0_data_master_readdatavalid |
    CPU0_data_master_read_data_valid_Comms_mutex_tx_s1 |
    CPU0_data_master_read_but_no_slave_selected |
    pre_flush_CPU0_data_master_readdatavalid |
    CPU0_data_master_read_data_valid_pio_LED_s1;

  //CPU0/data_master readdata mux, which is an e_mux
  assign CPU0_data_master_readdata = ({32 {~(CPU0_data_master_qualified_request_CPU0_jtag_debug_module & CPU0_data_master_read)}} | CPU0_jtag_debug_module_readdata_from_sa) &
    ({32 {~(CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave & CPU0_data_master_read)}} | CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa) &
    ({32 {~CPU0_data_master_read_data_valid_CPU0_memory_s1}} | CPU0_memory_s1_readdata_from_sa) &
    ({32 {~CPU0_data_master_read_data_valid_Comms_memory_s1}} | Comms_memory_s1_readdata_from_sa) &
    ({32 {~(CPU0_data_master_qualified_request_Comms_mutex_rx_s1 & CPU0_data_master_read)}} | Comms_mutex_rx_s1_readdata_from_sa) &
    ({32 {~(CPU0_data_master_qualified_request_Comms_mutex_tx_s1 & CPU0_data_master_read)}} | Comms_mutex_tx_s1_readdata_from_sa) &
    ({32 {~(CPU0_data_master_qualified_request_pio_LED_s1 & CPU0_data_master_read)}} | pio_LED_s1_readdata_from_sa);

  //actual waitrequest port, which is an e_assign
  assign CPU0_data_master_waitrequest = ~CPU0_data_master_run;

  //latent max counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_latency_counter <= 0;
      else 
        CPU0_data_master_latency_counter <= p1_CPU0_data_master_latency_counter;
    end


  //latency counter load mux, which is an e_mux
  assign p1_CPU0_data_master_latency_counter = ((CPU0_data_master_run & CPU0_data_master_read))? latency_load_value :
    (CPU0_data_master_latency_counter)? CPU0_data_master_latency_counter - 1 :
    0;

  //read latency load values, which is an e_mux
  assign latency_load_value = ({1 {CPU0_data_master_requests_CPU0_memory_s1}} & 1) |
    ({1 {CPU0_data_master_requests_Comms_memory_s1}} & 1);

  //irq assign, which is an e_assign
  assign CPU0_data_master_irq = {1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa,
    CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa};


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU0_data_master_address check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_address_last_time <= 0;
      else 
        CPU0_data_master_address_last_time <= CPU0_data_master_address;
    end


  //CPU0/data_master waited last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          active_and_waiting_last_time <= 0;
      else 
        active_and_waiting_last_time <= CPU0_data_master_waitrequest & (CPU0_data_master_read | CPU0_data_master_write);
    end


  //CPU0_data_master_address matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU0_data_master_address != CPU0_data_master_address_last_time))
        begin
          $write("%0d ns: CPU0_data_master_address did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU0_data_master_byteenable check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_byteenable_last_time <= 0;
      else 
        CPU0_data_master_byteenable_last_time <= CPU0_data_master_byteenable;
    end


  //CPU0_data_master_byteenable matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU0_data_master_byteenable != CPU0_data_master_byteenable_last_time))
        begin
          $write("%0d ns: CPU0_data_master_byteenable did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU0_data_master_read check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_read_last_time <= 0;
      else 
        CPU0_data_master_read_last_time <= CPU0_data_master_read;
    end


  //CPU0_data_master_read matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU0_data_master_read != CPU0_data_master_read_last_time))
        begin
          $write("%0d ns: CPU0_data_master_read did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU0_data_master_write check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_write_last_time <= 0;
      else 
        CPU0_data_master_write_last_time <= CPU0_data_master_write;
    end


  //CPU0_data_master_write matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU0_data_master_write != CPU0_data_master_write_last_time))
        begin
          $write("%0d ns: CPU0_data_master_write did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU0_data_master_writedata check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_writedata_last_time <= 0;
      else 
        CPU0_data_master_writedata_last_time <= CPU0_data_master_writedata;
    end


  //CPU0_data_master_writedata matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU0_data_master_writedata != CPU0_data_master_writedata_last_time) & CPU0_data_master_write)
        begin
          $write("%0d ns: CPU0_data_master_writedata did not heed wait!!!", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU0_instruction_master_arbitrator (
                                            // inputs:
                                             CPU0_instruction_master_address,
                                             CPU0_instruction_master_granted_CPU0_jtag_debug_module,
                                             CPU0_instruction_master_granted_CPU0_memory_s1,
                                             CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module,
                                             CPU0_instruction_master_qualified_request_CPU0_memory_s1,
                                             CPU0_instruction_master_read,
                                             CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module,
                                             CPU0_instruction_master_read_data_valid_CPU0_memory_s1,
                                             CPU0_instruction_master_requests_CPU0_jtag_debug_module,
                                             CPU0_instruction_master_requests_CPU0_memory_s1,
                                             CPU0_jtag_debug_module_readdata_from_sa,
                                             CPU0_memory_s1_readdata_from_sa,
                                             clk,
                                             d1_CPU0_jtag_debug_module_end_xfer,
                                             d1_CPU0_memory_s1_end_xfer,
                                             reset_n,

                                            // outputs:
                                             CPU0_instruction_master_address_to_slave,
                                             CPU0_instruction_master_latency_counter,
                                             CPU0_instruction_master_readdata,
                                             CPU0_instruction_master_readdatavalid,
                                             CPU0_instruction_master_waitrequest
                                          )
;

  output  [ 18: 0] CPU0_instruction_master_address_to_slave;
  output           CPU0_instruction_master_latency_counter;
  output  [ 31: 0] CPU0_instruction_master_readdata;
  output           CPU0_instruction_master_readdatavalid;
  output           CPU0_instruction_master_waitrequest;
  input   [ 18: 0] CPU0_instruction_master_address;
  input            CPU0_instruction_master_granted_CPU0_jtag_debug_module;
  input            CPU0_instruction_master_granted_CPU0_memory_s1;
  input            CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module;
  input            CPU0_instruction_master_qualified_request_CPU0_memory_s1;
  input            CPU0_instruction_master_read;
  input            CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module;
  input            CPU0_instruction_master_read_data_valid_CPU0_memory_s1;
  input            CPU0_instruction_master_requests_CPU0_jtag_debug_module;
  input            CPU0_instruction_master_requests_CPU0_memory_s1;
  input   [ 31: 0] CPU0_jtag_debug_module_readdata_from_sa;
  input   [ 31: 0] CPU0_memory_s1_readdata_from_sa;
  input            clk;
  input            d1_CPU0_jtag_debug_module_end_xfer;
  input            d1_CPU0_memory_s1_end_xfer;
  input            reset_n;

  reg     [ 18: 0] CPU0_instruction_master_address_last_time;
  wire    [ 18: 0] CPU0_instruction_master_address_to_slave;
  wire             CPU0_instruction_master_is_granted_some_slave;
  reg              CPU0_instruction_master_latency_counter;
  reg              CPU0_instruction_master_read_but_no_slave_selected;
  reg              CPU0_instruction_master_read_last_time;
  wire    [ 31: 0] CPU0_instruction_master_readdata;
  wire             CPU0_instruction_master_readdatavalid;
  wire             CPU0_instruction_master_run;
  wire             CPU0_instruction_master_waitrequest;
  reg              active_and_waiting_last_time;
  wire             latency_load_value;
  wire             p1_CPU0_instruction_master_latency_counter;
  wire             pre_flush_CPU0_instruction_master_readdatavalid;
  wire             r_0;
  //r_0 master_run cascaded wait assignment, which is an e_assign
  assign r_0 = 1 & (CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module | ~CPU0_instruction_master_requests_CPU0_jtag_debug_module) & (CPU0_instruction_master_granted_CPU0_jtag_debug_module | ~CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module) & ((~CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module | ~CPU0_instruction_master_read | (1 & ~d1_CPU0_jtag_debug_module_end_xfer & CPU0_instruction_master_read))) & 1 & (CPU0_instruction_master_qualified_request_CPU0_memory_s1 | ~CPU0_instruction_master_requests_CPU0_memory_s1) & (CPU0_instruction_master_granted_CPU0_memory_s1 | ~CPU0_instruction_master_qualified_request_CPU0_memory_s1) & ((~CPU0_instruction_master_qualified_request_CPU0_memory_s1 | ~(CPU0_instruction_master_read) | (1 & (CPU0_instruction_master_read))));

  //cascaded wait assignment, which is an e_assign
  assign CPU0_instruction_master_run = r_0;

  //optimize select-logic by passing only those address bits which matter.
  assign CPU0_instruction_master_address_to_slave = CPU0_instruction_master_address[18 : 0];

  //CPU0_instruction_master_read_but_no_slave_selected assignment, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_instruction_master_read_but_no_slave_selected <= 0;
      else 
        CPU0_instruction_master_read_but_no_slave_selected <= CPU0_instruction_master_read & CPU0_instruction_master_run & ~CPU0_instruction_master_is_granted_some_slave;
    end


  //some slave is getting selected, which is an e_mux
  assign CPU0_instruction_master_is_granted_some_slave = CPU0_instruction_master_granted_CPU0_jtag_debug_module |
    CPU0_instruction_master_granted_CPU0_memory_s1;

  //latent slave read data valids which may be flushed, which is an e_mux
  assign pre_flush_CPU0_instruction_master_readdatavalid = CPU0_instruction_master_read_data_valid_CPU0_memory_s1;

  //latent slave read data valid which is not flushed, which is an e_mux
  assign CPU0_instruction_master_readdatavalid = CPU0_instruction_master_read_but_no_slave_selected |
    pre_flush_CPU0_instruction_master_readdatavalid |
    CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module |
    CPU0_instruction_master_read_but_no_slave_selected |
    pre_flush_CPU0_instruction_master_readdatavalid;

  //CPU0/instruction_master readdata mux, which is an e_mux
  assign CPU0_instruction_master_readdata = ({32 {~(CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module & CPU0_instruction_master_read)}} | CPU0_jtag_debug_module_readdata_from_sa) &
    ({32 {~CPU0_instruction_master_read_data_valid_CPU0_memory_s1}} | CPU0_memory_s1_readdata_from_sa);

  //actual waitrequest port, which is an e_assign
  assign CPU0_instruction_master_waitrequest = ~CPU0_instruction_master_run;

  //latent max counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_instruction_master_latency_counter <= 0;
      else 
        CPU0_instruction_master_latency_counter <= p1_CPU0_instruction_master_latency_counter;
    end


  //latency counter load mux, which is an e_mux
  assign p1_CPU0_instruction_master_latency_counter = ((CPU0_instruction_master_run & CPU0_instruction_master_read))? latency_load_value :
    (CPU0_instruction_master_latency_counter)? CPU0_instruction_master_latency_counter - 1 :
    0;

  //read latency load values, which is an e_mux
  assign latency_load_value = {1 {CPU0_instruction_master_requests_CPU0_memory_s1}} & 1;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU0_instruction_master_address check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_instruction_master_address_last_time <= 0;
      else 
        CPU0_instruction_master_address_last_time <= CPU0_instruction_master_address;
    end


  //CPU0/instruction_master waited last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          active_and_waiting_last_time <= 0;
      else 
        active_and_waiting_last_time <= CPU0_instruction_master_waitrequest & (CPU0_instruction_master_read);
    end


  //CPU0_instruction_master_address matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU0_instruction_master_address != CPU0_instruction_master_address_last_time))
        begin
          $write("%0d ns: CPU0_instruction_master_address did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU0_instruction_master_read check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_instruction_master_read_last_time <= 0;
      else 
        CPU0_instruction_master_read_last_time <= CPU0_instruction_master_read;
    end


  //CPU0_instruction_master_read matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU0_instruction_master_read != CPU0_instruction_master_read_last_time))
        begin
          $write("%0d ns: CPU0_instruction_master_read did not heed wait!!!", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU0_JTAG_UART_avalon_jtag_slave_arbitrator (
                                                     // inputs:
                                                      CPU0_JTAG_UART_avalon_jtag_slave_dataavailable,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_irq,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_readdata,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_readyfordata,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_waitrequest,
                                                      CPU0_data_master_address_to_slave,
                                                      CPU0_data_master_latency_counter,
                                                      CPU0_data_master_read,
                                                      CPU0_data_master_write,
                                                      CPU0_data_master_writedata,
                                                      clk,
                                                      reset_n,

                                                     // outputs:
                                                      CPU0_JTAG_UART_avalon_jtag_slave_address,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_chipselect,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_read_n,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_reset_n,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_write_n,
                                                      CPU0_JTAG_UART_avalon_jtag_slave_writedata,
                                                      CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave,
                                                      CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave,
                                                      CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave,
                                                      CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave,
                                                      d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer
                                                   )
;

  output           CPU0_JTAG_UART_avalon_jtag_slave_address;
  output           CPU0_JTAG_UART_avalon_jtag_slave_chipselect;
  output           CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa;
  output           CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  output           CPU0_JTAG_UART_avalon_jtag_slave_read_n;
  output  [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa;
  output           CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa;
  output           CPU0_JTAG_UART_avalon_jtag_slave_reset_n;
  output           CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;
  output           CPU0_JTAG_UART_avalon_jtag_slave_write_n;
  output  [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_writedata;
  output           CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave;
  output           CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave;
  output           CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave;
  output           CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave;
  output           d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer;
  input            CPU0_JTAG_UART_avalon_jtag_slave_dataavailable;
  input            CPU0_JTAG_UART_avalon_jtag_slave_irq;
  input   [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_readdata;
  input            CPU0_JTAG_UART_avalon_jtag_slave_readyfordata;
  input            CPU0_JTAG_UART_avalon_jtag_slave_waitrequest;
  input   [ 18: 0] CPU0_data_master_address_to_slave;
  input            CPU0_data_master_latency_counter;
  input            CPU0_data_master_read;
  input            CPU0_data_master_write;
  input   [ 31: 0] CPU0_data_master_writedata;
  input            clk;
  input            reset_n;

  wire             CPU0_JTAG_UART_avalon_jtag_slave_address;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_allgrants;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_allow_new_arb_cycle;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_any_bursting_master_saved_grant;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_any_continuerequest;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_arb_counter_enable;
  reg              CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_arb_share_set_values;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_beginbursttransfer_internal;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_begins_xfer;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_chipselect;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_end_xfer;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_firsttransfer;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_grant_vector;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_in_a_read_cycle;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_in_a_write_cycle;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_master_qreq_vector;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_read_n;
  wire    [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa;
  reg              CPU0_JTAG_UART_avalon_jtag_slave_reg_firsttransfer;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_reset_n;
  reg              CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable2;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_waits_for_read;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_waits_for_write;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_write_n;
  wire    [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_writedata;
  wire             CPU0_data_master_arbiterlock;
  wire             CPU0_data_master_arbiterlock2;
  wire             CPU0_data_master_continuerequest;
  wire             CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             CPU0_data_master_saved_grant_CPU0_JTAG_UART_avalon_jtag_slave;
  reg              d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 18: 0] shifted_address_to_CPU0_JTAG_UART_avalon_jtag_slave_from_CPU0_data_master;
  wire             wait_for_CPU0_JTAG_UART_avalon_jtag_slave_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~CPU0_JTAG_UART_avalon_jtag_slave_end_xfer;
    end


  assign CPU0_JTAG_UART_avalon_jtag_slave_begins_xfer = ~d1_reasons_to_wait & ((CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave));
  //assign CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_readdata;

  assign CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave = ({CPU0_data_master_address_to_slave[18 : 3] , 3'b0} == 19'h43020) & (CPU0_data_master_read | CPU0_data_master_write);
  //assign CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_dataavailable so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_dataavailable;

  //assign CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_readyfordata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_readyfordata;

  //assign CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_waitrequest so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_waitrequest;

  //CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter set values, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_arb_share_set_values = 1;

  //CPU0_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests mux, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests = CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave;

  //CPU0_JTAG_UART_avalon_jtag_slave_any_bursting_master_saved_grant mux, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_any_bursting_master_saved_grant = 0;

  //CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value assignment, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value = CPU0_JTAG_UART_avalon_jtag_slave_firsttransfer ? (CPU0_JTAG_UART_avalon_jtag_slave_arb_share_set_values - 1) : |CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter ? (CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter - 1) : 0;

  //CPU0_JTAG_UART_avalon_jtag_slave_allgrants all slave grants, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_allgrants = |CPU0_JTAG_UART_avalon_jtag_slave_grant_vector;

  //CPU0_JTAG_UART_avalon_jtag_slave_end_xfer assignment, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_end_xfer = ~(CPU0_JTAG_UART_avalon_jtag_slave_waits_for_read | CPU0_JTAG_UART_avalon_jtag_slave_waits_for_write);

  //end_xfer_arb_share_counter_term_CPU0_JTAG_UART_avalon_jtag_slave arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_CPU0_JTAG_UART_avalon_jtag_slave = CPU0_JTAG_UART_avalon_jtag_slave_end_xfer & (~CPU0_JTAG_UART_avalon_jtag_slave_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter arbitration counter enable, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_arb_counter_enable = (end_xfer_arb_share_counter_term_CPU0_JTAG_UART_avalon_jtag_slave & CPU0_JTAG_UART_avalon_jtag_slave_allgrants) | (end_xfer_arb_share_counter_term_CPU0_JTAG_UART_avalon_jtag_slave & ~CPU0_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests);

  //CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter <= 0;
      else if (CPU0_JTAG_UART_avalon_jtag_slave_arb_counter_enable)
          CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter <= CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value;
    end


  //CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable <= 0;
      else if ((|CPU0_JTAG_UART_avalon_jtag_slave_master_qreq_vector & end_xfer_arb_share_counter_term_CPU0_JTAG_UART_avalon_jtag_slave) | (end_xfer_arb_share_counter_term_CPU0_JTAG_UART_avalon_jtag_slave & ~CPU0_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests))
          CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable <= |CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value;
    end


  //CPU0/data_master CPU0_JTAG_UART/avalon_jtag_slave arbiterlock, which is an e_assign
  assign CPU0_data_master_arbiterlock = CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable & CPU0_data_master_continuerequest;

  //CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable2 = |CPU0_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value;

  //CPU0/data_master CPU0_JTAG_UART/avalon_jtag_slave arbiterlock2, which is an e_assign
  assign CPU0_data_master_arbiterlock2 = CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable2 & CPU0_data_master_continuerequest;

  //CPU0_JTAG_UART_avalon_jtag_slave_any_continuerequest at least one master continues requesting, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_any_continuerequest = 1;

  //CPU0_data_master_continuerequest continued request, which is an e_assign
  assign CPU0_data_master_continuerequest = 1;

  assign CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave = CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave & ~((CPU0_data_master_read & ((CPU0_data_master_latency_counter != 0))));
  //local readdatavalid CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave, which is an e_mux
  assign CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave = CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave & CPU0_data_master_read & ~CPU0_JTAG_UART_avalon_jtag_slave_waits_for_read;

  //CPU0_JTAG_UART_avalon_jtag_slave_writedata mux, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_writedata = CPU0_data_master_writedata;

  //master is always granted when requested
  assign CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave = CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave;

  //CPU0/data_master saved-grant CPU0_JTAG_UART/avalon_jtag_slave, which is an e_assign
  assign CPU0_data_master_saved_grant_CPU0_JTAG_UART_avalon_jtag_slave = CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave;

  //allow new arb cycle for CPU0_JTAG_UART/avalon_jtag_slave, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign CPU0_JTAG_UART_avalon_jtag_slave_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign CPU0_JTAG_UART_avalon_jtag_slave_master_qreq_vector = 1;

  //CPU0_JTAG_UART_avalon_jtag_slave_reset_n assignment, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_reset_n = reset_n;

  assign CPU0_JTAG_UART_avalon_jtag_slave_chipselect = CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave;
  //CPU0_JTAG_UART_avalon_jtag_slave_firsttransfer first transaction, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_firsttransfer = CPU0_JTAG_UART_avalon_jtag_slave_begins_xfer ? CPU0_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer : CPU0_JTAG_UART_avalon_jtag_slave_reg_firsttransfer;

  //CPU0_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer first transaction, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer = ~(CPU0_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable & CPU0_JTAG_UART_avalon_jtag_slave_any_continuerequest);

  //CPU0_JTAG_UART_avalon_jtag_slave_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_JTAG_UART_avalon_jtag_slave_reg_firsttransfer <= 1'b1;
      else if (CPU0_JTAG_UART_avalon_jtag_slave_begins_xfer)
          CPU0_JTAG_UART_avalon_jtag_slave_reg_firsttransfer <= CPU0_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer;
    end


  //CPU0_JTAG_UART_avalon_jtag_slave_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_beginbursttransfer_internal = CPU0_JTAG_UART_avalon_jtag_slave_begins_xfer;

  //~CPU0_JTAG_UART_avalon_jtag_slave_read_n assignment, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_read_n = ~(CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave & CPU0_data_master_read);

  //~CPU0_JTAG_UART_avalon_jtag_slave_write_n assignment, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_write_n = ~(CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave & CPU0_data_master_write);

  assign shifted_address_to_CPU0_JTAG_UART_avalon_jtag_slave_from_CPU0_data_master = CPU0_data_master_address_to_slave;
  //CPU0_JTAG_UART_avalon_jtag_slave_address mux, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_address = shifted_address_to_CPU0_JTAG_UART_avalon_jtag_slave_from_CPU0_data_master >> 2;

  //d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer <= 1;
      else 
        d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer <= CPU0_JTAG_UART_avalon_jtag_slave_end_xfer;
    end


  //CPU0_JTAG_UART_avalon_jtag_slave_waits_for_read in a cycle, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_waits_for_read = CPU0_JTAG_UART_avalon_jtag_slave_in_a_read_cycle & CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;

  //CPU0_JTAG_UART_avalon_jtag_slave_in_a_read_cycle assignment, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_in_a_read_cycle = CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave & CPU0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = CPU0_JTAG_UART_avalon_jtag_slave_in_a_read_cycle;

  //CPU0_JTAG_UART_avalon_jtag_slave_waits_for_write in a cycle, which is an e_mux
  assign CPU0_JTAG_UART_avalon_jtag_slave_waits_for_write = CPU0_JTAG_UART_avalon_jtag_slave_in_a_write_cycle & CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;

  //CPU0_JTAG_UART_avalon_jtag_slave_in_a_write_cycle assignment, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_in_a_write_cycle = CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave & CPU0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = CPU0_JTAG_UART_avalon_jtag_slave_in_a_write_cycle;

  assign wait_for_CPU0_JTAG_UART_avalon_jtag_slave_counter = 0;
  //assign CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_irq so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa = CPU0_JTAG_UART_avalon_jtag_slave_irq;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU0_JTAG_UART/avalon_jtag_slave enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU0_memory_s1_arbitrator (
                                   // inputs:
                                    CPU0_data_master_address_to_slave,
                                    CPU0_data_master_byteenable,
                                    CPU0_data_master_latency_counter,
                                    CPU0_data_master_read,
                                    CPU0_data_master_write,
                                    CPU0_data_master_writedata,
                                    CPU0_instruction_master_address_to_slave,
                                    CPU0_instruction_master_latency_counter,
                                    CPU0_instruction_master_read,
                                    CPU0_memory_s1_readdata,
                                    clk,
                                    reset_n,

                                   // outputs:
                                    CPU0_data_master_granted_CPU0_memory_s1,
                                    CPU0_data_master_qualified_request_CPU0_memory_s1,
                                    CPU0_data_master_read_data_valid_CPU0_memory_s1,
                                    CPU0_data_master_requests_CPU0_memory_s1,
                                    CPU0_instruction_master_granted_CPU0_memory_s1,
                                    CPU0_instruction_master_qualified_request_CPU0_memory_s1,
                                    CPU0_instruction_master_read_data_valid_CPU0_memory_s1,
                                    CPU0_instruction_master_requests_CPU0_memory_s1,
                                    CPU0_memory_s1_address,
                                    CPU0_memory_s1_byteenable,
                                    CPU0_memory_s1_chipselect,
                                    CPU0_memory_s1_clken,
                                    CPU0_memory_s1_readdata_from_sa,
                                    CPU0_memory_s1_reset,
                                    CPU0_memory_s1_write,
                                    CPU0_memory_s1_writedata,
                                    d1_CPU0_memory_s1_end_xfer
                                 )
;

  output           CPU0_data_master_granted_CPU0_memory_s1;
  output           CPU0_data_master_qualified_request_CPU0_memory_s1;
  output           CPU0_data_master_read_data_valid_CPU0_memory_s1;
  output           CPU0_data_master_requests_CPU0_memory_s1;
  output           CPU0_instruction_master_granted_CPU0_memory_s1;
  output           CPU0_instruction_master_qualified_request_CPU0_memory_s1;
  output           CPU0_instruction_master_read_data_valid_CPU0_memory_s1;
  output           CPU0_instruction_master_requests_CPU0_memory_s1;
  output  [ 14: 0] CPU0_memory_s1_address;
  output  [  3: 0] CPU0_memory_s1_byteenable;
  output           CPU0_memory_s1_chipselect;
  output           CPU0_memory_s1_clken;
  output  [ 31: 0] CPU0_memory_s1_readdata_from_sa;
  output           CPU0_memory_s1_reset;
  output           CPU0_memory_s1_write;
  output  [ 31: 0] CPU0_memory_s1_writedata;
  output           d1_CPU0_memory_s1_end_xfer;
  input   [ 18: 0] CPU0_data_master_address_to_slave;
  input   [  3: 0] CPU0_data_master_byteenable;
  input            CPU0_data_master_latency_counter;
  input            CPU0_data_master_read;
  input            CPU0_data_master_write;
  input   [ 31: 0] CPU0_data_master_writedata;
  input   [ 18: 0] CPU0_instruction_master_address_to_slave;
  input            CPU0_instruction_master_latency_counter;
  input            CPU0_instruction_master_read;
  input   [ 31: 0] CPU0_memory_s1_readdata;
  input            clk;
  input            reset_n;

  wire             CPU0_data_master_arbiterlock;
  wire             CPU0_data_master_arbiterlock2;
  wire             CPU0_data_master_continuerequest;
  wire             CPU0_data_master_granted_CPU0_memory_s1;
  wire             CPU0_data_master_qualified_request_CPU0_memory_s1;
  wire             CPU0_data_master_read_data_valid_CPU0_memory_s1;
  reg              CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register;
  wire             CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register_in;
  wire             CPU0_data_master_requests_CPU0_memory_s1;
  wire             CPU0_data_master_saved_grant_CPU0_memory_s1;
  wire             CPU0_instruction_master_arbiterlock;
  wire             CPU0_instruction_master_arbiterlock2;
  wire             CPU0_instruction_master_continuerequest;
  wire             CPU0_instruction_master_granted_CPU0_memory_s1;
  wire             CPU0_instruction_master_qualified_request_CPU0_memory_s1;
  wire             CPU0_instruction_master_read_data_valid_CPU0_memory_s1;
  reg              CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register;
  wire             CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register_in;
  wire             CPU0_instruction_master_requests_CPU0_memory_s1;
  wire             CPU0_instruction_master_saved_grant_CPU0_memory_s1;
  wire    [ 14: 0] CPU0_memory_s1_address;
  wire             CPU0_memory_s1_allgrants;
  wire             CPU0_memory_s1_allow_new_arb_cycle;
  wire             CPU0_memory_s1_any_bursting_master_saved_grant;
  wire             CPU0_memory_s1_any_continuerequest;
  reg     [  1: 0] CPU0_memory_s1_arb_addend;
  wire             CPU0_memory_s1_arb_counter_enable;
  reg              CPU0_memory_s1_arb_share_counter;
  wire             CPU0_memory_s1_arb_share_counter_next_value;
  wire             CPU0_memory_s1_arb_share_set_values;
  wire    [  1: 0] CPU0_memory_s1_arb_winner;
  wire             CPU0_memory_s1_arbitration_holdoff_internal;
  wire             CPU0_memory_s1_beginbursttransfer_internal;
  wire             CPU0_memory_s1_begins_xfer;
  wire    [  3: 0] CPU0_memory_s1_byteenable;
  wire             CPU0_memory_s1_chipselect;
  wire    [  3: 0] CPU0_memory_s1_chosen_master_double_vector;
  wire    [  1: 0] CPU0_memory_s1_chosen_master_rot_left;
  wire             CPU0_memory_s1_clken;
  wire             CPU0_memory_s1_end_xfer;
  wire             CPU0_memory_s1_firsttransfer;
  wire    [  1: 0] CPU0_memory_s1_grant_vector;
  wire             CPU0_memory_s1_in_a_read_cycle;
  wire             CPU0_memory_s1_in_a_write_cycle;
  wire    [  1: 0] CPU0_memory_s1_master_qreq_vector;
  wire             CPU0_memory_s1_non_bursting_master_requests;
  wire    [ 31: 0] CPU0_memory_s1_readdata_from_sa;
  reg              CPU0_memory_s1_reg_firsttransfer;
  wire             CPU0_memory_s1_reset;
  reg     [  1: 0] CPU0_memory_s1_saved_chosen_master_vector;
  reg              CPU0_memory_s1_slavearbiterlockenable;
  wire             CPU0_memory_s1_slavearbiterlockenable2;
  wire             CPU0_memory_s1_unreg_firsttransfer;
  wire             CPU0_memory_s1_waits_for_read;
  wire             CPU0_memory_s1_waits_for_write;
  wire             CPU0_memory_s1_write;
  wire    [ 31: 0] CPU0_memory_s1_writedata;
  reg              d1_CPU0_memory_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_CPU0_memory_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_CPU0_data_master_granted_slave_CPU0_memory_s1;
  reg              last_cycle_CPU0_instruction_master_granted_slave_CPU0_memory_s1;
  wire             p1_CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register;
  wire             p1_CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register;
  wire    [ 18: 0] shifted_address_to_CPU0_memory_s1_from_CPU0_data_master;
  wire    [ 18: 0] shifted_address_to_CPU0_memory_s1_from_CPU0_instruction_master;
  wire             wait_for_CPU0_memory_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~CPU0_memory_s1_end_xfer;
    end


  assign CPU0_memory_s1_begins_xfer = ~d1_reasons_to_wait & ((CPU0_data_master_qualified_request_CPU0_memory_s1 | CPU0_instruction_master_qualified_request_CPU0_memory_s1));
  //assign CPU0_memory_s1_readdata_from_sa = CPU0_memory_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU0_memory_s1_readdata_from_sa = CPU0_memory_s1_readdata;

  assign CPU0_data_master_requests_CPU0_memory_s1 = ({CPU0_data_master_address_to_slave[18 : 17] , 17'b0} == 19'h20000) & (CPU0_data_master_read | CPU0_data_master_write);
  //CPU0_memory_s1_arb_share_counter set values, which is an e_mux
  assign CPU0_memory_s1_arb_share_set_values = 1;

  //CPU0_memory_s1_non_bursting_master_requests mux, which is an e_mux
  assign CPU0_memory_s1_non_bursting_master_requests = CPU0_data_master_requests_CPU0_memory_s1 |
    CPU0_instruction_master_requests_CPU0_memory_s1 |
    CPU0_data_master_requests_CPU0_memory_s1 |
    CPU0_instruction_master_requests_CPU0_memory_s1;

  //CPU0_memory_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign CPU0_memory_s1_any_bursting_master_saved_grant = 0;

  //CPU0_memory_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign CPU0_memory_s1_arb_share_counter_next_value = CPU0_memory_s1_firsttransfer ? (CPU0_memory_s1_arb_share_set_values - 1) : |CPU0_memory_s1_arb_share_counter ? (CPU0_memory_s1_arb_share_counter - 1) : 0;

  //CPU0_memory_s1_allgrants all slave grants, which is an e_mux
  assign CPU0_memory_s1_allgrants = (|CPU0_memory_s1_grant_vector) |
    (|CPU0_memory_s1_grant_vector) |
    (|CPU0_memory_s1_grant_vector) |
    (|CPU0_memory_s1_grant_vector);

  //CPU0_memory_s1_end_xfer assignment, which is an e_assign
  assign CPU0_memory_s1_end_xfer = ~(CPU0_memory_s1_waits_for_read | CPU0_memory_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_CPU0_memory_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_CPU0_memory_s1 = CPU0_memory_s1_end_xfer & (~CPU0_memory_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //CPU0_memory_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign CPU0_memory_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_CPU0_memory_s1 & CPU0_memory_s1_allgrants) | (end_xfer_arb_share_counter_term_CPU0_memory_s1 & ~CPU0_memory_s1_non_bursting_master_requests);

  //CPU0_memory_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_memory_s1_arb_share_counter <= 0;
      else if (CPU0_memory_s1_arb_counter_enable)
          CPU0_memory_s1_arb_share_counter <= CPU0_memory_s1_arb_share_counter_next_value;
    end


  //CPU0_memory_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_memory_s1_slavearbiterlockenable <= 0;
      else if ((|CPU0_memory_s1_master_qreq_vector & end_xfer_arb_share_counter_term_CPU0_memory_s1) | (end_xfer_arb_share_counter_term_CPU0_memory_s1 & ~CPU0_memory_s1_non_bursting_master_requests))
          CPU0_memory_s1_slavearbiterlockenable <= |CPU0_memory_s1_arb_share_counter_next_value;
    end


  //CPU0/data_master CPU0_memory/s1 arbiterlock, which is an e_assign
  assign CPU0_data_master_arbiterlock = CPU0_memory_s1_slavearbiterlockenable & CPU0_data_master_continuerequest;

  //CPU0_memory_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign CPU0_memory_s1_slavearbiterlockenable2 = |CPU0_memory_s1_arb_share_counter_next_value;

  //CPU0/data_master CPU0_memory/s1 arbiterlock2, which is an e_assign
  assign CPU0_data_master_arbiterlock2 = CPU0_memory_s1_slavearbiterlockenable2 & CPU0_data_master_continuerequest;

  //CPU0/instruction_master CPU0_memory/s1 arbiterlock, which is an e_assign
  assign CPU0_instruction_master_arbiterlock = CPU0_memory_s1_slavearbiterlockenable & CPU0_instruction_master_continuerequest;

  //CPU0/instruction_master CPU0_memory/s1 arbiterlock2, which is an e_assign
  assign CPU0_instruction_master_arbiterlock2 = CPU0_memory_s1_slavearbiterlockenable2 & CPU0_instruction_master_continuerequest;

  //CPU0/instruction_master granted CPU0_memory/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU0_instruction_master_granted_slave_CPU0_memory_s1 <= 0;
      else 
        last_cycle_CPU0_instruction_master_granted_slave_CPU0_memory_s1 <= CPU0_instruction_master_saved_grant_CPU0_memory_s1 ? 1 : (CPU0_memory_s1_arbitration_holdoff_internal | ~CPU0_instruction_master_requests_CPU0_memory_s1) ? 0 : last_cycle_CPU0_instruction_master_granted_slave_CPU0_memory_s1;
    end


  //CPU0_instruction_master_continuerequest continued request, which is an e_mux
  assign CPU0_instruction_master_continuerequest = last_cycle_CPU0_instruction_master_granted_slave_CPU0_memory_s1 & CPU0_instruction_master_requests_CPU0_memory_s1;

  //CPU0_memory_s1_any_continuerequest at least one master continues requesting, which is an e_mux
  assign CPU0_memory_s1_any_continuerequest = CPU0_instruction_master_continuerequest |
    CPU0_data_master_continuerequest;

  assign CPU0_data_master_qualified_request_CPU0_memory_s1 = CPU0_data_master_requests_CPU0_memory_s1 & ~((CPU0_data_master_read & ((1 < CPU0_data_master_latency_counter))) | CPU0_instruction_master_arbiterlock);
  //CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register_in mux for readlatency shift register, which is an e_mux
  assign CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register_in = CPU0_data_master_granted_CPU0_memory_s1 & CPU0_data_master_read & ~CPU0_memory_s1_waits_for_read;

  //shift register p1 CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register in if flush, otherwise shift left, which is an e_mux
  assign p1_CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register = {CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register, CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register_in};

  //CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register for remembering which master asked for a fixed latency read, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register <= 0;
      else 
        CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register <= p1_CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register;
    end


  //local readdatavalid CPU0_data_master_read_data_valid_CPU0_memory_s1, which is an e_mux
  assign CPU0_data_master_read_data_valid_CPU0_memory_s1 = CPU0_data_master_read_data_valid_CPU0_memory_s1_shift_register;

  //CPU0_memory_s1_writedata mux, which is an e_mux
  assign CPU0_memory_s1_writedata = CPU0_data_master_writedata;

  //mux CPU0_memory_s1_clken, which is an e_mux
  assign CPU0_memory_s1_clken = 1'b1;

  assign CPU0_instruction_master_requests_CPU0_memory_s1 = (({CPU0_instruction_master_address_to_slave[18 : 17] , 17'b0} == 19'h20000) & (CPU0_instruction_master_read)) & CPU0_instruction_master_read;
  //CPU0/data_master granted CPU0_memory/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU0_data_master_granted_slave_CPU0_memory_s1 <= 0;
      else 
        last_cycle_CPU0_data_master_granted_slave_CPU0_memory_s1 <= CPU0_data_master_saved_grant_CPU0_memory_s1 ? 1 : (CPU0_memory_s1_arbitration_holdoff_internal | ~CPU0_data_master_requests_CPU0_memory_s1) ? 0 : last_cycle_CPU0_data_master_granted_slave_CPU0_memory_s1;
    end


  //CPU0_data_master_continuerequest continued request, which is an e_mux
  assign CPU0_data_master_continuerequest = last_cycle_CPU0_data_master_granted_slave_CPU0_memory_s1 & CPU0_data_master_requests_CPU0_memory_s1;

  assign CPU0_instruction_master_qualified_request_CPU0_memory_s1 = CPU0_instruction_master_requests_CPU0_memory_s1 & ~((CPU0_instruction_master_read & ((1 < CPU0_instruction_master_latency_counter))) | CPU0_data_master_arbiterlock);
  //CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register_in mux for readlatency shift register, which is an e_mux
  assign CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register_in = CPU0_instruction_master_granted_CPU0_memory_s1 & CPU0_instruction_master_read & ~CPU0_memory_s1_waits_for_read;

  //shift register p1 CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register in if flush, otherwise shift left, which is an e_mux
  assign p1_CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register = {CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register, CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register_in};

  //CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register for remembering which master asked for a fixed latency read, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register <= 0;
      else 
        CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register <= p1_CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register;
    end


  //local readdatavalid CPU0_instruction_master_read_data_valid_CPU0_memory_s1, which is an e_mux
  assign CPU0_instruction_master_read_data_valid_CPU0_memory_s1 = CPU0_instruction_master_read_data_valid_CPU0_memory_s1_shift_register;

  //allow new arb cycle for CPU0_memory/s1, which is an e_assign
  assign CPU0_memory_s1_allow_new_arb_cycle = ~CPU0_data_master_arbiterlock & ~CPU0_instruction_master_arbiterlock;

  //CPU0/instruction_master assignment into master qualified-requests vector for CPU0_memory/s1, which is an e_assign
  assign CPU0_memory_s1_master_qreq_vector[0] = CPU0_instruction_master_qualified_request_CPU0_memory_s1;

  //CPU0/instruction_master grant CPU0_memory/s1, which is an e_assign
  assign CPU0_instruction_master_granted_CPU0_memory_s1 = CPU0_memory_s1_grant_vector[0];

  //CPU0/instruction_master saved-grant CPU0_memory/s1, which is an e_assign
  assign CPU0_instruction_master_saved_grant_CPU0_memory_s1 = CPU0_memory_s1_arb_winner[0] && CPU0_instruction_master_requests_CPU0_memory_s1;

  //CPU0/data_master assignment into master qualified-requests vector for CPU0_memory/s1, which is an e_assign
  assign CPU0_memory_s1_master_qreq_vector[1] = CPU0_data_master_qualified_request_CPU0_memory_s1;

  //CPU0/data_master grant CPU0_memory/s1, which is an e_assign
  assign CPU0_data_master_granted_CPU0_memory_s1 = CPU0_memory_s1_grant_vector[1];

  //CPU0/data_master saved-grant CPU0_memory/s1, which is an e_assign
  assign CPU0_data_master_saved_grant_CPU0_memory_s1 = CPU0_memory_s1_arb_winner[1] && CPU0_data_master_requests_CPU0_memory_s1;

  //CPU0_memory/s1 chosen-master double-vector, which is an e_assign
  assign CPU0_memory_s1_chosen_master_double_vector = {CPU0_memory_s1_master_qreq_vector, CPU0_memory_s1_master_qreq_vector} & ({~CPU0_memory_s1_master_qreq_vector, ~CPU0_memory_s1_master_qreq_vector} + CPU0_memory_s1_arb_addend);

  //stable onehot encoding of arb winner
  assign CPU0_memory_s1_arb_winner = (CPU0_memory_s1_allow_new_arb_cycle & | CPU0_memory_s1_grant_vector) ? CPU0_memory_s1_grant_vector : CPU0_memory_s1_saved_chosen_master_vector;

  //saved CPU0_memory_s1_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_memory_s1_saved_chosen_master_vector <= 0;
      else if (CPU0_memory_s1_allow_new_arb_cycle)
          CPU0_memory_s1_saved_chosen_master_vector <= |CPU0_memory_s1_grant_vector ? CPU0_memory_s1_grant_vector : CPU0_memory_s1_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign CPU0_memory_s1_grant_vector = {(CPU0_memory_s1_chosen_master_double_vector[1] | CPU0_memory_s1_chosen_master_double_vector[3]),
    (CPU0_memory_s1_chosen_master_double_vector[0] | CPU0_memory_s1_chosen_master_double_vector[2])};

  //CPU0_memory/s1 chosen master rotated left, which is an e_assign
  assign CPU0_memory_s1_chosen_master_rot_left = (CPU0_memory_s1_arb_winner << 1) ? (CPU0_memory_s1_arb_winner << 1) : 1;

  //CPU0_memory/s1's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_memory_s1_arb_addend <= 1;
      else if (|CPU0_memory_s1_grant_vector)
          CPU0_memory_s1_arb_addend <= CPU0_memory_s1_end_xfer? CPU0_memory_s1_chosen_master_rot_left : CPU0_memory_s1_grant_vector;
    end


  //~CPU0_memory_s1_reset assignment, which is an e_assign
  assign CPU0_memory_s1_reset = ~reset_n;

  assign CPU0_memory_s1_chipselect = CPU0_data_master_granted_CPU0_memory_s1 | CPU0_instruction_master_granted_CPU0_memory_s1;
  //CPU0_memory_s1_firsttransfer first transaction, which is an e_assign
  assign CPU0_memory_s1_firsttransfer = CPU0_memory_s1_begins_xfer ? CPU0_memory_s1_unreg_firsttransfer : CPU0_memory_s1_reg_firsttransfer;

  //CPU0_memory_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign CPU0_memory_s1_unreg_firsttransfer = ~(CPU0_memory_s1_slavearbiterlockenable & CPU0_memory_s1_any_continuerequest);

  //CPU0_memory_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_memory_s1_reg_firsttransfer <= 1'b1;
      else if (CPU0_memory_s1_begins_xfer)
          CPU0_memory_s1_reg_firsttransfer <= CPU0_memory_s1_unreg_firsttransfer;
    end


  //CPU0_memory_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign CPU0_memory_s1_beginbursttransfer_internal = CPU0_memory_s1_begins_xfer;

  //CPU0_memory_s1_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign CPU0_memory_s1_arbitration_holdoff_internal = CPU0_memory_s1_begins_xfer & CPU0_memory_s1_firsttransfer;

  //CPU0_memory_s1_write assignment, which is an e_mux
  assign CPU0_memory_s1_write = CPU0_data_master_granted_CPU0_memory_s1 & CPU0_data_master_write;

  assign shifted_address_to_CPU0_memory_s1_from_CPU0_data_master = CPU0_data_master_address_to_slave;
  //CPU0_memory_s1_address mux, which is an e_mux
  assign CPU0_memory_s1_address = (CPU0_data_master_granted_CPU0_memory_s1)? (shifted_address_to_CPU0_memory_s1_from_CPU0_data_master >> 2) :
    (shifted_address_to_CPU0_memory_s1_from_CPU0_instruction_master >> 2);

  assign shifted_address_to_CPU0_memory_s1_from_CPU0_instruction_master = CPU0_instruction_master_address_to_slave;
  //d1_CPU0_memory_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_CPU0_memory_s1_end_xfer <= 1;
      else 
        d1_CPU0_memory_s1_end_xfer <= CPU0_memory_s1_end_xfer;
    end


  //CPU0_memory_s1_waits_for_read in a cycle, which is an e_mux
  assign CPU0_memory_s1_waits_for_read = CPU0_memory_s1_in_a_read_cycle & 0;

  //CPU0_memory_s1_in_a_read_cycle assignment, which is an e_assign
  assign CPU0_memory_s1_in_a_read_cycle = (CPU0_data_master_granted_CPU0_memory_s1 & CPU0_data_master_read) | (CPU0_instruction_master_granted_CPU0_memory_s1 & CPU0_instruction_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = CPU0_memory_s1_in_a_read_cycle;

  //CPU0_memory_s1_waits_for_write in a cycle, which is an e_mux
  assign CPU0_memory_s1_waits_for_write = CPU0_memory_s1_in_a_write_cycle & 0;

  //CPU0_memory_s1_in_a_write_cycle assignment, which is an e_assign
  assign CPU0_memory_s1_in_a_write_cycle = CPU0_data_master_granted_CPU0_memory_s1 & CPU0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = CPU0_memory_s1_in_a_write_cycle;

  assign wait_for_CPU0_memory_s1_counter = 0;
  //CPU0_memory_s1_byteenable byte enable port mux, which is an e_mux
  assign CPU0_memory_s1_byteenable = (CPU0_data_master_granted_CPU0_memory_s1)? CPU0_data_master_byteenable :
    -1;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU0_memory/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_granted_CPU0_memory_s1 + CPU0_instruction_master_granted_CPU0_memory_s1 > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_saved_grant_CPU0_memory_s1 + CPU0_instruction_master_saved_grant_CPU0_memory_s1 > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU1_jtag_debug_module_arbitrator (
                                           // inputs:
                                            CPU1_data_master_address_to_slave,
                                            CPU1_data_master_byteenable,
                                            CPU1_data_master_debugaccess,
                                            CPU1_data_master_latency_counter,
                                            CPU1_data_master_read,
                                            CPU1_data_master_write,
                                            CPU1_data_master_writedata,
                                            CPU1_instruction_master_address_to_slave,
                                            CPU1_instruction_master_latency_counter,
                                            CPU1_instruction_master_read,
                                            CPU1_jtag_debug_module_readdata,
                                            CPU1_jtag_debug_module_resetrequest,
                                            clk,
                                            reset_n,

                                           // outputs:
                                            CPU1_data_master_granted_CPU1_jtag_debug_module,
                                            CPU1_data_master_qualified_request_CPU1_jtag_debug_module,
                                            CPU1_data_master_read_data_valid_CPU1_jtag_debug_module,
                                            CPU1_data_master_requests_CPU1_jtag_debug_module,
                                            CPU1_instruction_master_granted_CPU1_jtag_debug_module,
                                            CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module,
                                            CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module,
                                            CPU1_instruction_master_requests_CPU1_jtag_debug_module,
                                            CPU1_jtag_debug_module_address,
                                            CPU1_jtag_debug_module_begintransfer,
                                            CPU1_jtag_debug_module_byteenable,
                                            CPU1_jtag_debug_module_chipselect,
                                            CPU1_jtag_debug_module_debugaccess,
                                            CPU1_jtag_debug_module_readdata_from_sa,
                                            CPU1_jtag_debug_module_reset_n,
                                            CPU1_jtag_debug_module_resetrequest_from_sa,
                                            CPU1_jtag_debug_module_write,
                                            CPU1_jtag_debug_module_writedata,
                                            d1_CPU1_jtag_debug_module_end_xfer
                                         )
;

  output           CPU1_data_master_granted_CPU1_jtag_debug_module;
  output           CPU1_data_master_qualified_request_CPU1_jtag_debug_module;
  output           CPU1_data_master_read_data_valid_CPU1_jtag_debug_module;
  output           CPU1_data_master_requests_CPU1_jtag_debug_module;
  output           CPU1_instruction_master_granted_CPU1_jtag_debug_module;
  output           CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module;
  output           CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module;
  output           CPU1_instruction_master_requests_CPU1_jtag_debug_module;
  output  [  8: 0] CPU1_jtag_debug_module_address;
  output           CPU1_jtag_debug_module_begintransfer;
  output  [  3: 0] CPU1_jtag_debug_module_byteenable;
  output           CPU1_jtag_debug_module_chipselect;
  output           CPU1_jtag_debug_module_debugaccess;
  output  [ 31: 0] CPU1_jtag_debug_module_readdata_from_sa;
  output           CPU1_jtag_debug_module_reset_n;
  output           CPU1_jtag_debug_module_resetrequest_from_sa;
  output           CPU1_jtag_debug_module_write;
  output  [ 31: 0] CPU1_jtag_debug_module_writedata;
  output           d1_CPU1_jtag_debug_module_end_xfer;
  input   [ 18: 0] CPU1_data_master_address_to_slave;
  input   [  3: 0] CPU1_data_master_byteenable;
  input            CPU1_data_master_debugaccess;
  input            CPU1_data_master_latency_counter;
  input            CPU1_data_master_read;
  input            CPU1_data_master_write;
  input   [ 31: 0] CPU1_data_master_writedata;
  input   [ 18: 0] CPU1_instruction_master_address_to_slave;
  input            CPU1_instruction_master_latency_counter;
  input            CPU1_instruction_master_read;
  input   [ 31: 0] CPU1_jtag_debug_module_readdata;
  input            CPU1_jtag_debug_module_resetrequest;
  input            clk;
  input            reset_n;

  wire             CPU1_data_master_arbiterlock;
  wire             CPU1_data_master_arbiterlock2;
  wire             CPU1_data_master_continuerequest;
  wire             CPU1_data_master_granted_CPU1_jtag_debug_module;
  wire             CPU1_data_master_qualified_request_CPU1_jtag_debug_module;
  wire             CPU1_data_master_read_data_valid_CPU1_jtag_debug_module;
  wire             CPU1_data_master_requests_CPU1_jtag_debug_module;
  wire             CPU1_data_master_saved_grant_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_arbiterlock;
  wire             CPU1_instruction_master_arbiterlock2;
  wire             CPU1_instruction_master_continuerequest;
  wire             CPU1_instruction_master_granted_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_requests_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_saved_grant_CPU1_jtag_debug_module;
  wire    [  8: 0] CPU1_jtag_debug_module_address;
  wire             CPU1_jtag_debug_module_allgrants;
  wire             CPU1_jtag_debug_module_allow_new_arb_cycle;
  wire             CPU1_jtag_debug_module_any_bursting_master_saved_grant;
  wire             CPU1_jtag_debug_module_any_continuerequest;
  reg     [  1: 0] CPU1_jtag_debug_module_arb_addend;
  wire             CPU1_jtag_debug_module_arb_counter_enable;
  reg              CPU1_jtag_debug_module_arb_share_counter;
  wire             CPU1_jtag_debug_module_arb_share_counter_next_value;
  wire             CPU1_jtag_debug_module_arb_share_set_values;
  wire    [  1: 0] CPU1_jtag_debug_module_arb_winner;
  wire             CPU1_jtag_debug_module_arbitration_holdoff_internal;
  wire             CPU1_jtag_debug_module_beginbursttransfer_internal;
  wire             CPU1_jtag_debug_module_begins_xfer;
  wire             CPU1_jtag_debug_module_begintransfer;
  wire    [  3: 0] CPU1_jtag_debug_module_byteenable;
  wire             CPU1_jtag_debug_module_chipselect;
  wire    [  3: 0] CPU1_jtag_debug_module_chosen_master_double_vector;
  wire    [  1: 0] CPU1_jtag_debug_module_chosen_master_rot_left;
  wire             CPU1_jtag_debug_module_debugaccess;
  wire             CPU1_jtag_debug_module_end_xfer;
  wire             CPU1_jtag_debug_module_firsttransfer;
  wire    [  1: 0] CPU1_jtag_debug_module_grant_vector;
  wire             CPU1_jtag_debug_module_in_a_read_cycle;
  wire             CPU1_jtag_debug_module_in_a_write_cycle;
  wire    [  1: 0] CPU1_jtag_debug_module_master_qreq_vector;
  wire             CPU1_jtag_debug_module_non_bursting_master_requests;
  wire    [ 31: 0] CPU1_jtag_debug_module_readdata_from_sa;
  reg              CPU1_jtag_debug_module_reg_firsttransfer;
  wire             CPU1_jtag_debug_module_reset_n;
  wire             CPU1_jtag_debug_module_resetrequest_from_sa;
  reg     [  1: 0] CPU1_jtag_debug_module_saved_chosen_master_vector;
  reg              CPU1_jtag_debug_module_slavearbiterlockenable;
  wire             CPU1_jtag_debug_module_slavearbiterlockenable2;
  wire             CPU1_jtag_debug_module_unreg_firsttransfer;
  wire             CPU1_jtag_debug_module_waits_for_read;
  wire             CPU1_jtag_debug_module_waits_for_write;
  wire             CPU1_jtag_debug_module_write;
  wire    [ 31: 0] CPU1_jtag_debug_module_writedata;
  reg              d1_CPU1_jtag_debug_module_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_CPU1_jtag_debug_module;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_CPU1_data_master_granted_slave_CPU1_jtag_debug_module;
  reg              last_cycle_CPU1_instruction_master_granted_slave_CPU1_jtag_debug_module;
  wire    [ 18: 0] shifted_address_to_CPU1_jtag_debug_module_from_CPU1_data_master;
  wire    [ 18: 0] shifted_address_to_CPU1_jtag_debug_module_from_CPU1_instruction_master;
  wire             wait_for_CPU1_jtag_debug_module_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~CPU1_jtag_debug_module_end_xfer;
    end


  assign CPU1_jtag_debug_module_begins_xfer = ~d1_reasons_to_wait & ((CPU1_data_master_qualified_request_CPU1_jtag_debug_module | CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module));
  //assign CPU1_jtag_debug_module_readdata_from_sa = CPU1_jtag_debug_module_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU1_jtag_debug_module_readdata_from_sa = CPU1_jtag_debug_module_readdata;

  assign CPU1_data_master_requests_CPU1_jtag_debug_module = ({CPU1_data_master_address_to_slave[18 : 11] , 11'b0} == 19'h40800) & (CPU1_data_master_read | CPU1_data_master_write);
  //CPU1_jtag_debug_module_arb_share_counter set values, which is an e_mux
  assign CPU1_jtag_debug_module_arb_share_set_values = 1;

  //CPU1_jtag_debug_module_non_bursting_master_requests mux, which is an e_mux
  assign CPU1_jtag_debug_module_non_bursting_master_requests = CPU1_data_master_requests_CPU1_jtag_debug_module |
    CPU1_instruction_master_requests_CPU1_jtag_debug_module |
    CPU1_data_master_requests_CPU1_jtag_debug_module |
    CPU1_instruction_master_requests_CPU1_jtag_debug_module;

  //CPU1_jtag_debug_module_any_bursting_master_saved_grant mux, which is an e_mux
  assign CPU1_jtag_debug_module_any_bursting_master_saved_grant = 0;

  //CPU1_jtag_debug_module_arb_share_counter_next_value assignment, which is an e_assign
  assign CPU1_jtag_debug_module_arb_share_counter_next_value = CPU1_jtag_debug_module_firsttransfer ? (CPU1_jtag_debug_module_arb_share_set_values - 1) : |CPU1_jtag_debug_module_arb_share_counter ? (CPU1_jtag_debug_module_arb_share_counter - 1) : 0;

  //CPU1_jtag_debug_module_allgrants all slave grants, which is an e_mux
  assign CPU1_jtag_debug_module_allgrants = (|CPU1_jtag_debug_module_grant_vector) |
    (|CPU1_jtag_debug_module_grant_vector) |
    (|CPU1_jtag_debug_module_grant_vector) |
    (|CPU1_jtag_debug_module_grant_vector);

  //CPU1_jtag_debug_module_end_xfer assignment, which is an e_assign
  assign CPU1_jtag_debug_module_end_xfer = ~(CPU1_jtag_debug_module_waits_for_read | CPU1_jtag_debug_module_waits_for_write);

  //end_xfer_arb_share_counter_term_CPU1_jtag_debug_module arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_CPU1_jtag_debug_module = CPU1_jtag_debug_module_end_xfer & (~CPU1_jtag_debug_module_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //CPU1_jtag_debug_module_arb_share_counter arbitration counter enable, which is an e_assign
  assign CPU1_jtag_debug_module_arb_counter_enable = (end_xfer_arb_share_counter_term_CPU1_jtag_debug_module & CPU1_jtag_debug_module_allgrants) | (end_xfer_arb_share_counter_term_CPU1_jtag_debug_module & ~CPU1_jtag_debug_module_non_bursting_master_requests);

  //CPU1_jtag_debug_module_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_jtag_debug_module_arb_share_counter <= 0;
      else if (CPU1_jtag_debug_module_arb_counter_enable)
          CPU1_jtag_debug_module_arb_share_counter <= CPU1_jtag_debug_module_arb_share_counter_next_value;
    end


  //CPU1_jtag_debug_module_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_jtag_debug_module_slavearbiterlockenable <= 0;
      else if ((|CPU1_jtag_debug_module_master_qreq_vector & end_xfer_arb_share_counter_term_CPU1_jtag_debug_module) | (end_xfer_arb_share_counter_term_CPU1_jtag_debug_module & ~CPU1_jtag_debug_module_non_bursting_master_requests))
          CPU1_jtag_debug_module_slavearbiterlockenable <= |CPU1_jtag_debug_module_arb_share_counter_next_value;
    end


  //CPU1/data_master CPU1/jtag_debug_module arbiterlock, which is an e_assign
  assign CPU1_data_master_arbiterlock = CPU1_jtag_debug_module_slavearbiterlockenable & CPU1_data_master_continuerequest;

  //CPU1_jtag_debug_module_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign CPU1_jtag_debug_module_slavearbiterlockenable2 = |CPU1_jtag_debug_module_arb_share_counter_next_value;

  //CPU1/data_master CPU1/jtag_debug_module arbiterlock2, which is an e_assign
  assign CPU1_data_master_arbiterlock2 = CPU1_jtag_debug_module_slavearbiterlockenable2 & CPU1_data_master_continuerequest;

  //CPU1/instruction_master CPU1/jtag_debug_module arbiterlock, which is an e_assign
  assign CPU1_instruction_master_arbiterlock = CPU1_jtag_debug_module_slavearbiterlockenable & CPU1_instruction_master_continuerequest;

  //CPU1/instruction_master CPU1/jtag_debug_module arbiterlock2, which is an e_assign
  assign CPU1_instruction_master_arbiterlock2 = CPU1_jtag_debug_module_slavearbiterlockenable2 & CPU1_instruction_master_continuerequest;

  //CPU1/instruction_master granted CPU1/jtag_debug_module last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU1_instruction_master_granted_slave_CPU1_jtag_debug_module <= 0;
      else 
        last_cycle_CPU1_instruction_master_granted_slave_CPU1_jtag_debug_module <= CPU1_instruction_master_saved_grant_CPU1_jtag_debug_module ? 1 : (CPU1_jtag_debug_module_arbitration_holdoff_internal | ~CPU1_instruction_master_requests_CPU1_jtag_debug_module) ? 0 : last_cycle_CPU1_instruction_master_granted_slave_CPU1_jtag_debug_module;
    end


  //CPU1_instruction_master_continuerequest continued request, which is an e_mux
  assign CPU1_instruction_master_continuerequest = last_cycle_CPU1_instruction_master_granted_slave_CPU1_jtag_debug_module & CPU1_instruction_master_requests_CPU1_jtag_debug_module;

  //CPU1_jtag_debug_module_any_continuerequest at least one master continues requesting, which is an e_mux
  assign CPU1_jtag_debug_module_any_continuerequest = CPU1_instruction_master_continuerequest |
    CPU1_data_master_continuerequest;

  assign CPU1_data_master_qualified_request_CPU1_jtag_debug_module = CPU1_data_master_requests_CPU1_jtag_debug_module & ~((CPU1_data_master_read & ((CPU1_data_master_latency_counter != 0))) | CPU1_instruction_master_arbiterlock);
  //local readdatavalid CPU1_data_master_read_data_valid_CPU1_jtag_debug_module, which is an e_mux
  assign CPU1_data_master_read_data_valid_CPU1_jtag_debug_module = CPU1_data_master_granted_CPU1_jtag_debug_module & CPU1_data_master_read & ~CPU1_jtag_debug_module_waits_for_read;

  //CPU1_jtag_debug_module_writedata mux, which is an e_mux
  assign CPU1_jtag_debug_module_writedata = CPU1_data_master_writedata;

  assign CPU1_instruction_master_requests_CPU1_jtag_debug_module = (({CPU1_instruction_master_address_to_slave[18 : 11] , 11'b0} == 19'h40800) & (CPU1_instruction_master_read)) & CPU1_instruction_master_read;
  //CPU1/data_master granted CPU1/jtag_debug_module last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU1_data_master_granted_slave_CPU1_jtag_debug_module <= 0;
      else 
        last_cycle_CPU1_data_master_granted_slave_CPU1_jtag_debug_module <= CPU1_data_master_saved_grant_CPU1_jtag_debug_module ? 1 : (CPU1_jtag_debug_module_arbitration_holdoff_internal | ~CPU1_data_master_requests_CPU1_jtag_debug_module) ? 0 : last_cycle_CPU1_data_master_granted_slave_CPU1_jtag_debug_module;
    end


  //CPU1_data_master_continuerequest continued request, which is an e_mux
  assign CPU1_data_master_continuerequest = last_cycle_CPU1_data_master_granted_slave_CPU1_jtag_debug_module & CPU1_data_master_requests_CPU1_jtag_debug_module;

  assign CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module = CPU1_instruction_master_requests_CPU1_jtag_debug_module & ~((CPU1_instruction_master_read & ((CPU1_instruction_master_latency_counter != 0))) | CPU1_data_master_arbiterlock);
  //local readdatavalid CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module, which is an e_mux
  assign CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module = CPU1_instruction_master_granted_CPU1_jtag_debug_module & CPU1_instruction_master_read & ~CPU1_jtag_debug_module_waits_for_read;

  //allow new arb cycle for CPU1/jtag_debug_module, which is an e_assign
  assign CPU1_jtag_debug_module_allow_new_arb_cycle = ~CPU1_data_master_arbiterlock & ~CPU1_instruction_master_arbiterlock;

  //CPU1/instruction_master assignment into master qualified-requests vector for CPU1/jtag_debug_module, which is an e_assign
  assign CPU1_jtag_debug_module_master_qreq_vector[0] = CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module;

  //CPU1/instruction_master grant CPU1/jtag_debug_module, which is an e_assign
  assign CPU1_instruction_master_granted_CPU1_jtag_debug_module = CPU1_jtag_debug_module_grant_vector[0];

  //CPU1/instruction_master saved-grant CPU1/jtag_debug_module, which is an e_assign
  assign CPU1_instruction_master_saved_grant_CPU1_jtag_debug_module = CPU1_jtag_debug_module_arb_winner[0] && CPU1_instruction_master_requests_CPU1_jtag_debug_module;

  //CPU1/data_master assignment into master qualified-requests vector for CPU1/jtag_debug_module, which is an e_assign
  assign CPU1_jtag_debug_module_master_qreq_vector[1] = CPU1_data_master_qualified_request_CPU1_jtag_debug_module;

  //CPU1/data_master grant CPU1/jtag_debug_module, which is an e_assign
  assign CPU1_data_master_granted_CPU1_jtag_debug_module = CPU1_jtag_debug_module_grant_vector[1];

  //CPU1/data_master saved-grant CPU1/jtag_debug_module, which is an e_assign
  assign CPU1_data_master_saved_grant_CPU1_jtag_debug_module = CPU1_jtag_debug_module_arb_winner[1] && CPU1_data_master_requests_CPU1_jtag_debug_module;

  //CPU1/jtag_debug_module chosen-master double-vector, which is an e_assign
  assign CPU1_jtag_debug_module_chosen_master_double_vector = {CPU1_jtag_debug_module_master_qreq_vector, CPU1_jtag_debug_module_master_qreq_vector} & ({~CPU1_jtag_debug_module_master_qreq_vector, ~CPU1_jtag_debug_module_master_qreq_vector} + CPU1_jtag_debug_module_arb_addend);

  //stable onehot encoding of arb winner
  assign CPU1_jtag_debug_module_arb_winner = (CPU1_jtag_debug_module_allow_new_arb_cycle & | CPU1_jtag_debug_module_grant_vector) ? CPU1_jtag_debug_module_grant_vector : CPU1_jtag_debug_module_saved_chosen_master_vector;

  //saved CPU1_jtag_debug_module_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_jtag_debug_module_saved_chosen_master_vector <= 0;
      else if (CPU1_jtag_debug_module_allow_new_arb_cycle)
          CPU1_jtag_debug_module_saved_chosen_master_vector <= |CPU1_jtag_debug_module_grant_vector ? CPU1_jtag_debug_module_grant_vector : CPU1_jtag_debug_module_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign CPU1_jtag_debug_module_grant_vector = {(CPU1_jtag_debug_module_chosen_master_double_vector[1] | CPU1_jtag_debug_module_chosen_master_double_vector[3]),
    (CPU1_jtag_debug_module_chosen_master_double_vector[0] | CPU1_jtag_debug_module_chosen_master_double_vector[2])};

  //CPU1/jtag_debug_module chosen master rotated left, which is an e_assign
  assign CPU1_jtag_debug_module_chosen_master_rot_left = (CPU1_jtag_debug_module_arb_winner << 1) ? (CPU1_jtag_debug_module_arb_winner << 1) : 1;

  //CPU1/jtag_debug_module's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_jtag_debug_module_arb_addend <= 1;
      else if (|CPU1_jtag_debug_module_grant_vector)
          CPU1_jtag_debug_module_arb_addend <= CPU1_jtag_debug_module_end_xfer? CPU1_jtag_debug_module_chosen_master_rot_left : CPU1_jtag_debug_module_grant_vector;
    end


  assign CPU1_jtag_debug_module_begintransfer = CPU1_jtag_debug_module_begins_xfer;
  //CPU1_jtag_debug_module_reset_n assignment, which is an e_assign
  assign CPU1_jtag_debug_module_reset_n = reset_n;

  //assign CPU1_jtag_debug_module_resetrequest_from_sa = CPU1_jtag_debug_module_resetrequest so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU1_jtag_debug_module_resetrequest_from_sa = CPU1_jtag_debug_module_resetrequest;

  assign CPU1_jtag_debug_module_chipselect = CPU1_data_master_granted_CPU1_jtag_debug_module | CPU1_instruction_master_granted_CPU1_jtag_debug_module;
  //CPU1_jtag_debug_module_firsttransfer first transaction, which is an e_assign
  assign CPU1_jtag_debug_module_firsttransfer = CPU1_jtag_debug_module_begins_xfer ? CPU1_jtag_debug_module_unreg_firsttransfer : CPU1_jtag_debug_module_reg_firsttransfer;

  //CPU1_jtag_debug_module_unreg_firsttransfer first transaction, which is an e_assign
  assign CPU1_jtag_debug_module_unreg_firsttransfer = ~(CPU1_jtag_debug_module_slavearbiterlockenable & CPU1_jtag_debug_module_any_continuerequest);

  //CPU1_jtag_debug_module_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_jtag_debug_module_reg_firsttransfer <= 1'b1;
      else if (CPU1_jtag_debug_module_begins_xfer)
          CPU1_jtag_debug_module_reg_firsttransfer <= CPU1_jtag_debug_module_unreg_firsttransfer;
    end


  //CPU1_jtag_debug_module_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign CPU1_jtag_debug_module_beginbursttransfer_internal = CPU1_jtag_debug_module_begins_xfer;

  //CPU1_jtag_debug_module_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign CPU1_jtag_debug_module_arbitration_holdoff_internal = CPU1_jtag_debug_module_begins_xfer & CPU1_jtag_debug_module_firsttransfer;

  //CPU1_jtag_debug_module_write assignment, which is an e_mux
  assign CPU1_jtag_debug_module_write = CPU1_data_master_granted_CPU1_jtag_debug_module & CPU1_data_master_write;

  assign shifted_address_to_CPU1_jtag_debug_module_from_CPU1_data_master = CPU1_data_master_address_to_slave;
  //CPU1_jtag_debug_module_address mux, which is an e_mux
  assign CPU1_jtag_debug_module_address = (CPU1_data_master_granted_CPU1_jtag_debug_module)? (shifted_address_to_CPU1_jtag_debug_module_from_CPU1_data_master >> 2) :
    (shifted_address_to_CPU1_jtag_debug_module_from_CPU1_instruction_master >> 2);

  assign shifted_address_to_CPU1_jtag_debug_module_from_CPU1_instruction_master = CPU1_instruction_master_address_to_slave;
  //d1_CPU1_jtag_debug_module_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_CPU1_jtag_debug_module_end_xfer <= 1;
      else 
        d1_CPU1_jtag_debug_module_end_xfer <= CPU1_jtag_debug_module_end_xfer;
    end


  //CPU1_jtag_debug_module_waits_for_read in a cycle, which is an e_mux
  assign CPU1_jtag_debug_module_waits_for_read = CPU1_jtag_debug_module_in_a_read_cycle & CPU1_jtag_debug_module_begins_xfer;

  //CPU1_jtag_debug_module_in_a_read_cycle assignment, which is an e_assign
  assign CPU1_jtag_debug_module_in_a_read_cycle = (CPU1_data_master_granted_CPU1_jtag_debug_module & CPU1_data_master_read) | (CPU1_instruction_master_granted_CPU1_jtag_debug_module & CPU1_instruction_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = CPU1_jtag_debug_module_in_a_read_cycle;

  //CPU1_jtag_debug_module_waits_for_write in a cycle, which is an e_mux
  assign CPU1_jtag_debug_module_waits_for_write = CPU1_jtag_debug_module_in_a_write_cycle & 0;

  //CPU1_jtag_debug_module_in_a_write_cycle assignment, which is an e_assign
  assign CPU1_jtag_debug_module_in_a_write_cycle = CPU1_data_master_granted_CPU1_jtag_debug_module & CPU1_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = CPU1_jtag_debug_module_in_a_write_cycle;

  assign wait_for_CPU1_jtag_debug_module_counter = 0;
  //CPU1_jtag_debug_module_byteenable byte enable port mux, which is an e_mux
  assign CPU1_jtag_debug_module_byteenable = (CPU1_data_master_granted_CPU1_jtag_debug_module)? CPU1_data_master_byteenable :
    -1;

  //debugaccess mux, which is an e_mux
  assign CPU1_jtag_debug_module_debugaccess = (CPU1_data_master_granted_CPU1_jtag_debug_module)? CPU1_data_master_debugaccess :
    0;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU1/jtag_debug_module enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU1_data_master_granted_CPU1_jtag_debug_module + CPU1_instruction_master_granted_CPU1_jtag_debug_module > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU1_data_master_saved_grant_CPU1_jtag_debug_module + CPU1_instruction_master_saved_grant_CPU1_jtag_debug_module > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU1_data_master_arbitrator (
                                     // inputs:
                                      CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa,
                                      CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa,
                                      CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa,
                                      CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa,
                                      CPU1_data_master_address,
                                      CPU1_data_master_byteenable,
                                      CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave,
                                      CPU1_data_master_granted_CPU1_jtag_debug_module,
                                      CPU1_data_master_granted_CPU1_memory_s1,
                                      CPU1_data_master_granted_Comms_memory_s1,
                                      CPU1_data_master_granted_Comms_mutex_rx_s1,
                                      CPU1_data_master_granted_Comms_mutex_tx_s1,
                                      CPU1_data_master_granted_pio_LED_s1,
                                      CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave,
                                      CPU1_data_master_qualified_request_CPU1_jtag_debug_module,
                                      CPU1_data_master_qualified_request_CPU1_memory_s1,
                                      CPU1_data_master_qualified_request_Comms_memory_s1,
                                      CPU1_data_master_qualified_request_Comms_mutex_rx_s1,
                                      CPU1_data_master_qualified_request_Comms_mutex_tx_s1,
                                      CPU1_data_master_qualified_request_pio_LED_s1,
                                      CPU1_data_master_read,
                                      CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave,
                                      CPU1_data_master_read_data_valid_CPU1_jtag_debug_module,
                                      CPU1_data_master_read_data_valid_CPU1_memory_s1,
                                      CPU1_data_master_read_data_valid_Comms_memory_s1,
                                      CPU1_data_master_read_data_valid_Comms_mutex_rx_s1,
                                      CPU1_data_master_read_data_valid_Comms_mutex_tx_s1,
                                      CPU1_data_master_read_data_valid_pio_LED_s1,
                                      CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave,
                                      CPU1_data_master_requests_CPU1_jtag_debug_module,
                                      CPU1_data_master_requests_CPU1_memory_s1,
                                      CPU1_data_master_requests_Comms_memory_s1,
                                      CPU1_data_master_requests_Comms_mutex_rx_s1,
                                      CPU1_data_master_requests_Comms_mutex_tx_s1,
                                      CPU1_data_master_requests_pio_LED_s1,
                                      CPU1_data_master_write,
                                      CPU1_data_master_writedata,
                                      CPU1_jtag_debug_module_readdata_from_sa,
                                      CPU1_memory_s1_readdata_from_sa,
                                      Comms_memory_s1_readdata_from_sa,
                                      Comms_mutex_rx_s1_readdata_from_sa,
                                      Comms_mutex_tx_s1_readdata_from_sa,
                                      clk,
                                      d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer,
                                      d1_CPU1_jtag_debug_module_end_xfer,
                                      d1_CPU1_memory_s1_end_xfer,
                                      d1_Comms_memory_s1_end_xfer,
                                      d1_Comms_mutex_rx_s1_end_xfer,
                                      d1_Comms_mutex_tx_s1_end_xfer,
                                      d1_pio_LED_s1_end_xfer,
                                      pio_LED_s1_readdata_from_sa,
                                      reset_n,

                                     // outputs:
                                      CPU1_data_master_address_to_slave,
                                      CPU1_data_master_irq,
                                      CPU1_data_master_latency_counter,
                                      CPU1_data_master_readdata,
                                      CPU1_data_master_readdatavalid,
                                      CPU1_data_master_waitrequest
                                   )
;

  output  [ 18: 0] CPU1_data_master_address_to_slave;
  output  [ 31: 0] CPU1_data_master_irq;
  output           CPU1_data_master_latency_counter;
  output  [ 31: 0] CPU1_data_master_readdata;
  output           CPU1_data_master_readdatavalid;
  output           CPU1_data_master_waitrequest;
  input            CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  input            CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  input   [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa;
  input            CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;
  input   [ 18: 0] CPU1_data_master_address;
  input   [  3: 0] CPU1_data_master_byteenable;
  input            CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave;
  input            CPU1_data_master_granted_CPU1_jtag_debug_module;
  input            CPU1_data_master_granted_CPU1_memory_s1;
  input            CPU1_data_master_granted_Comms_memory_s1;
  input            CPU1_data_master_granted_Comms_mutex_rx_s1;
  input            CPU1_data_master_granted_Comms_mutex_tx_s1;
  input            CPU1_data_master_granted_pio_LED_s1;
  input            CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave;
  input            CPU1_data_master_qualified_request_CPU1_jtag_debug_module;
  input            CPU1_data_master_qualified_request_CPU1_memory_s1;
  input            CPU1_data_master_qualified_request_Comms_memory_s1;
  input            CPU1_data_master_qualified_request_Comms_mutex_rx_s1;
  input            CPU1_data_master_qualified_request_Comms_mutex_tx_s1;
  input            CPU1_data_master_qualified_request_pio_LED_s1;
  input            CPU1_data_master_read;
  input            CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave;
  input            CPU1_data_master_read_data_valid_CPU1_jtag_debug_module;
  input            CPU1_data_master_read_data_valid_CPU1_memory_s1;
  input            CPU1_data_master_read_data_valid_Comms_memory_s1;
  input            CPU1_data_master_read_data_valid_Comms_mutex_rx_s1;
  input            CPU1_data_master_read_data_valid_Comms_mutex_tx_s1;
  input            CPU1_data_master_read_data_valid_pio_LED_s1;
  input            CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave;
  input            CPU1_data_master_requests_CPU1_jtag_debug_module;
  input            CPU1_data_master_requests_CPU1_memory_s1;
  input            CPU1_data_master_requests_Comms_memory_s1;
  input            CPU1_data_master_requests_Comms_mutex_rx_s1;
  input            CPU1_data_master_requests_Comms_mutex_tx_s1;
  input            CPU1_data_master_requests_pio_LED_s1;
  input            CPU1_data_master_write;
  input   [ 31: 0] CPU1_data_master_writedata;
  input   [ 31: 0] CPU1_jtag_debug_module_readdata_from_sa;
  input   [ 31: 0] CPU1_memory_s1_readdata_from_sa;
  input   [ 31: 0] Comms_memory_s1_readdata_from_sa;
  input   [ 31: 0] Comms_mutex_rx_s1_readdata_from_sa;
  input   [ 31: 0] Comms_mutex_tx_s1_readdata_from_sa;
  input            clk;
  input            d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer;
  input            d1_CPU1_jtag_debug_module_end_xfer;
  input            d1_CPU1_memory_s1_end_xfer;
  input            d1_Comms_memory_s1_end_xfer;
  input            d1_Comms_mutex_rx_s1_end_xfer;
  input            d1_Comms_mutex_tx_s1_end_xfer;
  input            d1_pio_LED_s1_end_xfer;
  input   [ 31: 0] pio_LED_s1_readdata_from_sa;
  input            reset_n;

  reg     [ 18: 0] CPU1_data_master_address_last_time;
  wire    [ 18: 0] CPU1_data_master_address_to_slave;
  reg     [  3: 0] CPU1_data_master_byteenable_last_time;
  wire    [ 31: 0] CPU1_data_master_irq;
  wire             CPU1_data_master_is_granted_some_slave;
  reg              CPU1_data_master_latency_counter;
  reg              CPU1_data_master_read_but_no_slave_selected;
  reg              CPU1_data_master_read_last_time;
  wire    [ 31: 0] CPU1_data_master_readdata;
  wire             CPU1_data_master_readdatavalid;
  wire             CPU1_data_master_run;
  wire             CPU1_data_master_waitrequest;
  reg              CPU1_data_master_write_last_time;
  reg     [ 31: 0] CPU1_data_master_writedata_last_time;
  reg              active_and_waiting_last_time;
  wire             latency_load_value;
  wire             p1_CPU1_data_master_latency_counter;
  wire             pre_flush_CPU1_data_master_readdatavalid;
  wire             r_0;
  wire             r_1;
  //r_0 master_run cascaded wait assignment, which is an e_assign
  assign r_0 = 1 & (CPU1_data_master_qualified_request_CPU1_jtag_debug_module | ~CPU1_data_master_requests_CPU1_jtag_debug_module) & (CPU1_data_master_granted_CPU1_jtag_debug_module | ~CPU1_data_master_qualified_request_CPU1_jtag_debug_module) & ((~CPU1_data_master_qualified_request_CPU1_jtag_debug_module | ~CPU1_data_master_read | (1 & ~d1_CPU1_jtag_debug_module_end_xfer & CPU1_data_master_read))) & ((~CPU1_data_master_qualified_request_CPU1_jtag_debug_module | ~CPU1_data_master_write | (1 & CPU1_data_master_write))) & 1 & (CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave | ~CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave) & ((~CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave | ~(CPU1_data_master_read | CPU1_data_master_write) | (1 & ~CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa & (CPU1_data_master_read | CPU1_data_master_write)))) & ((~CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave | ~(CPU1_data_master_read | CPU1_data_master_write) | (1 & ~CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa & (CPU1_data_master_read | CPU1_data_master_write)))) & 1 & (CPU1_data_master_qualified_request_CPU1_memory_s1 | ~CPU1_data_master_requests_CPU1_memory_s1) & (CPU1_data_master_granted_CPU1_memory_s1 | ~CPU1_data_master_qualified_request_CPU1_memory_s1) & ((~CPU1_data_master_qualified_request_CPU1_memory_s1 | ~(CPU1_data_master_read | CPU1_data_master_write) | (1 & (CPU1_data_master_read | CPU1_data_master_write)))) & ((~CPU1_data_master_qualified_request_CPU1_memory_s1 | ~(CPU1_data_master_read | CPU1_data_master_write) | (1 & (CPU1_data_master_read | CPU1_data_master_write)))) & 1 & (CPU1_data_master_qualified_request_Comms_memory_s1 | ~CPU1_data_master_requests_Comms_memory_s1) & (CPU1_data_master_granted_Comms_memory_s1 | ~CPU1_data_master_qualified_request_Comms_memory_s1) & ((~CPU1_data_master_qualified_request_Comms_memory_s1 | ~(CPU1_data_master_read | CPU1_data_master_write) | (1 & (CPU1_data_master_read | CPU1_data_master_write)))) & ((~CPU1_data_master_qualified_request_Comms_memory_s1 | ~(CPU1_data_master_read | CPU1_data_master_write) | (1 & (CPU1_data_master_read | CPU1_data_master_write))));

  //cascaded wait assignment, which is an e_assign
  assign CPU1_data_master_run = r_0 & r_1;

  //r_1 master_run cascaded wait assignment, which is an e_assign
  assign r_1 = 1 & (CPU1_data_master_qualified_request_Comms_mutex_rx_s1 | ~CPU1_data_master_requests_Comms_mutex_rx_s1) & (CPU1_data_master_granted_Comms_mutex_rx_s1 | ~CPU1_data_master_qualified_request_Comms_mutex_rx_s1) & ((~CPU1_data_master_qualified_request_Comms_mutex_rx_s1 | ~CPU1_data_master_read | (1 & ~d1_Comms_mutex_rx_s1_end_xfer & CPU1_data_master_read))) & ((~CPU1_data_master_qualified_request_Comms_mutex_rx_s1 | ~CPU1_data_master_write | (1 & CPU1_data_master_write))) & 1 & (CPU1_data_master_qualified_request_Comms_mutex_tx_s1 | ~CPU1_data_master_requests_Comms_mutex_tx_s1) & (CPU1_data_master_granted_Comms_mutex_tx_s1 | ~CPU1_data_master_qualified_request_Comms_mutex_tx_s1) & ((~CPU1_data_master_qualified_request_Comms_mutex_tx_s1 | ~CPU1_data_master_read | (1 & ~d1_Comms_mutex_tx_s1_end_xfer & CPU1_data_master_read))) & ((~CPU1_data_master_qualified_request_Comms_mutex_tx_s1 | ~CPU1_data_master_write | (1 & CPU1_data_master_write))) & 1 & (CPU1_data_master_qualified_request_pio_LED_s1 | ~CPU1_data_master_requests_pio_LED_s1) & (CPU1_data_master_granted_pio_LED_s1 | ~CPU1_data_master_qualified_request_pio_LED_s1) & ((~CPU1_data_master_qualified_request_pio_LED_s1 | ~CPU1_data_master_read | (1 & ~d1_pio_LED_s1_end_xfer & CPU1_data_master_read))) & ((~CPU1_data_master_qualified_request_pio_LED_s1 | ~CPU1_data_master_write | (1 & CPU1_data_master_write)));

  //irq assign, which is an e_assign
  assign CPU1_data_master_irq = {1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa,
    CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa};

  //optimize select-logic by passing only those address bits which matter.
  assign CPU1_data_master_address_to_slave = {1'b1,
    CPU1_data_master_address[17 : 0]};

  //CPU1_data_master_read_but_no_slave_selected assignment, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_read_but_no_slave_selected <= 0;
      else 
        CPU1_data_master_read_but_no_slave_selected <= CPU1_data_master_read & CPU1_data_master_run & ~CPU1_data_master_is_granted_some_slave;
    end


  //some slave is getting selected, which is an e_mux
  assign CPU1_data_master_is_granted_some_slave = CPU1_data_master_granted_CPU1_jtag_debug_module |
    CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave |
    CPU1_data_master_granted_CPU1_memory_s1 |
    CPU1_data_master_granted_Comms_memory_s1 |
    CPU1_data_master_granted_Comms_mutex_rx_s1 |
    CPU1_data_master_granted_Comms_mutex_tx_s1 |
    CPU1_data_master_granted_pio_LED_s1;

  //latent slave read data valids which may be flushed, which is an e_mux
  assign pre_flush_CPU1_data_master_readdatavalid = CPU1_data_master_read_data_valid_CPU1_memory_s1 |
    CPU1_data_master_read_data_valid_Comms_memory_s1;

  //latent slave read data valid which is not flushed, which is an e_mux
  assign CPU1_data_master_readdatavalid = CPU1_data_master_read_but_no_slave_selected |
    pre_flush_CPU1_data_master_readdatavalid |
    CPU1_data_master_read_data_valid_CPU1_jtag_debug_module |
    CPU1_data_master_read_but_no_slave_selected |
    pre_flush_CPU1_data_master_readdatavalid |
    CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave |
    CPU1_data_master_read_but_no_slave_selected |
    pre_flush_CPU1_data_master_readdatavalid |
    CPU1_data_master_read_but_no_slave_selected |
    pre_flush_CPU1_data_master_readdatavalid |
    CPU1_data_master_read_but_no_slave_selected |
    pre_flush_CPU1_data_master_readdatavalid |
    CPU1_data_master_read_data_valid_Comms_mutex_rx_s1 |
    CPU1_data_master_read_but_no_slave_selected |
    pre_flush_CPU1_data_master_readdatavalid |
    CPU1_data_master_read_data_valid_Comms_mutex_tx_s1 |
    CPU1_data_master_read_but_no_slave_selected |
    pre_flush_CPU1_data_master_readdatavalid |
    CPU1_data_master_read_data_valid_pio_LED_s1;

  //CPU1/data_master readdata mux, which is an e_mux
  assign CPU1_data_master_readdata = ({32 {~(CPU1_data_master_qualified_request_CPU1_jtag_debug_module & CPU1_data_master_read)}} | CPU1_jtag_debug_module_readdata_from_sa) &
    ({32 {~(CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave & CPU1_data_master_read)}} | CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa) &
    ({32 {~CPU1_data_master_read_data_valid_CPU1_memory_s1}} | CPU1_memory_s1_readdata_from_sa) &
    ({32 {~CPU1_data_master_read_data_valid_Comms_memory_s1}} | Comms_memory_s1_readdata_from_sa) &
    ({32 {~(CPU1_data_master_qualified_request_Comms_mutex_rx_s1 & CPU1_data_master_read)}} | Comms_mutex_rx_s1_readdata_from_sa) &
    ({32 {~(CPU1_data_master_qualified_request_Comms_mutex_tx_s1 & CPU1_data_master_read)}} | Comms_mutex_tx_s1_readdata_from_sa) &
    ({32 {~(CPU1_data_master_qualified_request_pio_LED_s1 & CPU1_data_master_read)}} | pio_LED_s1_readdata_from_sa);

  //actual waitrequest port, which is an e_assign
  assign CPU1_data_master_waitrequest = ~CPU1_data_master_run;

  //latent max counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_latency_counter <= 0;
      else 
        CPU1_data_master_latency_counter <= p1_CPU1_data_master_latency_counter;
    end


  //latency counter load mux, which is an e_mux
  assign p1_CPU1_data_master_latency_counter = ((CPU1_data_master_run & CPU1_data_master_read))? latency_load_value :
    (CPU1_data_master_latency_counter)? CPU1_data_master_latency_counter - 1 :
    0;

  //read latency load values, which is an e_mux
  assign latency_load_value = ({1 {CPU1_data_master_requests_CPU1_memory_s1}} & 1) |
    ({1 {CPU1_data_master_requests_Comms_memory_s1}} & 1);


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU1_data_master_address check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_address_last_time <= 0;
      else 
        CPU1_data_master_address_last_time <= CPU1_data_master_address;
    end


  //CPU1/data_master waited last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          active_and_waiting_last_time <= 0;
      else 
        active_and_waiting_last_time <= CPU1_data_master_waitrequest & (CPU1_data_master_read | CPU1_data_master_write);
    end


  //CPU1_data_master_address matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU1_data_master_address != CPU1_data_master_address_last_time))
        begin
          $write("%0d ns: CPU1_data_master_address did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU1_data_master_byteenable check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_byteenable_last_time <= 0;
      else 
        CPU1_data_master_byteenable_last_time <= CPU1_data_master_byteenable;
    end


  //CPU1_data_master_byteenable matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU1_data_master_byteenable != CPU1_data_master_byteenable_last_time))
        begin
          $write("%0d ns: CPU1_data_master_byteenable did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU1_data_master_read check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_read_last_time <= 0;
      else 
        CPU1_data_master_read_last_time <= CPU1_data_master_read;
    end


  //CPU1_data_master_read matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU1_data_master_read != CPU1_data_master_read_last_time))
        begin
          $write("%0d ns: CPU1_data_master_read did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU1_data_master_write check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_write_last_time <= 0;
      else 
        CPU1_data_master_write_last_time <= CPU1_data_master_write;
    end


  //CPU1_data_master_write matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU1_data_master_write != CPU1_data_master_write_last_time))
        begin
          $write("%0d ns: CPU1_data_master_write did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU1_data_master_writedata check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_writedata_last_time <= 0;
      else 
        CPU1_data_master_writedata_last_time <= CPU1_data_master_writedata;
    end


  //CPU1_data_master_writedata matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU1_data_master_writedata != CPU1_data_master_writedata_last_time) & CPU1_data_master_write)
        begin
          $write("%0d ns: CPU1_data_master_writedata did not heed wait!!!", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU1_instruction_master_arbitrator (
                                            // inputs:
                                             CPU1_instruction_master_address,
                                             CPU1_instruction_master_granted_CPU1_jtag_debug_module,
                                             CPU1_instruction_master_granted_CPU1_memory_s1,
                                             CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module,
                                             CPU1_instruction_master_qualified_request_CPU1_memory_s1,
                                             CPU1_instruction_master_read,
                                             CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module,
                                             CPU1_instruction_master_read_data_valid_CPU1_memory_s1,
                                             CPU1_instruction_master_requests_CPU1_jtag_debug_module,
                                             CPU1_instruction_master_requests_CPU1_memory_s1,
                                             CPU1_jtag_debug_module_readdata_from_sa,
                                             CPU1_memory_s1_readdata_from_sa,
                                             clk,
                                             d1_CPU1_jtag_debug_module_end_xfer,
                                             d1_CPU1_memory_s1_end_xfer,
                                             reset_n,

                                            // outputs:
                                             CPU1_instruction_master_address_to_slave,
                                             CPU1_instruction_master_latency_counter,
                                             CPU1_instruction_master_readdata,
                                             CPU1_instruction_master_readdatavalid,
                                             CPU1_instruction_master_waitrequest
                                          )
;

  output  [ 18: 0] CPU1_instruction_master_address_to_slave;
  output           CPU1_instruction_master_latency_counter;
  output  [ 31: 0] CPU1_instruction_master_readdata;
  output           CPU1_instruction_master_readdatavalid;
  output           CPU1_instruction_master_waitrequest;
  input   [ 18: 0] CPU1_instruction_master_address;
  input            CPU1_instruction_master_granted_CPU1_jtag_debug_module;
  input            CPU1_instruction_master_granted_CPU1_memory_s1;
  input            CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module;
  input            CPU1_instruction_master_qualified_request_CPU1_memory_s1;
  input            CPU1_instruction_master_read;
  input            CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module;
  input            CPU1_instruction_master_read_data_valid_CPU1_memory_s1;
  input            CPU1_instruction_master_requests_CPU1_jtag_debug_module;
  input            CPU1_instruction_master_requests_CPU1_memory_s1;
  input   [ 31: 0] CPU1_jtag_debug_module_readdata_from_sa;
  input   [ 31: 0] CPU1_memory_s1_readdata_from_sa;
  input            clk;
  input            d1_CPU1_jtag_debug_module_end_xfer;
  input            d1_CPU1_memory_s1_end_xfer;
  input            reset_n;

  reg     [ 18: 0] CPU1_instruction_master_address_last_time;
  wire    [ 18: 0] CPU1_instruction_master_address_to_slave;
  wire             CPU1_instruction_master_is_granted_some_slave;
  reg              CPU1_instruction_master_latency_counter;
  reg              CPU1_instruction_master_read_but_no_slave_selected;
  reg              CPU1_instruction_master_read_last_time;
  wire    [ 31: 0] CPU1_instruction_master_readdata;
  wire             CPU1_instruction_master_readdatavalid;
  wire             CPU1_instruction_master_run;
  wire             CPU1_instruction_master_waitrequest;
  reg              active_and_waiting_last_time;
  wire             latency_load_value;
  wire             p1_CPU1_instruction_master_latency_counter;
  wire             pre_flush_CPU1_instruction_master_readdatavalid;
  wire             r_0;
  //r_0 master_run cascaded wait assignment, which is an e_assign
  assign r_0 = 1 & (CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module | ~CPU1_instruction_master_requests_CPU1_jtag_debug_module) & (CPU1_instruction_master_granted_CPU1_jtag_debug_module | ~CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module) & ((~CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module | ~CPU1_instruction_master_read | (1 & ~d1_CPU1_jtag_debug_module_end_xfer & CPU1_instruction_master_read))) & 1 & (CPU1_instruction_master_qualified_request_CPU1_memory_s1 | ~CPU1_instruction_master_requests_CPU1_memory_s1) & (CPU1_instruction_master_granted_CPU1_memory_s1 | ~CPU1_instruction_master_qualified_request_CPU1_memory_s1) & ((~CPU1_instruction_master_qualified_request_CPU1_memory_s1 | ~(CPU1_instruction_master_read) | (1 & (CPU1_instruction_master_read))));

  //cascaded wait assignment, which is an e_assign
  assign CPU1_instruction_master_run = r_0;

  //optimize select-logic by passing only those address bits which matter.
  assign CPU1_instruction_master_address_to_slave = {1'b1,
    CPU1_instruction_master_address[17 : 0]};

  //CPU1_instruction_master_read_but_no_slave_selected assignment, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_instruction_master_read_but_no_slave_selected <= 0;
      else 
        CPU1_instruction_master_read_but_no_slave_selected <= CPU1_instruction_master_read & CPU1_instruction_master_run & ~CPU1_instruction_master_is_granted_some_slave;
    end


  //some slave is getting selected, which is an e_mux
  assign CPU1_instruction_master_is_granted_some_slave = CPU1_instruction_master_granted_CPU1_jtag_debug_module |
    CPU1_instruction_master_granted_CPU1_memory_s1;

  //latent slave read data valids which may be flushed, which is an e_mux
  assign pre_flush_CPU1_instruction_master_readdatavalid = CPU1_instruction_master_read_data_valid_CPU1_memory_s1;

  //latent slave read data valid which is not flushed, which is an e_mux
  assign CPU1_instruction_master_readdatavalid = CPU1_instruction_master_read_but_no_slave_selected |
    pre_flush_CPU1_instruction_master_readdatavalid |
    CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module |
    CPU1_instruction_master_read_but_no_slave_selected |
    pre_flush_CPU1_instruction_master_readdatavalid;

  //CPU1/instruction_master readdata mux, which is an e_mux
  assign CPU1_instruction_master_readdata = ({32 {~(CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module & CPU1_instruction_master_read)}} | CPU1_jtag_debug_module_readdata_from_sa) &
    ({32 {~CPU1_instruction_master_read_data_valid_CPU1_memory_s1}} | CPU1_memory_s1_readdata_from_sa);

  //actual waitrequest port, which is an e_assign
  assign CPU1_instruction_master_waitrequest = ~CPU1_instruction_master_run;

  //latent max counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_instruction_master_latency_counter <= 0;
      else 
        CPU1_instruction_master_latency_counter <= p1_CPU1_instruction_master_latency_counter;
    end


  //latency counter load mux, which is an e_mux
  assign p1_CPU1_instruction_master_latency_counter = ((CPU1_instruction_master_run & CPU1_instruction_master_read))? latency_load_value :
    (CPU1_instruction_master_latency_counter)? CPU1_instruction_master_latency_counter - 1 :
    0;

  //read latency load values, which is an e_mux
  assign latency_load_value = {1 {CPU1_instruction_master_requests_CPU1_memory_s1}} & 1;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU1_instruction_master_address check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_instruction_master_address_last_time <= 0;
      else 
        CPU1_instruction_master_address_last_time <= CPU1_instruction_master_address;
    end


  //CPU1/instruction_master waited last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          active_and_waiting_last_time <= 0;
      else 
        active_and_waiting_last_time <= CPU1_instruction_master_waitrequest & (CPU1_instruction_master_read);
    end


  //CPU1_instruction_master_address matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU1_instruction_master_address != CPU1_instruction_master_address_last_time))
        begin
          $write("%0d ns: CPU1_instruction_master_address did not heed wait!!!", $time);
          $stop;
        end
    end


  //CPU1_instruction_master_read check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_instruction_master_read_last_time <= 0;
      else 
        CPU1_instruction_master_read_last_time <= CPU1_instruction_master_read;
    end


  //CPU1_instruction_master_read matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (CPU1_instruction_master_read != CPU1_instruction_master_read_last_time))
        begin
          $write("%0d ns: CPU1_instruction_master_read did not heed wait!!!", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU1_JTAG_UART_avalon_jtag_slave_arbitrator (
                                                     // inputs:
                                                      CPU1_JTAG_UART_avalon_jtag_slave_dataavailable,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_irq,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_readdata,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_readyfordata,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_waitrequest,
                                                      CPU1_data_master_address_to_slave,
                                                      CPU1_data_master_latency_counter,
                                                      CPU1_data_master_read,
                                                      CPU1_data_master_write,
                                                      CPU1_data_master_writedata,
                                                      clk,
                                                      reset_n,

                                                     // outputs:
                                                      CPU1_JTAG_UART_avalon_jtag_slave_address,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_chipselect,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_read_n,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_reset_n,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_write_n,
                                                      CPU1_JTAG_UART_avalon_jtag_slave_writedata,
                                                      CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave,
                                                      CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave,
                                                      CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave,
                                                      CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave,
                                                      d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer
                                                   )
;

  output           CPU1_JTAG_UART_avalon_jtag_slave_address;
  output           CPU1_JTAG_UART_avalon_jtag_slave_chipselect;
  output           CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa;
  output           CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  output           CPU1_JTAG_UART_avalon_jtag_slave_read_n;
  output  [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa;
  output           CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa;
  output           CPU1_JTAG_UART_avalon_jtag_slave_reset_n;
  output           CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;
  output           CPU1_JTAG_UART_avalon_jtag_slave_write_n;
  output  [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_writedata;
  output           CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave;
  output           CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave;
  output           CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave;
  output           CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave;
  output           d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer;
  input            CPU1_JTAG_UART_avalon_jtag_slave_dataavailable;
  input            CPU1_JTAG_UART_avalon_jtag_slave_irq;
  input   [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_readdata;
  input            CPU1_JTAG_UART_avalon_jtag_slave_readyfordata;
  input            CPU1_JTAG_UART_avalon_jtag_slave_waitrequest;
  input   [ 18: 0] CPU1_data_master_address_to_slave;
  input            CPU1_data_master_latency_counter;
  input            CPU1_data_master_read;
  input            CPU1_data_master_write;
  input   [ 31: 0] CPU1_data_master_writedata;
  input            clk;
  input            reset_n;

  wire             CPU1_JTAG_UART_avalon_jtag_slave_address;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_allgrants;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_allow_new_arb_cycle;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_any_bursting_master_saved_grant;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_any_continuerequest;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_arb_counter_enable;
  reg              CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_arb_share_set_values;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_beginbursttransfer_internal;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_begins_xfer;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_chipselect;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_end_xfer;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_firsttransfer;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_grant_vector;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_in_a_read_cycle;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_in_a_write_cycle;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_master_qreq_vector;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_read_n;
  wire    [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa;
  reg              CPU1_JTAG_UART_avalon_jtag_slave_reg_firsttransfer;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_reset_n;
  reg              CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable2;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_waits_for_read;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_waits_for_write;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_write_n;
  wire    [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_writedata;
  wire             CPU1_data_master_arbiterlock;
  wire             CPU1_data_master_arbiterlock2;
  wire             CPU1_data_master_continuerequest;
  wire             CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             CPU1_data_master_saved_grant_CPU1_JTAG_UART_avalon_jtag_slave;
  reg              d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 18: 0] shifted_address_to_CPU1_JTAG_UART_avalon_jtag_slave_from_CPU1_data_master;
  wire             wait_for_CPU1_JTAG_UART_avalon_jtag_slave_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~CPU1_JTAG_UART_avalon_jtag_slave_end_xfer;
    end


  assign CPU1_JTAG_UART_avalon_jtag_slave_begins_xfer = ~d1_reasons_to_wait & ((CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave));
  //assign CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_readdata;

  assign CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave = ({CPU1_data_master_address_to_slave[18 : 3] , 3'b0} == 19'h42000) & (CPU1_data_master_read | CPU1_data_master_write);
  //assign CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_dataavailable so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_dataavailable;

  //assign CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_readyfordata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_readyfordata;

  //assign CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_waitrequest so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_waitrequest;

  //CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter set values, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_arb_share_set_values = 1;

  //CPU1_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests mux, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests = CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave;

  //CPU1_JTAG_UART_avalon_jtag_slave_any_bursting_master_saved_grant mux, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_any_bursting_master_saved_grant = 0;

  //CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value assignment, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value = CPU1_JTAG_UART_avalon_jtag_slave_firsttransfer ? (CPU1_JTAG_UART_avalon_jtag_slave_arb_share_set_values - 1) : |CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter ? (CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter - 1) : 0;

  //CPU1_JTAG_UART_avalon_jtag_slave_allgrants all slave grants, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_allgrants = |CPU1_JTAG_UART_avalon_jtag_slave_grant_vector;

  //CPU1_JTAG_UART_avalon_jtag_slave_end_xfer assignment, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_end_xfer = ~(CPU1_JTAG_UART_avalon_jtag_slave_waits_for_read | CPU1_JTAG_UART_avalon_jtag_slave_waits_for_write);

  //end_xfer_arb_share_counter_term_CPU1_JTAG_UART_avalon_jtag_slave arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_CPU1_JTAG_UART_avalon_jtag_slave = CPU1_JTAG_UART_avalon_jtag_slave_end_xfer & (~CPU1_JTAG_UART_avalon_jtag_slave_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter arbitration counter enable, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_arb_counter_enable = (end_xfer_arb_share_counter_term_CPU1_JTAG_UART_avalon_jtag_slave & CPU1_JTAG_UART_avalon_jtag_slave_allgrants) | (end_xfer_arb_share_counter_term_CPU1_JTAG_UART_avalon_jtag_slave & ~CPU1_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests);

  //CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter <= 0;
      else if (CPU1_JTAG_UART_avalon_jtag_slave_arb_counter_enable)
          CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter <= CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value;
    end


  //CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable <= 0;
      else if ((|CPU1_JTAG_UART_avalon_jtag_slave_master_qreq_vector & end_xfer_arb_share_counter_term_CPU1_JTAG_UART_avalon_jtag_slave) | (end_xfer_arb_share_counter_term_CPU1_JTAG_UART_avalon_jtag_slave & ~CPU1_JTAG_UART_avalon_jtag_slave_non_bursting_master_requests))
          CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable <= |CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value;
    end


  //CPU1/data_master CPU1_JTAG_UART/avalon_jtag_slave arbiterlock, which is an e_assign
  assign CPU1_data_master_arbiterlock = CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable & CPU1_data_master_continuerequest;

  //CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable2 = |CPU1_JTAG_UART_avalon_jtag_slave_arb_share_counter_next_value;

  //CPU1/data_master CPU1_JTAG_UART/avalon_jtag_slave arbiterlock2, which is an e_assign
  assign CPU1_data_master_arbiterlock2 = CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable2 & CPU1_data_master_continuerequest;

  //CPU1_JTAG_UART_avalon_jtag_slave_any_continuerequest at least one master continues requesting, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_any_continuerequest = 1;

  //CPU1_data_master_continuerequest continued request, which is an e_assign
  assign CPU1_data_master_continuerequest = 1;

  assign CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave = CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave & ~((CPU1_data_master_read & ((CPU1_data_master_latency_counter != 0))));
  //local readdatavalid CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave, which is an e_mux
  assign CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave = CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave & CPU1_data_master_read & ~CPU1_JTAG_UART_avalon_jtag_slave_waits_for_read;

  //CPU1_JTAG_UART_avalon_jtag_slave_writedata mux, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_writedata = CPU1_data_master_writedata;

  //master is always granted when requested
  assign CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave = CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave;

  //CPU1/data_master saved-grant CPU1_JTAG_UART/avalon_jtag_slave, which is an e_assign
  assign CPU1_data_master_saved_grant_CPU1_JTAG_UART_avalon_jtag_slave = CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave;

  //allow new arb cycle for CPU1_JTAG_UART/avalon_jtag_slave, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign CPU1_JTAG_UART_avalon_jtag_slave_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign CPU1_JTAG_UART_avalon_jtag_slave_master_qreq_vector = 1;

  //CPU1_JTAG_UART_avalon_jtag_slave_reset_n assignment, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_reset_n = reset_n;

  assign CPU1_JTAG_UART_avalon_jtag_slave_chipselect = CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave;
  //CPU1_JTAG_UART_avalon_jtag_slave_firsttransfer first transaction, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_firsttransfer = CPU1_JTAG_UART_avalon_jtag_slave_begins_xfer ? CPU1_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer : CPU1_JTAG_UART_avalon_jtag_slave_reg_firsttransfer;

  //CPU1_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer first transaction, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer = ~(CPU1_JTAG_UART_avalon_jtag_slave_slavearbiterlockenable & CPU1_JTAG_UART_avalon_jtag_slave_any_continuerequest);

  //CPU1_JTAG_UART_avalon_jtag_slave_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_JTAG_UART_avalon_jtag_slave_reg_firsttransfer <= 1'b1;
      else if (CPU1_JTAG_UART_avalon_jtag_slave_begins_xfer)
          CPU1_JTAG_UART_avalon_jtag_slave_reg_firsttransfer <= CPU1_JTAG_UART_avalon_jtag_slave_unreg_firsttransfer;
    end


  //CPU1_JTAG_UART_avalon_jtag_slave_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_beginbursttransfer_internal = CPU1_JTAG_UART_avalon_jtag_slave_begins_xfer;

  //~CPU1_JTAG_UART_avalon_jtag_slave_read_n assignment, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_read_n = ~(CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave & CPU1_data_master_read);

  //~CPU1_JTAG_UART_avalon_jtag_slave_write_n assignment, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_write_n = ~(CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave & CPU1_data_master_write);

  assign shifted_address_to_CPU1_JTAG_UART_avalon_jtag_slave_from_CPU1_data_master = CPU1_data_master_address_to_slave;
  //CPU1_JTAG_UART_avalon_jtag_slave_address mux, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_address = shifted_address_to_CPU1_JTAG_UART_avalon_jtag_slave_from_CPU1_data_master >> 2;

  //d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer <= 1;
      else 
        d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer <= CPU1_JTAG_UART_avalon_jtag_slave_end_xfer;
    end


  //CPU1_JTAG_UART_avalon_jtag_slave_waits_for_read in a cycle, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_waits_for_read = CPU1_JTAG_UART_avalon_jtag_slave_in_a_read_cycle & CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;

  //CPU1_JTAG_UART_avalon_jtag_slave_in_a_read_cycle assignment, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_in_a_read_cycle = CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave & CPU1_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = CPU1_JTAG_UART_avalon_jtag_slave_in_a_read_cycle;

  //CPU1_JTAG_UART_avalon_jtag_slave_waits_for_write in a cycle, which is an e_mux
  assign CPU1_JTAG_UART_avalon_jtag_slave_waits_for_write = CPU1_JTAG_UART_avalon_jtag_slave_in_a_write_cycle & CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;

  //CPU1_JTAG_UART_avalon_jtag_slave_in_a_write_cycle assignment, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_in_a_write_cycle = CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave & CPU1_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = CPU1_JTAG_UART_avalon_jtag_slave_in_a_write_cycle;

  assign wait_for_CPU1_JTAG_UART_avalon_jtag_slave_counter = 0;
  //assign CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_irq so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa = CPU1_JTAG_UART_avalon_jtag_slave_irq;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU1_JTAG_UART/avalon_jtag_slave enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module CPU1_memory_s1_arbitrator (
                                   // inputs:
                                    CPU1_data_master_address_to_slave,
                                    CPU1_data_master_byteenable,
                                    CPU1_data_master_latency_counter,
                                    CPU1_data_master_read,
                                    CPU1_data_master_write,
                                    CPU1_data_master_writedata,
                                    CPU1_instruction_master_address_to_slave,
                                    CPU1_instruction_master_latency_counter,
                                    CPU1_instruction_master_read,
                                    CPU1_memory_s1_readdata,
                                    clk,
                                    reset_n,

                                   // outputs:
                                    CPU1_data_master_granted_CPU1_memory_s1,
                                    CPU1_data_master_qualified_request_CPU1_memory_s1,
                                    CPU1_data_master_read_data_valid_CPU1_memory_s1,
                                    CPU1_data_master_requests_CPU1_memory_s1,
                                    CPU1_instruction_master_granted_CPU1_memory_s1,
                                    CPU1_instruction_master_qualified_request_CPU1_memory_s1,
                                    CPU1_instruction_master_read_data_valid_CPU1_memory_s1,
                                    CPU1_instruction_master_requests_CPU1_memory_s1,
                                    CPU1_memory_s1_address,
                                    CPU1_memory_s1_byteenable,
                                    CPU1_memory_s1_chipselect,
                                    CPU1_memory_s1_clken,
                                    CPU1_memory_s1_readdata_from_sa,
                                    CPU1_memory_s1_reset,
                                    CPU1_memory_s1_write,
                                    CPU1_memory_s1_writedata,
                                    d1_CPU1_memory_s1_end_xfer
                                 )
;

  output           CPU1_data_master_granted_CPU1_memory_s1;
  output           CPU1_data_master_qualified_request_CPU1_memory_s1;
  output           CPU1_data_master_read_data_valid_CPU1_memory_s1;
  output           CPU1_data_master_requests_CPU1_memory_s1;
  output           CPU1_instruction_master_granted_CPU1_memory_s1;
  output           CPU1_instruction_master_qualified_request_CPU1_memory_s1;
  output           CPU1_instruction_master_read_data_valid_CPU1_memory_s1;
  output           CPU1_instruction_master_requests_CPU1_memory_s1;
  output  [ 14: 0] CPU1_memory_s1_address;
  output  [  3: 0] CPU1_memory_s1_byteenable;
  output           CPU1_memory_s1_chipselect;
  output           CPU1_memory_s1_clken;
  output  [ 31: 0] CPU1_memory_s1_readdata_from_sa;
  output           CPU1_memory_s1_reset;
  output           CPU1_memory_s1_write;
  output  [ 31: 0] CPU1_memory_s1_writedata;
  output           d1_CPU1_memory_s1_end_xfer;
  input   [ 18: 0] CPU1_data_master_address_to_slave;
  input   [  3: 0] CPU1_data_master_byteenable;
  input            CPU1_data_master_latency_counter;
  input            CPU1_data_master_read;
  input            CPU1_data_master_write;
  input   [ 31: 0] CPU1_data_master_writedata;
  input   [ 18: 0] CPU1_instruction_master_address_to_slave;
  input            CPU1_instruction_master_latency_counter;
  input            CPU1_instruction_master_read;
  input   [ 31: 0] CPU1_memory_s1_readdata;
  input            clk;
  input            reset_n;

  wire             CPU1_data_master_arbiterlock;
  wire             CPU1_data_master_arbiterlock2;
  wire             CPU1_data_master_continuerequest;
  wire             CPU1_data_master_granted_CPU1_memory_s1;
  wire             CPU1_data_master_qualified_request_CPU1_memory_s1;
  wire             CPU1_data_master_read_data_valid_CPU1_memory_s1;
  reg              CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register;
  wire             CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register_in;
  wire             CPU1_data_master_requests_CPU1_memory_s1;
  wire             CPU1_data_master_saved_grant_CPU1_memory_s1;
  wire             CPU1_instruction_master_arbiterlock;
  wire             CPU1_instruction_master_arbiterlock2;
  wire             CPU1_instruction_master_continuerequest;
  wire             CPU1_instruction_master_granted_CPU1_memory_s1;
  wire             CPU1_instruction_master_qualified_request_CPU1_memory_s1;
  wire             CPU1_instruction_master_read_data_valid_CPU1_memory_s1;
  reg              CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register;
  wire             CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register_in;
  wire             CPU1_instruction_master_requests_CPU1_memory_s1;
  wire             CPU1_instruction_master_saved_grant_CPU1_memory_s1;
  wire    [ 14: 0] CPU1_memory_s1_address;
  wire             CPU1_memory_s1_allgrants;
  wire             CPU1_memory_s1_allow_new_arb_cycle;
  wire             CPU1_memory_s1_any_bursting_master_saved_grant;
  wire             CPU1_memory_s1_any_continuerequest;
  reg     [  1: 0] CPU1_memory_s1_arb_addend;
  wire             CPU1_memory_s1_arb_counter_enable;
  reg              CPU1_memory_s1_arb_share_counter;
  wire             CPU1_memory_s1_arb_share_counter_next_value;
  wire             CPU1_memory_s1_arb_share_set_values;
  wire    [  1: 0] CPU1_memory_s1_arb_winner;
  wire             CPU1_memory_s1_arbitration_holdoff_internal;
  wire             CPU1_memory_s1_beginbursttransfer_internal;
  wire             CPU1_memory_s1_begins_xfer;
  wire    [  3: 0] CPU1_memory_s1_byteenable;
  wire             CPU1_memory_s1_chipselect;
  wire    [  3: 0] CPU1_memory_s1_chosen_master_double_vector;
  wire    [  1: 0] CPU1_memory_s1_chosen_master_rot_left;
  wire             CPU1_memory_s1_clken;
  wire             CPU1_memory_s1_end_xfer;
  wire             CPU1_memory_s1_firsttransfer;
  wire    [  1: 0] CPU1_memory_s1_grant_vector;
  wire             CPU1_memory_s1_in_a_read_cycle;
  wire             CPU1_memory_s1_in_a_write_cycle;
  wire    [  1: 0] CPU1_memory_s1_master_qreq_vector;
  wire             CPU1_memory_s1_non_bursting_master_requests;
  wire    [ 31: 0] CPU1_memory_s1_readdata_from_sa;
  reg              CPU1_memory_s1_reg_firsttransfer;
  wire             CPU1_memory_s1_reset;
  reg     [  1: 0] CPU1_memory_s1_saved_chosen_master_vector;
  reg              CPU1_memory_s1_slavearbiterlockenable;
  wire             CPU1_memory_s1_slavearbiterlockenable2;
  wire             CPU1_memory_s1_unreg_firsttransfer;
  wire             CPU1_memory_s1_waits_for_read;
  wire             CPU1_memory_s1_waits_for_write;
  wire             CPU1_memory_s1_write;
  wire    [ 31: 0] CPU1_memory_s1_writedata;
  reg              d1_CPU1_memory_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_CPU1_memory_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_CPU1_data_master_granted_slave_CPU1_memory_s1;
  reg              last_cycle_CPU1_instruction_master_granted_slave_CPU1_memory_s1;
  wire             p1_CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register;
  wire             p1_CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register;
  wire    [ 18: 0] shifted_address_to_CPU1_memory_s1_from_CPU1_data_master;
  wire    [ 18: 0] shifted_address_to_CPU1_memory_s1_from_CPU1_instruction_master;
  wire             wait_for_CPU1_memory_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~CPU1_memory_s1_end_xfer;
    end


  assign CPU1_memory_s1_begins_xfer = ~d1_reasons_to_wait & ((CPU1_data_master_qualified_request_CPU1_memory_s1 | CPU1_instruction_master_qualified_request_CPU1_memory_s1));
  //assign CPU1_memory_s1_readdata_from_sa = CPU1_memory_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign CPU1_memory_s1_readdata_from_sa = CPU1_memory_s1_readdata;

  assign CPU1_data_master_requests_CPU1_memory_s1 = ({CPU1_data_master_address_to_slave[18 : 17] , 17'b0} == 19'h60000) & (CPU1_data_master_read | CPU1_data_master_write);
  //CPU1_memory_s1_arb_share_counter set values, which is an e_mux
  assign CPU1_memory_s1_arb_share_set_values = 1;

  //CPU1_memory_s1_non_bursting_master_requests mux, which is an e_mux
  assign CPU1_memory_s1_non_bursting_master_requests = CPU1_data_master_requests_CPU1_memory_s1 |
    CPU1_instruction_master_requests_CPU1_memory_s1 |
    CPU1_data_master_requests_CPU1_memory_s1 |
    CPU1_instruction_master_requests_CPU1_memory_s1;

  //CPU1_memory_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign CPU1_memory_s1_any_bursting_master_saved_grant = 0;

  //CPU1_memory_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign CPU1_memory_s1_arb_share_counter_next_value = CPU1_memory_s1_firsttransfer ? (CPU1_memory_s1_arb_share_set_values - 1) : |CPU1_memory_s1_arb_share_counter ? (CPU1_memory_s1_arb_share_counter - 1) : 0;

  //CPU1_memory_s1_allgrants all slave grants, which is an e_mux
  assign CPU1_memory_s1_allgrants = (|CPU1_memory_s1_grant_vector) |
    (|CPU1_memory_s1_grant_vector) |
    (|CPU1_memory_s1_grant_vector) |
    (|CPU1_memory_s1_grant_vector);

  //CPU1_memory_s1_end_xfer assignment, which is an e_assign
  assign CPU1_memory_s1_end_xfer = ~(CPU1_memory_s1_waits_for_read | CPU1_memory_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_CPU1_memory_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_CPU1_memory_s1 = CPU1_memory_s1_end_xfer & (~CPU1_memory_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //CPU1_memory_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign CPU1_memory_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_CPU1_memory_s1 & CPU1_memory_s1_allgrants) | (end_xfer_arb_share_counter_term_CPU1_memory_s1 & ~CPU1_memory_s1_non_bursting_master_requests);

  //CPU1_memory_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_memory_s1_arb_share_counter <= 0;
      else if (CPU1_memory_s1_arb_counter_enable)
          CPU1_memory_s1_arb_share_counter <= CPU1_memory_s1_arb_share_counter_next_value;
    end


  //CPU1_memory_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_memory_s1_slavearbiterlockenable <= 0;
      else if ((|CPU1_memory_s1_master_qreq_vector & end_xfer_arb_share_counter_term_CPU1_memory_s1) | (end_xfer_arb_share_counter_term_CPU1_memory_s1 & ~CPU1_memory_s1_non_bursting_master_requests))
          CPU1_memory_s1_slavearbiterlockenable <= |CPU1_memory_s1_arb_share_counter_next_value;
    end


  //CPU1/data_master CPU1_memory/s1 arbiterlock, which is an e_assign
  assign CPU1_data_master_arbiterlock = CPU1_memory_s1_slavearbiterlockenable & CPU1_data_master_continuerequest;

  //CPU1_memory_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign CPU1_memory_s1_slavearbiterlockenable2 = |CPU1_memory_s1_arb_share_counter_next_value;

  //CPU1/data_master CPU1_memory/s1 arbiterlock2, which is an e_assign
  assign CPU1_data_master_arbiterlock2 = CPU1_memory_s1_slavearbiterlockenable2 & CPU1_data_master_continuerequest;

  //CPU1/instruction_master CPU1_memory/s1 arbiterlock, which is an e_assign
  assign CPU1_instruction_master_arbiterlock = CPU1_memory_s1_slavearbiterlockenable & CPU1_instruction_master_continuerequest;

  //CPU1/instruction_master CPU1_memory/s1 arbiterlock2, which is an e_assign
  assign CPU1_instruction_master_arbiterlock2 = CPU1_memory_s1_slavearbiterlockenable2 & CPU1_instruction_master_continuerequest;

  //CPU1/instruction_master granted CPU1_memory/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU1_instruction_master_granted_slave_CPU1_memory_s1 <= 0;
      else 
        last_cycle_CPU1_instruction_master_granted_slave_CPU1_memory_s1 <= CPU1_instruction_master_saved_grant_CPU1_memory_s1 ? 1 : (CPU1_memory_s1_arbitration_holdoff_internal | ~CPU1_instruction_master_requests_CPU1_memory_s1) ? 0 : last_cycle_CPU1_instruction_master_granted_slave_CPU1_memory_s1;
    end


  //CPU1_instruction_master_continuerequest continued request, which is an e_mux
  assign CPU1_instruction_master_continuerequest = last_cycle_CPU1_instruction_master_granted_slave_CPU1_memory_s1 & CPU1_instruction_master_requests_CPU1_memory_s1;

  //CPU1_memory_s1_any_continuerequest at least one master continues requesting, which is an e_mux
  assign CPU1_memory_s1_any_continuerequest = CPU1_instruction_master_continuerequest |
    CPU1_data_master_continuerequest;

  assign CPU1_data_master_qualified_request_CPU1_memory_s1 = CPU1_data_master_requests_CPU1_memory_s1 & ~((CPU1_data_master_read & ((1 < CPU1_data_master_latency_counter))) | CPU1_instruction_master_arbiterlock);
  //CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register_in mux for readlatency shift register, which is an e_mux
  assign CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register_in = CPU1_data_master_granted_CPU1_memory_s1 & CPU1_data_master_read & ~CPU1_memory_s1_waits_for_read;

  //shift register p1 CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register in if flush, otherwise shift left, which is an e_mux
  assign p1_CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register = {CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register, CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register_in};

  //CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register for remembering which master asked for a fixed latency read, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register <= 0;
      else 
        CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register <= p1_CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register;
    end


  //local readdatavalid CPU1_data_master_read_data_valid_CPU1_memory_s1, which is an e_mux
  assign CPU1_data_master_read_data_valid_CPU1_memory_s1 = CPU1_data_master_read_data_valid_CPU1_memory_s1_shift_register;

  //CPU1_memory_s1_writedata mux, which is an e_mux
  assign CPU1_memory_s1_writedata = CPU1_data_master_writedata;

  //mux CPU1_memory_s1_clken, which is an e_mux
  assign CPU1_memory_s1_clken = 1'b1;

  assign CPU1_instruction_master_requests_CPU1_memory_s1 = (({CPU1_instruction_master_address_to_slave[18 : 17] , 17'b0} == 19'h60000) & (CPU1_instruction_master_read)) & CPU1_instruction_master_read;
  //CPU1/data_master granted CPU1_memory/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU1_data_master_granted_slave_CPU1_memory_s1 <= 0;
      else 
        last_cycle_CPU1_data_master_granted_slave_CPU1_memory_s1 <= CPU1_data_master_saved_grant_CPU1_memory_s1 ? 1 : (CPU1_memory_s1_arbitration_holdoff_internal | ~CPU1_data_master_requests_CPU1_memory_s1) ? 0 : last_cycle_CPU1_data_master_granted_slave_CPU1_memory_s1;
    end


  //CPU1_data_master_continuerequest continued request, which is an e_mux
  assign CPU1_data_master_continuerequest = last_cycle_CPU1_data_master_granted_slave_CPU1_memory_s1 & CPU1_data_master_requests_CPU1_memory_s1;

  assign CPU1_instruction_master_qualified_request_CPU1_memory_s1 = CPU1_instruction_master_requests_CPU1_memory_s1 & ~((CPU1_instruction_master_read & ((1 < CPU1_instruction_master_latency_counter))) | CPU1_data_master_arbiterlock);
  //CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register_in mux for readlatency shift register, which is an e_mux
  assign CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register_in = CPU1_instruction_master_granted_CPU1_memory_s1 & CPU1_instruction_master_read & ~CPU1_memory_s1_waits_for_read;

  //shift register p1 CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register in if flush, otherwise shift left, which is an e_mux
  assign p1_CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register = {CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register, CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register_in};

  //CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register for remembering which master asked for a fixed latency read, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register <= 0;
      else 
        CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register <= p1_CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register;
    end


  //local readdatavalid CPU1_instruction_master_read_data_valid_CPU1_memory_s1, which is an e_mux
  assign CPU1_instruction_master_read_data_valid_CPU1_memory_s1 = CPU1_instruction_master_read_data_valid_CPU1_memory_s1_shift_register;

  //allow new arb cycle for CPU1_memory/s1, which is an e_assign
  assign CPU1_memory_s1_allow_new_arb_cycle = ~CPU1_data_master_arbiterlock & ~CPU1_instruction_master_arbiterlock;

  //CPU1/instruction_master assignment into master qualified-requests vector for CPU1_memory/s1, which is an e_assign
  assign CPU1_memory_s1_master_qreq_vector[0] = CPU1_instruction_master_qualified_request_CPU1_memory_s1;

  //CPU1/instruction_master grant CPU1_memory/s1, which is an e_assign
  assign CPU1_instruction_master_granted_CPU1_memory_s1 = CPU1_memory_s1_grant_vector[0];

  //CPU1/instruction_master saved-grant CPU1_memory/s1, which is an e_assign
  assign CPU1_instruction_master_saved_grant_CPU1_memory_s1 = CPU1_memory_s1_arb_winner[0] && CPU1_instruction_master_requests_CPU1_memory_s1;

  //CPU1/data_master assignment into master qualified-requests vector for CPU1_memory/s1, which is an e_assign
  assign CPU1_memory_s1_master_qreq_vector[1] = CPU1_data_master_qualified_request_CPU1_memory_s1;

  //CPU1/data_master grant CPU1_memory/s1, which is an e_assign
  assign CPU1_data_master_granted_CPU1_memory_s1 = CPU1_memory_s1_grant_vector[1];

  //CPU1/data_master saved-grant CPU1_memory/s1, which is an e_assign
  assign CPU1_data_master_saved_grant_CPU1_memory_s1 = CPU1_memory_s1_arb_winner[1] && CPU1_data_master_requests_CPU1_memory_s1;

  //CPU1_memory/s1 chosen-master double-vector, which is an e_assign
  assign CPU1_memory_s1_chosen_master_double_vector = {CPU1_memory_s1_master_qreq_vector, CPU1_memory_s1_master_qreq_vector} & ({~CPU1_memory_s1_master_qreq_vector, ~CPU1_memory_s1_master_qreq_vector} + CPU1_memory_s1_arb_addend);

  //stable onehot encoding of arb winner
  assign CPU1_memory_s1_arb_winner = (CPU1_memory_s1_allow_new_arb_cycle & | CPU1_memory_s1_grant_vector) ? CPU1_memory_s1_grant_vector : CPU1_memory_s1_saved_chosen_master_vector;

  //saved CPU1_memory_s1_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_memory_s1_saved_chosen_master_vector <= 0;
      else if (CPU1_memory_s1_allow_new_arb_cycle)
          CPU1_memory_s1_saved_chosen_master_vector <= |CPU1_memory_s1_grant_vector ? CPU1_memory_s1_grant_vector : CPU1_memory_s1_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign CPU1_memory_s1_grant_vector = {(CPU1_memory_s1_chosen_master_double_vector[1] | CPU1_memory_s1_chosen_master_double_vector[3]),
    (CPU1_memory_s1_chosen_master_double_vector[0] | CPU1_memory_s1_chosen_master_double_vector[2])};

  //CPU1_memory/s1 chosen master rotated left, which is an e_assign
  assign CPU1_memory_s1_chosen_master_rot_left = (CPU1_memory_s1_arb_winner << 1) ? (CPU1_memory_s1_arb_winner << 1) : 1;

  //CPU1_memory/s1's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_memory_s1_arb_addend <= 1;
      else if (|CPU1_memory_s1_grant_vector)
          CPU1_memory_s1_arb_addend <= CPU1_memory_s1_end_xfer? CPU1_memory_s1_chosen_master_rot_left : CPU1_memory_s1_grant_vector;
    end


  //~CPU1_memory_s1_reset assignment, which is an e_assign
  assign CPU1_memory_s1_reset = ~reset_n;

  assign CPU1_memory_s1_chipselect = CPU1_data_master_granted_CPU1_memory_s1 | CPU1_instruction_master_granted_CPU1_memory_s1;
  //CPU1_memory_s1_firsttransfer first transaction, which is an e_assign
  assign CPU1_memory_s1_firsttransfer = CPU1_memory_s1_begins_xfer ? CPU1_memory_s1_unreg_firsttransfer : CPU1_memory_s1_reg_firsttransfer;

  //CPU1_memory_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign CPU1_memory_s1_unreg_firsttransfer = ~(CPU1_memory_s1_slavearbiterlockenable & CPU1_memory_s1_any_continuerequest);

  //CPU1_memory_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_memory_s1_reg_firsttransfer <= 1'b1;
      else if (CPU1_memory_s1_begins_xfer)
          CPU1_memory_s1_reg_firsttransfer <= CPU1_memory_s1_unreg_firsttransfer;
    end


  //CPU1_memory_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign CPU1_memory_s1_beginbursttransfer_internal = CPU1_memory_s1_begins_xfer;

  //CPU1_memory_s1_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign CPU1_memory_s1_arbitration_holdoff_internal = CPU1_memory_s1_begins_xfer & CPU1_memory_s1_firsttransfer;

  //CPU1_memory_s1_write assignment, which is an e_mux
  assign CPU1_memory_s1_write = CPU1_data_master_granted_CPU1_memory_s1 & CPU1_data_master_write;

  assign shifted_address_to_CPU1_memory_s1_from_CPU1_data_master = CPU1_data_master_address_to_slave;
  //CPU1_memory_s1_address mux, which is an e_mux
  assign CPU1_memory_s1_address = (CPU1_data_master_granted_CPU1_memory_s1)? (shifted_address_to_CPU1_memory_s1_from_CPU1_data_master >> 2) :
    (shifted_address_to_CPU1_memory_s1_from_CPU1_instruction_master >> 2);

  assign shifted_address_to_CPU1_memory_s1_from_CPU1_instruction_master = CPU1_instruction_master_address_to_slave;
  //d1_CPU1_memory_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_CPU1_memory_s1_end_xfer <= 1;
      else 
        d1_CPU1_memory_s1_end_xfer <= CPU1_memory_s1_end_xfer;
    end


  //CPU1_memory_s1_waits_for_read in a cycle, which is an e_mux
  assign CPU1_memory_s1_waits_for_read = CPU1_memory_s1_in_a_read_cycle & 0;

  //CPU1_memory_s1_in_a_read_cycle assignment, which is an e_assign
  assign CPU1_memory_s1_in_a_read_cycle = (CPU1_data_master_granted_CPU1_memory_s1 & CPU1_data_master_read) | (CPU1_instruction_master_granted_CPU1_memory_s1 & CPU1_instruction_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = CPU1_memory_s1_in_a_read_cycle;

  //CPU1_memory_s1_waits_for_write in a cycle, which is an e_mux
  assign CPU1_memory_s1_waits_for_write = CPU1_memory_s1_in_a_write_cycle & 0;

  //CPU1_memory_s1_in_a_write_cycle assignment, which is an e_assign
  assign CPU1_memory_s1_in_a_write_cycle = CPU1_data_master_granted_CPU1_memory_s1 & CPU1_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = CPU1_memory_s1_in_a_write_cycle;

  assign wait_for_CPU1_memory_s1_counter = 0;
  //CPU1_memory_s1_byteenable byte enable port mux, which is an e_mux
  assign CPU1_memory_s1_byteenable = (CPU1_data_master_granted_CPU1_memory_s1)? CPU1_data_master_byteenable :
    -1;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //CPU1_memory/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU1_data_master_granted_CPU1_memory_s1 + CPU1_instruction_master_granted_CPU1_memory_s1 > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU1_data_master_saved_grant_CPU1_memory_s1 + CPU1_instruction_master_saved_grant_CPU1_memory_s1 > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module Comms_memory_s1_arbitrator (
                                    // inputs:
                                     CPU0_data_master_address_to_slave,
                                     CPU0_data_master_byteenable,
                                     CPU0_data_master_latency_counter,
                                     CPU0_data_master_read,
                                     CPU0_data_master_write,
                                     CPU0_data_master_writedata,
                                     CPU1_data_master_address_to_slave,
                                     CPU1_data_master_byteenable,
                                     CPU1_data_master_latency_counter,
                                     CPU1_data_master_read,
                                     CPU1_data_master_write,
                                     CPU1_data_master_writedata,
                                     Comms_memory_s1_readdata,
                                     clk,
                                     reset_n,

                                    // outputs:
                                     CPU0_data_master_granted_Comms_memory_s1,
                                     CPU0_data_master_qualified_request_Comms_memory_s1,
                                     CPU0_data_master_read_data_valid_Comms_memory_s1,
                                     CPU0_data_master_requests_Comms_memory_s1,
                                     CPU1_data_master_granted_Comms_memory_s1,
                                     CPU1_data_master_qualified_request_Comms_memory_s1,
                                     CPU1_data_master_read_data_valid_Comms_memory_s1,
                                     CPU1_data_master_requests_Comms_memory_s1,
                                     Comms_memory_s1_address,
                                     Comms_memory_s1_byteenable,
                                     Comms_memory_s1_chipselect,
                                     Comms_memory_s1_clken,
                                     Comms_memory_s1_readdata_from_sa,
                                     Comms_memory_s1_reset,
                                     Comms_memory_s1_write,
                                     Comms_memory_s1_writedata,
                                     d1_Comms_memory_s1_end_xfer
                                  )
;

  output           CPU0_data_master_granted_Comms_memory_s1;
  output           CPU0_data_master_qualified_request_Comms_memory_s1;
  output           CPU0_data_master_read_data_valid_Comms_memory_s1;
  output           CPU0_data_master_requests_Comms_memory_s1;
  output           CPU1_data_master_granted_Comms_memory_s1;
  output           CPU1_data_master_qualified_request_Comms_memory_s1;
  output           CPU1_data_master_read_data_valid_Comms_memory_s1;
  output           CPU1_data_master_requests_Comms_memory_s1;
  output  [  9: 0] Comms_memory_s1_address;
  output  [  3: 0] Comms_memory_s1_byteenable;
  output           Comms_memory_s1_chipselect;
  output           Comms_memory_s1_clken;
  output  [ 31: 0] Comms_memory_s1_readdata_from_sa;
  output           Comms_memory_s1_reset;
  output           Comms_memory_s1_write;
  output  [ 31: 0] Comms_memory_s1_writedata;
  output           d1_Comms_memory_s1_end_xfer;
  input   [ 18: 0] CPU0_data_master_address_to_slave;
  input   [  3: 0] CPU0_data_master_byteenable;
  input            CPU0_data_master_latency_counter;
  input            CPU0_data_master_read;
  input            CPU0_data_master_write;
  input   [ 31: 0] CPU0_data_master_writedata;
  input   [ 18: 0] CPU1_data_master_address_to_slave;
  input   [  3: 0] CPU1_data_master_byteenable;
  input            CPU1_data_master_latency_counter;
  input            CPU1_data_master_read;
  input            CPU1_data_master_write;
  input   [ 31: 0] CPU1_data_master_writedata;
  input   [ 31: 0] Comms_memory_s1_readdata;
  input            clk;
  input            reset_n;

  wire             CPU0_data_master_arbiterlock;
  wire             CPU0_data_master_arbiterlock2;
  wire             CPU0_data_master_continuerequest;
  wire             CPU0_data_master_granted_Comms_memory_s1;
  wire             CPU0_data_master_qualified_request_Comms_memory_s1;
  wire             CPU0_data_master_read_data_valid_Comms_memory_s1;
  reg              CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register;
  wire             CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register_in;
  wire             CPU0_data_master_requests_Comms_memory_s1;
  wire             CPU0_data_master_saved_grant_Comms_memory_s1;
  wire             CPU1_data_master_arbiterlock;
  wire             CPU1_data_master_arbiterlock2;
  wire             CPU1_data_master_continuerequest;
  wire             CPU1_data_master_granted_Comms_memory_s1;
  wire             CPU1_data_master_qualified_request_Comms_memory_s1;
  wire             CPU1_data_master_read_data_valid_Comms_memory_s1;
  reg              CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register;
  wire             CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register_in;
  wire             CPU1_data_master_requests_Comms_memory_s1;
  wire             CPU1_data_master_saved_grant_Comms_memory_s1;
  wire    [  9: 0] Comms_memory_s1_address;
  wire             Comms_memory_s1_allgrants;
  wire             Comms_memory_s1_allow_new_arb_cycle;
  wire             Comms_memory_s1_any_bursting_master_saved_grant;
  wire             Comms_memory_s1_any_continuerequest;
  reg     [  1: 0] Comms_memory_s1_arb_addend;
  wire             Comms_memory_s1_arb_counter_enable;
  reg              Comms_memory_s1_arb_share_counter;
  wire             Comms_memory_s1_arb_share_counter_next_value;
  wire             Comms_memory_s1_arb_share_set_values;
  wire    [  1: 0] Comms_memory_s1_arb_winner;
  wire             Comms_memory_s1_arbitration_holdoff_internal;
  wire             Comms_memory_s1_beginbursttransfer_internal;
  wire             Comms_memory_s1_begins_xfer;
  wire    [  3: 0] Comms_memory_s1_byteenable;
  wire             Comms_memory_s1_chipselect;
  wire    [  3: 0] Comms_memory_s1_chosen_master_double_vector;
  wire    [  1: 0] Comms_memory_s1_chosen_master_rot_left;
  wire             Comms_memory_s1_clken;
  wire             Comms_memory_s1_end_xfer;
  wire             Comms_memory_s1_firsttransfer;
  wire    [  1: 0] Comms_memory_s1_grant_vector;
  wire             Comms_memory_s1_in_a_read_cycle;
  wire             Comms_memory_s1_in_a_write_cycle;
  wire    [  1: 0] Comms_memory_s1_master_qreq_vector;
  wire             Comms_memory_s1_non_bursting_master_requests;
  wire    [ 31: 0] Comms_memory_s1_readdata_from_sa;
  reg              Comms_memory_s1_reg_firsttransfer;
  wire             Comms_memory_s1_reset;
  reg     [  1: 0] Comms_memory_s1_saved_chosen_master_vector;
  reg              Comms_memory_s1_slavearbiterlockenable;
  wire             Comms_memory_s1_slavearbiterlockenable2;
  wire             Comms_memory_s1_unreg_firsttransfer;
  wire             Comms_memory_s1_waits_for_read;
  wire             Comms_memory_s1_waits_for_write;
  wire             Comms_memory_s1_write;
  wire    [ 31: 0] Comms_memory_s1_writedata;
  reg              d1_Comms_memory_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_Comms_memory_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_CPU0_data_master_granted_slave_Comms_memory_s1;
  reg              last_cycle_CPU1_data_master_granted_slave_Comms_memory_s1;
  wire             p1_CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register;
  wire             p1_CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register;
  wire    [ 18: 0] shifted_address_to_Comms_memory_s1_from_CPU0_data_master;
  wire    [ 18: 0] shifted_address_to_Comms_memory_s1_from_CPU1_data_master;
  wire             wait_for_Comms_memory_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~Comms_memory_s1_end_xfer;
    end


  assign Comms_memory_s1_begins_xfer = ~d1_reasons_to_wait & ((CPU0_data_master_qualified_request_Comms_memory_s1 | CPU1_data_master_qualified_request_Comms_memory_s1));
  //assign Comms_memory_s1_readdata_from_sa = Comms_memory_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign Comms_memory_s1_readdata_from_sa = Comms_memory_s1_readdata;

  assign CPU0_data_master_requests_Comms_memory_s1 = ({CPU0_data_master_address_to_slave[18 : 12] , 12'b0} == 19'h41000) & (CPU0_data_master_read | CPU0_data_master_write);
  //Comms_memory_s1_arb_share_counter set values, which is an e_mux
  assign Comms_memory_s1_arb_share_set_values = 1;

  //Comms_memory_s1_non_bursting_master_requests mux, which is an e_mux
  assign Comms_memory_s1_non_bursting_master_requests = CPU0_data_master_requests_Comms_memory_s1 |
    CPU1_data_master_requests_Comms_memory_s1 |
    CPU0_data_master_requests_Comms_memory_s1 |
    CPU1_data_master_requests_Comms_memory_s1;

  //Comms_memory_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign Comms_memory_s1_any_bursting_master_saved_grant = 0;

  //Comms_memory_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign Comms_memory_s1_arb_share_counter_next_value = Comms_memory_s1_firsttransfer ? (Comms_memory_s1_arb_share_set_values - 1) : |Comms_memory_s1_arb_share_counter ? (Comms_memory_s1_arb_share_counter - 1) : 0;

  //Comms_memory_s1_allgrants all slave grants, which is an e_mux
  assign Comms_memory_s1_allgrants = (|Comms_memory_s1_grant_vector) |
    (|Comms_memory_s1_grant_vector) |
    (|Comms_memory_s1_grant_vector) |
    (|Comms_memory_s1_grant_vector);

  //Comms_memory_s1_end_xfer assignment, which is an e_assign
  assign Comms_memory_s1_end_xfer = ~(Comms_memory_s1_waits_for_read | Comms_memory_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_Comms_memory_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_Comms_memory_s1 = Comms_memory_s1_end_xfer & (~Comms_memory_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //Comms_memory_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign Comms_memory_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_Comms_memory_s1 & Comms_memory_s1_allgrants) | (end_xfer_arb_share_counter_term_Comms_memory_s1 & ~Comms_memory_s1_non_bursting_master_requests);

  //Comms_memory_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_memory_s1_arb_share_counter <= 0;
      else if (Comms_memory_s1_arb_counter_enable)
          Comms_memory_s1_arb_share_counter <= Comms_memory_s1_arb_share_counter_next_value;
    end


  //Comms_memory_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_memory_s1_slavearbiterlockenable <= 0;
      else if ((|Comms_memory_s1_master_qreq_vector & end_xfer_arb_share_counter_term_Comms_memory_s1) | (end_xfer_arb_share_counter_term_Comms_memory_s1 & ~Comms_memory_s1_non_bursting_master_requests))
          Comms_memory_s1_slavearbiterlockenable <= |Comms_memory_s1_arb_share_counter_next_value;
    end


  //CPU0/data_master Comms_memory/s1 arbiterlock, which is an e_assign
  assign CPU0_data_master_arbiterlock = Comms_memory_s1_slavearbiterlockenable & CPU0_data_master_continuerequest;

  //Comms_memory_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign Comms_memory_s1_slavearbiterlockenable2 = |Comms_memory_s1_arb_share_counter_next_value;

  //CPU0/data_master Comms_memory/s1 arbiterlock2, which is an e_assign
  assign CPU0_data_master_arbiterlock2 = Comms_memory_s1_slavearbiterlockenable2 & CPU0_data_master_continuerequest;

  //CPU1/data_master Comms_memory/s1 arbiterlock, which is an e_assign
  assign CPU1_data_master_arbiterlock = Comms_memory_s1_slavearbiterlockenable & CPU1_data_master_continuerequest;

  //CPU1/data_master Comms_memory/s1 arbiterlock2, which is an e_assign
  assign CPU1_data_master_arbiterlock2 = Comms_memory_s1_slavearbiterlockenable2 & CPU1_data_master_continuerequest;

  //CPU1/data_master granted Comms_memory/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU1_data_master_granted_slave_Comms_memory_s1 <= 0;
      else 
        last_cycle_CPU1_data_master_granted_slave_Comms_memory_s1 <= CPU1_data_master_saved_grant_Comms_memory_s1 ? 1 : (Comms_memory_s1_arbitration_holdoff_internal | ~CPU1_data_master_requests_Comms_memory_s1) ? 0 : last_cycle_CPU1_data_master_granted_slave_Comms_memory_s1;
    end


  //CPU1_data_master_continuerequest continued request, which is an e_mux
  assign CPU1_data_master_continuerequest = last_cycle_CPU1_data_master_granted_slave_Comms_memory_s1 & CPU1_data_master_requests_Comms_memory_s1;

  //Comms_memory_s1_any_continuerequest at least one master continues requesting, which is an e_mux
  assign Comms_memory_s1_any_continuerequest = CPU1_data_master_continuerequest |
    CPU0_data_master_continuerequest;

  assign CPU0_data_master_qualified_request_Comms_memory_s1 = CPU0_data_master_requests_Comms_memory_s1 & ~((CPU0_data_master_read & ((1 < CPU0_data_master_latency_counter))) | CPU1_data_master_arbiterlock);
  //CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register_in mux for readlatency shift register, which is an e_mux
  assign CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register_in = CPU0_data_master_granted_Comms_memory_s1 & CPU0_data_master_read & ~Comms_memory_s1_waits_for_read;

  //shift register p1 CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register in if flush, otherwise shift left, which is an e_mux
  assign p1_CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register = {CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register, CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register_in};

  //CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register for remembering which master asked for a fixed latency read, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register <= 0;
      else 
        CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register <= p1_CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register;
    end


  //local readdatavalid CPU0_data_master_read_data_valid_Comms_memory_s1, which is an e_mux
  assign CPU0_data_master_read_data_valid_Comms_memory_s1 = CPU0_data_master_read_data_valid_Comms_memory_s1_shift_register;

  //Comms_memory_s1_writedata mux, which is an e_mux
  assign Comms_memory_s1_writedata = (CPU0_data_master_granted_Comms_memory_s1)? CPU0_data_master_writedata :
    CPU1_data_master_writedata;

  //mux Comms_memory_s1_clken, which is an e_mux
  assign Comms_memory_s1_clken = 1'b1;

  assign CPU1_data_master_requests_Comms_memory_s1 = ({CPU1_data_master_address_to_slave[18 : 12] , 12'b0} == 19'h41000) & (CPU1_data_master_read | CPU1_data_master_write);
  //CPU0/data_master granted Comms_memory/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU0_data_master_granted_slave_Comms_memory_s1 <= 0;
      else 
        last_cycle_CPU0_data_master_granted_slave_Comms_memory_s1 <= CPU0_data_master_saved_grant_Comms_memory_s1 ? 1 : (Comms_memory_s1_arbitration_holdoff_internal | ~CPU0_data_master_requests_Comms_memory_s1) ? 0 : last_cycle_CPU0_data_master_granted_slave_Comms_memory_s1;
    end


  //CPU0_data_master_continuerequest continued request, which is an e_mux
  assign CPU0_data_master_continuerequest = last_cycle_CPU0_data_master_granted_slave_Comms_memory_s1 & CPU0_data_master_requests_Comms_memory_s1;

  assign CPU1_data_master_qualified_request_Comms_memory_s1 = CPU1_data_master_requests_Comms_memory_s1 & ~((CPU1_data_master_read & ((1 < CPU1_data_master_latency_counter))) | CPU0_data_master_arbiterlock);
  //CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register_in mux for readlatency shift register, which is an e_mux
  assign CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register_in = CPU1_data_master_granted_Comms_memory_s1 & CPU1_data_master_read & ~Comms_memory_s1_waits_for_read;

  //shift register p1 CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register in if flush, otherwise shift left, which is an e_mux
  assign p1_CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register = {CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register, CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register_in};

  //CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register for remembering which master asked for a fixed latency read, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register <= 0;
      else 
        CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register <= p1_CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register;
    end


  //local readdatavalid CPU1_data_master_read_data_valid_Comms_memory_s1, which is an e_mux
  assign CPU1_data_master_read_data_valid_Comms_memory_s1 = CPU1_data_master_read_data_valid_Comms_memory_s1_shift_register;

  //allow new arb cycle for Comms_memory/s1, which is an e_assign
  assign Comms_memory_s1_allow_new_arb_cycle = ~CPU0_data_master_arbiterlock & ~CPU1_data_master_arbiterlock;

  //CPU1/data_master assignment into master qualified-requests vector for Comms_memory/s1, which is an e_assign
  assign Comms_memory_s1_master_qreq_vector[0] = CPU1_data_master_qualified_request_Comms_memory_s1;

  //CPU1/data_master grant Comms_memory/s1, which is an e_assign
  assign CPU1_data_master_granted_Comms_memory_s1 = Comms_memory_s1_grant_vector[0];

  //CPU1/data_master saved-grant Comms_memory/s1, which is an e_assign
  assign CPU1_data_master_saved_grant_Comms_memory_s1 = Comms_memory_s1_arb_winner[0] && CPU1_data_master_requests_Comms_memory_s1;

  //CPU0/data_master assignment into master qualified-requests vector for Comms_memory/s1, which is an e_assign
  assign Comms_memory_s1_master_qreq_vector[1] = CPU0_data_master_qualified_request_Comms_memory_s1;

  //CPU0/data_master grant Comms_memory/s1, which is an e_assign
  assign CPU0_data_master_granted_Comms_memory_s1 = Comms_memory_s1_grant_vector[1];

  //CPU0/data_master saved-grant Comms_memory/s1, which is an e_assign
  assign CPU0_data_master_saved_grant_Comms_memory_s1 = Comms_memory_s1_arb_winner[1] && CPU0_data_master_requests_Comms_memory_s1;

  //Comms_memory/s1 chosen-master double-vector, which is an e_assign
  assign Comms_memory_s1_chosen_master_double_vector = {Comms_memory_s1_master_qreq_vector, Comms_memory_s1_master_qreq_vector} & ({~Comms_memory_s1_master_qreq_vector, ~Comms_memory_s1_master_qreq_vector} + Comms_memory_s1_arb_addend);

  //stable onehot encoding of arb winner
  assign Comms_memory_s1_arb_winner = (Comms_memory_s1_allow_new_arb_cycle & | Comms_memory_s1_grant_vector) ? Comms_memory_s1_grant_vector : Comms_memory_s1_saved_chosen_master_vector;

  //saved Comms_memory_s1_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_memory_s1_saved_chosen_master_vector <= 0;
      else if (Comms_memory_s1_allow_new_arb_cycle)
          Comms_memory_s1_saved_chosen_master_vector <= |Comms_memory_s1_grant_vector ? Comms_memory_s1_grant_vector : Comms_memory_s1_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign Comms_memory_s1_grant_vector = {(Comms_memory_s1_chosen_master_double_vector[1] | Comms_memory_s1_chosen_master_double_vector[3]),
    (Comms_memory_s1_chosen_master_double_vector[0] | Comms_memory_s1_chosen_master_double_vector[2])};

  //Comms_memory/s1 chosen master rotated left, which is an e_assign
  assign Comms_memory_s1_chosen_master_rot_left = (Comms_memory_s1_arb_winner << 1) ? (Comms_memory_s1_arb_winner << 1) : 1;

  //Comms_memory/s1's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_memory_s1_arb_addend <= 1;
      else if (|Comms_memory_s1_grant_vector)
          Comms_memory_s1_arb_addend <= Comms_memory_s1_end_xfer? Comms_memory_s1_chosen_master_rot_left : Comms_memory_s1_grant_vector;
    end


  //~Comms_memory_s1_reset assignment, which is an e_assign
  assign Comms_memory_s1_reset = ~reset_n;

  assign Comms_memory_s1_chipselect = CPU0_data_master_granted_Comms_memory_s1 | CPU1_data_master_granted_Comms_memory_s1;
  //Comms_memory_s1_firsttransfer first transaction, which is an e_assign
  assign Comms_memory_s1_firsttransfer = Comms_memory_s1_begins_xfer ? Comms_memory_s1_unreg_firsttransfer : Comms_memory_s1_reg_firsttransfer;

  //Comms_memory_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign Comms_memory_s1_unreg_firsttransfer = ~(Comms_memory_s1_slavearbiterlockenable & Comms_memory_s1_any_continuerequest);

  //Comms_memory_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_memory_s1_reg_firsttransfer <= 1'b1;
      else if (Comms_memory_s1_begins_xfer)
          Comms_memory_s1_reg_firsttransfer <= Comms_memory_s1_unreg_firsttransfer;
    end


  //Comms_memory_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign Comms_memory_s1_beginbursttransfer_internal = Comms_memory_s1_begins_xfer;

  //Comms_memory_s1_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign Comms_memory_s1_arbitration_holdoff_internal = Comms_memory_s1_begins_xfer & Comms_memory_s1_firsttransfer;

  //Comms_memory_s1_write assignment, which is an e_mux
  assign Comms_memory_s1_write = (CPU0_data_master_granted_Comms_memory_s1 & CPU0_data_master_write) | (CPU1_data_master_granted_Comms_memory_s1 & CPU1_data_master_write);

  assign shifted_address_to_Comms_memory_s1_from_CPU0_data_master = CPU0_data_master_address_to_slave;
  //Comms_memory_s1_address mux, which is an e_mux
  assign Comms_memory_s1_address = (CPU0_data_master_granted_Comms_memory_s1)? (shifted_address_to_Comms_memory_s1_from_CPU0_data_master >> 2) :
    (shifted_address_to_Comms_memory_s1_from_CPU1_data_master >> 2);

  assign shifted_address_to_Comms_memory_s1_from_CPU1_data_master = CPU1_data_master_address_to_slave;
  //d1_Comms_memory_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_Comms_memory_s1_end_xfer <= 1;
      else 
        d1_Comms_memory_s1_end_xfer <= Comms_memory_s1_end_xfer;
    end


  //Comms_memory_s1_waits_for_read in a cycle, which is an e_mux
  assign Comms_memory_s1_waits_for_read = Comms_memory_s1_in_a_read_cycle & 0;

  //Comms_memory_s1_in_a_read_cycle assignment, which is an e_assign
  assign Comms_memory_s1_in_a_read_cycle = (CPU0_data_master_granted_Comms_memory_s1 & CPU0_data_master_read) | (CPU1_data_master_granted_Comms_memory_s1 & CPU1_data_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = Comms_memory_s1_in_a_read_cycle;

  //Comms_memory_s1_waits_for_write in a cycle, which is an e_mux
  assign Comms_memory_s1_waits_for_write = Comms_memory_s1_in_a_write_cycle & 0;

  //Comms_memory_s1_in_a_write_cycle assignment, which is an e_assign
  assign Comms_memory_s1_in_a_write_cycle = (CPU0_data_master_granted_Comms_memory_s1 & CPU0_data_master_write) | (CPU1_data_master_granted_Comms_memory_s1 & CPU1_data_master_write);

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = Comms_memory_s1_in_a_write_cycle;

  assign wait_for_Comms_memory_s1_counter = 0;
  //Comms_memory_s1_byteenable byte enable port mux, which is an e_mux
  assign Comms_memory_s1_byteenable = (CPU0_data_master_granted_Comms_memory_s1)? CPU0_data_master_byteenable :
    (CPU1_data_master_granted_Comms_memory_s1)? CPU1_data_master_byteenable :
    -1;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //Comms_memory/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_granted_Comms_memory_s1 + CPU1_data_master_granted_Comms_memory_s1 > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_saved_grant_Comms_memory_s1 + CPU1_data_master_saved_grant_Comms_memory_s1 > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module Comms_mutex_rx_s1_arbitrator (
                                      // inputs:
                                       CPU0_data_master_address_to_slave,
                                       CPU0_data_master_latency_counter,
                                       CPU0_data_master_read,
                                       CPU0_data_master_write,
                                       CPU0_data_master_writedata,
                                       CPU1_data_master_address_to_slave,
                                       CPU1_data_master_latency_counter,
                                       CPU1_data_master_read,
                                       CPU1_data_master_write,
                                       CPU1_data_master_writedata,
                                       Comms_mutex_rx_s1_readdata,
                                       clk,
                                       reset_n,

                                      // outputs:
                                       CPU0_data_master_granted_Comms_mutex_rx_s1,
                                       CPU0_data_master_qualified_request_Comms_mutex_rx_s1,
                                       CPU0_data_master_read_data_valid_Comms_mutex_rx_s1,
                                       CPU0_data_master_requests_Comms_mutex_rx_s1,
                                       CPU1_data_master_granted_Comms_mutex_rx_s1,
                                       CPU1_data_master_qualified_request_Comms_mutex_rx_s1,
                                       CPU1_data_master_read_data_valid_Comms_mutex_rx_s1,
                                       CPU1_data_master_requests_Comms_mutex_rx_s1,
                                       Comms_mutex_rx_s1_address,
                                       Comms_mutex_rx_s1_chipselect,
                                       Comms_mutex_rx_s1_read,
                                       Comms_mutex_rx_s1_readdata_from_sa,
                                       Comms_mutex_rx_s1_reset_n,
                                       Comms_mutex_rx_s1_write,
                                       Comms_mutex_rx_s1_writedata,
                                       d1_Comms_mutex_rx_s1_end_xfer
                                    )
;

  output           CPU0_data_master_granted_Comms_mutex_rx_s1;
  output           CPU0_data_master_qualified_request_Comms_mutex_rx_s1;
  output           CPU0_data_master_read_data_valid_Comms_mutex_rx_s1;
  output           CPU0_data_master_requests_Comms_mutex_rx_s1;
  output           CPU1_data_master_granted_Comms_mutex_rx_s1;
  output           CPU1_data_master_qualified_request_Comms_mutex_rx_s1;
  output           CPU1_data_master_read_data_valid_Comms_mutex_rx_s1;
  output           CPU1_data_master_requests_Comms_mutex_rx_s1;
  output           Comms_mutex_rx_s1_address;
  output           Comms_mutex_rx_s1_chipselect;
  output           Comms_mutex_rx_s1_read;
  output  [ 31: 0] Comms_mutex_rx_s1_readdata_from_sa;
  output           Comms_mutex_rx_s1_reset_n;
  output           Comms_mutex_rx_s1_write;
  output  [ 31: 0] Comms_mutex_rx_s1_writedata;
  output           d1_Comms_mutex_rx_s1_end_xfer;
  input   [ 18: 0] CPU0_data_master_address_to_slave;
  input            CPU0_data_master_latency_counter;
  input            CPU0_data_master_read;
  input            CPU0_data_master_write;
  input   [ 31: 0] CPU0_data_master_writedata;
  input   [ 18: 0] CPU1_data_master_address_to_slave;
  input            CPU1_data_master_latency_counter;
  input            CPU1_data_master_read;
  input            CPU1_data_master_write;
  input   [ 31: 0] CPU1_data_master_writedata;
  input   [ 31: 0] Comms_mutex_rx_s1_readdata;
  input            clk;
  input            reset_n;

  wire             CPU0_data_master_arbiterlock;
  wire             CPU0_data_master_arbiterlock2;
  wire             CPU0_data_master_continuerequest;
  wire             CPU0_data_master_granted_Comms_mutex_rx_s1;
  wire             CPU0_data_master_qualified_request_Comms_mutex_rx_s1;
  wire             CPU0_data_master_read_data_valid_Comms_mutex_rx_s1;
  wire             CPU0_data_master_requests_Comms_mutex_rx_s1;
  wire             CPU0_data_master_saved_grant_Comms_mutex_rx_s1;
  wire             CPU1_data_master_arbiterlock;
  wire             CPU1_data_master_arbiterlock2;
  wire             CPU1_data_master_continuerequest;
  wire             CPU1_data_master_granted_Comms_mutex_rx_s1;
  wire             CPU1_data_master_qualified_request_Comms_mutex_rx_s1;
  wire             CPU1_data_master_read_data_valid_Comms_mutex_rx_s1;
  wire             CPU1_data_master_requests_Comms_mutex_rx_s1;
  wire             CPU1_data_master_saved_grant_Comms_mutex_rx_s1;
  wire             Comms_mutex_rx_s1_address;
  wire             Comms_mutex_rx_s1_allgrants;
  wire             Comms_mutex_rx_s1_allow_new_arb_cycle;
  wire             Comms_mutex_rx_s1_any_bursting_master_saved_grant;
  wire             Comms_mutex_rx_s1_any_continuerequest;
  reg     [  1: 0] Comms_mutex_rx_s1_arb_addend;
  wire             Comms_mutex_rx_s1_arb_counter_enable;
  reg              Comms_mutex_rx_s1_arb_share_counter;
  wire             Comms_mutex_rx_s1_arb_share_counter_next_value;
  wire             Comms_mutex_rx_s1_arb_share_set_values;
  wire    [  1: 0] Comms_mutex_rx_s1_arb_winner;
  wire             Comms_mutex_rx_s1_arbitration_holdoff_internal;
  wire             Comms_mutex_rx_s1_beginbursttransfer_internal;
  wire             Comms_mutex_rx_s1_begins_xfer;
  wire             Comms_mutex_rx_s1_chipselect;
  wire    [  3: 0] Comms_mutex_rx_s1_chosen_master_double_vector;
  wire    [  1: 0] Comms_mutex_rx_s1_chosen_master_rot_left;
  wire             Comms_mutex_rx_s1_end_xfer;
  wire             Comms_mutex_rx_s1_firsttransfer;
  wire    [  1: 0] Comms_mutex_rx_s1_grant_vector;
  wire             Comms_mutex_rx_s1_in_a_read_cycle;
  wire             Comms_mutex_rx_s1_in_a_write_cycle;
  wire    [  1: 0] Comms_mutex_rx_s1_master_qreq_vector;
  wire             Comms_mutex_rx_s1_non_bursting_master_requests;
  wire             Comms_mutex_rx_s1_read;
  wire    [ 31: 0] Comms_mutex_rx_s1_readdata_from_sa;
  reg              Comms_mutex_rx_s1_reg_firsttransfer;
  wire             Comms_mutex_rx_s1_reset_n;
  reg     [  1: 0] Comms_mutex_rx_s1_saved_chosen_master_vector;
  reg              Comms_mutex_rx_s1_slavearbiterlockenable;
  wire             Comms_mutex_rx_s1_slavearbiterlockenable2;
  wire             Comms_mutex_rx_s1_unreg_firsttransfer;
  wire             Comms_mutex_rx_s1_waits_for_read;
  wire             Comms_mutex_rx_s1_waits_for_write;
  wire             Comms_mutex_rx_s1_write;
  wire    [ 31: 0] Comms_mutex_rx_s1_writedata;
  reg              d1_Comms_mutex_rx_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_Comms_mutex_rx_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_CPU0_data_master_granted_slave_Comms_mutex_rx_s1;
  reg              last_cycle_CPU1_data_master_granted_slave_Comms_mutex_rx_s1;
  wire    [ 18: 0] shifted_address_to_Comms_mutex_rx_s1_from_CPU0_data_master;
  wire    [ 18: 0] shifted_address_to_Comms_mutex_rx_s1_from_CPU1_data_master;
  wire             wait_for_Comms_mutex_rx_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~Comms_mutex_rx_s1_end_xfer;
    end


  assign Comms_mutex_rx_s1_begins_xfer = ~d1_reasons_to_wait & ((CPU0_data_master_qualified_request_Comms_mutex_rx_s1 | CPU1_data_master_qualified_request_Comms_mutex_rx_s1));
  //assign Comms_mutex_rx_s1_readdata_from_sa = Comms_mutex_rx_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign Comms_mutex_rx_s1_readdata_from_sa = Comms_mutex_rx_s1_readdata;

  assign CPU0_data_master_requests_Comms_mutex_rx_s1 = ({CPU0_data_master_address_to_slave[18 : 3] , 3'b0} == 19'h43018) & (CPU0_data_master_read | CPU0_data_master_write);
  //Comms_mutex_rx_s1_arb_share_counter set values, which is an e_mux
  assign Comms_mutex_rx_s1_arb_share_set_values = 1;

  //Comms_mutex_rx_s1_non_bursting_master_requests mux, which is an e_mux
  assign Comms_mutex_rx_s1_non_bursting_master_requests = CPU0_data_master_requests_Comms_mutex_rx_s1 |
    CPU1_data_master_requests_Comms_mutex_rx_s1 |
    CPU0_data_master_requests_Comms_mutex_rx_s1 |
    CPU1_data_master_requests_Comms_mutex_rx_s1;

  //Comms_mutex_rx_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign Comms_mutex_rx_s1_any_bursting_master_saved_grant = 0;

  //Comms_mutex_rx_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign Comms_mutex_rx_s1_arb_share_counter_next_value = Comms_mutex_rx_s1_firsttransfer ? (Comms_mutex_rx_s1_arb_share_set_values - 1) : |Comms_mutex_rx_s1_arb_share_counter ? (Comms_mutex_rx_s1_arb_share_counter - 1) : 0;

  //Comms_mutex_rx_s1_allgrants all slave grants, which is an e_mux
  assign Comms_mutex_rx_s1_allgrants = (|Comms_mutex_rx_s1_grant_vector) |
    (|Comms_mutex_rx_s1_grant_vector) |
    (|Comms_mutex_rx_s1_grant_vector) |
    (|Comms_mutex_rx_s1_grant_vector);

  //Comms_mutex_rx_s1_end_xfer assignment, which is an e_assign
  assign Comms_mutex_rx_s1_end_xfer = ~(Comms_mutex_rx_s1_waits_for_read | Comms_mutex_rx_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_Comms_mutex_rx_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_Comms_mutex_rx_s1 = Comms_mutex_rx_s1_end_xfer & (~Comms_mutex_rx_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //Comms_mutex_rx_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign Comms_mutex_rx_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_Comms_mutex_rx_s1 & Comms_mutex_rx_s1_allgrants) | (end_xfer_arb_share_counter_term_Comms_mutex_rx_s1 & ~Comms_mutex_rx_s1_non_bursting_master_requests);

  //Comms_mutex_rx_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_rx_s1_arb_share_counter <= 0;
      else if (Comms_mutex_rx_s1_arb_counter_enable)
          Comms_mutex_rx_s1_arb_share_counter <= Comms_mutex_rx_s1_arb_share_counter_next_value;
    end


  //Comms_mutex_rx_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_rx_s1_slavearbiterlockenable <= 0;
      else if ((|Comms_mutex_rx_s1_master_qreq_vector & end_xfer_arb_share_counter_term_Comms_mutex_rx_s1) | (end_xfer_arb_share_counter_term_Comms_mutex_rx_s1 & ~Comms_mutex_rx_s1_non_bursting_master_requests))
          Comms_mutex_rx_s1_slavearbiterlockenable <= |Comms_mutex_rx_s1_arb_share_counter_next_value;
    end


  //CPU0/data_master Comms_mutex_rx/s1 arbiterlock, which is an e_assign
  assign CPU0_data_master_arbiterlock = Comms_mutex_rx_s1_slavearbiterlockenable & CPU0_data_master_continuerequest;

  //Comms_mutex_rx_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign Comms_mutex_rx_s1_slavearbiterlockenable2 = |Comms_mutex_rx_s1_arb_share_counter_next_value;

  //CPU0/data_master Comms_mutex_rx/s1 arbiterlock2, which is an e_assign
  assign CPU0_data_master_arbiterlock2 = Comms_mutex_rx_s1_slavearbiterlockenable2 & CPU0_data_master_continuerequest;

  //CPU1/data_master Comms_mutex_rx/s1 arbiterlock, which is an e_assign
  assign CPU1_data_master_arbiterlock = Comms_mutex_rx_s1_slavearbiterlockenable & CPU1_data_master_continuerequest;

  //CPU1/data_master Comms_mutex_rx/s1 arbiterlock2, which is an e_assign
  assign CPU1_data_master_arbiterlock2 = Comms_mutex_rx_s1_slavearbiterlockenable2 & CPU1_data_master_continuerequest;

  //CPU1/data_master granted Comms_mutex_rx/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU1_data_master_granted_slave_Comms_mutex_rx_s1 <= 0;
      else 
        last_cycle_CPU1_data_master_granted_slave_Comms_mutex_rx_s1 <= CPU1_data_master_saved_grant_Comms_mutex_rx_s1 ? 1 : (Comms_mutex_rx_s1_arbitration_holdoff_internal | ~CPU1_data_master_requests_Comms_mutex_rx_s1) ? 0 : last_cycle_CPU1_data_master_granted_slave_Comms_mutex_rx_s1;
    end


  //CPU1_data_master_continuerequest continued request, which is an e_mux
  assign CPU1_data_master_continuerequest = last_cycle_CPU1_data_master_granted_slave_Comms_mutex_rx_s1 & CPU1_data_master_requests_Comms_mutex_rx_s1;

  //Comms_mutex_rx_s1_any_continuerequest at least one master continues requesting, which is an e_mux
  assign Comms_mutex_rx_s1_any_continuerequest = CPU1_data_master_continuerequest |
    CPU0_data_master_continuerequest;

  assign CPU0_data_master_qualified_request_Comms_mutex_rx_s1 = CPU0_data_master_requests_Comms_mutex_rx_s1 & ~((CPU0_data_master_read & ((CPU0_data_master_latency_counter != 0))) | CPU1_data_master_arbiterlock);
  //local readdatavalid CPU0_data_master_read_data_valid_Comms_mutex_rx_s1, which is an e_mux
  assign CPU0_data_master_read_data_valid_Comms_mutex_rx_s1 = CPU0_data_master_granted_Comms_mutex_rx_s1 & CPU0_data_master_read & ~Comms_mutex_rx_s1_waits_for_read;

  //Comms_mutex_rx_s1_writedata mux, which is an e_mux
  assign Comms_mutex_rx_s1_writedata = (CPU0_data_master_granted_Comms_mutex_rx_s1)? CPU0_data_master_writedata :
    CPU1_data_master_writedata;

  assign CPU1_data_master_requests_Comms_mutex_rx_s1 = ({CPU1_data_master_address_to_slave[18 : 3] , 3'b0} == 19'h43018) & (CPU1_data_master_read | CPU1_data_master_write);
  //CPU0/data_master granted Comms_mutex_rx/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU0_data_master_granted_slave_Comms_mutex_rx_s1 <= 0;
      else 
        last_cycle_CPU0_data_master_granted_slave_Comms_mutex_rx_s1 <= CPU0_data_master_saved_grant_Comms_mutex_rx_s1 ? 1 : (Comms_mutex_rx_s1_arbitration_holdoff_internal | ~CPU0_data_master_requests_Comms_mutex_rx_s1) ? 0 : last_cycle_CPU0_data_master_granted_slave_Comms_mutex_rx_s1;
    end


  //CPU0_data_master_continuerequest continued request, which is an e_mux
  assign CPU0_data_master_continuerequest = last_cycle_CPU0_data_master_granted_slave_Comms_mutex_rx_s1 & CPU0_data_master_requests_Comms_mutex_rx_s1;

  assign CPU1_data_master_qualified_request_Comms_mutex_rx_s1 = CPU1_data_master_requests_Comms_mutex_rx_s1 & ~((CPU1_data_master_read & ((CPU1_data_master_latency_counter != 0))) | CPU0_data_master_arbiterlock);
  //local readdatavalid CPU1_data_master_read_data_valid_Comms_mutex_rx_s1, which is an e_mux
  assign CPU1_data_master_read_data_valid_Comms_mutex_rx_s1 = CPU1_data_master_granted_Comms_mutex_rx_s1 & CPU1_data_master_read & ~Comms_mutex_rx_s1_waits_for_read;

  //allow new arb cycle for Comms_mutex_rx/s1, which is an e_assign
  assign Comms_mutex_rx_s1_allow_new_arb_cycle = ~CPU0_data_master_arbiterlock & ~CPU1_data_master_arbiterlock;

  //CPU1/data_master assignment into master qualified-requests vector for Comms_mutex_rx/s1, which is an e_assign
  assign Comms_mutex_rx_s1_master_qreq_vector[0] = CPU1_data_master_qualified_request_Comms_mutex_rx_s1;

  //CPU1/data_master grant Comms_mutex_rx/s1, which is an e_assign
  assign CPU1_data_master_granted_Comms_mutex_rx_s1 = Comms_mutex_rx_s1_grant_vector[0];

  //CPU1/data_master saved-grant Comms_mutex_rx/s1, which is an e_assign
  assign CPU1_data_master_saved_grant_Comms_mutex_rx_s1 = Comms_mutex_rx_s1_arb_winner[0] && CPU1_data_master_requests_Comms_mutex_rx_s1;

  //CPU0/data_master assignment into master qualified-requests vector for Comms_mutex_rx/s1, which is an e_assign
  assign Comms_mutex_rx_s1_master_qreq_vector[1] = CPU0_data_master_qualified_request_Comms_mutex_rx_s1;

  //CPU0/data_master grant Comms_mutex_rx/s1, which is an e_assign
  assign CPU0_data_master_granted_Comms_mutex_rx_s1 = Comms_mutex_rx_s1_grant_vector[1];

  //CPU0/data_master saved-grant Comms_mutex_rx/s1, which is an e_assign
  assign CPU0_data_master_saved_grant_Comms_mutex_rx_s1 = Comms_mutex_rx_s1_arb_winner[1] && CPU0_data_master_requests_Comms_mutex_rx_s1;

  //Comms_mutex_rx/s1 chosen-master double-vector, which is an e_assign
  assign Comms_mutex_rx_s1_chosen_master_double_vector = {Comms_mutex_rx_s1_master_qreq_vector, Comms_mutex_rx_s1_master_qreq_vector} & ({~Comms_mutex_rx_s1_master_qreq_vector, ~Comms_mutex_rx_s1_master_qreq_vector} + Comms_mutex_rx_s1_arb_addend);

  //stable onehot encoding of arb winner
  assign Comms_mutex_rx_s1_arb_winner = (Comms_mutex_rx_s1_allow_new_arb_cycle & | Comms_mutex_rx_s1_grant_vector) ? Comms_mutex_rx_s1_grant_vector : Comms_mutex_rx_s1_saved_chosen_master_vector;

  //saved Comms_mutex_rx_s1_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_rx_s1_saved_chosen_master_vector <= 0;
      else if (Comms_mutex_rx_s1_allow_new_arb_cycle)
          Comms_mutex_rx_s1_saved_chosen_master_vector <= |Comms_mutex_rx_s1_grant_vector ? Comms_mutex_rx_s1_grant_vector : Comms_mutex_rx_s1_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign Comms_mutex_rx_s1_grant_vector = {(Comms_mutex_rx_s1_chosen_master_double_vector[1] | Comms_mutex_rx_s1_chosen_master_double_vector[3]),
    (Comms_mutex_rx_s1_chosen_master_double_vector[0] | Comms_mutex_rx_s1_chosen_master_double_vector[2])};

  //Comms_mutex_rx/s1 chosen master rotated left, which is an e_assign
  assign Comms_mutex_rx_s1_chosen_master_rot_left = (Comms_mutex_rx_s1_arb_winner << 1) ? (Comms_mutex_rx_s1_arb_winner << 1) : 1;

  //Comms_mutex_rx/s1's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_rx_s1_arb_addend <= 1;
      else if (|Comms_mutex_rx_s1_grant_vector)
          Comms_mutex_rx_s1_arb_addend <= Comms_mutex_rx_s1_end_xfer? Comms_mutex_rx_s1_chosen_master_rot_left : Comms_mutex_rx_s1_grant_vector;
    end


  //Comms_mutex_rx_s1_reset_n assignment, which is an e_assign
  assign Comms_mutex_rx_s1_reset_n = reset_n;

  assign Comms_mutex_rx_s1_chipselect = CPU0_data_master_granted_Comms_mutex_rx_s1 | CPU1_data_master_granted_Comms_mutex_rx_s1;
  //Comms_mutex_rx_s1_firsttransfer first transaction, which is an e_assign
  assign Comms_mutex_rx_s1_firsttransfer = Comms_mutex_rx_s1_begins_xfer ? Comms_mutex_rx_s1_unreg_firsttransfer : Comms_mutex_rx_s1_reg_firsttransfer;

  //Comms_mutex_rx_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign Comms_mutex_rx_s1_unreg_firsttransfer = ~(Comms_mutex_rx_s1_slavearbiterlockenable & Comms_mutex_rx_s1_any_continuerequest);

  //Comms_mutex_rx_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_rx_s1_reg_firsttransfer <= 1'b1;
      else if (Comms_mutex_rx_s1_begins_xfer)
          Comms_mutex_rx_s1_reg_firsttransfer <= Comms_mutex_rx_s1_unreg_firsttransfer;
    end


  //Comms_mutex_rx_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign Comms_mutex_rx_s1_beginbursttransfer_internal = Comms_mutex_rx_s1_begins_xfer;

  //Comms_mutex_rx_s1_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign Comms_mutex_rx_s1_arbitration_holdoff_internal = Comms_mutex_rx_s1_begins_xfer & Comms_mutex_rx_s1_firsttransfer;

  //Comms_mutex_rx_s1_read assignment, which is an e_mux
  assign Comms_mutex_rx_s1_read = (CPU0_data_master_granted_Comms_mutex_rx_s1 & CPU0_data_master_read) | (CPU1_data_master_granted_Comms_mutex_rx_s1 & CPU1_data_master_read);

  //Comms_mutex_rx_s1_write assignment, which is an e_mux
  assign Comms_mutex_rx_s1_write = (CPU0_data_master_granted_Comms_mutex_rx_s1 & CPU0_data_master_write) | (CPU1_data_master_granted_Comms_mutex_rx_s1 & CPU1_data_master_write);

  assign shifted_address_to_Comms_mutex_rx_s1_from_CPU0_data_master = CPU0_data_master_address_to_slave;
  //Comms_mutex_rx_s1_address mux, which is an e_mux
  assign Comms_mutex_rx_s1_address = (CPU0_data_master_granted_Comms_mutex_rx_s1)? (shifted_address_to_Comms_mutex_rx_s1_from_CPU0_data_master >> 2) :
    (shifted_address_to_Comms_mutex_rx_s1_from_CPU1_data_master >> 2);

  assign shifted_address_to_Comms_mutex_rx_s1_from_CPU1_data_master = CPU1_data_master_address_to_slave;
  //d1_Comms_mutex_rx_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_Comms_mutex_rx_s1_end_xfer <= 1;
      else 
        d1_Comms_mutex_rx_s1_end_xfer <= Comms_mutex_rx_s1_end_xfer;
    end


  //Comms_mutex_rx_s1_waits_for_read in a cycle, which is an e_mux
  assign Comms_mutex_rx_s1_waits_for_read = Comms_mutex_rx_s1_in_a_read_cycle & Comms_mutex_rx_s1_begins_xfer;

  //Comms_mutex_rx_s1_in_a_read_cycle assignment, which is an e_assign
  assign Comms_mutex_rx_s1_in_a_read_cycle = (CPU0_data_master_granted_Comms_mutex_rx_s1 & CPU0_data_master_read) | (CPU1_data_master_granted_Comms_mutex_rx_s1 & CPU1_data_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = Comms_mutex_rx_s1_in_a_read_cycle;

  //Comms_mutex_rx_s1_waits_for_write in a cycle, which is an e_mux
  assign Comms_mutex_rx_s1_waits_for_write = Comms_mutex_rx_s1_in_a_write_cycle & 0;

  //Comms_mutex_rx_s1_in_a_write_cycle assignment, which is an e_assign
  assign Comms_mutex_rx_s1_in_a_write_cycle = (CPU0_data_master_granted_Comms_mutex_rx_s1 & CPU0_data_master_write) | (CPU1_data_master_granted_Comms_mutex_rx_s1 & CPU1_data_master_write);

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = Comms_mutex_rx_s1_in_a_write_cycle;

  assign wait_for_Comms_mutex_rx_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //Comms_mutex_rx/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_granted_Comms_mutex_rx_s1 + CPU1_data_master_granted_Comms_mutex_rx_s1 > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_saved_grant_Comms_mutex_rx_s1 + CPU1_data_master_saved_grant_Comms_mutex_rx_s1 > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module Comms_mutex_tx_s1_arbitrator (
                                      // inputs:
                                       CPU0_data_master_address_to_slave,
                                       CPU0_data_master_latency_counter,
                                       CPU0_data_master_read,
                                       CPU0_data_master_write,
                                       CPU0_data_master_writedata,
                                       CPU1_data_master_address_to_slave,
                                       CPU1_data_master_latency_counter,
                                       CPU1_data_master_read,
                                       CPU1_data_master_write,
                                       CPU1_data_master_writedata,
                                       Comms_mutex_tx_s1_readdata,
                                       clk,
                                       reset_n,

                                      // outputs:
                                       CPU0_data_master_granted_Comms_mutex_tx_s1,
                                       CPU0_data_master_qualified_request_Comms_mutex_tx_s1,
                                       CPU0_data_master_read_data_valid_Comms_mutex_tx_s1,
                                       CPU0_data_master_requests_Comms_mutex_tx_s1,
                                       CPU1_data_master_granted_Comms_mutex_tx_s1,
                                       CPU1_data_master_qualified_request_Comms_mutex_tx_s1,
                                       CPU1_data_master_read_data_valid_Comms_mutex_tx_s1,
                                       CPU1_data_master_requests_Comms_mutex_tx_s1,
                                       Comms_mutex_tx_s1_address,
                                       Comms_mutex_tx_s1_chipselect,
                                       Comms_mutex_tx_s1_read,
                                       Comms_mutex_tx_s1_readdata_from_sa,
                                       Comms_mutex_tx_s1_reset_n,
                                       Comms_mutex_tx_s1_write,
                                       Comms_mutex_tx_s1_writedata,
                                       d1_Comms_mutex_tx_s1_end_xfer
                                    )
;

  output           CPU0_data_master_granted_Comms_mutex_tx_s1;
  output           CPU0_data_master_qualified_request_Comms_mutex_tx_s1;
  output           CPU0_data_master_read_data_valid_Comms_mutex_tx_s1;
  output           CPU0_data_master_requests_Comms_mutex_tx_s1;
  output           CPU1_data_master_granted_Comms_mutex_tx_s1;
  output           CPU1_data_master_qualified_request_Comms_mutex_tx_s1;
  output           CPU1_data_master_read_data_valid_Comms_mutex_tx_s1;
  output           CPU1_data_master_requests_Comms_mutex_tx_s1;
  output           Comms_mutex_tx_s1_address;
  output           Comms_mutex_tx_s1_chipselect;
  output           Comms_mutex_tx_s1_read;
  output  [ 31: 0] Comms_mutex_tx_s1_readdata_from_sa;
  output           Comms_mutex_tx_s1_reset_n;
  output           Comms_mutex_tx_s1_write;
  output  [ 31: 0] Comms_mutex_tx_s1_writedata;
  output           d1_Comms_mutex_tx_s1_end_xfer;
  input   [ 18: 0] CPU0_data_master_address_to_slave;
  input            CPU0_data_master_latency_counter;
  input            CPU0_data_master_read;
  input            CPU0_data_master_write;
  input   [ 31: 0] CPU0_data_master_writedata;
  input   [ 18: 0] CPU1_data_master_address_to_slave;
  input            CPU1_data_master_latency_counter;
  input            CPU1_data_master_read;
  input            CPU1_data_master_write;
  input   [ 31: 0] CPU1_data_master_writedata;
  input   [ 31: 0] Comms_mutex_tx_s1_readdata;
  input            clk;
  input            reset_n;

  wire             CPU0_data_master_arbiterlock;
  wire             CPU0_data_master_arbiterlock2;
  wire             CPU0_data_master_continuerequest;
  wire             CPU0_data_master_granted_Comms_mutex_tx_s1;
  wire             CPU0_data_master_qualified_request_Comms_mutex_tx_s1;
  wire             CPU0_data_master_read_data_valid_Comms_mutex_tx_s1;
  wire             CPU0_data_master_requests_Comms_mutex_tx_s1;
  wire             CPU0_data_master_saved_grant_Comms_mutex_tx_s1;
  wire             CPU1_data_master_arbiterlock;
  wire             CPU1_data_master_arbiterlock2;
  wire             CPU1_data_master_continuerequest;
  wire             CPU1_data_master_granted_Comms_mutex_tx_s1;
  wire             CPU1_data_master_qualified_request_Comms_mutex_tx_s1;
  wire             CPU1_data_master_read_data_valid_Comms_mutex_tx_s1;
  wire             CPU1_data_master_requests_Comms_mutex_tx_s1;
  wire             CPU1_data_master_saved_grant_Comms_mutex_tx_s1;
  wire             Comms_mutex_tx_s1_address;
  wire             Comms_mutex_tx_s1_allgrants;
  wire             Comms_mutex_tx_s1_allow_new_arb_cycle;
  wire             Comms_mutex_tx_s1_any_bursting_master_saved_grant;
  wire             Comms_mutex_tx_s1_any_continuerequest;
  reg     [  1: 0] Comms_mutex_tx_s1_arb_addend;
  wire             Comms_mutex_tx_s1_arb_counter_enable;
  reg              Comms_mutex_tx_s1_arb_share_counter;
  wire             Comms_mutex_tx_s1_arb_share_counter_next_value;
  wire             Comms_mutex_tx_s1_arb_share_set_values;
  wire    [  1: 0] Comms_mutex_tx_s1_arb_winner;
  wire             Comms_mutex_tx_s1_arbitration_holdoff_internal;
  wire             Comms_mutex_tx_s1_beginbursttransfer_internal;
  wire             Comms_mutex_tx_s1_begins_xfer;
  wire             Comms_mutex_tx_s1_chipselect;
  wire    [  3: 0] Comms_mutex_tx_s1_chosen_master_double_vector;
  wire    [  1: 0] Comms_mutex_tx_s1_chosen_master_rot_left;
  wire             Comms_mutex_tx_s1_end_xfer;
  wire             Comms_mutex_tx_s1_firsttransfer;
  wire    [  1: 0] Comms_mutex_tx_s1_grant_vector;
  wire             Comms_mutex_tx_s1_in_a_read_cycle;
  wire             Comms_mutex_tx_s1_in_a_write_cycle;
  wire    [  1: 0] Comms_mutex_tx_s1_master_qreq_vector;
  wire             Comms_mutex_tx_s1_non_bursting_master_requests;
  wire             Comms_mutex_tx_s1_read;
  wire    [ 31: 0] Comms_mutex_tx_s1_readdata_from_sa;
  reg              Comms_mutex_tx_s1_reg_firsttransfer;
  wire             Comms_mutex_tx_s1_reset_n;
  reg     [  1: 0] Comms_mutex_tx_s1_saved_chosen_master_vector;
  reg              Comms_mutex_tx_s1_slavearbiterlockenable;
  wire             Comms_mutex_tx_s1_slavearbiterlockenable2;
  wire             Comms_mutex_tx_s1_unreg_firsttransfer;
  wire             Comms_mutex_tx_s1_waits_for_read;
  wire             Comms_mutex_tx_s1_waits_for_write;
  wire             Comms_mutex_tx_s1_write;
  wire    [ 31: 0] Comms_mutex_tx_s1_writedata;
  reg              d1_Comms_mutex_tx_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_Comms_mutex_tx_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_CPU0_data_master_granted_slave_Comms_mutex_tx_s1;
  reg              last_cycle_CPU1_data_master_granted_slave_Comms_mutex_tx_s1;
  wire    [ 18: 0] shifted_address_to_Comms_mutex_tx_s1_from_CPU0_data_master;
  wire    [ 18: 0] shifted_address_to_Comms_mutex_tx_s1_from_CPU1_data_master;
  wire             wait_for_Comms_mutex_tx_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~Comms_mutex_tx_s1_end_xfer;
    end


  assign Comms_mutex_tx_s1_begins_xfer = ~d1_reasons_to_wait & ((CPU0_data_master_qualified_request_Comms_mutex_tx_s1 | CPU1_data_master_qualified_request_Comms_mutex_tx_s1));
  //assign Comms_mutex_tx_s1_readdata_from_sa = Comms_mutex_tx_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign Comms_mutex_tx_s1_readdata_from_sa = Comms_mutex_tx_s1_readdata;

  assign CPU0_data_master_requests_Comms_mutex_tx_s1 = ({CPU0_data_master_address_to_slave[18 : 3] , 3'b0} == 19'h43010) & (CPU0_data_master_read | CPU0_data_master_write);
  //Comms_mutex_tx_s1_arb_share_counter set values, which is an e_mux
  assign Comms_mutex_tx_s1_arb_share_set_values = 1;

  //Comms_mutex_tx_s1_non_bursting_master_requests mux, which is an e_mux
  assign Comms_mutex_tx_s1_non_bursting_master_requests = CPU0_data_master_requests_Comms_mutex_tx_s1 |
    CPU1_data_master_requests_Comms_mutex_tx_s1 |
    CPU0_data_master_requests_Comms_mutex_tx_s1 |
    CPU1_data_master_requests_Comms_mutex_tx_s1;

  //Comms_mutex_tx_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign Comms_mutex_tx_s1_any_bursting_master_saved_grant = 0;

  //Comms_mutex_tx_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign Comms_mutex_tx_s1_arb_share_counter_next_value = Comms_mutex_tx_s1_firsttransfer ? (Comms_mutex_tx_s1_arb_share_set_values - 1) : |Comms_mutex_tx_s1_arb_share_counter ? (Comms_mutex_tx_s1_arb_share_counter - 1) : 0;

  //Comms_mutex_tx_s1_allgrants all slave grants, which is an e_mux
  assign Comms_mutex_tx_s1_allgrants = (|Comms_mutex_tx_s1_grant_vector) |
    (|Comms_mutex_tx_s1_grant_vector) |
    (|Comms_mutex_tx_s1_grant_vector) |
    (|Comms_mutex_tx_s1_grant_vector);

  //Comms_mutex_tx_s1_end_xfer assignment, which is an e_assign
  assign Comms_mutex_tx_s1_end_xfer = ~(Comms_mutex_tx_s1_waits_for_read | Comms_mutex_tx_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_Comms_mutex_tx_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_Comms_mutex_tx_s1 = Comms_mutex_tx_s1_end_xfer & (~Comms_mutex_tx_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //Comms_mutex_tx_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign Comms_mutex_tx_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_Comms_mutex_tx_s1 & Comms_mutex_tx_s1_allgrants) | (end_xfer_arb_share_counter_term_Comms_mutex_tx_s1 & ~Comms_mutex_tx_s1_non_bursting_master_requests);

  //Comms_mutex_tx_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_tx_s1_arb_share_counter <= 0;
      else if (Comms_mutex_tx_s1_arb_counter_enable)
          Comms_mutex_tx_s1_arb_share_counter <= Comms_mutex_tx_s1_arb_share_counter_next_value;
    end


  //Comms_mutex_tx_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_tx_s1_slavearbiterlockenable <= 0;
      else if ((|Comms_mutex_tx_s1_master_qreq_vector & end_xfer_arb_share_counter_term_Comms_mutex_tx_s1) | (end_xfer_arb_share_counter_term_Comms_mutex_tx_s1 & ~Comms_mutex_tx_s1_non_bursting_master_requests))
          Comms_mutex_tx_s1_slavearbiterlockenable <= |Comms_mutex_tx_s1_arb_share_counter_next_value;
    end


  //CPU0/data_master Comms_mutex_tx/s1 arbiterlock, which is an e_assign
  assign CPU0_data_master_arbiterlock = Comms_mutex_tx_s1_slavearbiterlockenable & CPU0_data_master_continuerequest;

  //Comms_mutex_tx_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign Comms_mutex_tx_s1_slavearbiterlockenable2 = |Comms_mutex_tx_s1_arb_share_counter_next_value;

  //CPU0/data_master Comms_mutex_tx/s1 arbiterlock2, which is an e_assign
  assign CPU0_data_master_arbiterlock2 = Comms_mutex_tx_s1_slavearbiterlockenable2 & CPU0_data_master_continuerequest;

  //CPU1/data_master Comms_mutex_tx/s1 arbiterlock, which is an e_assign
  assign CPU1_data_master_arbiterlock = Comms_mutex_tx_s1_slavearbiterlockenable & CPU1_data_master_continuerequest;

  //CPU1/data_master Comms_mutex_tx/s1 arbiterlock2, which is an e_assign
  assign CPU1_data_master_arbiterlock2 = Comms_mutex_tx_s1_slavearbiterlockenable2 & CPU1_data_master_continuerequest;

  //CPU1/data_master granted Comms_mutex_tx/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU1_data_master_granted_slave_Comms_mutex_tx_s1 <= 0;
      else 
        last_cycle_CPU1_data_master_granted_slave_Comms_mutex_tx_s1 <= CPU1_data_master_saved_grant_Comms_mutex_tx_s1 ? 1 : (Comms_mutex_tx_s1_arbitration_holdoff_internal | ~CPU1_data_master_requests_Comms_mutex_tx_s1) ? 0 : last_cycle_CPU1_data_master_granted_slave_Comms_mutex_tx_s1;
    end


  //CPU1_data_master_continuerequest continued request, which is an e_mux
  assign CPU1_data_master_continuerequest = last_cycle_CPU1_data_master_granted_slave_Comms_mutex_tx_s1 & CPU1_data_master_requests_Comms_mutex_tx_s1;

  //Comms_mutex_tx_s1_any_continuerequest at least one master continues requesting, which is an e_mux
  assign Comms_mutex_tx_s1_any_continuerequest = CPU1_data_master_continuerequest |
    CPU0_data_master_continuerequest;

  assign CPU0_data_master_qualified_request_Comms_mutex_tx_s1 = CPU0_data_master_requests_Comms_mutex_tx_s1 & ~((CPU0_data_master_read & ((CPU0_data_master_latency_counter != 0))) | CPU1_data_master_arbiterlock);
  //local readdatavalid CPU0_data_master_read_data_valid_Comms_mutex_tx_s1, which is an e_mux
  assign CPU0_data_master_read_data_valid_Comms_mutex_tx_s1 = CPU0_data_master_granted_Comms_mutex_tx_s1 & CPU0_data_master_read & ~Comms_mutex_tx_s1_waits_for_read;

  //Comms_mutex_tx_s1_writedata mux, which is an e_mux
  assign Comms_mutex_tx_s1_writedata = (CPU0_data_master_granted_Comms_mutex_tx_s1)? CPU0_data_master_writedata :
    CPU1_data_master_writedata;

  assign CPU1_data_master_requests_Comms_mutex_tx_s1 = ({CPU1_data_master_address_to_slave[18 : 3] , 3'b0} == 19'h43010) & (CPU1_data_master_read | CPU1_data_master_write);
  //CPU0/data_master granted Comms_mutex_tx/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU0_data_master_granted_slave_Comms_mutex_tx_s1 <= 0;
      else 
        last_cycle_CPU0_data_master_granted_slave_Comms_mutex_tx_s1 <= CPU0_data_master_saved_grant_Comms_mutex_tx_s1 ? 1 : (Comms_mutex_tx_s1_arbitration_holdoff_internal | ~CPU0_data_master_requests_Comms_mutex_tx_s1) ? 0 : last_cycle_CPU0_data_master_granted_slave_Comms_mutex_tx_s1;
    end


  //CPU0_data_master_continuerequest continued request, which is an e_mux
  assign CPU0_data_master_continuerequest = last_cycle_CPU0_data_master_granted_slave_Comms_mutex_tx_s1 & CPU0_data_master_requests_Comms_mutex_tx_s1;

  assign CPU1_data_master_qualified_request_Comms_mutex_tx_s1 = CPU1_data_master_requests_Comms_mutex_tx_s1 & ~((CPU1_data_master_read & ((CPU1_data_master_latency_counter != 0))) | CPU0_data_master_arbiterlock);
  //local readdatavalid CPU1_data_master_read_data_valid_Comms_mutex_tx_s1, which is an e_mux
  assign CPU1_data_master_read_data_valid_Comms_mutex_tx_s1 = CPU1_data_master_granted_Comms_mutex_tx_s1 & CPU1_data_master_read & ~Comms_mutex_tx_s1_waits_for_read;

  //allow new arb cycle for Comms_mutex_tx/s1, which is an e_assign
  assign Comms_mutex_tx_s1_allow_new_arb_cycle = ~CPU0_data_master_arbiterlock & ~CPU1_data_master_arbiterlock;

  //CPU1/data_master assignment into master qualified-requests vector for Comms_mutex_tx/s1, which is an e_assign
  assign Comms_mutex_tx_s1_master_qreq_vector[0] = CPU1_data_master_qualified_request_Comms_mutex_tx_s1;

  //CPU1/data_master grant Comms_mutex_tx/s1, which is an e_assign
  assign CPU1_data_master_granted_Comms_mutex_tx_s1 = Comms_mutex_tx_s1_grant_vector[0];

  //CPU1/data_master saved-grant Comms_mutex_tx/s1, which is an e_assign
  assign CPU1_data_master_saved_grant_Comms_mutex_tx_s1 = Comms_mutex_tx_s1_arb_winner[0] && CPU1_data_master_requests_Comms_mutex_tx_s1;

  //CPU0/data_master assignment into master qualified-requests vector for Comms_mutex_tx/s1, which is an e_assign
  assign Comms_mutex_tx_s1_master_qreq_vector[1] = CPU0_data_master_qualified_request_Comms_mutex_tx_s1;

  //CPU0/data_master grant Comms_mutex_tx/s1, which is an e_assign
  assign CPU0_data_master_granted_Comms_mutex_tx_s1 = Comms_mutex_tx_s1_grant_vector[1];

  //CPU0/data_master saved-grant Comms_mutex_tx/s1, which is an e_assign
  assign CPU0_data_master_saved_grant_Comms_mutex_tx_s1 = Comms_mutex_tx_s1_arb_winner[1] && CPU0_data_master_requests_Comms_mutex_tx_s1;

  //Comms_mutex_tx/s1 chosen-master double-vector, which is an e_assign
  assign Comms_mutex_tx_s1_chosen_master_double_vector = {Comms_mutex_tx_s1_master_qreq_vector, Comms_mutex_tx_s1_master_qreq_vector} & ({~Comms_mutex_tx_s1_master_qreq_vector, ~Comms_mutex_tx_s1_master_qreq_vector} + Comms_mutex_tx_s1_arb_addend);

  //stable onehot encoding of arb winner
  assign Comms_mutex_tx_s1_arb_winner = (Comms_mutex_tx_s1_allow_new_arb_cycle & | Comms_mutex_tx_s1_grant_vector) ? Comms_mutex_tx_s1_grant_vector : Comms_mutex_tx_s1_saved_chosen_master_vector;

  //saved Comms_mutex_tx_s1_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_tx_s1_saved_chosen_master_vector <= 0;
      else if (Comms_mutex_tx_s1_allow_new_arb_cycle)
          Comms_mutex_tx_s1_saved_chosen_master_vector <= |Comms_mutex_tx_s1_grant_vector ? Comms_mutex_tx_s1_grant_vector : Comms_mutex_tx_s1_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign Comms_mutex_tx_s1_grant_vector = {(Comms_mutex_tx_s1_chosen_master_double_vector[1] | Comms_mutex_tx_s1_chosen_master_double_vector[3]),
    (Comms_mutex_tx_s1_chosen_master_double_vector[0] | Comms_mutex_tx_s1_chosen_master_double_vector[2])};

  //Comms_mutex_tx/s1 chosen master rotated left, which is an e_assign
  assign Comms_mutex_tx_s1_chosen_master_rot_left = (Comms_mutex_tx_s1_arb_winner << 1) ? (Comms_mutex_tx_s1_arb_winner << 1) : 1;

  //Comms_mutex_tx/s1's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_tx_s1_arb_addend <= 1;
      else if (|Comms_mutex_tx_s1_grant_vector)
          Comms_mutex_tx_s1_arb_addend <= Comms_mutex_tx_s1_end_xfer? Comms_mutex_tx_s1_chosen_master_rot_left : Comms_mutex_tx_s1_grant_vector;
    end


  //Comms_mutex_tx_s1_reset_n assignment, which is an e_assign
  assign Comms_mutex_tx_s1_reset_n = reset_n;

  assign Comms_mutex_tx_s1_chipselect = CPU0_data_master_granted_Comms_mutex_tx_s1 | CPU1_data_master_granted_Comms_mutex_tx_s1;
  //Comms_mutex_tx_s1_firsttransfer first transaction, which is an e_assign
  assign Comms_mutex_tx_s1_firsttransfer = Comms_mutex_tx_s1_begins_xfer ? Comms_mutex_tx_s1_unreg_firsttransfer : Comms_mutex_tx_s1_reg_firsttransfer;

  //Comms_mutex_tx_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign Comms_mutex_tx_s1_unreg_firsttransfer = ~(Comms_mutex_tx_s1_slavearbiterlockenable & Comms_mutex_tx_s1_any_continuerequest);

  //Comms_mutex_tx_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          Comms_mutex_tx_s1_reg_firsttransfer <= 1'b1;
      else if (Comms_mutex_tx_s1_begins_xfer)
          Comms_mutex_tx_s1_reg_firsttransfer <= Comms_mutex_tx_s1_unreg_firsttransfer;
    end


  //Comms_mutex_tx_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign Comms_mutex_tx_s1_beginbursttransfer_internal = Comms_mutex_tx_s1_begins_xfer;

  //Comms_mutex_tx_s1_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign Comms_mutex_tx_s1_arbitration_holdoff_internal = Comms_mutex_tx_s1_begins_xfer & Comms_mutex_tx_s1_firsttransfer;

  //Comms_mutex_tx_s1_read assignment, which is an e_mux
  assign Comms_mutex_tx_s1_read = (CPU0_data_master_granted_Comms_mutex_tx_s1 & CPU0_data_master_read) | (CPU1_data_master_granted_Comms_mutex_tx_s1 & CPU1_data_master_read);

  //Comms_mutex_tx_s1_write assignment, which is an e_mux
  assign Comms_mutex_tx_s1_write = (CPU0_data_master_granted_Comms_mutex_tx_s1 & CPU0_data_master_write) | (CPU1_data_master_granted_Comms_mutex_tx_s1 & CPU1_data_master_write);

  assign shifted_address_to_Comms_mutex_tx_s1_from_CPU0_data_master = CPU0_data_master_address_to_slave;
  //Comms_mutex_tx_s1_address mux, which is an e_mux
  assign Comms_mutex_tx_s1_address = (CPU0_data_master_granted_Comms_mutex_tx_s1)? (shifted_address_to_Comms_mutex_tx_s1_from_CPU0_data_master >> 2) :
    (shifted_address_to_Comms_mutex_tx_s1_from_CPU1_data_master >> 2);

  assign shifted_address_to_Comms_mutex_tx_s1_from_CPU1_data_master = CPU1_data_master_address_to_slave;
  //d1_Comms_mutex_tx_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_Comms_mutex_tx_s1_end_xfer <= 1;
      else 
        d1_Comms_mutex_tx_s1_end_xfer <= Comms_mutex_tx_s1_end_xfer;
    end


  //Comms_mutex_tx_s1_waits_for_read in a cycle, which is an e_mux
  assign Comms_mutex_tx_s1_waits_for_read = Comms_mutex_tx_s1_in_a_read_cycle & Comms_mutex_tx_s1_begins_xfer;

  //Comms_mutex_tx_s1_in_a_read_cycle assignment, which is an e_assign
  assign Comms_mutex_tx_s1_in_a_read_cycle = (CPU0_data_master_granted_Comms_mutex_tx_s1 & CPU0_data_master_read) | (CPU1_data_master_granted_Comms_mutex_tx_s1 & CPU1_data_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = Comms_mutex_tx_s1_in_a_read_cycle;

  //Comms_mutex_tx_s1_waits_for_write in a cycle, which is an e_mux
  assign Comms_mutex_tx_s1_waits_for_write = Comms_mutex_tx_s1_in_a_write_cycle & 0;

  //Comms_mutex_tx_s1_in_a_write_cycle assignment, which is an e_assign
  assign Comms_mutex_tx_s1_in_a_write_cycle = (CPU0_data_master_granted_Comms_mutex_tx_s1 & CPU0_data_master_write) | (CPU1_data_master_granted_Comms_mutex_tx_s1 & CPU1_data_master_write);

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = Comms_mutex_tx_s1_in_a_write_cycle;

  assign wait_for_Comms_mutex_tx_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //Comms_mutex_tx/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_granted_Comms_mutex_tx_s1 + CPU1_data_master_granted_Comms_mutex_tx_s1 > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_saved_grant_Comms_mutex_tx_s1 + CPU1_data_master_saved_grant_Comms_mutex_tx_s1 > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module pio_LED_s1_arbitrator (
                               // inputs:
                                CPU0_data_master_address_to_slave,
                                CPU0_data_master_latency_counter,
                                CPU0_data_master_read,
                                CPU0_data_master_write,
                                CPU0_data_master_writedata,
                                CPU1_data_master_address_to_slave,
                                CPU1_data_master_latency_counter,
                                CPU1_data_master_read,
                                CPU1_data_master_write,
                                CPU1_data_master_writedata,
                                clk,
                                pio_LED_s1_readdata,
                                reset_n,

                               // outputs:
                                CPU0_data_master_granted_pio_LED_s1,
                                CPU0_data_master_qualified_request_pio_LED_s1,
                                CPU0_data_master_read_data_valid_pio_LED_s1,
                                CPU0_data_master_requests_pio_LED_s1,
                                CPU1_data_master_granted_pio_LED_s1,
                                CPU1_data_master_qualified_request_pio_LED_s1,
                                CPU1_data_master_read_data_valid_pio_LED_s1,
                                CPU1_data_master_requests_pio_LED_s1,
                                d1_pio_LED_s1_end_xfer,
                                pio_LED_s1_address,
                                pio_LED_s1_chipselect,
                                pio_LED_s1_readdata_from_sa,
                                pio_LED_s1_reset_n,
                                pio_LED_s1_write_n,
                                pio_LED_s1_writedata
                             )
;

  output           CPU0_data_master_granted_pio_LED_s1;
  output           CPU0_data_master_qualified_request_pio_LED_s1;
  output           CPU0_data_master_read_data_valid_pio_LED_s1;
  output           CPU0_data_master_requests_pio_LED_s1;
  output           CPU1_data_master_granted_pio_LED_s1;
  output           CPU1_data_master_qualified_request_pio_LED_s1;
  output           CPU1_data_master_read_data_valid_pio_LED_s1;
  output           CPU1_data_master_requests_pio_LED_s1;
  output           d1_pio_LED_s1_end_xfer;
  output  [  1: 0] pio_LED_s1_address;
  output           pio_LED_s1_chipselect;
  output  [ 31: 0] pio_LED_s1_readdata_from_sa;
  output           pio_LED_s1_reset_n;
  output           pio_LED_s1_write_n;
  output  [ 31: 0] pio_LED_s1_writedata;
  input   [ 18: 0] CPU0_data_master_address_to_slave;
  input            CPU0_data_master_latency_counter;
  input            CPU0_data_master_read;
  input            CPU0_data_master_write;
  input   [ 31: 0] CPU0_data_master_writedata;
  input   [ 18: 0] CPU1_data_master_address_to_slave;
  input            CPU1_data_master_latency_counter;
  input            CPU1_data_master_read;
  input            CPU1_data_master_write;
  input   [ 31: 0] CPU1_data_master_writedata;
  input            clk;
  input   [ 31: 0] pio_LED_s1_readdata;
  input            reset_n;

  wire             CPU0_data_master_arbiterlock;
  wire             CPU0_data_master_arbiterlock2;
  wire             CPU0_data_master_continuerequest;
  wire             CPU0_data_master_granted_pio_LED_s1;
  wire             CPU0_data_master_qualified_request_pio_LED_s1;
  wire             CPU0_data_master_read_data_valid_pio_LED_s1;
  wire             CPU0_data_master_requests_pio_LED_s1;
  wire             CPU0_data_master_saved_grant_pio_LED_s1;
  wire             CPU1_data_master_arbiterlock;
  wire             CPU1_data_master_arbiterlock2;
  wire             CPU1_data_master_continuerequest;
  wire             CPU1_data_master_granted_pio_LED_s1;
  wire             CPU1_data_master_qualified_request_pio_LED_s1;
  wire             CPU1_data_master_read_data_valid_pio_LED_s1;
  wire             CPU1_data_master_requests_pio_LED_s1;
  wire             CPU1_data_master_saved_grant_pio_LED_s1;
  reg              d1_pio_LED_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_pio_LED_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_CPU0_data_master_granted_slave_pio_LED_s1;
  reg              last_cycle_CPU1_data_master_granted_slave_pio_LED_s1;
  wire    [  1: 0] pio_LED_s1_address;
  wire             pio_LED_s1_allgrants;
  wire             pio_LED_s1_allow_new_arb_cycle;
  wire             pio_LED_s1_any_bursting_master_saved_grant;
  wire             pio_LED_s1_any_continuerequest;
  reg     [  1: 0] pio_LED_s1_arb_addend;
  wire             pio_LED_s1_arb_counter_enable;
  reg              pio_LED_s1_arb_share_counter;
  wire             pio_LED_s1_arb_share_counter_next_value;
  wire             pio_LED_s1_arb_share_set_values;
  wire    [  1: 0] pio_LED_s1_arb_winner;
  wire             pio_LED_s1_arbitration_holdoff_internal;
  wire             pio_LED_s1_beginbursttransfer_internal;
  wire             pio_LED_s1_begins_xfer;
  wire             pio_LED_s1_chipselect;
  wire    [  3: 0] pio_LED_s1_chosen_master_double_vector;
  wire    [  1: 0] pio_LED_s1_chosen_master_rot_left;
  wire             pio_LED_s1_end_xfer;
  wire             pio_LED_s1_firsttransfer;
  wire    [  1: 0] pio_LED_s1_grant_vector;
  wire             pio_LED_s1_in_a_read_cycle;
  wire             pio_LED_s1_in_a_write_cycle;
  wire    [  1: 0] pio_LED_s1_master_qreq_vector;
  wire             pio_LED_s1_non_bursting_master_requests;
  wire    [ 31: 0] pio_LED_s1_readdata_from_sa;
  reg              pio_LED_s1_reg_firsttransfer;
  wire             pio_LED_s1_reset_n;
  reg     [  1: 0] pio_LED_s1_saved_chosen_master_vector;
  reg              pio_LED_s1_slavearbiterlockenable;
  wire             pio_LED_s1_slavearbiterlockenable2;
  wire             pio_LED_s1_unreg_firsttransfer;
  wire             pio_LED_s1_waits_for_read;
  wire             pio_LED_s1_waits_for_write;
  wire             pio_LED_s1_write_n;
  wire    [ 31: 0] pio_LED_s1_writedata;
  wire    [ 18: 0] shifted_address_to_pio_LED_s1_from_CPU0_data_master;
  wire    [ 18: 0] shifted_address_to_pio_LED_s1_from_CPU1_data_master;
  wire             wait_for_pio_LED_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~pio_LED_s1_end_xfer;
    end


  assign pio_LED_s1_begins_xfer = ~d1_reasons_to_wait & ((CPU0_data_master_qualified_request_pio_LED_s1 | CPU1_data_master_qualified_request_pio_LED_s1));
  //assign pio_LED_s1_readdata_from_sa = pio_LED_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign pio_LED_s1_readdata_from_sa = pio_LED_s1_readdata;

  assign CPU0_data_master_requests_pio_LED_s1 = ({CPU0_data_master_address_to_slave[18 : 4] , 4'b0} == 19'h43000) & (CPU0_data_master_read | CPU0_data_master_write);
  //pio_LED_s1_arb_share_counter set values, which is an e_mux
  assign pio_LED_s1_arb_share_set_values = 1;

  //pio_LED_s1_non_bursting_master_requests mux, which is an e_mux
  assign pio_LED_s1_non_bursting_master_requests = CPU0_data_master_requests_pio_LED_s1 |
    CPU1_data_master_requests_pio_LED_s1 |
    CPU0_data_master_requests_pio_LED_s1 |
    CPU1_data_master_requests_pio_LED_s1;

  //pio_LED_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign pio_LED_s1_any_bursting_master_saved_grant = 0;

  //pio_LED_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign pio_LED_s1_arb_share_counter_next_value = pio_LED_s1_firsttransfer ? (pio_LED_s1_arb_share_set_values - 1) : |pio_LED_s1_arb_share_counter ? (pio_LED_s1_arb_share_counter - 1) : 0;

  //pio_LED_s1_allgrants all slave grants, which is an e_mux
  assign pio_LED_s1_allgrants = (|pio_LED_s1_grant_vector) |
    (|pio_LED_s1_grant_vector) |
    (|pio_LED_s1_grant_vector) |
    (|pio_LED_s1_grant_vector);

  //pio_LED_s1_end_xfer assignment, which is an e_assign
  assign pio_LED_s1_end_xfer = ~(pio_LED_s1_waits_for_read | pio_LED_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_pio_LED_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_pio_LED_s1 = pio_LED_s1_end_xfer & (~pio_LED_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //pio_LED_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign pio_LED_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_pio_LED_s1 & pio_LED_s1_allgrants) | (end_xfer_arb_share_counter_term_pio_LED_s1 & ~pio_LED_s1_non_bursting_master_requests);

  //pio_LED_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          pio_LED_s1_arb_share_counter <= 0;
      else if (pio_LED_s1_arb_counter_enable)
          pio_LED_s1_arb_share_counter <= pio_LED_s1_arb_share_counter_next_value;
    end


  //pio_LED_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          pio_LED_s1_slavearbiterlockenable <= 0;
      else if ((|pio_LED_s1_master_qreq_vector & end_xfer_arb_share_counter_term_pio_LED_s1) | (end_xfer_arb_share_counter_term_pio_LED_s1 & ~pio_LED_s1_non_bursting_master_requests))
          pio_LED_s1_slavearbiterlockenable <= |pio_LED_s1_arb_share_counter_next_value;
    end


  //CPU0/data_master pio_LED/s1 arbiterlock, which is an e_assign
  assign CPU0_data_master_arbiterlock = pio_LED_s1_slavearbiterlockenable & CPU0_data_master_continuerequest;

  //pio_LED_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign pio_LED_s1_slavearbiterlockenable2 = |pio_LED_s1_arb_share_counter_next_value;

  //CPU0/data_master pio_LED/s1 arbiterlock2, which is an e_assign
  assign CPU0_data_master_arbiterlock2 = pio_LED_s1_slavearbiterlockenable2 & CPU0_data_master_continuerequest;

  //CPU1/data_master pio_LED/s1 arbiterlock, which is an e_assign
  assign CPU1_data_master_arbiterlock = pio_LED_s1_slavearbiterlockenable & CPU1_data_master_continuerequest;

  //CPU1/data_master pio_LED/s1 arbiterlock2, which is an e_assign
  assign CPU1_data_master_arbiterlock2 = pio_LED_s1_slavearbiterlockenable2 & CPU1_data_master_continuerequest;

  //CPU1/data_master granted pio_LED/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU1_data_master_granted_slave_pio_LED_s1 <= 0;
      else 
        last_cycle_CPU1_data_master_granted_slave_pio_LED_s1 <= CPU1_data_master_saved_grant_pio_LED_s1 ? 1 : (pio_LED_s1_arbitration_holdoff_internal | ~CPU1_data_master_requests_pio_LED_s1) ? 0 : last_cycle_CPU1_data_master_granted_slave_pio_LED_s1;
    end


  //CPU1_data_master_continuerequest continued request, which is an e_mux
  assign CPU1_data_master_continuerequest = last_cycle_CPU1_data_master_granted_slave_pio_LED_s1 & CPU1_data_master_requests_pio_LED_s1;

  //pio_LED_s1_any_continuerequest at least one master continues requesting, which is an e_mux
  assign pio_LED_s1_any_continuerequest = CPU1_data_master_continuerequest |
    CPU0_data_master_continuerequest;

  assign CPU0_data_master_qualified_request_pio_LED_s1 = CPU0_data_master_requests_pio_LED_s1 & ~((CPU0_data_master_read & ((CPU0_data_master_latency_counter != 0))) | CPU1_data_master_arbiterlock);
  //local readdatavalid CPU0_data_master_read_data_valid_pio_LED_s1, which is an e_mux
  assign CPU0_data_master_read_data_valid_pio_LED_s1 = CPU0_data_master_granted_pio_LED_s1 & CPU0_data_master_read & ~pio_LED_s1_waits_for_read;

  //pio_LED_s1_writedata mux, which is an e_mux
  assign pio_LED_s1_writedata = (CPU0_data_master_granted_pio_LED_s1)? CPU0_data_master_writedata :
    CPU1_data_master_writedata;

  assign CPU1_data_master_requests_pio_LED_s1 = ({CPU1_data_master_address_to_slave[18 : 4] , 4'b0} == 19'h43000) & (CPU1_data_master_read | CPU1_data_master_write);
  //CPU0/data_master granted pio_LED/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_CPU0_data_master_granted_slave_pio_LED_s1 <= 0;
      else 
        last_cycle_CPU0_data_master_granted_slave_pio_LED_s1 <= CPU0_data_master_saved_grant_pio_LED_s1 ? 1 : (pio_LED_s1_arbitration_holdoff_internal | ~CPU0_data_master_requests_pio_LED_s1) ? 0 : last_cycle_CPU0_data_master_granted_slave_pio_LED_s1;
    end


  //CPU0_data_master_continuerequest continued request, which is an e_mux
  assign CPU0_data_master_continuerequest = last_cycle_CPU0_data_master_granted_slave_pio_LED_s1 & CPU0_data_master_requests_pio_LED_s1;

  assign CPU1_data_master_qualified_request_pio_LED_s1 = CPU1_data_master_requests_pio_LED_s1 & ~((CPU1_data_master_read & ((CPU1_data_master_latency_counter != 0))) | CPU0_data_master_arbiterlock);
  //local readdatavalid CPU1_data_master_read_data_valid_pio_LED_s1, which is an e_mux
  assign CPU1_data_master_read_data_valid_pio_LED_s1 = CPU1_data_master_granted_pio_LED_s1 & CPU1_data_master_read & ~pio_LED_s1_waits_for_read;

  //allow new arb cycle for pio_LED/s1, which is an e_assign
  assign pio_LED_s1_allow_new_arb_cycle = ~CPU0_data_master_arbiterlock & ~CPU1_data_master_arbiterlock;

  //CPU1/data_master assignment into master qualified-requests vector for pio_LED/s1, which is an e_assign
  assign pio_LED_s1_master_qreq_vector[0] = CPU1_data_master_qualified_request_pio_LED_s1;

  //CPU1/data_master grant pio_LED/s1, which is an e_assign
  assign CPU1_data_master_granted_pio_LED_s1 = pio_LED_s1_grant_vector[0];

  //CPU1/data_master saved-grant pio_LED/s1, which is an e_assign
  assign CPU1_data_master_saved_grant_pio_LED_s1 = pio_LED_s1_arb_winner[0] && CPU1_data_master_requests_pio_LED_s1;

  //CPU0/data_master assignment into master qualified-requests vector for pio_LED/s1, which is an e_assign
  assign pio_LED_s1_master_qreq_vector[1] = CPU0_data_master_qualified_request_pio_LED_s1;

  //CPU0/data_master grant pio_LED/s1, which is an e_assign
  assign CPU0_data_master_granted_pio_LED_s1 = pio_LED_s1_grant_vector[1];

  //CPU0/data_master saved-grant pio_LED/s1, which is an e_assign
  assign CPU0_data_master_saved_grant_pio_LED_s1 = pio_LED_s1_arb_winner[1] && CPU0_data_master_requests_pio_LED_s1;

  //pio_LED/s1 chosen-master double-vector, which is an e_assign
  assign pio_LED_s1_chosen_master_double_vector = {pio_LED_s1_master_qreq_vector, pio_LED_s1_master_qreq_vector} & ({~pio_LED_s1_master_qreq_vector, ~pio_LED_s1_master_qreq_vector} + pio_LED_s1_arb_addend);

  //stable onehot encoding of arb winner
  assign pio_LED_s1_arb_winner = (pio_LED_s1_allow_new_arb_cycle & | pio_LED_s1_grant_vector) ? pio_LED_s1_grant_vector : pio_LED_s1_saved_chosen_master_vector;

  //saved pio_LED_s1_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          pio_LED_s1_saved_chosen_master_vector <= 0;
      else if (pio_LED_s1_allow_new_arb_cycle)
          pio_LED_s1_saved_chosen_master_vector <= |pio_LED_s1_grant_vector ? pio_LED_s1_grant_vector : pio_LED_s1_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign pio_LED_s1_grant_vector = {(pio_LED_s1_chosen_master_double_vector[1] | pio_LED_s1_chosen_master_double_vector[3]),
    (pio_LED_s1_chosen_master_double_vector[0] | pio_LED_s1_chosen_master_double_vector[2])};

  //pio_LED/s1 chosen master rotated left, which is an e_assign
  assign pio_LED_s1_chosen_master_rot_left = (pio_LED_s1_arb_winner << 1) ? (pio_LED_s1_arb_winner << 1) : 1;

  //pio_LED/s1's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          pio_LED_s1_arb_addend <= 1;
      else if (|pio_LED_s1_grant_vector)
          pio_LED_s1_arb_addend <= pio_LED_s1_end_xfer? pio_LED_s1_chosen_master_rot_left : pio_LED_s1_grant_vector;
    end


  //pio_LED_s1_reset_n assignment, which is an e_assign
  assign pio_LED_s1_reset_n = reset_n;

  assign pio_LED_s1_chipselect = CPU0_data_master_granted_pio_LED_s1 | CPU1_data_master_granted_pio_LED_s1;
  //pio_LED_s1_firsttransfer first transaction, which is an e_assign
  assign pio_LED_s1_firsttransfer = pio_LED_s1_begins_xfer ? pio_LED_s1_unreg_firsttransfer : pio_LED_s1_reg_firsttransfer;

  //pio_LED_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign pio_LED_s1_unreg_firsttransfer = ~(pio_LED_s1_slavearbiterlockenable & pio_LED_s1_any_continuerequest);

  //pio_LED_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          pio_LED_s1_reg_firsttransfer <= 1'b1;
      else if (pio_LED_s1_begins_xfer)
          pio_LED_s1_reg_firsttransfer <= pio_LED_s1_unreg_firsttransfer;
    end


  //pio_LED_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign pio_LED_s1_beginbursttransfer_internal = pio_LED_s1_begins_xfer;

  //pio_LED_s1_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign pio_LED_s1_arbitration_holdoff_internal = pio_LED_s1_begins_xfer & pio_LED_s1_firsttransfer;

  //~pio_LED_s1_write_n assignment, which is an e_mux
  assign pio_LED_s1_write_n = ~((CPU0_data_master_granted_pio_LED_s1 & CPU0_data_master_write) | (CPU1_data_master_granted_pio_LED_s1 & CPU1_data_master_write));

  assign shifted_address_to_pio_LED_s1_from_CPU0_data_master = CPU0_data_master_address_to_slave;
  //pio_LED_s1_address mux, which is an e_mux
  assign pio_LED_s1_address = (CPU0_data_master_granted_pio_LED_s1)? (shifted_address_to_pio_LED_s1_from_CPU0_data_master >> 2) :
    (shifted_address_to_pio_LED_s1_from_CPU1_data_master >> 2);

  assign shifted_address_to_pio_LED_s1_from_CPU1_data_master = CPU1_data_master_address_to_slave;
  //d1_pio_LED_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_pio_LED_s1_end_xfer <= 1;
      else 
        d1_pio_LED_s1_end_xfer <= pio_LED_s1_end_xfer;
    end


  //pio_LED_s1_waits_for_read in a cycle, which is an e_mux
  assign pio_LED_s1_waits_for_read = pio_LED_s1_in_a_read_cycle & pio_LED_s1_begins_xfer;

  //pio_LED_s1_in_a_read_cycle assignment, which is an e_assign
  assign pio_LED_s1_in_a_read_cycle = (CPU0_data_master_granted_pio_LED_s1 & CPU0_data_master_read) | (CPU1_data_master_granted_pio_LED_s1 & CPU1_data_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = pio_LED_s1_in_a_read_cycle;

  //pio_LED_s1_waits_for_write in a cycle, which is an e_mux
  assign pio_LED_s1_waits_for_write = pio_LED_s1_in_a_write_cycle & 0;

  //pio_LED_s1_in_a_write_cycle assignment, which is an e_assign
  assign pio_LED_s1_in_a_write_cycle = (CPU0_data_master_granted_pio_LED_s1 & CPU0_data_master_write) | (CPU1_data_master_granted_pio_LED_s1 & CPU1_data_master_write);

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = pio_LED_s1_in_a_write_cycle;

  assign wait_for_pio_LED_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //pio_LED/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_granted_pio_LED_s1 + CPU1_data_master_granted_pio_LED_s1 > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (CPU0_data_master_saved_grant_pio_LED_s1 + CPU1_data_master_saved_grant_pio_LED_s1 > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module DE2_115_SOPC_reset_clk_50_domain_synch_module (
                                                       // inputs:
                                                        clk,
                                                        data_in,
                                                        reset_n,

                                                       // outputs:
                                                        data_out
                                                     )
;

  output           data_out;
  input            clk;
  input            data_in;
  input            reset_n;

  reg              data_in_d1 /* synthesis ALTERA_ATTRIBUTE = "{-from \"*\"} CUT=ON ; PRESERVE_REGISTER=ON ; SUPPRESS_DA_RULE_INTERNAL=R101"  */;
  reg              data_out /* synthesis ALTERA_ATTRIBUTE = "PRESERVE_REGISTER=ON ; SUPPRESS_DA_RULE_INTERNAL=R101"  */;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          data_in_d1 <= 0;
      else 
        data_in_d1 <= data_in;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          data_out <= 0;
      else 
        data_out <= data_in_d1;
    end



endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module DE2_115_SOPC (
                      // 1) global signals:
                       clk_50,
                       reset_n,

                      // the_pio_LED
                       out_port_from_the_pio_LED
                    )
;

  output  [  7: 0] out_port_from_the_pio_LED;
  input            clk_50;
  input            reset_n;

  wire             CPU0_JTAG_UART_avalon_jtag_slave_address;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_chipselect;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_dataavailable;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_irq;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_read_n;
  wire    [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_readdata;
  wire    [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_readyfordata;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_reset_n;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_waitrequest;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_write_n;
  wire    [ 31: 0] CPU0_JTAG_UART_avalon_jtag_slave_writedata;
  wire    [ 18: 0] CPU0_data_master_address;
  wire    [ 18: 0] CPU0_data_master_address_to_slave;
  wire    [  3: 0] CPU0_data_master_byteenable;
  wire             CPU0_data_master_debugaccess;
  wire             CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             CPU0_data_master_granted_CPU0_jtag_debug_module;
  wire             CPU0_data_master_granted_CPU0_memory_s1;
  wire             CPU0_data_master_granted_Comms_memory_s1;
  wire             CPU0_data_master_granted_Comms_mutex_rx_s1;
  wire             CPU0_data_master_granted_Comms_mutex_tx_s1;
  wire             CPU0_data_master_granted_pio_LED_s1;
  wire    [ 31: 0] CPU0_data_master_irq;
  wire             CPU0_data_master_latency_counter;
  wire             CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             CPU0_data_master_qualified_request_CPU0_jtag_debug_module;
  wire             CPU0_data_master_qualified_request_CPU0_memory_s1;
  wire             CPU0_data_master_qualified_request_Comms_memory_s1;
  wire             CPU0_data_master_qualified_request_Comms_mutex_rx_s1;
  wire             CPU0_data_master_qualified_request_Comms_mutex_tx_s1;
  wire             CPU0_data_master_qualified_request_pio_LED_s1;
  wire             CPU0_data_master_read;
  wire             CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             CPU0_data_master_read_data_valid_CPU0_jtag_debug_module;
  wire             CPU0_data_master_read_data_valid_CPU0_memory_s1;
  wire             CPU0_data_master_read_data_valid_Comms_memory_s1;
  wire             CPU0_data_master_read_data_valid_Comms_mutex_rx_s1;
  wire             CPU0_data_master_read_data_valid_Comms_mutex_tx_s1;
  wire             CPU0_data_master_read_data_valid_pio_LED_s1;
  wire    [ 31: 0] CPU0_data_master_readdata;
  wire             CPU0_data_master_readdatavalid;
  wire             CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave;
  wire             CPU0_data_master_requests_CPU0_jtag_debug_module;
  wire             CPU0_data_master_requests_CPU0_memory_s1;
  wire             CPU0_data_master_requests_Comms_memory_s1;
  wire             CPU0_data_master_requests_Comms_mutex_rx_s1;
  wire             CPU0_data_master_requests_Comms_mutex_tx_s1;
  wire             CPU0_data_master_requests_pio_LED_s1;
  wire             CPU0_data_master_waitrequest;
  wire             CPU0_data_master_write;
  wire    [ 31: 0] CPU0_data_master_writedata;
  wire    [ 18: 0] CPU0_instruction_master_address;
  wire    [ 18: 0] CPU0_instruction_master_address_to_slave;
  wire             CPU0_instruction_master_granted_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_granted_CPU0_memory_s1;
  wire             CPU0_instruction_master_latency_counter;
  wire             CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_qualified_request_CPU0_memory_s1;
  wire             CPU0_instruction_master_read;
  wire             CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_read_data_valid_CPU0_memory_s1;
  wire    [ 31: 0] CPU0_instruction_master_readdata;
  wire             CPU0_instruction_master_readdatavalid;
  wire             CPU0_instruction_master_requests_CPU0_jtag_debug_module;
  wire             CPU0_instruction_master_requests_CPU0_memory_s1;
  wire             CPU0_instruction_master_waitrequest;
  wire    [  8: 0] CPU0_jtag_debug_module_address;
  wire             CPU0_jtag_debug_module_begintransfer;
  wire    [  3: 0] CPU0_jtag_debug_module_byteenable;
  wire             CPU0_jtag_debug_module_chipselect;
  wire             CPU0_jtag_debug_module_debugaccess;
  wire    [ 31: 0] CPU0_jtag_debug_module_readdata;
  wire    [ 31: 0] CPU0_jtag_debug_module_readdata_from_sa;
  wire             CPU0_jtag_debug_module_reset_n;
  wire             CPU0_jtag_debug_module_resetrequest;
  wire             CPU0_jtag_debug_module_resetrequest_from_sa;
  wire             CPU0_jtag_debug_module_write;
  wire    [ 31: 0] CPU0_jtag_debug_module_writedata;
  wire    [ 14: 0] CPU0_memory_s1_address;
  wire    [  3: 0] CPU0_memory_s1_byteenable;
  wire             CPU0_memory_s1_chipselect;
  wire             CPU0_memory_s1_clken;
  wire    [ 31: 0] CPU0_memory_s1_readdata;
  wire    [ 31: 0] CPU0_memory_s1_readdata_from_sa;
  wire             CPU0_memory_s1_reset;
  wire             CPU0_memory_s1_write;
  wire    [ 31: 0] CPU0_memory_s1_writedata;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_address;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_chipselect;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_dataavailable;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_irq;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_read_n;
  wire    [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_readdata;
  wire    [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_readyfordata;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_reset_n;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_waitrequest;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_write_n;
  wire    [ 31: 0] CPU1_JTAG_UART_avalon_jtag_slave_writedata;
  wire    [ 18: 0] CPU1_data_master_address;
  wire    [ 18: 0] CPU1_data_master_address_to_slave;
  wire    [  3: 0] CPU1_data_master_byteenable;
  wire             CPU1_data_master_debugaccess;
  wire             CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             CPU1_data_master_granted_CPU1_jtag_debug_module;
  wire             CPU1_data_master_granted_CPU1_memory_s1;
  wire             CPU1_data_master_granted_Comms_memory_s1;
  wire             CPU1_data_master_granted_Comms_mutex_rx_s1;
  wire             CPU1_data_master_granted_Comms_mutex_tx_s1;
  wire             CPU1_data_master_granted_pio_LED_s1;
  wire    [ 31: 0] CPU1_data_master_irq;
  wire             CPU1_data_master_latency_counter;
  wire             CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             CPU1_data_master_qualified_request_CPU1_jtag_debug_module;
  wire             CPU1_data_master_qualified_request_CPU1_memory_s1;
  wire             CPU1_data_master_qualified_request_Comms_memory_s1;
  wire             CPU1_data_master_qualified_request_Comms_mutex_rx_s1;
  wire             CPU1_data_master_qualified_request_Comms_mutex_tx_s1;
  wire             CPU1_data_master_qualified_request_pio_LED_s1;
  wire             CPU1_data_master_read;
  wire             CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             CPU1_data_master_read_data_valid_CPU1_jtag_debug_module;
  wire             CPU1_data_master_read_data_valid_CPU1_memory_s1;
  wire             CPU1_data_master_read_data_valid_Comms_memory_s1;
  wire             CPU1_data_master_read_data_valid_Comms_mutex_rx_s1;
  wire             CPU1_data_master_read_data_valid_Comms_mutex_tx_s1;
  wire             CPU1_data_master_read_data_valid_pio_LED_s1;
  wire    [ 31: 0] CPU1_data_master_readdata;
  wire             CPU1_data_master_readdatavalid;
  wire             CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave;
  wire             CPU1_data_master_requests_CPU1_jtag_debug_module;
  wire             CPU1_data_master_requests_CPU1_memory_s1;
  wire             CPU1_data_master_requests_Comms_memory_s1;
  wire             CPU1_data_master_requests_Comms_mutex_rx_s1;
  wire             CPU1_data_master_requests_Comms_mutex_tx_s1;
  wire             CPU1_data_master_requests_pio_LED_s1;
  wire             CPU1_data_master_waitrequest;
  wire             CPU1_data_master_write;
  wire    [ 31: 0] CPU1_data_master_writedata;
  wire    [ 18: 0] CPU1_instruction_master_address;
  wire    [ 18: 0] CPU1_instruction_master_address_to_slave;
  wire             CPU1_instruction_master_granted_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_granted_CPU1_memory_s1;
  wire             CPU1_instruction_master_latency_counter;
  wire             CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_qualified_request_CPU1_memory_s1;
  wire             CPU1_instruction_master_read;
  wire             CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_read_data_valid_CPU1_memory_s1;
  wire    [ 31: 0] CPU1_instruction_master_readdata;
  wire             CPU1_instruction_master_readdatavalid;
  wire             CPU1_instruction_master_requests_CPU1_jtag_debug_module;
  wire             CPU1_instruction_master_requests_CPU1_memory_s1;
  wire             CPU1_instruction_master_waitrequest;
  wire    [  8: 0] CPU1_jtag_debug_module_address;
  wire             CPU1_jtag_debug_module_begintransfer;
  wire    [  3: 0] CPU1_jtag_debug_module_byteenable;
  wire             CPU1_jtag_debug_module_chipselect;
  wire             CPU1_jtag_debug_module_debugaccess;
  wire    [ 31: 0] CPU1_jtag_debug_module_readdata;
  wire    [ 31: 0] CPU1_jtag_debug_module_readdata_from_sa;
  wire             CPU1_jtag_debug_module_reset_n;
  wire             CPU1_jtag_debug_module_resetrequest;
  wire             CPU1_jtag_debug_module_resetrequest_from_sa;
  wire             CPU1_jtag_debug_module_write;
  wire    [ 31: 0] CPU1_jtag_debug_module_writedata;
  wire    [ 14: 0] CPU1_memory_s1_address;
  wire    [  3: 0] CPU1_memory_s1_byteenable;
  wire             CPU1_memory_s1_chipselect;
  wire             CPU1_memory_s1_clken;
  wire    [ 31: 0] CPU1_memory_s1_readdata;
  wire    [ 31: 0] CPU1_memory_s1_readdata_from_sa;
  wire             CPU1_memory_s1_reset;
  wire             CPU1_memory_s1_write;
  wire    [ 31: 0] CPU1_memory_s1_writedata;
  wire    [  9: 0] Comms_memory_s1_address;
  wire    [  3: 0] Comms_memory_s1_byteenable;
  wire             Comms_memory_s1_chipselect;
  wire             Comms_memory_s1_clken;
  wire    [ 31: 0] Comms_memory_s1_readdata;
  wire    [ 31: 0] Comms_memory_s1_readdata_from_sa;
  wire             Comms_memory_s1_reset;
  wire             Comms_memory_s1_write;
  wire    [ 31: 0] Comms_memory_s1_writedata;
  wire             Comms_mutex_rx_s1_address;
  wire             Comms_mutex_rx_s1_chipselect;
  wire             Comms_mutex_rx_s1_read;
  wire    [ 31: 0] Comms_mutex_rx_s1_readdata;
  wire    [ 31: 0] Comms_mutex_rx_s1_readdata_from_sa;
  wire             Comms_mutex_rx_s1_reset_n;
  wire             Comms_mutex_rx_s1_write;
  wire    [ 31: 0] Comms_mutex_rx_s1_writedata;
  wire             Comms_mutex_tx_s1_address;
  wire             Comms_mutex_tx_s1_chipselect;
  wire             Comms_mutex_tx_s1_read;
  wire    [ 31: 0] Comms_mutex_tx_s1_readdata;
  wire    [ 31: 0] Comms_mutex_tx_s1_readdata_from_sa;
  wire             Comms_mutex_tx_s1_reset_n;
  wire             Comms_mutex_tx_s1_write;
  wire    [ 31: 0] Comms_mutex_tx_s1_writedata;
  wire             clk_50_reset_n;
  wire             d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer;
  wire             d1_CPU0_jtag_debug_module_end_xfer;
  wire             d1_CPU0_memory_s1_end_xfer;
  wire             d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer;
  wire             d1_CPU1_jtag_debug_module_end_xfer;
  wire             d1_CPU1_memory_s1_end_xfer;
  wire             d1_Comms_memory_s1_end_xfer;
  wire             d1_Comms_mutex_rx_s1_end_xfer;
  wire             d1_Comms_mutex_tx_s1_end_xfer;
  wire             d1_pio_LED_s1_end_xfer;
  wire    [  7: 0] out_port_from_the_pio_LED;
  wire    [  1: 0] pio_LED_s1_address;
  wire             pio_LED_s1_chipselect;
  wire    [ 31: 0] pio_LED_s1_readdata;
  wire    [ 31: 0] pio_LED_s1_readdata_from_sa;
  wire             pio_LED_s1_reset_n;
  wire             pio_LED_s1_write_n;
  wire    [ 31: 0] pio_LED_s1_writedata;
  wire             reset_n_sources;
  CPU0_jtag_debug_module_arbitrator the_CPU0_jtag_debug_module
    (
      .CPU0_data_master_address_to_slave                                (CPU0_data_master_address_to_slave),
      .CPU0_data_master_byteenable                                      (CPU0_data_master_byteenable),
      .CPU0_data_master_debugaccess                                     (CPU0_data_master_debugaccess),
      .CPU0_data_master_granted_CPU0_jtag_debug_module                  (CPU0_data_master_granted_CPU0_jtag_debug_module),
      .CPU0_data_master_latency_counter                                 (CPU0_data_master_latency_counter),
      .CPU0_data_master_qualified_request_CPU0_jtag_debug_module        (CPU0_data_master_qualified_request_CPU0_jtag_debug_module),
      .CPU0_data_master_read                                            (CPU0_data_master_read),
      .CPU0_data_master_read_data_valid_CPU0_jtag_debug_module          (CPU0_data_master_read_data_valid_CPU0_jtag_debug_module),
      .CPU0_data_master_requests_CPU0_jtag_debug_module                 (CPU0_data_master_requests_CPU0_jtag_debug_module),
      .CPU0_data_master_write                                           (CPU0_data_master_write),
      .CPU0_data_master_writedata                                       (CPU0_data_master_writedata),
      .CPU0_instruction_master_address_to_slave                         (CPU0_instruction_master_address_to_slave),
      .CPU0_instruction_master_granted_CPU0_jtag_debug_module           (CPU0_instruction_master_granted_CPU0_jtag_debug_module),
      .CPU0_instruction_master_latency_counter                          (CPU0_instruction_master_latency_counter),
      .CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module (CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module),
      .CPU0_instruction_master_read                                     (CPU0_instruction_master_read),
      .CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module   (CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module),
      .CPU0_instruction_master_requests_CPU0_jtag_debug_module          (CPU0_instruction_master_requests_CPU0_jtag_debug_module),
      .CPU0_jtag_debug_module_address                                   (CPU0_jtag_debug_module_address),
      .CPU0_jtag_debug_module_begintransfer                             (CPU0_jtag_debug_module_begintransfer),
      .CPU0_jtag_debug_module_byteenable                                (CPU0_jtag_debug_module_byteenable),
      .CPU0_jtag_debug_module_chipselect                                (CPU0_jtag_debug_module_chipselect),
      .CPU0_jtag_debug_module_debugaccess                               (CPU0_jtag_debug_module_debugaccess),
      .CPU0_jtag_debug_module_readdata                                  (CPU0_jtag_debug_module_readdata),
      .CPU0_jtag_debug_module_readdata_from_sa                          (CPU0_jtag_debug_module_readdata_from_sa),
      .CPU0_jtag_debug_module_reset_n                                   (CPU0_jtag_debug_module_reset_n),
      .CPU0_jtag_debug_module_resetrequest                              (CPU0_jtag_debug_module_resetrequest),
      .CPU0_jtag_debug_module_resetrequest_from_sa                      (CPU0_jtag_debug_module_resetrequest_from_sa),
      .CPU0_jtag_debug_module_write                                     (CPU0_jtag_debug_module_write),
      .CPU0_jtag_debug_module_writedata                                 (CPU0_jtag_debug_module_writedata),
      .clk                                                              (clk_50),
      .d1_CPU0_jtag_debug_module_end_xfer                               (d1_CPU0_jtag_debug_module_end_xfer),
      .reset_n                                                          (clk_50_reset_n)
    );

  CPU0_data_master_arbitrator the_CPU0_data_master
    (
      .CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa                        (CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa),
      .CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa                   (CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa),
      .CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa                (CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa),
      .CPU0_data_master_address                                            (CPU0_data_master_address),
      .CPU0_data_master_address_to_slave                                   (CPU0_data_master_address_to_slave),
      .CPU0_data_master_byteenable                                         (CPU0_data_master_byteenable),
      .CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave           (CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave),
      .CPU0_data_master_granted_CPU0_jtag_debug_module                     (CPU0_data_master_granted_CPU0_jtag_debug_module),
      .CPU0_data_master_granted_CPU0_memory_s1                             (CPU0_data_master_granted_CPU0_memory_s1),
      .CPU0_data_master_granted_Comms_memory_s1                            (CPU0_data_master_granted_Comms_memory_s1),
      .CPU0_data_master_granted_Comms_mutex_rx_s1                          (CPU0_data_master_granted_Comms_mutex_rx_s1),
      .CPU0_data_master_granted_Comms_mutex_tx_s1                          (CPU0_data_master_granted_Comms_mutex_tx_s1),
      .CPU0_data_master_granted_pio_LED_s1                                 (CPU0_data_master_granted_pio_LED_s1),
      .CPU0_data_master_irq                                                (CPU0_data_master_irq),
      .CPU0_data_master_latency_counter                                    (CPU0_data_master_latency_counter),
      .CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave (CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave),
      .CPU0_data_master_qualified_request_CPU0_jtag_debug_module           (CPU0_data_master_qualified_request_CPU0_jtag_debug_module),
      .CPU0_data_master_qualified_request_CPU0_memory_s1                   (CPU0_data_master_qualified_request_CPU0_memory_s1),
      .CPU0_data_master_qualified_request_Comms_memory_s1                  (CPU0_data_master_qualified_request_Comms_memory_s1),
      .CPU0_data_master_qualified_request_Comms_mutex_rx_s1                (CPU0_data_master_qualified_request_Comms_mutex_rx_s1),
      .CPU0_data_master_qualified_request_Comms_mutex_tx_s1                (CPU0_data_master_qualified_request_Comms_mutex_tx_s1),
      .CPU0_data_master_qualified_request_pio_LED_s1                       (CPU0_data_master_qualified_request_pio_LED_s1),
      .CPU0_data_master_read                                               (CPU0_data_master_read),
      .CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave   (CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave),
      .CPU0_data_master_read_data_valid_CPU0_jtag_debug_module             (CPU0_data_master_read_data_valid_CPU0_jtag_debug_module),
      .CPU0_data_master_read_data_valid_CPU0_memory_s1                     (CPU0_data_master_read_data_valid_CPU0_memory_s1),
      .CPU0_data_master_read_data_valid_Comms_memory_s1                    (CPU0_data_master_read_data_valid_Comms_memory_s1),
      .CPU0_data_master_read_data_valid_Comms_mutex_rx_s1                  (CPU0_data_master_read_data_valid_Comms_mutex_rx_s1),
      .CPU0_data_master_read_data_valid_Comms_mutex_tx_s1                  (CPU0_data_master_read_data_valid_Comms_mutex_tx_s1),
      .CPU0_data_master_read_data_valid_pio_LED_s1                         (CPU0_data_master_read_data_valid_pio_LED_s1),
      .CPU0_data_master_readdata                                           (CPU0_data_master_readdata),
      .CPU0_data_master_readdatavalid                                      (CPU0_data_master_readdatavalid),
      .CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave          (CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave),
      .CPU0_data_master_requests_CPU0_jtag_debug_module                    (CPU0_data_master_requests_CPU0_jtag_debug_module),
      .CPU0_data_master_requests_CPU0_memory_s1                            (CPU0_data_master_requests_CPU0_memory_s1),
      .CPU0_data_master_requests_Comms_memory_s1                           (CPU0_data_master_requests_Comms_memory_s1),
      .CPU0_data_master_requests_Comms_mutex_rx_s1                         (CPU0_data_master_requests_Comms_mutex_rx_s1),
      .CPU0_data_master_requests_Comms_mutex_tx_s1                         (CPU0_data_master_requests_Comms_mutex_tx_s1),
      .CPU0_data_master_requests_pio_LED_s1                                (CPU0_data_master_requests_pio_LED_s1),
      .CPU0_data_master_waitrequest                                        (CPU0_data_master_waitrequest),
      .CPU0_data_master_write                                              (CPU0_data_master_write),
      .CPU0_data_master_writedata                                          (CPU0_data_master_writedata),
      .CPU0_jtag_debug_module_readdata_from_sa                             (CPU0_jtag_debug_module_readdata_from_sa),
      .CPU0_memory_s1_readdata_from_sa                                     (CPU0_memory_s1_readdata_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa                        (CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa),
      .Comms_memory_s1_readdata_from_sa                                    (Comms_memory_s1_readdata_from_sa),
      .Comms_mutex_rx_s1_readdata_from_sa                                  (Comms_mutex_rx_s1_readdata_from_sa),
      .Comms_mutex_tx_s1_readdata_from_sa                                  (Comms_mutex_tx_s1_readdata_from_sa),
      .clk                                                                 (clk_50),
      .d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer                        (d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer),
      .d1_CPU0_jtag_debug_module_end_xfer                                  (d1_CPU0_jtag_debug_module_end_xfer),
      .d1_CPU0_memory_s1_end_xfer                                          (d1_CPU0_memory_s1_end_xfer),
      .d1_Comms_memory_s1_end_xfer                                         (d1_Comms_memory_s1_end_xfer),
      .d1_Comms_mutex_rx_s1_end_xfer                                       (d1_Comms_mutex_rx_s1_end_xfer),
      .d1_Comms_mutex_tx_s1_end_xfer                                       (d1_Comms_mutex_tx_s1_end_xfer),
      .d1_pio_LED_s1_end_xfer                                              (d1_pio_LED_s1_end_xfer),
      .pio_LED_s1_readdata_from_sa                                         (pio_LED_s1_readdata_from_sa),
      .reset_n                                                             (clk_50_reset_n)
    );

  CPU0_instruction_master_arbitrator the_CPU0_instruction_master
    (
      .CPU0_instruction_master_address                                  (CPU0_instruction_master_address),
      .CPU0_instruction_master_address_to_slave                         (CPU0_instruction_master_address_to_slave),
      .CPU0_instruction_master_granted_CPU0_jtag_debug_module           (CPU0_instruction_master_granted_CPU0_jtag_debug_module),
      .CPU0_instruction_master_granted_CPU0_memory_s1                   (CPU0_instruction_master_granted_CPU0_memory_s1),
      .CPU0_instruction_master_latency_counter                          (CPU0_instruction_master_latency_counter),
      .CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module (CPU0_instruction_master_qualified_request_CPU0_jtag_debug_module),
      .CPU0_instruction_master_qualified_request_CPU0_memory_s1         (CPU0_instruction_master_qualified_request_CPU0_memory_s1),
      .CPU0_instruction_master_read                                     (CPU0_instruction_master_read),
      .CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module   (CPU0_instruction_master_read_data_valid_CPU0_jtag_debug_module),
      .CPU0_instruction_master_read_data_valid_CPU0_memory_s1           (CPU0_instruction_master_read_data_valid_CPU0_memory_s1),
      .CPU0_instruction_master_readdata                                 (CPU0_instruction_master_readdata),
      .CPU0_instruction_master_readdatavalid                            (CPU0_instruction_master_readdatavalid),
      .CPU0_instruction_master_requests_CPU0_jtag_debug_module          (CPU0_instruction_master_requests_CPU0_jtag_debug_module),
      .CPU0_instruction_master_requests_CPU0_memory_s1                  (CPU0_instruction_master_requests_CPU0_memory_s1),
      .CPU0_instruction_master_waitrequest                              (CPU0_instruction_master_waitrequest),
      .CPU0_jtag_debug_module_readdata_from_sa                          (CPU0_jtag_debug_module_readdata_from_sa),
      .CPU0_memory_s1_readdata_from_sa                                  (CPU0_memory_s1_readdata_from_sa),
      .clk                                                              (clk_50),
      .d1_CPU0_jtag_debug_module_end_xfer                               (d1_CPU0_jtag_debug_module_end_xfer),
      .d1_CPU0_memory_s1_end_xfer                                       (d1_CPU0_memory_s1_end_xfer),
      .reset_n                                                          (clk_50_reset_n)
    );

  CPU0 the_CPU0
    (
      .clk                                   (clk_50),
      .d_address                             (CPU0_data_master_address),
      .d_byteenable                          (CPU0_data_master_byteenable),
      .d_irq                                 (CPU0_data_master_irq),
      .d_read                                (CPU0_data_master_read),
      .d_readdata                            (CPU0_data_master_readdata),
      .d_readdatavalid                       (CPU0_data_master_readdatavalid),
      .d_waitrequest                         (CPU0_data_master_waitrequest),
      .d_write                               (CPU0_data_master_write),
      .d_writedata                           (CPU0_data_master_writedata),
      .i_address                             (CPU0_instruction_master_address),
      .i_read                                (CPU0_instruction_master_read),
      .i_readdata                            (CPU0_instruction_master_readdata),
      .i_readdatavalid                       (CPU0_instruction_master_readdatavalid),
      .i_waitrequest                         (CPU0_instruction_master_waitrequest),
      .jtag_debug_module_address             (CPU0_jtag_debug_module_address),
      .jtag_debug_module_begintransfer       (CPU0_jtag_debug_module_begintransfer),
      .jtag_debug_module_byteenable          (CPU0_jtag_debug_module_byteenable),
      .jtag_debug_module_debugaccess         (CPU0_jtag_debug_module_debugaccess),
      .jtag_debug_module_debugaccess_to_roms (CPU0_data_master_debugaccess),
      .jtag_debug_module_readdata            (CPU0_jtag_debug_module_readdata),
      .jtag_debug_module_resetrequest        (CPU0_jtag_debug_module_resetrequest),
      .jtag_debug_module_select              (CPU0_jtag_debug_module_chipselect),
      .jtag_debug_module_write               (CPU0_jtag_debug_module_write),
      .jtag_debug_module_writedata           (CPU0_jtag_debug_module_writedata),
      .reset_n                               (CPU0_jtag_debug_module_reset_n)
    );

  CPU0_JTAG_UART_avalon_jtag_slave_arbitrator the_CPU0_JTAG_UART_avalon_jtag_slave
    (
      .CPU0_JTAG_UART_avalon_jtag_slave_address                            (CPU0_JTAG_UART_avalon_jtag_slave_address),
      .CPU0_JTAG_UART_avalon_jtag_slave_chipselect                         (CPU0_JTAG_UART_avalon_jtag_slave_chipselect),
      .CPU0_JTAG_UART_avalon_jtag_slave_dataavailable                      (CPU0_JTAG_UART_avalon_jtag_slave_dataavailable),
      .CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa              (CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa),
      .CPU0_JTAG_UART_avalon_jtag_slave_irq                                (CPU0_JTAG_UART_avalon_jtag_slave_irq),
      .CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa                        (CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa),
      .CPU0_JTAG_UART_avalon_jtag_slave_read_n                             (CPU0_JTAG_UART_avalon_jtag_slave_read_n),
      .CPU0_JTAG_UART_avalon_jtag_slave_readdata                           (CPU0_JTAG_UART_avalon_jtag_slave_readdata),
      .CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa                   (CPU0_JTAG_UART_avalon_jtag_slave_readdata_from_sa),
      .CPU0_JTAG_UART_avalon_jtag_slave_readyfordata                       (CPU0_JTAG_UART_avalon_jtag_slave_readyfordata),
      .CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa               (CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa),
      .CPU0_JTAG_UART_avalon_jtag_slave_reset_n                            (CPU0_JTAG_UART_avalon_jtag_slave_reset_n),
      .CPU0_JTAG_UART_avalon_jtag_slave_waitrequest                        (CPU0_JTAG_UART_avalon_jtag_slave_waitrequest),
      .CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa                (CPU0_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa),
      .CPU0_JTAG_UART_avalon_jtag_slave_write_n                            (CPU0_JTAG_UART_avalon_jtag_slave_write_n),
      .CPU0_JTAG_UART_avalon_jtag_slave_writedata                          (CPU0_JTAG_UART_avalon_jtag_slave_writedata),
      .CPU0_data_master_address_to_slave                                   (CPU0_data_master_address_to_slave),
      .CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave           (CPU0_data_master_granted_CPU0_JTAG_UART_avalon_jtag_slave),
      .CPU0_data_master_latency_counter                                    (CPU0_data_master_latency_counter),
      .CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave (CPU0_data_master_qualified_request_CPU0_JTAG_UART_avalon_jtag_slave),
      .CPU0_data_master_read                                               (CPU0_data_master_read),
      .CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave   (CPU0_data_master_read_data_valid_CPU0_JTAG_UART_avalon_jtag_slave),
      .CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave          (CPU0_data_master_requests_CPU0_JTAG_UART_avalon_jtag_slave),
      .CPU0_data_master_write                                              (CPU0_data_master_write),
      .CPU0_data_master_writedata                                          (CPU0_data_master_writedata),
      .clk                                                                 (clk_50),
      .d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer                        (d1_CPU0_JTAG_UART_avalon_jtag_slave_end_xfer),
      .reset_n                                                             (clk_50_reset_n)
    );

  CPU0_JTAG_UART the_CPU0_JTAG_UART
    (
      .av_address     (CPU0_JTAG_UART_avalon_jtag_slave_address),
      .av_chipselect  (CPU0_JTAG_UART_avalon_jtag_slave_chipselect),
      .av_irq         (CPU0_JTAG_UART_avalon_jtag_slave_irq),
      .av_read_n      (CPU0_JTAG_UART_avalon_jtag_slave_read_n),
      .av_readdata    (CPU0_JTAG_UART_avalon_jtag_slave_readdata),
      .av_waitrequest (CPU0_JTAG_UART_avalon_jtag_slave_waitrequest),
      .av_write_n     (CPU0_JTAG_UART_avalon_jtag_slave_write_n),
      .av_writedata   (CPU0_JTAG_UART_avalon_jtag_slave_writedata),
      .clk            (clk_50),
      .dataavailable  (CPU0_JTAG_UART_avalon_jtag_slave_dataavailable),
      .readyfordata   (CPU0_JTAG_UART_avalon_jtag_slave_readyfordata),
      .rst_n          (CPU0_JTAG_UART_avalon_jtag_slave_reset_n)
    );

  CPU0_memory_s1_arbitrator the_CPU0_memory_s1
    (
      .CPU0_data_master_address_to_slave                        (CPU0_data_master_address_to_slave),
      .CPU0_data_master_byteenable                              (CPU0_data_master_byteenable),
      .CPU0_data_master_granted_CPU0_memory_s1                  (CPU0_data_master_granted_CPU0_memory_s1),
      .CPU0_data_master_latency_counter                         (CPU0_data_master_latency_counter),
      .CPU0_data_master_qualified_request_CPU0_memory_s1        (CPU0_data_master_qualified_request_CPU0_memory_s1),
      .CPU0_data_master_read                                    (CPU0_data_master_read),
      .CPU0_data_master_read_data_valid_CPU0_memory_s1          (CPU0_data_master_read_data_valid_CPU0_memory_s1),
      .CPU0_data_master_requests_CPU0_memory_s1                 (CPU0_data_master_requests_CPU0_memory_s1),
      .CPU0_data_master_write                                   (CPU0_data_master_write),
      .CPU0_data_master_writedata                               (CPU0_data_master_writedata),
      .CPU0_instruction_master_address_to_slave                 (CPU0_instruction_master_address_to_slave),
      .CPU0_instruction_master_granted_CPU0_memory_s1           (CPU0_instruction_master_granted_CPU0_memory_s1),
      .CPU0_instruction_master_latency_counter                  (CPU0_instruction_master_latency_counter),
      .CPU0_instruction_master_qualified_request_CPU0_memory_s1 (CPU0_instruction_master_qualified_request_CPU0_memory_s1),
      .CPU0_instruction_master_read                             (CPU0_instruction_master_read),
      .CPU0_instruction_master_read_data_valid_CPU0_memory_s1   (CPU0_instruction_master_read_data_valid_CPU0_memory_s1),
      .CPU0_instruction_master_requests_CPU0_memory_s1          (CPU0_instruction_master_requests_CPU0_memory_s1),
      .CPU0_memory_s1_address                                   (CPU0_memory_s1_address),
      .CPU0_memory_s1_byteenable                                (CPU0_memory_s1_byteenable),
      .CPU0_memory_s1_chipselect                                (CPU0_memory_s1_chipselect),
      .CPU0_memory_s1_clken                                     (CPU0_memory_s1_clken),
      .CPU0_memory_s1_readdata                                  (CPU0_memory_s1_readdata),
      .CPU0_memory_s1_readdata_from_sa                          (CPU0_memory_s1_readdata_from_sa),
      .CPU0_memory_s1_reset                                     (CPU0_memory_s1_reset),
      .CPU0_memory_s1_write                                     (CPU0_memory_s1_write),
      .CPU0_memory_s1_writedata                                 (CPU0_memory_s1_writedata),
      .clk                                                      (clk_50),
      .d1_CPU0_memory_s1_end_xfer                               (d1_CPU0_memory_s1_end_xfer),
      .reset_n                                                  (clk_50_reset_n)
    );

  CPU0_memory the_CPU0_memory
    (
      .address    (CPU0_memory_s1_address),
      .byteenable (CPU0_memory_s1_byteenable),
      .chipselect (CPU0_memory_s1_chipselect),
      .clk        (clk_50),
      .clken      (CPU0_memory_s1_clken),
      .readdata   (CPU0_memory_s1_readdata),
      .reset      (CPU0_memory_s1_reset),
      .write      (CPU0_memory_s1_write),
      .writedata  (CPU0_memory_s1_writedata)
    );

  CPU1_jtag_debug_module_arbitrator the_CPU1_jtag_debug_module
    (
      .CPU1_data_master_address_to_slave                                (CPU1_data_master_address_to_slave),
      .CPU1_data_master_byteenable                                      (CPU1_data_master_byteenable),
      .CPU1_data_master_debugaccess                                     (CPU1_data_master_debugaccess),
      .CPU1_data_master_granted_CPU1_jtag_debug_module                  (CPU1_data_master_granted_CPU1_jtag_debug_module),
      .CPU1_data_master_latency_counter                                 (CPU1_data_master_latency_counter),
      .CPU1_data_master_qualified_request_CPU1_jtag_debug_module        (CPU1_data_master_qualified_request_CPU1_jtag_debug_module),
      .CPU1_data_master_read                                            (CPU1_data_master_read),
      .CPU1_data_master_read_data_valid_CPU1_jtag_debug_module          (CPU1_data_master_read_data_valid_CPU1_jtag_debug_module),
      .CPU1_data_master_requests_CPU1_jtag_debug_module                 (CPU1_data_master_requests_CPU1_jtag_debug_module),
      .CPU1_data_master_write                                           (CPU1_data_master_write),
      .CPU1_data_master_writedata                                       (CPU1_data_master_writedata),
      .CPU1_instruction_master_address_to_slave                         (CPU1_instruction_master_address_to_slave),
      .CPU1_instruction_master_granted_CPU1_jtag_debug_module           (CPU1_instruction_master_granted_CPU1_jtag_debug_module),
      .CPU1_instruction_master_latency_counter                          (CPU1_instruction_master_latency_counter),
      .CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module (CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module),
      .CPU1_instruction_master_read                                     (CPU1_instruction_master_read),
      .CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module   (CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module),
      .CPU1_instruction_master_requests_CPU1_jtag_debug_module          (CPU1_instruction_master_requests_CPU1_jtag_debug_module),
      .CPU1_jtag_debug_module_address                                   (CPU1_jtag_debug_module_address),
      .CPU1_jtag_debug_module_begintransfer                             (CPU1_jtag_debug_module_begintransfer),
      .CPU1_jtag_debug_module_byteenable                                (CPU1_jtag_debug_module_byteenable),
      .CPU1_jtag_debug_module_chipselect                                (CPU1_jtag_debug_module_chipselect),
      .CPU1_jtag_debug_module_debugaccess                               (CPU1_jtag_debug_module_debugaccess),
      .CPU1_jtag_debug_module_readdata                                  (CPU1_jtag_debug_module_readdata),
      .CPU1_jtag_debug_module_readdata_from_sa                          (CPU1_jtag_debug_module_readdata_from_sa),
      .CPU1_jtag_debug_module_reset_n                                   (CPU1_jtag_debug_module_reset_n),
      .CPU1_jtag_debug_module_resetrequest                              (CPU1_jtag_debug_module_resetrequest),
      .CPU1_jtag_debug_module_resetrequest_from_sa                      (CPU1_jtag_debug_module_resetrequest_from_sa),
      .CPU1_jtag_debug_module_write                                     (CPU1_jtag_debug_module_write),
      .CPU1_jtag_debug_module_writedata                                 (CPU1_jtag_debug_module_writedata),
      .clk                                                              (clk_50),
      .d1_CPU1_jtag_debug_module_end_xfer                               (d1_CPU1_jtag_debug_module_end_xfer),
      .reset_n                                                          (clk_50_reset_n)
    );

  CPU1_data_master_arbitrator the_CPU1_data_master
    (
      .CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa                        (CPU0_JTAG_UART_avalon_jtag_slave_irq_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa                        (CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa                   (CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa                (CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa),
      .CPU1_data_master_address                                            (CPU1_data_master_address),
      .CPU1_data_master_address_to_slave                                   (CPU1_data_master_address_to_slave),
      .CPU1_data_master_byteenable                                         (CPU1_data_master_byteenable),
      .CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave           (CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave),
      .CPU1_data_master_granted_CPU1_jtag_debug_module                     (CPU1_data_master_granted_CPU1_jtag_debug_module),
      .CPU1_data_master_granted_CPU1_memory_s1                             (CPU1_data_master_granted_CPU1_memory_s1),
      .CPU1_data_master_granted_Comms_memory_s1                            (CPU1_data_master_granted_Comms_memory_s1),
      .CPU1_data_master_granted_Comms_mutex_rx_s1                          (CPU1_data_master_granted_Comms_mutex_rx_s1),
      .CPU1_data_master_granted_Comms_mutex_tx_s1                          (CPU1_data_master_granted_Comms_mutex_tx_s1),
      .CPU1_data_master_granted_pio_LED_s1                                 (CPU1_data_master_granted_pio_LED_s1),
      .CPU1_data_master_irq                                                (CPU1_data_master_irq),
      .CPU1_data_master_latency_counter                                    (CPU1_data_master_latency_counter),
      .CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave (CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave),
      .CPU1_data_master_qualified_request_CPU1_jtag_debug_module           (CPU1_data_master_qualified_request_CPU1_jtag_debug_module),
      .CPU1_data_master_qualified_request_CPU1_memory_s1                   (CPU1_data_master_qualified_request_CPU1_memory_s1),
      .CPU1_data_master_qualified_request_Comms_memory_s1                  (CPU1_data_master_qualified_request_Comms_memory_s1),
      .CPU1_data_master_qualified_request_Comms_mutex_rx_s1                (CPU1_data_master_qualified_request_Comms_mutex_rx_s1),
      .CPU1_data_master_qualified_request_Comms_mutex_tx_s1                (CPU1_data_master_qualified_request_Comms_mutex_tx_s1),
      .CPU1_data_master_qualified_request_pio_LED_s1                       (CPU1_data_master_qualified_request_pio_LED_s1),
      .CPU1_data_master_read                                               (CPU1_data_master_read),
      .CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave   (CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave),
      .CPU1_data_master_read_data_valid_CPU1_jtag_debug_module             (CPU1_data_master_read_data_valid_CPU1_jtag_debug_module),
      .CPU1_data_master_read_data_valid_CPU1_memory_s1                     (CPU1_data_master_read_data_valid_CPU1_memory_s1),
      .CPU1_data_master_read_data_valid_Comms_memory_s1                    (CPU1_data_master_read_data_valid_Comms_memory_s1),
      .CPU1_data_master_read_data_valid_Comms_mutex_rx_s1                  (CPU1_data_master_read_data_valid_Comms_mutex_rx_s1),
      .CPU1_data_master_read_data_valid_Comms_mutex_tx_s1                  (CPU1_data_master_read_data_valid_Comms_mutex_tx_s1),
      .CPU1_data_master_read_data_valid_pio_LED_s1                         (CPU1_data_master_read_data_valid_pio_LED_s1),
      .CPU1_data_master_readdata                                           (CPU1_data_master_readdata),
      .CPU1_data_master_readdatavalid                                      (CPU1_data_master_readdatavalid),
      .CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave          (CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave),
      .CPU1_data_master_requests_CPU1_jtag_debug_module                    (CPU1_data_master_requests_CPU1_jtag_debug_module),
      .CPU1_data_master_requests_CPU1_memory_s1                            (CPU1_data_master_requests_CPU1_memory_s1),
      .CPU1_data_master_requests_Comms_memory_s1                           (CPU1_data_master_requests_Comms_memory_s1),
      .CPU1_data_master_requests_Comms_mutex_rx_s1                         (CPU1_data_master_requests_Comms_mutex_rx_s1),
      .CPU1_data_master_requests_Comms_mutex_tx_s1                         (CPU1_data_master_requests_Comms_mutex_tx_s1),
      .CPU1_data_master_requests_pio_LED_s1                                (CPU1_data_master_requests_pio_LED_s1),
      .CPU1_data_master_waitrequest                                        (CPU1_data_master_waitrequest),
      .CPU1_data_master_write                                              (CPU1_data_master_write),
      .CPU1_data_master_writedata                                          (CPU1_data_master_writedata),
      .CPU1_jtag_debug_module_readdata_from_sa                             (CPU1_jtag_debug_module_readdata_from_sa),
      .CPU1_memory_s1_readdata_from_sa                                     (CPU1_memory_s1_readdata_from_sa),
      .Comms_memory_s1_readdata_from_sa                                    (Comms_memory_s1_readdata_from_sa),
      .Comms_mutex_rx_s1_readdata_from_sa                                  (Comms_mutex_rx_s1_readdata_from_sa),
      .Comms_mutex_tx_s1_readdata_from_sa                                  (Comms_mutex_tx_s1_readdata_from_sa),
      .clk                                                                 (clk_50),
      .d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer                        (d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer),
      .d1_CPU1_jtag_debug_module_end_xfer                                  (d1_CPU1_jtag_debug_module_end_xfer),
      .d1_CPU1_memory_s1_end_xfer                                          (d1_CPU1_memory_s1_end_xfer),
      .d1_Comms_memory_s1_end_xfer                                         (d1_Comms_memory_s1_end_xfer),
      .d1_Comms_mutex_rx_s1_end_xfer                                       (d1_Comms_mutex_rx_s1_end_xfer),
      .d1_Comms_mutex_tx_s1_end_xfer                                       (d1_Comms_mutex_tx_s1_end_xfer),
      .d1_pio_LED_s1_end_xfer                                              (d1_pio_LED_s1_end_xfer),
      .pio_LED_s1_readdata_from_sa                                         (pio_LED_s1_readdata_from_sa),
      .reset_n                                                             (clk_50_reset_n)
    );

  CPU1_instruction_master_arbitrator the_CPU1_instruction_master
    (
      .CPU1_instruction_master_address                                  (CPU1_instruction_master_address),
      .CPU1_instruction_master_address_to_slave                         (CPU1_instruction_master_address_to_slave),
      .CPU1_instruction_master_granted_CPU1_jtag_debug_module           (CPU1_instruction_master_granted_CPU1_jtag_debug_module),
      .CPU1_instruction_master_granted_CPU1_memory_s1                   (CPU1_instruction_master_granted_CPU1_memory_s1),
      .CPU1_instruction_master_latency_counter                          (CPU1_instruction_master_latency_counter),
      .CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module (CPU1_instruction_master_qualified_request_CPU1_jtag_debug_module),
      .CPU1_instruction_master_qualified_request_CPU1_memory_s1         (CPU1_instruction_master_qualified_request_CPU1_memory_s1),
      .CPU1_instruction_master_read                                     (CPU1_instruction_master_read),
      .CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module   (CPU1_instruction_master_read_data_valid_CPU1_jtag_debug_module),
      .CPU1_instruction_master_read_data_valid_CPU1_memory_s1           (CPU1_instruction_master_read_data_valid_CPU1_memory_s1),
      .CPU1_instruction_master_readdata                                 (CPU1_instruction_master_readdata),
      .CPU1_instruction_master_readdatavalid                            (CPU1_instruction_master_readdatavalid),
      .CPU1_instruction_master_requests_CPU1_jtag_debug_module          (CPU1_instruction_master_requests_CPU1_jtag_debug_module),
      .CPU1_instruction_master_requests_CPU1_memory_s1                  (CPU1_instruction_master_requests_CPU1_memory_s1),
      .CPU1_instruction_master_waitrequest                              (CPU1_instruction_master_waitrequest),
      .CPU1_jtag_debug_module_readdata_from_sa                          (CPU1_jtag_debug_module_readdata_from_sa),
      .CPU1_memory_s1_readdata_from_sa                                  (CPU1_memory_s1_readdata_from_sa),
      .clk                                                              (clk_50),
      .d1_CPU1_jtag_debug_module_end_xfer                               (d1_CPU1_jtag_debug_module_end_xfer),
      .d1_CPU1_memory_s1_end_xfer                                       (d1_CPU1_memory_s1_end_xfer),
      .reset_n                                                          (clk_50_reset_n)
    );

  CPU1 the_CPU1
    (
      .clk                                   (clk_50),
      .d_address                             (CPU1_data_master_address),
      .d_byteenable                          (CPU1_data_master_byteenable),
      .d_irq                                 (CPU1_data_master_irq),
      .d_read                                (CPU1_data_master_read),
      .d_readdata                            (CPU1_data_master_readdata),
      .d_readdatavalid                       (CPU1_data_master_readdatavalid),
      .d_waitrequest                         (CPU1_data_master_waitrequest),
      .d_write                               (CPU1_data_master_write),
      .d_writedata                           (CPU1_data_master_writedata),
      .i_address                             (CPU1_instruction_master_address),
      .i_read                                (CPU1_instruction_master_read),
      .i_readdata                            (CPU1_instruction_master_readdata),
      .i_readdatavalid                       (CPU1_instruction_master_readdatavalid),
      .i_waitrequest                         (CPU1_instruction_master_waitrequest),
      .jtag_debug_module_address             (CPU1_jtag_debug_module_address),
      .jtag_debug_module_begintransfer       (CPU1_jtag_debug_module_begintransfer),
      .jtag_debug_module_byteenable          (CPU1_jtag_debug_module_byteenable),
      .jtag_debug_module_debugaccess         (CPU1_jtag_debug_module_debugaccess),
      .jtag_debug_module_debugaccess_to_roms (CPU1_data_master_debugaccess),
      .jtag_debug_module_readdata            (CPU1_jtag_debug_module_readdata),
      .jtag_debug_module_resetrequest        (CPU1_jtag_debug_module_resetrequest),
      .jtag_debug_module_select              (CPU1_jtag_debug_module_chipselect),
      .jtag_debug_module_write               (CPU1_jtag_debug_module_write),
      .jtag_debug_module_writedata           (CPU1_jtag_debug_module_writedata),
      .reset_n                               (CPU1_jtag_debug_module_reset_n)
    );

  CPU1_JTAG_UART_avalon_jtag_slave_arbitrator the_CPU1_JTAG_UART_avalon_jtag_slave
    (
      .CPU1_JTAG_UART_avalon_jtag_slave_address                            (CPU1_JTAG_UART_avalon_jtag_slave_address),
      .CPU1_JTAG_UART_avalon_jtag_slave_chipselect                         (CPU1_JTAG_UART_avalon_jtag_slave_chipselect),
      .CPU1_JTAG_UART_avalon_jtag_slave_dataavailable                      (CPU1_JTAG_UART_avalon_jtag_slave_dataavailable),
      .CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa              (CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_irq                                (CPU1_JTAG_UART_avalon_jtag_slave_irq),
      .CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa                        (CPU1_JTAG_UART_avalon_jtag_slave_irq_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_read_n                             (CPU1_JTAG_UART_avalon_jtag_slave_read_n),
      .CPU1_JTAG_UART_avalon_jtag_slave_readdata                           (CPU1_JTAG_UART_avalon_jtag_slave_readdata),
      .CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa                   (CPU1_JTAG_UART_avalon_jtag_slave_readdata_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_readyfordata                       (CPU1_JTAG_UART_avalon_jtag_slave_readyfordata),
      .CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa               (CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_reset_n                            (CPU1_JTAG_UART_avalon_jtag_slave_reset_n),
      .CPU1_JTAG_UART_avalon_jtag_slave_waitrequest                        (CPU1_JTAG_UART_avalon_jtag_slave_waitrequest),
      .CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa                (CPU1_JTAG_UART_avalon_jtag_slave_waitrequest_from_sa),
      .CPU1_JTAG_UART_avalon_jtag_slave_write_n                            (CPU1_JTAG_UART_avalon_jtag_slave_write_n),
      .CPU1_JTAG_UART_avalon_jtag_slave_writedata                          (CPU1_JTAG_UART_avalon_jtag_slave_writedata),
      .CPU1_data_master_address_to_slave                                   (CPU1_data_master_address_to_slave),
      .CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave           (CPU1_data_master_granted_CPU1_JTAG_UART_avalon_jtag_slave),
      .CPU1_data_master_latency_counter                                    (CPU1_data_master_latency_counter),
      .CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave (CPU1_data_master_qualified_request_CPU1_JTAG_UART_avalon_jtag_slave),
      .CPU1_data_master_read                                               (CPU1_data_master_read),
      .CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave   (CPU1_data_master_read_data_valid_CPU1_JTAG_UART_avalon_jtag_slave),
      .CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave          (CPU1_data_master_requests_CPU1_JTAG_UART_avalon_jtag_slave),
      .CPU1_data_master_write                                              (CPU1_data_master_write),
      .CPU1_data_master_writedata                                          (CPU1_data_master_writedata),
      .clk                                                                 (clk_50),
      .d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer                        (d1_CPU1_JTAG_UART_avalon_jtag_slave_end_xfer),
      .reset_n                                                             (clk_50_reset_n)
    );

  CPU1_JTAG_UART the_CPU1_JTAG_UART
    (
      .av_address     (CPU1_JTAG_UART_avalon_jtag_slave_address),
      .av_chipselect  (CPU1_JTAG_UART_avalon_jtag_slave_chipselect),
      .av_irq         (CPU1_JTAG_UART_avalon_jtag_slave_irq),
      .av_read_n      (CPU1_JTAG_UART_avalon_jtag_slave_read_n),
      .av_readdata    (CPU1_JTAG_UART_avalon_jtag_slave_readdata),
      .av_waitrequest (CPU1_JTAG_UART_avalon_jtag_slave_waitrequest),
      .av_write_n     (CPU1_JTAG_UART_avalon_jtag_slave_write_n),
      .av_writedata   (CPU1_JTAG_UART_avalon_jtag_slave_writedata),
      .clk            (clk_50),
      .dataavailable  (CPU1_JTAG_UART_avalon_jtag_slave_dataavailable),
      .readyfordata   (CPU1_JTAG_UART_avalon_jtag_slave_readyfordata),
      .rst_n          (CPU1_JTAG_UART_avalon_jtag_slave_reset_n)
    );

  CPU1_memory_s1_arbitrator the_CPU1_memory_s1
    (
      .CPU1_data_master_address_to_slave                        (CPU1_data_master_address_to_slave),
      .CPU1_data_master_byteenable                              (CPU1_data_master_byteenable),
      .CPU1_data_master_granted_CPU1_memory_s1                  (CPU1_data_master_granted_CPU1_memory_s1),
      .CPU1_data_master_latency_counter                         (CPU1_data_master_latency_counter),
      .CPU1_data_master_qualified_request_CPU1_memory_s1        (CPU1_data_master_qualified_request_CPU1_memory_s1),
      .CPU1_data_master_read                                    (CPU1_data_master_read),
      .CPU1_data_master_read_data_valid_CPU1_memory_s1          (CPU1_data_master_read_data_valid_CPU1_memory_s1),
      .CPU1_data_master_requests_CPU1_memory_s1                 (CPU1_data_master_requests_CPU1_memory_s1),
      .CPU1_data_master_write                                   (CPU1_data_master_write),
      .CPU1_data_master_writedata                               (CPU1_data_master_writedata),
      .CPU1_instruction_master_address_to_slave                 (CPU1_instruction_master_address_to_slave),
      .CPU1_instruction_master_granted_CPU1_memory_s1           (CPU1_instruction_master_granted_CPU1_memory_s1),
      .CPU1_instruction_master_latency_counter                  (CPU1_instruction_master_latency_counter),
      .CPU1_instruction_master_qualified_request_CPU1_memory_s1 (CPU1_instruction_master_qualified_request_CPU1_memory_s1),
      .CPU1_instruction_master_read                             (CPU1_instruction_master_read),
      .CPU1_instruction_master_read_data_valid_CPU1_memory_s1   (CPU1_instruction_master_read_data_valid_CPU1_memory_s1),
      .CPU1_instruction_master_requests_CPU1_memory_s1          (CPU1_instruction_master_requests_CPU1_memory_s1),
      .CPU1_memory_s1_address                                   (CPU1_memory_s1_address),
      .CPU1_memory_s1_byteenable                                (CPU1_memory_s1_byteenable),
      .CPU1_memory_s1_chipselect                                (CPU1_memory_s1_chipselect),
      .CPU1_memory_s1_clken                                     (CPU1_memory_s1_clken),
      .CPU1_memory_s1_readdata                                  (CPU1_memory_s1_readdata),
      .CPU1_memory_s1_readdata_from_sa                          (CPU1_memory_s1_readdata_from_sa),
      .CPU1_memory_s1_reset                                     (CPU1_memory_s1_reset),
      .CPU1_memory_s1_write                                     (CPU1_memory_s1_write),
      .CPU1_memory_s1_writedata                                 (CPU1_memory_s1_writedata),
      .clk                                                      (clk_50),
      .d1_CPU1_memory_s1_end_xfer                               (d1_CPU1_memory_s1_end_xfer),
      .reset_n                                                  (clk_50_reset_n)
    );

  CPU1_memory the_CPU1_memory
    (
      .address    (CPU1_memory_s1_address),
      .byteenable (CPU1_memory_s1_byteenable),
      .chipselect (CPU1_memory_s1_chipselect),
      .clk        (clk_50),
      .clken      (CPU1_memory_s1_clken),
      .readdata   (CPU1_memory_s1_readdata),
      .reset      (CPU1_memory_s1_reset),
      .write      (CPU1_memory_s1_write),
      .writedata  (CPU1_memory_s1_writedata)
    );

  Comms_memory_s1_arbitrator the_Comms_memory_s1
    (
      .CPU0_data_master_address_to_slave                  (CPU0_data_master_address_to_slave),
      .CPU0_data_master_byteenable                        (CPU0_data_master_byteenable),
      .CPU0_data_master_granted_Comms_memory_s1           (CPU0_data_master_granted_Comms_memory_s1),
      .CPU0_data_master_latency_counter                   (CPU0_data_master_latency_counter),
      .CPU0_data_master_qualified_request_Comms_memory_s1 (CPU0_data_master_qualified_request_Comms_memory_s1),
      .CPU0_data_master_read                              (CPU0_data_master_read),
      .CPU0_data_master_read_data_valid_Comms_memory_s1   (CPU0_data_master_read_data_valid_Comms_memory_s1),
      .CPU0_data_master_requests_Comms_memory_s1          (CPU0_data_master_requests_Comms_memory_s1),
      .CPU0_data_master_write                             (CPU0_data_master_write),
      .CPU0_data_master_writedata                         (CPU0_data_master_writedata),
      .CPU1_data_master_address_to_slave                  (CPU1_data_master_address_to_slave),
      .CPU1_data_master_byteenable                        (CPU1_data_master_byteenable),
      .CPU1_data_master_granted_Comms_memory_s1           (CPU1_data_master_granted_Comms_memory_s1),
      .CPU1_data_master_latency_counter                   (CPU1_data_master_latency_counter),
      .CPU1_data_master_qualified_request_Comms_memory_s1 (CPU1_data_master_qualified_request_Comms_memory_s1),
      .CPU1_data_master_read                              (CPU1_data_master_read),
      .CPU1_data_master_read_data_valid_Comms_memory_s1   (CPU1_data_master_read_data_valid_Comms_memory_s1),
      .CPU1_data_master_requests_Comms_memory_s1          (CPU1_data_master_requests_Comms_memory_s1),
      .CPU1_data_master_write                             (CPU1_data_master_write),
      .CPU1_data_master_writedata                         (CPU1_data_master_writedata),
      .Comms_memory_s1_address                            (Comms_memory_s1_address),
      .Comms_memory_s1_byteenable                         (Comms_memory_s1_byteenable),
      .Comms_memory_s1_chipselect                         (Comms_memory_s1_chipselect),
      .Comms_memory_s1_clken                              (Comms_memory_s1_clken),
      .Comms_memory_s1_readdata                           (Comms_memory_s1_readdata),
      .Comms_memory_s1_readdata_from_sa                   (Comms_memory_s1_readdata_from_sa),
      .Comms_memory_s1_reset                              (Comms_memory_s1_reset),
      .Comms_memory_s1_write                              (Comms_memory_s1_write),
      .Comms_memory_s1_writedata                          (Comms_memory_s1_writedata),
      .clk                                                (clk_50),
      .d1_Comms_memory_s1_end_xfer                        (d1_Comms_memory_s1_end_xfer),
      .reset_n                                            (clk_50_reset_n)
    );

  Comms_memory the_Comms_memory
    (
      .address    (Comms_memory_s1_address),
      .byteenable (Comms_memory_s1_byteenable),
      .chipselect (Comms_memory_s1_chipselect),
      .clk        (clk_50),
      .clken      (Comms_memory_s1_clken),
      .readdata   (Comms_memory_s1_readdata),
      .reset      (Comms_memory_s1_reset),
      .write      (Comms_memory_s1_write),
      .writedata  (Comms_memory_s1_writedata)
    );

  Comms_mutex_rx_s1_arbitrator the_Comms_mutex_rx_s1
    (
      .CPU0_data_master_address_to_slave                    (CPU0_data_master_address_to_slave),
      .CPU0_data_master_granted_Comms_mutex_rx_s1           (CPU0_data_master_granted_Comms_mutex_rx_s1),
      .CPU0_data_master_latency_counter                     (CPU0_data_master_latency_counter),
      .CPU0_data_master_qualified_request_Comms_mutex_rx_s1 (CPU0_data_master_qualified_request_Comms_mutex_rx_s1),
      .CPU0_data_master_read                                (CPU0_data_master_read),
      .CPU0_data_master_read_data_valid_Comms_mutex_rx_s1   (CPU0_data_master_read_data_valid_Comms_mutex_rx_s1),
      .CPU0_data_master_requests_Comms_mutex_rx_s1          (CPU0_data_master_requests_Comms_mutex_rx_s1),
      .CPU0_data_master_write                               (CPU0_data_master_write),
      .CPU0_data_master_writedata                           (CPU0_data_master_writedata),
      .CPU1_data_master_address_to_slave                    (CPU1_data_master_address_to_slave),
      .CPU1_data_master_granted_Comms_mutex_rx_s1           (CPU1_data_master_granted_Comms_mutex_rx_s1),
      .CPU1_data_master_latency_counter                     (CPU1_data_master_latency_counter),
      .CPU1_data_master_qualified_request_Comms_mutex_rx_s1 (CPU1_data_master_qualified_request_Comms_mutex_rx_s1),
      .CPU1_data_master_read                                (CPU1_data_master_read),
      .CPU1_data_master_read_data_valid_Comms_mutex_rx_s1   (CPU1_data_master_read_data_valid_Comms_mutex_rx_s1),
      .CPU1_data_master_requests_Comms_mutex_rx_s1          (CPU1_data_master_requests_Comms_mutex_rx_s1),
      .CPU1_data_master_write                               (CPU1_data_master_write),
      .CPU1_data_master_writedata                           (CPU1_data_master_writedata),
      .Comms_mutex_rx_s1_address                            (Comms_mutex_rx_s1_address),
      .Comms_mutex_rx_s1_chipselect                         (Comms_mutex_rx_s1_chipselect),
      .Comms_mutex_rx_s1_read                               (Comms_mutex_rx_s1_read),
      .Comms_mutex_rx_s1_readdata                           (Comms_mutex_rx_s1_readdata),
      .Comms_mutex_rx_s1_readdata_from_sa                   (Comms_mutex_rx_s1_readdata_from_sa),
      .Comms_mutex_rx_s1_reset_n                            (Comms_mutex_rx_s1_reset_n),
      .Comms_mutex_rx_s1_write                              (Comms_mutex_rx_s1_write),
      .Comms_mutex_rx_s1_writedata                          (Comms_mutex_rx_s1_writedata),
      .clk                                                  (clk_50),
      .d1_Comms_mutex_rx_s1_end_xfer                        (d1_Comms_mutex_rx_s1_end_xfer),
      .reset_n                                              (clk_50_reset_n)
    );

  Comms_mutex_rx the_Comms_mutex_rx
    (
      .address       (Comms_mutex_rx_s1_address),
      .chipselect    (Comms_mutex_rx_s1_chipselect),
      .clk           (clk_50),
      .data_from_cpu (Comms_mutex_rx_s1_writedata),
      .data_to_cpu   (Comms_mutex_rx_s1_readdata),
      .read          (Comms_mutex_rx_s1_read),
      .reset_n       (Comms_mutex_rx_s1_reset_n),
      .write         (Comms_mutex_rx_s1_write)
    );

  Comms_mutex_tx_s1_arbitrator the_Comms_mutex_tx_s1
    (
      .CPU0_data_master_address_to_slave                    (CPU0_data_master_address_to_slave),
      .CPU0_data_master_granted_Comms_mutex_tx_s1           (CPU0_data_master_granted_Comms_mutex_tx_s1),
      .CPU0_data_master_latency_counter                     (CPU0_data_master_latency_counter),
      .CPU0_data_master_qualified_request_Comms_mutex_tx_s1 (CPU0_data_master_qualified_request_Comms_mutex_tx_s1),
      .CPU0_data_master_read                                (CPU0_data_master_read),
      .CPU0_data_master_read_data_valid_Comms_mutex_tx_s1   (CPU0_data_master_read_data_valid_Comms_mutex_tx_s1),
      .CPU0_data_master_requests_Comms_mutex_tx_s1          (CPU0_data_master_requests_Comms_mutex_tx_s1),
      .CPU0_data_master_write                               (CPU0_data_master_write),
      .CPU0_data_master_writedata                           (CPU0_data_master_writedata),
      .CPU1_data_master_address_to_slave                    (CPU1_data_master_address_to_slave),
      .CPU1_data_master_granted_Comms_mutex_tx_s1           (CPU1_data_master_granted_Comms_mutex_tx_s1),
      .CPU1_data_master_latency_counter                     (CPU1_data_master_latency_counter),
      .CPU1_data_master_qualified_request_Comms_mutex_tx_s1 (CPU1_data_master_qualified_request_Comms_mutex_tx_s1),
      .CPU1_data_master_read                                (CPU1_data_master_read),
      .CPU1_data_master_read_data_valid_Comms_mutex_tx_s1   (CPU1_data_master_read_data_valid_Comms_mutex_tx_s1),
      .CPU1_data_master_requests_Comms_mutex_tx_s1          (CPU1_data_master_requests_Comms_mutex_tx_s1),
      .CPU1_data_master_write                               (CPU1_data_master_write),
      .CPU1_data_master_writedata                           (CPU1_data_master_writedata),
      .Comms_mutex_tx_s1_address                            (Comms_mutex_tx_s1_address),
      .Comms_mutex_tx_s1_chipselect                         (Comms_mutex_tx_s1_chipselect),
      .Comms_mutex_tx_s1_read                               (Comms_mutex_tx_s1_read),
      .Comms_mutex_tx_s1_readdata                           (Comms_mutex_tx_s1_readdata),
      .Comms_mutex_tx_s1_readdata_from_sa                   (Comms_mutex_tx_s1_readdata_from_sa),
      .Comms_mutex_tx_s1_reset_n                            (Comms_mutex_tx_s1_reset_n),
      .Comms_mutex_tx_s1_write                              (Comms_mutex_tx_s1_write),
      .Comms_mutex_tx_s1_writedata                          (Comms_mutex_tx_s1_writedata),
      .clk                                                  (clk_50),
      .d1_Comms_mutex_tx_s1_end_xfer                        (d1_Comms_mutex_tx_s1_end_xfer),
      .reset_n                                              (clk_50_reset_n)
    );

  Comms_mutex_tx the_Comms_mutex_tx
    (
      .address       (Comms_mutex_tx_s1_address),
      .chipselect    (Comms_mutex_tx_s1_chipselect),
      .clk           (clk_50),
      .data_from_cpu (Comms_mutex_tx_s1_writedata),
      .data_to_cpu   (Comms_mutex_tx_s1_readdata),
      .read          (Comms_mutex_tx_s1_read),
      .reset_n       (Comms_mutex_tx_s1_reset_n),
      .write         (Comms_mutex_tx_s1_write)
    );

  pio_LED_s1_arbitrator the_pio_LED_s1
    (
      .CPU0_data_master_address_to_slave             (CPU0_data_master_address_to_slave),
      .CPU0_data_master_granted_pio_LED_s1           (CPU0_data_master_granted_pio_LED_s1),
      .CPU0_data_master_latency_counter              (CPU0_data_master_latency_counter),
      .CPU0_data_master_qualified_request_pio_LED_s1 (CPU0_data_master_qualified_request_pio_LED_s1),
      .CPU0_data_master_read                         (CPU0_data_master_read),
      .CPU0_data_master_read_data_valid_pio_LED_s1   (CPU0_data_master_read_data_valid_pio_LED_s1),
      .CPU0_data_master_requests_pio_LED_s1          (CPU0_data_master_requests_pio_LED_s1),
      .CPU0_data_master_write                        (CPU0_data_master_write),
      .CPU0_data_master_writedata                    (CPU0_data_master_writedata),
      .CPU1_data_master_address_to_slave             (CPU1_data_master_address_to_slave),
      .CPU1_data_master_granted_pio_LED_s1           (CPU1_data_master_granted_pio_LED_s1),
      .CPU1_data_master_latency_counter              (CPU1_data_master_latency_counter),
      .CPU1_data_master_qualified_request_pio_LED_s1 (CPU1_data_master_qualified_request_pio_LED_s1),
      .CPU1_data_master_read                         (CPU1_data_master_read),
      .CPU1_data_master_read_data_valid_pio_LED_s1   (CPU1_data_master_read_data_valid_pio_LED_s1),
      .CPU1_data_master_requests_pio_LED_s1          (CPU1_data_master_requests_pio_LED_s1),
      .CPU1_data_master_write                        (CPU1_data_master_write),
      .CPU1_data_master_writedata                    (CPU1_data_master_writedata),
      .clk                                           (clk_50),
      .d1_pio_LED_s1_end_xfer                        (d1_pio_LED_s1_end_xfer),
      .pio_LED_s1_address                            (pio_LED_s1_address),
      .pio_LED_s1_chipselect                         (pio_LED_s1_chipselect),
      .pio_LED_s1_readdata                           (pio_LED_s1_readdata),
      .pio_LED_s1_readdata_from_sa                   (pio_LED_s1_readdata_from_sa),
      .pio_LED_s1_reset_n                            (pio_LED_s1_reset_n),
      .pio_LED_s1_write_n                            (pio_LED_s1_write_n),
      .pio_LED_s1_writedata                          (pio_LED_s1_writedata),
      .reset_n                                       (clk_50_reset_n)
    );

  pio_LED the_pio_LED
    (
      .address    (pio_LED_s1_address),
      .chipselect (pio_LED_s1_chipselect),
      .clk        (clk_50),
      .out_port   (out_port_from_the_pio_LED),
      .readdata   (pio_LED_s1_readdata),
      .reset_n    (pio_LED_s1_reset_n),
      .write_n    (pio_LED_s1_write_n),
      .writedata  (pio_LED_s1_writedata)
    );

  //reset is asserted asynchronously and deasserted synchronously
  DE2_115_SOPC_reset_clk_50_domain_synch_module DE2_115_SOPC_reset_clk_50_domain_synch
    (
      .clk      (clk_50),
      .data_in  (1'b1),
      .data_out (clk_50_reset_n),
      .reset_n  (reset_n_sources)
    );

  //reset sources mux, which is an e_mux
  assign reset_n_sources = ~(~reset_n |
    0 |
    CPU0_jtag_debug_module_resetrequest_from_sa |
    CPU0_jtag_debug_module_resetrequest_from_sa |
    CPU1_jtag_debug_module_resetrequest_from_sa |
    CPU1_jtag_debug_module_resetrequest_from_sa);


endmodule


//synthesis translate_off



// <ALTERA_NOTE> CODE INSERTED BETWEEN HERE

// AND HERE WILL BE PRESERVED </ALTERA_NOTE>


// If user logic components use Altsync_Ram with convert_hex2ver.dll,
// set USE_convert_hex2ver in the user comments section above

// `ifdef USE_convert_hex2ver
// `else
// `define NO_PLI 1
// `endif

`include "c:/altera/12.1/quartus/eda/sim_lib/altera_mf.v"
`include "c:/altera/12.1/quartus/eda/sim_lib/220model.v"
`include "c:/altera/12.1/quartus/eda/sim_lib/sgate.v"
`include "CPU1_memory.v"
`include "Comms_mutex_rx.v"
`include "pio_LED.v"
`include "CPU1_JTAG_UART.v"
`include "Comms_mutex_tx.v"
`include "CPU0_JTAG_UART.v"
`include "CPU1_test_bench.v"
`include "CPU1_mult_cell.v"
`include "CPU1_oci_test_bench.v"
`include "CPU1_jtag_debug_module_tck.v"
`include "CPU1_jtag_debug_module_sysclk.v"
`include "CPU1_jtag_debug_module_wrapper.v"
`include "CPU1.v"
`include "Comms_memory.v"
`include "CPU0_memory.v"
`include "CPU0_test_bench.v"
`include "CPU0_mult_cell.v"
`include "CPU0_oci_test_bench.v"
`include "CPU0_jtag_debug_module_tck.v"
`include "CPU0_jtag_debug_module_sysclk.v"
`include "CPU0_jtag_debug_module_wrapper.v"
`include "CPU0.v"

`timescale 1ns / 1ps

module test_bench 
;


  wire             CPU0_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa;
  wire             CPU0_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_dataavailable_from_sa;
  wire             CPU1_JTAG_UART_avalon_jtag_slave_readyfordata_from_sa;
  wire             clk;
  reg              clk_50;
  wire    [  7: 0] out_port_from_the_pio_LED;
  reg              reset_n;


// <ALTERA_NOTE> CODE INSERTED BETWEEN HERE
//  add your signals and additional architecture here
// AND HERE WILL BE PRESERVED </ALTERA_NOTE>

  //Set us up the Dut
  DE2_115_SOPC DUT
    (
      .clk_50                    (clk_50),
      .out_port_from_the_pio_LED (out_port_from_the_pio_LED),
      .reset_n                   (reset_n)
    );

  initial
    clk_50 = 1'b0;
  always
    #10 clk_50 <= ~clk_50;
  
  initial 
    begin
      reset_n <= 0;
      #200 reset_n <= 1;
    end

endmodule


//synthesis translate_on