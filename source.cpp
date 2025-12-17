#include "header.h"

/* ================================================================ */
/* IMPLEMENTASI PRIMITIF DASAR                                      */
/* ================================================================ */

// I.S. Sembarang
// F.S. Terbentuk List L kosong (L.first = NULL)
void createList(List &L) {
    L.first = NULL;
}

// I.S. Sembarang
// F.S. Mengembalikan address P yang berisi data kantin, next=NULL, firstMenu=NULL
adrKantin allocateKantin(string nama) {
    adrKantin P = new elmKantin;
    P->namaKantin = nama;
    P->next = NULL;
    P->firstMenu = NULL;
    return P;
}

// I.S. Sembarang
// F.S. Mengembalikan address P yang berisi data menu lengkap (termasuk kategori & status)
adrMenu allocateMenu(string namaMenu, int harga, int stok, string kategori, bool isAvailable) {
    adrMenu P = new elmMenu;
    P->info.namaMenu = namaMenu;
    P->info.harga = harga;
    P->info.stok = stok;
    P->info.kategori = kategori;
    P->info.isAvailable = isAvailable;
    P->next = NULL;
    return P;
}

/* ================================================================ */
/* IMPLEMENTASI FUNGSI BANTUAN (HELPER)                             */
/* ================================================================ */

// I.S. List L mungkin kosong, P terdefinisi
// F.S. P ditambahkan sebagai elemen TERAKHIR di List L
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

// [REVISI POIN 1] Implementasi Insert First untuk Menu
// I.S. Kantin K terdefinisi, P menu terdefinisi
// F.S. P menjadi elemen PERTAMA di list menu milik Kantin K
void insertFirstMenu(adrKantin K, adrMenu P) {
    // Logika Insert First SLL
    P->next = K->firstMenu;
    K->firstMenu = P;
}

// I.S. List L tidak kosong
// F.S. Elemen pertama List L dihapus, P berisi elemen yang dihapus
void deleteFirstKantin(List &L, adrKantin &P) {
    P = L.first;
    if (L.first != NULL) {
        L.first = L.first->next;
        P->next = NULL;
    }
}

// I.S. Prec terdefinisi dan bukan elemen terakhir
// F.S. Elemen setelah Prec dihapus, P berisi elemen yang dihapus
void deleteAfterKantin(List &L, adrKantin Prec, adrKantin &P) {
    P = Prec->next;
    if (P != NULL) {
        Prec->next = P->next;
        P->next = NULL;
    }
}

// I.S. List Menu pada K tidak kosong
// F.S. Elemen menu pertama dihapus, P berisi menu yang dihapus
void deleteFirstMenu(adrKantin K, adrMenu &P) {
    P = K->firstMenu;
    if (P != NULL) {
        K->firstMenu = P->next;
        P->next = NULL;
    }
}

// I.S. Prec terdefinisi dalam list menu K
// F.S. Menu setelah Prec dihapus, P berisi menu yang dihapus
void deleteAfterMenu(adrKantin K, adrMenu Prec, adrMenu &P) {
    P = Prec->next;
    if (P != NULL) {
        Prec->next = P->next;
        P->next = NULL;
    }
}

/* ================================================================ */
/* IMPLEMENTASI FUNGSIONALITAS UTAMA                                */
/* ================================================================ */

// I.S. L mungkin kosong, P sudah dialokasi
// F.S. P masuk ke L sebagai elemen terakhir (Parent: Insert Last)
void insertKantin(List &L, adrKantin P) {
    insertLastKantin(L, P);
}

// I.S. L terdefinisi, namaKantin terdefinisi
// F.S. Mengembalikan address kantin jika ketemu, NULL jika tidak
// Catatan: Menggunakan boolean flag (No return in loop)
adrKantin searchKantin(List L, string namaKantin) {
    adrKantin P = L.first;
    adrKantin foundKantin = NULL;
    bool found = false;

    while (P != NULL && !found) {
        if (P->namaKantin == namaKantin) {
            foundKantin = P;
            found = true;
        } else {
            P = P->next;
        }
    }
    return foundKantin;
}

// I.S. L terdefinisi, P sudah dialokasi
// F.S. Jika kantin ada, P masuk sebagai elemen PERTAMA menu (Child: Insert First)
void insertMenuToKantin(List &L, string namaKantin, adrMenu P) {
    adrKantin K = searchKantin(L, namaKantin);
    if (K != NULL) {
        // [REVISI POIN 1] Memanggil Insert First
        insertFirstMenu(K, P);
    } else {
        cout << "[Error] Kantin '" << namaKantin << "' tidak ditemukan." << endl;
    }
}

