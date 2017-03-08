//bucket sort
//2017-03-08 21:38:05
#include<iostream>
#include<vector>

using namespace std;

class Sort {
public:
	static vector<double> bucket_sort(vector<double> nums) {
		vector<vector<double> > buckets(10);
		for (auto n : nums) {
			int index = (int)n;
			bool is_num_inserted = false;
			for (auto it = buckets[index].begin(); it != buckets[index].end(); it++) {
				if (*it >= n) {
					is_num_inserted = true;
					buckets[index].insert(it, n);
					break;
				}
			}
			if (!is_num_inserted) {
				buckets[index].push_back(n);
			}
		}
		

		vector<double> sorted_nums;
		for (auto b : buckets) {
			for (auto n : b) {
				sorted_nums.push_back(n);
			}
		}
		return sorted_nums;
	}
};

int main() {
	vector<double> text_nums = { 5.21,6.33,1.59,9.45,2.55,1.34,8.24,1.78,9.23,0.11,4.26,8.12,2.78,8.79,2.55,0.34,4.88,5.19 };
	vector<double> result_nums = Sort::bucket_sort(text_nums);
	for (auto n : result_nums) {
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}