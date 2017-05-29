module afd
#(parameter WIDTH=8)
(
 clk, rst, en, acum, a0,b0,a1,b1,
 out_afd
);
 	input clk, rst, en, acum;
	input [WIDTH-1:0] a0,b0,a1,b1;

	reg [WIDTH-1:0] reg_a0, reg_b0, reg_a1, reg_b1;
	reg reg_en_IN, reg_acum_IN;
	wire [WIDTH:0] abs0, abs1;
	wire [WIDTH+1:0] sum;
 	reg [WIDTH+4:0] reg_summation;

	output [WIDTH+7:0] out_afd;
	
	always @(posedge clk) 
	begin
		if(rst) 
		begin		
			reg_a0 <= 0;
			reg_b0 <= 0;
			reg_a1 <= 0;
			reg_b1 <= 0;
			reg_en_IN<=0;
			reg_acum_IN<=0;	
		end
		else 
		begin
			if( en )
			begin
				reg_a0 <= a0;
				reg_b0 <= b0;
				reg_a1 <= a1;
				reg_b1 <= b1;
				reg_acum_IN<=acum;
			end
				reg_en_IN<=en;
		end
	end
	
	absolute_diff #(WIDTH) b_abs0 (reg_a0, reg_b0, abs0);
	absolute_diff #(WIDTH) b_abs1 (reg_a1, reg_b1, abs1);

	assign sum = abs0 + abs1;

	always @(posedge clk) begin
		if(rst) 
		begin
			reg_summation = 0;
		end
		else 
		begin	
			if(reg_en_IN)
			begin
				if(reg_acum_IN)
					reg_summation = reg_summation + sum;
				else
					reg_summation = sum;			
			end			
		end
	end

assign out_afd[WIDTH+7:3] = reg_summation;
assign out_afd[2:0] = 0;
endmodule
