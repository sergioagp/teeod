`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/18/2020 01:06:25 PM
// Design Name: 
// Module Name: bv_sm
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module bv_sm ();

    localparam CLK_PERIOD_SYS  = 100;
    localparam C_S00_AXI_DATA_WIDTH = 32;
    reg         clk_sys  = 1'b0;
    reg         reset_n;
    reg         init_req;
    reg         done_load;
    wire         init_load;
    wire         done;
    wire         reset_enclav;


	 security_monitor security_monitor_int (
		.aclk(clk_sys),
		.nreset(reset_n),
		.done_cpy(done_load),
		.str_cpy(init_req),
		.done(done)
	 ); 

    always #(CLK_PERIOD_SYS/2)  clk_sys  <= ~clk_sys;

   // Release resets on appropriate clock edges
    initial
    begin
        reset_n                 = 1'b0;
        init_req                = 1'b0;
        done_load               = 1'b0;
        
        repeat (500) @(posedge clk_sys) begin end;
        reset_n = 1'b1;
        repeat (100) @(posedge clk_sys) begin end;
        init_req = 1'b1;
        repeat (100) @(posedge clk_sys) begin end;
        done_load= 1'b1;
        repeat (1) @(posedge clk_sys) begin end;
        done_load= 1'b0;
        repeat (100) @(posedge clk_sys) begin end;
        init_req = 1'b0;
    end


endmodule