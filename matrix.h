#include "vec.h"

using namespace std;

template<class T>
class matrix{

public:
	matrix(T *mat, int row, int col){

	    for(int i=0; i< row; i++){
				for (int j=0; j< col; j++){
					T elem = *(mat + i*col + j);
					v_row.push_back(elem);
				}
				v_mat.push_back(v_row);
				v_row.clear();
			}
	}
	vector<vector<T>> & ref();

	static void identity(vector<vector<T>> &I);
	static void dump(vector<vector<T>> &v);
	static bool mult(vector<vector<T>> &left, vector<vector<T>> &right, vector<vector<T>> &result);
	static void transpose(vector<vector<T>> &mat, vector<vector<T>> &result);
	static bool scalar(vector<vector<T>> &a, T scalar, vector<vector<T>> &result);
	static bool add(vector<vector<T>> &a, vector<vector<T>> &b, vector<vector<T>> &r);
	static bool sub(vector<vector<T>> &a, vector<vector<T>> &b, vector<vector<T>> &r);
	static bool QR(vector<vector<T>> &A, vector<vector<T>> &Q, vector<vector<T>> &R);
	static void zeros(vector<vector<T>> &a, int row, int col);
	static void frobenius_norm(vector<vector<T>> &mat, T &result);	

private:
	vector<T> v_row;
	vector<vector<T>> v_mat;
	static bool get_row_col_vec(vector<vector<T>> &mat, vector<T> &v, bool is_row, int indx);
	static bool set_row_col_vec(vector<vector<T>> &mat, vector<T> &v, bool is_row, int indx);
};

// froenius_norm = math.sqrt(sum(sum(abs(aij))^2))
// https://en.wikipedia.org/wiki/Matrix_norm
template<class T>
void matrix<T>::frobenius_norm(vector<vector<T>> &mat, T &result){

	int row_len = mat.size();
	int col_len = mat[0].size();
	bool is_row;
	vector<T> v;
	T v_norm;

	result = 0;
	is_row = false;
	v_norm = 0;
	
	for(int i=0; i<col_len;i++ ){
			v.clear();
	    get_row_col_vec(mat, v, is_row, i);	
			v_norm = vec<T>::l2_norm(v);
			cout << "v_norm: " << v_norm<< endl;
			result += v_norm*v_norm;
	}
	result = sqrt(result);
}

template<class T>
void matrix<T>::zeros(vector<vector<T>> &a, int row, int col){

	vector<T> v_col;
	a.clear();

	for(int i=0;i<row;i++){
		v_col.clear();
		for(int j=0;j<col;j++){
			v_col.push_back(0);	
		}
		a.push_back(v_col);
	}	
}

template<class T>
void matrix<T>::identity(vector<vector<T>> &I){

	int len_row = I.size();
	int len_col = I[0].size();
	
	for(int i=0;i<len_row;i++){
		for(int j=0; j< len_col; j++){
			if(i == j){
				I[i][j] = 1;
			}
			else{
				I[i][j] = 0;	
			}
		}
	}	
}

