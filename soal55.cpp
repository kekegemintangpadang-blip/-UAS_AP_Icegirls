#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

string acakHuruf(string kata) {
    string hasil = kata;

    for (int i = 1; i < hasil.length() - 1; i++) {
       
        int random = rand() % 2;

        if (random == 0) {
            hasil[i] = '_';
        }
    }

    return hasil;
}

int main() {
    srand(time(0));

    string daftarNegara[40] = {
    {"Indonesia"},
    {"Malaysia"},
    {"Singapura"},
    {"Thailand"},
    {"Vietnam"},
    {"Laos"},
    {"Kamboja"},
    {"Filipina"},
    {"Brunei"},
    {"Myanmar"},
    {"Jepang"},
    {"China"},
    {"Korea"},
    {"India"},
    {"Pakistan"},
    {"Oman"},
    {"Qatar"},
    {"Yaman"},
    {"Irak"},
    {"Iran"},
    {"Prancis"},
    {"Italia"},
    {"Jerman"},
    {"Belanda"},
    {"Norway"},
    {"Swedia"},
    {"Finlandia"},
    {"Spanyol"},
    {"Portugal"},
    {"Inggris"},
    {"Amerika"},
    {"Kanada"},
    {"Meksiko"},
    {"Argentina"},
    {"Brazil"},
    {"Chile"},
    {"Mesir"},
    {"Maroko"},
    {"Afrika"},
    {"Australia"}
    };

    int skor = 0;
    char lagi = 'Y';

    while (lagi == 'Y' || lagi == 'y') {

        int index = rand() % 40;

         string jawabanBenar = daftarNegara[index];
         string petunjuk = acakHuruf(jawabanBenar);

         cout << "Tebak Negara: " << petunjuk << endl;
         string jawabanUser;

         cout << "Masukkan jawaban: ";
         cin >> jawabanUser;

        if (jawabanUser == jawabanBenar) {
            cout << "Selamat Anda Benar!!!!!.\n";
            skor++;
        } else {
            cout << "Salah!\n";
            cout << "Jawaban yang benar adalah : "
                 << jawabanBenar << endl;
        }

            cout << "Skor Anda: " << skor << endl;

        cout << "\nMau main lagi? (Y/N): ";
        cin >> lagi;
    }

    cout << "\nGame Selesai \n";  

   
}