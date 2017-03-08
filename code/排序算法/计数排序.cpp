//counting sort
//2017-03-08 20:20:24
#include<iostream>
#include<vector>

using namespace std;

class Sort {
public:
	static vector<int> counting_sort(vector<int> nums) {
		int max_num = 0;
		for (auto n : nums) {
			if (n > max_num) max_num = n;
		}

		vector<int> count(max_num + 1);
		for (auto n : nums) {
			count[n]++;
		}

		for (int index = 1; index < count.size(); index++) {
			count[index] += count[index - 1];
		}

		vector<int> sorted_nums(nums.size());
		for (auto n : nums) {
			sorted_nums[count[n]-1] = n;
			count[n]--;
		}

		return sorted_nums;
	}
};

int main() {
	vector<int> test_nums = { 5,5,7,5,3,6,4,8,5,2,1,2,4,4,6,4,2,3,1,1,1,3,6,7,9,0,6,4,3,1,1,9,5,8,5 };

	vector<int> result_nums = Sort::counting_sort(test_nums);
	for (auto n : result_nums) {
		cout << n << ' ';
	}
	cout << endl;

	return 0;
}