// I.S. L terdefinisi
// F.S. Menampilkan seluruh menu pada kantin tertentu beserta atributnya
void showMenuByKantin(List L, string namaKantin) {
    adrKantin K = searchKantin(L, namaKantin);
    if (K != NULL) {
        cout << "--- Daftar Menu Kantin: " << K->namaKantin << " ---" << endl;
        adrMenu M = K->firstMenu;
        if (M == NULL) {
            cout << "(Tidak ada menu)" << endl;
        }
        while (M != NULL) {
            // [REVISI POIN 2] Menampilkan Kategori & Status
            string status = (M->info.isAvailable) ? "Tersedia" : "Habis";
            cout << "- " << M->info.namaMenu 
                 << " [" << M->info.kategori << "] "
                 << " | Rp " << M->info.harga 
                 << " | Stok: " << M->info.stok 
                 << " | Status: " << status << endl;
            M = M->next;
        }
        cout << "---------------------------------------" << endl;
    } else {
        cout << "[Error] Kantin '" << namaKantin << "' tidak ditemukan." << endl;
    }
}

// I.S. L terdefinisi
// F.S. Kantin dan seluruh isi menunya terhapus dari List
void deleteKantinCascade(List &L, string namaKantin) {
    adrKantin P = L.first;
    adrKantin Prec = NULL;
    adrKantin target = NULL;
    bool found = false;

    // Cari Kantin
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
        // Hapus SEMUA menu (Child)
        adrMenu M = target->firstMenu;
        adrMenu tempMenu;
        while (M != NULL) {
            tempMenu = M;
            M = M->next;
            delete tempMenu;
        }
        target->firstMenu = NULL;

        // Hapus Kantin (Parent)
        adrKantin deletedNode;
        if (Prec == NULL) {
            deleteFirstKantin(L, deletedNode);
        } else {
            deleteAfterKantin(L, Prec, deletedNode);
        }
        delete deletedNode;
        cout << "[Success] Kantin '" << namaKantin << "' dihapus." << endl;
    } else {
        cout << "[Error] Kantin tidak ditemukan." << endl;
    }
}

// I.S. L terdefinisi
// F.S. Menu spesifik terhapus dari kantin tertentu
void deleteMenuFromKantin(List &L, string namaKantin, string namaMenu) {
    adrKantin K = searchKantin(L, namaKantin);
    
    if (K != NULL) {
        adrMenu M = K->firstMenu;
        adrMenu PrecM = NULL;
        bool foundMenu = false;

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
                deleteFirstMenu(K, deletedMenu);
            } else {
                deleteAfterMenu(K, PrecM, deletedMenu);
            }
            delete deletedMenu;
            cout << "[Success] Menu '" << namaMenu << "' dihapus." << endl;
        } else {
            cout << "[Error] Menu tidak ditemukan." << endl;
        }
    } else {
        cout << "[Error] Kantin tidak ditemukan." << endl;
    }
}

// I.S. L terdefinisi
// F.S. Menampilkan seluruh struktur data (Parent & Child)
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
                // [REVISI POIN 2] Tampilkan atribut lengkap
                string status = (M->info.isAvailable) ? "OK" : "X";
                cout << "   -> " << M->info.namaMenu 
                     << " (" << M->info.kategori << ") "
                     << "\tRp" << M->info.harga 
                     << "\tStok:" << M->info.stok 
                     << "\t[" << status << "]" << endl;
                M = M->next;
            }
            cout << endl;
            K = K->next;
        }
    }
    cout << "========================================" << endl;
}

// I.S. L terdefinisi
// F.S. Mengembalikan jumlah menu yang ada di kantin tertentu
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

// I.S. L terdefinisi
// F.S. Menampilkan info kantin dengan stok total Max dan Min
void showMinMaxStok(List L) {
    if (L.first == NULL) {
        cout << "Data kosong." << endl;
    } else {
        adrKantin K = L.first;
        
        string maxKantinName = K->namaKantin;
        string minKantinName = K->namaKantin;
        
        // Helper lokal untuk hitung stok
        int maxStok = 0;
        adrMenu firstM = K->firstMenu;
        while(firstM != NULL){
            maxStok += firstM->info.stok;
            firstM = firstM->next;
        }
        int minStok = maxStok;

        K = K->next; 

        while (K != NULL) {
            int currentTotalStok = 0;
            adrMenu M = K->firstMenu;
            while (M != NULL) {
                currentTotalStok += M->info.stok;
                M = M->next;
            }

            if (currentTotalStok > maxStok) {
                maxStok = currentTotalStok;
                maxKantinName = K->namaKantin;
            }
            if (currentTotalStok < minStok) {
                minStok = currentTotalStok;
                minKantinName = K->namaKantin;
            }
            K = K->next;
        }

        cout << "\n=== ANALISIS STOK ===" << endl;
        cout << "Max Stok: " << maxKantinName << " (" << maxStok << ")" << endl;
        cout << "Min Stok: " << minKantinName << " (" << minStok << ")" << endl;
    }
}