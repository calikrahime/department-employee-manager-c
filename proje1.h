
/**
 * @file Proje1.h
 * @description Bu dosya, proje için gerekli yapıların tanımlarını ve fonksiyon prototiplerini içermektedir.
 * @assignment 1. Ödev
 * @date 20.12.2024
 * @author Rahime Çalık - rahime.calik@stu.fsm.edu.tr
 */

// Eğer PROJE1_H tanımlı değilse
#ifndef PROJE1_H
// PROJE1_H adında bir makro tanımlanır.
#define PROJE1_H

#include <stdlib.h> // malloc, realloc, free için
#include <string.h> // strcpy, strlen için
#include <stdio.h>  // printf için

// Header dosyasının içeriği burada yer alır (struct tanımları, fonksiyon prototipleri vb.)

typedef struct
{
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
} Calisan;

typedef struct
{
    char *birimAdi;
    unsigned short int birimKodu;
    Calisan *birimCalisanlar;

} Birim;

Birim birimOlustur(char *birimAdi, unsigned short int birimKodu);
Calisan calisanOlustur(char *adi, char *soyadi, unsigned short int birimKodu, float maas, int girisYili);

// Oluşturulan yeni struct yapılarını diziye ekleyen fonksiyonlar. 2 ayrı fonksiyon yaptım.
void birimEkle(Birim **birimler, int *birimSayisi, Birim yeniBirim);
void calisanEkle(Calisan **calisanlar, int *calisanSayisi, Calisan yeniCalisan);

void calisanBilgileriniYazdir(Calisan c);
void birimBilgileriniYazdir(Birim b);

void tumBirimleriYazdir(Birim *birimler, int birimSayisi);

float maasOrtalamasiHesapla(Birim b, int calisanSayisi);
void ortalamaUstuCalisanlariListele(Birim b, int calisanSayisi);
void enYuksekMaasCalisaniniYazdir(Birim *birimler, int birimSayisi);
void maasGuncelle(Birim *birimler, int birimSayisi, float yeniMaas);

void birimVeCalisanlariAyriDosyalaraYaz(Birim *birimler, int birimSayisi, const char *birimlerDosyaAdi, const char *calisanlarDosyaAdi);
void birimVeCalisanlariAyriDosyalardanOku(Birim **birimler, int *birimSayisi, const char *birimlerDosyaAdi, const char *calisanlarDosyaAdi);

void freeBirimBellegi(Birim *birimler, int birimSayisi);

// Header guard'ı kapatır
#endif
