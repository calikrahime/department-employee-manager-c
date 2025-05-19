
/**
 * @file main.c
 * @description Bu dosya, programın test edildiği ana dosyadır
 * @assignment 1. Ödev
 * @date 23.12.2024
 * @author Rahime Çalık - rahime.calik@stu.fsm.edu.tr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proje1.h"

int main(int argc, char *argv[])
{
    // Komut satırı parametrelerini kontrol et
    if (argc != 3)
    {
        printf("Kullanım: %s <birimler_dosya_adı> <calisanlar_dosya_adı>\n", argv[0]);
        return 1;
    }
    //argv[0]: Programın adı
    const char *birimlerDosyaAdi = argv[1];
    const char *calisanlarDosyaAdi = argv[2];

    Birim *birimler = NULL; // Dinamik birim listesi
    int birimSayisi = 0;    // Birim sayısı başlangıçta 0

    printf("Dosyalardan veriler okunuyor...\n");
    birimVeCalisanlariAyriDosyalardanOku(&birimler, &birimSayisi, birimlerDosyaAdi, calisanlarDosyaAdi);
    tumBirimleriYazdir(birimler, birimSayisi);

    // 1. Birim oluşturma fonksiyonunu test et
    printf("1. Birim Olustur Testi\n");
    Birim bilgisayar = birimOlustur("Bilgisayar", 122);
    Birim yazilim = birimOlustur("Yazilim", 121);
    birimBilgileriniYazdir(bilgisayar);
    birimBilgileriniYazdir(yazilim);

    // 2. Çalışan oluşturma fonksiyonunu test et
    printf("\n2. Calisan Olustur Testi\n");
    Calisan zeynep = calisanOlustur("Zeynep", "Kaya", 122, 5000.0, 2012);
    Calisan enes = calisanOlustur("Enes", "Yılmaz", 122, 4500.0, 2015);
    Calisan bülent = calisanOlustur("Bülent", "Şen", 121, 6000.0, 2020);
    Calisan esma = calisanOlustur("Esma", "Ak", 121, 8000.0, 2013);
    printf("--------------------------\n");

    calisanBilgileriniYazdir(zeynep);
    calisanBilgileriniYazdir(enes);
    calisanBilgileriniYazdir(bülent);
    calisanBilgileriniYazdir(esma);

    // 3. Birim ekleme fonksiyonunu test et
    printf("\n3. Birim Ekle Testi\n");
    birimEkle(&birimler, &birimSayisi, bilgisayar);
    birimEkle(&birimler, &birimSayisi, yazilim);

    tumBirimleriYazdir(birimler, birimSayisi);

    // 4. Çalışan ekleme fonksiyonunu test et
    printf("\n4. Calisan Ekle Testi\n");
    int bilgisayarCalisanSayisi = 0;
    int yazilimCalisanSayisi = 0;

    // Ahmet ve Mehmet Bilgisayar'ye ekleniyor
    calisanEkle(&(birimler[1].birimCalisanlar), &bilgisayarCalisanSayisi, zeynep);
    calisanEkle(&(birimler[1].birimCalisanlar), &bilgisayarCalisanSayisi, enes);

    // Ayşe ve Esma Yazılım'a ekleniyor
    calisanEkle(&(birimler[2].birimCalisanlar), &yazilimCalisanSayisi, bülent);
    calisanEkle(&(birimler[2].birimCalisanlar), &yazilimCalisanSayisi, esma);

    // Tüm birim ve çalışan bilgilerini yazdır
    tumBirimleriYazdir(birimler, birimSayisi);

    // 5. Maaş ortalaması hesaplama fonksiyonunu test et
    printf("\n5. Maas Ortalamasi Testi\n");
    float bilgisayarOrtalama = maasOrtalamasiHesapla(birimler[1], bilgisayarCalisanSayisi);
    printf("Bilgisayar Maas Ortalamasi: %.2f\n", bilgisayarOrtalama);
    float yazilimOrtalama = maasOrtalamasiHesapla(birimler[2], yazilimCalisanSayisi);
    printf("Yazilim Maas Ortalamasi: %.2f\n", yazilimOrtalama);

    // 6. Ortalama maaşın üstünde maaş alan çalışanları listeleyen fonksiyonu test et
    printf("\n6. Ortalama Ustu Maas Alanlar Testi\n");
    ortalamaUstuCalisanlariListele(birimler[1], bilgisayarCalisanSayisi);
    ortalamaUstuCalisanlariListele(birimler[2], yazilimCalisanSayisi);

    // 7. Her birimin en yüksek maaş alan çalışanını yazdıran fonksiyonu test et
    printf("\n7. En Yuksek Maas Alan Calisan Testi\n");
    enYuksekMaasCalisaniniYazdir(birimler, birimSayisi);

    // 8. 10 yıldan fazla çalışanların maaşını güncelleyen fonksiyonu test et
    printf("\n8. Maas Guncelle Testi\n");
    maasGuncelle(birimler, birimSayisi, 8500.0);
    printf("%.2f Esmanın yeni maaşı\n",birimler[2].birimCalisanlar[1].maas);
    tumBirimleriYazdir(birimler, birimSayisi);

    printf("\nBirim ve çalışan bilgileri dosyalara yazılıyor...\n");
    birimVeCalisanlariAyriDosyalaraYaz(birimler, birimSayisi, birimlerDosyaAdi, calisanlarDosyaAdi);

    // Belleği temizle
    printf("\nBellek Temizleme Testi\n");
    freeBirimBellegi(birimler, birimSayisi);

    return 0;
}
