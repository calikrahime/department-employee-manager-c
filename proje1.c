
/**
 * @file Proje1.c
 * @description Bu dosya, proje için yazılmış tüm fonksiyonların tanımlarını içermektedir. 
 * Yapılar, dosya işlemleri, dinamik bellek yönetimi ve işlevsel fonksiyonlar yer almaktadır.
 * @assignment 1. Ödev
 * @date 20.12.2024
 * @author Rahime Çalık - rahime.calik@stu.fsm.edu.tr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proje1.h"

// Birim oluşturma fonksiyonu: Yeni bir birim oluşturur ve döndürür.
Birim birimOlustur(char *birimAdi, unsigned short int birimKodu)
{

    if (birimAdi == NULL)
    {
        printf("Hata: birimAdi NULL olamaz!\n");
        exit(1);
    }

    Birim yeniBirim;
    //Birim adı için bellek tahsis edilir.
    yeniBirim.birimAdi = malloc(strlen(birimAdi) + 1); // '\0' için +1
    if (yeniBirim.birimAdi == NULL)
    {
        printf("Bellek tahsisi basarisiz!\n");
        exit(1);
    }
    strcpy(yeniBirim.birimAdi, birimAdi);

    yeniBirim.birimKodu = birimKodu;
    yeniBirim.birimCalisanlar = NULL; // Çalışan listesi başlangıçta boş

    return yeniBirim;
}

// Çalışan oluşturma fonksiyonu: Yeni bir çalışan oluşturur ve döndürür.
Calisan calisanOlustur(char *adi, char *soyadi, unsigned short int birimKodu, float maas, int girisYili)
{
    if (adi == NULL || soyadi == NULL)
    {
        printf("Hata: Çalışan adı veya soyadı NULL olamaz!\n");
        exit(1);
    }

    Calisan yeniCalisan;
    // Çalışan adı ve soyadı için bellek tahsis edilir.
    yeniCalisan.calisanAdi = malloc(strlen(adi) + 1);
    yeniCalisan.calisanSoyadi = malloc(strlen(soyadi) + 1);

    if (yeniCalisan.calisanAdi == NULL || yeniCalisan.calisanSoyadi == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        exit(1);
    }

    strcpy(yeniCalisan.calisanAdi, adi);
    strcpy(yeniCalisan.calisanSoyadi, soyadi);
    yeniCalisan.birimKodu = birimKodu;
    yeniCalisan.maas = maas;
    yeniCalisan.girisYili = girisYili;

    return yeniCalisan;
}

// Birim ekleme fonksiyonu: Birimi birim listesine ekler.
void birimEkle(Birim **birimler, int *birimSayisi, Birim yeniBirim)
{

    // Aynı birim zaten var mı?
    for (int i = 0; i < *birimSayisi; i++)
    {
        if ((*birimler)[i].birimKodu == yeniBirim.birimKodu)
        {
            printf("Birim zaten mevcut: %s (%u)\n", yeniBirim.birimAdi, yeniBirim.birimKodu);
            return; // Yeni birim eklenmez
        }
    }

    // Belleği genişlet: yeni birim eklenebilmesi için realloc kullanılır
    *birimler = realloc(*birimler, (*birimSayisi + 1) * sizeof(Birim));

    if (*birimler == NULL)
    {
        printf("Bellek tahsisi basarisiz!\n");
        exit(1);
    }

    // Yeni birimi diziye ekle
    (*birimler)[*birimSayisi] = yeniBirim;

    // Birim sayısını bir artır
    (*birimSayisi)++;
}

// Çalışan ekleme fonksiyonu: Çalışanı çalışan listesine ekler.
void calisanEkle(Calisan **calisanlar, int *calisanSayisi, Calisan yeniCalisan)
{
    // Çalışan listesi için bellek tahsisi veya genişletme.
    *calisanlar = realloc(*calisanlar, (*calisanSayisi + 2) * sizeof(Calisan)); // +1 çalışan, +1 NULL için
    if (*calisanlar == NULL)
    {
        printf("Bellek tahsisi başarısız!\n");
        exit(1);
    }

    (*calisanlar)[*calisanSayisi] = yeniCalisan;         // Yeni çalışan ekleniyor
    (*calisanlar)[*calisanSayisi + 1].calisanAdi = NULL; // Diziyi sonlandırmak için NULL işaretçisi
    (*calisanSayisi)++;
}

void calisanBilgileriniYazdir(Calisan c)
{
    printf("Calisan Bilgileri:\n");
    printf("Ad: %s\n", c.calisanAdi);
    printf("Soyad: %s\n", c.calisanSoyadi);
    printf("Birim Kodu: %u\n", c.birimKodu);
    printf("Maas: %.2f\n", c.maas);
    printf("Giris Yili: %d\n", c.girisYili);
    printf("--------------------------\n");
}

void birimBilgileriniYazdir(Birim birim)
{
    printf("Birim Bilgileri:\n");
    printf("Birim Adi: %s\n", birim.birimAdi);
    printf("Birim Kodu: %u\n", birim.birimKodu);

    if (birim.birimCalisanlar == NULL)
    {
        printf("Bu birimde calisan yok.\n");
    }
    else
    {
        printf("Bu birimde calisanlar var.\n");
    }
    printf("--------------------------\n");
}

void tumBirimleriYazdir(Birim *birimler, int birimSayisi)
{
    printf("Tum Birimler:\n");
    for (int i = 0; i < birimSayisi; i++)
    {
        printf("Birim %d:\n", i + 1);
        printf("Birim Adi: %s\n", birimler[i].birimAdi);
        printf("Birim Kodu: %u\n", birimler[i].birimKodu);

        if (birimler[i].birimCalisanlar == NULL)
        {
            printf("  Bu birimde calisan yok.\n");
        }
        else
        {
            printf("  Calisanlar:\n");
            int j = 0;
            while (birimler[i].birimCalisanlar[j].calisanAdi != NULL)
            {
                printf("    Calisan %d: %s %s, Maas: %.2f, Giris Yili: %d\n", j + 1,
                       birimler[i].birimCalisanlar[j].calisanAdi,
                       birimler[i].birimCalisanlar[j].calisanSoyadi,
                       birimler[i].birimCalisanlar[j].maas,
                       birimler[i].birimCalisanlar[j].girisYili);
                j++;
            }
        }
        printf("--------------------------\n");
    }
}

// Birimdeki çalışanların maaş ortalamasını hesaplar.
float maasOrtalamasiHesapla(Birim b, int calisanSayisi)
{
    if (calisanSayisi == 0)
    {
        printf("Bu birimde calisan bulunmamaktadir.\n");
        return 0.0;
    }

    float toplamMaas = 0.0;
// Tüm çalışanların maaşlarını toplar.
    for (int i = 0; i < calisanSayisi; i++)
    {
        toplamMaas += b.birimCalisanlar[i].maas; // Çalışan maaşlarını toplama
    }
 // Ortalama maaşı hesaplar ve döndürür.
    return toplamMaas / calisanSayisi; // Ortalama maaş
}

// Ortalama maaşın üzerinde maaş alan çalışanları listeleyen fonksiyon.
void ortalamaUstuCalisanlariListele(Birim b, int calisanSayisi)
{
    if (calisanSayisi == 0)
    {
        printf("Bu birimde calisan bulunmamaktadir.\n");
        return;
    }

    // Maaş ortalamasını hesapla
    float toplamMaas = 0.0;
    for (int i = 0; i < calisanSayisi; i++)
    {
        toplamMaas += b.birimCalisanlar[i].maas;
    }
    float ortalamaMaas = toplamMaas / calisanSayisi;

    // Ortalama üstü maaş alan çalışanları listele
    printf("Ortalama Maas: %.2f\n", ortalamaMaas);
    printf("Ortalama Maas Uzerinde Alan Calisanlar:\n");

    int bulunanCalisanSayisi = 0;
    for (int i = 0; i < calisanSayisi; i++)
    {
        if (b.birimCalisanlar[i].maas > ortalamaMaas)
        {
            printf("Calisan Adi: %s %s, Maas: %.2f\n",
                   b.birimCalisanlar[i].calisanAdi,
                   b.birimCalisanlar[i].calisanSoyadi,
                   b.birimCalisanlar[i].maas);
            bulunanCalisanSayisi++;
        }
    }

    if (bulunanCalisanSayisi == 0)
    {
        printf("Ortalama uzerinde maas alan calisan bulunmamaktadir.\n");
    }
}

// Her birimde en yüksek maaş alan çalışanı bulan ve yazdıran fonksiyon.
void enYuksekMaasCalisaniniYazdir(Birim *birimler, int birimSayisi)
{
    for (int i = 0; i < birimSayisi; i++)
    {
        printf("Birim: %s (Kodu: %u)\n", birimler[i].birimAdi, birimler[i].birimKodu);

        // Çalışan kontrolü
        if (birimler[i].birimCalisanlar == NULL)
        {
            printf("Bu birimde calisan bulunmamaktadir.\n\n");
            continue;
        }

        int calisanSayisi = 0;
        while (birimler[i].birimCalisanlar[calisanSayisi].calisanAdi != NULL)
        {
            calisanSayisi++;
        }

        if (calisanSayisi == 0)
        {
            printf("Bu birimde calisan bulunmamaktadir.\n\n");
            continue;
        }

        // En yüksek maaşı bulma
        float maxMaas = -1.0;
        int maxIndex = -1;

        for (int j = 0; j < calisanSayisi; j++)
        {
            if (birimler[i].birimCalisanlar[j].maas > maxMaas)
            {
                maxMaas = birimler[i].birimCalisanlar[j].maas;
                maxIndex = j;
            }
        }

        // En yüksek maaşlı çalışanı yazdır
        if (maxIndex != -1)
        {
            printf("En Yuksek Maas Alan Calisan:\n");
            printf("Ad: %s %s\n", birimler[i].birimCalisanlar[maxIndex].calisanAdi,
                   birimler[i].birimCalisanlar[maxIndex].calisanSoyadi);
            printf("Maas: %.2f\n\n", birimler[i].birimCalisanlar[maxIndex].maas);
        }
        else
        {
            printf("Bu birimde calisan bulunmamaktadir.\n\n");
        }
    }
}

// Çalışanların maaşlarını güncelleyen fonksiyon (10 yıldan fazla çalışanlar için).
void maasGuncelle(Birim *birimler, int birimSayisi, float yeniMaas)
{
    for (int i = 0; i < birimSayisi; i++)
    {
        printf("Birim: %s (Kodu: %u)\n", birimler[i].birimAdi, birimler[i].birimKodu);

        if (birimler[i].birimCalisanlar == NULL)
        {
            printf("Bu birimde calisan bulunmamaktadir.\n");
            continue;
        }
// Çalışanlar üzerinde döngü yaparak güncelleme işlemi yapar.
        for (int j = 0; birimler[i].birimCalisanlar[j].calisanAdi != NULL; j++)
        {
            int calismaSuresi = 2024 - birimler[i].birimCalisanlar[j].girisYili;

            // Çalışma süresi 10 yıldan fazla olan ve maaşı yeni maaştan küçük olanlar için güncelleme yapar.
            if (calismaSuresi > 10 && birimler[i].birimCalisanlar[j].maas <= yeniMaas)
            {
                printf("  Guncellenen Calisan: %s %s\n",
                       birimler[i].birimCalisanlar[j].calisanAdi,
                       birimler[i].birimCalisanlar[j].calisanSoyadi);
                printf("    Eski Maas: %.2f, Yeni Maas: %.2f\n",
                       birimler[i].birimCalisanlar[j].maas, yeniMaas);

                birimler[i].birimCalisanlar[j].maas = yeniMaas; // Maaşı güncelle
            }
        }

        printf("----------------------\n");
    }
}

// Fonksiyon: Dosyalardan Okuma
void birimVeCalisanlariAyriDosyalardanOku(
    Birim **birimler, int *birimSayisi,
    const char *birimlerDosyaAdi, const char *calisanlarDosyaAdi)
{

    // Birimler dosyasını aç
    FILE *birimlerDosya = fopen(birimlerDosyaAdi, "r");
    if (birimlerDosya == NULL)
    {
        printf("Birimler dosyası açılamadı: %s\n", birimlerDosyaAdi);
        exit(1);
    }

    // Çalışanlar dosyasını aç
    FILE *calisanlarDosya = fopen(calisanlarDosyaAdi, "r");
    if (calisanlarDosya == NULL)
    {
        printf("Çalışanlar dosyası açılamadı: %s\n", calisanlarDosyaAdi);
        fclose(birimlerDosya);
        exit(1);
    }

    // Birim bilgilerini oku
    char birimAdi[256];
    unsigned short int birimKodu;
    *birimSayisi = 0;

    printf("Birim bilgileri okunuyor...\n");
    while (fscanf(birimlerDosya, "%255[^,],%hu\n", birimAdi, &birimKodu) == 2)
    {
        Birim yeniBirim = birimOlustur(birimAdi, birimKodu);
        birimEkle(birimler, birimSayisi, yeniBirim);
    }
    fclose(birimlerDosya);

    // Çalışan bilgilerini oku ve ilgili birime ekle
    char calisanAdi[256], calisanSoyadi[256];
    float maas;
    int girisYili;

    printf("Çalışan bilgileri okunuyor...\n");
    while (fscanf(calisanlarDosya, "%255[^,],%255[^,],%hu,%f,%d\n",
                  calisanAdi, calisanSoyadi, &birimKodu, &maas, &girisYili) == 5)
    {
        Calisan yeniCalisan = calisanOlustur(calisanAdi, calisanSoyadi, birimKodu, maas, girisYili);

        // Çalışanı ilgili birime ekle
        int birimBulundu = 0;
        for (int i = 0; i < *birimSayisi; i++)
        {
            if ((*birimler)[i].birimKodu == birimKodu)
            {
                int calisanSayisi = 0;

                // Çalışan dizisini genişletmek ve eklemek için uygun bir yer bul
                if ((*birimler)[i].birimCalisanlar != NULL)
                {
                    while ((*birimler)[i].birimCalisanlar[calisanSayisi].calisanAdi != NULL)
                    {
                        calisanSayisi++;
                    }
                }

                calisanEkle(&((*birimler)[i].birimCalisanlar), &calisanSayisi, yeniCalisan);
                birimBulundu = 1;
                break;
            }
        }

        if (!birimBulundu)
        {
            printf("Uyarı: Çalışanın bağlı olduğu birim bulunamadı! Çalışan eklenmedi: %s %s\n",
                   calisanAdi, calisanSoyadi);
        }
    }
    fclose(calisanlarDosya);

    printf("Dosyalardan veriler başarıyla okundu.\n");
}

void birimVeCalisanlariAyriDosyalaraYaz(
    Birim *birimler, int birimSayisi,
    const char *birimlerDosyaAdi, const char *calisanlarDosyaAdi)
{

    // Birimler dosyasını yazmak için aç
    FILE *birimlerDosya = fopen(birimlerDosyaAdi, "w");
    if (birimlerDosya == NULL)
    {
        printf("Birimler dosyası açılamadı: %s\n", birimlerDosyaAdi);
        exit(1);
    }

    // Çalışanlar dosyasını yazmak için aç
    FILE *calisanlarDosya = fopen(calisanlarDosyaAdi, "w");
    if (calisanlarDosya == NULL)
    {
        printf("Çalışanlar dosyası açılamadı: %s\n", calisanlarDosyaAdi);
        fclose(birimlerDosya);
        exit(1);
    }

    // Birimleri dosyaya yaz
    for (int i = 0; i < birimSayisi; i++)
    {
        fprintf(birimlerDosya, "%s,%hu\n", birimler[i].birimAdi, birimler[i].birimKodu);

        // Çalışanları dosyaya yaz
        if (birimler[i].birimCalisanlar != NULL)
        {
            int j = 0;
            while (birimler[i].birimCalisanlar[j].calisanAdi != NULL)
            {
                fprintf(calisanlarDosya, "%s,%s,%hu,%.2f,%d\n",
                        birimler[i].birimCalisanlar[j].calisanAdi,
                        birimler[i].birimCalisanlar[j].calisanSoyadi,
                        birimler[i].birimCalisanlar[j].birimKodu,
                        birimler[i].birimCalisanlar[j].maas,
                        birimler[i].birimCalisanlar[j].girisYili);
                j++;
            }
        }
    }

    // Dosyaları kapat
    fclose(birimlerDosya);
    fclose(calisanlarDosya);

    printf("Birim ve çalışan bilgileri başarıyla dosyalara yazıldı.\n");
}

void freeBirimBellegi(Birim *birimler, int birimSayisi)
{
    for (int i = 0; i < birimSayisi; i++)
    {
        if (birimler[i].birimAdi != NULL)
        {
            free(birimler[i].birimAdi);
            birimler[i].birimAdi = NULL;
        }

        if (birimler[i].birimCalisanlar != NULL)
        {
            int j = 0;
            while (birimler[i].birimCalisanlar[j].calisanAdi != NULL)
            {
                free(birimler[i].birimCalisanlar[j].calisanAdi);
                free(birimler[i].birimCalisanlar[j].calisanSoyadi);
                j++;
            }
            free(birimler[i].birimCalisanlar);
            birimler[i].birimCalisanlar = NULL;
        }
    }
    free(birimler);
}
