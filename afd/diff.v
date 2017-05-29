module diff
#(parameter WIDTH=8)
(a,b,d);

	input [WIDTH-1:0] a,b;
	output signed[WIDTH:0] d;
	
	assign d = a - b;

endmodule
