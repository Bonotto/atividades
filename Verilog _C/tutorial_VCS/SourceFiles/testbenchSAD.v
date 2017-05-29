`timescale 1ns/10ps

module testbenchSAD;

   integer i;
   reg [127:0] e1, e2;
   wire [11:0] result;

   SAD SAD1 (
        .pA(e1),
        .pB(e2),
        .SAD(result));

   initial begin

      //Chamada da função em C
      $sad_monitor(testbenchSAD.e1, testbenchSAD.e2, testbenchSAD.result, testbenchSAD.i);

      //$monitor é utilizado  para imprimir no terminal qualquer alteração nos registradores e1 e e2.
      //%h é usado para que os valores sejam impressos em hexadecimal		
      $monitor("e1 = %h, e2 = %h", e1, e2);
      
      //O número de iterações do loop abaixo define
      //quantos vetores de entrada serão testados.		  	
      for (i = 0; i < 50; i = i+1)
   	begin
   	   #1;
   	end

      //$finish termina a simulação	
      $finish;
   end

endmodule
