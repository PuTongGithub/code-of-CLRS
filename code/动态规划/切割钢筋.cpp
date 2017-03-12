//cut rod
//2017-03-12 10:04:02
/*
rod_length	1	2	3	4	5	6	7	8	9	10
rod_price	1	5	8	9	10	17	17	20	24	30
Find the best way to cut rod which make the highest price.
*/
#include<iostream>
#include<vector>

using namespace std;

vector<int> rod_price = { 0,1,5,8,9,10,17,17,20,24,30 };

class B2UCutRod {
private:
	vector<int> best_price = rod_price;
	vector<int> first_cut;

	void show_cut(int length) {
		if (first_cut.size() + 1 < length) {
			return;
		}
		while (length > 0) {
			cout << first_cut[length] << ' ';
			length = length - first_cut[length];
		}
	}
public:
	int find_best(int length) {
		if (length > 11) {
			best_price.resize(length + 1, 0);
		}
		first_cut.resize(length + 1 , 0);

		for (int len = 1; len <= length; len++) {
			int price = -1;
			for (int c_len = 1; c_len <= len && c_len < rod_price.size(); c_len++) {
				if (price < best_price[c_len] + best_price[len - c_len]) {
					first_cut[len] = c_len;
					price = best_price[c_len] + best_price[len - c_len];
				}
			}
			best_price[len] = price;
		}
		cout << "the best way to cut:";
		show_cut(length);
		cout << endl;
		cout << "price:" << best_price[length] << endl;
		return best_price[length];
	}
};

class U2BCutRod {
private:
	vector<int> best_price = rod_price;
	vector<int> first_cut;

	void show_cut(int length) {
		if (first_cut.size() + 1 < length) {
			return;
		}
		while (length > 0) {
			cout << first_cut[length] << ' ';
			length = length - first_cut[length];
		}
	}

	int the_best(int length) {
		if (best_price[length] > -1) {
			return best_price[length];
		}
		int price = -1;
		for (int len = 1; len <= length && len < rod_price.size(); len++) {
			int new_price = rod_price[len] + the_best(length - len);
			if (price < new_price) {
				first_cut[length] = len;
				price = new_price;
			}
		}
		best_price[length] = price;
		return price;
	}

public:
	int find_best(int length) {
		best_price.resize(length + 1, -1);
		first_cut.resize(length + 1, -1);
		best_price[0] = 0;

		the_best(length);
		cout << "price:" << best_price[length] << endl;

		return best_price[length];
	}
};

int main() {
	vector<int> test_nums = { 3,4,6,10,14,18,27,40 };
	 
	cout << "Buttom to up cut rod:" << endl;
	B2UCutRod b2u_cut;
	for (auto n : test_nums) {
		cout << "length:" << n << endl;
		b2u_cut.find_best(n);
		cout << endl;
	}

	U2BCutRod u2b_cut;
	cout << "Up to buttom cut rod:" << endl;
	for (auto n : test_nums) {
		cout << "length:" << n << endl;
		u2b_cut.find_best(n);
		cout << endl;
	}

	return 0;
}