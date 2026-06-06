#include <iostream> 
#include <cstdlib>
#include <ctime> 
using namespace std;

class Minesweeper {
private:
    char papan[10][10];      
    bool bom[10][10];       
    bool buka[10][10];    
    bool tanda[10][10];

    int ukuran;
    int jumlahBom;
    time_t waktuMulai;

public:
    void setup() {
        do {
            cout << "Ukuran papan (4 - 10) : ";
            cin >> ukuran;

            if (ukuran < 4 || ukuran > 10) {
                cout << "Ukuran harus antara 4 sampai 10.\n";
            }

        } while (ukuran < 4 || ukuran > 10);

        int maksimalBom = (ukuran * ukuran) - 1;
        do {
            cout << "Jumlah bom : ";
            cin >> jumlahBom;

            if (jumlahBom < 1 || jumlahBom > maksimalBom) {
                cout << "Jumlah bom tidak valid.\n";
            }

        } while (jumlahBom < 1 || jumlahBom > maksimalBom);

        for (int i = 0; i < ukuran; i++) {
            for (int j = 0; j < ukuran; j++) {
                papan[i][j] = '-';
                bom[i][j] = false;
                buka[i][j] = false;
                tanda[i][j] = false;
            }
        }

        srand(time(0));
        int totalBom = 0;
        while (totalBom < jumlahBom) {
            int x = rand() % ukuran;
            int y = rand() % ukuran;

            if (!bom[x][y]) {
                bom[x][y] = true;
                totalBom++;
            }
        }
        waktuMulai = time(0);
    }
    int hitungBomSekitar(int x, int y) {
        int jumlah = 0;

        for (int i = -1; i <= 1; i++) { 
            for (int j = -1; j <= 1; j++) {
//akan memeriksa koordinat di sekeliling kotak pusat
                int nx = x + i;
                int ny = y + j;

                if (nx >= 0 &&
                    ny >= 0 &&
                    nx < ukuran &&
                    ny < ukuran &&
                    bom[nx][ny]) {
//fungsinya memastikan program tidak mengecek koordinat di luar batas array
                    jumlah++;
                }
            }
        }
        return jumlah;
    }
    void floodFill(int x, int y) {

        if (x < 0 || y < 0 ||
            x >= ukuran || y >= ukuran) {
            return;
        }

        if (buka[x][y] || tanda[x][y]) {
            return;
        }

        buka[x][y] = true;
        int jumlah = hitungBomSekitar(x, y);
        papan[x][y] = jumlah + '0';
        if (jumlah != 0) {
            return;
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                floodFill(x + i, y + j);
            }
        }
    }
    bool cekMenang() {
        int benar = 0;
        int totalTanda = 0;

        for (int i = 0; i < ukuran; i++) {
            for (int j = 0; j < ukuran; j++) {
                if (tanda[i][j]) {
                    totalTanda++;
                }
                if (tanda[i][j] && bom[i][j]) {
                    benar++;
                }
            }
        }
        return (benar == jumlahBom &&
                totalTanda == jumlahBom);
    }
    int bomTersisa() {
        int jumlahTanda = 0;

        for (int i = 0; i < ukuran; i++) {
            for (int j = 0; j < ukuran; j++) {
                if (tanda[i][j]) {
                    jumlahTanda++;
                }
            }
        }
        return jumlahBom - jumlahTanda;
    }
    void tampilPapan() {
        cout << "\nBom belum ditandai : "
             << bomTersisa();
        cout << "\nWaktu berjalan : "
             << (int)(time(0) - waktuMulai)
             << " detik\n\n";
        cout << "   ";

        for (int i = 1; i <= ukuran; i++) {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < ukuran; i++) {
            cout << i + 1 << "  ";

            for (int j = 0; j < ukuran; j++) {
                cout << papan[i][j] << " ";
            }
            cout << endl;
        }
    }
    void tampilBom() {
        for (int i = 0; i < ukuran; i++) {
            for (int j = 0; j < ukuran; j++) {
                if (bom[i][j]) {
                    papan[i][j] = '*';
                }
            }
        }
    }
    void mainGame() {
        bool gameOver = false;
        while (!gameOver) {
            tampilPapan();

            char aksi;
            cout << "\n(B)uka atau (T)andai : ";
            cin >> aksi;

            int x, y;
            cout << "Baris : ";
            cin >> x;

            cout << "Kolom : ";
            cin >> y;

            x--;
            y--;

            if (x < 0 || y < 0 ||
                x >= ukuran || y >= ukuran) {

                cout << "Koordinat tidak valid.\n";
                continue;
            }
            if (aksi == 'T' || aksi == 't') {
                tanda[x][y] = !tanda[x][y];

                if (tanda[x][y]) {
                    papan[x][y] = 'F';
                }
                else {
                    papan[x][y] = '-';
                }
            }
            else if (aksi == 'B' || aksi == 'b') {
                if (tanda[x][y]) {
                    cout << "Kotak masih ditandai.\n";
                    continue;
                }

                if (bom[x][y]) {
                    tampilBom();
                    tampilPapan();

                    cout << "\nBOOM! Kamu kalah.\n";
                    cout << "Waktu bermain : "
                         << (int)(time(0) - waktuMulai)
                         << " detik\n";

                    gameOver = true;
                }
                else {
                    int jumlah = hitungBomSekitar(x, y);

                    if (jumlah == 0) {
                        floodFill(x, y);
                    } else {
                        buka[x][y] = true;
                        papan[x][y] = jumlah + '0';
                    }
                }
            }
            if (!gameOver && cekMenang()) {
                tampilPapan();

                cout << "\nSELAMAT! Kamu menang.\n";
                cout << "Waktu bermain : "
                     << (int)(time(0) - waktuMulai)
                     << " detik\n";
                gameOver = true;
            }
        }
    }
};

int main() {
    system("cls");

    int pilihan;
    do {
        cout << "\n===== MINESWEEPER++ =====\n";
        cout << "1. Mulai Permainan Baru\n";
        cout << "2. Keluar\n";
        cout << "Pilih : ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            Minesweeper game;
            game.setup();
            game.mainGame();
            break;
        }

        case 2:
            cout << "Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 2);
    return 0;
}