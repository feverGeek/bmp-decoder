#ifndef __MY_BMP_DECODER_
#define __MY_BMP_DECODER_

#include <stdio.h>
#include <stdlib.h>

typedef unsigned short U16;
typedef unsigned int U32;
typedef unsigned char  u8;

#pragma pack(2) //设置1字节对齐模式，pack()将对齐模式取消
/*位图文件头*/
typedef struct BMP_FILE_HEADER
{
	U16 bType;             /*  文件标识符          */
	U32 bfSize;            /*  文件的大小，单位字节 */
	U16 bReserved1;        /*  保留值,必须设置为0  */       
	U16 bReserved2;        /*  保留值,必须设置为0  */
	U32 bOffset;           /*  文件头的最后到图像数据位开始的偏移量    */
} BMPFILEHEADER;
#pragma pack()

#pragma pack(2)
/*位图信息头*/
typedef struct BMP_INFO
{
	U32 bInfoSize;        /*  信息头的大小             */
	U32 bWidth;           /*  图像的宽度               */
	U32 bHeight;          /*  图像的高度               */
	U16 bPlanes;          /*  图像的位面数             */
	U16 bBitCount;        /*  每个像素的位数           */
	U32 bCompression;     /*  压缩类型                 */
	U32 bmpImageSize;     /*  图像的大小,以字节为单位   */
	U32 bXPelsPerMeter;   /*  水平分辨率               */
	U32 bYPelsPerMeter;   /*  垂直分辨率               */
	U32 bClrUsed;         /*  使用的色彩数             */
	U32 bClrImportant;    /*  重要的颜色数             */
} BMPINF;
#pragma pack()

/*彩色表*/
typedef struct RGB_QUAD 
{
	U16 rgbBlue;         /*  蓝色强度  */
	U16 rgbGreen;        /*  绿色强度  */
	U16 rgbRed;          /*  红色强度  */
	U16 rgbReversed;     /*  保留值    */
} RGBQUAD;

/* 24色彩色表 */
typedef struct 
{
	u8 rgbBlue;
	u8 rgbGreen;
	u8 rgbRed;
} Bits_24_RGBQUAD;


/* 读文件 */
FILE* read_bmp(const char *file_name);

/* 读文件头和信息 */
void read_bmp_header_info(BMPFILEHEADER *bmp_file_header, BMPINF *bmp_info, FILE *bmp_file);
 
/* 获取2色图文件像素 */
void get_1bit_file_pixel(void);

/* 获取16色图文件像素 */
void get_4bit_file_pixel(void);

/* 获取256色图文件像素 */
void get_8bit_file_pixel(void);

/* 获取真彩色图文件像素 */
void get_24bit_file_pixel(BMPINF bmp_info, BMPFILEHEADER bmp_file_header,FILE* bmp_file);

/* 输出结构体信息 */
void output_struct_info(BMPFILEHEADER* bmp_file_header, BMPINF *bmp_info);
#endif
