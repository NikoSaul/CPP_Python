#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>
#include <functional>
#include <chrono>
#include <ctime>
#include <numeric>


using namespace std;

template<typename T>
class Gen
{
public:
	Gen(T _step, T first=0) : step(_step), val(first) {}
	Gen(T first, T last, int n) : step((last - first) / n), val(first) { }
	T operator()() { T res = val;  val += step;  return res; }
protected:
	T val;
	T step;
};

class generateur_multiples
{
public :
  explicit generateur_multiples(int mult): m(mult), courant(0){}
  int operator()() {return courant+=m;}
private :
  int m;
  int courant;
};

template<typename T>
class GenRand
{
public:
	GenRand(T _m, T _M = 0) : m(_m), M(_M) {}
	T operator()() { T res = m + (M - m)*(static_cast<float>(std::rand()) / RAND_MAX);  return res; }
protected:
	T m,M;
};




int main()
{
	printf("***** CREATION\n");
	int* tl = new int[3];            // tableau dynamique alloué sur le tas (il faut le libérer)
	tl[0] = 1;
	delete[] tl;

	std::vector<int> ts = { 1,2,3 };          // vector STL alloué de manière cachée dans le tas, le vector gère son allocation et destruction
	std::copy(ts.begin(), ts.end(), std::ostream_iterator<int>(std::cout, " "));
	cout << endl;

	std::vector<int> a;
	std::generate_n(std::inserter(a, a.begin()), 25, Gen<int>(4,100));
	cout << "a : ";
	std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
	cout << endl;

	//std::vector<float> b(20);
	std::deque<int> b(20);
	//std::generate_n(std::inserter(b, b.begin()), 20, Gen<float>(27, 44, 20));
	std::generate(b.begin(), b.end(), Gen<int>(27, 44, 20));
	
	cout << "b : ";
	std::copy(b.begin(), b.end(), std::ostream_iterator<float>(std::cout, " "));
	cout << endl;

	printf("***** CREATION 2D\n");
	typedef vector< vector<float> > vector2d;
	vector2d a2d(5, vector<float>(7));
	for (unsigned int i = 0; i < a2d.size();++i)
		for (unsigned int j = 0; j < a2d[i].size();++j)
			a2d[i][j] = static_cast<float>(i)*i + 5 * j - 4;

	cout << a2d.size() << endl;
	for (auto& i : a2d)
	{
		cout << i.size() << " : ";
		std::copy(i.begin(), i.end(), std::ostream_iterator<float>(std::cout, " "));
		cout << endl;
	}
	cout << endl;


	printf("***** COMPTER\n");

	printf("***** SLICING\n");

	printf("***** PERFORMANCE\n");
	const int NP = 5000;
	const int NT = 10000;
	cout << "***Creation" << endl;
	auto start = std::chrono::system_clock::now();
	vector2d pat(NP, vector<float>(NT));
	for (vector2d::iterator i = pat.begin(); i != pat.end(); ++i)
		std::generate(i->begin(), i->end(), Gen<float>(36, 39, NT));

	vector<float> temp(NP);
	auto end = std::chrono::system_clock::now();
	std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
	//std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s\n";

	cout << "***Calcul" << endl;
	start = std::chrono::system_clock::now();
	for (unsigned int i=0;i<temp.size();++i)
		temp[i] = static_cast<float>(accumulate( pat[i].begin(), pat[i].end(), 0)) / pat[i].size();

	end = std::chrono::system_clock::now();
	std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
	//std::cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s\n";

	if (0)
	{
		cout << pat.size() << endl;
		for (auto& i : pat)
		{
			cout << i.size() << " : ";
			std::copy(i.begin(), i.end(), std::ostream_iterator<float>(std::cout, " "));
			cout << endl;
		}
		cout << "temp : ";
		std::copy(temp.begin(), temp.end(), std::ostream_iterator<float>(std::cout, " "));
		cout << endl;
	}



	system("pause");
	return 0;
}



//for (vector<float>::const_iterator i = b.begin(); i != b.end(); ++i)
//cout << *i << " ";
//cout << endl;
