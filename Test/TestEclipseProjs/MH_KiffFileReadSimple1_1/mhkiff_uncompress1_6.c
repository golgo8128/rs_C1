/*
 * mhkiff_uncompress1_2.c
 *
 *  Created on: 2020/09/22
 *      Author: rsaito
 */

/* On Mac,
 * gcc -c mhkiff_uncompress1_6.c
 * gcc -L/usr/lib mhkiff_uncompress1_6.o -o mhkiff_uncompress1_6 -lz

In some environment:

clang -I"/Library/Frameworks/R.framework/Resources/include" -DNDEBUG   -isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk -I/usr/local/include -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include -fPIC  -Wall -g -O2  -c mhkiff_uncompress1_6.c -o mhkiff_uncompress1_6.o

Then,

R CMD SHLIB mhkiff_uncompress1_6.c


On Windows in MINGW64,

R.exe CMD SHLIB mhkiff_uncompress1_6.c -lz

 */

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

void read_uncompress_kiffchunk(
		char **, int *, int *, int *,
		unsigned char *, int *);

void read_uncompress_kiffchunk(
		char **filename,
		int *seekpos,
		int *compressed_size,
		int *uncompressed_size,
		unsigned char *uncompressbuf,
		int *res_status){

	FILE *fp;
	unsigned char *compressedbuf;
	int uncompress_res;

	if((fp = fopen(*filename, "r")) == NULL){
		*res_status = -1001;
		printf("Failed to open %s\n", *filename);
		return;
	} else {
		printf("Successfully opened %s\n", *filename);	
	}

	printf("Seek position: %d  Compressed size: %d  Uncompressed size: %d\n",
			*seekpos, *compressed_size, *uncompressed_size);


	if(fseek(fp, *seekpos, SEEK_SET) != 0){
		*res_status = -1002;
		return;
	}

	if((compressedbuf = (unsigned char *)malloc(*compressed_size * sizeof(unsigned char))) == NULL){
		*res_status = -1003;
		return;
	}

	if(fread(compressedbuf, sizeof(char), *compressed_size, fp) < 0){
		*res_status = -1004;
		return;
	}

	uncompress_res = uncompress(
			uncompressbuf, uncompressed_size,
			compressedbuf, *compressed_size);
	// https://refspecs.linuxbase.org/LSB_4.1.0/LSB-Core-generic/LSB-Core-generic/zlib-uncompress-1.html

	printf("Z_OK: %d, Z_BUF_ERROR: %d, Z_MEM_ERROR: %d, Z_DATA_ERROR: %d\n",
			Z_OK, Z_BUF_ERROR, Z_MEM_ERROR, Z_DATA_ERROR);
	printf("Uncompress result: %d\n", uncompress_res);

	free(compressedbuf);
	// free(uncompressbuf);

	*res_status = uncompress_res;

}



int main(){

	int ret_val;
	int seek_pos          = 19853425;
	int compressed_size   = 1453424;
	int uncompressed_size = 2574004 * 2;
	/* char *filename = "/Users/rsaito/Desktop/TMP_Area/C_114STD_1.kiff"; */
	char *filename = "C:\\Users\\golgo\\Desktop\\TMP_Area\\C_114STD_1.kiff";
	
	unsigned char *uncompressbuf; // static char unc[10000000]; ??
	uncompressbuf = (unsigned char *)malloc(uncompressed_size * sizeof(unsigned char));

	read_uncompress_kiffchunk(
			&filename,
			&seek_pos, &compressed_size, &uncompressed_size,
			uncompressbuf, &ret_val);

	printf("Hello, world!\n");
	printf("%d\n", ret_val);

}


