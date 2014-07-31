
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

# ACDS 12.1 177 win32 2014.06.21.12:51:54

# ----------------------------------------
# Auto-generated simulation script

# ----------------------------------------
# Initialize the variable
if ![info exists SYSTEM_INSTANCE_NAME] { 
  set SYSTEM_INSTANCE_NAME ""
} elseif { ![ string match "" $SYSTEM_INSTANCE_NAME ] } { 
  set SYSTEM_INSTANCE_NAME "/$SYSTEM_INSTANCE_NAME"
} 

if ![info exists TOP_LEVEL_NAME] { 
  set TOP_LEVEL_NAME "carControl"
} elseif { ![ string match "" $TOP_LEVEL_NAME ] } { 
  set TOP_LEVEL_NAME "$TOP_LEVEL_NAME"
} 

if ![info exists QSYS_SIMDIR] { 
  set QSYS_SIMDIR "./../"
} elseif { ![ string match "" $QSYS_SIMDIR ] } { 
  set QSYS_SIMDIR "$QSYS_SIMDIR"
} 

set Aldec "Riviera"
if { [ string match "*Active-HDL*" [ vsim -version ] ] } {
  set Aldec "Active"
}

if { [ string match "Active" $Aldec ] } {
  scripterconf -tcl
  createdesign "$TOP_LEVEL_NAME"  "."
  opendesign "$TOP_LEVEL_NAME"
}

# ----------------------------------------
# Copy ROM/RAM files to simulation directory
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_memory.hex ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ic_tag_ram.dat ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ic_tag_ram.hex ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ic_tag_ram.mif ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ociram_default_contents.dat ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ociram_default_contents.hex ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_ociram_default_contents.mif ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_a.dat ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_a.hex ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_a.mif ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_b.dat ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_b.hex ./
file copy -force $QSYS_SIMDIR/submodules/carControl_carControl_nios2_rf_ram_b.mif ./

# ----------------------------------------
# Create compilation libraries
proc ensure_lib { lib } { if ![file isdirectory $lib] { vlib $lib } }
ensure_lib      ./libraries     
ensure_lib      ./libraries/work
vmap       work ./libraries/work
ensure_lib                  ./libraries/altera_ver      
vmap       altera_ver       ./libraries/altera_ver      
ensure_lib                  ./libraries/lpm_ver         
vmap       lpm_ver          ./libraries/lpm_ver         
ensure_lib                  ./libraries/sgate_ver       
vmap       sgate_ver        ./libraries/sgate_ver       
ensure_lib                  ./libraries/altera_mf_ver   
vmap       altera_mf_ver    ./libraries/altera_mf_ver   
ensure_lib                  ./libraries/altera_lnsim_ver
vmap       altera_lnsim_ver ./libraries/altera_lnsim_ver
ensure_lib                  ./libraries/cycloneive_ver  
vmap       cycloneive_ver   ./libraries/cycloneive_ver  
ensure_lib                                                                         ./libraries/irq_mapper                                                             
vmap       irq_mapper                                                              ./libraries/irq_mapper                                                             
ensure_lib                                                                         ./libraries/rsp_xbar_mux_001                                                       
vmap       rsp_xbar_mux_001                                                        ./libraries/rsp_xbar_mux_001                                                       
ensure_lib                                                                         ./libraries/rsp_xbar_mux                                                           
vmap       rsp_xbar_mux                                                            ./libraries/rsp_xbar_mux                                                           
ensure_lib                                                                         ./libraries/rsp_xbar_demux_002                                                     
vmap       rsp_xbar_demux_002                                                      ./libraries/rsp_xbar_demux_002                                                     
ensure_lib                                                                         ./libraries/rsp_xbar_demux                                                         
vmap       rsp_xbar_demux                                                          ./libraries/rsp_xbar_demux                                                         
ensure_lib                                                                         ./libraries/cmd_xbar_mux                                                           
vmap       cmd_xbar_mux                                                            ./libraries/cmd_xbar_mux                                                           
ensure_lib                                                                         ./libraries/cmd_xbar_demux_001                                                     
vmap       cmd_xbar_demux_001                                                      ./libraries/cmd_xbar_demux_001                                                     
ensure_lib                                                                         ./libraries/cmd_xbar_demux                                                         
vmap       cmd_xbar_demux                                                          ./libraries/cmd_xbar_demux                                                         
ensure_lib                                                                         ./libraries/rst_controller                                                         
vmap       rst_controller                                                          ./libraries/rst_controller                                                         
ensure_lib                                                                         ./libraries/limiter                                                                
vmap       limiter                                                                 ./libraries/limiter                                                                
ensure_lib                                                                         ./libraries/id_router_002                                                          
vmap       id_router_002                                                           ./libraries/id_router_002                                                          
ensure_lib                                                                         ./libraries/id_router                                                              
vmap       id_router                                                               ./libraries/id_router                                                              
ensure_lib                                                                         ./libraries/addr_router_001                                                        
vmap       addr_router_001                                                         ./libraries/addr_router_001                                                        
ensure_lib                                                                         ./libraries/addr_router                                                            
vmap       addr_router                                                             ./libraries/addr_router                                                            
ensure_lib                                                                         ./libraries/carControl_memory_s1_translator_avalon_universal_slave_0_agent_rsp_fifo
vmap       carControl_memory_s1_translator_avalon_universal_slave_0_agent_rsp_fifo ./libraries/carControl_memory_s1_translator_avalon_universal_slave_0_agent_rsp_fifo
ensure_lib                                                                         ./libraries/carControl_memory_s1_translator_avalon_universal_slave_0_agent         
vmap       carControl_memory_s1_translator_avalon_universal_slave_0_agent          ./libraries/carControl_memory_s1_translator_avalon_universal_slave_0_agent         
ensure_lib                                                                         ./libraries/carControl_nios2_data_master_translator_avalon_universal_master_0_agent
vmap       carControl_nios2_data_master_translator_avalon_universal_master_0_agent ./libraries/carControl_nios2_data_master_translator_avalon_universal_master_0_agent
ensure_lib                                                                         ./libraries/carControl_memory_s1_translator                                        
vmap       carControl_memory_s1_translator                                         ./libraries/carControl_memory_s1_translator                                        
ensure_lib                                                                         ./libraries/carControl_nios2_data_master_translator                                
vmap       carControl_nios2_data_master_translator                                 ./libraries/carControl_nios2_data_master_translator                                
ensure_lib                                                                         ./libraries/mm_bridge_0                                                            
vmap       mm_bridge_0                                                             ./libraries/mm_bridge_0                                                            
ensure_lib                                                                         ./libraries/carControl_uart                                                        
vmap       carControl_uart                                                         ./libraries/carControl_uart                                                        
ensure_lib                                                                         ./libraries/carControl_memory                                                      
vmap       carControl_memory                                                       ./libraries/carControl_memory                                                      
ensure_lib                                                                         ./libraries/carControl_nios2                                                       
vmap       carControl_nios2                                                        ./libraries/carControl_nios2                                                       

