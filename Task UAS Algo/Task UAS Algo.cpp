#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

// Struct definitions
struct Produk {
    string nama;
    int stok;
    double harga;
};

struct Toko {
    string nama;
    string alamat;
    string telepon;
};

struct Transaksi {
    time_t waktu;
    string jenis;
    string namaProduk;
    string namaToko;
    int jumlah;
    double harga;
};

// Global variables
Produk produk[100];
Toko toko[100];
Transaksi transaksi[1000];
int jumlahProduk = 0;
int jumlahToko = 0;
int jumlahTransaksi = 0;

// Function declarations
void tambahProduk();
void tambahToko();
void tambahStok();
void hapusProduk();
void hapusStok();
void lihatDaftarProduk();
void editHarga();
void hapusToko();
void editNamaToko();
void editAlamatToko();
void editTeleponToko();
void lihatDaftarToko();
void distribusiProduk();
void catatTransaksi(string jenis, string namaProduk, string namaToko, int jumlah, double harga);
void lihatHistoryTransaksi();

// Function implementations
void tambahProduk() {
    if (jumlahProduk >= 100) {
        cout << "Kapasitas produk penuh!\n";
        return;
    }

    cout << "\n=== Tambah Produk Baru ===\n";
    cout << "> Masukkan nama produk: ";
    cin.ignore();
    getline(cin, produk[jumlahProduk].nama);

    cout << "> Masukkan jumlah stok awal: ";
    cin >> produk[jumlahProduk].stok;

    cout << "> Masukkan harga produk: Rp ";
    cin >> produk[jumlahProduk].harga;

    jumlahProduk++;
    cout << "\nProduk berhasil ditambahkan!\n";
}

void tambahToko() {
    if (jumlahToko >= 100) {
        cout << "Kapasitas toko penuh!\n";
        return;
    }

    cout << "\n=== Tambah Toko Baru ===\n";
    cout << "> Masukkan nama toko: ";
    cin.ignore();
    getline(cin, toko[jumlahToko].nama);

    cout << "> Masukkan alamat toko: ";
    getline(cin, toko[jumlahToko].alamat);

    cout << "> Masukkan nomor telepon toko: ";
    getline(cin, toko[jumlahToko].telepon);

    jumlahToko++;
    cout << "\nToko berhasil ditambahkan!\n";
}

void tambahStok() {
    if (jumlahProduk == 0) {
        cout << "\nTidak ada produk yang tersedia.\n";
        return;
    }

    cout << "\n=== Tambah Stok Produk ===\n";
    cout << "\nDaftar Produk:\n";
    for (int i = 0; i < jumlahProduk; i++) {
        cout << i + 1 << ". " << produk[i].nama
            << " (Stok: " << produk[i].stok
            << ", Harga: Rp " << fixed << setprecision(2) << produk[i].harga << ")\n";
    }

    int pilihan, tambahan;
    cout << "\n> Pilih nomor produk (1-" << jumlahProduk << "): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahProduk) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << "> Masukkan jumlah stok yang ditambahkan: ";
    cin >> tambahan;

    if (tambahan <= 0) {
        cout << "Jumlah stok tidak valid!\n";
        return;
    }

    produk[pilihan - 1].stok += tambahan;

    catatTransaksi("Stok Masuk",
        produk[pilihan - 1].nama,
        "",
        tambahan,
        produk[pilihan - 1].harga);

    cout << "\nStok berhasil ditambahkan!\n";
}

void hapusProduk() {
    if (jumlahProduk == 0) {
        cout << "\nTidak ada produk yang tersedia.\n";
        return;
    }

    cout << "\n=== Hapus Produk ===\n";
    cout << "\nDaftar Produk:\n";
    for (int i = 0; i < jumlahProduk; i++) {
        cout << i + 1 << ". " << produk[i].nama
            << " (Stok: " << produk[i].stok
            << ", Harga: Rp " << fixed << setprecision(2) << produk[i].harga << ")\n";
    }

    int pilihan;
    cout << "\n> Pilih nomor produk yang akan dihapus (1-" << jumlahProduk << "): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahProduk) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    string namaProduk = produk[pilihan - 1].nama;

    for (int i = pilihan - 1; i < jumlahProduk - 1; i++) {
        produk[i] = produk[i + 1];
    }
    jumlahProduk--;

    cout << "\nProduk " << namaProduk << " berhasil dihapus!\n";
}

