#include <iostream>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


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
	int n;				// jumlah titik
	int i, j, k;		// variabel untuk loop
	int lm; 			// index leftmost
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
	cout << "Daftar Poin : " << endl;
	for (i = 0; i < n; i++){
		p[i].x = rand() % 200;
		p[i].y = rand() % 200;
		arr.push_back(p[i]);
		CetakPoint(arr[i]);
		cout << endl;
	}


	// Memulai algoritma convex hull
	// Menentukan titik terkiri
	lm = 0;
	for (i = 0; i < n; i++){
		if(arr[i].x < arr[lm].x){
			lm = i;
		}
	}

	// Menentukan titik berikutnya yg termasuk himpunan 
	// titik penbentuk convex hull

	current = lm;
	prev = 999;
	hull.push_back(arr[current]);
	Stop1 = false;
	cout << "ini paling kiri" << endl;
	CetakPoint(arr[current]); cout << endl;
	cout << "yuk bisa yuk" << endl;
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

				// cout << "ini current" << current << endl;
				// cout << "ini i" << i << endl;
				// cout << "ini j" << j << endl;
				// cout << "ini result " << result << endl;
				if (i != current and i != prev and i != j and current != j){
					result = IsCH(arr[current], arr[i], arr[j]);
					if (result == 100){
						Stop3 = true; // Gnti i
					}
					else if (result != 100){
						count++;
						total += result;
					
						// if (j == n-3){
						// 	cout << "ini total ";
						// 	cout << total << endl;
						// }
						
						if (count == n-2 and ((total/count == 1) or (total/count == 2))){
							if (i != lm) {
								hull.push_back(arr[i]);
								prev = current;
								current = i;
								Stop2 = true;
								CetakPoint(arr[i]); cout << i << endl;
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
	} while (!(Stop1)); //sudah sekali putaran
	
	// for (int i = 0; i < hull.size(); i++) 
	// 	cout << "(" << hull[i].x << ", "
	// 		<< hull[i].y << ")\n"; 
	
	return 0;
}