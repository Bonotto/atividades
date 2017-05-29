module difAbs

	(a, b, difABS);

	input[7:0] a, b;
	output [7:0] difABS;

	wire [7:0] 	dif, negDif, difAbsComp;

	assign dif = a - b;
	assign negDif = -dif;
	assign difAbsComp = (a < b) ? negDif : dif ;
	assign difABS = difAbsComp[7:0];

endmodule
