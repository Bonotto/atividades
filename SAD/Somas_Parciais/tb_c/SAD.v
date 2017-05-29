module SAD

	#(parameter WIDTH = 8)

	(
	input clk, rst, en_in, en_acum, en_out,
	input [WIDTH-1:0]
		ori_0,
		ori_1,
		ori_2,
		ori_3,
		can_0,
		can_1,
		can_2,
		can_3,
	output [WIDTH+4:0] out_sad
	);

	reg [WIDTH-1:0] reg_ori_0,
					reg_ori_1,
					reg_ori_2,
					reg_ori_3,
					reg_can_0,
					reg_can_1,
					reg_can_2,
					reg_can_3;

	reg [WIDTH+4:0] reg_sum, reg_total_sum;

	wire [WIDTH+1:0] sum;

	wire [WIDTH-1:0] abs_diff_0,
					 abs_diff_1,
					 abs_diff_2,
					 abs_diff_3;

	always @(posedge clk)
	begin
		if(rst)
		begin
			reg_ori_0 <= 0;
			reg_ori_1 <= 0;
			reg_ori_2 <= 0;
			reg_ori_3 <= 0;
			reg_can_0 <= 0;
			reg_can_1 <= 0;
			reg_can_2 <= 0;
			reg_can_3 <= 0;		
		end
		else
		begin
			if(en_in)
			begin
				reg_ori_0 <= ori_0;
				reg_ori_1 <= ori_1;
				reg_ori_2 <= ori_2;
				reg_ori_3 <= ori_3;
				reg_can_0 <= can_0;
				reg_can_1 <= can_1;
				reg_can_2 <= can_2;
				reg_can_3 <= can_3;
			end
		end
	end

	abs_difference #(WIDTH) b_abs_diff_0 (reg_ori_0, reg_can_0, abs_diff_0);
	abs_difference #(WIDTH) b_abs_diff_1 (reg_ori_1, reg_can_1, abs_diff_1);
	abs_difference #(WIDTH) b_abs_diff_2 (reg_ori_2, reg_can_2, abs_diff_2);
	abs_difference #(WIDTH) b_abs_diff_3 (reg_ori_3, reg_can_3, abs_diff_3);

	assign sum = abs_diff_0 +
				 abs_diff_1 +
				 abs_diff_2 +
				 abs_diff_3;

	always @(posedge clk)
	begin
		if(rst)
		begin
			reg_sum <= 0;
		end
		else
		begin
			if(en_acum)
			begin
				reg_sum <= reg_sum + sum;
			end
		end
	end

	always @(posedge clk)
	begin
		if(rst)
		begin
			reg_total_sum <= 0;
		end
		else
		begin
			if(en_out)
			begin
				reg_total_sum <= reg_sum + sum;
			end
		end
	end

	assign out_sad = reg_total_sum;

endmodule