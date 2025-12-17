#include "header.h"

int main() {
    List L;
    createList(L);

    int pilihan = -1; 
    string namaKantin, namaMenu, kategori;
    int harga, stok, statusInput;
    bool isAvailable;
    adrKantin P_K;
    adrMenu P_M;

    while (pilihan != 0) {
        cout << endl;
        cout << "=== SISTEM KANTIN ===" << endl;
        cout << "1. Tambah Kantin" << endl;
        cout << "2. Tambah Menu (Insert First)" << endl;
        cout << "3. Cari Kantin" << endl;
        cout << "4. Lihat Menu Kantin" << endl;
        cout << "5. Hapus Menu" << endl;
        cout << "6. Hapus Kantin" << endl;
        cout << "7. Lihat Semua Data" << endl;
        cout << "8. Hitung Jumlah Menu" << endl;
        cout << "9. Info Stok Min/Max" << endl;
        cout << "0. Keluarrr" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        cout << endl;

        if (pilihan == 1) {
            cout << "Nama Kantin (tanpa spasi): ";
            cin >> namaKantin;
            P_K = allocateKantin(namaKantin);
            insertKantin(L, P_K); // Parent: Insert Last
        
        } else if (pilihan == 2) {
            cout << "Nama Kantin Tujuan: ";
            cin >> namaKantin;
            
            if (searchKantin(L, namaKantin) != NULL) {
                cout << "Nama Menu: ";
                cin >> namaMenu;
                cout << "Kategori (Makanan/Snack/Minuman): ";
                cin >> kategori;
                cout << "Harga: ";
                cin >> harga;
                cout << "Stok: ";
                cin >> stok;
                cout << "Status (1: Ada, 0: Habis): ";
                cin >> statusInput;

                // Konversi int ke bool
                if (statusInput == 1) isAvailable = true;
                else isAvailable = false;
                
                // [REVISI POIN 2] Alokasi dengan data lengkap
                P_M = allocateMenu(namaMenu, harga, stok, kategori, isAvailable);
                
                // [REVISI POIN 1] Ini akan memanggil Insert First
                insertMenuToKantin(L, namaKantin, P_M); 
            } else {
                cout << "Kantin tidak ditemukan." << endl;
            }

        } else if (pilihan == 3) {
            cout << "Nama Kantin: ";
            cin >> namaKantin;
            P_K = searchKantin(L, namaKantin);
            if (P_K != NULL) {
                cout << "Ditemukan: " << P_K->namaKantin << endl;
            } else {
                cout << "Tidak ditemukan." << endl;
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
            cout << "Selesai." << endl;
            
        } else {
            cout << "Pilihan salah." << endl;
        }
    }

    return 0;
}