#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
using namespace std;

void Mult(int** matrix1, int** matrix2, int** result, int n, int start, int num_threads) {
	for (int i = start; i < n; i += num_threads) {
		for (int j = 0; j < n; j++) {
			int k = 0;
			while (k < n) {
				result[i][j] += matrix1[i][k] * matrix2[k][j];
				k++;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	cout << "Введите размер первой матрицы: ";
	int n;
	cin >> n;
	int** matrix1 = new int*[n];
	for (int i = 0; i < n; i++)
	{
		matrix1[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			matrix1[i][j] = rand() % 9;
			cout << matrix1[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Введите размер второй матрицы: ";
	int m;
	cin >> m;
	int** matrix2 = new int*[m];
	for (int i = 0; i < m; i++)
	{
		matrix2[i] = new int[m];
		for (int j = 0; j < m; j++)
		{
			matrix2[i][j] = rand() % 9;
			cout << matrix2[i][j] << " ";
		}
		cout << endl;
	}
	if (n != m) {
		cout << "Эти матрицы нельзя перемножить :(";
		return 0;
	}
	vector<thread> thr;
	int** result = new int* [n];
	for (int i = 0; i < n; i++) {
		result[i] = new int[n];
		for (int j = 0; j < n; j++) {
			result[i][j] = 0;
		}
	}
	cout << "Результат умножения этих матриц: " << endl;
	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
				int k = 0;
				while (k != n) {
					result[i][j] += matrix1[i][k] * matrix2[k][j];
					k++;
				}
		}
	}*/
	for (int i = 0; i < 4; i++) {
		thr.emplace_back(std::thread(Mult, matrix1, matrix2, result, n, i, 4));
	}
	for (int i = 0; i < thr.size(); i++) {
		thr[i].join();
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << result[i][j] << " " << setw(2);
		}
		cout << endl;
	}
}