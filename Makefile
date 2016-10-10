#
# 	CAB202
#	Generic Makefile for compiling with floating point printf
#
#	B.Talbot, September 2015
#	Queensland University of Technology
#

# Modify these
SRC=main

# The rest should be all good as is
FLAGS=-mmcu=atmega32u4 -Os -DF_CPU=8000000UL -std=gnu99 -Wall -Icab202_teensy -Lcab202_teensy
LIBS=-Wl,-u,vfprintf -lprintf_flt -lm -lcab202_teensy

# Default 'recipe'
all: 
	avr-gcc main.c interface.c $(FLAGS) $(LIBS) -o fin.o
	avr-objcopy -O ihex fin.o fin.hex
	
main.o: 
	avr-gcc -c main.c $(FLAGS) $(LIBS) -o main.o

interface.o:
	avr-gcc -c interface.c $(FLAGS) $(LIBS) -o interface.o

# Cleaning  (be wary of this in directories with lots of executables...)
clean:
	rm *.o
	rm *.hex