template<class T>
bool matrix<T>::QR(vector<vector<T>> &A, vector<vector<T>> &Q, vector<vector<T>> &R){

	int result = false;

	int a_row_len = A.size();
	int a_col_len = A[0].size();

	int loop = 0;

	if(a_row_len == a_col_len)
		loop = a_col_len - 1;
	else 
		loop = a_col_len;

	vector<vector<T>> In;
	vector<vector<T>> Rn;
	vector<vector<T>> Hn;
	
	matrix<T>::zeros(In, a_row_len, a_row_len);
	matrix<T>::identity(In);
	matrix<T>::zeros(Hn, a_row_len, a_row_len);
	matrix<T>::zeros(Rn, a_row_len, a_col_len);

#if DEBUG_QR	
	cout << "In" << endl;
	dump(In);
	cout << "Hn" << endl;
	dump(Hn);
	cout << "Rn" << endl;
	dump(Rn);
#endif 

	vector<T> vn ;
	vector<T> en ;
	vector<T> an ;

	vec<T>::zeros(vn, a_row_len);
	vec<T>::zeros(en, a_row_len);
	vec<T>::zeros(an, a_row_len);

	Rn = A;
	vector<vector<T>> Qn = In;	

	for(int i=0; i<loop; i++){
		vec<T>::zeros(en, a_row_len);
		en[i] = 1;
		
		for(int j = 0; j< a_row_len; j++){
			if(j<i){
				an[j] = 0;
			}
			else{
				an[j] = Rn[j][i];
			}
		}

#if DEBUG_QR	
		cout << "an" << endl;
		vec<T>::dump(an);
#endif

		T cn = vec<T>::l2_norm(an);

#if DEBUG_QR	
		cout << "norm: " <<  cn << endl;	
#endif
	
		int sign = 0;
		if(an[i] > 0){
			//sign = -1;
			sign = 1;
		}
		else if(an[i] < 0){
			//sign = 1;
			sign = -1;
		}
		
		//vn = an - sign*cn*en;
		vector<T> r_vec;
		vec<T>::zeros(r_vec, a_row_len);
		T vn_scalar = cn * sign;

#if DEBUG_QR	
		cout << "vn_scalar:" << vn_scalar<< endl;
		cout << "en:" << endl;
		vec<T>::dump(en);
#endif
		vec<T>::scalar(en, vn_scalar, r_vec);
#if DEBUG_QR	
		cout << "r_vec:" << endl;
#endif 
		vec<T>::sub(an, r_vec, vn);

#if DEBUG_QR	
		cout <<"vn: " << endl;
		vec<T>::dump(vn);
#endif
	
		//Hn = In - 2 * vec<T>::mult(vn, vn.T) / vec<T>::dot_product(vn.T, vn);
		vector<vector<T>> r_mat_mult;
		matrix<T>::zeros(r_mat_mult, a_row_len, a_row_len);
		vec<T>::mult(vn, vn, r_mat_mult);

		T scalar;
		 vec<T>::dot_product(vn, vn, scalar);
		scalar = 2 / scalar;
		vector<vector<T>> r_mat_scalar;
		matrix<T>::zeros(r_mat_scalar, a_row_len, a_row_len);
		matrix<T>::scalar(r_mat_mult, scalar, r_mat_scalar);
				
		matrix<T>::sub(In, r_mat_scalar, Hn);
#if DEBUG_QR	
		cout << "Hn:" << endl;	
		matrix<T>::dump(Hn);
#endif

		vector<vector<T>> Rn_new = Rn;
		matrix<T>::mult(Hn, Rn, Rn_new);
		Rn = Rn_new;
#if DEBUG_QR	
		cout << "Rn" << endl;
		matrix<T>::dump(Rn);
#endif	
		// H2*H1*A = R
    // A = H1.T*H2.T()*R;
		// Q = H1.T*H2.T
		vector<vector<T>> Hn_T;
		matrix<T>::zeros(Hn_T, a_row_len, a_row_len);
	
		matrix<T>::transpose(Hn, Hn_T);
		matrix<T>::mult(Qn, Hn_T, Q);
#if DEBUG_QR	
		cout << "Q:" << endl;
		matrix<T>::dump(Q);	
#endif 
		Qn = Q;
	}

	R = Rn;

	return result;
}

template<class T>
bool matrix<T>::add(vector<vector<T>> &a, vector<vector<T>> &b, vector<vector<T>> &r){

	bool result = false;	
	int a_row_len = a.size();
	int a_col_len = a[0].size();
	int b_row_len = b.size();
	int b_col_len = b[0].size();
	int r_row_len = r.size();
	int r_col_len = r[0].size();

	if(a_row_len == b_row_len && a_col_len == b_col_len && a_row_len == r_row_len && a_col_len == r_col_len){
	
		for(int i=0; i<a_row_len; i++){
			for(int j=0;j<a_col_len; j++){
				r[i][j] = a[i][j] + b[i][j];
				cout << r[i][j] << " " << a[i][j] << " "<< b[i][j] << endl;
			}
		}		
		result = true;
	}

	return result;
}

