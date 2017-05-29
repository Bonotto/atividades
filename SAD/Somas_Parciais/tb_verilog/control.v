module control

(
	input  clk, rst, init, loaded, done, ack,
 	output en_sad, out_done, rst_sad
);

	reg [3:0] state;
	reg reg_en_sad, reg_out_done, reg_rst_sad;

	parameter INIT = 0, LOAD = 1, CALC = 2, DONE = 3;

	always @(state)
	begin
		case(state)

			INIT:
			begin
				reg_out_done = 0;
				reg_rst_sad = 1;
				reg_en_sad = 0;
			end

			LOAD:
			begin
				reg_out_done = 0;
				reg_rst_sad = 0;
				reg_en_sad = 1;
			end

			CALC:
			begin
				reg_out_done = 0;
				reg_rst_sad = 0;
				reg_en_sad = 0;
			end

			DONE:
			begin
				reg_out_done = 1;
				reg_rst_sad = 0;
				reg_en_sad = 1;
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
						state <= LOAD;
					else
						state <= INIT;
				end

				LOAD:
				begin
					if(loaded)
						state <= CALC;
					else
						state <= LOAD;
				end

				CALC:
				begin
					if(done)
						state <= LOAD;
					else
						state <= DONE;
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

	assign out_done = reg_out_done;
	assign rst_sad = reg_rst_sad;
	assign en_sad = reg_en_sad;

endmodule