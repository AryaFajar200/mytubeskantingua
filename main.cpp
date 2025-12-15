#include "header.h"

/* * PROGRAM UTAMA (MAIN)
 * Menggunakan Loop Menu interaktif
 */

int main() {
    // 1. Inisialisasi List Utama
    List L;
    createList(L);

    // Variabel lokal untuk menampung input user
    int pilihan = -1;
    string namaKantin, namaMenu;
    int harga, stok;
    adrKantin P_K;
    adrMenu P_M;

    // Loop Menu Utama
    while (pilihan != 0) {
        cout << "\n==========================================" << endl;
        cout << "   SISTEM MONITORING STOK KANTIN KAMPUS   " << endl;
        cout << "==========================================" << endl;
        cout << "1.  Tambah Kantin (Insert Parent)" << endl;
        cout << "2.  Tambah Menu ke Kantin (Insert Child)" << endl;
        cout << "3.  Cari Data Kantin (Search Parent)" << endl;
        cout << "4.  Tampilkan Menu Kantin Tertentu" << endl;
        cout << "5.  Hapus Menu (Delete Child)" << endl;
        cout << "6.  Hapus Kantin & Isinya (Delete Cascade)" << endl;
        cout << "7.  Lihat Semua Data (Show All)" << endl;
        cout << "8.  Hitung Jumlah Menu di Kantin" << endl;
        cout << "9.  Laporan Stok Terbanyak/Tersedikit" << endl;
        cout << "0.  Keluar" << endl;
        cout << "==========================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
        case 1:
            cout << "--- TAMBAH KANTIN ---" << endl;
            cout << "Masukkan Nama Kantin: ";
            cin >> namaKantin;
            
            // Alokasi dan Insert
            P_K = allocateKantin(namaKantin);
            insertKantin(L, P_K);
            cout << "[OK] Kantin berhasil didaftarkan." << endl;
            break;

        case 2:
            cout << "--- TAMBAH MENU ---" << endl;
            // Validasi dulu apakah ada kantinnya (Opsional, tapi bagus untuk UX)
            cout << "Masukkan Nama Kantin Tujuan: ";
            cin >> namaKantin;
            
            // Cek keberadaan kantin (gunakan fungsi search yang sudah dibuat)
            if (searchKantin(L, namaKantin) != NULL) {
                cout << "Masukkan Nama Menu: ";
                cin >> namaMenu;
                cout << "Masukkan Harga: ";
                cin >> harga;
                cout << "Masukkan Stok: ";
                cin >> stok;

                P_M = allocateMenu(namaMenu, harga, stok);
                insertMenuToKantin(L, namaKantin, P_M);
                cout << "[OK] Menu berhasil ditambahkan." << endl;
            } else {
                cout << "[Gagal] Kantin tidak ditemukan. Buat kantin dulu." << endl;
            }
            break;

        case 3:
            cout << "--- CARI KANTIN ---" << endl;
            cout << "Masukkan Nama Kantin: ";
            cin >> namaKantin;
            P_K = searchKantin(L, namaKantin);
            if (P_K != NULL) {
                cout << "Ditemukan! Kantin: " << P_K->namaKantin << endl;
            } else {
                cout << "Kantin tidak ditemukan." << endl;
            }
            break;

        case 4:
            cout << "--- LIHAT MENU PER KANTIN ---" << endl;
            cout << "Masukkan Nama Kantin: ";
            cin >> namaKantin;
            showMenuByKantin(L, namaKantin);
            break;

        case 5:
            cout << "--- HAPUS MENU ---" << endl;
            cout << "Masukkan Nama Kantin: ";
            cin >> namaKantin;
            cout << "Masukkan Nama Menu yang dihapus: ";