#include<iostream>

using namespace std;

int ruong[4];
int diem[4] = {2, 10, 20, 50};

int main()
{
    cout << "Nhap so luong ruong xanh: ";
    cin >> ruong[0];
    cout << "Nhap so luong ruong tim: ";
    cin >> ruong[1];
    cout << "Nhap so luong ruong vang: ";
    cin >> ruong[2];
    cout << "Nhap so luong ruong do: ";
    cin >> ruong[3];

    int res = 0;
    for(int i = 0; i < 4; i++)
    {
        res += (ruong[i] * diem[i]);
    }

    cout << "Diem ruong cua ban la: " << res << endl;
    cout << "Diem moc cua ban la; " << double(res * 2.62) << endl;
}