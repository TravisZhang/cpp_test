#include <bits/stdc++.h>

using namespace std;

class Quat
{
public:

	int r_min=0,r_max=0,c_min=0,c_max=0;

	Quat(int a, int b, int c, int d):r_min(a),r_max(b),c_min(c),c_max(d){};
	
};

void matrix_add(vector<float>& C, vector<float>& A, vector<float>& B, Quat& c)
{
	int n = sqrt(C.size());
	int m = sqrt(A.size());
	cout << "oooo " << n << endl;
	int offset = c.r_min * n/2 * n + c.c_min * n/2;
	for(int i = 0;i < m;++i)
	{
		for(int j = 0;j < m;++j)
		{
			int i_temp = i*m+j;
			int index_temp = i*m+j + offset + i*n/2;
			C[index_temp] = A[i_temp] + B[i_temp];
			cout << "eeee " << c.r_min << " " << c.c_min << endl;
			cout << "dddd " << index_temp << " " <<  C[index_temp] << endl;
		}
	}
}


vector<float> sq_matrix_mul_recursive(vector<float>& A, vector<float>& B
										,Quat a, Quat b)
{
	int n = sqrt(A.size());
	cout << "n: " << n <<endl;
	
	if(a.r_min == a.r_max)
	{
		cout << "aaaa " << a.r_min << " " << b.r_min << endl;
		int a_i = a.r_min * n + a.c_min;
		int b_i = b.r_min * n + b.c_min;
		cout << "ssss " << A[a_i] * B[b_i] << endl;
		vector<float> C{A[a_i] * B[b_i]};
		return C;
	}
	else
	{
		vector<float> C;
		C.resize(A.size(),0);

		cout << "c size: " << C.size() <<endl;

		float ar2 = ((a.r_max-a.r_min)*0.5);
		float ac2 = ((a.c_max-a.c_min)*0.5);

		cout << "ar2: " << ar2 << endl;
		cout << "ac2: " << ac2 << endl;

		Quat a11(a.r_min, floor(a.r_min+ar2), a.c_min, floor(a.c_min+ac2));
		Quat a21(ceil(a.r_min+ar2), a.r_max, a.c_min, floor(a.c_min+ac2));
		Quat a12(a.r_min, floor(a.r_min+ar2), ceil(a.c_min+ac2), a.c_max);
		Quat a22(ceil(a.r_min+ar2), a.r_max, ceil(a.c_min+ac2), a.c_max);

		float br2 = ((b.r_max-b.r_min)*0.5);
		float bc2 = ((b.c_max-b.c_min)*0.5);

		cout << "br2: " << br2 << endl;
		cout << "bc2: " << bc2 << endl;

		Quat b11(b.r_min, floor(b.r_min+br2), b.c_min, floor(b.c_min+bc2));
		Quat b21(ceil(b.r_min+br2), b.r_max, b.c_min, floor(b.c_min+bc2));
		Quat b12(b.r_min, floor(b.r_min+br2), ceil(b.c_min+bc2), b.c_max);
		Quat b22(ceil(b.r_min+br2), b.r_max, ceil(b.c_min+bc2), b.c_max);

		vector<float> S1111 = sq_matrix_mul_recursive(A,B,a11,b11);
		vector<float> S1221 = sq_matrix_mul_recursive(A,B,a12,b21);
		Quat c11(0, floor(ar2), 0, floor(ac2));
		matrix_add(C,S1111,S1221,c11);

		vector<float> S1112 = sq_matrix_mul_recursive(A,B,a11,b12);
		vector<float> S1222 = sq_matrix_mul_recursive(A,B,a12,b22);
		Quat c12(0, floor(ar2), ceil(ac2), a.c_max-a.c_min);
		matrix_add(C,S1112,S1222,c12);

		vector<float> S2111 = sq_matrix_mul_recursive(A,B,a21,b11);
		vector<float> S2221 = sq_matrix_mul_recursive(A,B,a22,b21);
		Quat c21(ceil(ar2), a.r_max-a.r_min, 0, floor(ac2));
		matrix_add(C,S2111,S2221,c21);

		vector<float> S2112 = sq_matrix_mul_recursive(A,B,a21,b12);
		vector<float> S2222 = sq_matrix_mul_recursive(A,B,a22,b22);
		Quat c22(ceil(ar2), a.r_max-a.r_min, ceil(ac2), a.c_max-a.c_min);
		matrix_add(C,S2112,S2222,c22);

		cout << "asdadsasd" << endl;
		return C;
	

	}

}

void print_matrix(vector<float>& m)
{
	cout << "----- printing matrix -----" << endl;
	int n = sqrt(m.size());

	for(int i = 0;i < n;++i)
	{
		for(int j = 0;j < n;++j)
		{
			int index_temp = i*n+j;
			printf(" %.1f ",m[index_temp]);
		}
		cout<<endl;
	}

	cout << "done !!!" << endl;
}


int main()
{
	vector<float> A,B,C;

	int n = 4;

	A.resize(n*n);
	B.resize(n*n);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int index_temp = i*n+j;
			/* generate random number between 1 and 10: */
			A[index_temp] = rand() % 10 + 1;
			B[index_temp] = rand() % 10 + 1;
		}
	}

	print_matrix(A);
	print_matrix(B);

	Quat a(0,n-1,0,n-1), b(0,n-1,0,n-1);

	C = sq_matrix_mul_recursive(A,B,a,b);

	print_matrix(C);


	

    return 0;
}
