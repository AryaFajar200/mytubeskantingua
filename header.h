#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using namespace std;

// --- DEFINISI TYPE DATA ---
typedef struct elmKantin *adrKantin;
typedef struct elmMenu *adrMenu;

struct infotypeMenu {
    string namaMenu;
    int harga;
    int stok;
    // [REVISI POIN 2] Atribut Tambahan
    string kategori;    // Makanan Berat, Snack, Minuman
    bool isAvailable;   // 1 (Tersedia) atau 0 (Habis/Tidak aktif)
};

struct elmMenu {
    infotypeMenu info;
    adrMenu next; 
};

struct elmKantin {
    string namaKantin;
    adrKantin next;      
    adrMenu firstMenu;   
};

struct List {
    adrKantin first; 
};

// --- PRIMITIF DASAR ---
void createList(List &L);
// [REVISI POIN 2] Update parameter alokasi
adrKantin allocateKantin(string nama);
adrMenu allocateMenu(string namaMenu, int harga, int stok, string kategori, bool isAvailable);

// --- FUNGSIONALITAS UTAMA ---

// a. Menambahkan data kantin (Insert Parent - Tetap Insert Last)
void insertKantin(List &L, adrKantin P); 

// c. Mencari kantin tertentu (Search Parent)
adrKantin searchKantin(List L, string namaKantin);

// d. Menambahkan menu pada kantin (Insert Child - UBAH JADI INSERT FIRST)
void insertMenuToKantin(List &L, string namaKantin, adrMenu P);

// e. Menampilkan menu dalam kantin tertentu
void showMenuByKantin(List L, string namaKantin);

// f. Menghapus kantin beserta seluruh menunya (Delete Parent Cascade)
void deleteKantinCascade(List &L, string namaKantin);

// g. Menghapus menu dari kantin tertentu
void deleteMenuFromKantin(List &L, string namaKantin, string namaMenu);

// h. Menampilkan seluruh kantin dan daftar menunya
void showAllData(List L);

// i. Menghitung jumlah menu pada kantin tertentu
int countMenuInKantin(List L, string namaKantin);

// j. Menampilkan kantin dengan total stok terbanyak dan tersedikit
void showMinMaxStok(List L);

// --- FUNGSI BANTUAN (HELPER) ---
void insertLastKantin(List &L, adrKantin P);

// [REVISI POIN 1] Ubah helper child menjadi Insert First
void insertFirstMenu(adrKantin K, adrMenu P);

void deleteFirstKantin(List &L, adrKantin &P);
void deleteAfterKantin(List &L, adrKantin Prec, adrKantin &P);
void deleteFirstMenu(adrKantin K, adrMenu &P);
void deleteAfterMenu(adrKantin K, adrMenu Prec, adrMenu &P);

#endif