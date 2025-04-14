#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>

int main(int argc, char** argv) {
    if (argc <= 2 || argc >= 4) {
        printf("command requires 2 arguments, <program> <image> <output>\n");
        return -1;
    }
    
    int w, h, c;
    unsigned char* image = stbi_load(argv[1], &w, &h, &c, 4);
    FILE* file = fopen(argv[2], "w+");
    
    fprintf(file, "unsigned char image[%i * %i * %i] = {\n", w, h, c);
    
    for (size_t i = 0; i < w * h * c; i++)
        fprintf(file, "	%i,", image[i]);

    fprintf(file, "\n};\n");
    
    free(image);
    fclose(file);
}
