module teste;

  reg [9:0] valor;
  reg clk;

  assign valor = "1100110011";
  assign clk = '1';
  
  initial
  begin
    $SATD_monitor(teste.valor, teste.clk);
  end
  
endmodule