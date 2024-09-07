#include <stdio.h>
#include <math.h>
#include <iostream>
#include "subproblem_3.h"

// Subproblem 3 Buku TIK Kelas 10
// Menggunakan rumus parabolic trajectory untuk mencari tinggi maximum burung boro
int main(){
    int jumlah_burung, burung_counter = {0}; //berapa burung yang bakal dikalkulasikan + counter untuk burung keberapa yang sedang dikalkulasikan
    double tinggi_pohon, gravitasi = {}; //variable yang dipakai antara semua percobaan burung

    std::cout << "Simulasi ketinggian maximum burung boro.";
    std::cout << ("Masukan Jumlah burung:");
    std::cin >> jumlah_burung;
    std::cout << ("Masukan Tinggi pohon:");
    std::cin >> tinggi_pohon;
    std::cout << ("Masukan gravitasi bumi:"); //bisa pake constants, tapi biarkan user mau gravitasi seberapa (10m/s, 9.8m/s, 20 terserah)
    std::cin >> gravitasi;

    double velositas, sudut = {}; //variable yang dipakai untuk setiap burung
    kalkulasi_burung_boro(velositas, sudut, gravitasi, tinggi_pohon, jumlah_burung, burung_counter);
}

void kalkulasi_burung_boro(double &velositas, double &sudut, double gravitasi, double tinggi_pohon, int jumlah_burung, int burung_counter)
{
    burung_counter++; //mulaikan counter
    std::cout << "Masukan velositas burung ke-" << burung_counter << ":";
    std::cin >> velositas;
    std::cout << "Masukan sudut burung ke-" << burung_counter <<  ":";
    std::cin >> sudut;
    double radian = sudut * (22 / 7) / 180.;

    double tinggi_max = ((pow(velositas, 2) * pow(sin(radian), 2))) / (gravitasi * 2); // apakah rumus ini benar? yntkts. blm ajarin jg! yang penting logikanya bener

    int bool_status;
    if (tinggi_max >= tinggi_pohon)
    {
        bool_status = 1; // melebihi tinggi pohon
    }
    else
    {
        bool_status = 0; // tidak melebihi tinggi pohon
    }

    std::cout << "Status Burung: " << burung_counter << " : " << bool_status << "\n";
    std::cout << "Ketinggian: " << tinggi_max << " meter \n";
    
    if(burung_counter < jumlah_burung) //Apakah semua burung telah terkalkulasi? jika iya, hentikan operasi. jika tidak, rekursi.
    {
        kalkulasi_burung_boro(velositas, sudut, gravitasi, tinggi_pohon, jumlah_burung, burung_counter);
    }
    else
    {
        return;
    }
}