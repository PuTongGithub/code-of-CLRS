//LCS
//2017-03-12 19:57:49
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class LCS {
private:
	vector<vector<int> > cstr_length;
	vector<vector<int> > build_LCS;		//0 for xi==yj , 1 for c[i-1,j]>=c[i,j-1] , -1 for else
	string string_x;
	string string_y;

	void print_LCS(int x_index, int y_index) {
		if (x_index == 0 || y_index == 0) {
			return;
		}
		if (build_LCS[x_index][y_index] == 0) {
			print_LCS(x_index - 1, y_index - 1);
			cout << string_x[x_index - 1];
		}
		else if (build_LCS[x_index][y_index] == 1) {
			print_LCS(x_index - 1, y_index);
		}
		else {
			print_LCS(x_index, y_index - 1);
		}
	}

public:
	LCS(string str_x, string str_y): string_x(str_x), string_y(str_y){
		cstr_length.resize(str_x.length() + 1, vector<int>(str_y.length() + 1, 0));
		build_LCS.resize(str_x.length() + 1, vector<int>(str_y.length() + 1, 0));

		for (int x_index = 1; x_index <= str_x.length(); x_index++) {
			for (int y_index = 1; y_index <= str_y.length(); y_index++) {
				if (str_x[x_index - 1] == str_y[y_index - 1]) {
					cstr_length[x_index][y_index] = cstr_length[x_index - 1][y_index - 1] + 1;
					build_LCS[x_index][y_index] = 0;
				}
				else if (cstr_length[x_index - 1][y_index] >= cstr_length[x_index][y_index - 1]) {
					cstr_length[x_index][y_index] = cstr_length[x_index - 1][y_index];
					build_LCS[x_index][y_index] = 1;
				}
				else {
					cstr_length[x_index][y_index] = cstr_length[x_index][y_index - 1];
					build_LCS[x_index][y_index] = -1;
				}
			}
		}
	}

	void show_LCS() {
		print_LCS(string_x.length(), string_y.length());
	}
};

int main() {
	string test_x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
	string test_y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";

	//string test_x = "ACADE";
	//string test_y = "CDAEA";

	LCS test_LCS(test_x, test_y);
	test_LCS.show_LCS();
	cout << endl;
}