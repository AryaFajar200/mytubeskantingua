#include "header.h"

/* ================================================================ */
/* IMPLEMENTASI PRIMITIF DASAR                                      */
/* ================================================================ */

void createList(List &L) {
    L.first = nullptr;
}

adrKantin allocateKantin(string nama) {
    adrKantin P = new elmKantin;
    P->namaKantin = nama;
    P->next = nullptr;
    P->firstMenu = nullptr;
    return P;
}

adrMenu allocateMenu(string namaMenu, int harga, int stok) {
    adrMenu P = new elmMenu;
    P->info.namaMenu = namaMenu;
    P->info.harga = harga;
    P->info.stok = stok;
    P->next = nullptr;
    return P;
}

/* ================================================================ */
/* IMPLEMENTASI FUNGSI BANTUAN (HELPER)                             */
/* ================================================================ */

void insertLastKantin(List &L, adrKantin P) {
    adrKantin Q;
    if (L.first == nullptr) {
        L.first = P;
    } else {
        Q = L.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertLastMenu(adrKantin K, adrMenu P) {
    adrMenu Q;
    if (K->firstMenu == nullptr) {
        K->firstMenu = P;
    } else {
        Q = K->firstMenu;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void deleteFirstKantin(List &L, adrKantin &P) {
    P = L.first;
    if (L.first != nullptr) {
        L.first = L.first->next;
        P->next = nullptr;
    }
}

void deleteAfterKantin(List &L, adrKantin Prec, adrKantin &P) {
    P = Prec->next;
    if (P != nullptr) {
        Prec->next = P->next;
        P->next = nullptr;
    }
}

void deleteFirstMenu(adrKantin K, adrMenu &P) {
    P = K->firstMenu;
    if (P != nullptr) {
        K->firstMenu = P->next;
        P->next = nullptr;
    }
}

void deleteAfterMenu(adrKantin K, adrMenu Prec, adrMenu &P) {
    P = Prec->next;
    if (P != nullptr) {
        Prec->next = P->next;
        P->next = nullptr;
    }
}

/* ================================================================ */
/* IMPLEMENTASI FUNGSIONALITAS UTAMA (A-J)                          */
/* ================================================================ */

// a. Menambahkan data kantin
void insertKantin(List &L, adrKantin P) {
    insertLastKantin(L, P);
}

// c. Mencari kantin tertentu (Search Parent)
// ATURAN: Tidak boleh ada return di dalam loop
adrKantin searchKantin(List L, string namaKantin) {
    adrKantin P = L.first;
    adrKantin foundKantin = nullptr;
    bool found = false;

    while (P != nullptr && !found) {
        if (P->namaKantin == namaKantin) {
            foundKantin = P;
            found = true; // Set flag untuk berhenti
        } else {
            P = P->next;
        }
    }
    return foundKantin;
}

// d. Menambahkan menu pada kantin
void insertMenuToKantin(List &L, string namaKantin, adrMenu P) {
    adrKantin K;
    K = searchKantin(L, namaKantin);
    if (K != nullptr) {
        insertLastMenu(K, P);
        // cout << "Menu berhasil ditambahkan ke " << namaKantin << endl;
    } else {
        cout << "[Error] Kantin '" << namaKantin << "' tidak ditemukan." << endl;
    }
}

// e. Menampilkan menu dalam kantin tertentu
void showMenuByKantin(List L, string namaKantin) {
    adrKantin K;
    K = searchKantin(L, namaKantin);
    adrMenu M;
    if (K != nullptr) {
        cout << "--- Daftar Menu Kantin: " << K->namaKantin << " ---" << endl;
        M = K->firstMenu;
        if (M == nullptr) {
            cout << "(Tidak ada menu)" << endl;
        }
        while (M != nullptr) {
            cout << "- " << M->info.namaMenu 
                 << " | Rp " << M->info.harga 
                 << " | Stok: " << M->info.stok << endl;
            M = M->next;
        }
        cout << "---------------------------------------" << endl;
    } else {
        cout << "[Error] Kantin '" << namaKantin << "' tidak ditemukan." << endl;
    }
}

// f. Menghapus kantin beserta seluruh menunya (Delete Parent Cascade)
void deleteKantinCascade(List &L, string namaKantin) {
    adrKantin P = L.first;
    adrKantin Prec = nullptr;
    adrKantin target = nullptr;
    adrMenu M;
    bool found = false;

    // 1. Mencari Kantin (Parent) dan Predecessor-nya
    while (P != nullptr && !found) {
        if (P->namaKantin == namaKantin) {
            target = P;
            found = true;
        } else {
            Prec = P;
            P = P->next;
        }
    }

    if (found) {
        // 2. Hapus seluruh Menu (Child) terlebih dahulu
        // Ini wajib dilakukan untuk menghindari memory leak (orphaned nodes)
        M = target->firstMenu;
        adrMenu tempMenu;
        while (M != nullptr) {
            tempMenu = M;
            M = M->next;
            delete tempMenu; // Dealokasi memori menu
        }
        target->firstMenu = nullptr;

        // 3. Putus relasi Parent dari List Utama
        adrKantin deletedNode;
        if (Prec == nullptr) {
            // Hapus elemen pertama
            deleteFirstKantin(L, deletedNode);
        } else {
            // Hapus elemen di tengah atau akhir
            deleteAfterKantin(L, Prec, deletedNode);
        }

        // 4. Dealokasi memori Parent
        delete deletedNode;
        cout << "[Success] Kantin '" << namaKantin << "' dan seluruh menunya dihapus." << endl;
    } else {
        cout << "[Error] Kantin '" << namaKantin << "' tidak ditemukan." << endl;
    }
}

// g. Menghapus menu dari kantin tertentu
void deleteMenuFromKantin(List &L, string namaKantin, string namaMenu) {
    adrKantin K;
    adrrMenu M, PrecM;
    K = searchKantin(L, namaKantin);
    
    if (K != nullptr) {
        M = K->firstMenu;
        PrecM = nullptr;
        bool foundMenu = false;

        // Cari menu di dalam list child
        while (M != nullptr && !foundMenu) {
            if (M->info.namaMenu == namaMenu) {
                foundMenu = true;
            } else {
                PrecM = M;
                M = M->next;
            }
        }

        if (foundMenu) {
            adrMenu deletedMenu;
            if (PrecM == nullptr) {
                // Hapus menu pertama
                deleteFirstMenu(K, deletedMenu);
            } else {
                // Hapus menu setelahnya
                deleteAfterMenu(K, PrecM, deletedMenu);
            }
            delete deletedMenu; // Dealokasi
            cout << "[Success] Menu '" << namaMenu << "' dihapus dari " << namaKantin << "." << endl;
        } else {
            cout << "[Error] Menu '" << namaMenu << "' tidak ditemukan di kantin ini." << endl;
        }
    } else {
        cout << "[Error] Kantin '" << namaKantin << "' tidak ditemukan." << endl;
    }
}

// h. Menampilkan seluruh kantin dan daftar menunya
void showAllData(List L) {
    adrKantin K;
    adrMenu M;
    cout << "\n========== DATA KANTIN KAMPUS ==========" << endl;
    if (L.first == nullptr) {
        cout << "Data Kosong." << endl;
    } else {
        K = L.first;
        while (K != nullptr) {
            cout << "KANTIN: " << K->namaKantin << endl;
            
            M = K->firstMenu;
            if (M == nullptr) {
                cout << "   (Belum ada menu)" << endl;
            }
            while (M != nullptr) {
                cout << "   -> " << M->info.namaMenu 
                     << "\t(Rp " << M->info.harga 
                     << ", Stok: " << M->info.stok << ")" << endl;
                M = M->next;
            }
            cout << endl;
            K = K->next;
        }
    }
    cout << "========================================" << endl;
}

// i. Menghitung jumlah menu pada kantin tertentu
int countMenuInKantin(List L, string namaKantin) {
    adrKantin K;
    adrMenu M;
    int count = 0;
    K = searchKantin(L, namaKantin);
    
    if (K != nullptr) {
        M = K->firstMenu;
        while (M != nullptr) {
            count++;
            M = M->next;
        }
    }
    return count;
}

// j. Menampilkan kantin dengan total stok terbanyak dan tersedikit
void showMinMaxStok(List L) {
    adrKantin K;
    adrMenu M;
    if (L.first == nullptr) {
        cout << "Tidak ada data kantin untuk dianalisis." << endl;
    } else {
        K = L.first;
        
        // Inisialisasi Min dan Max dengan data kantin pertama
        string maxKantinName = K->namaKantin;
        string minKantinName = K->namaKantin;
        
        // Hitung stok awal untuk inisialisasi
        int maxStok = 0;
        int minStok = 0;
        
        // Hitung stok kantin pertama
        adrMenu firstM = K->firstMenu;
        while(firstM != nullptr){
            maxStok += firstM->info.stok;
            firstM = firstM->next;
        }
        minStok = maxStok; // Set awal sama

        // Pindah ke kantin kedua (jika ada)
        K = K->next; 

        // Loop sisa kantin
        while (K != nullptr) {
            int currentTotalStok = 0;
            M = K->firstMenu;
            
            // Hitung total stok di kantin saat ini
            while (M != nullptr) {
                currentTotalStok += M->info.stok;
                M = M->next;
            }

            // Cek Max
            if (currentTotalStok > maxStok) {
                maxStok = currentTotalStok;
                maxKantinName = K->namaKantin;
            }
            // Cek Min
            if (currentTotalStok < minStok) {
                minStok = currentTotalStok;
                minKantinName = K->namaKantin;
            }

            K = K->next;
        }

        cout << "\n=== ANALISIS STOK KANTIN ===" << endl;
        cout << "Total Stok Terbanyak  : " << maxKantinName << " (" << maxStok << " item)" << endl;
        cout << "Total Stok Tersedikit : " << minKantinName << " (" << minStok << " item)" << endl;
        cout << "============================" << endl;
    }
}