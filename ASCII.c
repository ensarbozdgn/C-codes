/*

    ASCII tablosunu yazd�rmak i�in kod.

*/

#include <stdio.h>

int main()
{
    int i;
    for (i=0; i < 256; i++)
        {
        printf("Degeri: %d ASCII kodu: %c\n", i, i);
        }
    getchar();
    return 0;   
}
