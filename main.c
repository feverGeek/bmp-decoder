#include "my_bmp_decoder.h"
#include <stdio.h>

int main()
{
    FILE* fp;
    BMPINF bmp_info = {0};
    BMPFILEHEADER bmp_file_header = {0};

    // char file_name[100] = "./21_pure_white.bmp";
    char file_name[100] = "./2019-04-13-19-05-11.bmp";
    fp = read_bmp(file_name);

    read_bmp_header_info(&bmp_file_header, &bmp_info, fp);

    get_24bit_file_pixel(bmp_info, bmp_file_header, fp);

    //output_struct_info(&bmp_file_header, &bmp_info);
    return 0;
}