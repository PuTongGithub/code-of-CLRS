//matrix chain
//2017-03-12 13:21:47
#include<iostream>
#include<vector>

using namespace std;

struct Matrix {
	//vector<vector<int> > mat;
	int rows;
	int columns;
	Matrix(int r, int c) :rows(r), columns(c) {};
};
Matrix ERROR_MAT(-1, -1);

class SolveMatrixChain {
private:
	vector<vector<int> > mul_num;
	vector<vector<int> > break_pos;
	int chain_size;

	void show_chain(int head, int tail) {
		if (head == tail) {
			cout << 'A';
		}
		else {
			cout << '(';
			show_chain(head, break_pos[head][tail]);
			show_chain(break_pos[head][tail] + 1, tail);
			cout << ')';
		}
	}
public:
	SolveMatrixChain(vector<Matrix> mats) {
		chain_size = mats.size();
		vector<int> ini_nums(chain_size, 0);
		for (int loop_tag = 0; loop_tag < chain_size; loop_tag++) {
			mul_num.push_back(ini_nums);
			break_pos.push_back(ini_nums);
		}

		for (int len = 2; len <= mats.size(); len++) {
			for (int index = 0; index <= mats.size() - len; index++) {
				int m_index = index + len - 1;
				mul_num[index][m_index] = INT_MAX;
				for (int b_pos = index; b_pos < m_index; b_pos++) {
					int times = mul_num[index][b_pos] + mul_num[b_pos + 1][m_index] + mats[index].rows*mats[b_pos].columns*mats[m_index].columns;
					if (times < mul_num[index][m_index]) {
						mul_num[index][m_index] = times;
						break_pos[index][m_index] = b_pos;
					}
				}
			}
		}
	}

	void show_solution() {
		cout << "Need multiply times:" << mul_num[0][chain_size - 1] << endl;
		show_chain(0, chain_size - 1);
	}
};

int main() {
	vector<Matrix> test_mats;
	test_mats.push_back(*(new Matrix(10, 100)));
	test_mats.push_back(*(new Matrix(100, 5)));
	test_mats.push_back(*(new Matrix(5, 50)));
	test_mats.push_back(*(new Matrix(50, 100)));
	test_mats.push_back(*(new Matrix(100, 5)));
	test_mats.push_back(*(new Matrix(5, 50)));

	SolveMatrixChain solution(test_mats);
	solution.show_solution();
	cout << endl;
}