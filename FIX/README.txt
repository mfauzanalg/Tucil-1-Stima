Program Menyelesaikan Convex Hull
Muhammad Fauzan Al-Ghifari
13518112
============================================================================

Program convex hull ini menggunakan 
- Bahasa pemrograman C++
- Visualisasi data menggunakan matplotlib for C++ 
- Library chrono untuk menghitung waktu algoritma

sehingga hanya bisa dijalankan pada
- OS Linux yang terinstal :
- compiler g++
- python 3.7
- python-dev
- matplotlib
- numpy

untuk mengcomplie program pada terminal gunakan perintah
g++ -o Tucil1 Tucil1.cpp -std=c++11 -I/usr/include/python3.7 -lpython3.7m

============================================================================

File Tucil1.cpp tidak akan berjalan di windows karena
matplotlib C++ dan library chrono hanya run di linux sehingga 
saya menyediakanopsi untuk menjalankan program di windows
- Tanpa visualisasi data
- tanpa perhitungan waktu (ouput akan 0 ms)

untuk mengcomplie program pada terminal gunakan perintah
g++ -o TanpaVisualisasi TanpaVisualisasi.cpp

=============================================================================