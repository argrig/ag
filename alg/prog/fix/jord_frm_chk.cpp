#include "myqmatr.h"

#define DIM 4


int main() {
  myMatrix A(DIM, DIM), C(DIM, DIM), J(DIM, DIM) ;
  cin >> A >> C >> J ;
  myMatrix left = C.rvs()*A*C ;
//  cout << "C1*AC = " << left << "J = " << J ;
  if (A*C == C*J) {
    cout << 2 ;
    exit(2) ;
  }
  else {
    cout << 1 ;
    exit (1) ;
  }
}
