#define STBI_NO_HDR
#define STBI_NO_LINEAR
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>


int main(int argc, char** argv) {
	if (argc <= 2 || strcmp(argv[1], "-h") == 0 || argc > 6) {
		printf("command requires 2 arguments, <program> <image> <output> [channels] [name] [type]\n");
		return -1;
	}

	int w, h, tmp_c;
	int c = (argc >= 4) ? atoi(argv[3]) : 0;
	unsigned char* image = stbi_load(
		argv[1], &w, &h, &tmp_c, c
	);
	if (c == 0) { c = tmp_c; }

	FILE* file = fopen(argv[2], "w+");

	char* name = (argc >= 5) ? argv[4] : "image";
	char* type = (argc == 6) ? argv[5] : "ptrdiff_t";
	fprintf(
		file,
		"#ifndef I2H_IMAGE_%s_H\n"
		"#define I2H_IMAGE_%s_H\n"
		"\n"
		"#include <stddef.h>\n"
		"\n"
		"const %s img_%s_width = %i,\n"
		"		  img_%s_height = %i,\n"
		"		  img_%s_channels = %i;\n"
		"\n"
		"unsigned char img_%s_data[%i * %i * %i] = {\n\t",
		name, name, type,
		name, w,
		name, h,
		name, c,
		name, w, h, c
	);

	for (ptrdiff_t i = 0; i < w * h * c; i++) {
		fprintf(file, "0x%X, ", image[i]);
	}

	fprintf(
		file,
		"\n};\n"
		"\n"
		"#endif /* I2H_IMAGE_%s_H */\n",
		name
	);

	free(image);
	fclose(file);
}
