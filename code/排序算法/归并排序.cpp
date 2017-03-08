//merge sort
//2017-03-08 19:41:11
#include<iostream>
#include<vector>

using namespace std;

class Sort {
private:
	static vector<int> merge(vector<int> nums, int begin, int end) {
		int mid = (end + begin) / 2;
		vector<int> dnums1, dnums2, sorted_nums;
		
		if (begin < end) {
			dnums1 = merge(nums, begin, mid);
			dnums2 = merge(nums, mid + 1, end);
			dnums1.push_back(INT_MAX);
			dnums2.push_back(INT_MAX);
		}

		if (begin == end) {
			sorted_nums.push_back(nums[begin]);
		}
		else {
			for (int i1 = 0, i2 = 0, loop_tag = 0; loop_tag < end - begin + 1; loop_tag++) {
				if (dnums1[i1] < dnums2[i2]) {
					sorted_nums.push_back(dnums1[i1]);
					i1++;
				}
				else {
					sorted_nums.push_back(dnums2[i2]);
					i2++;
				}
			}
		}

		return sorted_nums;
	}

public:
	static vector<int> merge_sort(vector<int> nums) {
		return merge(nums, 0, nums.size()-1);
	}
};

int main() {
	vector<int> test_nums = { 5,5,7,5,13,46,54,68,5,32,12,32,45,45,64,4,2,3,13,11,1,31,6,7,9,10,46,4,3,1,1,23,5,8,5 };

	vector<int> result_nums = Sort::merge_sort(test_nums);
	for (auto n : result_nums) {
		cout << n << ' ';
	}
	cout << endl;

	return 0;
}