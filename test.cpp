#include "matrix.h"

float A[][3] = {
                {1,0,0},
                {0,1,0},
                {0,0,1}
              };

float B[][4] = {
                {1,1,0,0},
                {0,2,2,0},
                {0,0,3,3}
              };

float C[][3] = {
                {1,0,0},
                {0,2,0},
                {0,0,3}
              };



float vec_a[] = {1,2,1};
float vec_b[] = {4,3,-2};

bool test_matrix_sub(){
	
	bool result = true;
	cout << "test_matrix_sub::" << endl;

	class matrix<float> a(A[0],3,3);
  class matrix<float> c(C[0],3,3);
	float R[3][3] = {0};
  class matrix<float> r(R[0],3,3);

  matrix<float>::sub(a.ref(), c.ref(), r.ref());

	cout << "matrix A:  "<< endl; 
	a.dump(a.ref());
	cout << "matrix C:  "<< endl; 
	c.dump(c.ref());
	cout << "R = A-B" << endl;
  r.dump(r.ref());

	return result;
}

bool test_matrix_add(){
	
	bool result = true;
	cout << "test_matrix_add::" << endl;

	class matrix<float> a(A[0],3,3);
  class matrix<float> c(C[0],3,3);
	float R[3][3] = {0};
  class matrix<float> r(R[0],3,3);

  matrix<float>::add(a.ref(), c.ref(), r.ref());

	cout << "matrix A:  "<< endl; 
	a.dump(a.ref());
	cout << "matrix C:  "<< endl; 
	c.dump(c.ref());
	cout << "R = A+B" << endl;
  r.dump(r.ref());

	return result;
}

bool test_matrix_mult(){
	
	bool result = true;
	cout << "test_matrix_mult::" << endl;

	class matrix<float> a(A[0],3,3);
  class matrix<float> b(B[0],3,4);
	float C[3][4] = {0};
  class matrix<float> r(C[0], 3,4);

  matrix<float>::mult(a.ref(), b.ref(), r.ref());

	cout << "matrix A:  "<< endl; 
	a.dump(a.ref());
	cout << "matrix B:  "<< endl; 
	b.dump(b.ref());
	cout << "C = A*B" << endl;
  r.dump(r.ref());

	return result;
}

bool test_vec_dot_product(){

	bool ret = true;

	class vec<float> c(vec_a, 3);
  class vec<float> d(vec_b, 3);
  float result = 0;

  c.dot_product(c.ref(), d.ref(), result);
	cout << "vector c:" << endl;
	c.dump(c.ref());
	cout << "vector d:" << endl;
	c.dump(d.ref());
  cout << "c.d =  " << result << endl;

	return ret;
}

bool test_vec_l2_norm(){

	bool ret = true;
	
	class vec<float> c(vec_a, 3);
  float result = c.l2_norm(c.ref());
	
	cout << "vector A:" << endl;
	c.dump(c.ref());

  cout << "l2_norm(A) = " << result << endl;

	return ret;
}

bool test_matrix_transpose(){
	
	bool ret = true;

	class matrix<float> a(B[0],3,4);
	float C[4][3] = {0};
	class matrix<float> r(C[0],4,3);
	matrix<float>::transpose(a.ref(), r.ref());	
	cout << "Matrix A:" << endl;
	matrix<float>::dump(a.ref());
	cout << "transpose(A): " <<  endl;
	r.dump(r.ref());

	return ret;
}

bool test_vector_scalar(){

	bool ret = true;

	class vec<float> a(vec_a, 3);
	float r[3] = {0};
	class vec<float> result(r, 3);
	float s = 2;

	vec<float>::scalar(a.ref(), s, result.ref());
	cout << "vector a: "<< endl;
	a.dump(a.ref());
	cout << "vector a*scalar: " << s << endl;
	result.dump(result.ref());

	return ret;
}

bool test_matrix_scalar(){

	bool ret = true;

	class matrix<float> a(B[0], 3, 4);
	float R[3][4] = {0};
	class matrix<float> r(R[0], 3, 4);
	float s = 2;

	matrix<float>::scalar(a.ref(), s, r.ref());
	cout << "matrix: " << endl;
	a.dump(a.ref());
	cout << "matrix * scalar: " << endl;
	r.dump(r.ref());

	return ret;
}

bool test_vector_sub(){
	
	bool ret = true;
  class vec<float> a(vec_a, 3);
  class vec<float> b(vec_b, 3);
	float vec_r[3] = {0};	
	class vec<float> r(vec_r, 3);

	vec<float>::sub(a.ref(), b.ref(), r.ref());

	cout << "vector a: " << endl;
	a.dump(a.ref());
	
	cout << "vector b: " << endl;
	b.dump(b.ref());

	cout << "vector a-b: " << endl;
	r.dump(r.ref());

	return ret;
}

bool test_vector_add(){
	
	bool ret = true;
  class vec<float> a(vec_a, 3);
  class vec<float> b(vec_b, 3);
	float vec_r[3] = {0};	
	class vec<float> r(vec_r, 3);

	vec<float>::add(a.ref(), b.ref(), r.ref());

	cout << "vector a: " << endl;
	a.dump(a.ref());
	
	cout << "vector b: " << endl;
	b.dump(b.ref());

	cout << "vector a+b: " << endl;
	r.dump(r.ref());

	return ret;
}

