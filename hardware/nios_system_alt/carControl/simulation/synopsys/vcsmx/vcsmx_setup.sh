
# (C) 2001-2014 Altera Corporation. All rights reserved.
# Your use of Altera Corporation's design tools, logic functions and 
# other software and tools, and its AMPP partner logic functions, and 
# any output files any of the foregoing (including device programming 
# or simulation files), and any associated documentation or information 
# are expressly subject to the terms and conditions of the Altera 
# Program License Subscription Agreement, Altera MegaCore Function 
# License Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by Altera 
# or its authorized distributors. Please refer to the applicable 
# agreement for further details.

# ACDS 12.1 177 win32 2014.06.21.12:51:53

# ----------------------------------------
# vcsmx - auto-generated simulation script

# ----------------------------------------
# initialize variables
TOP_LEVEL_NAME="carControl"
QSYS_SIMDIR="./../../"
SKIP_FILE_COPY=0
SKIP_DEV_COM=0
SKIP_COM=0
SKIP_ELAB=0
SKIP_SIM=0
USER_DEFINED_ELAB_OPTIONS=""
USER_DEFINED_SIM_OPTIONS="+vcs+finish+100"

# ----------------------------------------
# overwrite variables - DO NOT MODIFY!
# This block evaluates each command line argument, typically used for 
# overwriting variables. An example usage:
#   sh <simulator>_setup.sh SKIP_ELAB=1 SKIP_SIM=1
for expression in "$@"; do
  eval $expression
  if [ $? -ne 0 ]; then
    echo "Error: This command line argument, \"$expression\", is/has an invalid expression." >&2
    exit $?
  fi
done

# ----------------------------------------
# create compilation libraries
mkdir -p ./libraries/work/
mkdir -p ./libraries/irq_mapper/
mkdir -p ./libraries/rsp_xbar_mux_001/
mkdir -p ./libraries/rsp_xbar_mux/
mkdir -p ./libraries/rsp_xbar_demux_002/
mkdir -p ./libraries/rsp_xbar_demux/
mkdir -p ./libraries/cmd_xbar_mux/
mkdir -p ./libraries/cmd_xbar_demux_001/
mkdir -p ./libraries/cmd_xbar_demux/
mkdir -p ./libraries/rst_controller/
mkdir -p ./libraries/limiter/
mkdir -p ./libraries/id_router_002/
mkdir -p ./libraries/id_router/
mkdir -p ./libraries/addr_router_001/
mkdir -p ./libraries/addr_router/
mkdir -p ./libraries/carControl_memory_s1_translator_avalon_universal_slave_0_agent_rsp_fifo/
mkdir -p ./libraries/carControl_memory_s1_translator_avalon_universal_slave_0_agent/
mkdir -p ./libraries/carControl_nios2_data_master_translator_avalon_universal_master_0_agent/
mkdir -p ./libraries/carControl_memory_s1_translator/
mkdir -p ./libraries/carControl_nios2_data_master_translator/
mkdir -p ./libraries/mm_bridge_0/
mkdir -p ./libraries/carControl_uart/
mkdir -p ./libraries/carControl_memory/
mkdir -p ./libraries/carControl_nios2/
mkdir -p ./libraries/altera_ver/
mkdir -p ./libraries/lpm_ver/
mkdir -p ./libraries/sgate_ver/
mkdir -p ./libraries/altera_mf_ver/
mkdir -p ./libraries/altera_lnsim_ver/
mkdir -p ./libraries/cycloneive_ver/

# ----------------------------------------
# copy RAM/ROM files to simulation directory
if [ $SKIP_FILE_COPY -eq 0 ]; then
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_memory.hex ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ic_tag_ram.dat ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ic_tag_ram.hex ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ic_tag_ram.mif ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ociram_default_contents.dat ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ociram_default_contents.hex ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ociram_default_contents.mif ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_a.dat ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_a.hex ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_a.mif ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_b.dat ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_b.hex ./
  cp -f $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_b.mif ./
fi

