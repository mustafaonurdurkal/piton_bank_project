# CMakeList.txt: TcpServer için CMake projesi, kaynağı ekleyin ve tanımlayın
# projeye özgü mantık burada bulunur.
#
cmake_minimum_required (VERSION 3.8)

# Kaynağı bu projenin yürütülebilir dosyasına ekleyin.
add_executable (TcpServer "TcpServer.cpp" "TcpServer.h"     "Customer.h" "Bank.h" "Card.h"  "Customer.cpp" "Bank.cpp" "Card.cpp" "ServiceOperations.h" "ServiceOperations.cpp")

# TODO: Gerekirse testleri ve yükleme hedeflerini ekleyin.
