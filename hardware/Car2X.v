module Car2X(
	// Clock
	input         CLOCK_50,
	
	// KEY
	input  [0: 0] KEY,
	
	// Ethernet 0
	output        NET0_MDC,
	inout         NET0_MDIO,
	output        NET0_RESET_N,
	
	// Ethernet 1
	output        NET1_GTX_CLK,
	output        NET1_MDC,
	inout         NET1_MDIO,
	output        NET1_RESET_N,
	input         NET1_RX_CLK,
	input  [3: 0] NET1_RX_DATA,
	input         NET1_RX_DV,
	output [3: 0] NET1_TX_DATA,
	output        NET1_TX_EN
);

	wire sys_clk, clk_125, clk_25, clk_2p5, tx_clk;
	wire core_reset_n;
	wire mdc, mdio_in, mdio_oen, mdio_out;
	wire eth_mode, ena_10;

	assign mdio_in   = NET1_MDIO;
	assign NET0_MDC  = mdc;
	assign NET1_MDC  = mdc;
	assign NET0_MDIO = mdio_oen ? 1'bz : mdio_out;
	assign NET1_MDIO = mdio_oen ? 1'bz : mdio_out;
	
	assign NET0_RESET_N = core_reset_n;
	assign NET1_RESET_N = core_reset_n;
	
	my_pll pll_inst(
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
	
	my_ddio_out ddio_out_inst(
		.datain_h(1'b1),
		.datain_l(1'b0),
		.outclock(tx_clk),
		.dataout(NET1_GTX_CLK)
	);
	
	nios_system system_inst(
		.clk_clk                                (sys_clk),      //             clk.clk
		.reset_reset_n                          (core_reset_n), //           reset.reset_n	

		.tse_mac_conduit_connection_rx_control  (NET1_RX_DV),   // tse_mac_conduit.rx_control
		.tse_mac_conduit_connection_rx_clk      (NET1_RX_CLK),  //                .rx_clk
		.tse_mac_conduit_connection_tx_control  (NET1_TX_EN),   //                .tx_control
		.tse_mac_conduit_connection_tx_clk      (tx_clk),       //                .tx_clk
		.tse_mac_conduit_connection_rgmii_out   (NET1_TX_DATA), //                .rgmii_out
		.tse_mac_conduit_connection_rgmii_in    (NET1_RX_DATA), //                .rgmii_in
		.tse_mac_conduit_connection_ena_10      (ena_10),       //                .ena_10
		.tse_mac_conduit_connection_eth_mode    (eth_mode),     //                .eth_mode
		.tse_mac_conduit_connection_mdio_in     (mdio_in),      //                .mdio_in
		.tse_mac_conduit_connection_mdio_out    (mdio_out),     //                .mdio_out
		.tse_mac_conduit_connection_mdc         (mdc),          //                .mdc
		.tse_mac_conduit_connection_mdio_oen    (mdio_oen)      //                .mdio_oen
	);

endmodule 