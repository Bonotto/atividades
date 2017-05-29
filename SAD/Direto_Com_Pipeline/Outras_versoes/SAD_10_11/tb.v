`timescale 100ps/1ps
module testbench;

	parameter TOTAL_EXECS = 1000;
	parameter H_CLK_PERIOD = 5;
	parameter CLK_PERIOD = H_CLK_PERIOD*2;
	parameter WIDTH = 8;

	integer i;
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

	always
		#H_CLK_PERIOD clk = !clk;

	initial
	begin
		
		$sad_monitor(testbench.i,
					 testbench.ori_0,
					 testbench.ori_1,
					 testbench.ori_2,
					 testbench.ori_3,
					 testbench.ori_4,
					 testbench.ori_5,
					 testbench.ori_6,
					 testbench.ori_7,
					 testbench.ori_8,
					 testbench.ori_9,
					 testbench.ori_10,
					 testbench.ori_11,
					 testbench.ori_12,
					 testbench.ori_13,
					 testbench.ori_14,
					 testbench.ori_15,
					 testbench.ori_16,
					 testbench.ori_17,
					 testbench.ori_18,
					 testbench.ori_19,
					 testbench.ori_20,
					 testbench.ori_21,
					 testbench.ori_22,
					 testbench.ori_23,
					 testbench.ori_24,
					 testbench.ori_25,
					 testbench.ori_26,
					 testbench.ori_27,
					 testbench.ori_28,
					 testbench.ori_29,
					 testbench.ori_30,
					 testbench.ori_31,
					 testbench.can_0,
					 testbench.can_1,
					 testbench.can_2,
					 testbench.can_3,
					 testbench.can_4,
					 testbench.can_5,
					 testbench.can_6,
					 testbench.can_7,
					 testbench.can_8,
					 testbench.can_9,
					 testbench.can_10,
					 testbench.can_11,
					 testbench.can_12,
					 testbench.can_13,
					 testbench.can_14,
					 testbench.can_15,
					 testbench.can_16,
					 testbench.can_17,
					 testbench.can_18,
					 testbench.can_19,
					 testbench.can_20,
					 testbench.can_21,
					 testbench.can_22,
					 testbench.can_23,
					 testbench.can_24,
					 testbench.can_25,
					 testbench.can_26,
					 testbench.can_27,
					 testbench.can_28,
					 testbench.can_29,
					 testbench.can_30,
					 testbench.can_31,
					 testbench.out_sad);

		$dumpfile("wave.vcd");
		$dumpvars;

   		clk = 0;
		rst = 0;
		init = 0;
		ack = 0;
		finish = 0;

		#CLK_PERIOD;

		@(negedge clk);
			rst = 1;
		@(negedge clk);
			rst = 0;

		#CLK_PERIOD;

		init = 1;

		#CLK_PERIOD;

	    for (i = 0; i < TOTAL_EXECS; i = i + 1)
	   	begin
	   		#CLK_PERIOD;
	   	end

		$finish;

	end

endmodule