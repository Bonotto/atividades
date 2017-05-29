module testBench;
	parameter TOTAL_EXECS = 1000;
	parameter H_CLK_PERIOD = 5;
	parameter CLK_PERIOD = H_CLK_PERIOD*2;
	parameter WIDTH = 8;

	reg [WIDTH-1:0] ori_vector [TOTAL_EXECS*32-1:0];
	reg [WIDTH-1:0] can_vector [TOTAL_EXECS*32-1:0];
	reg [WIDTH+4:0] ref_result [TOTAL_EXECS-1:0];
	reg [31:0] idx_file, idx_result, i;

	reg clk, rst, init, finish, ack;
	reg [WIDTH-1:0]
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
		can_31;

	wire [WIDTH+4:0] out_sad;
	wire done;

	top_level #(WIDTH) b_top(
		.clk(clk),
		.rst(rst),
		.init(init),
		.finish(finish),
		.ack(ack),
		.ori_0(ori_0),
		.ori_1(ori_1),
		.ori_2(ori_2),
		.ori_3(ori_3),
		.ori_4(ori_4),
		.ori_5(ori_5),
		.ori_6(ori_6),
		.ori_7(ori_7),
		.ori_8(ori_8),
		.ori_9(ori_9),
		.ori_10(ori_10),
		.ori_11(ori_11),
		.ori_12(ori_12),
		.ori_13(ori_13),
		.ori_14(ori_14),
		.ori_15(ori_15),
		.ori_16(ori_16),
		.ori_17(ori_17),
		.ori_18(ori_18),
		.ori_19(ori_19),
		.ori_20(ori_20),
		.ori_21(ori_21),
		.ori_22(ori_22),
		.ori_23(ori_23),
		.ori_24(ori_24),
		.ori_25(ori_25),
		.ori_26(ori_26),
		.ori_27(ori_27),
		.ori_28(ori_28),
		.ori_29(ori_29),
		.ori_30(ori_30),
		.ori_31(ori_31),
		.can_0(can_0),
		.can_1(can_1),
		.can_2(can_2),
		.can_3(can_3),
		.can_4(can_4),
		.can_5(can_5),
		.can_6(can_6),
		.can_7(can_7),
		.can_8(can_8),
		.can_9(can_9),
		.can_10(can_10),
		.can_11(can_11),
		.can_12(can_12),
		.can_13(can_13),
		.can_14(can_14),
		.can_15(can_15),
		.can_16(can_16),
		.can_17(can_17),
		.can_18(can_18),
		.can_19(can_19),
		.can_20(can_20),
		.can_21(can_21),
		.can_22(can_22),
		.can_23(can_23),
		.can_24(can_24),
		.can_25(can_25),
		.can_26(can_26),
		.can_27(can_27),
		.can_28(can_28),
		.can_29(can_29),
		.can_30(can_30),
		.can_31(can_31),
		.out_sad(out_sad),
		.done(done)
	);

	initial $readmemh("./vector/can_hex.txt", can_vector);
	initial $readmemh("./vector/ori_hex.txt", ori_vector);
	initial $readmemh("./vector/result_hex.txt", ref_result);

	always
		#H_CLK_PERIOD clk = !clk;

	initial
		begin: Test_Case

			$dumpfile("wave.vcd");
			$dumpvars;

			idx_file = 0;
			idx_result = 0;

			clk = 0;
			rst = 0;
			init = 0;
			ack = 0;

			ori_0 = 0;
			ori_1 = 0;
			ori_2 = 0;
			ori_3 = 0;
			ori_4 = 0;
			ori_5 = 0;
			ori_6 = 0;
			ori_7 = 0;
			ori_8 = 0;
			ori_9 = 0;
			ori_10 = 0;
			ori_11 = 0;
			ori_12 = 0;
			ori_13 = 0;
			ori_14 = 0;
			ori_15 = 0;
			ori_16 = 0;
			ori_17 = 0;
			ori_18 = 0;
			ori_19 = 0;
			ori_20 = 0;
			ori_21 = 0;
			ori_22 = 0;
			ori_23 = 0;
			ori_24 = 0;
			ori_25 = 0;
			ori_26 = 0;
			ori_27 = 0;
			ori_28 = 0;
			ori_29 = 0;
			ori_30 = 0;
			ori_31 = 0;
			can_0 = 0;
			can_1 = 0;
			can_2 = 0;
			can_3 = 0;
			can_4 = 0;
			can_5 = 0;
			can_6 = 0;
			can_7 = 0;
			can_8 = 0;
			can_9 = 0;
			can_10 = 0;
			can_11 = 0;
			can_12 = 0;
			can_13 = 0;
			can_14 = 0;
			can_15 = 0;
			can_16 = 0;
			can_17 = 0;
			can_18 = 0;
			can_19 = 0;
			can_20 = 0;
			can_21 = 0;
			can_22 = 0;
			can_23 = 0;
			can_24 = 0;
			can_25 = 0;
			can_26 = 0;
			can_27 = 0;
			can_28 = 0;
			can_29 = 0;
			can_30 = 0;
			can_31 = 0;

	#CLK_PERIOD;

		@(negedge clk);
			rst = 1;
		@(negedge clk);
			rst = 0;

	#CLK_PERIOD;
		
		init = 1;
		finish = 0;
		ack = 0;

	#CLK_PERIOD;

	for(i = 0; i <= 2; i++)
		begin

		can_0 = can_vector[(idx_file*32) + 0];
		can_1 = can_vector[(idx_file*32) + 1];
		can_2 = can_vector[(idx_file*32) + 2];
		can_3 = can_vector[(idx_file*32) + 3];
		can_4 = can_vector[(idx_file*32) + 4];
		can_5 = can_vector[(idx_file*32) + 5];
		can_6 = can_vector[(idx_file*32) + 6];
		can_7 = can_vector[(idx_file*32) + 7];
		can_8 = can_vector[(idx_file*32) + 8];
		can_9 = can_vector[(idx_file*32) + 9];
		can_10 = can_vector[(idx_file*32) + 10];
		can_11 = can_vector[(idx_file*32) + 11];
		can_12 = can_vector[(idx_file*32) + 12];
		can_13 = can_vector[(idx_file*32) + 13];
		can_14 = can_vector[(idx_file*32) + 14];
		can_15 = can_vector[(idx_file*32) + 15];
		can_16 = can_vector[(idx_file*32) + 16];
		can_17 = can_vector[(idx_file*32) + 17];
		can_18 = can_vector[(idx_file*32) + 18];
		can_19 = can_vector[(idx_file*32) + 19];
		can_20 = can_vector[(idx_file*32) + 20];
		can_21 = can_vector[(idx_file*32) + 21];
		can_22 = can_vector[(idx_file*32) + 22];
		can_23 = can_vector[(idx_file*32) + 23];
		can_24 = can_vector[(idx_file*32) + 24];
		can_25 = can_vector[(idx_file*32) + 25];
		can_26 = can_vector[(idx_file*32) + 26];
		can_27 = can_vector[(idx_file*32) + 27];
		can_28 = can_vector[(idx_file*32) + 28];
		can_29 = can_vector[(idx_file*32) + 29];
		can_30 = can_vector[(idx_file*32) + 30];
		can_31 = can_vector[(idx_file*32) + 31];
		ori_0 = ori_vector[(idx_file*32) + 0];
		ori_1 = ori_vector[(idx_file*32) + 1];
		ori_2 = ori_vector[(idx_file*32) + 2];
		ori_3 = ori_vector[(idx_file*32) + 3];
		ori_4 = ori_vector[(idx_file*32) + 4];
		ori_5 = ori_vector[(idx_file*32) + 5];
		ori_6 = ori_vector[(idx_file*32) + 6];
		ori_7 = ori_vector[(idx_file*32) + 7];
		ori_8 = ori_vector[(idx_file*32) + 8];
		ori_9 = ori_vector[(idx_file*32) + 9];
		ori_10 = ori_vector[(idx_file*32) + 10];
		ori_11 = ori_vector[(idx_file*32) + 11];
		ori_12 = ori_vector[(idx_file*32) + 12];
		ori_13 = ori_vector[(idx_file*32) + 13];
		ori_14 = ori_vector[(idx_file*32) + 14];
		ori_15 = ori_vector[(idx_file*32) + 15];
		ori_16 = ori_vector[(idx_file*32) + 16];
		ori_17 = ori_vector[(idx_file*32) + 17];
		ori_18 = ori_vector[(idx_file*32) + 18];
		ori_19 = ori_vector[(idx_file*32) + 19];
		ori_20 = ori_vector[(idx_file*32) + 20];
		ori_21 = ori_vector[(idx_file*32) + 21];
		ori_22 = ori_vector[(idx_file*32) + 22];
		ori_23 = ori_vector[(idx_file*32) + 23];
		ori_24 = ori_vector[(idx_file*32) + 24];
		ori_25 = ori_vector[(idx_file*32) + 25];
		ori_26 = ori_vector[(idx_file*32) + 26];
		ori_27 = ori_vector[(idx_file*32) + 27];
		ori_28 = ori_vector[(idx_file*32) + 28];
		ori_29 = ori_vector[(idx_file*32) + 29];
		ori_30 = ori_vector[(idx_file*32) + 30];
		ori_31 = ori_vector[(idx_file*32) + 31];
		
		#CLK_PERIOD;

		idx_file = idx_file + 1;

	end

	forever
	begin

		can_0 = can_vector[(idx_file*32) + 0];
		can_1 = can_vector[(idx_file*32) + 1];
		can_2 = can_vector[(idx_file*32) + 2];
		can_3 = can_vector[(idx_file*32) + 3];
		can_4 = can_vector[(idx_file*32) + 4];
		can_5 = can_vector[(idx_file*32) + 5];
		can_6 = can_vector[(idx_file*32) + 6];
		can_7 = can_vector[(idx_file*32) + 7];
		can_8 = can_vector[(idx_file*32) + 8];
		can_9 = can_vector[(idx_file*32) + 9];
		can_10 = can_vector[(idx_file*32) + 10];
		can_11 = can_vector[(idx_file*32) + 11];
		can_12 = can_vector[(idx_file*32) + 12];
		can_13 = can_vector[(idx_file*32) + 13];
		can_14 = can_vector[(idx_file*32) + 14];
		can_15 = can_vector[(idx_file*32) + 15];
		can_16 = can_vector[(idx_file*32) + 16];
		can_17 = can_vector[(idx_file*32) + 17];
		can_18 = can_vector[(idx_file*32) + 18];
		can_19 = can_vector[(idx_file*32) + 19];
		can_20 = can_vector[(idx_file*32) + 20];
		can_21 = can_vector[(idx_file*32) + 21];
		can_22 = can_vector[(idx_file*32) + 22];
		can_23 = can_vector[(idx_file*32) + 23];
		can_24 = can_vector[(idx_file*32) + 24];
		can_25 = can_vector[(idx_file*32) + 25];
		can_26 = can_vector[(idx_file*32) + 26];
		can_27 = can_vector[(idx_file*32) + 27];
		can_28 = can_vector[(idx_file*32) + 28];
		can_29 = can_vector[(idx_file*32) + 29];
		can_30 = can_vector[(idx_file*32) + 30];
		can_31 = can_vector[(idx_file*32) + 31];
		ori_0 = ori_vector[(idx_file*32) + 0];
		ori_1 = ori_vector[(idx_file*32) + 1];
		ori_2 = ori_vector[(idx_file*32) + 2];
		ori_3 = ori_vector[(idx_file*32) + 3];
		ori_4 = ori_vector[(idx_file*32) + 4];
		ori_5 = ori_vector[(idx_file*32) + 5];
		ori_6 = ori_vector[(idx_file*32) + 6];
		ori_7 = ori_vector[(idx_file*32) + 7];
		ori_8 = ori_vector[(idx_file*32) + 8];
		ori_9 = ori_vector[(idx_file*32) + 9];
		ori_10 = ori_vector[(idx_file*32) + 10];
		ori_11 = ori_vector[(idx_file*32) + 11];
		ori_12 = ori_vector[(idx_file*32) + 12];
		ori_13 = ori_vector[(idx_file*32) + 13];
		ori_14 = ori_vector[(idx_file*32) + 14];
		ori_15 = ori_vector[(idx_file*32) + 15];
		ori_16 = ori_vector[(idx_file*32) + 16];
		ori_17 = ori_vector[(idx_file*32) + 17];
		ori_18 = ori_vector[(idx_file*32) + 18];
		ori_19 = ori_vector[(idx_file*32) + 19];
		ori_20 = ori_vector[(idx_file*32) + 20];
		ori_21 = ori_vector[(idx_file*32) + 21];
		ori_22 = ori_vector[(idx_file*32) + 22];
		ori_23 = ori_vector[(idx_file*32) + 23];
		ori_24 = ori_vector[(idx_file*32) + 24];
		ori_25 = ori_vector[(idx_file*32) + 25];
		ori_26 = ori_vector[(idx_file*32) + 26];
		ori_27 = ori_vector[(idx_file*32) + 27];
		ori_28 = ori_vector[(idx_file*32) + 28];
		ori_29 = ori_vector[(idx_file*32) + 29];
		ori_30 = ori_vector[(idx_file*32) + 30];
		ori_31 = ori_vector[(idx_file*32) + 31];

		//if(ref_result[idx_result] != out_sad)
		//begin
			$display("erro");
			$display("%d", idx_result);
			$display("value = (%d)", ref_result[idx_result]);
			$display("architecture value = (%d)\n", out_sad);
			$display("==========================");
		//end

		if(idx_file == TOTAL_EXECS)
			$finish;

		#CLK_PERIOD;
		
		idx_file = idx_file + 1;
		idx_result = idx_result + 1;

	end

	end

endmodule