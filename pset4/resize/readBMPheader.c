// video https://www.youtube.com/watch?v=bkoAK-6Cq5Q

#include <stdio.h>

int main(){

    unsigned char imagedata[54];
    char filename[40];
    int bytevalue;
    int index = 0;

    printf("Enter bitmap filename: ");
    scanf("%s", filename);

    FILE * file;
    file = fopen(filename, "rb");

    if (file != NULL){
        do{
            bytevalue = fgetc(file);
            imagedata[index] = bytevalue;
            index++;

            if(index == 54) break;

        } while (bytevalue != EOF);
    } else {
        for(int i = 0; i < 29; i++){
            imagedata[i]='\0';
        }
    }

    fclose(file);

    int image_width = imagedata[20-1] * 256 + imagedata[19-1];
    int image_height = imagedata[24-1] * 256 + imagedata[23-1];
    int image_bits = imagedata[29-1];

    printf("\n");
    printf("Image width: %d \n", image_width);
    printf("Image height: %d \n", image_height);
    printf("%d bit image", image_bits);
    printf("\n\n");

    return 0;
}