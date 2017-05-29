module absolute
#(parameter WIDTH=13)
(
	in,abs
 );
 
	input signed[WIDTH-1:0] in;
	wire signed[WIDTH-1:0] neg;
	output  [WIDTH-1:0] abs;
	
	assign neg = -in;
	assign abs = (in < 0)? neg : in;
endmodule	