# ----------------------------------------
# compile device library files
if [ $SKIP_DEV_COM -eq 0 ]; then
  vlogan +v2k           "c:/altera/12.1/quartus/eda/sim_lib/altera_primitives.v" -work altera_ver      
  vlogan +v2k           "c:/altera/12.1/quartus/eda/sim_lib/220model.v"          -work lpm_ver         
  vlogan +v2k           "c:/altera/12.1/quartus/eda/sim_lib/sgate.v"             -work sgate_ver       
  vlogan +v2k           "c:/altera/12.1/quartus/eda/sim_lib/altera_mf.v"         -work altera_mf_ver   
  vlogan +v2k -sverilog "c:/altera/12.1/quartus/eda/sim_lib/altera_lnsim.sv"     -work altera_lnsim_ver
  vlogan +v2k           "c:/altera/12.1/quartus/eda/sim_lib/cycloneive_atoms.v"  -work cycloneive_ver  
fi

# ----------------------------------------
# compile design files in correct order
if [ $SKIP_COM -eq 0 ]; then
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_irq_mapper.sv"                                -work irq_mapper                                                             
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                             -work rsp_xbar_mux_001                                                       
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_rsp_xbar_mux_001.sv"                          -work rsp_xbar_mux_001                                                       
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                             -work rsp_xbar_mux                                                           
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_rsp_xbar_mux.sv"                              -work rsp_xbar_mux                                                           
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_rsp_xbar_demux_002.sv"                        -work rsp_xbar_demux_002                                                     
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_rsp_xbar_demux.sv"                            -work rsp_xbar_demux                                                         
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                             -work cmd_xbar_mux                                                           
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_cmd_xbar_mux.sv"                              -work cmd_xbar_mux                                                           
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_cmd_xbar_demux_001.sv"                        -work cmd_xbar_demux_001                                                     
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_cmd_xbar_demux.sv"                            -work cmd_xbar_demux                                                         
  vlogan +v2k           "$QSYS_SIMDIR/submodules/altera_reset_controller.v"                               -work rst_controller                                                         
  vlogan +v2k           "$QSYS_SIMDIR/submodules/altera_reset_synchronizer.v"                             -work rst_controller                                                         
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_traffic_limiter.sv"                        -work limiter                                                                
  vlogan +v2k           "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_base.v"                        -work limiter                                                                
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_id_router_002.sv"                             -work id_router_002                                                          
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_id_router.sv"                                 -work id_router                                                              
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_addr_router_001.sv"                           -work addr_router_001                                                        
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/carControl_addr_router.sv"                               -work addr_router                                                            
  vlogan +v2k           "$QSYS_SIMDIR/submodules/altera_avalon_sc_fifo.v"                                 -work carControl_memory_s1_translator_avalon_universal_slave_0_agent_rsp_fifo
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_slave_agent.sv"                            -work carControl_memory_s1_translator_avalon_universal_slave_0_agent         
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_burst_uncompressor.sv"                     -work carControl_memory_s1_translator_avalon_universal_slave_0_agent         
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_master_agent.sv"                           -work carControl_nios2_data_master_translator_avalon_universal_master_0_agent
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_slave_translator.sv"                       -work carControl_memory_s1_translator                                        
  vlogan +v2k -sverilog "$QSYS_SIMDIR/submodules/altera_merlin_master_translator.sv"                      -work carControl_nios2_data_master_translator                                
  vlogan +v2k           "$QSYS_SIMDIR/submodules/altera_avalon_mm_bridge.v"                               -work mm_bridge_0                                                            
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_uart.v"                            -work carControl_uart                                                        
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_memory.v"                          -work carControl_memory                                                      
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_nios2.vo"                          -work carControl_nios2                                                       
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_jtag_debug_module_sysclk.v"  -work carControl_nios2                                                       
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_jtag_debug_module_tck.v"     -work carControl_nios2                                                       
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_jtag_debug_module_wrapper.v" -work carControl_nios2                                                       
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_mult_cell.v"                 -work carControl_nios2                                                       
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_oci_test_bench.v"            -work carControl_nios2                                                       
  vlogan +v2k           "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_test_bench.v"                -work carControl_nios2                                                       
  vlogan +v2k           "$QSYS_SIMDIR/carControl.v"                                                                                                                                    
fi

# ----------------------------------------
# elaborate top level design
if [ $SKIP_ELAB -eq 0 ]; then
  vcs -lca -t ps $USER_DEFINED_ELAB_OPTIONS $TOP_LEVEL_NAME
fi

# ----------------------------------------
# simulate
if [ $SKIP_SIM -eq 0 ]; then
  ./simv $USER_DEFINED_SIM_OPTIONS
fi
