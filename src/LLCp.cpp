#include <Rcpp.h>
#include <cmath>
#include <omp.h>
using namespace Rcpp;

//[[Rcpp::plugins(openmp)]]

// [[Rcpp::export]]
double LLC_cpp(NumericVector X, double L, double A) {
  int n = X.size();
  double LLC = 0.0;
  for (int i = 0; i < n; ++i) {
    LLC += fmax(0.0, fmin(X[i] - A, L));
  }
  return(LLC);
}

// [[Rcpp::export]]
double LLC_cpps(NumericVector X, double L, double A) {
  int n = X.size();
  double LLC = 0.0;
#pragma omp simd reduction(+: LLC)  
  for (int i = 0; i < n; ++i) {
    LLC += fmax(0.0, fmin(X[i] - A, L));
  }
  return(LLC);
}

// [[Rcpp::export]]
double LLC_cppl(NumericVector X, double L, double A) {
  int n = X.size();
  double LLC = 0.0;
#pragma omp parallel for schedule(static), reduction(+:LLC)
  for (int i = 0; i < n; ++i) {
    LLC += fmax(0.0, fmin(X[i] - A, L));
  }
  return(LLC);
}

// [[Rcpp::export]]
double LLC_cppls(NumericVector X, double L, double A) {
  int n = X.size();
  double LLC = 0.0;
#pragma omp parallel for simd schedule(static), reduction(+:LLC)
  for (int i = 0; i < n; ++i) {
    LLC += fmax(0.0, fmin(X[i] - A, L));
  }
  return(LLC);
}