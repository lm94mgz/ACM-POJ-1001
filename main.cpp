#include <iostream>
#include <string>

using namespace std;

void multiply(string &lhs, string rhs)
{	
	// 倒序存放运算的结果
	string result(lhs.size() + rhs.size(), '0');

	// 做忽略小数点的乘法
	int res_pos = 0;
	for (string::reverse_iterator rhs_ri = rhs.rbegin(); rhs_ri != rhs.rend(); ++rhs_ri)
	{
		if (*rhs_ri != '.')
		{
			int carry = 0;		// 进位
			string::iterator res_si = result.begin() + res_pos++;
			for (string::reverse_iterator lhs_ri = lhs.rbegin(); lhs_ri != lhs.rend(); ++lhs_ri)
			{
				if (*lhs_ri != '.')
				{
					int mul_tmp = (*rhs_ri - '0') * (*lhs_ri - '0');
					int add_tmp = mul_tmp % 10 + (*res_si - '0') + carry;
					*res_si++ = (int)(add_tmp % 10) + '0';
					carry = mul_tmp / 10 + add_tmp / 10;
				}
			}

			// 处理最后的进位
			while (carry > 0 && res_si != result.end())
			{
				int add_tmp = (*res_si - '0') + carry;
				*res_si++ = (int)(add_tmp % 10) + '0';
				carry = add_tmp / 10;
			}
		}
	}

	// 添加小数点
	string::size_type res_point = 0;

	string::size_type lhs_point = lhs.find('.');
	if (lhs_point != string::npos)
	{
		res_point += lhs.size() - 1 - lhs_point;
	}

	string::size_type rhs_point = rhs.find('.');
	if (rhs_point != string::npos)
	{
		res_point += rhs.size() - 1 - rhs_point;
	}

	if (res_point > 0)
	{
		result.insert(result.begin() + res_point, '.');
	}

	string::reverse_iterator res_rb = result.rbegin();
	string::reverse_iterator res_re = result.rend();

	// 首部除0
	while (res_rb != result.rend() && *res_rb == '0') 
		res_rb++;

	// 如果是小数，尾部除0
	if (res_point > 0)
	{
		while (res_re != result.rbegin() && *(res_re - 1) == '0') res_re--;		// 除掉小数后面连续的0
		if (res_re != result.rbegin() && *(res_re - 1) == '.') res_re--;		// 如果最后一位是小数点，也除掉
	}

	// 倒序赋值
	lhs.assign(res_rb, res_re);
}

int main()
{
	string s;
	int n;
	while (cin >> s >> n)
	{
		string r = "1";		// 0次方的结果是1
		for (int i = 0; i < n; ++i)
		{
			multiply(r, s);
		}
		cout << r << endl;
	}
	return 0;
}
