#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm> 
#include <chrono> 

using namespace std;
using namespace std::chrono; 

struct Point{
	// Struktur Poin
	int x;
	int y;
};

void CetakPoint (Point p){
	// Prosedur untuk mencetak point
	cout << "(" << p.x << "," << p.y << ")";
}

int IsCH (Point a, Point b, Point c){
	// Menentukan sebuah titik termasuk penyusun
	// dari convex hull atau bukan
	// Menggunakan persamaan garis yang dibentuk
	// oleh dua buah titik a dan b
	// (y-y1)*(x2-x1)-(x-x1)*(y2-y1)
	float nilai;
	nilai = (c.y-a.y)*(b.x-a.x) - (c.x-a.x)*(b.y-a.y);
	if (nilai == 0){
		return 100;			// ada di garis
	}
	else if (nilai > 0){
		return 1;			// ada di kanan garis
	}
	else{ // nilai < 0
		return 2;			// ada di kiri garis
	}
	
}

int main() {
	int n;							// jumlah titik
	int i, j;						// variabel untuk loop
	int lm; 						// index leftmost
	int current, prev;				
	float result, total, count;
	bool Stop1, Stop2, Stop3;

	//Meminta input banyaknya titik dari user
	cout << "Masukkan banyaknya titik : ";
	cin >> n;
	vector<Point> arr;
	vector<Point> hull;
	Point p[n];

	// Membangun titik secara random
	srand(time(0));
	cout << endl << "Daftar Poin : " << endl;
	for (i = 0; i < n; i++){
		p[i].x = rand() % 10000;
		p[i].y = rand() % 10000;
		arr.push_back(p[i]);
		CetakPoint(arr[i]);
		cout << endl;
	}
	cout << endl;

	auto start = high_resolution_clock::now();	// Mulai menghitung waktu
	// Memulai algoritma convex hull
	// Menentukan titik terkiri sebagai titik pertama
	lm = 0;
	for (i = 0; i < n; i++){
		if(arr[i].x < arr[lm].x){
			lm = i;
		}
	}

	// Menentukan titik berikutnya yg termasuk himpunan 
	// titik penbentuk convex hull
	if (n <= 2){
		hull.push_back(arr[0]);
		hull.push_back(arr[1]);
	}
	else{
		current = lm;
		prev = 999;
		hull.push_back(arr[current]);
		Stop1 = false;
		do{
			i = 0;
			Stop2 = false;
			while (Stop2 == false and i < n){
				j = 0;			
				Stop3 = false;
				result = 0;
				total = 0;
				count = 0;

				while(Stop3 == false and j < n){
					if (i != current and i != prev and i != j and current != j){
						result = IsCH(arr[current], arr[i], arr[j]);
						if (result == 100){
							// Jika terdapat titik yang kolinear Do nothing
						}
						else if (result != 100){
							count++;
							total += result;
							
							if (count == n-2 and ((total/count == 1) or (total/count == 2))){
								if (i != lm) {
									hull.push_back(arr[i]);
									prev = current;
									current = i;
									Stop2 = true;
								}
								else if (i == lm){
									Stop1 = true;
								}
							}
						}
					}
					j++;
				}
				i++;
			}
		} while (!(Stop1)); //sudah sekali putaran dan mencapai titik awal
		hull.push_back(arr[lm]);
	}
	
	auto stop = high_resolution_clock::now(); // Berhenti menghitung waktu

	// Mencetak titik-titik convex hull
	cout << "Titik penyusun convex hull : " <<endl;
	cout << "[";
	for (int i = 0; i < hull.size()-1; i++) {
		CetakPoint(hull[i]);
		cout << ", ";
	}
	CetakPoint(hull[hull.size()-1]);
	cout << "]" << endl;

	auto duration = duration_cast<microseconds>(stop - start).count(); 
	cout << "Waktu yang dibutuhkan untuk membentuk convex hull : " << duration << " microseconds" << endl;
	
	return 0;
}