bool test_vector_mult(){
	
	bool result = true;

  class vec<float> a(vec_a, 3);
  class vec<float> b(vec_b, 3);
	float R[3][3] = {0};
	class matrix<float> r(R[0], 3, 3);

	cout << "vec a:" << endl;
	a.dump(a.ref());
	cout << "vec b:" << endl;
	b.dump(b.ref());
	cout << "a*(b.T): " << endl;
	result = vec<float>::mult(a.ref(), b.ref(), r.ref());
	r.dump(r.ref());

	return result;
}

bool test_matrix_identity(){
	
	bool result = true;
	float id[3][3] = {0};
	matrix<float> I(id[0], 3, 3);

	matrix<float>::identity(I.ref());

	cout << "identity matrix:" << endl;
	I.dump(I.ref());

	return result;
}

bool test_matrix_assign(){

	bool result = true;

	float right[3][3] = {0};
	matrix<float> A(right[0], 3, 3);

	float left[3][3] = {0};
	matrix<float> B(left[0], 3, 3);

	matrix<float>::identity(A.ref());
	cout << "matrix A:" << endl;
	A.dump(A.ref());
	B = A;
	cout << "B = A, B:" << endl;
	B.dump(B.ref());
	
	float r[3][3] = {0};
	matrix<float> R(r[0],3,3);
	matrix<float>::scalar(A.ref(), 2, R.ref());
	A = R;

	cout << "matrix A = 2*A" << endl;
	A.dump(A.ref());
	cout << "matrix B:" << endl;
	B.dump(B.ref());

	vector<vector<float>> c;
	c = A.ref();

	cout << "c = A.ref(), c:" << endl;
	matrix<float>::dump(c);

	vector<vector<float>> d;
	d = c;
	cout << "d = c, d:" << endl;
	matrix<float>::dump(d);


	return result;	
}

bool test_matrix_QR(){

	bool result = true;
	
	float a[3][3] = { 
										{2,-1,5},
										{2,1,2},
										{1,0,-2}
									};
	float q[3][3] = {0};
	float r[3][3] = {0};
	matrix<float> A(a[0],3,3);
	matrix<float> Q(q[0],3,3);
	matrix<float> R(r[0],3,3);

	matrix<float>::dump(A.ref());

	matrix<float>::QR(A.ref(), Q.ref(), R.ref());

	cout << "Q :" << endl;
	matrix<float>::dump(Q.ref());
	cout << "R :" << endl;
	matrix<float>::dump(R.ref());

	vector<vector<float>> QR;
	matrix<float>::zeros(QR, 3, 3);
	matrix<float>::mult(Q.ref(), R.ref(), QR);
	cout << "QR:" << endl;
	matrix<float>::dump(QR);

	return result;
}

bool test_matrix_frobenius_norm(){

	bool result = false;

	class matrix<float> b(B[0],3,4);
	float norm;
	matrix<float>::frobenius_norm(b.ref(),norm);

	cout << "matrix:" << endl;
	matrix<float>::dump(b.ref());	
	cout << "frobenius_norm(b): "<< norm <<  endl;

	return result;
}

bool test_matrix_QR_iteration(){

	bool result ;
	vector<vector<float>> Q;
	vector<vector<float>> R;
	vector<vector<float>> Qn;
	vector<vector<float>> mult_r;

	matrix<float>::zeros(Qn, 2, 2);
	matrix<float>::identity(Qn);
	
	matrix<float>::zeros(mult_r, 2, 2);
	
	float a[2][2] = {{2,3},
                   {3,2}};
	
	matrix<float> A(a[0],2,2);
	vector<vector<float>> A_copy = A.ref();

	vector<vector<float>> last_iter_matrix = A.ref();

	for(int i=0;i<10;i++){
		
		matrix<float>::zeros(Q, 2, 2);

		matrix<float>::zeros(R, 2, 2);

		matrix<float>::QR(A.ref(), Q, R);
		
		matrix<float>::mult(Qn, Q, mult_r);
		
		Qn = mult_r;

	  cout << "A:" << endl;
		matrix<float>::dump(A.ref());
		cout << "Q:" << endl;
		matrix<float>::dump(Q);
		cout << "R:" << endl;
		matrix<float>::dump(R);
		cout << "Qn:" << endl;
		matrix<float>::dump(Qn);
		
		matrix<float>::mult(R, Q, A.ref());
		
	}

	vector<vector<float>>Qn_T;
	matrix<float>::zeros(Qn_T,2,2);

	matrix<float>::transpose(Qn, Qn_T);

	cout << "Qn_T:" << endl;
	matrix<float>::dump(Qn_T);

	cout << "Qn_T*Qn: " << endl;
	matrix<float>::mult(Qn_T, Qn, mult_r);
	matrix<float>::dump(mult_r);

	matrix<float>::mult(Qn_T, A_copy, mult_r);
	matrix<float>::mult(mult_r, Qn, Qn_T);

	cout << "Qn_T*A*Qn: " << endl;
	matrix<float>::dump(Qn_T);

	return result;
}

int main(){

#if 0
	test_vec_dot_product();
	test_vec_l2_norm();
	test_matrix_mult();
	test_matrix_transpose();

  test_vector_scalar();
	test_matrix_scalar();
	test_vector_sub();
	test_vector_add();

	test_matrix_add();
	test_matrix_sub();

  test_vector_mult();
	test_matrix_identity();
	test_matrix_assign();
	
	test_matrix_QR();
	test_matrix_frobenius_norm();
#endif

  test_matrix_QR_iteration();

  return 0;
}
