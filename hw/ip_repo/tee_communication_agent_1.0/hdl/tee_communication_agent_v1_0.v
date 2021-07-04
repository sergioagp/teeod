
`timescale 1 ns / 1 ps

	module tee_communication_agent_v1_0 #
	(
		// Users to add parameters here

		// User parameters ends
		// Do not modify the parameters beyond this line


		// Parameters of Axi Slave Bus Interface S00_AXI
		parameter integer C_S_AXI_DATA_WIDTH	= 32,
		parameter integer C_S_AXI_ADDR_WIDTH	= 6
	)
	(
		// Users to add ports here
		output reg reg0_intr,
		// User ports ends
		// Do not modify the ports beyond this line


		// Ports of Axi Slave Bus Interface S00_AXI
		input wire  s00_axi_aclk,
		input wire  s00_axi_aresetn,
		input wire [C_S_AXI_ADDR_WIDTH-1 : 0] s00_axi_awaddr,
		input wire [2 : 0] s00_axi_awprot,
		input wire  s00_axi_awvalid,
		output wire  s00_axi_awready,
		input wire [C_S_AXI_DATA_WIDTH-1 : 0] s00_axi_wdata,
		input wire [(C_S_AXI_DATA_WIDTH/8)-1 : 0] s00_axi_wstrb,
		input wire  s00_axi_wvalid,
		output wire  s00_axi_wready,
		output wire [1 : 0] s00_axi_bresp,
		output wire  s00_axi_bvalid,
		input wire  s00_axi_bready,
		input wire [C_S_AXI_ADDR_WIDTH-1 : 0] s00_axi_araddr,
		input wire [2 : 0] s00_axi_arprot,
		input wire  s00_axi_arvalid,
		output wire  s00_axi_arready,
		output wire [C_S_AXI_DATA_WIDTH-1 : 0] s00_axi_rdata,
		output wire [1 : 0] s00_axi_rresp,
		output wire  s00_axi_rvalid,
		input wire  s00_axi_rready,

		// Ports of Axi Slave Bus Interface S01_AXI
		input wire  s01_axi_aclk,
		input wire  s01_axi_aresetn,
		input wire [C_S_AXI_ADDR_WIDTH-1 : 0] s01_axi_awaddr,
		input wire [2 : 0] s01_axi_awprot,
		input wire  s01_axi_awvalid,
		output wire  s01_axi_awready,
		input wire [C_S_AXI_DATA_WIDTH-1 : 0] s01_axi_wdata,
		input wire [(C_S_AXI_DATA_WIDTH/8)-1 : 0] s01_axi_wstrb,
		input wire  s01_axi_wvalid,
		output wire  s01_axi_wready,
		output wire [1 : 0] s01_axi_bresp,
		output wire  s01_axi_bvalid,
		input wire  s01_axi_bready,
		input wire [C_S_AXI_ADDR_WIDTH-1 : 0] s01_axi_araddr,
		input wire [2 : 0] s01_axi_arprot,
		input wire  s01_axi_arvalid,
		output wire  s01_axi_arready,
		output wire [C_S_AXI_DATA_WIDTH-1 : 0] s01_axi_rdata,
		output wire [1 : 0] s01_axi_rresp,
		output wire  s01_axi_rvalid,
		input wire  s01_axi_rready
	);

	wire s00_update_reg [11:0];
	wire [C_S_AXI_DATA_WIDTH-1:0]	s00_out_reg [11:0];

	wire s01_update_reg [11:0];
	wire [C_S_AXI_DATA_WIDTH-1:0]	s01_out_reg [11:0];

	
	reg [C_S_AXI_DATA_WIDTH-1:0]	shrd_reg [11:0];
	
	integer	 addr_index;
	always @( posedge s00_axi_aclk )
	begin
	  if ( s00_axi_aresetn == 1'b0 )
	    begin
			for ( addr_index = 0; addr_index < 12 ; addr_index = addr_index+1 )
				shrd_reg[addr_index] <= 0;
	    end 
	  else
	    begin
			for ( addr_index = 0; addr_index < 12 ; addr_index = addr_index+1 )  
				if (s01_update_reg[addr_index])
					begin
						shrd_reg[addr_index] <= s01_out_reg[addr_index];
					end
				else if(s00_update_reg[addr_index])
					begin
						shrd_reg[addr_index] <= s00_out_reg[addr_index];
					end
	    end
	end    

	always @( posedge s00_axi_aclk )
	begin
	  if ( s00_axi_aresetn == 1'b0 )
	    begin
			reg0_intr <= 0'b0;
	    end 
	  else
	    begin
			if(s01_update_reg[0])
				reg0_intr <= 0'b0;
			else if(s00_update_reg[0])
				reg0_intr <= 0'b1;

	    end
	end   

// Instantiation of Axi Bus Interface S00_AXI
	tee_communication_agent_v1_0_S00_AXI # ( 
		.C_S_AXI_DATA_WIDTH(C_S_AXI_DATA_WIDTH),
		.C_S_AXI_ADDR_WIDTH(C_S_AXI_ADDR_WIDTH)
	) tee_communication_agent_v1_0_S00_AXI_inst (
		.update_reg0(s00_update_reg[0]),
		.update_reg1(s00_update_reg[1]),
		.update_reg2(s00_update_reg[2]),
		.update_reg3(s00_update_reg[3]),
		.update_reg4(s00_update_reg[4]),
		.update_reg5(s00_update_reg[5]),
		.update_reg6(s00_update_reg[6]),
		.update_reg7(s00_update_reg[7]),
		.update_reg8(s00_update_reg[8]),
		.update_reg9(s00_update_reg[9]),
		.update_reg10(s00_update_reg[10]),
		.update_reg11(s00_update_reg[11]),
		.out_reg0(s00_out_reg[0]),
		.out_reg1(s00_out_reg[1]),
		.out_reg2(s00_out_reg[2]),
		.out_reg3(s00_out_reg[3]),
		.out_reg4(s00_out_reg[4]),
		.out_reg5(s00_out_reg[5]),
		.out_reg6(s00_out_reg[6]),
		.out_reg7(s00_out_reg[7]),
		.out_reg8(s00_out_reg[8]),
		.out_reg9(s00_out_reg[9]),
		.out_reg10(s00_out_reg[10]),
		.out_reg11(s00_out_reg[11]),
		.in_reg0(shrd_reg[0]),
		.in_reg1(shrd_reg[1]),
		.in_reg2(shrd_reg[2]),
		.in_reg3(shrd_reg[3]),
		.in_reg4(shrd_reg[4]),
		.in_reg5(shrd_reg[5]),
		.in_reg6(shrd_reg[6]),
		.in_reg7(shrd_reg[7]),
		.in_reg8(shrd_reg[8]),
		.in_reg9(shrd_reg[9]),
		.in_reg10(shrd_reg[10]),
		.in_reg11(shrd_reg[11]),
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

// Instantiation of Axi Bus Interface S01_AXI
	tee_communication_agent_v1_0_S01_AXI # ( 
		.C_S_AXI_DATA_WIDTH(C_S_AXI_DATA_WIDTH),
		.C_S_AXI_ADDR_WIDTH(C_S_AXI_ADDR_WIDTH)
	) tee_communication_agent_v1_0_S01_AXI_inst (
		.update_reg0(s01_update_reg[0]),
		.update_reg1(s01_update_reg[1]),
		.update_reg2(s01_update_reg[2]),
		.update_reg3(s01_update_reg[3]),
		.update_reg4(s01_update_reg[4]),
		.update_reg5(s01_update_reg[5]),
		.update_reg6(s01_update_reg[6]),
		.update_reg7(s01_update_reg[7]),
		.update_reg8(s01_update_reg[8]),
		.update_reg9(s01_update_reg[9]),
		.update_reg10(s01_update_reg[10]),
		.update_reg11(s01_update_reg[11]),
		.out_reg0(s01_out_reg[0]),
		.out_reg1(s01_out_reg[1]),
		.out_reg2(s01_out_reg[2]),
		.out_reg3(s01_out_reg[3]),
		.out_reg4(s01_out_reg[4]),
		.out_reg5(s01_out_reg[5]),
		.out_reg6(s01_out_reg[6]),
		.out_reg7(s01_out_reg[7]),
		.out_reg8(s01_out_reg[8]),
		.out_reg9(s01_out_reg[9]),
		.out_reg10(s01_out_reg[10]),
		.out_reg11(s01_out_reg[11]),
		.in_reg0(shrd_reg[0]),
		.in_reg1(shrd_reg[1]),
		.in_reg2(shrd_reg[2]),
		.in_reg3(shrd_reg[3]),
		.in_reg4(shrd_reg[4]),
		.in_reg5(shrd_reg[5]),
		.in_reg6(shrd_reg[6]),
		.in_reg7(shrd_reg[7]),
		.in_reg8(shrd_reg[8]),
		.in_reg9(shrd_reg[9]),
		.in_reg10(shrd_reg[10]),
		.in_reg11(shrd_reg[11]),
		.S_AXI_ACLK(s01_axi_aclk),
		.S_AXI_ARESETN(s01_axi_aresetn),
		.S_AXI_AWADDR(s01_axi_awaddr),
		.S_AXI_AWPROT(s01_axi_awprot),
		.S_AXI_AWVALID(s01_axi_awvalid),
		.S_AXI_AWREADY(s01_axi_awready),
		.S_AXI_WDATA(s01_axi_wdata),
		.S_AXI_WSTRB(s01_axi_wstrb),
		.S_AXI_WVALID(s01_axi_wvalid),
		.S_AXI_WREADY(s01_axi_wready),
		.S_AXI_BRESP(s01_axi_bresp),
		.S_AXI_BVALID(s01_axi_bvalid),
		.S_AXI_BREADY(s01_axi_bready),
		.S_AXI_ARADDR(s01_axi_araddr),
		.S_AXI_ARPROT(s01_axi_arprot),
		.S_AXI_ARVALID(s01_axi_arvalid),
		.S_AXI_ARREADY(s01_axi_arready),
		.S_AXI_RDATA(s01_axi_rdata),
		.S_AXI_RRESP(s01_axi_rresp),
		.S_AXI_RVALID(s01_axi_rvalid),
		.S_AXI_RREADY(s01_axi_rready)
	);

	// Add user logic here

	// User logic ends

	endmodule
