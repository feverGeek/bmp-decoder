#include "my_bmp_decoder.h"
#include <stdio.h>

/* 读文件 */
FILE* read_bmp(const char *file_name)
{
	FILE *fp;
	fp = fopen(file_name, "rb");
	if(fp == NULL)
	{
		printf("文件打开失败\n");
		return NULL;
	}
	return fp;
}

/* 读文件头和信息 */
void read_bmp_header_info(BMPFILEHEADER *bmp_file_header, BMPINF *bmp_info, FILE *bmp_file)
{
	fread(bmp_file_header, sizeof(BMPFILEHEADER), 1, bmp_file);
	fread(bmp_info, sizeof(BMPINF), 1, bmp_file);
}

/* 获取图片的颜色位数 */
int get_bmp_bits(BMPINF bmp_info)
{
	return (bmp_info.bBitCount);
}



// /* 获取2色图文件像素 */
// void get_1bit_file_pixel(void);

// /* 获取16色图文件像素 */
// void get_4bit_file_pixel(void);

// /* 获取256色图文件像素 */
// void get_8bit_file_pixel(void);

/* 获取真彩色图文件像素 */
void get_24bit_file_pixel(BMPINF bmp_info, BMPFILEHEADER bmp_file_header,FILE* bmp_file)
{
	// 图片会按4字节补全用 UBYTE padBytes[2] 补全到4的整数倍
	// 一直补到每一行的内存数为4整数个byte
	int bmp_width;   								// bmp 文件像素的宽度
	int bmp_height;  								// bmp 文件像素的高度
	int bmp_append = 0;  							// bmp 文件宽度的扩充字节数
	int bmp_length;  								// 经过计算得到的bmp文件宽度的字节数
	Bits_24_RGBQUAD* bmp_line = NULL;

	bmp_width = bmp_info.bWidth;
	bmp_height = bmp_info.bHeight;
	
	if(bmp_width * 3 % 4)
	{
		bmp_length = ((int)bmp_width * 3 / 4) * 4 + 4;
		bmp_append = bmp_length - bmp_width*3;
		printf("bmp_append:%d", bmp_append);
	}

	bmp_line = (Bits_24_RGBQUAD*)malloc(bmp_width*sizeof(Bits_24_RGBQUAD));
	if(bmp_line != NULL)
	{
		fseek(bmp_file, bmp_file_header.bOffset, SEEK_SET);

		FILE* bmp_data_file = fopen("bmp_data.txt", "w+");

		if(bmp_data_file != NULL)
		{
			while(fread(bmp_line, bmp_width*sizeof(Bits_24_RGBQUAD), 1, bmp_file))
			{
				for(int i = 0; i < bmp_width; i++)
				{
					
					fprintf(bmp_data_file, "{B:%d,G:%d,R:%d} ", bmp_line[i].rgbBlue,
															   bmp_line[i].rgbGreen, 
															   bmp_line[i].rgbRed);
				}
				fseek(bmp_file, bmp_append, SEEK_CUR);
				fprintf(bmp_data_file, "\n");
			}
		}
		fclose(bmp_data_file);
	}

	free(bmp_line);
	bmp_line = NULL;
	
}

/* 输出结构体信息 */
void output_struct_info(BMPFILEHEADER* bmp_file_header, BMPINF *bmp_info)
{
	printf("文件标识符:%x\n文件的大小，单位字节:%x\n保留值,必须设置为0:%x\n保留值,必须设置为0:%x\n文件头的最后到图像数据位开始的偏移量:%x\n",
		bmp_file_header->bType,             /*  文件标识符          */
		bmp_file_header->bfSize,            /*  文件的大小，单位字节 */
		bmp_file_header->bReserved1,        /*  保留值,必须设置为0  */       
		bmp_file_header->bReserved2,        /*  保留值,必须设置为0  */
		bmp_file_header->bOffset);          /*  文件头的最后到图像数据位开始的偏移量    */

	printf("信息头的大小:%x\n图像的宽度:%x\n图像的高度:%x\n图像的位面数:%x\n每个像素的位数:%x\n压缩类型:%x\n图像的大小,以字节为单位:%x\n水平分辨率:%x\n 垂直分辨率:%x\n使用的色彩数:%x\n重要的颜色数:%x\n",
		bmp_info->bInfoSize,        /*  信息头的大小             */
		bmp_info->bWidth,           /*  图像的宽度               */
		bmp_info->bHeight,          /*  图像的高度               */
		bmp_info->bPlanes,          /*  图像的位面数             */
		bmp_info->bBitCount,        /*  每个像素的位数           */
		bmp_info->bCompression,     /*  压缩类型                 */
		bmp_info->bmpImageSize,     /*  图像的大小,以字节为单位   */
		bmp_info->bXPelsPerMeter,   /*  水平分辨率               */
		bmp_info->bYPelsPerMeter,   /*  垂直分辨率               */
		bmp_info->bClrUsed,         /*  使用的色彩数             */
		bmp_info->bClrImportant     /*  重要的颜色数             */
	);
}