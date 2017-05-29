module top_level

#(parameter WIDTH = 8)

(
	input clk, rst, init, loaded, ack,
	input [WIDTH-1:0]
		ori_0,
		ori_1,
		ori_2,
		ori_3,
		can_0,
		can_1,
		can_2,
		can_3,
	output done, load,
	output [WIDTH+4:0] out_sad
	);

	wire rst_regs, en_regs_in, en_regs_acum, en_regs_out, counter;

	control b_control(
		.clk(clk),
		.rst(rst),
		.init(init),
		.loaded(loaded),
		.counter(counter),
		.ack(ack),
		.rst_regs(rst_regs),
		.en_regs_in(en_regs_in),
		.en_regs_acum(en_regs_acum),
		.en_regs_out(en_regs_out),
		.done(done),
		.load(load)
		);

	SAD b_SAD(
		.clk(clk),
		.rst(rst_regs),
		.en_in(en_regs_in),
		.en_acum(en_regs_acum),
		.en_out(en_regs_out),
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

	counter b_counter(
		.clk(clk),
		.rst(rst_regs),
		.en(en_regs_acum),
		.counter(counter)
		);

endmodule