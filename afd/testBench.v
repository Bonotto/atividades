module testBench;
	parameter TOTAL_EXECS = 100;
	parameter NUM_PARTITION = 1;

	parameter H_CLK_PERIOD = 5;
	parameter CLK_PERIOD = H_CLK_PERIOD*2;

	parameter WIDTH=8;


	reg [WIDTH-1:0] oriVector [TOTAL_EXECS*2 -1:0];
	reg [WIDTH-1:0] canVector [TOTAL_EXECS*2 -1:0];
	reg [WIDTH+7:0] ref_result [TOTAL_EXECS-1:0];

	reg [31:0] idx_file, idx_partition, idx_test;

	//input declarations as registers
	reg clk, rst, en, acum;
	reg [WIDTH-1:0] a0,a1;
	reg [WIDTH-1:0] b0,b1;

	//output declarations as wires;
	wire [WIDTH+7:0] out_afd;

	afd b_afd(
		.clk (clk),
		.rst (rst),
		.en (en),
		.acum(acum),

		.a0(a0),
		.b0(b0),
		.a1(a1),
		.b1(b1),

		.out_afd (out_afd)
	);
	initial $readmemh("./vector/can_hex.txt", canVector);
	initial $readmemh("./vector/ori_hex.txt", oriVector);
	initial $readmemh("./vector/result_hex.txt", ref_result);

	always
		#H_CLK_PERIOD clk = !clk;

	initial
	begin: Test_Case
		$dumpfile ("wave.vcd");
		$dumpvars;
		idx_test=0;
		idx_partition=0;
		idx_file=0;

		clk = 0;
		rst = 0;
		en = 0;
		acum = 0;
		
		a0 = 0;
		a1 = 0;
		b0 = 0;
		b1 = 0;

	#CLK_PERIOD
		@ (negedge clk); 
			rst = 1;
		@ (negedge clk); 
			rst = 0;

	#CLK_PERIOD
	forever
	begin
			//first element doesn't acumulate
		
		
		en = 1;
		acum = 0;
		a0 = canVector[(idx_file*2) + 0];
		a1 = canVector[(idx_file*2) + 1];
		b0 = oriVector[(idx_file*2) + 0];
		b1 = oriVector[(idx_file*2) + 1];
		
		idx_file = idx_file + 1;
		idx_partition = idx_partition + 1;

		#CLK_PERIOD;

		while(idx_partition<NUM_PARTITION) 
		begin

			en = 1;
			acum = 1;
			a0 = canVector[(idx_file*2) + 0];
			a1 = canVector[(idx_file*2) + 1];
			b0 = oriVector[(idx_file*2) + 0];
			b1 = oriVector[(idx_file*2) + 1];
			#CLK_PERIOD;
			idx_file = idx_file + 1;
			idx_partition = idx_partition + 1;
		end
		en = 0;
		acum = 0;
		#CLK_PERIOD;

		if(ref_result[idx_test]!=out_afd) begin
			$display("erro");
			$display("%d", idx_test);
			$display("value = (%d)", ref_result[idx_test]);
			$display("architecture value = (%d)\n", out_afd);
			$display("==========================");	
		end
		// else 
		// begin
		// 	$display("OK");
		// 	$display("%d", idx_test);
		// 	$display("value = (%d)", ref_result[idx_test]);
		// 	$display("architecture value = (%d)\n", out_afd);
		// 	$display("==========================");	
		// end
		#CLK_PERIOD;
		idx_test=idx_test+1;
		idx_partition=0;

		if(idx_test==TOTAL_EXECS)
			$finish;
		end
		#CLK_PERIOD; //on state afd
	end	
endmodule
