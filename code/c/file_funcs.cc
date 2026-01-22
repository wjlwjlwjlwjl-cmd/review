#include <stdio.h>

#define SIZE 5

int main()
{
    //FILE* pf = fopen("log.txt", "r");

    //output functions
    //fputs("hello world", pf);
    //fseek(pf, 4, SEEK_SET);
    //fputs("hello world", pf);

    //fseek(pf, 0, SEEK_END);
    //int pos = ftell(pf);
    //printf("the size of the file is %d\n", pos);
    //
    //rewind(pf);
    //char buffer[200];
    //fread(buffer, 1, 100, pf);
    //buffer[100] = '\0';
    //printf("%s\n", buffer);
    
    //input functions
    //text functions
    //int c;
    //while((c = fgetc(pf)) != EOF)
    //{
    //    putchar(c);
    //}
    //printf("\n");
    //if(ferror(pf))
    //{
    //    printf("I/O fail\n");
    //}
    //else if(feof(pf))
    //{
    //    printf("file read success\n");
    //}
    
    //binary functions
    //the two arguments in the middle of the fwrite and fread means the sizeof single units
    //and the total number of the units;
    //FILE* pf = fopen("log.txt", "wb");   
    //double arr[SIZE] = {1., 2., 3., 4., 5.};
    //fwrite(arr, sizeof(*arr), SIZE, pf);
    //fclose(pf);
    //pf = fopen("log.txt", "rb");
    //double buffer[SIZE];
    //int read_num = fread(buffer, sizeof(*buffer), SIZE, pf);
    //for(int i = 0; i < SIZE; i++)
    //{
    //    printf("%lf ", buffer[i]);
    //}
    //if(read_num == SIZE)
    //{
    //    printf("read from log.txt success\n");
    //}
    //else
    //{
    //    printf("read error\n");
    //}
    
    //formatted I/O functions
    //FILE* pf = fopen("log.txt", "w");
    //fprintf(pf, "the content of the file is: \n %s", "hello world");
    //fclose(pf);
    //pf = fopen("log.txt", "r");
    //char buffer[100];
    //fscanf(pf, "%s", buffer);
    //buffer[100] = '\0';
    //printf("%s\n", buffer);

    //sprintf and sscanf
    char buffer[100];
    sprintf(buffer, "the content is %d", 1);
    printf("%s\n", buffer);
    char str[100];
    sscanf(buffer, "%s", str);
    printf("%s\n", str);

    //fclose(pf);
    return 0;
}