template<class T>
bool matrix<T>::sub(vector<vector<T>> &a, vector<vector<T>> &b, vector<vector<T>> &r){

	bool result = false;	
	int a_row_len = a.size();
	int a_col_len = a[0].size();
	int b_row_len = b.size();
	int b_col_len = b[0].size();
	int r_row_len = r.size();
	int r_col_len = r[0].size();

	if(a_row_len == b_row_len && a_col_len == b_col_len && a_row_len == r_row_len && a_col_len == r_col_len){
	
		for(int i=0; i<a_row_len; i++){
			for(int j=0;j<a_col_len; j++){
				r[i][j] = a[i][j] - b[i][j];
			}
		}		
		result = true;
	}

	return result;
}


template<class T>
bool matrix<T>::scalar(vector<vector<T>> &a, T scalar, vector<vector<T>> &r){

	int ret = false;
	int row_len_a = a.size();
	int col_len_a = a[0].size();
	int row_len_r = r.size();
	int col_len_r = r[0].size();
	
	if( (row_len_a == row_len_r) && (col_len_a == col_len_r) ){

		for(int i=0;i<row_len_a;i++){
			for(int j=0; j<col_len_a; j++){
				r[i][j] = a[i][j] * scalar;			
			}
		}
		ret = true;
	}

	return ret;
}

template<class T>
void matrix<T>::transpose(vector<vector<T>> &mat, vector<vector<T>> &result){

	int row_len = mat.size();
	vector<T> v;
	bool is_row;
	for(int i = 0; i< row_len; i++){
		v.clear();
		is_row = true;
		get_row_col_vec(mat, v, is_row, i);
		is_row = false;
		set_row_col_vec(result, v, is_row, i);
	}

}

template<class T>
bool matrix<T>::set_row_col_vec(vector<vector<T>> &mat, vector<T> &v, bool is_row, int indx){
	
	bool result = false;

	int row_len = mat.size();
	int col_len = mat[0].size();
	int v_len = v.size();

	if(v_len != row_len){
		cout << "set_row_col_vec::vec_len does not match row_len: " << v_len << " " << row_len << endl;
		return result;
	}
		

	if(is_row){
		if(indx < row_len){
			for(int i=0; i< col_len; i++){
				mat[indx][i]=v[i];
			}
			result = true;
		}
	}
	else{
		if(indx < col_len){
			for(int i=0; i< row_len; i++){
				mat[i][indx] = v[i];
				//cout << " " << v[i] ;
			}
			//cout << endl;
			result = true;
		}
	}
	
	return result;
}


template<class T>
bool matrix<T>::get_row_col_vec(vector<vector<T>> &mat, vector<T> &v, bool is_row, int indx){
	
	bool result = false;

	int row_len = mat.size();
	int col_len = mat[0].size();

	if(is_row){
		if(indx < row_len){
			for(int i=0; i< col_len; i++){
				v.push_back(mat[indx][i]);
			}
			result = true;
		}
	}
	else{
		if(indx < col_len){
			for(int i=0; i< row_len; i++){
				v.push_back(mat[i][indx]);
			}
			result = true;
		}
	}
	
	return result;
}

template<class T>
bool matrix<T>::mult(vector<vector<T>> &left_mat, vector<vector<T>> &right_mat, vector<vector<T>> &result){

	int left_row_len = left_mat.size();
	int left_col_len = left_mat[0].size();
	int right_row_len = right_mat.size();
	int right_col_len = right_mat[0].size();
	int is_valid = false;
	bool is_row;
	vector<T> v_left;
	vector<T> v_right;
	T aij;

	if(left_col_len == right_row_len){
		for(int i=0;i<left_row_len;i++){
				is_row = true;
				v_left.clear();
				get_row_col_vec(left_mat, v_left, is_row, i);
			for(int j=0; j< right_col_len;j++){
				is_row = false;
				v_right.clear();
				get_row_col_vec(right_mat, v_right, is_row, j);
				vec<T>::dot_product(v_left, v_right, aij);	
				result[i][j] = aij;
			}
		}
		is_valid = true;
	}

	return is_valid;
}

template<class T>
vector<vector<T>>& matrix<T>::ref(){

	return v_mat;

}

template<class T>
void matrix<T>::dump(vector<vector<T>> &v){

	int row = v.size();

	for(int i=0;i< row;i++){
		int col = v[i].size();
		for(int j=0; j<col ; j++){
			cout << " " << v[i][j];
		}
		cout << endl;
	}
}


