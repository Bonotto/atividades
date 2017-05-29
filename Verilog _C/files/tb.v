`timescale 100ps/1ps
`define H_PERIOD 2.38281251
`define TOTAL_SATDS 1000000
`define CYCLES_EACH_SATD 2
`define TIME_STEP 5

module testbenchSATD;

	time i;

	//input declarations as registers. And what about clock?
	reg clk;
	reg reset;
	reg init;
	reg ack;
	reg [7:0] a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15;
	reg [7:0] b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10 ,b11, b12, b13, b14, b15;

	//output declarations as wires;
	wire [15:0] result;
	wire done;
 
	//DUT port mapping
	SATD SATD_UV (
		.clk(clk),
		.reset(reset),
		.init(init),
		.ack(ack),
	
		.a0(a0),
		.a1(a1),
		.a2(a2),
		.a3(a3),
		.a4(a4),
		.a5(a5),
		.a6(a6),
		.a7(a7),
		.a8(a8),
		.a9(a9),
		.a10(a10),
		.a11(a11),
		.a12(a12),
		.a13(a13),
		.a14(a14),
		.a15(a15),

		.b0(b0),
		.b1(b1),
		.b2(b2),
		.b3(b3),
		.b4(b4),
		.b5(b5),
		.b6(b6),
		.b7(b7),
		.b8(b8),
		.b9(b9),
		.b10(b10),
		.b11(b11),
		.b12(b12),
		.b13(b13),
		.b14(b14),
		.b15(b15),

		.result(result),
	
		.done(done)
	);

always 
	#`H_PERIOD clk = !clk;

initial begin

	$set_gate_level_monitoring("on");
	$set_toggle_region(SATD_UV); 
	
	clk=0;	//initializing clock

	reset=1; //begin reseting the DUV

	init=0; //do not init yet

	ack=0; //


	a0=0;
	a1=0;
	a2=0;
	a3=0;
	a4=0;
	a5=0;
	a6=0;
	a7=0;
	a8=0;
	a9=0;
	a10=0;
	a11=0;
	a12=0;
	a13=0;
	a14=0;
	a15=0;

	b0=0;
	b1=0;
	b2=0;
	b3=0;
	b4=0;
	b5=0;
	b6=0;
	b7=0;
	b8=0;
	b9=0;
	b10=0;
	b11=0;
	b12=0;
	b13=0;
	b14=0;
	b15=0;
	
	#150
	
	reset=0;
	
	$SATD_monitor(testbenchSATD.init, testbenchSATD.a0, testbenchSATD.a1, testbenchSATD.a2, testbenchSATD.a3 , testbenchSATD.a4 , testbenchSATD.a5 , testbenchSATD.a6 , testbenchSATD.a7 , testbenchSATD.a8 , testbenchSATD.a9 , testbenchSATD.a10 , testbenchSATD.a11 , testbenchSATD.a12 , testbenchSATD.a13, testbenchSATD.a14 , testbenchSATD.a15, testbenchSATD.b0, testbenchSATD.b1, testbenchSATD.b2, testbenchSATD.b3 , testbenchSATD.b4 , testbenchSATD.b5 , testbenchSATD.b6 , testbenchSATD.b7 , testbenchSATD.b8 , testbenchSATD.b9 , testbenchSATD.b10 , testbenchSATD.b11 , testbenchSATD.b12 , testbenchSATD.b13, testbenchSATD.b14 , testbenchSATD.b15, testbenchSATD.ack, testbenchSATD.result, testbenchSATD.done, testbenchSATD.clk);
	//$monitor("%b, %d", testbenchSATD.done, testbenchSATD.result);

	//$monitor("e1 = %d, e2 = %d, e1 = %d, e2 = %d, e1 = %d, e2 = %d, e1 = %d, e2 = %d", e1[31:24], e2[31:24], e1[23:16], e2[23:16], e1[15:8], e2[15:8], e1[7:0], e2[7:0]);

	#50

	init=1;

	$toggle_start;

	ack=1;

	for (i=0; i < (2*`CYCLES_EACH_SATD*`H_PERIOD*`TOTAL_SATDS)/`TIME_STEP; i=i+1)
	begin
		#`TIME_STEP;
	end

	$toggle_stop;

	$toggle_report("output.saif", 0.00001, SATD_UV);

	$finish;

end

endmodule
