
CC = gcc

C_FLAGS = -O0 -g -Wall
LD_FLAGS = -lwiringPi

all: ledtest blink swtest swtest_loop temp

%.o: %.c
	    gcc $(C_FLAGS) -c $< -o $@

ledtest: ledtest.o
	    gcc $(C_FLAGS) $(LD_FLAGS) ledtest.o -o $@

blink: blink.o
	    gcc $(C_FLAGS) $(LD_FLAGS) blink.o -o $@

swtest: swtest.o
	    gcc $(C_FLAGS) $(LD_FLAGS) swtest.o -o $@

swtest_loop: swtest_loop.o
	    gcc $(C_FLAGS) $(LD_FLAGS) swtest_loop.o -o $@

temp: temp.o
	    gcc $(C_FLAGS) $(LD_FLAGS) temp.o -o $@

clean:
	    -rm -f ledtest.o
	    -rm -f ledtest
	    -rm -f blink.o
	    -rm -f blink
	    -rm -f swtest.o
	    -rm -f swtest
	    -rm -f swtest_loop.o
	    -rm -f swtest_loop
	    -rm -f temp.o
	    -rm -f temp
