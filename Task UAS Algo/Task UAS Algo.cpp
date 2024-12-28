#include <iostream>
#include <string>
using namespace std;

string namaProduk[100];
int stokProduk[100];
double hargaProduk[100];
int jumlahProduk = 0;

string penjualanProduk[1000];
int penjualanJumlah[1000];
double penjualanTotal[1000];
int jumlahPenjualan = 0;

string namaToko[100];
int jumlahToko = 0;
string penjualanToko[1000];

void tambahToko() {
    if (jumlahToko >= 100) {
        cout << "Kapasitas toko penuh!\n";
        return;
    }

    cout << "\n== Tambah Toko ==\n";
    cout << "Nama Toko: ";
    cin.ignore(); 
    getline(cin, namaToko[jumlahToko]);

    jumlahToko++;
    cout << "Toko berhasil ditambahkan!\n";
}

void lihatToko() {
    if (jumlahToko == 0) {
        cout << "Tidak ada toko terdaftar!\n";
        return;
    }

    cout << "\n== Daftar Toko ==\n";
    cout << "No | Nama Toko\n";
    cout << "------------------------\n";

    for (int i = 0; i < jumlahToko; i++) {
        cout << (i + 1) << ". " << namaToko[i] << endl;
    }
}

void tambahProduk() {
    if (jumlahProduk >= 100) {
        cout << "Kapasitas penuh!\n";
        return;
    }

    cout << "\n== Tambah Produk ==\n";
    cout << "Nama produk: ";
    cin.ignore();
    getline(cin, namaProduk[jumlahProduk]);

    cout << "Jumlah stok: ";
    cin >> stokProduk[jumlahProduk];

    cout << "Harga: Rp ";
    cin >> hargaProduk[jumlahProduk];

    jumlahProduk++;
    cout << "Produk berhasil ditambahkan!\n";
}

void lihatProduk() {
    if (jumlahProduk == 0) {
        cout << "Tidak ada produk!\n";
        return;
    }

    cout << "\n== Daftar Produk ==\n";
    cout << "No | Nama Produk | Stok | Harga\n";
    cout << "--------------------------------\n";

    for (int i = 0; i < jumlahProduk; i++) {
        cout << (i + 1) << ". " << namaProduk[i] << " | "
            << stokProduk[i] << " | Rp "
            << hargaProduk[i] << endl;
    }
}

void tambahStok() {
    if (jumlahProduk == 0) {
        cout << "Tidak ada produk!\n";
        return;
    }

    lihatProduk();
    int pilihan, tambahan;
    cout << "Pilih nomor produk: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahProduk) {
        cout << "Produk tidak valid!\n";
        return;
    }

    cout << "Jumlah tambahan: ";
    cin >> tambahan;

    if (tambahan <= 0) {
        cout << "Jumlah tidak valid!\n";
        return;
    }

    stokProduk[pilihan - 1] += tambahan;
    cout << "Stok berhasil ditambahkan!\n";
}

void kurangiStok() {
    if (jumlahProduk == 0) {
        cout << "Tidak ada produk!\n";
        return;
    }

    lihatProduk(); 
    int pilihan, kurang;
    cout << "Pilih nomor produk: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahProduk) {
        cout << "Produk tidak valid!\n";
        return;
    }

    cout << "Jumlah pengurangan: ";
    cin >> kurang;

    if (kurang <= 0 || kurang > stokProduk[pilihan - 1]) {
        cout << "Jumlah tidak valid!\n";
        return;
    }

    stokProduk[pilihan - 1] -= kurang;
    cout << "Stok berhasil dikurangi!\n";
}


void hapusProduk() {
    if (jumlahProduk == 0) {
        cout << "Tidak ada produk!\n";
        return;
    }

    lihatProduk();
    int pilihan;
    cout << "Pilih nomor produk yang akan dihapus: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahProduk) {
        cout << "Produk tidak valid!\n";
        return;
    }

    for (int i = pilihan - 1; i < jumlahProduk - 1; i++) {
        namaProduk[i] = namaProduk[i + 1];
        stokProduk[i] = stokProduk[i + 1];
        hargaProduk[i] = hargaProduk[i + 1];
    }
    jumlahProduk--;
    cout << "Produk berhasil dihapus!\n";
}

void ubahHarga() {
    if (jumlahProduk == 0) {
        cout << "Tidak ada produk!\n";
        return;
    }

    lihatProduk();
    int pilihan;
    cout << "Pilih nomor produk: ";
    cin >> pilihan;

    if (pilihan < 1 || pilihan > jumlahProduk) {
        cout << "Produk tidak valid!\n";
        return;
    }

    cout << "Masukkan harga baru: Rp ";
    cin >> hargaProduk[pilihan - 1];
    cout << "Harga berhasil diubah!\n";
}

