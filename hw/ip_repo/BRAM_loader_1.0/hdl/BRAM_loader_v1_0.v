
`timescale 1 ns / 1 ps

	module BRAM_loader_v1_0 #
	(
		// Users to add parameters here

		// User parameters ends
		// Do not modify the parameters beyond this line


		// Parameters of Axi Master Bus Interface M_AXI_DDR
		parameter  C_M_AXI_DDR_TARGET_SLAVE_BASE_ADDR	= 32'h40000000,
		parameter integer C_M_AXI_DDR_BURST_LEN	= 16,
		parameter integer C_M_AXI_DDR_ID_WIDTH	= 1,
		parameter integer C_M_AXI_DDR_ADDR_WIDTH	= 32,
		parameter integer C_M_AXI_DDR_DATA_WIDTH	= 32,
		parameter integer C_M_AXI_DDR_AWUSER_WIDTH	= 0,
		parameter integer C_M_AXI_DDR_ARUSER_WIDTH	= 0,
		parameter integer C_M_AXI_DDR_WUSER_WIDTH	= 0,
		parameter integer C_M_AXI_DDR_RUSER_WIDTH	= 0,
		parameter integer C_M_AXI_DDR_BUSER_WIDTH	= 0,

		// Parameters of Axi Master Bus Interface M_AXI_BRAM
		parameter  C_M_AXI_BRAM_START_DATA_VALUE	= 32'hAA000000,
		parameter  C_M_AXI_BRAM_TARGET_SLAVE_BASE_ADDR	= 32'h40000000,
		parameter integer C_M_AXI_BRAM_ADDR_WIDTH	= 32,
		parameter integer C_M_AXI_BRAM_DATA_WIDTH	= 32,
		parameter integer C_M_AXI_BRAM_TRANSACTIONS_NUM	= 4
	)
	(
		// Users to add ports here
		input wire aclk,
		input wire aresetn,
		input wire [31:0] addr_source,
		input wire [31:0] addr_destiny,
		input wire [31:0] size,
		input wire trigger,
		output wire done,
		// User ports ends
		// Do not modify the ports beyond this line


		// Ports of Axi Master Bus Interface M_AXI_DDR
		input wire  m_axi_ddr_init_axi_txn,
		output wire  m_axi_ddr_txn_done,
		output wire  m_axi_ddr_error,
		/*input wire  m_axi_ddr_aclk,
		input wire  m_axi_ddr_aresetn,*/
		output wire [C_M_AXI_DDR_ID_WIDTH-1 : 0] m_axi_ddr_awid,
		output wire [C_M_AXI_DDR_ADDR_WIDTH-1 : 0] m_axi_ddr_awaddr,
		output wire [7 : 0] m_axi_ddr_awlen,
		output wire [2 : 0] m_axi_ddr_awsize,
		output wire [1 : 0] m_axi_ddr_awburst,
		output wire  m_axi_ddr_awlock,
		output wire [3 : 0] m_axi_ddr_awcache,
		output wire [2 : 0] m_axi_ddr_awprot,
		output wire [3 : 0] m_axi_ddr_awqos,
		output wire [C_M_AXI_DDR_AWUSER_WIDTH-1 : 0] m_axi_ddr_awuser,
		output wire  m_axi_ddr_awvalid,
		input wire  m_axi_ddr_awready,
		output wire [C_M_AXI_DDR_DATA_WIDTH-1 : 0] m_axi_ddr_wdata,
		output wire [C_M_AXI_DDR_DATA_WIDTH/8-1 : 0] m_axi_ddr_wstrb,
		output wire  m_axi_ddr_wlast,
		output wire [C_M_AXI_DDR_WUSER_WIDTH-1 : 0] m_axi_ddr_wuser,
		output wire  m_axi_ddr_wvalid,
		input wire  m_axi_ddr_wready,
		input wire [C_M_AXI_DDR_ID_WIDTH-1 : 0] m_axi_ddr_bid,
		input wire [1 : 0] m_axi_ddr_bresp,
		input wire [C_M_AXI_DDR_BUSER_WIDTH-1 : 0] m_axi_ddr_buser,
		input wire  m_axi_ddr_bvalid,
		output wire  m_axi_ddr_bready,
		output wire [C_M_AXI_DDR_ID_WIDTH-1 : 0] m_axi_ddr_arid,
		output wire [C_M_AXI_DDR_ADDR_WIDTH-1 : 0] m_axi_ddr_araddr,
		output wire [7 : 0] m_axi_ddr_arlen,
		output wire [2 : 0] m_axi_ddr_arsize,
		output wire [1 : 0] m_axi_ddr_arburst,
		output wire  m_axi_ddr_arlock,
		output wire [3 : 0] m_axi_ddr_arcache,
		output wire [2 : 0] m_axi_ddr_arprot,
		output wire [3 : 0] m_axi_ddr_arqos,
		output wire [C_M_AXI_DDR_ARUSER_WIDTH-1 : 0] m_axi_ddr_aruser,
		output wire  m_axi_ddr_arvalid,
		input wire  m_axi_ddr_arready,
		input wire [C_M_AXI_DDR_ID_WIDTH-1 : 0] m_axi_ddr_rid,
		input wire [C_M_AXI_DDR_DATA_WIDTH-1 : 0] m_axi_ddr_rdata,
		input wire [1 : 0] m_axi_ddr_rresp,
		input wire  m_axi_ddr_rlast,
		input wire [C_M_AXI_DDR_RUSER_WIDTH-1 : 0] m_axi_ddr_ruser,
		input wire  m_axi_ddr_rvalid,
		output wire  m_axi_ddr_rready

		// Ports of Axi Master Bus Interface M_AXI_BRAM
		/*input wire  m_axi_bram_init_axi_txn,
		output wire  m_axi_bram_error,
		output wire  m_axi_bram_txn_done,
		/*input wire  m_axi_bram_aclk,
		input wire  m_axi_bram_aresetn,
		output wire [C_M_AXI_BRAM_ADDR_WIDTH-1 : 0] m_axi_bram_awaddr,
		output wire [2 : 0] m_axi_bram_awprot,
		output wire  m_axi_bram_awvalid,
		input wire  m_axi_bram_awready,
		output wire [C_M_AXI_BRAM_DATA_WIDTH-1 : 0] m_axi_bram_wdata,
		output wire [C_M_AXI_BRAM_DATA_WIDTH/8-1 : 0] m_axi_bram_wstrb,
		output wire  m_axi_bram_wvalid,
		input wire  m_axi_bram_wready,
		input wire [1 : 0] m_axi_bram_bresp,
		input wire  m_axi_bram_bvalid,
		output wire  m_axi_bram_bready,
		output wire [C_M_AXI_BRAM_ADDR_WIDTH-1 : 0] m_axi_bram_araddr,
		output wire [2 : 0] m_axi_bram_arprot,
		output wire  m_axi_bram_arvalid,
		input wire  m_axi_bram_arready,
		input wire [C_M_AXI_BRAM_DATA_WIDTH-1 : 0] m_axi_bram_rdata,
		input wire [1 : 0] m_axi_bram_rresp,
		input wire  m_axi_bram_rvalid,
		output wire  m_axi_bram_rready*/
	);

	wire  _m_axi_bram_init_axi_txn;
	wire  _m_axi_bram_error;
	wire  _m_axi_bram_txn_done;
	wire [C_M_AXI_BRAM_ADDR_WIDTH-1 : 0] _m_axi_bram_awaddr;
	wire [2 : 0] _m_axi_bram_awprot;
	wire  _m_axi_bram_awvalid;
	wire  _m_axi_bram_awready;
	wire [C_M_AXI_BRAM_DATA_WIDTH-1 : 0] _m_axi_bram_wdata;
	wire [C_M_AXI_BRAM_DATA_WIDTH/8-1 : 0] _m_axi_bram_wstrb;
	wire  _m_axi_bram_wvalid;
	wire  _m_axi_bram_wready;
	wire [1 : 0] _m_axi_bram_bresp;
	wire  _m_axi_bram_bvalid;
	wire  _m_axi_bram_bready;
	wire [C_M_AXI_BRAM_ADDR_WIDTH-1 : 0] _m_axi_bram_araddr;
	wire [2 : 0] _m_axi_bram_arprot;
	wire  _m_axi_bram_arvalid;
	wire  _m_axi_bram_arready;
	wire [C_M_AXI_BRAM_DATA_WIDTH-1 : 0] _m_axi_bram_rdata;
	wire [1 : 0] _m_axi_bram_rresp;
	wire  _m_axi_bram_rvalid;
	wire  _m_axi_bram_rready;

	wire w_trigger, w_reads_done, w_writes_done, w_write;
	wire [C_M_AXI_BRAM_ADDR_WIDTH-1 : 0] w_raddr, w_waddr;
	wire [C_M_AXI_BRAM_DATA_WIDTH-1 : 0] w_wdata;

// Instantiation of Axi Bus Interface M_AXI_DDR
/*	BRAM_loader_v1_0_M_AXI_DDR # ( 
		.C_M_TARGET_SLAVE_BASE_ADDR(C_M_AXI_DDR_TARGET_SLAVE_BASE_ADDR),
		.C_M_AXI_BURST_LEN(C_M_AXI_DDR_BURST_LEN),
		.C_M_AXI_ID_WIDTH(C_M_AXI_DDR_ID_WIDTH),
		.C_M_AXI_ADDR_WIDTH(C_M_AXI_DDR_ADDR_WIDTH),
		.C_M_AXI_DATA_WIDTH(C_M_AXI_DDR_DATA_WIDTH),
		.C_M_AXI_AWUSER_WIDTH(C_M_AXI_DDR_AWUSER_WIDTH),
		.C_M_AXI_ARUSER_WIDTH(C_M_AXI_DDR_ARUSER_WIDTH),
		.C_M_AXI_WUSER_WIDTH(C_M_AXI_DDR_WUSER_WIDTH),
		.C_M_AXI_RUSER_WIDTH(C_M_AXI_DDR_RUSER_WIDTH),
		.C_M_AXI_BUSER_WIDTH(C_M_AXI_DDR_BUSER_WIDTH)
	) BRAM_loader_v1_0_M_AXI_DDR_inst (
		.INIT_AXI_TXN(m_axi_ddr_init_axi_txn),
		.TXN_DONE(m_axi_ddr_txn_done),
		.ERROR(m_axi_ddr_error),
		.M_AXI_ACLK(aclk),
		.M_AXI_ARESETN(aresetn),
		.M_AXI_AWID(m_axi_ddr_awid),
		.M_AXI_AWADDR(m_axi_ddr_awaddr),
		.M_AXI_AWLEN(m_axi_ddr_awlen),
		.M_AXI_AWSIZE(m_axi_ddr_awsize),
		.M_AXI_AWBURST(m_axi_ddr_awburst),
		.M_AXI_AWLOCK(m_axi_ddr_awlock),
		.M_AXI_AWCACHE(m_axi_ddr_awcache),
		.M_AXI_AWPROT(m_axi_ddr_awprot),
		.M_AXI_AWQOS(m_axi_ddr_awqos),
		.M_AXI_AWUSER(m_axi_ddr_awuser),
		.M_AXI_AWVALID(m_axi_ddr_awvalid),
		.M_AXI_AWREADY(m_axi_ddr_awready),
		.M_AXI_WDATA(m_axi_ddr_wdata),
		.M_AXI_WSTRB(m_axi_ddr_wstrb),
		.M_AXI_WLAST(m_axi_ddr_wlast),
		.M_AXI_WUSER(m_axi_ddr_wuser),
		.M_AXI_WVALID(m_axi_ddr_wvalid),
		.M_AXI_WREADY(m_axi_ddr_wready),
		.M_AXI_BID(m_axi_ddr_bid),
		.M_AXI_BRESP(m_axi_ddr_bresp),
		.M_AXI_BUSER(m_axi_ddr_buser),
		.M_AXI_BVALID(m_axi_ddr_bvalid),
		.M_AXI_BREADY(m_axi_ddr_bready),
		.M_AXI_ARID(m_axi_ddr_arid),
		.M_AXI_ARADDR(m_axi_ddr_araddr),
		.M_AXI_ARLEN(m_axi_ddr_arlen),
		.M_AXI_ARSIZE(m_axi_ddr_arsize),
		.M_AXI_ARBURST(m_axi_ddr_arburst),
		.M_AXI_ARLOCK(m_axi_ddr_arlock),
		.M_AXI_ARCACHE(m_axi_ddr_arcache),
		.M_AXI_ARPROT(m_axi_ddr_arprot),
		.M_AXI_ARQOS(m_axi_ddr_arqos),
		.M_AXI_ARUSER(m_axi_ddr_aruser),
		.M_AXI_ARVALID(m_axi_ddr_arvalid),
		.M_AXI_ARREADY(m_axi_ddr_arready),
		.M_AXI_RID(m_axi_ddr_rid),
		.M_AXI_RDATA(m_axi_ddr_rdata),
		.M_AXI_RRESP(m_axi_ddr_rresp),
		.M_AXI_RLAST(m_axi_ddr_rlast),
		.M_AXI_RUSER(m_axi_ddr_ruser),
		.M_AXI_RVALID(m_axi_ddr_rvalid),
		.M_AXI_RREADY(m_axi_ddr_rready)
	);
*/
// Instantiation of Axi Bus Interface M_AXI_BRAM
	BRAM_loader_v1_0_M_AXI_BRAM # ( 
		/*.C_M_START_DATA_VALUE(C_M_AXI_BRAM_START_DATA_VALUE),
		.C_M_TARGET_SLAVE_BASE_ADDR(C_M_AXI_BRAM_TARGET_SLAVE_BASE_ADDR),*/
		.C_M_AXI_ADDR_WIDTH(C_M_AXI_BRAM_ADDR_WIDTH),
		.C_M_AXI_DATA_WIDTH(C_M_AXI_BRAM_DATA_WIDTH)
		//.C_M_TRANSACTIONS_NUM(C_M_AXI_BRAM_TRANSACTIONS_NUM)
	) BRAM_loader_v1_0_M_AXI_BRAM_inst (
		.write(w_write),
		.write_done(w_writes_done),
		.read_done(w_reads_done),
		.wdata(w_wdata),
		.raddr(w_raddr),
		.waddr(w_waddr),
		.INIT_AXI_TXN(w_trigger),
		.ERROR(m_axi_bram_error),
		//.TXN_DONE(m_axi_bram_txn_done),
		.M_AXI_ACLK(aclk),
		.M_AXI_ARESETN(aresetn),
		.M_AXI_AWADDR(_m_axi_bram_awaddr),
		.M_AXI_AWPROT(_m_axi_bram_awprot),
		.M_AXI_AWVALID(_m_axi_bram_awvalid),
		.M_AXI_AWREADY(_m_axi_bram_awready),
		.M_AXI_WDATA(_m_axi_bram_wdata),
		.M_AXI_WSTRB(_m_axi_bram_wstrb),
		.M_AXI_WVALID(_m_axi_bram_wvalid),
		.M_AXI_WREADY(_m_axi_bram_wready),
		.M_AXI_BRESP(_m_axi_bram_bresp),
		.M_AXI_BVALID(_m_axi_bram_bvalid),
		.M_AXI_BREADY(_m_axi_bram_bready),
		.M_AXI_ARADDR(_m_axi_bram_araddr),
		.M_AXI_ARPROT(_m_axi_bram_arprot),
		.M_AXI_ARVALID(_m_axi_bram_arvalid),
		.M_AXI_ARREADY(_m_axi_bram_arready),
		.M_AXI_RDATA(_m_axi_bram_rdata),
		.M_AXI_RRESP(_m_axi_bram_rresp),
		.M_AXI_RVALID(_m_axi_bram_rvalid),
		.M_AXI_RREADY(_m_axi_bram_rready)
	);

	// Add user logic here

	M_AXI_Lite_cdma_config # (
		/*.ADDR_SOURCE(C_M_AXI_Lite_cdma_ADDR_SOURCE),
		.ADDR_DESTINY(C_M_AXI_Lite_cdma_ADDR_DESTINY),*/
		.C_M00_AXI_ADDR_WIDTH(C_M_AXI_BRAM_ADDR_WIDTH),
		.C_M00_AXI_DATA_WIDTH(C_M_AXI_BRAM_DATA_WIDTH)
	)
	M_AXI_Lite_cdma_config_inst
	(
		.write(w_write),
		.write_done(w_writes_done),
		.read_done(w_reads_done),
		.wdata(w_wdata),
		.raddr(w_raddr),
		.waddr(w_waddr),
		.trigger_transfer(w_trigger),
		.cdma_done(done),
		.m00_axi_init_axi_txn(trigger),
		.m00_axi_aclk(aclk),
		.m00_axi_aresetn(aresetn),
		.m00_axi_rdata(_m_axi_bram_rdata),
		/*.SA_offset(32'h0000_d0b0),
		.DA_offset(32'hA000_2000),
		.size(1024*4) */
		.SA_offset(addr_source),
		.DA_offset(addr_destiny),
		.size(size*4) 
	);

	axi_cdma_0 cdma (
	  .m_axi_aclk(aclk),                 		// input wire m_axi_aclk
	  .s_axi_lite_aclk(aclk),       			// input wire s_axi_lite_aclk
	  .s_axi_lite_aresetn(aresetn),  			// input wire s_axi_lite_aresetn
	  .cdma_introut(done),              		// output wire cdma_introut
	  //Configuration PORT
	  .s_axi_lite_awready(_m_axi_bram_awready),  // output wire s_axi_lite_awready
	  .s_axi_lite_awvalid(_m_axi_bram_awvalid),  // input wire s_axi_lite_awvalid
	  .s_axi_lite_awaddr(_m_axi_bram_awaddr),    // input wire [5 : 0] s_axi_lite_awaddr
	  .s_axi_lite_wready(_m_axi_bram_wready),    // output wire s_axi_lite_wready
	  .s_axi_lite_wvalid(_m_axi_bram_wvalid),    // input wire s_axi_lite_wvalid
	  .s_axi_lite_wdata(_m_axi_bram_wdata),      // input wire [31 : 0] s_axi_lite_wdata
	  .s_axi_lite_bready(_m_axi_bram_bready),    // input wire s_axi_lite_bready
	  .s_axi_lite_bvalid(_m_axi_bram_bvalid),    // output wire s_axi_lite_bvalid
	  .s_axi_lite_bresp(_m_axi_bram_bresp),      // output wire [1 : 0] s_axi_lite_bresp
	  .s_axi_lite_arready(_m_axi_bram_arready),  // output wire s_axi_lite_arready
	  .s_axi_lite_arvalid(_m_axi_bram_arvalid),  // input wire s_axi_lite_arvalid
	  .s_axi_lite_araddr(_m_axi_bram_araddr),    // input wire [5 : 0] s_axi_lite_araddr
	  .s_axi_lite_rready(_m_axi_bram_rready),    // input wire s_axi_lite_rready
	  .s_axi_lite_rvalid(_m_axi_bram_rvalid),    // output wire s_axi_lite_rvalid
	  .s_axi_lite_rdata(_m_axi_bram_rdata),      // output wire [31 : 0] s_axi_lite_rdata
	  .s_axi_lite_rresp(_m_axi_bram_rresp),      // output wire [1 : 0] s_axi_lite_rresp
	  //data port
	  .m_axi_arready(m_axi_ddr_arready),            // input wire m_axi_arready
	  .m_axi_arvalid(m_axi_ddr_arvalid),            // output wire m_axi_arvalid
	  .m_axi_araddr(m_axi_ddr_araddr),              // output wire [31 : 0] m_axi_araddr
	  .m_axi_arlen(m_axi_ddr_arlen),                // output wire [7 : 0] m_axi_arlen
	  .m_axi_arsize(m_axi_ddr_arsize),              // output wire [2 : 0] m_axi_arsize
	  .m_axi_arburst(m_axi_ddr_arburst),            // output wire [1 : 0] m_axi_arburst
	  .m_axi_arprot(m_axi_ddr_arprot),              // output wire [2 : 0] m_axi_arprot
	  .m_axi_arcache(m_axi_ddr_arcache),            // output wire [3 : 0] m_axi_arcache
	  .m_axi_rready(m_axi_ddr_rready),              // output wire m_axi_rready
	  .m_axi_rvalid(m_axi_ddr_rvalid),              // input wire m_axi_rvalid
	  .m_axi_rdata(m_axi_ddr_rdata),                // input wire [31 : 0] m_axi_rdata
	  .m_axi_rresp(m_axi_ddr_rresp),                // input wire [1 : 0] m_axi_rresp
	  .m_axi_rlast(m_axi_ddr_rlast),                // input wire m_axi_rlast
	  .m_axi_awready(m_axi_ddr_awready),            // input wire m_axi_awready
	  .m_axi_awvalid(m_axi_ddr_awvalid),            // output wire m_axi_awvalid
	  .m_axi_awaddr(m_axi_ddr_awaddr),              // output wire [31 : 0] m_axi_awaddr
	  .m_axi_awlen(m_axi_ddr_awlen),                // output wire [7 : 0] m_axi_awlen
	  .m_axi_awsize(m_axi_ddr_awsize),              // output wire [2 : 0] m_axi_awsize
	  .m_axi_awburst(m_axi_ddr_awburst),            // output wire [1 : 0] m_axi_awburst
	  .m_axi_awprot(m_axi_ddr_awprot),              // output wire [2 : 0] m_axi_awprot
	  .m_axi_awcache(m_axi_ddr_awcache),            // output wire [3 : 0] m_axi_awcache
	  .m_axi_wready(m_axi_ddr_wready),              // input wire m_axi_wready
	  .m_axi_wvalid(m_axi_ddr_wvalid),              // output wire m_axi_wvalid
	  .m_axi_wdata(m_axi_ddr_wdata),                // output wire [31 : 0] m_axi_wdata
	  .m_axi_wstrb(m_axi_ddr_wstrb),                // output wire [3 : 0] m_axi_wstrb
	  .m_axi_wlast(m_axi_ddr_wlast),                // output wire m_axi_wlast
	  .m_axi_bready(m_axi_ddr_bready),              // output wire m_axi_bready
	  .m_axi_bvalid(m_axi_ddr_bvalid),              // input wire m_axi_bvalid
	  .m_axi_bresp(m_axi_ddr_bresp)		            // input wire [1 : 0] m_axi_bresp
	  //.cdma_tvect_out(cdma_tvect_out)          // output wire [31 : 0] cdma_tvect_out
	);

	// User logic ends

	endmodule
