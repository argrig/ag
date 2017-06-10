#include "myqmatr.h"
#include "mytex.h"
#include "mypermut.h"

#define DIM 4
#define R_RAD 3
#define ABS_MAX 40

size_t is_triang(myMatrix& X) {
	// returns 2 -- upzero; 1 -- downzero ; 3 diag ; 0 -- not triang ???
  int k = X.size(), n=X[0].size() ;
  size_t res=3 ;
  for (size_t i=0; i<k && (res&2 == 2) ; i++) {
    for(size_t j=i+1; j<n ; j++){
        if(X[i][j] != 0)  res = (res | 2) xor 2;
    }
  }

  for (size_t j=0 ; j<n && (res&1 == 1) ; j++) {
    for(size_t i=j+1 ; i<k ; i++){
        if(X[i][j] != 0) res = (res | 1) xor 1  ;
    }
  }
  return res ;
 }

myMatrix jord (size_t r, myScalar lambda) {
  myMatrix res=diag(lambda, r) ;
  for (size_t i=1; i<r; i++) {
	res[i][i-1] = 1 ;
  }
  return res ;
}

// two matrix direct sum 
myMatrix dsum (myMatrix A, myMatrix B) {
  myMatrix zero_A(A.size(), B[0].size(), 0) ;
  myMatrix zero_B(B.size(), A[0].size(), 0) ;
  myMatrix res1 = A.concat(zero_A,'|') ;
  myMatrix res2 = zero_B.concat(B,'|') ;
  return res1.concat(res2, '-') ;
}

// natural number num decomposition to cnt summands  
vector<size_t> decomp (size_t num, size_t cnt=0) {
  myVector empty(0) ;
  vector<size_t> res(0);
  if (num==0) {return res;}
  if (cnt==0) {
	cnt=rand()%num+1  ;
  }
  size_t rest=num ;
  for(size_t i=0; i<cnt && rest>0; rest-=res[i], i++) {
	size_t rnd = rand()%(rest-cnt+i+1)+1 ;
	size_t push = (i==cnt-1) ? rest : rnd ;
	res.push_back(push) ;
  }
  return res ;
}

myVector gen_roots(size_t root_num ) {
  myVector res(root_num) ;
  myPermut yo(2*R_RAD) ;
  yo.gen_rand() ;
//  cout << yo <<endl ;
  for (size_t i=0; i<root_num; i++) {
    res[i] = (int)R_RAD - (int)( (yo[i]<R_RAD) ? yo[i] : yo[i] + 1 ) ;
  }
  return res ;
}

int main() {
  myVector empty(0) ;
  myMatrix j_matr[DIM] ;
  myMatrix j_matrix;
  size_t rrn = rand()%10 ;
  size_t root_num = (rrn<6) ? 1 : ((rrn<9) ? 2 : 3) ;
  myVector roots = gen_roots(root_num) ;
  vector<size_t> krat = decomp(DIM, root_num) ;
//  cout << "root_num = " << root_num << endl ;
  size_t j_num ;

do {
    j_num = 0 ;
    for (size_t r=0 ; r<root_num; r++) {
      vector<size_t> j_root = decomp(krat[r]) ;
      for(size_t dec=0 ; dec<j_root.size() ; dec++) {
    	j_matr[j_num] = jord (j_root[dec],roots[r]) ;
	j_num++ ;
      }
    }
  
  j_matrix = j_matr[0] ;
  for(size_t i=1; i<j_num; i++) {
  	j_matrix = dsum(j_matrix,j_matr[i]) ;
  }
} while ( is_triang(j_matrix) == 3 && root_num == 1) ;
  myMatrix C(4,4), C1(4,4), A(4,4) ;

  do {
    C  = gen_uni(4,1,1) ;
    C1 = C.rvs() ;
    A = C*j_matrix*C1 ;
  } while (A.abs_max()>ABS_MAX || is_triang(A)) ;

  cout << "Вычисллить жорданову нормальную форму матрицы и найти жорданов базис:\n\n $$" ;
  tex_matrix(A) ; cout << "$$\n\n" ;
  cout << "%struct=\n%" ;
  for(size_t i=0; i<j_num; i++) {
    cout << j_matr[i].size() << ":" << j_matr[i][0][0] << ";" ;
  }
  comment_matrix (j_matrix, "jord") ;
  comment_matrix (A,"A") ;
  comment_matrix (C, "tranc") ;
  
  cerr << "Жорданова нормальная форма:\n\n$$" ; tex_matrix(j_matrix, cerr) ;
  cerr << "$$\n\nМатрица перехода к жорданову базису:\n\n$$" ; tex_matrix(C, cerr) ; cerr << "$$\n" ;


  exit(0) ;
}
