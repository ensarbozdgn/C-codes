#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
		4 basamakl� say� tahmin etme oyunu
*/



int puanHesapla(int arti, int eksi, int hak){
	return 10 * arti + 5 * eksi + 1000/hak  - (arti * eksi) / (arti + eksi);
}

int ekranBas(int * randSayi, int * arti, int * eksi, int hak){
	int tahmin;
	int i=0,j=0,tahminInt[4];
	system("cls");
	printf("Kalan hak: %d\nSayiyi tahmin ediniz: ", 10 - hak +1);
	scanf("%d",&tahmin);
	for(i = 3; i >= 0; i--){			//alinan tahmin int ini basamaklar�na ay�r
		tahminInt[i] = tahmin % 10;
    	tahmin /= 10;
	}
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(randSayi[j] == tahminInt[i]){		//elimizdeki random sayi ile tahmin basamaklar�n� kar��la�t�r
				if(i == j)
					*arti = *arti + 1;
				else
					*eksi = *eksi + 1;
			}
		}
	}
	printf("-%d +%d\n",*eksi,*arti);
	system("pause");
	if(*arti == 4){				//4 artimiz varsa bildik demektir
		printf("Bildiniz!");
		return 0;
		
	}
	return 1;
}

int oyunaBasla(){
	int randSayi[4], gecici = 0,hak = 1, puan = 0;
	int arti=0, eksi=0, artiToplam=0, eksiToplam=0, flag = 1;
	
	
	//4 basamakl� random say� �ret
	randSayi[0] = rand() % 10;
	do{
		randSayi[1] = rand() % 10; 
	}
	while(randSayi[1] == randSayi[0]);
	do{
		randSayi[2] = rand() % 10; 
	}
	while(randSayi[2] == randSayi[0] || randSayi[2] == randSayi[1]);
	do{
		randSayi[3] = rand() % 10; 
	}
	while(randSayi[3] == randSayi[0] || randSayi[3] == randSayi[1] || randSayi[3] == randSayi[2]);

	while(flag){               //flag 0 olunca d�ng�den ��k
		if(hak == 11){		//hak 11 olursa
			system("cls");
			printf("\tHakkiniz doldu...\n");
			flag = 0;		//d�ng�den ��k
			break;
		}
		flag = ekranBas(randSayi, &arti, &eksi, hak);    //ekranBas fonksiyonunu �al��t�r ve d�nen de�eri flag a e�itle
		if(flag == 1){		 //flag 1 oldu�u s�rece hak i artt�r
			hak++;
		}
		artiToplam += arti;	//yapilan artilari toplama ekle
		arti = 0;			//ve artilari s�f�rla
		eksiToplam += eksi;	//yapilan eksileri toplama ekle
		eksi = 0;			//ve eksileri s�f�rlar
		if(flag == 0)		//flag 0 ise diziden ��k
			break;
	}
	
	puan = puanHesapla(artiToplam, eksiToplam, hak);	//toplam artilardan, eksilerden ve ka��nc� hakta bilindi�ine g�re puani hesaplay�p puana yaz
	printf("\n\tPuaniniz:  %d\n",puan);  //puani kullan�c�ya g�ster
	system("pause");
	return puan; //puan d�nd�r
}

