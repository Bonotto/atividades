module control

(
	input  clk, rst, init, finish, ack,
 	output en, done, rst_sad
);

	reg [3:0] state;
	reg reg_en, reg_done, reg_rst_sad;

	parameter INIT = 0, CALC = 1, WAIT = 2, DONE = 3;

	always @(state)
	begin
		case(state)

			INIT:
			begin
				reg_rst_sad = 1;
				reg_done = 0;
				reg_en = 0;
			end

			CALC:
			begin
				reg_rst_sad = 0;
				reg_done = 0;
				reg_en = 1;
			end

			WAIT:
			begin
				reg_rst_sad = 0;
				reg_done = 0;
				reg_en = 1;
			end

			DONE:
			begin
				reg_rst_sad = 0;
				reg_done = 1;
				reg_en = 0;
			end
		endcase
	end

	always @(posedge clk or posedge rst)
	begin
		if(rst)
			state <= INIT;
		else
		begin
			case(state)
			
				INIT:
				begin
					if(init)
						state <= CALC;
					else
						state <= INIT;
				end

				CALC:
				begin
					if(init)
						state <= CALC;
					else
						state <= WAIT;
				end

				WAIT:
				begin
					if(finish)
						state <= DONE;
					else
						state <= WAIT;
				end

				DONE:
				begin
					if(ack)
						state <= INIT;
					else
						state <= DONE;
				end
			endcase
		end
	end

	assign rst_sad = reg_rst_sad;
	assign en = reg_en;
	assign done = reg_done;

endmodule