/* 
    
    Bu kod Algoritmalar ve Programlamaya Giri� dersi i�in yaz�lm��t�r.
    
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    
    {
	int islem,sayi1,sayi2;
    float sonuc;
    //Kullan�c�dan 2 say� al.
    printf("Birinci Sayiyi Girin: ");
    scanf("%d",&sayi1);
    printf("Ikinci Sayiyi Girin: ");
    scanf("%d",&sayi2);
    //��lem t�r�n� ekrana yazd�r. Kullan�c�ya i�lemi se�tir.
    printf("\n1.Toplama""\n2.Cikarma""\n3.Bolme""\n4.Carpma\n""\nIslemi seciniz: ");
    scanf("%d",&islem);
    //�slemi uygula ve sonucu yazd�r.
    switch(islem){
	case 1:
        sonuc = (float)sayi1+(float)sayi2;  
        printf("\nSonuc:       %0.1f",sonuc);
    	break;
    case 2:
        sonuc = (float)sayi1-(float)sayi2;
        printf("\nSonuc:       %0.1f",sonuc);
        break;
    case 3:
        sonuc = (float)sayi1/(float)sayi2;
        printf("\nSonuc:       %0.1f",sonuc);
        break;
    case 4:
        sonuc = (float)sayi1*(float)sayi2;      
        printf("\nSonuc:       %0.1f",sonuc);
		break;
    default:
         printf("\n""Sectigin islem gecersiz...");       
		 break;
	}
	getchar();
	return 0;
	}
}