void hapusStok() {
    if (jumlahProduk == 0) {
        cout << "\nTidak ada produk yang tersedia.\n";
        return;
    }

    cout << "\n=== Kurangi Stok Produk ===\n";
    cout << "\nDaftar Produk:\n";
    for (int i = 0; i < jumlahProduk; i++) {
        cout << i + 1 << ". " << produk[i].nama
            << " (Stok: " << produk[i].stok
            << ", Harga: Rp " << fixed << setprecision(2) << produk[i].harga << ")\n";
    }

    int pilihan, pengurangan;
    cout << "\n> Pilih nomor produk (1-" << jumlahProduk << "): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahProduk) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << "> Masukkan jumlah stok yang dikurangi: ";
    cin >> pengurangan;

    if (pengurangan <= 0) {
        cout << "Jumlah pengurangan tidak valid!\n";
        return;
    }

    if (produk[pilihan - 1].stok < pengurangan) {
        cout << "Stok tidak mencukupi!\n";
        return;
    }

    produk[pilihan - 1].stok -= pengurangan;

    catatTransaksi("Stok Keluar",
        produk[pilihan - 1].nama,
        "",
        pengurangan,
        produk[pilihan - 1].harga);

    cout << "\nStok berhasil dikurangi!\n";
}

void lihatDaftarProduk() {
    if (jumlahProduk == 0) {
        cout << "\nTidak ada produk yang tersedia.\n";
        return;
    }

    cout << "\n=== Daftar Produk ===\n";
    cout << setw(5) << "No" << setw(20) << "Nama Produk"
        << setw(10) << "Stok" << setw(15) << "Harga\n";
    cout << string(50, '-') << endl;

    for (int i = 0; i < jumlahProduk; i++) {
        cout << setw(5) << i + 1
            << setw(20) << produk[i].nama
            << setw(10) << produk[i].stok
            << setw(15) << "Rp " << fixed << setprecision(2) << produk[i].harga << endl;
    }
}

void editHarga() {
    if (jumlahProduk == 0) {
        cout << "\nTidak ada produk yang tersedia.\n";
        return;
    }

    cout << "\n=== Ubah Harga Produk ===\n";
    lihatDaftarProduk();

    int pilihan;
    cout << "\n> Pilih nomor produk (1-" << jumlahProduk << "): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahProduk) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    double hargaBaru;
    cout << "> Masukkan harga baru untuk " << produk[pilihan - 1].nama << ": Rp ";
    cin >> hargaBaru;

    if (hargaBaru <= 0) {
        cout << "Harga tidak valid!\n";
        return;
    }

    produk[pilihan - 1].harga = hargaBaru;
    cout << "\nHarga berhasil diperbarui!\n";
}

void hapusToko() {
    if (jumlahToko == 0) {
        cout << "\nTidak ada toko yang tersedia.\n";
        return;
    }

    cout << "\n=== Hapus Toko ===\n";
    lihatDaftarToko();

    int pilihan;
    cout << "\n> Pilih nomor toko yang akan dihapus (1-" << jumlahToko << "): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahToko) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    string namaToko = toko[pilihan - 1].nama;

    for (int i = pilihan - 1; i < jumlahToko - 1; i++) {
        toko[i] = toko[i + 1];
    }
    jumlahToko--;

    cout << "\nToko " << namaToko << " berhasil dihapus!\n";
}

void editNamaToko() {
    if (jumlahToko == 0) {
        cout << "\nTidak ada toko yang tersedia.\n";
        return;
    }

    cout << "\n=== Ubah Nama Toko ===\n";
    lihatDaftarToko();

    int pilihan;
    cout << "\n> Pilih nomor toko (1-" << jumlahToko << "): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahToko) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << "> Masukkan nama baru untuk toko: ";
    cin.ignore();
    getline(cin, toko[pilihan - 1].nama);

    cout << "\nNama toko berhasil diperbarui!\n";
}

