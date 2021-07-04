`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/21/2020 10:32:58 AM
// Design Name: 
// Module Name: M_AXI_Lite_cdma_config
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


module M_AXI_Lite_cdma_config # (
		parameter  ADDR_SOURCE	= 32'hC000_0000,
		parameter  ADDR_DESTINY	= 32'h44A0_2000,
		parameter integer C_M00_AXI_ADDR_WIDTH	= 32,
		parameter integer C_M00_AXI_DATA_WIDTH	= 32
	)
	(
		output wire write,
		input wire write_done,
		input wire read_done,
		output wire [C_M00_AXI_DATA_WIDTH-1 : 0] wdata,
		output wire [C_M00_AXI_ADDR_WIDTH-1 : 0] raddr,
		output wire [C_M00_AXI_ADDR_WIDTH-1 : 0] waddr,
		output wire trigger_transfer,
		input wire cdma_done,

		input wire  m00_axi_init_axi_txn,
		input wire  m00_axi_aclk,
		input wire  m00_axi_aresetn,
		input wire [C_M00_AXI_DATA_WIDTH-1 : 0] m00_axi_rdata,
		input wire [C_M00_AXI_ADDR_WIDTH-1 : 0] SA_offset,
		input wire [C_M00_AXI_ADDR_WIDTH-1 : 0] DA_offset,
		input wire [C_M00_AXI_ADDR_WIDTH-1 : 0] size
	);

	// Add user logic here
	reg r_trigger,	// triggers a write or read transaction form the master to the slave
	 	r_write,		// Indicates if the AXI transactions is a write or a read 	
	 	r_pulse, 		// to init the next fsm state transaction
	 	r_cdma_busy;	

	reg [C_M00_AXI_DATA_WIDTH-1 : 0] r_wdata, r_rdata;
	reg [C_M00_AXI_ADDR_WIDTH-1 : 0] r_raddr, r_waddr;

	reg [2:0] fsm_state;
	parameter [2:0] IDLE 	= 3'b000, // This state initiates AXI4Lite transaction 
			WRITE_CDMACR   	= 3'b001, // This state configures the CDMA
			WRITE_SA 		= 3'b010, // This state configures the CDMA Source Address
			WRITE_DA 		= 3'b011, // This state configures the CDMA Destination Address
			WRITE_BTT 		= 3'b100, // This state issues the transaction by write the size to copy 
			WRITE_CDMASR   	= 3'b101; 
	
	// CDMA register space
	parameter [C_M00_AXI_ADDR_WIDTH-1 : 0] BASE_ADDR = 32'hA000_4000,
			CDMACR 	 = 8'h00,
			CDMASR 	 = 8'h04,
			SA 		 = 8'h18, 
			DA 		 = 8'h20,
			BTT 	 = 8'h28;

	reg  	init_txn_ff;
	reg  	init_txn_ff2;
	wire  	init_txn_pulse;	
	assign init_txn_pulse	= (!init_txn_ff2) && init_txn_ff;

	assign wdata = r_wdata;
	assign raddr = r_raddr;
	assign waddr = r_waddr;
	assign trigger_transfer = r_trigger;
	assign write = r_write ;
	/*assign w_fsm = fsm_state ;
*/
	//Generate a pulse to initiate AXI transaction.
	always @(posedge m00_axi_aclk)										      
	  begin                                                                        
	    // Initiates AXI transaction delay    
	    if (m00_axi_aresetn == 0 )                                                   
	      begin                                                                    
	        init_txn_ff <= 1'b0;                                                   
	        init_txn_ff2 <= 1'b0;                                                   
	      end                                                                               
	    else                                                                       
	      begin  
	        init_txn_ff <= m00_axi_init_axi_txn;
	        init_txn_ff2 <= init_txn_ff;                                                                 
	      end                                                                      
	  end  

	//CDMA configuration state machine                        
	  always @ ( posedge m00_axi_aclk)                                                    
	  begin                                                                             
	    if (m00_axi_aresetn == 1'b0)                                                     
	      begin          
	        fsm_state  <= IDLE;  
	        r_trigger <= 0;
	        r_write <= 0;
	        r_pulse <= 0;
	        r_cdma_busy <= 0; 
	        r_wdata <= 0;   
	        r_raddr <= 0;
	        r_rdata <= 0;                                    
	      end                                                                           
	    else                                                                            
	      begin                                                                                                                               
	        case (fsm_state)                                                       
	                                                                                    
	          IDLE:   
	          	if(init_txn_pulse) begin
	          		r_raddr <= BASE_ADDR + CDMASR;
	          		r_trigger <= 1;
	          		r_write <= 0;
	          	end
	          	else begin
	          		r_rdata <= m00_axi_rdata;
	          		if(read_done) begin
		          		if(r_rdata[1] == 1)	begin
		          			fsm_state <= WRITE_CDMACR;
		          			r_pulse <= 1; 
	          				r_trigger <= 0;
		          			r_cdma_busy <= 0; // The cdma is free to be used
		          		end
			          	else begin
			          		r_trigger <= 0;
			          		r_cdma_busy <= 1; // The cdma is busy, try again
		                	fsm_state  <= IDLE;                                                                                                    
		          		end                                                                                                                    
	          		end
	          		if (cdma_done) begin
	          			r_pulse <= 1; 
	          			fsm_state  <= WRITE_CDMASR;  
	          		end
	          	end
	          WRITE_CDMACR:
	          	if(r_pulse)
	          	begin     
		            r_raddr <= BASE_ADDR + CDMACR; // to read the register's content
	          		r_trigger <= 1;
	          		r_write <= 0;
	          		r_pulse <= 0;
	          	end
	          	else begin
	          		if(read_done) begin
	          			r_wdata <= m00_axi_rdata & (~32'h0000_4000) | (32'h0000_1000) ; //clear bit 14 and set bit 12
	          			r_waddr <= BASE_ADDR + CDMACR;
	          			r_trigger <= 1;
	          			r_write <= 1;
	          		end
	          		else begin
	          			r_trigger <= 0;
	          		end 
	          		if(write_done) begin
	          			fsm_state <= WRITE_SA;     
	          			r_pulse <= 1;  
	          			r_trigger <= 0;
	          		end
		            else begin                                                                 
						fsm_state  <= WRITE_CDMACR;                                                                                               
					end                                                                   
	          	end
	                                                                             
	          WRITE_SA:   
	          	if(r_pulse)begin
		          	//r_wdata <= ADDR_SOURCE + SA_offset;
		          	r_wdata <= SA_offset;
		          	r_waddr <= BASE_ADDR + SA;
		          	r_trigger <= 1;
		          	r_write <= 1;
		          	r_pulse <= 0;
		        end
		        else begin
		          	if(write_done)begin
	          			fsm_state <= WRITE_DA;  
	          			r_pulse <= 1;  
	          			r_trigger <= 0;                                                   
	          		end
		            else begin                                                                 
						fsm_state  <= WRITE_SA;                                                                                               
					end    
		        end
                                                                                                                                    
	           WRITE_DA: 
	           	if(r_pulse)begin                                                           
	             	//r_wdata <= 32'hA000_6000;
	             	/*r_wdata <= ADDR_DESTINY + DA_offset;*/
	             	r_wdata <= DA_offset;
	             	r_waddr <= BASE_ADDR + DA;
		          	r_trigger <= 1;
		          	r_write <= 1;
		          	r_pulse <= 0;
		        end
		       	else begin
		          	if(write_done)begin
		      			fsm_state <= WRITE_BTT; 
		      			r_pulse <= 1;  
		      			r_trigger <= 0;                                                    
		      		end
		            else begin                                                                 
						fsm_state  <= WRITE_DA;                                                                                               
					end
		       	end
	            WRITE_BTT:  
	            if(r_pulse)begin                                                          
		            r_wdata <= size;
		            r_waddr <= BASE_ADDR + BTT;
		          	r_trigger <= 1;
		          	r_write <= 1;
		          	r_pulse <= 0;
		        end
		        else begin
		          	if(write_done)begin
	          			fsm_state <= IDLE; 
	          			r_pulse <= 0;  
	          			r_trigger <= 0;                                                    
	          		end
		            else begin                                                                 
						fsm_state  <= WRITE_BTT;                                                                                               
					end 
				end
				WRITE_CDMASR:
	          	if(r_pulse)
	          	begin     
		            r_raddr <= BASE_ADDR + CDMASR; // to read the register's content
	          		r_trigger <= 1;
	          		r_write <= 0;
	          		r_pulse <= 0;
	          	end
	          	else begin
	          		if(read_done) begin
	          			r_wdata <= m00_axi_rdata | (32'h0000_1000) ; //set bit 12 (IOC_Irq) to clear the interrupt
	          			r_waddr <= BASE_ADDR + CDMASR;
	          			r_trigger <= 1;
	          			r_write <= 1;
	          		end
	          		else begin
	          			r_trigger <= 0;
	          		end 
	          		if(write_done) begin
						fsm_state  <= IDLE;                                                                                                   
	          			r_pulse <= 0;  
	          			r_trigger <= 0;
	          		end
		            else begin                                                                 
						fsm_state  <= WRITE_CDMASR;                                                                                               
					end                                                                   
	          	end
	           default :                                                                
	             begin                                                                  
	               fsm_state  <= IDLE;                                     
	             end                                                                    
	        endcase                                                                     
	    end                                                                             
	  end       

	// User logic ends

	endmodule
