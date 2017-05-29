module counter

(
	input clk, rst, en,
	output counter
);

	reg [3:0] reg_counter;

	always @(posedge clk)
	begin
		if(rst)
		begin
			reg_counter <= 0;
		end
		else
		begin
			if(en)
			begin
				reg_counter <= reg_counter + 1;
			end
		end
	end

	assign counter = (reg_counter == 7)? 0 : 1;

endmodule