//activity selector
//2017-03-13 18:23:46
/*
Number	0	1	2	3	4	5	6	7	8	9	10
Start	1	3	0	5	3	5	6	8	8	2	12
End		4	5	6	7	9	9	10	11	12	14	16
*/
#include<iostream>
#include<vector>

using namespace std;

struct Activity {
	int begin;
	int end;
	Activity(int begin_time, int end_time) :begin(begin_time), end(end_time) {};
};

class ASP {
private:
	vector<Activity> act_table;
	vector<int> the_best_act_chooses;

public:
	ASP(vector<Activity> acts) {
		act_table = acts;

		the_best_act_chooses.push_back(0);
		int end_time = acts[0].end;
		for (int index = 1; index < acts.size(); index++) {
			if (acts[index].begin >= end_time) {
				the_best_act_chooses.push_back(index);
				end_time = acts[index].end;
			}
		}
	}

	void show_chooses() {
		for (auto act : the_best_act_chooses) {
			cout << act << ' ';
		}
	}
};

int main() {
	vector<Activity> test_acts;
	test_acts.push_back(Activity(1, 4));
	test_acts.push_back(Activity(3, 5));
	test_acts.push_back(Activity(0, 6));
	test_acts.push_back(Activity(5, 7));
	test_acts.push_back(Activity(3, 9));
	test_acts.push_back(Activity(5, 9));
	test_acts.push_back(Activity(6, 10));
	test_acts.push_back(Activity(8, 11));
	test_acts.push_back(Activity(8, 12));
	test_acts.push_back(Activity(2, 14));
	test_acts.push_back(Activity(12, 16));

	ASP test_ASP(test_acts);
	test_ASP.show_chooses();
	cout << endl;

	return 0;
}