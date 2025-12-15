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
};

struct elmMenu {
    infotypeMenu info;
    adrMenu next; 
};

struct elmKantin {
    string namaKantin;
    adrKantin next;      
    adrMenu firstMenu;   // Relasi ke Child
};

struct List {
    adrKantin first; 
};

// --- PRIMITIF DASAR ---
void createList(List &L);
adrKantin allocateKantin(string nama);
adrMenu allocateMenu(string namaMenu, int harga, int stok);

// --- FUNGSIONALITAS UTAMA (SESUAI POIN a-j) ---

// a. Menambahkan data kantin (Insert Parent)
void insertKantin(List &L, adrKantin P); 

// b. Menambahkan data menu (Hanya alokasi/persiapan data)
// (Fungsi ini diwakili oleh allocateMenu di atas, dipanggil sebelum insert)

// c. Mencari kantin tertentu (Search Parent)
adrKantin searchKantin(List L, string namaKantin);

// d. Menambahkan menu pada kantin (Insert Child to Parent)
void insertMenuToKantin(List &L, string namaKantin, adrMenu P);

// e. Menampilkan menu dalam kantin tertentu (Show Child of Parent)
void showMenuByKantin(List L, string namaKantin);

// f. Menghapus kantin beserta seluruh menunya (Delete Parent Cascade)
void deleteKantinCascade(List &L, string namaKantin);

// g. Menghapus menu dari kantin tertentu (Delete Child)
void deleteMenuFromKantin(List &L, string namaKantin, string namaMenu);

// h. Menampilkan seluruh kantin dan daftar menunya (Show All)
void showAllData(List L);

// i. Menghitung jumlah menu pada kantin tertentu
int countMenuInKantin(List L, string namaKantin);

// j. Menampilkan kantin dengan total stok terbanyak dan tersedikit
void showMinMaxStok(List L);

// --- FUNGSI BANTUAN (HELPER) ---
// Digunakan internal untuk kerapian kode insert/delete
void insertLastKantin(List &L, adrKantin P);
void insertLastMenu(adrKantin K, adrMenu P);
void deleteFirstKantin(List &L, adrKantin &P);
void deleteAfterKantin(List &L, adrKantin Prec, adrKantin &P);
void deleteFirstMenu(adrKantin K, adrMenu &P);
void deleteAfterMenu(adrKantin K, adrMenu Prec, adrMenu &P);

#endif