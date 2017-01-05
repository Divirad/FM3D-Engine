#include <iostream>
#include <tuple>
#include <functional>

using namespace std;

class Func {
public:
	void func(int x) {
		cout << 0 << endl;
	}

	void func(float x) {
		cout << 1 << endl;
	}

	void func(int x, float y) {
		cout << 2 << endl;
	}

	void func(int x, float y, int z) {
		cout << 3 << endl;
	}

	void xxx();

	void xxx(int);
};

template<class... Args>
class Test {
private:
	std::tuple<Args...> m_args;
	function<void(Func*)> m_func;
public:
	void DoTest(Func* f) {
		m_func(f);
	}

	Test(Args... a) {
		m_args = std::make_tuple(a...);
		m_func = [=](Func* f) { f->func(a...); };
	}
};

int main() {
	auto test = Test<int, float>(5, 2.0f);
	Func* f = new Func();
	test.DoTest(f);
	delete f;
	system("PAUSE");
}