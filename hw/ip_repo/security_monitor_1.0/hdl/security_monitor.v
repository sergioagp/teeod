`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/18/2020 10:27:15 AM
// Design Name: 
// Module Name: security_monitor
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


module security_monitor(
		input wire  aclk,
		input wire nreset,
		input wire done_cpy,
		input wire str_cpy,
		output wire done
    );
	
    reg done_r;
    
	assign done = done_r;

	always @( posedge aclk )
	begin
	   if(~nreset)
	   begin
	       done_r <= 'b0;
	   end
	   else begin
	       if(done_cpy)
	       begin
	           done_r <= 1;
	       end
	       else if(~str_cpy)
	       begin
	           done_r <= 0;
	       end
	   end
	 end

endmodule
