//chained hash table
//2017-03-09 18:45:40
#include<iostream>
#include<vector>
#include<string>
#define HASHNUM 19
#define HASH(x) x%HASHNUM

using namespace std;

class Student {
	friend ostream &operator<<(ostream &os, const Student stu);
public:
	string name;
	int number;
	Student(string s_name, int s_number) :name(s_name), number(s_number) {};
};

Student NOT_FIND(" ", INT_MAX);

class Hash {
	friend ostream &operator<<(ostream &os, const Hash h);
private:
	vector<vector<Student> > hash_table;
public:
	Hash(vector<Student> stus) {
		hash_table.resize(HASHNUM);
		for (auto s : stus) {
			insert(s);
		}
	}

	void insert(Student s) {
		hash_table[HASH(s.number)].push_back(s);
	}

	Student find(int s_num) {
		for (auto s : hash_table[HASH(s_num)]) {
			if (s.number == s_num) {
				return s;
			}
		}
		return NOT_FIND;
	}

	void erase(int s_num) {
		for (auto it = hash_table[HASH(s_num)].begin(); it != hash_table[HASH(s_num)].end(); it++) {
			if ((*it).number == s_num) {
				hash_table[HASH(s_num)].erase(it);
				break;
			}
		}
	}
};

ostream &operator<<(ostream &os, const Student stu) {
	os << stu.name << ' ' << stu.number;
	return os;
}

ostream &operator<<(ostream &os, const Hash h) {
	int loop_tag = 0;
	for (auto row : h.hash_table) {
		os << loop_tag << ": ";
		for (auto s : row) {
			os << s << "    ";
		}
		os << endl;
		loop_tag++;
	}
	return os;
}

int main() {
	vector<Student> test_stus;
	test_stus.push_back(*(new Student("Bob", 14)));
	test_stus.push_back(*(new Student("Panny", 84)));
	test_stus.push_back(*(new Student("Lina", 91)));
	test_stus.push_back(*(new Student("Lion", 3)));
	test_stus.push_back(*(new Student("Coco", 6)));
	test_stus.push_back(*(new Student("Hebe", 15)));
	test_stus.push_back(*(new Student("Ang", 32)));
	test_stus.push_back(*(new Student("Lee", 11)));
	test_stus.push_back(*(new Student("Neo", 65)));
	test_stus.push_back(*(new Student("Scott", 43)));

	Hash test_hash(test_stus);
	cout << "Creat hash table:" << endl;
	cout << test_hash << endl;

	cout << "Insert (Alice, 40):" << endl;
	test_hash.insert(*(new Student("Alice", 40)));
	cout << test_hash << endl;

	cout << "Search (Lee, 11):" << endl;
	cout << test_hash.find(11) << endl << endl;

	cout << "Delete (Scott, 43):" << endl;
	test_hash.erase(43);
	cout << test_hash << endl;

	return 0;
}