int dosyayaYaz(int puan){
	FILE *fptr;
	char buffer[128], dosyadanStringler[10][128], isimler[10][128], isim[16];
	int puanListesi[10], elemanSayisi = 0, sonIndex = 0, hedefIndex = 11,i = 0, flag = 0, offset = 0;
	fptr = fopen("top10.txt","r");						
	if(fptr == NULL)									// dosya kontrolleri yap�ld�
		fptr = fopen("top10.txt","w+");					// dosya yoksa yeni dosya olu�tur
	fclose(fptr);
	
	fptr = fopen("top10.txt","r");						// art�k dosya kesin olarak var o y�zden okumak i�in a�
	fseek(fptr, 0, SEEK_END);							//dosyada imleci sona getir
    if (ftell(fptr) != 0){								// e�er imlec hala 0 nokta de�ilse 
    	fseek(fptr, 0, SEEK_SET);						//imleci dosyan�n ba��na getir
		while(fgets(buffer,128,fptr) != NULL && buffer != "\n"){		//dosyadan veri �ek e�er veri NULL ve \n de�ilse
			strcpy(dosyadanStringler[elemanSayisi], buffer);			//�ekti�in veriyi dosyadanStringler dizisine ata
			elemanSayisi++;							//ka� tane say� ald���m�z� sakl�yor
			if(elemanSayisi == 10)					//eleman sayisi 10 olduysa d�ng�den ��k
				break;
		}
		sonIndex = elemanSayisi - 1;
	
		for(i = sonIndex; i >= 0; i--){												// sonIndexten ba�lay�p 0 a kadar d�n
			sscanf(dosyadanStringler[i],"%d %s\n",&puanListesi[i],isimler[i]);		// dosyadanStringler dizisinin i�indeki stringlerden formatl� �ekip puanListesi ve isimler dizisine kaydet
			if(puan > puanListesi[i]){						//e�er fonksiyona gelen puan, puanListesinin i. eleman�ndan y�ksekse 
				hedefIndex = i;								//hedefIndexi i ye e�itle
				flag = 1;									//ve flagi 1 yap
			}
		}
		if(sonIndex < 9){					//sonIndex 9 dan k���kse kesin olarak gir ��nk� en iyi 10 oyuncuyu daha tamamlamad���m�z i�in kesinlikle isme ihtiyac var
			flag = 1;
			if(hedefIndex == 11)				//e�er hedefIndex default de�erindeyse sonIndex'in 1 b�y���ne getir ki son elemandan bir sonraki yere yerle�sin
				hedefIndex = sonIndex + 1;
		}
		if(flag){								//flag 1 ise
			printf("\tIsminizi giriniz: \t");	//kullan�c�ya ismini sor
			scanf("%s",isim);
		}
		else
			return -1;							//e�er flag 0 ise ilk 10 a giremedi o y�zden fonksiyonu kapat yap�lmas� gereken bir i�lem yok
		fclose(fptr);
		fptr = fopen("temp10.txt", "w+");
		
		for(i = 0; i <= sonIndex + 1; i++){					//i sonIndex in 1 b�y���ne gelene kadar d�n
			if(i == 10)										//i 10 a gelmi�se d�ng�den ��k ��nk� ilk 10 ki�i doldu
				break;
			if(i == hedefIndex){							//e�er i hedefIndex e e�it ise o zaman fonksiyona gelen puan� yerle�tir
				fprintf(fptr,"%d %s\n",puan,isim);
				offset = 1;									//ve offseti 1 yap ki s�radaki elemanlar�n yeri bozulmas�n
			}
			else
				fputs(dosyadanStringler[i-offset],fptr);
		}
		fclose(fptr);
		remove("top10.txt");								//top10 dosyas�n� sil
		rename("temp10.txt","top10.txt");					// ve ge�i�i dosyay� top10 yap
	}
	else{										//e�er dosyan�n sonundaki imle� 0 a e�itse dosya bo�
    	fseek(fptr, 0, SEEK_SET);
    	fclose(fptr);
    	printf("Isminizi giriniz: ");			//dosya bo� ise direk ismi sorup dosyaya yazd�r
		scanf("%s",isim);
    	fptr = fopen("top10.txt", "a");
    	fprintf(fptr,"%d %s\n",puan, isim);
	}
	fclose(fptr);
}

void top10(){
	FILE *fptr;
	char buffer[128];				//dosyadan �ekti�im sat�rlar� saklayan dizi
	system("cls");
	fptr = fopen("top10.txt","r");	//dosyay� okumak i�in a�t�k
	if(fptr == NULL){				//dosya yok ise
		printf("-------------------------------------------------\n|\t\t\t\t\t\t|\n|\ttop10.txt dosyasi bulunamadi...\t\t|\n|\t\t\t\t\t\t|\n-------------------------------------------------\n");
		return;
	}
	printf("--------------------------------\n\tEn iyi 10 skor\n--------------------------------\n");
	while(fgets(buffer,128,fptr) != NULL && buffer != "\n"){	//dosyadan okunan veri NULL ve \n de�ilse devam et d�ng�ye
		printf("%s",buffer);	//�ekti�in veriyi yazd�r
	}
	fclose(fptr);
	printf("--------------------------------\n");
}

int main(){
	srand(time(NULL));          //Random say�lar�n random olmas�n� sa�layan fonksiyon
	int flag = 1;				//Bool yerine kulland���m int de�eri
	int secenek, puan=0;
	while(1){
		system("cls");
		printf("---------------------------------\n|\t1-Oyuna Basla\t\t|\n|\t2-En iyi 10 puan\t|\n|\t3-Cikis\t\t\t|\n---------------------------------\n\nSeciminizi giriniz:\t");  //men�y� yazd�r
		scanf("%d",&secenek);
		switch(secenek){
			case 1:
				puan = oyunaBasla();		//oyunaBasla fonksiyonundan d�nen de�eri puana e�itledik
				dosyayaYaz(puan);			//puan� dosyaya yaz�lmak �zere yollad�k
				break;
			case 2:
				top10();					//en iyi 10 oyuncuyu ekrana yazd�ran fonksiyonum
				system("pause");
				break;
			case 3:
				return -1;
			default:
				printf("Girdiginiz secenek bulunmamaktadir...");
		}
	}
}
