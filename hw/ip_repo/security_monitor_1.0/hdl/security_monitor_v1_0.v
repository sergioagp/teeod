
`timescale 1 ns / 1 ps

	module security_monitor_v1_0 #
	(
		// Users to add parameters here

		// User parameters ends
		// Do not modify the parameters beyond this line


		// Parameters of Axi Slave Bus Interface S00_AXI
		parameter integer C_S00_AXI_DATA_WIDTH	= 32,
		parameter integer C_S00_AXI_ADDR_WIDTH	= 4,
		
		parameter integer C_ADDR_BRAM_DST	= 'h00_A002_0000,
		parameter integer C_CDMA_CONFIG   	= 'h0FF0
	)
	(
		// Users to add ports here
		input wire done_cpy,
		output wire [C_S00_AXI_DATA_WIDTH-1 : 0] addr_src,
     	output wire [C_S00_AXI_DATA_WIDTH-1 : 0] addr_dest,
     	output wire [C_S00_AXI_DATA_WIDTH-1 : 0] size,
     	output wire strt_cpy,
     	output wire [16-1 : 0] cma_config,
     	output wire rst_enclave,
		// User ports ends
		// Do not modify the ports beyond this line
		// Ports of Axi Slave Bus Interface S00_AXI
		input wire  s00_axi_aclk,
		input wire  s00_axi_aresetn,
		input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_awaddr,
		input wire [2 : 0] s00_axi_awprot,
		input wire  s00_axi_awvalid,
		output wire  s00_axi_awready,
		input wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_wdata,
		input wire [(C_S00_AXI_DATA_WIDTH/8)-1 : 0] s00_axi_wstrb,
		input wire  s00_axi_wvalid,
		output wire  s00_axi_wready,
		output wire [1 : 0] s00_axi_bresp,
		output wire  s00_axi_bvalid,
		input wire  s00_axi_bready,
		input wire [C_S00_AXI_ADDR_WIDTH-1 : 0] s00_axi_araddr,
		input wire [2 : 0] s00_axi_arprot,
		input wire  s00_axi_arvalid,
		output wire  s00_axi_arready,
		output wire [C_S00_AXI_DATA_WIDTH-1 : 0] s00_axi_rdata,
		output wire [1 : 0] s00_axi_rresp,
		output wire  s00_axi_rvalid,
		input wire  s00_axi_rready
	);

// Declare wires and regs
	wire done;

	wire [C_S00_AXI_DATA_WIDTH-1 : 0] rcv_reg0;
	wire [C_S00_AXI_DATA_WIDTH-1 : 0] rcv_reg1;
	wire [C_S00_AXI_DATA_WIDTH-1 : 0] rcv_reg2;
	wire [C_S00_AXI_DATA_WIDTH-1 : 0] rcv_reg3;

	wire [C_S00_AXI_DATA_WIDTH-1 : 0] trs_reg0;
	wire [C_S00_AXI_DATA_WIDTH-1 : 0] trs_reg1;
	wire [C_S00_AXI_DATA_WIDTH-1 : 0] trs_reg2;
	wire [C_S00_AXI_DATA_WIDTH-1 : 0] trs_reg3;


// ASSIGN I/O
    assign cma_config = C_CDMA_CONFIG;
	assign addr_src = rcv_reg0;
    assign addr_dest = C_ADDR_BRAM_DST;
    assign size = rcv_reg2;
    assign strt_cpy = rcv_reg3[0];

	assign trs_reg0 = addr_src;
	assign trs_reg1 = addr_dest;
	assign trs_reg2 = size;
	assign trs_reg3 = done; 



// Instantiation of Axi Bus Interface S00_AXI
	security_monitor_v1_0_S00_AXI # ( 
		.C_S_AXI_DATA_WIDTH(C_S00_AXI_DATA_WIDTH),
		.C_S_AXI_ADDR_WIDTH(C_S00_AXI_ADDR_WIDTH)
	) security_monitor_v1_0_S00_AXI_inst (
	    .rcv_reg0(rcv_reg0),
		.rcv_reg1(rcv_reg1),
		.rcv_reg2(rcv_reg2),
		.rcv_reg3(rcv_reg3),
		.trs_reg0(trs_reg0),
		.trs_reg1(trs_reg1),
		.trs_reg2(trs_reg2),
		.trs_reg3(trs_reg3),
		.S_AXI_ACLK(s00_axi_aclk),
		.S_AXI_ARESETN(s00_axi_aresetn),
		.S_AXI_AWADDR(s00_axi_awaddr),
		.S_AXI_AWPROT(s00_axi_awprot),
		.S_AXI_AWVALID(s00_axi_awvalid),
		.S_AXI_AWREADY(s00_axi_awready),
		.S_AXI_WDATA(s00_axi_wdata),
		.S_AXI_WSTRB(s00_axi_wstrb),
		.S_AXI_WVALID(s00_axi_wvalid),
		.S_AXI_WREADY(s00_axi_wready),
		.S_AXI_BRESP(s00_axi_bresp),
		.S_AXI_BVALID(s00_axi_bvalid),
		.S_AXI_BREADY(s00_axi_bready),
		.S_AXI_ARADDR(s00_axi_araddr),
		.S_AXI_ARPROT(s00_axi_arprot),
		.S_AXI_ARVALID(s00_axi_arvalid),
		.S_AXI_ARREADY(s00_axi_arready),
		.S_AXI_RDATA(s00_axi_rdata),
		.S_AXI_RRESP(s00_axi_rresp),
		.S_AXI_RVALID(s00_axi_rvalid),
		.S_AXI_RREADY(s00_axi_rready)
	);

	// Add user logic here
// Instantiation of Security Monitor
	 security_monitor security_monitor_int (
		.aclk(s00_axi_aclk),
		.nreset(s00_axi_aresetn),
		.done_cpy(done_cpy),
		.strt_cpy(strt_cpy),
		.done(done),
		.rst_enclave(rst_enclave)
	 ); 
	// User logic ends

	endmodule
