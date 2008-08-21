#include <stdlib.h>
#include <stdio.h>
#include <xpwn/libxpwn.h>
#include "abstractfile.h"
#include <xpwn/nor_files.h>
#include <xpwn/ibootim.h>
#include <string.h>

void print_usage() {
	XLOG(0, "  _____________________________________________________________________\n");
	XLOG(0, "|	img3decrypt	Decrypt iPhone ramdisks and other img3 files!	|\n");
	XLOG(0, "|			-by Steven Troughton-Smith			|\n");
	XLOG(0, "|			-based on imagetool in xpwn			|\n");
	XLOG(0, "  ---------------------------------------------------------------------\n\n");
	XLOG(0, "	usage:		img3decrypt e [input.dmg] [output.dmg] [iv] [key]\n");
}

int main(int argc, char* argv[]) {
	init_libxpwn();
	
	if(argc < 4) {
		print_usage();
		return 0;
	}

	AbstractFile* png;
	AbstractFile* img;
	AbstractFile* dst;
	void* imageBuffer;
	size_t imageSize;

	unsigned int key[16];
	unsigned int iv[16];
	unsigned int* pKey = NULL;
	unsigned int* pIV = NULL;

	if(strcmp(argv[1], "e") == 0) {
		img = createAbstractFileFromFile(fopen(argv[2], "rb"));

		if(argc >= 6) {
			sscanf(argv[4], "%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x",
				&iv[0], &iv[1], &iv[2], &iv[3], &iv[4], &iv[5], &iv[6], &iv[7], &iv[8],
				&iv[9], &iv[10], &iv[11], &iv[12], &iv[13], &iv[14], &iv[15]);

			sscanf(argv[5], "%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x",
				&key[0], &key[1], &key[2], &key[3], &key[4], &key[5], &key[6], &key[7], &key[8],
				&key[9], &key[10], &key[11], &key[12], &key[13], &key[14], &key[15]);

			pKey = key;
			pIV = iv;
		}
			
		AbstractFile2* img3 = (AbstractFile2*) createAbstractFileFromImg3(img);
		img3->setKey(img3, key, iv);
		
		AbstractFile * out = createAbstractFileFromFile(fopen(argv[3], "wb"));
		
		size_t inDataSize = (size_t) ((AbstractFile *)img3)->getLength((AbstractFile *)img3);
		char *inData = (char*) malloc(inDataSize);
		
		((AbstractFile *)img3)->read((AbstractFile *)img3, inData, inDataSize);
		
		out->write(out, inData, inDataSize);
		
	}

	return 0;
}

