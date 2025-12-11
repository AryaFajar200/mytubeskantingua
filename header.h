#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using namespace std;

typedef struct elmKantin *adrKantin;
typedef struct elmMenu *adrMenu;

struct infotypeMenu {
    string namaMenu;
    int harga;
    int stok;
};

struct infotypeKantin {
    string namaKantin;
    string namaPemilik; 
};

struct elmMenu {
    infotypeMenu info;
    adrMenu next;   
};

struct elmKantin {
    infotypeKantin info;
    adrKantin next;   
    adrMenu firstMenu;  
};

struct ListKantin {
    adrKantin first; 
};




void createList(List &L);

adrKantin createKantin(string nama, string pemilik);

adrMenu createMenu(string nama, int harga, int stok);


/* a. MENAMBAHKAN DATA KANTIN (INSERT PARENT)
 * I.S. List L mungkin kosong.
 * F.S. P menjadi elemen terakhir di List L.
 */
void insertKantin(List &L, adrKantin P);

/* b. MENAMBAHKAN MENU KE KANTIN TERTENTU (INSERT CHILD)
 * I.S. namaKantin tujuan diketahui. P menu baru siap.
 * F.S. P menjadi menu baru di kantin tersebut.
 */
void insertMenu(List &L, string namaKantin, adrMenu P);

/* c. MENCARI KANTIN TERTENTU (SEARCH PARENT)
 * Mengembalikan address kantin jika ditemukan, nullptrptr jika tidak.
 */
adrKantin searchKantin(List L, string namaKantin);

/* d. MENGHAPUS KANTIN BESERTA MENUNYA (DELETE PARENT CASCADE)
 * Menghapus node kantin dan seluruh node menu di bawahnya.
 */
void deleteKantin(List &L, string namaKantin);

/* e. MENGHAPUS MENU SPESIFIK (DELETE CHILD)
 * Menghapus satu menu tertentu dari kantin tertentu.
 */
void deleteMenu(List &L, string namaKantin, string namaMenu);

/* f. MENAMPILKAN SELURUH DATA (SHOW ALL)
 * Menampilkan hirarki Kantin -> Menu.
 */
void showAll(List L);

/* g. MENGHITUNG JUMLAH MENU
 * Mengembalikan total item menu pada satu kantin.
 */
int countMenu(List L, string namaKantin);

/* h. LAPORAN STOK (MIN/MAX)
 * Menampilkan kantin dengan total stok terbanyak dan tersedikit.
 */
void showMinMaxStock(List L);

#endif