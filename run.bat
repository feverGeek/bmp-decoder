gcc -c main.c
gcc -c my_bmp_decoder.c

gcc main.o my_bmp_decoder.o -o main.exe

main.exe