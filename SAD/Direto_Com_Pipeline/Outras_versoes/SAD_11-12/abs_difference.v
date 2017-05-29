module abs_difference

#(parameter WIDTH = 8)

(ori, can, abs);

	input [WIDTH-1:0] ori, can;
	wire signed[WIDTH:0] neg1, neg2;
	output  [WIDTH-1:0] abs;
	
	assign neg1 = ori - can;
	assign neg2 = can - ori;
	assign abs = (neg1 < 0)? neg2[7:0] : neg1[7:0];
	
endmodule	