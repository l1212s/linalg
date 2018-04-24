#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<class T>
class vec{

public:
	vec(T *mat, int len){

		for(int i=0; i< len; i++)
			v_vec.push_back(mat[i]);
	}

	vector<T> &ref(){
		return v_vec;
	}

	// v.T*v = scalar 
	static bool dot_product(vector<T> &a, vector<T> &b, T &result);
	// v.T*v = nxn matrix
	static bool mult(vector<T> &a, vector<T> &b, vector<vector<T>> &r);
	static bool scalar(vector<T> &a, T scalar, vector<T> &result);
	static bool sub(vector<T> &a, vector<T> &b, vector<T> &r);
	static bool add(vector<T> &a, vector<T> &b, vector<T> &r);
	static T l2_norm(vector<T> &v);
	static void dump(vector<T> &v);
	static void zeros(vector<T> &v, int len);
private:
	vector<T> v_vec;

};

template<class T>
void vec<T>::zeros(vector<T> &v, int len){

		v.clear();

		for(int i=0;i<len;i++){
			v.push_back(0);
		}

}


template<class T>
bool vec<T>::mult(vector<T> &a, vector<T> &b, vector<vector<T>> &r){

	bool result = false;
	int len_a = a.size();
	int len_b = b.size();
	int len_row_r = r.size();
	int len_col_r = r[0].size();

	if(len_a == len_b && len_a == len_row_r && len_a == len_col_r){
		for(int i = 0; i< len_a; i++){
			for(int j= 0; j < len_a; j++){
				r[i][j] = a[i]*b[j];
			}
		}
		result = true;
	}
	
	return result;	
}


template<class T>
bool vec<T>::add(vector<T> &a, vector<T> &b, vector<T> &r){
	
	bool result = false;
	int len_a = a.size();
	int len_b = b.size();
	int len_r = r.size();

	if(len_a == len_b && len_a == len_r){

		for(int i=0; i<len_a; i++){
			r[i] = a[i] + b[i];		
		}

		result = true;
	}
	return result;
}


template<class T>
bool vec<T>::sub(vector<T> &a, vector<T> &b, vector<T> &r){
	
	bool result = false;
	int len_a = a.size();
	int len_b = b.size();
	int len_r = r.size();

	if(len_a == len_b && len_a == len_r){

		for(int i=0; i<len_a; i++){
			r[i] = a[i] - b[i];		
		}

		result = true;
	}
	return result;
}

template<class T>
bool vec<T>::scalar(vector<T> &a, T scalar, vector<T> &result){

	int len_a = a.size();
	int len_r = result.size();
	bool ret = false;

	if(len_a == len_r){

		for(int i=0;i<len_a;i++){
			result[i] = a[i] * scalar;
		}
		ret = true;

	}
	
	return ret;
}

template<class T>
bool vec<T>::dot_product(vector<T> &a, vector<T> &b, T &result)
{
	int len_a = a.size();
	int len_b = b.size();

#if DEBUG
	dump(a);
	dump(b);
#endif

	if(len_a != len_b)
		return false;
	else{
		result = 0;
		for(int i = 0; i< len_a; i++){
			result += a[i] * b[i];
		}	
	}

#if DEBUG	
	cout << "dot_product: " << result << endl;
#endif

	return true;
};

template<class T>
T vec<T>::l2_norm(vector<T> &v){

	T result;	
	dot_product(v, v, result);
	result = sqrt(result);
	
	return result;
}

template<class T>
void vec<T>::dump(vector<T> &v){

	int len = v.size();
	for(int i=0; i< len; i++){
		cout << " " << v[i]; 
	}
	cout << endl;

}


