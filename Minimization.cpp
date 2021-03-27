#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //for sort function
using namespace std;

//functions declaration
void var2(vector <int> v);
void var3(vector <int> v3);

// function 2 variable k map
void var2(vector <int> v)
{
	int kmap2[2][2] = { 0 };
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == 0)
			kmap2[0][0] = 1;
		if (v[i] == 1)
			kmap2[0][1] = 1;
		if (v[i] == 2)
			kmap2[1][0] = 1;
		if (v[i] == 3)
			kmap2[1][1] = 1;
	}

	int i = 0;
	for (int j = 0; j < 2; j++)
	{
		cout << kmap2[i][j] << " ";
	}
	cout << endl;
	i = 1;
	for (int j = 0; j < 2; j++)
	{
		cout << kmap2[i][j] << " ";
	}
	cout << endl;
}

// function for 3 variable kmap 
void var3(vector <int> v3)
{
	int kmap3[2][4] = { 0 };
	for (int i = 0; i < v3.size(); i++)
	{
		if (v3[i] == 0)
			kmap3[0][0] = 1;
		if (v3[i] == 1)
			kmap3[0][1] = 1;
		if (v3[i] == 2)
			kmap3[0][3] = 1;
		if (v3[i] == 3)
			kmap3[0][2] = 1;
		if (v3[i] == 4)
			kmap3[1][0] = 1;
		if (v3[i] == 5)
			kmap3[1][1] = 1;
		if (v3[i] == 6)
			kmap3[1][3] = 1;
		if (v3[i] == 7)
			kmap3[1][2] = 1;
	}
	int i = 0;
	for (int j = 0; j < 4; j++)
	{
		cout << kmap3[i][j] << " ";
	}
	cout << endl;
	i = 1;
	for (int j = 0; j < 4; j++)
	{
		cout << kmap3[i][j] << " ";
	}
	cout << endl;
}

vector<string> toBinary(vector<int> minterm, int vars) {
	
	// number of digits = num of vars
	vector <string> storeBinary;
	for (int i = 0; i < minterm.size(); i++) {
		string b,
			newBit;
		while (minterm[i] > 0) {
			newBit = to_string(minterm[i] % 2); 
			minterm[i] = minterm[i] / 2;
			b = newBit + b; //at the end it's the number of in binary
		}
		
		while (b.length() != vars)
		{
			b = "0" + b;
		}
		storeBinary.push_back(b);
	}

	return storeBinary;
}

//a function to re-arrange the vector according to the number of ones in each string (ascending order)
void arrange_ones(vector<string> &str) {
	
	//vector of pairs <num of ones, the binary num>
	vector<pair<int, string>> count;
	int ones;

	for (int i = 0; i < str.size(); i++) {
		ones = 0;
		for (int j = 0; j < str[i].length(); j++) {
			if (str[i][j] == '1')
				ones++;
		}
		count.push_back(make_pair(ones, str[i]));
	}

	sort(count.begin(), count.end());

	for (int i = 0; i < str.size(); i++) {
		str[i] = count[i].second;
	}
}

void lett(string a)
{
	if (a[0] == '0') cout << "A'"; else if (a[0] == '1') cout << "A";
	if (a[1] == '0') cout << "B'"; else if (a[1] == '1') cout << "B";
	if (a[2] == '0') cout << "C'"; else if (a[2] == '1') cout << "C";

}
void letters(vector<string> min)
{
	// we now have array of minterm (all different )
	for (int i = 0; i < min.size(); i++) //over ever sting 
	{
		lett(min[i]);
		cout << " + ";
	}

}

// function that returns true when only 1 difference 
bool compare(string& a, string& b)
{         // 0011 0001

	int count = 0;
	// saves the indieces of the common element 
	
	int c = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) // common element found 
		{
			count++;
			c = i;
		}
	}

	if (count == 1)
	{
		// turn the common element into "-" element index is c
		a.replace(c, 1, "-");
		b.replace(c, 1, "-");
		return true;
	}
	else
		return false;
}

vector<string> minimize(vector<string> binary) {

	vector<string> binary2;
	bool flag = false;

	for (int i = 0; i < binary.size(); i++) {
		for (int j = i + 1; j < binary.size(); j++) {
			if (compare(binary[i], binary[j])) {
				binary2.push_back(binary[i]);
				flag = true;
				//binary2 will contain numbers with '-'
			}
		}
	}
	if (flag)
		return minimize(binary2);
	else 
		return binary2;
}


int main()
{
	int vars, min_n;
	cout << "How many variables in your function? ";
	cin >> vars;
	cout << "How many minterms do your function have? ";
	cin >> min_n;
	vector<int> minterms;
	//minterms.resize(min_n);
	cout << "Enter your minterms: (press Enter after each number)" << endl;

	int min;
	for (int i = 0; i < min_n; i++)
	{
		cin >> min;
		while (min <0 || min > pow(2, vars) - 1)
		{
			cout << "Invalide input. Please Enter a number between 0 and " << pow(2, vars) - 1 << endl;
			cin >> min;
		}
		minterms.push_back(min);
	}

	/*cout << "Your function k-map is: " <<endl;
	if (vars == 2) {
		var2(minterms);
	}
	if (vars == 3) {
		var3(minterms);
	}*/


	//test to toBinary
	vector<string> binary = toBinary(minterms, vars);
	//test to arrange ones 
	//step (1)
	arrange_ones(binary);
	/*for (int i = 0; i < binary.size(); i++)
		cout << binary[i] << endl;*/

	vector<string> minimized = minimize(binary);



	//optional to print the minterms
	/*for (int i = 0; i < minterms.size(); i++)
		cout << minterms[i] << " ";
	cout << endl;*/

	//test to diff
	/*string a = "0100", b = "0100";
	if (diff(a, b))
		cout << a << "  " << b <<endl;
	else
		cout << "sth wrong" << endl;*/

	//test for letters
	//letters(s);


	system("pause");
	return 0;
}

/*
* converting minterms to binary
* function: returns the number of ones
* step 1: num of ones --> grouping (arranging them to be after each other)
* step 2: compair each number with the rest
*		  function returns true if there is one element different (put '-' instead of it)
*		  delete one element and replace the other with the number having '-'
* step 3: repeat step 2
* step 4: 
* 
*		
*/