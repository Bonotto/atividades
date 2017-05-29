module top_level

#(parameter WIDTH = 8)

(
	input clk, rst, init, loaded, done, ack,
	input [WIDTH-1:0]
		ori_0,
		ori_1,
		ori_2,
		ori_3,
		can_0,
		can_1,
		can_2,
		can_3,
	output out_done,
	output [WIDTH+4:0] out_sad
	);

	wire rst_regs, en_sad;

	control b_control(
		.clk(clk),
		.rst(rst),
		.init(init),
		.loaded(loaded),
		.done(done),
		.ack(ack),
		.en_sad(en_sad),
		.out_done(out_done),
		.rst_sad(rst_regs)
		);

	SAD b_SAD(
		.clk(clk),
		.rst(rst_regs),
		.en(en_sad),
		.ori_0(ori_0),
		.ori_1(ori_1),
		.ori_2(ori_2),
		.ori_3(ori_3),
		.can_0(can_0),
		.can_1(can_1),
		.can_2(can_2),
		.can_3(can_3),
		.out_sad(out_sad)
		);

endmodule