# ----------------------------------------
# Compile device library files
alias dev_com {
  echo "\[exec\] dev_com"
  vlog +define+SKIP_KEYWORDS_PRAGMA "c:/altera/12.1/quartus/eda/sim_lib/altera_primitives.v" -work altera_ver      
  vlog                              "c:/altera/12.1/quartus/eda/sim_lib/220model.v"          -work lpm_ver         
  vlog                              "c:/altera/12.1/quartus/eda/sim_lib/sgate.v"             -work sgate_ver       
  vlog                              "c:/altera/12.1/quartus/eda/sim_lib/altera_mf.v"         -work altera_mf_ver   
  vlog                              "c:/altera/12.1/quartus/eda/sim_lib/altera_lnsim.sv"     -work altera_lnsim_ver
  vlog                              "c:/altera/12.1/quartus/eda/sim_lib/cycloneive_atoms.v"  -work cycloneive_ver  
}

# ----------------------------------------
# Compile the design files in correct order
alias com {
  echo "\[exec\] com"
  vlog  "$QSYS_SIMDIR/submodules/carControl_irq_mapper.sv"                                -work irq_mapper                                                             
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                             -work rsp_xbar_mux_001                                                       
  vlog  "$QSYS_SIMDIR/submodules/carControl_rsp_xbar_mux_001.sv"                          -work rsp_xbar_mux_001                                                       
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                             -work rsp_xbar_mux                                                           
  vlog  "$QSYS_SIMDIR/submodules/carControl_rsp_xbar_mux.sv"                              -work rsp_xbar_mux                                                           
  vlog  "$QSYS_SIMDIR/submodules/carControl_rsp_xbar_demux_002.sv"                        -work rsp_xbar_demux_002                                                     
  vlog  "$QSYS_SIMDIR/submodules/carControl_rsp_xbar_demux.sv"                            -work rsp_xbar_demux                                                         
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_arbitrator.sv"                             -work cmd_xbar_mux                                                           
  vlog  "$QSYS_SIMDIR/submodules/carControl_cmd_xbar_mux.sv"                              -work cmd_xbar_mux                                                           
  vlog  "$QSYS_SIMDIR/submodules/carControl_cmd_xbar_demux_001.sv"                        -work cmd_xbar_demux_001                                                     
  vlog  "$QSYS_SIMDIR/submodules/carControl_cmd_xbar_demux.sv"                            -work cmd_xbar_demux                                                         
  vlog  "$QSYS_SIMDIR/submodules/altera_reset_controller.v"                               -work rst_controller                                                         
  vlog  "$QSYS_SIMDIR/submodules/altera_reset_synchronizer.v"                             -work rst_controller                                                         
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_traffic_limiter.sv"                        -work limiter                                                                
  vlog  "$QSYS_SIMDIR/submodules/altera_avalon_st_pipeline_base.v"                        -work limiter                                                                
  vlog  "$QSYS_SIMDIR/submodules/carControl_id_router_002.sv"                             -work id_router_002                                                          
  vlog  "$QSYS_SIMDIR/submodules/carControl_id_router.sv"                                 -work id_router                                                              
  vlog  "$QSYS_SIMDIR/submodules/carControl_addr_router_001.sv"                           -work addr_router_001                                                        
  vlog  "$QSYS_SIMDIR/submodules/carControl_addr_router.sv"                               -work addr_router                                                            
  vlog  "$QSYS_SIMDIR/submodules/altera_avalon_sc_fifo.v"                                 -work carControl_memory_s1_translator_avalon_universal_slave_0_agent_rsp_fifo
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_slave_agent.sv"                            -work carControl_memory_s1_translator_avalon_universal_slave_0_agent         
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_burst_uncompressor.sv"                     -work carControl_memory_s1_translator_avalon_universal_slave_0_agent         
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_master_agent.sv"                           -work carControl_nios2_data_master_translator_avalon_universal_master_0_agent
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_slave_translator.sv"                       -work carControl_memory_s1_translator                                        
  vlog  "$QSYS_SIMDIR/submodules/altera_merlin_master_translator.sv"                      -work carControl_nios2_data_master_translator                                
  vlog  "$QSYS_SIMDIR/submodules/altera_avalon_mm_bridge.v"                               -work mm_bridge_0                                                            
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_uart.v"                            -work carControl_uart                                                        
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_memory.v"                          -work carControl_memory                                                      
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_nios2.vo"                          -work carControl_nios2                                                       
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_jtag_debug_module_sysclk.v"  -work carControl_nios2                                                       
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_jtag_debug_module_tck.v"     -work carControl_nios2                                                       
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_jtag_debug_module_wrapper.v" -work carControl_nios2                                                       
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_mult_cell.v"                 -work carControl_nios2                                                       
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_oci_test_bench.v"            -work carControl_nios2                                                       
  vlog  "$QSYS_SIMDIR/submodules/carControl_carControl_nios2_test_bench.v"                -work carControl_nios2                                                       
  vlog  "$QSYS_SIMDIR/carControl.v"                                                                                                                                    
}

