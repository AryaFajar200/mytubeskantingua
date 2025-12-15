#include "header.h"

/* ================================================================ */
/* IMPLEMENTASI PRIMITIF DASAR                                      */
/* ================================================================ */

void createList(List &L) {
    L.first = NULL;
}

adrKantin allocateKantin(string nama) {
    adrKantin P = new elmKantin;
    P->namaKantin = nama;
    P->next = NULL;
    P->firstMenu = NULL; // Pastikan pointer child di-null-kan saat inisialisasi
    return P;
}

adrMenu allocateMenu(string namaMenu, int harga, int stok) {
    adrMenu P = new elmMenu;
    P->info.namaMenu = namaMenu;
    P->info.harga = harga;
    P->info.stok = stok;
    P->next = NULL;
    return P;
}

/* ================================================================ */
/* IMPLEMENTASI FUNGSI BANTUAN (HELPER)                             */
/* ================================================================ */

void insertLastKantin(List &L, adrKantin P) {
    if (L.first == NULL) {
        L.first = P;
    } else {
        adrKantin Q = L.first;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertLastMenu(adrKantin K, adrMenu P) {
    if (K->firstMenu == NULL) {
        K->firstMenu = P;
    } else {
        adrMenu Q = K->firstMenu;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void deleteFirstKantin(List &L, adrKantin &P) {
    P = L.first;
    if (L.first != NULL) {
        L.first = L.first->next;
        P->next = NULL;
    }
}

void deleteAfterKantin(List &L, adrKantin Prec, adrKantin &P) {
    P = Prec->next;
    if (P != NULL) {
        Prec->next = P->next;
        P->next = NULL;
    }
}

void deleteFirstMenu(adrKantin K, adrMenu &P) {
    P = K->firstMenu;
    if (P != NULL) {
        K->firstMenu = P->next;
        P->next = NULL;
    }
}

void deleteAfterMenu(adrKantin K, adrMenu Prec, adrMenu &P) {
    P = Prec->next;
    if (P != NULL) {
        Prec->next = P->next;
        P->next = NULL;
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
    adrKantin foundKantin = NULL;
    bool found = false;

    while (P != NULL && !found) {
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
    adrKantin K = searchKantin(L, namaKantin);
    if (K != NULL) {
        insertLastMenu(K, P);
        // cout << "Menu berhasil ditambahkan ke " << namaKantin << endl;
    } else {
        cout << "[Error] Kantin '" << namaKantin << "' tidak ditemukan." << endl;
    }
}

// e. Menampilkan menu dalam kantin tertentu
void showMenuByKantin(List L, string namaKantin) {
    adrKantin K = searchKantin(L, namaKantin);
    if (K != NULL) {
        cout << "--- Daftar Menu Kantin: " << K->namaKantin << " ---" << endl;
        adrMenu M = K->firstMenu;
        if (M == NULL) {
            cout << "(Tidak ada menu)" << endl;
        }
        while (M != NULL) {
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
    adrKantin Prec = NULL;
    adrKantin target = NULL;
    bool found = false;

    // 1. Mencari Kantin (Parent) dan Predecessor-nya
    while (P != NULL && !found) {
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
        adrMenu M = target->firstMenu;
        adrMenu tempMenu;
        while (M != NULL) {
            tempMenu = M;
            M = M->next;
            delete tempMenu; // Dealokasi memori menu
        }
        target->firstMenu = NULL;

        // 3. Putus relasi Parent dari List Utama
        adrKantin deletedNode;
        if (Prec == NULL) {
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
    adrKantin K = searchKantin(L, namaKantin);
    
    if (K != NULL) {
        adrMenu M = K->firstMenu;
        adrMenu PrecM = NULL;
        bool foundMenu = false;

        // Cari menu di dalam list child
        while (M != NULL && !foundMenu) {
            if (M->info.namaMenu == namaMenu) {
                foundMenu = true;
            } else {
                PrecM = M;
                M = M->next;
            }
        }

        if (foundMenu) {
            adrMenu deletedMenu;
            if (PrecM == NULL) {
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
    cout << "\n========== DATA KANTIN KAMPUS ==========" << endl;
    if (L.first == NULL) {
        cout << "Data Kosong." << endl;
    } else {
        adrKantin K = L.first;
        while (K != NULL) {
            cout << "KANTIN: " << K->namaKantin << endl;
            
            adrMenu M = K->firstMenu;
            if (M == NULL) {
                cout << "   (Belum ada menu)" << endl;
            }
            while (M != NULL) {
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
    int count = 0;
    adrKantin K = searchKantin(L, namaKantin);
    
    if (K != NULL) {
        adrMenu M = K->firstMenu;
        while (M != NULL) {
            count++;
            M = M->next;
        }
    }
    return count;
}

// j. Menampilkan kantin dengan total stok terbanyak dan tersedikit
void showMinMaxStok(List L) {
    if (L.first == NULL) {
        cout << "Tidak ada data kantin untuk dianalisis." << endl;
    } else {
        adrKantin K = L.first;
        
        // Inisialisasi Min dan Max dengan data kantin pertama
        string maxKantinName = K->namaKantin;
        string minKantinName = K->namaKantin;
        
        // Hitung stok awal untuk inisialisasi
        int maxStok = 0;
        int minStok = 0;
        
        // Hitung stok kantin pertama
        adrMenu firstM = K->firstMenu;
        while(firstM != NULL){
            maxStok += firstM->info.stok;
            firstM = firstM->next;
        }
        minStok = maxStok; // Set awal sama

        // Pindah ke kantin kedua (jika ada)
        K = K->next; 

        // Loop sisa kantin
        while (K != NULL) {
            int currentTotalStok = 0;
            adrMenu M = K->firstMenu;
            
            // Hitung total stok di kantin saat ini
            while (M != NULL) {
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