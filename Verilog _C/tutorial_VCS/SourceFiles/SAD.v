module SAD

	(SAD, pA, pB);

	input[127:0] pA, pB;
	output [11:0] SAD;

	wire [7:0] valor_ABS[15:0];

	generate
		genvar i;
		for(i=0; i<=15; i=i+1)
		begin:
			gera_sad
			difAbs ABS (pA[ 8*i+7 : 8*i ], pB[ 8*i+7 : 8*i ], valor_ABS[i]);
		end
	endgenerate

	assign SAD = valor_ABS[0] +
				 valor_ABS[1] +
				 valor_ABS[2] +
				 valor_ABS[3] +
				 valor_ABS[4] +
				 valor_ABS[5] +
				 valor_ABS[6] +
				 valor_ABS[7] +
				 valor_ABS[8] +
				 valor_ABS[9] +
				 valor_ABS[10] +
				 valor_ABS[11] +
				 valor_ABS[12] +
				 valor_ABS[13] +
				 valor_ABS[14] +
				 valor_ABS[15];

endmodule
