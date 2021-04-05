#include <stdio.h>
#include <stdlib.h>


void PartiAdiSirala(char partiAdi[])
{
    char temp;
    for (int i = 0; i < 3; i++)
        for (int j = i+1; j < 4; j++)
            if (partiAdi[i] > partiAdi[j]) {
                temp = partiAdi[i];
                partiAdi[i] = partiAdi[j];
                partiAdi[j] = temp;
         }

}

void PartiSiralama(float oySayisi[][6], char partiAdi[], int siralanacakSistem)//Sistem: il geneli mi ulke geneli mi?
{
    float temp;
    char temp1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j< 4-i  ; j++)
            if(oySayisi[j][siralanacakSistem] < oySayisi[j+1][siralanacakSistem]){ //Partilerin oy sayilarini siralamada yerlerini degistirirken parti adlarinin da ayni zamanda yerlerini degistirdim
                temp = oySayisi[j+1][siralanacakSistem];
                temp1 = partiAdi[j+1];
                oySayisi[j+1][siralanacakSistem] = oySayisi[j][siralanacakSistem];
                partiAdi[j+1] = partiAdi[j];
                oySayisi[j][siralanacakSistem] = temp;
                partiAdi[j] = temp1;
            }
}
void ilBirinciligiAtama(int ilBirinciligi[], char partiAdi[])
{
        switch(partiAdi[0]){
            case 'A':
                ilBirinciligi[0]++;
                break;
            case 'B':
                ilBirinciligi[1]++;
                break;
            case 'C':
                ilBirinciligi[2]++;
                break;
            case 'D':
                ilBirinciligi[3]++;
                break;
            default:
                break;
}
}
void MilletVekiliAtama(int kontenjan, float partiler[][6], char partiAdi[])
{
    for(int a = 0; a < 4; a++) //bir önceki ilde atanan milletvekillerini sifirliyoruz
            partiler[a][2] = 0;

    for(int i=0;i< kontenjan;i++){
        PartiSiralama(partiler, partiAdi, 0);

        switch(partiAdi[0]){ //Milletvekillerini dogru partilere atamak icin her seferinde yapilan siralamada birinci olan parti adina gore atadim
            case 'A':
                partiler[0][2]++;
                break;
            case 'B':
                partiler[1][2]++;
                break;
            case 'C':
                partiler[2][2]++;
                break;
            case 'D':
                partiler[3][2]++;
                break;
            default:
                break;
        }

        partiler[0][0] = partiler[0][0]/2;
    }
}

void TGYazdirma(float partiler[][6], int ilBirincilikleri[], int toplamKont, int toplamGecerliOy[], char partiAdi[])
{
    int TGGecerliOy = 0;
    float toplamOyYuzde[4] = {0};

    for(int i = 0; i < 4; i++)
        TGGecerliOy += toplamGecerliOy[i];

    for(int i = 0; i < 4; i++){
        toplamOyYuzde[i] = (partiler[i][5] * 100) / TGGecerliOy;
        partiler[i][4] = (partiler[i][3] * 100) / toplamKont;
    }
    printf("Turkiye Geneli :\n");
    printf("Milletvekili Kontenjani: %d\n", toplamKont);
    printf("Gecerli Oy Sayisi: %d\n", TGGecerliOy);
    printf("         \tOy Sayisi\t\tOy Yuzdesi\t\tMilletvekili Sayisi\t\tMilletvekili Yuzdesi\n");

    for(int i = 0; i < 4; i++)
        printf("%c Partisi\t   %.0f  \t\t  %.2f  \t\t    %.0f    \t\t\t     %.2f\n", partiAdi[i], partiler[i][5],toplamOyYuzde[i], partiler[i][3], partiler[i][4]);

    PartiAdiSirala(partiAdi);
    PartiSiralama(partiler, partiAdi, 5);

    printf("\nIktidar Partisi: %c\n", partiAdi[0]);
    printf("Ana Muhalefet Partisi: %c\n", partiAdi[1]);

    PartiAdiSirala(partiAdi);

    printf("\nOy Sayilarina Gore Il Birincilikleri: \n");

    for(int i = 0; i < 4; i++)
        printf("%c Partisi: %d\n", partiAdi[i], ilBirincilikleri[i]);

}

int main()
{
    int toplamGecerliOy[4]= {0}, kontenjan[4] = {0}, toplamKont = 0, ilBirincilikleri[4] = {0}, iller[4] = {1, 2, 3, 4};
    float partiler[4][6] = {0}; // 0-oy sayisi, 1-oy yuzdesi, 2-ilde mv sayisi, 3-toplam mv sayisi,4-toplam mv yuzdesi, 5-toplam oy sayisi
    char partiAdi[4] = {'A', 'B', 'C', 'D'};

    for(int i=0;i<4;i++)
    {
        printf("Il plaka kodu:%d \n", iller[i]);
        printf("Milletvekili kontenjani: ");
        scanf("%d",&kontenjan[i]);

        toplamKont += kontenjan[i];

        for(int a=0;a<4;a++)
        {
            printf("%c partisi oy sayisi ", partiAdi[a]);
            scanf("%f",&partiler[a][0]);
            partiler[a][5] += partiler[a][0]; // partinin toplam gecerli oy sayisini hesaplama
            toplamGecerliOy[i] += partiler[a][0]; // illerdeki toplam gecerli oy sayisini hesaplama
        }
        printf("Toplam gecerli oy sayisi: %d\n\n", toplamGecerliOy[i]);

        PartiSiralama(partiler, partiAdi, 0);
        ilBirinciligiAtama(ilBirincilikleri, partiAdi);
        printf("\t\tOy sayisi\tOy yuzdesi\n");

        for(int b=0;b<4;b++)
        {
            partiler[b][1]=(partiler[b][0]*100)/toplamGecerliOy[i];
            printf("%c partisi\t%.0f\t\t%.2f\n",partiAdi[b],partiler[b][0],partiler[b][1]);
        }

        printf("Milletvekili Sayilari:\n");
        MilletVekiliAtama(kontenjan[i], partiler, partiAdi);
        PartiAdiSirala(partiAdi); //parti adlarinin sirasini yukarida deðistirdigimiz icin bastan siraliyoruz alfabetik siraya gore

        for(int k = 0; k < 4; k++){
            printf("%c Partisi: %.0f\n", partiAdi[k], partiler[k][2]);
            partiler[k][3] += partiler[k][2]; // toplam mv sayisi
        }
        printf("\n");
        printf("Herhangi bir tusa basin");
        char c;
        scanf("%c", c);
    }

        TGYazdirma(partiler, ilBirincilikleri, toplamKont, toplamGecerliOy, partiAdi);


    return 0;
}
