//`timescale 100ps/1ps
module testbench;

	parameter TOTAL_EXECS = 1000;
	parameter H_CLK_PERIOD = 5;
	parameter CLK_PERIOD = H_CLK_PERIOD*2;
	parameter WIDTH = 8;

	reg [WIDTH-1:0] ori_vector [TOTAL_EXECS*32-1:0];
	reg [WIDTH-1:0] can_vector [TOTAL_EXECS*32-1:0];
	reg [WIDTH+4:0] ref_result [TOTAL_EXECS-1:0];
	reg [31:0] idx_file, i, j;

	reg clk, rst, init, loaded, done, ack;
	reg [WIDTH-1:0]
		ori_0,
		ori_1,
		ori_2,
		ori_3,
		can_0, 
		can_1,
		can_2,
		can_3;

	wire [WIDTH+4:0] out_sad;
	wire out_done;

	top_level #(WIDTH) b_top(
		.clk(clk),
		.rst(rst),
		.init(init),
		.loaded(loaded),
		.done(done),
		.ack(ack),
		.ori_0(ori_0),
		.ori_1(ori_1),
		.ori_2(ori_2),
		.ori_3(ori_3),
		.can_0(can_0),
		.can_1(can_1),
		.can_2(can_2),
		.can_3(can_3),
		.out_done(out_done),
		.out_sad(out_sad)
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

		clk = 0;
		rst = 0;
		init = 0;
		loaded = 0;
		done = 0;
		ack = 0;

		ori_0 = 0;
		ori_1 = 0;
		ori_2 = 0;
		ori_3 = 0;
		can_0 = 0;
		can_1 = 0;
		can_2 = 0;
		can_3 = 0;

		#CLK_PERIOD;

		@(negedge clk);
			rst = 1;
		@(negedge clk);
			rst = 0;

		#CLK_PERIOD;

		for(i = 0; i < TOTAL_EXECS; i++)
		begin
				
			init = 1;
			ack = 0;

			#CLK_PERIOD;

			for(j = 0; j < 8; j++)
			begin

				ori_0 = ori_vector[(idx_file*4) + 0];
				ori_1 = ori_vector[(idx_file*4) + 1];
				ori_2 = ori_vector[(idx_file*4) + 2];
				ori_3 = ori_vector[(idx_file*4) + 3];
				can_0 = can_vector[(idx_file*4) + 0];
				can_1 = can_vector[(idx_file*4) + 1];
				can_2 = can_vector[(idx_file*4) + 2];
				can_3 = can_vector[(idx_file*4) + 3];

				idx_file = idx_file + 1;

				loaded = 1;
				init = 0;

				#CLK_PERIOD;

				if (j == 7)
					done = 0;
				else
					done = 1;

				loaded = 0;

				#CLK_PERIOD;

				done = 0;

			end

			#CLK_PERIOD;
			
			ack = 1;

			#CLK_PERIOD;

			if (ref_result[i] != out_sad)
			begin
				$display("erro");
				$display("%d", i);
				$display("value_gen = (%d)", ref_result[i]);
				$display("value_arc = (%d)\n", out_sad);
				$display("==========================");
			end

		end

		$finish;

	end

endmodule