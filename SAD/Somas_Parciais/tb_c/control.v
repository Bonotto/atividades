module control

(
	input  clk, rst, init, loaded, counter, ack,
 	output rst_regs, en_regs_in, en_regs_acum, en_regs_out, done, load
);
	reg [3:0] state;
	reg reg_rst_regs, reg_en_regs_in, reg_en_regs_acum, reg_en_regs_out, reg_done, reg_load;

	parameter INIT = 0, LOAD = 1, CALC = 2, CALC_END = 3, DONE = 4;

	always @(state)
	begin
		case(state)

			INIT:
			begin
				reg_rst_regs = 1;
				reg_en_regs_in = 0;
				reg_en_regs_acum = 0;
				reg_en_regs_out = 0;
				reg_done = 0;
				reg_load = 0;
			end

			LOAD:
			begin
				reg_rst_regs = 0;
				reg_en_regs_in = 1;
				reg_en_regs_acum = 0;
				reg_en_regs_out = 0;
				reg_done = 0;
				reg_load = 1;
			end

			CALC:
			begin
				reg_rst_regs = 0;
				reg_en_regs_in = 0;
				reg_en_regs_acum = 1;
				reg_en_regs_out = 0;
				reg_done = 0;
				reg_load = 0;
			end

			CALC_END:
			begin
				reg_rst_regs = 0;
				reg_en_regs_in = 0;
				reg_en_regs_acum = 0;
				reg_en_regs_out = 1;
				reg_done = 0;
				reg_load = 0;
			end

			DONE:
			begin
				reg_rst_regs = 0;
				reg_en_regs_in = 0;
				reg_en_regs_acum = 0;
				reg_en_regs_out = 0;
				reg_done = 1;
				reg_load = 0;
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
					begin
						if(counter)
							state <= CALC;
						else
							state <= CALC_END;
					end
					else
					begin
						state <= LOAD;
					end
				end

				CALC:
				begin
					state <= LOAD;
				end

				CALC_END:
				begin
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

	assign rst_regs = reg_rst_regs;
	assign en_regs_in = reg_en_regs_in;
	assign en_regs_acum = reg_en_regs_acum;
	assign en_regs_out = reg_en_regs_out;
	assign done = reg_done;
	assign load = reg_load;

endmodule