# ----------------------------------------
# Elaborate top level design
alias elab {
  echo "\[exec\] elab"
  vsim +access +r  -t ps -L work -L irq_mapper -L rsp_xbar_mux_001 -L rsp_xbar_mux -L rsp_xbar_demux_002 -L rsp_xbar_demux -L cmd_xbar_mux -L cmd_xbar_demux_001 -L cmd_xbar_demux -L rst_controller -L limiter -L id_router_002 -L id_router -L addr_router_001 -L addr_router -L carControl_memory_s1_translator_avalon_universal_slave_0_agent_rsp_fifo -L carControl_memory_s1_translator_avalon_universal_slave_0_agent -L carControl_nios2_data_master_translator_avalon_universal_master_0_agent -L carControl_memory_s1_translator -L carControl_nios2_data_master_translator -L mm_bridge_0 -L carControl_uart -L carControl_memory -L carControl_nios2 -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver $TOP_LEVEL_NAME
}

# ----------------------------------------
# Elaborate the top level design with -dbg -O2 option
alias elab_debug {
  echo "\[exec\] elab_debug"
  vsim -dbg -O2 +access +r -t ps -L work -L irq_mapper -L rsp_xbar_mux_001 -L rsp_xbar_mux -L rsp_xbar_demux_002 -L rsp_xbar_demux -L cmd_xbar_mux -L cmd_xbar_demux_001 -L cmd_xbar_demux -L rst_controller -L limiter -L id_router_002 -L id_router -L addr_router_001 -L addr_router -L carControl_memory_s1_translator_avalon_universal_slave_0_agent_rsp_fifo -L carControl_memory_s1_translator_avalon_universal_slave_0_agent -L carControl_nios2_data_master_translator_avalon_universal_master_0_agent -L carControl_memory_s1_translator -L carControl_nios2_data_master_translator -L mm_bridge_0 -L carControl_uart -L carControl_memory -L carControl_nios2 -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver $TOP_LEVEL_NAME
}

# ----------------------------------------
# Compile all the design files and elaborate the top level design
alias ld "
  dev_com
  com
  elab
"

# ----------------------------------------
# Compile all the design files and elaborate the top level design with -dbg -O2
alias ld_debug "
  dev_com
  com
  elab_debug
"

# ----------------------------------------
# Print out user commmand line aliases
alias h {
  echo "List Of Command Line Aliases"
  echo
  echo "dev_com                       -- Compile device library files"
  echo
  echo "com                           -- Compile the design files in correct order"
  echo
  echo "elab                          -- Elaborate top level design"
  echo
  echo "elab_debug                    -- Elaborate the top level design with -dbg -O2 option"
  echo
  echo "ld                            -- Compile all the design files and elaborate the top level design"
  echo
  echo "ld_debug                      -- Compile all the design files and elaborate the top level design with -dbg -O2"
  echo
  echo 
  echo
  echo "List Of Variables"
  echo
  echo "TOP_LEVEL_NAME                -- Top level module name."
  echo
  echo "SYSTEM_INSTANCE_NAME          -- Instantiated system module name inside top level module."
  echo
  echo "QSYS_SIMDIR                   -- Qsys base simulation directory."
}
h