void transaksi() {
    if (jumlahProduk <= 0) {
        cout << "Tidak ada produk tersedia!\n";
        return;
    }

    
    if (jumlahToko == 0) {
        cout << "Tidak ada toko terdaftar!\n";
        return;
    }

    cout << "\n=== TRANSAKSI BARU ===\n";
    lihatToko(); 

    int pilihToko;
    cout << "\nPilih toko untuk transaksi: ";
    cin >> pilihToko;

    if (pilihToko < 1 || pilihToko > jumlahToko) {
        cout << "Toko tidak valid!\n";
        return;
    }

    cout << "\nAnda memilih toko: " << namaToko[pilihToko - 1] << endl;

    lihatProduk();

    double totalBelanja = 0;
    string produkDibeli = "";
    int totalItem = 0;
    char lanjut;

    do {
        int pilihan, jumlah;
        cout << "\nPilih nomor produk: ";
        cin >> pilihan;

        if (pilihan < 1 || pilihan > jumlahProduk) {
            cout << "Produk tidak valid!\n";
            continue;
        }

        cout << "Jumlah dibeli: ";
        cin >> jumlah;

        if (jumlah <= 0 || jumlah > stokProduk[pilihan - 1]) {
            cout << "Jumlah tidak valid atau stok tidak cukup!\n";
            continue;
        }

        double subtotal = hargaProduk[pilihan - 1] * jumlah;
        totalBelanja += subtotal;
        stokProduk[pilihan - 1] -= jumlah;
        totalItem += jumlah;

        produkDibeli += namaProduk[pilihan - 1] + "(" + to_string(jumlah) + ") ";

        cout << "Subtotal: Rp " << subtotal << endl;

        cout << "Tambah produk lain? (y/n): ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');

    cout << "\n=== RINGKASAN TRANSAKSI ===\n";
    cout << "Total Item: " << totalItem << endl;
    cout << "Total Belanja: Rp " << totalBelanja << endl;

    double bayar;
    do {
        cout << "Jumlah Pembayaran: Rp ";
        cin >> bayar;
        if (bayar < totalBelanja) {
            cout << "Pembayaran kurang!\n";
        }
    } while (bayar < totalBelanja);

    cout << "Kembalian: Rp " << (bayar - totalBelanja) << endl;

    penjualanProduk[jumlahPenjualan] = produkDibeli;
    penjualanJumlah[jumlahPenjualan] = totalItem;
    penjualanTotal[jumlahPenjualan] = totalBelanja;
    penjualanToko[jumlahPenjualan] = namaToko[pilihToko - 1]; 
    jumlahPenjualan++;

    cout << "Transaksi Selesai!\n";
}

void laporanPenjualan() {
    if (jumlahPenjualan == 0) {
        cout << "\nBelum ada penjualan tercatat.\n";
        return;
    }

    cout << "\n=== LAPORAN PENJUALAN ===\n";
    cout << "No | Toko | Produk | Jumlah | Total\n";
    cout << "------------------------------------\n";

    double totalPendapatan = 0;
    int totalTerjual = 0;

    for (int i = 0; i < jumlahPenjualan; i++) {
        cout << (i + 1) << ". " << penjualanToko[i] << " | "
            << penjualanProduk[i] << " | "
            << penjualanJumlah[i] << " | Rp "
            << penjualanTotal[i] << endl;

        totalPendapatan += penjualanTotal[i];
        totalTerjual += penjualanJumlah[i];
    }

    cout << "------------------------------------\n";
    cout << "Total Produk Terjual: " << totalTerjual << endl;
    cout << "Total Pendapatan: Rp " << totalPendapatan << endl;
}



void laporanStok() {
    if (jumlahProduk == 0) {
        cout << "\nTidak ada produk tersedia.\n";
        return;
    }

    cout << "\n=== LAPORAN STOK ===\n";
    cout << "No | Produk | Stok | Harga | Nilai Stok\n";
    cout << "--------------------------------\n";

    double totalNilaiStok = 0.0;
    int totalStok = 0;

    for (int i = 0; i < jumlahProduk; i++) {

        if (stokProduk[i] < 0 || hargaProduk[i] < 0) {
            cout << "Error: Stok atau harga produk tidak valid untuk produk ke-" << (i + 1) << endl;
            continue;
        }

        double nilaiStok = static_cast<double>(stokProduk[i]) * hargaProduk[i];
        cout << (i + 1) << ". " << namaProduk[i] << " | "
            << stokProduk[i] << " | Rp "
            << hargaProduk[i] << " | Rp "
            << nilaiStok << endl;

        totalNilaiStok += nilaiStok;
        totalStok += stokProduk[i];
    }

    cout << "--------------------------------\n";
    cout << "Total Stok: " << totalStok << endl;
    cout << "Total Nilai Stok: Rp " << totalNilaiStok << endl;
}


int main() {
    int pilihan;

    do {
        cout << "\n=== SISTEM INVENTORI DAN PENJUALAN ===\n";
        cout << "> Pengaturan Produk dan Stok\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Lihat Produk\n";
        cout << "3. Hapus Produk\n";
        cout << "4. Tambah Stok\n";
        cout << "5. Kurangi Stok\n";
        cout << "6. Laporan Stok\n";
        cout << "7. Ubah Harga\n";
        cout << "> Pengaturan Toko Pelanggan\n";
        cout << "8. Tambah Toko\n";
        cout << "9. Lihat Toko\n";
        cout << "> Transaksi dan Laporan transaksi\n";
        cout << "10. Transaksi\n";
        cout << "11. Laporan Penjualan\n";
        cout << "---------------------------------\n";
        cout << "12. Keluar\n";
        cout << "\n";
        cout << "> Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: tambahProduk(); break;
        case 2: lihatProduk(); break;
        case 3: hapusProduk(); break;
        case 4: tambahStok(); break;
        case 5: kurangiStok(); break;
        case 6: laporanStok(); break;
        case 7: ubahHarga(); break;
        case 8: tambahToko(); break;
        case 9: lihatToko(); break;
        case 10: transaksi(); break;
        case 11: laporanPenjualan(); break;
        case 12: cout << "\nTerima kasih telah menggunakan sistem ini!\n"; break;
        default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 12);

    return 0;
}
