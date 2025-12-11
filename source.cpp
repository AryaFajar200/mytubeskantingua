#include "header.h"


void createList(List &L) {
    L.first = nullptr;
}

bool isEmpty(List L) {
    return L.first == nullptr; 
}

adrKantin createKantin(string nama, string pemilik) {
    adrKantin P = new elmKantin;
    P->info.namaKantin = nama;
    P->info.namaPemilik = pemilik;
    P->next = nullptr;
    P->child = nullptr;
    return P;
}

adrMenu createMenu(string nama, int harga, int stok) {
    adrMenu P = new elmMenu;
    P->info.namaMenu = nama;
    P->info.harga = harga;
    P->info.stok = stok;
    P->next = nullptr;
    return P;
}


adrKantin searchKantin(List L, string namaKantin) {
    adrKantin P = L.first;
    adrKantin found = nullptr;
    bool ketemu = false;

    // Traversal menggunakan Boolean Flag (Sesuai Aturan Akademik)
    while (P != nullptr && !ketemu) {
        if (P->info.namaKantin == namaKantin) {
            found = P;
            ketemu = true; // Flag diubah agar loop berhenti
        } else {
            P = P->next;
        }
    }
    return found;
}


void insertKantin(List &L, adrKantin P) {
    if (isEmpty(L)) {
        L.first = P;
    } else {
        adrKantin Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertMenu(List &L, string namaKantin, adrMenu P) {
    adrKantin K = searchKantin(L, namaKantin);

    if (K != nullptr) {
        if (K->child == nullptr) {
            K->child = P;
        } else {
            adrMenu M = K->child;
            while (M->next != nullptr) {
                M = M->next;
            }
            M->next = P;
        }
        cout << "[BERHASIL] Menu " << P->info.namaMenu 
             << " ditambahkan ke kantin " << namaKantin << "." << endl;
    } else {
        cout << "[GAGAL] Kantin " << namaKantin << " tidak ditemukan." << endl;
    }
}


void showAll(List L) {
    if (isEmpty(L)) {
        cout << "[INFO] Belum ada data kantin yang terdaftar." << endl;
    } else {
        adrKantin K = L.first;
        int i = 1;
        while (K != nullptr) {
            cout << "----------------------------------------" << endl;
            cout << i << ". KANTIN: " << K->info.namaKantin 
                 << " (Owner: " << K->info.namaPemilik << ")" << endl;
            cout << "   DAFTAR MENU:" << endl;
            
            adrMenu M = K->child;
            if (M == nullptr) {
                cout << "   (Belum ada menu tersedia)" << endl;
            } else {
                while (M != nullptr) {
                    cout << "   - " << M->info.namaMenu 
                         << "\t| Harga: Rp " << M->info.harga 
                         << "\t| Stok: " << M->info.stok << endl;
                    M = M->next;
                }
            }
            K = K->next; 
            i++;
        }
        cout << "----------------------------------------" << endl;
    }
}

int countMenu(List L, string namaKantin) {
    adrKantin K = searchKantin(L, namaKantin);
    int jumlah = 0;
    
    if (K != nullptr) {
        adrMenu M = K->child;
        while (M != nullptr) {
            jumlah++;
            M = M->next;
        }
    }
    return jumlah;
}

void showMinMaxStock(List L) {
    if (isEmpty(L)) {
        cout << "[INFO] List kantin kosong." << endl;
    } else {
        adrKantin K = L.first;
        
        // Inisialisasi variabel komparator
        string maxKantin = "-", minKantin = "-";
        int maxStok = -1; 
        int minStok = 2147483647; // Nilai integer max sebagai dummy awal
        
        bool adaData = false; // Flag untuk memastikan minimal ada 1 kantin terproses

        while (K != nullptr) {
            int totalStok = 0;
            adrMenu M = K->child;
            
            // Hitung total stok menu di kantin ini
            while (M != nullptr) {
                totalStok = totalStok + M->info.stok;
                M = M->next;
            }

            // Cek Maksimum
            if (totalStok > maxStok) {
                maxStok = totalStok;
                maxKantin = K->info.namaKantin;
            }
            
            // Cek Minimum
            if (totalStok < minStok) {
                minStok = totalStok;
                minKantin = K->info.namaKantin;
            }
            
            adaData = true;
            K = K->next;
        }

        if (adaData) {
            cout << "\n=== LAPORAN STOK KANTIN ===" << endl;
            cout << "Total Stok Terbanyak : " << maxKantin << " (" << maxStok << " item)" << endl;
            cout << "Total Stok Tersedikit: " << minKantin << " (" << minStok << " item)" << endl;
        }
    }
}