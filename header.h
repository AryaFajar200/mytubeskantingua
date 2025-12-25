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
    string kategori;    
    bool isAvailable;   
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

void createList(List &L);
adrKantin allocateKantin(string nama);
adrMenu allocateMenu(string namaMenu, int harga, int stok, string kategori, bool isAvailable);

void insertKantin(List &L, adrKantin P); 

adrKantin searchKantin(List L, string namaKantin);

void insertMenuToKantin(List &L, string namaKantin, adrMenu P);

void showMenuByKantin(List L, string namaKantin);

void deleteKantin(List &L, string namaKantin);

void deleteMenuFromKantin(List &L, string namaKantin, string namaMenu);

void showAllData(List L);

int countMenuInKantin(List L, string namaKantin);

void showMinMaxStok(List L);

void insertLastKantin(List &L, adrKantin P);

void insertFirstMenu(adrKantin K, adrMenu P);

void deleteFirstKantin(List &L, adrKantin &P);

void deleteAfterKantin(List &L, adrKantin Prec, adrKantin &P);

void deleteFirstMenu(adrKantin K, adrMenu &P);

void deleteAfterMenu(adrKantin K, adrMenu Prec, adrMenu &P);

#endif