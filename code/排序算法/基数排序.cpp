//radix sort
//2017-03-08 21:18:40
#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Sort {
private:
	static void radix(vector<string> &nums, int pos) {		//Bubble Sort
		for (int loop_tag = 0; loop_tag < nums.size(); loop_tag++) {
			int key_index = 0;
			for (int index = 1; index < nums.size()-loop_tag; index++) {
				if (nums[index][pos] < nums[key_index][pos]) {
					string temp = nums[index];
					nums[index] = nums[key_index];
					nums[key_index] = temp;
				}
				key_index++;
			}
		}
	}

public:
	static void radix_sort(vector<string> &nums, int max_length) {
		for (int index = max_length - 1; index >= 0; index--) {
			radix(nums, index);
		}
	}
};

int main() {
	vector<string> text_nums = { "132","646","826","671","962","375","368","102","968","204","488","575","700" };
	Sort::radix_sort(text_nums, 3);
	for (auto n : text_nums) {
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}