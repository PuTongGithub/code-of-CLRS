//quick sort
//2017-03-08 19:50:19
#include<iostream>
#include<vector>

using namespace std;

class Sort {
private:
	static void quick(vector<int> &nums, int head, int tail) {
		if (head >= tail) return;
		//choose the tail's number for key number
		int b_index = head;		//front of the numbers which bigger than key number 

		for (int index = head; index < tail; index++) {
			if (nums[index] < nums[tail]) {
				int temp = nums[index];
				nums[index] = nums[b_index];
				nums[b_index] = temp;

				b_index++;
			}
		}
		int temp = nums[tail];
		nums[tail] = nums[b_index];
		nums[b_index] = temp;

		quick(nums, head, b_index - 1);
		quick(nums, b_index + 1, tail);
	}
public:
	static void quick_sort(vector<int> &nums) {
		quick(nums, 0, nums.size() - 1);
	}
};

int main() {
	vector<int> test_nums = { 5,5,7,5,13,46,54,68,5,32,12,32,45,45,64,4,2,3,13,11,1,31,6,7,9,10,46,4,3,1,1,23,5,8,5 };

	Sort::quick_sort(test_nums);
	for (auto n : test_nums) {
		cout << n << ' ';
	}
	cout << endl;

	return 0;
}