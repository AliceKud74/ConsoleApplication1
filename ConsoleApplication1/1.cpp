
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	string input;
	string output;
	int M;
	int N;
	cout << "¬ведите строку: ";
	getline(cin, input);
	input.insert(0, " ");
	printf_s("¬ведите M и N ");
	scanf_s("%i%i", &M,&N);
	int b = 0;
	int c = 1;
	while(b<input.length()) {
		if ((input[b] == ' ') && (input[b+1]!=' ')) {
			int a = input.find(' ', b + 1);
			if ((c < M) || (c > N)) {
				output.append(input.substr(b+1,a-b));
				//cout << input.substr(b, i - b);
			}
			b = a;
			c++;
		}
		else {
			b++;
		}
		
	}

	cout << output<< "\n";
	int n = 5;
	const int N1 = 10;
	int id[N1];
	srand(time(0));
	int i;
	int a = 0, x = 500000000;
	for (i = 0; i < N1; i++) {
		id[i] = a + rand() % (x - a + 1);
	}

	for (auto i : id) {
		cout << i<<" ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++) {
		id[i] = (id[i] << n);
	}
	for (auto i : id) {
		cout << i <<" ";
	}
	cout <<"\n"
	int s;
	printf_s("¬ведите номер id, который необходимо декодировать");
	scanf_s("%i", &s);
	cout << (id[s - 1] >> n);
	
	return 0;
}

	



   