void editAlamatToko() {
    if (jumlahToko == 0) {
        cout << "\nTidak ada toko yang tersedia.\n";
        return;
    }

    cout << "\n=== Ubah Alamat Toko ===\n";
    lihatDaftarToko();

    int pilihan;
    cout << "\n> Pilih nomor toko (1-" << jumlahToko << "): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahToko) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << "> Masukkan alamat baru untuk toko: ";
    cin.ignore();
    getline(cin, toko[pilihan - 1].alamat);

    cout << "\nAlamat toko berhasil diperbarui!\n";
}

void editTeleponToko() {
    if (jumlahToko == 0) {
        cout << "\nTidak ada toko yang tersedia.\n";
        return;
    }

    cout << "\n=== Ubah Nomor Telepon Toko ===\n";
    lihatDaftarToko();

    int pilihan;
    cout << "\n> Pilih nomor toko (1-" << jumlahToko << "): ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahToko) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    cout << "> Masukkan nomor telepon baru untuk toko: ";
    cin.ignore();
    getline(cin, toko[pilihan - 1].telepon);

    cout << "\nNomor telepon toko berhasil diperbarui!\n";
}

void lihatDaftarToko() {
    if (jumlahToko == 0) {
        cout << "\nTidak ada toko yang tersedia.\n";
        return;
    }

    cout << "\n=== Daftar Toko ===\n";
    cout << setw(5) << "No" << setw(20) << "Nama Toko"
        << setw(15) << "Telepon" << setw(30) << "Alamat\n";
    cout << string(70, '-') << endl;

    for (int i = 0; i < jumlahToko; i++) {
        cout << setw(5) << i + 1
            << setw(20) << toko[i].nama
            << setw(15) << toko[i].telepon
            << setw(30) << toko[i].alamat << endl;
    }
}

void distribusiProduk() {
    if (jumlahToko == 0 || jumlahProduk == 0) {
        cout << "\nTidak ada toko atau produk yang tersedia.\n";
        return;
    }

    cout << "\n=== Distribusi Produk ===\n";
    lihatDaftarToko();

    int pilihanToko;
    cout << "\n> Pilih nomor toko (1-" << jumlahToko << "): ";
    cin >> pilihanToko;

    if (pilihanToko < 1 || pilihanToko > jumlahToko) {
        cout << "Pilihan toko tidak valid!\n";
        return;
    }

    char lanjut;
    do {
        cout << "\nDaftar Produk Tersedia:\n";
        for (int i = 0; i < jumlahProduk; i++) {
            cout << i + 1 << ". " << produk[i].nama
                << " (Stok: " << produk[i].stok
                << ", Harga: Rp " << fixed << setprecision(2) << produk[i].harga << ")\n";
        }

        int pilihanProduk;
        cout << "\n> Pilih nomor produk (1-" << jumlahProduk << "): ";
        cin >> pilihanProduk;

        if (pilihanProduk < 1 || pilihanProduk > jumlahProduk) {
            cout << "Pilihan produk tidak valid!\n";
            continue;
        }

        int jumlah;
        cout << "> Masukkan jumlah yang akan didistribusikan: ";
        cin >> jumlah;

        if (jumlah <= 0) {
            cout << "Jumlah tidak valid!\n";
            continue;
        }

        if (produk[pilihanProduk - 1].stok < jumlah) {
            cout << "Stok tidak mencukupi!\n";
            continue;
        }

        // Kurangi stok
        produk[pilihanProduk - 1].stok -= jumlah;

        // Catat transaksi
        catatTransaksi("Distribusi",
            produk[pilihanProduk - 1].nama,
            toko[pilihanToko - 1].nama,
            jumlah,
            produk[pilihanProduk - 1].harga);

        cout << "\nBerhasil mendistribusikan " << jumlah << " "
            << produk[pilihanProduk - 1].nama << " ke "
            << toko[pilihanToko - 1].nama << endl;

        cout << "\nIngin mendistribusikan produk lain ke toko yang sama? (y/n): ";
        cin >> lanjut;

    } while (lanjut == 'y' || lanjut == 'Y');
}

