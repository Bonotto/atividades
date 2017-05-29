`timescale 100ps/1ps
module testbench;

	parameter TOTAL_EXECS = 10000;
	parameter H_CLK_PERIOD = 5;
	parameter CLK_PERIOD = H_CLK_PERIOD*2;
	parameter WIDTH = 8;
	reg [31:0] i, j;

	reg clk, rst, init, loaded, ack, end_sim;

	reg [WIDTH-1:0]
		ori_0,
		ori_1,
		ori_2,
		ori_3,
		can_0,
		can_1,
		can_2,
		can_3;

	wire done, load;

	wire [WIDTH+4:0] out_sad;

	top_level #(WIDTH) b_top(
		.clk(clk),
		.rst(rst),
		.init(init),
		.loaded(loaded),
		.ack(ack),
		.ori_0(ori_0),
		.ori_1(ori_1),
		.ori_2(ori_2),
		.ori_3(ori_3),
		.can_0(can_0),
		.can_1(can_1),
		.can_2(can_2),
		.can_3(can_3),
		.done(done),
		.load(load),
		.out_sad(out_sad)
	);

	always
		#H_CLK_PERIOD clk = !clk;

	initial
	begin: Test_Case

		clk = 0;
		rst = 0;
		init = 0;
		loaded = 0;
		end_sim = 0;
		ack = 0;

		$sad_monitor(testbench.loaded,
					 testbench.load,
					 testbench.ack,
					 testbench.done,
					 testbench.ori_0,
					 testbench.ori_1,
					 testbench.ori_2,
					 testbench.ori_3,
					 testbench.can_0,
					 testbench.can_1,
					 testbench.can_2,
					 testbench.can_3,
					 testbench.out_sad,
					 testbench.end_sim);

		$dumpfile("wave.vcd");
		$dumpvars;

		#CLK_PERIOD;

		@(negedge clk);
			rst = 1;
		@(negedge clk);
			rst = 0;

		#CLK_PERIOD;

		for(i = 0; i < TOTAL_EXECS; i=i+1)
		begin
				
			init = 1;

			ack = 0;

			#CLK_PERIOD;

			for(j = 0; j < 8; j=j+1)
			begin

				init = 0;

				wait(loaded);

				#CLK_PERIOD;

				loaded = 0;

				#CLK_PERIOD;

			end

			wait(ack);

			#CLK_PERIOD;

		end

		end_sim = 1;
		$finish;

	end

endmodule