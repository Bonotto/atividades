module absolute_diff
#(parameter WIDTH=13)
(
	a,b,abs
 );
	input [WIDTH-1:0] a, b;
	wire signed[WIDTH:0] neg1, neg2;
	output  [WIDTH:0] abs;
	
	assign neg1 = a-b;
	assign neg2 = b-a;
	assign abs = (neg1 < 0)? neg2 : neg1;
endmodule	