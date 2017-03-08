//heap sort
//2017-03-08 19:40:50
#include<iostream>
#include<vector>
#define LEFT(x) 2*x+1
#define RIGHT(x) 2*(x+1)

using namespace std;

class Sort {
private:
	static void max_heapify(vector<int> &nums, int index, int heap_size) {
		int max = index;
		if (LEFT(index) < heap_size && nums[LEFT(index)] > nums[max]) {
			max = LEFT(index);
		}
		if (RIGHT(index) < heap_size && nums[RIGHT(index)] > nums[max]) {
			max = RIGHT(index);
		}
		if (max != index) {
			int temp = nums[index];
			nums[index] = nums[max];
			nums[max] = temp;

			max_heapify(nums, max, heap_size);
		}
	}

	static void build_max_heap(vector<int> &nums) {
		for (int index = nums.size() / 2; index >= 0; index--) {
			max_heapify(nums, index, nums.size());
		}
	}

public:
	static void heap_sort(vector<int> &nums) {
		build_max_heap(nums);
		for (int heap_tail=nums.size()-1; heap_tail > 0; heap_tail--) {
			int temp = nums[0];
			nums[0] = nums[heap_tail];
			nums[heap_tail] = temp;
			max_heapify(nums, 0, heap_tail);
		}
	}
};

int main() {
	vector<int> test_nums = { 5,5,7,5,13,46,54,68,5,32,12,32,45,45,64,4,2,3,13,11,1,31,6,7,9,10,46,4,3,1,1,23,5,8,5 };

	Sort::heap_sort(test_nums);
	for (auto n : test_nums) {
		cout << n << ' ';
	}
	cout << endl;

	return 0;
}