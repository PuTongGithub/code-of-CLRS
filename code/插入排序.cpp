#include<iostream>
#include<vector>

using namespace std;

class Sort {
public:
	static vector<int> insertion_sort(vector<int> nums) {
		vector<int> sorted_nums;

		for (auto number : nums) {
			if (sorted_nums.empty()) {
				sorted_nums.push_back(number);
				continue;
			}

			bool is_num_inserted = false;
			for (auto it = sorted_nums.begin(); it != sorted_nums.end(); it++) {
				if (number <= (*it)) {
					sorted_nums.insert(it, number);
					is_num_inserted = true;
					break;
				}
			}
			if (!is_num_inserted) {
				sorted_nums.push_back(number);
			}

			for (auto n : sorted_nums) {		//逐步显示插入过程
				cout << n << ' ';
			}
			cout << endl;
		}

		return sorted_nums;
	}
};

int main() {
	vector<int> test_nums = { 5,5,7,5,13,46,54,68,5,32,12,32,45,45,64,4,2,3,13,11,1,31,6,7,9,10,46,4,3,1,1,23,5,8,5 };

	vector<int> result_nums = Sort::insertion_sort(test_nums);
	for (auto n : result_nums) {
		cout << n << ' ';
	}
	cout << endl;

	return 0;
}