# compile architecture
iverilog -g2005 -Wall -o test *.v

# compile c
g++ -std=c++11 Eliminacao_Gauss.cpp
# generate vectors
./a.out
# convert files to hex
(echo "obase=16" ; cat result.txt) | bc > ./vector/result_hex.txt
(echo "obase=16" ; cat can.txt) | bc > ./vector/can_hex.txt
(echo "obase=16" ; cat ori.txt) | bc > ./vector/ori_hex.txt

#execute tests
vvp test | tee logVVP.txt