void catatTransaksi(string jenis, string namaProduk, string namaToko, int jumlah, double harga) {
    if (jumlahTransaksi >= 1000) {
        cout << "Peringatan: Kapasitas history transaksi penuh!\n";
        return;
    }

    transaksi[jumlahTransaksi].waktu = time(0);
    transaksi[jumlahTransaksi].jenis = jenis;
    transaksi[jumlahTransaksi].namaProduk = namaProduk;
    transaksi[jumlahTransaksi].namaToko = namaToko;
    transaksi[jumlahTransaksi].jumlah = jumlah;
    transaksi[jumlahTransaksi].harga = harga;
    jumlahTransaksi++;
}

void lihatHistoryTransaksi() {
    if (jumlahTransaksi == 0) {
        cout << "\nBelum ada transaksi yang tercatat.\n";
        return;
    }

    cout << "\n=== History Transaksi ===\n\n";
    cout << setw(25) << "Waktu"
        << setw(15) << "Jenis"
        << setw(20) << "Produk"
        << setw(20) << "Toko"
        << setw(10) << "Jumlah"
        << setw(15) << "Total Harga\n";
    cout << string(105, '-') << endl;

    for (int i = 0; i < jumlahTransaksi; i++) {
        char* waktu = ctime(&transaksi[i].waktu);
        waktu[24] = '\0'; // Menghapus newline dari string waktu

        cout << setw(25) << waktu
            << setw(15) << transaksi[i].jenis
            << setw(20) << transaksi[i].namaProduk
            << setw(20) << (transaksi[i].namaToko.empty() ? "-" : transaksi[i].namaToko)
            << setw(10) << transaksi[i].jumlah
            << setw(15) << "Rp " << fixed << setprecision(2)
            << transaksi[i].jumlah * transaksi[i].harga
            << endl;
    }
}

int main() {
    int pilihan;

    cout << "\n=== SISTEM MANAJEMEN INVENTORI ===\n";

    do {
        cout << "\nMenu Utama:\n";
        cout << "1. Kelola Produk\n";
        cout << "2. Kelola Toko\n";
        cout << "3. Distribusi Produk\n";
        cout << "4. History Transaksi\n";
        cout << "5. Keluar\n";
        cout << "\n> Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            int subPilihan;
            do {
                cout << "\nMenu Kelola Produk:\n";
                cout << "1. Tambah Produk Baru\n";
                cout << "2. Tambah Stok\n";
                cout << "3. Hapus Produk\n";
                cout << "4. Kurangi Stok\n";
                cout << "5. Ubah Harga\n";
                cout << "6. Lihat Daftar Produk\n";
                cout << "7. Kembali ke Menu Utama\n";
                cout << "\n> Pilihan Anda: ";
                cin >> subPilihan;

                switch (subPilihan) {
                case 1: tambahProduk(); break;
                case 2: tambahStok(); break;
                case 3: hapusProduk(); break;
                case 4: hapusStok(); break;
                case 5: editHarga(); break;
                case 6: lihatDaftarProduk(); break;
                case 7: cout << "Kembali ke menu utama...\n"; break;
                default: cout << "Pilihan tidak valid!\n";
                }
            } while (subPilihan != 7);
            break;
        }
        case 2: {
            int subPilihan;
            do {
                cout << "\nMenu Kelola Toko:\n";
                cout << "1. Tambah Toko\n";
                cout << "2. Hapus Toko\n";
                cout << "3. Ubah Nama Toko\n";
                cout << "4. Ubah Nomor Telepon\n";
                cout << "5. Ubah Alamat\n";
                cout << "6. Lihat Daftar Toko\n";
                cout << "7. Kembali ke Menu Utama\n";
                cout << "\n> Pilihan Anda: ";
                cin >> subPilihan;

                switch (subPilihan) {
                case 1: tambahToko(); break;
                case 2: hapusToko(); break;
                case 3: editNamaToko(); break;
                case 4: editTeleponToko(); break;
                case 5: editAlamatToko(); break;
                case 6: lihatDaftarToko(); break;
                case 7: cout << "Kembali ke menu utama...\n"; break;
                default: cout << "Pilihan tidak valid!\n";
                }
            } while (subPilihan != 7);
            break;
        }
        case 3: distribusiProduk(); break;
        case 4: lihatHistoryTransaksi(); break;
        case 5: cout << "\nTerima kasih telah menggunakan sistem ini!\n"; break;
        default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 5);

    return 0;
}