#include "header.h"

int main() {
    List L;
    createList(L);

    // Variabel untuk menampung input
    int pilihan = -1;
    string namaKantin, namaMenu;
    int harga, stok;
    adrKantin P_K;
    adrMenu P_M;

    // Loop berjalan selama pilihan bukan 0
    while (pilihan != 0) {
        cout << endl;
        cout << "=== MENU KANTIN ===" << endl;
        cout << "1. Tambah Kantin" << endl;
        cout << "2. Tambah Menu" << endl;
        cout << "3. Cari Kantin" << endl;
        cout << "4. Lihat Menu Kantin" << endl;
        cout << "5. Hapus Menu" << endl;
        cout << "6. Hapus Kantin" << endl;
        cout << "7. Lihat Semua Data" << endl;
        cout << "8. Hitung Jumlah Menu" << endl;
        cout << "9. Info Stok Terbanyak/Sedikit" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        cout << endl;

        if (pilihan == 1) {
            cout << "Nama Kantin: ";
            cin >> namaKantin;
            P_K = allocateKantin(namaKantin);
            insertKantin(L, P_K);
        
        } else if (pilihan == 2) {
            cout << "Nama Kantin Tujuan: ";
            cin >> namaKantin;
            // Cek dulu apakah kantin ada
            if (searchKantin(L, namaKantin) != NULL) {
                cout << "Nama Menu: ";
                cin >> namaMenu;
                cout << "Harga: ";
                cin >> harga;
                cout << "Stok: ";
                cin >> stok;
                
                P_M = allocateMenu(namaMenu, harga, stok);
                insertMenuToKantin(L, namaKantin, P_M);
            } else {
                cout << "Kantin tidak ditemukan." << endl;
            }

        } else if (pilihan == 3) {
            cout << "Nama Kantin dicari: ";
            cin >> namaKantin;
            P_K = searchKantin(L, namaKantin);
            if (P_K != NULL) {
                cout << "Kantin ditemukan." << endl;
            } else {
                cout << "Kantin tidak ditemukan." << endl;
            }

        } else if (pilihan == 4) {
            cout << "Nama Kantin: ";
            cin >> namaKantin;
            showMenuByKantin(L, namaKantin);

        } else if (pilihan == 5) {
            cout << "Nama Kantin: ";
            cin >> namaKantin;
            cout << "Nama Menu dihapus: ";
            cin >> namaMenu;
            deleteMenuFromKantin(L, namaKantin, namaMenu);

        } else if (pilihan == 6) {
            cout << "Nama Kantin dihapus: ";
            cin >> namaKantin;
            deleteKantinCascade(L, namaKantin);

        } else if (pilihan == 7) {
            showAllData(L);

        } else if (pilihan == 8) {
            cout << "Nama Kantin: ";
            cin >> namaKantin;
            cout << "Jumlah Menu: " << countMenuInKantin(L, namaKantin) << endl;

        } else if (pilihan == 9) {
            showMinMaxStok(L);

        } else if (pilihan == 0) {
            cout << "Keluar program." << endl;
            
        } else {
            cout << "Pilihan salah." << endl;
        }
    }

    return 0;
}