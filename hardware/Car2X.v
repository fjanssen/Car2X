module Car2X(
	// Clock
	input         CLOCK_50,

	// KEY
	input  [0: 0] KEY,
	
	// Ethernet 0
	output        NET1_MDC,
	inout         NET1_MDIO,
	output        NET1_RESET_N,
	
	// Ethernet 1
	output        NET0_GTX_CLK,
	output        NET0_MDC,
	inout         NET0_MDIO,
	output        NET0_RESET_N,
	input         NET0_RX_CLK,
	input  [3: 0] NET0_RX_DATA,
	input         NET0_RX_DV,
	output [3: 0] NET0_TX_DATA,
	output        NET0_TX_EN,
	
	// DRAM
	output [12:0] DRAM_ADDR,
	output [1:0]  DRAM_BA,
	output 		  DRAM_CS_N,
	output        DRAM_WE_N,
	output		  DRAM_CKE,
	output		  DRAM_CAS_N,
	output		  DRAM_RAS_N,
	output [3:0]  DRAM_DQM,
	inout [31:0]  DRAM_DQ,
	output		  DRAM_CLK
);

	wire sys_clk, clk_125, clk_25, clk_2p5, tx_clk;
	wire core_reset_n;
	wire mdc, mdio_in, mdio_oen, mdio_out;
	wire eth_mode, ena_10;

	assign mdio_in   = NET0_MDIO;
	assign NET1_MDC  = mdc;
	assign NET0_MDC  = mdc;
	assign NET1_MDIO = mdio_oen ? 1'bz : mdio_out;
	assign NET0_MDIO = mdio_oen ? 1'bz : mdio_out;
	
	assign NET1_RESET_N = core_reset_n;
	assign NET0_RESET_N = core_reset_n;

	
	tse_pll pll_inst(
		.areset	(~KEY[0]),
		.inclk0	(CLOCK_50),
		.c0		(sys_clk),
		.c1		(clk_125),
		.c2		(clk_25),
		.c3		(clk_2p5),
		.locked	(core_reset_n)
	); 
			
	assign tx_clk = eth_mode ? clk_125 :       // GbE Mode   = 125MHz clock
	                ena_10   ? clk_2p5 :       // 10Mb Mode  = 2.5MHz clock
	                           clk_25;         // 100Mb Mode = 25 MHz clock
	
	sdram_pll neg_3ns (sys_clk, DRAM_CLK);

	
	tse_ddio_out ddio_out_inst(
		.datain_h(1'b1),
		.datain_l(1'b0),
		.outclock(tx_clk),
		.dataout(NET0_GTX_CLK)
	);
	
	nios_system system_inst(
		.clk_clk                                (sys_clk),      //             clk.clk
		.reset_reset_n                          (core_reset_n),  // (core_reset_n), //           reset.reset_n	
		
		.tse_conduit_connection_rx_control  (NET0_RX_DV),   // tse_mac_conduit.rx_control
		.tse_conduit_connection_rx_clk      (NET0_RX_CLK),  //                .rx_clk
		.tse_conduit_connection_tx_control  (NET0_TX_EN),   //                .tx_control
		.tse_conduit_connection_tx_clk      (tx_clk),       //                .tx_clk
		.tse_conduit_connection_rgmii_out   (NET0_TX_DATA), //                .rgmii_out
		.tse_conduit_connection_rgmii_in    (NET0_RX_DATA), //                .rgmii_in
		.tse_conduit_connection_ena_10      (ena_10),       //                .ena_10
		.tse_conduit_connection_eth_mode    (eth_mode),     //                .eth_mode
		.tse_conduit_connection_mdio_in     (mdio_in),      //                .mdio_in
		.tse_conduit_connection_mdio_out    (mdio_out),     //                .mdio_out
		.tse_conduit_connection_mdc         (mdc),          //                .mdc
		.tse_conduit_connection_mdio_oen    (mdio_oen),     //                .mdio_oen
		
		.com_sdram_wire_addr                              (DRAM_ADDR),                              //                            com_sdram_wire.addr
      .com_sdram_wire_ba                                (DRAM_BA),                                //                                          .ba
      .com_sdram_wire_cas_n                             (DRAM_CAS_N),                             //                                          .cas_n
      .com_sdram_wire_cke                               (DRAM_CKE),                               //                                          .cke
      .com_sdram_wire_cs_n                              (DRAM_CS_N),                              //                                          .cs_n
      .com_sdram_wire_dq                                (DRAM_DQ),                                //                                          .dq
      .com_sdram_wire_dqm                               (DRAM_DQM),                               //                                          .dqm
      .com_sdram_wire_ras_n                             (DRAM_RAS_N),                             //                                          .ras_n
      .com_sdram_wire_we_n                              (DRAM_WE_N),                              //                                          .we_n
		//.sdram_clk_clk												  (DRAM_CLK)
		);

endmodule 