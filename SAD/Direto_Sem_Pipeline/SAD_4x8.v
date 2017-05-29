module SAD_4x8

#(parameter WIDTH = 8)

(
	input clk, rst, en,
	input [WIDTH-1:0]
		ori_0,
		ori_1,
		ori_2,
		ori_3,
		ori_4,
		ori_5,
		ori_6,
		ori_7,
		ori_8,
		ori_9,
		ori_10,
		ori_11,
		ori_12,
		ori_13,
		ori_14,
		ori_15,
		ori_16,
		ori_17,
		ori_18,
		ori_19,
		ori_20,
		ori_21,
		ori_22,
		ori_23,
		ori_24,
		ori_25,
		ori_26,
		ori_27,
		ori_28,
		ori_29,
		ori_30,
		ori_31,
		can_0,
		can_1,
		can_2,
		can_3,
		can_4,
		can_5,
		can_6,
		can_7,
		can_8,
		can_9,
		can_10,
		can_11,
		can_12,
		can_13,
		can_14,
		can_15,
		can_16,
		can_17,
		can_18,
		can_19,
		can_20,
		can_21,
		can_22,
		can_23,
		can_24,
		can_25,
		can_26,
		can_27,
		can_28,
		can_29,
		can_30,
		can_31,
	output [WIDTH+4:0] out_sad
 );

	reg [WIDTH-1:0] reg_ori_0,
					reg_ori_1,
					reg_ori_2,
					reg_ori_3,
					reg_ori_4,
					reg_ori_5,
					reg_ori_6,
					reg_ori_7,
					reg_ori_8,
					reg_ori_9,
					reg_ori_10,
					reg_ori_11,
					reg_ori_12,
					reg_ori_13,
					reg_ori_14,
					reg_ori_15,
					reg_ori_16,
					reg_ori_17,
					reg_ori_18,
					reg_ori_19,
					reg_ori_20,
					reg_ori_21,
					reg_ori_22,
					reg_ori_23,
					reg_ori_24,
					reg_ori_25,
					reg_ori_26,
					reg_ori_27,
					reg_ori_28,
					reg_ori_29,
					reg_ori_30,
					reg_ori_31,
					reg_can_0,
					reg_can_1,
					reg_can_2,
					reg_can_3,
					reg_can_4,
					reg_can_5,
					reg_can_6,
					reg_can_7,
					reg_can_8,
					reg_can_9,
					reg_can_10,
					reg_can_11,
					reg_can_12,
					reg_can_13,
					reg_can_14,
					reg_can_15,
					reg_can_16,
					reg_can_17,
					reg_can_18,
					reg_can_19,
					reg_can_20,
					reg_can_21,
					reg_can_22,
					reg_can_23,
					reg_can_24,
					reg_can_25,
					reg_can_26,
					reg_can_27,
					reg_can_28,
					reg_can_29,
					reg_can_30,
					reg_can_31;

	reg [WIDTH+4:0] reg_total_sum;

	reg reg_en;

	wire [WIDTH+4:0] sum;

	wire [WIDTH-1:0] abs_diff_0,
					 abs_diff_1,
					 abs_diff_2,
					 abs_diff_3,
					 abs_diff_4,
					 abs_diff_5,
					 abs_diff_6,
					 abs_diff_7,
					 abs_diff_8,
					 abs_diff_9,
		 			 abs_diff_10,
		 			 abs_diff_11,
		 			 abs_diff_12,
		 			 abs_diff_13,
					 abs_diff_14,
					 abs_diff_15,
					 abs_diff_16,
					 abs_diff_17,
					 abs_diff_18,
					 abs_diff_19,
					 abs_diff_20,
					 abs_diff_21,
					 abs_diff_22,
					 abs_diff_23,
					 abs_diff_24,
					 abs_diff_25,
					 abs_diff_26,
					 abs_diff_27,
					 abs_diff_28,
					 abs_diff_29,
					 abs_diff_30,
					 abs_diff_31;

	always @(posedge clk)
	begin
		if(rst)
		begin
			reg_ori_0 <= 0;
			reg_ori_1 <= 0;
			reg_ori_2 <= 0;
			reg_ori_3 <= 0;
			reg_ori_4 <= 0;
			reg_ori_5 <= 0;
			reg_ori_6 <= 0;
			reg_ori_7 <= 0;
			reg_ori_8 <= 0;
			reg_ori_9 <= 0;
			reg_ori_10 <= 0;
			reg_ori_11 <= 0;
			reg_ori_12 <= 0;
			reg_ori_13 <= 0;
			reg_ori_14 <= 0;
			reg_ori_15 <= 0;
			reg_ori_16 <= 0;
			reg_ori_17 <= 0;
			reg_ori_18 <= 0;
			reg_ori_19 <= 0;
			reg_ori_20 <= 0;
			reg_ori_21 <= 0;
			reg_ori_22 <= 0;
			reg_ori_23 <= 0;
			reg_ori_24 <= 0;
			reg_ori_25 <= 0;
			reg_ori_26 <= 0;
			reg_ori_27 <= 0;
			reg_ori_28 <= 0;
			reg_ori_29 <= 0;
			reg_ori_30 <= 0;
			reg_ori_31 <= 0;
			reg_can_0 <= 0;
			reg_can_1 <= 0;
			reg_can_2 <= 0;
			reg_can_3 <= 0;
			reg_can_4 <= 0;
			reg_can_5 <= 0;
			reg_can_6 <= 0;
			reg_can_7 <= 0;
			reg_can_8 <= 0;
			reg_can_9 <= 0;
			reg_can_10 <= 0;
			reg_can_11 <= 0;
			reg_can_12 <= 0;
			reg_can_13 <= 0;
			reg_can_14 <= 0;
			reg_can_15 <= 0;
			reg_can_16 <= 0;
			reg_can_17 <= 0;
			reg_can_18 <= 0;
			reg_can_19 <= 0;
			reg_can_20 <= 0;
			reg_can_21 <= 0;
			reg_can_22 <= 0;
			reg_can_23 <= 0;
			reg_can_24 <= 0;
			reg_can_25 <= 0;
			reg_can_26 <= 0;
			reg_can_27 <= 0;
			reg_can_28 <= 0;
			reg_can_29 <= 0;
			reg_can_30 <= 0;
			reg_can_31 <= 0;
			reg_en <= 0;			
		end
		else
		begin
			if(en)
			begin
				reg_ori_0 <= ori_0;
				reg_ori_1 <= ori_1;
				reg_ori_2 <= ori_2;
				reg_ori_3 <= ori_3;
				reg_ori_4 <= ori_4;
				reg_ori_5 <= ori_5;
				reg_ori_6 <= ori_6;
				reg_ori_7 <= ori_7;
				reg_ori_8 <= ori_8;
				reg_ori_9 <= ori_9;
				reg_ori_10 <= ori_10;
				reg_ori_11 <= ori_11;
				reg_ori_12 <= ori_12;
				reg_ori_13 <= ori_13;
				reg_ori_14 <= ori_14;
				reg_ori_15 <= ori_15;
				reg_ori_16 <= ori_16;
				reg_ori_17 <= ori_17;
				reg_ori_18 <= ori_18;
				reg_ori_19 <= ori_19;
				reg_ori_20 <= ori_20;
				reg_ori_21 <= ori_21;
				reg_ori_22 <= ori_22;
				reg_ori_23 <= ori_23;
				reg_ori_24 <= ori_24;
				reg_ori_25 <= ori_25;
				reg_ori_26 <= ori_26;
				reg_ori_27 <= ori_27;
				reg_ori_28 <= ori_28;
				reg_ori_29 <= ori_29;
				reg_ori_30 <= ori_30;
				reg_ori_31 <= ori_31;
				reg_can_0 <= can_0;
				reg_can_1 <= can_1;
				reg_can_2 <= can_2;
				reg_can_3 <= can_3;
				reg_can_4 <= can_4;
				reg_can_5 <= can_5;
				reg_can_6 <= can_6;
				reg_can_7 <= can_7;
				reg_can_8 <= can_8;
				reg_can_9 <= can_9;
				reg_can_10 <= can_10;
				reg_can_11 <= can_11;
				reg_can_12 <= can_12;
				reg_can_13 <= can_13;
				reg_can_14 <= can_14;
				reg_can_15 <= can_15;
				reg_can_16 <= can_16;
				reg_can_17 <= can_17;
				reg_can_18 <= can_18;
				reg_can_19 <= can_19;
				reg_can_20 <= can_20;
				reg_can_21 <= can_21;
				reg_can_22 <= can_22;
				reg_can_23 <= can_23;
				reg_can_24 <= can_24;
				reg_can_25 <= can_25;
				reg_can_26 <= can_26;
				reg_can_27 <= can_27;
				reg_can_28 <= can_28;
				reg_can_29 <= can_29;
				reg_can_30 <= can_30;
				reg_can_31 <= can_31;
			end
			reg_en <= en;
		end
	end

	abs_difference #(WIDTH) b_abs_diff_0 (reg_ori_0, reg_can_0, abs_diff_0);
	abs_difference #(WIDTH) b_abs_diff_1 (reg_ori_1, reg_can_1, abs_diff_1);
	abs_difference #(WIDTH) b_abs_diff_2 (reg_ori_2, reg_can_2, abs_diff_2);
	abs_difference #(WIDTH) b_abs_diff_3 (reg_ori_3, reg_can_3, abs_diff_3);
	abs_difference #(WIDTH) b_abs_diff_4 (reg_ori_4, reg_can_4, abs_diff_4);
	abs_difference #(WIDTH) b_abs_diff_5 (reg_ori_5, reg_can_5, abs_diff_5);
	abs_difference #(WIDTH) b_abs_diff_6 (reg_ori_6, reg_can_6, abs_diff_6);
	abs_difference #(WIDTH) b_abs_diff_7 (reg_ori_7, reg_can_7, abs_diff_7);
	abs_difference #(WIDTH) b_abs_diff_8 (reg_ori_8, reg_can_8, abs_diff_8);
	abs_difference #(WIDTH) b_abs_diff_9 (reg_ori_9, reg_can_9, abs_diff_9);
	abs_difference #(WIDTH) b_abs_diff_10 (reg_ori_10, reg_can_10, abs_diff_10);
	abs_difference #(WIDTH) b_abs_diff_11 (reg_ori_11, reg_can_11, abs_diff_11);
	abs_difference #(WIDTH) b_abs_diff_12 (reg_ori_12, reg_can_12, abs_diff_12);
	abs_difference #(WIDTH) b_abs_diff_13 (reg_ori_13, reg_can_13, abs_diff_13);
	abs_difference #(WIDTH) b_abs_diff_14 (reg_ori_14, reg_can_14, abs_diff_14);
	abs_difference #(WIDTH) b_abs_diff_15 (reg_ori_15, reg_can_15, abs_diff_15);
	abs_difference #(WIDTH) b_abs_diff_16 (reg_ori_16, reg_can_16, abs_diff_16);
	abs_difference #(WIDTH) b_abs_diff_17 (reg_ori_17, reg_can_17, abs_diff_17);
	abs_difference #(WIDTH) b_abs_diff_18 (reg_ori_18, reg_can_18, abs_diff_18);
	abs_difference #(WIDTH) b_abs_diff_19 (reg_ori_19, reg_can_19, abs_diff_19);
	abs_difference #(WIDTH) b_abs_diff_20 (reg_ori_20, reg_can_20, abs_diff_20);
	abs_difference #(WIDTH) b_abs_diff_21 (reg_ori_21, reg_can_21, abs_diff_21);
	abs_difference #(WIDTH) b_abs_diff_22 (reg_ori_22, reg_can_22, abs_diff_22);
	abs_difference #(WIDTH) b_abs_diff_23 (reg_ori_23, reg_can_23, abs_diff_23);
	abs_difference #(WIDTH) b_abs_diff_24 (reg_ori_24, reg_can_24, abs_diff_24);
	abs_difference #(WIDTH) b_abs_diff_25 (reg_ori_25, reg_can_25, abs_diff_25);
	abs_difference #(WIDTH) b_abs_diff_26 (reg_ori_26, reg_can_26, abs_diff_26);
	abs_difference #(WIDTH) b_abs_diff_27 (reg_ori_27, reg_can_27, abs_diff_27);
	abs_difference #(WIDTH) b_abs_diff_28 (reg_ori_28, reg_can_28, abs_diff_28);
	abs_difference #(WIDTH) b_abs_diff_29 (reg_ori_29, reg_can_29, abs_diff_29);
	abs_difference #(WIDTH) b_abs_diff_30 (reg_ori_30, reg_can_30, abs_diff_30);
	abs_difference #(WIDTH) b_abs_diff_31 (reg_ori_31, reg_can_31, abs_diff_31);

	assign sum = abs_diff_0 +
				 abs_diff_1 +
				 abs_diff_2 +
				 abs_diff_3 +
				 abs_diff_4 +
				 abs_diff_5 +
				 abs_diff_6 +
				 abs_diff_7 +
				 abs_diff_8 +
				 abs_diff_9 +
				 abs_diff_10 +
				 abs_diff_11 +
				 abs_diff_12 +
				 abs_diff_13 +
				 abs_diff_14 +
				 abs_diff_15 +
				 abs_diff_16 +
				 abs_diff_17 +
				 abs_diff_18 +
				 abs_diff_19 +
				 abs_diff_20 +
				 abs_diff_21 +
				 abs_diff_22 +
				 abs_diff_23 +
				 abs_diff_24 +
				 abs_diff_25 +
				 abs_diff_26 +
				 abs_diff_27 +
				 abs_diff_28 +
				 abs_diff_29 +
				 abs_diff_30 +
				 abs_diff_31;

	always @(posedge clk)
	begin
		if(rst)
		begin
			reg_total_sum <= 0;
		end
		else
		begin
			if(reg_en)
				reg_total_sum <= sum;
		end
	end

	assign out_sad = reg_total_sum;

endmodule