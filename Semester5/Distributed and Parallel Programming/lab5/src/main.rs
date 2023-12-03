use std::sync::Arc;
use rayon::{iter::{ParallelIterator, IntoParallelIterator}, ThreadPool};
use rayon_join_macro::join;
use std::{ops::{Add, Neg}, time::Instant};
use core::cmp::{min, max};
use rand;

#[derive(Clone, Eq, PartialEq)]
struct Polynomial {
  coefs: Vec<i32>
}

impl Polynomial {
  pub fn new_from_coefs(coefs: Vec<i32>) -> Self {
    Self {
      coefs
    }
  }

  pub fn degree(self: &Self) -> usize {
    self.coefs.len()
  }

  pub fn get_polynomial_of_coefs(self: &Self, start_coef: usize, end_coef: usize) -> Self {
    Self {
      coefs: self.coefs[start_coef..end_coef].iter().map(|x| *x).collect()
    }
  }

  pub fn get_random_polynomial(degree: usize) -> Self {
    Self {
      coefs: (0..degree).map(|_| rand::random::<i8>() as i32).collect()
    }
  }
}

impl Add for &Polynomial {
  type Output=Polynomial;
  fn add(self, other: Self) -> Self::Output{
    let mut answer_coefs = vec![0;max(self.degree(), other.degree())];

    for i in 0..answer_coefs.len(){
      answer_coefs[i] = *self.coefs.get(i).unwrap_or(&0) + *other.coefs.get(i).unwrap_or(&0);
    }

    while answer_coefs.len() > 1 && *answer_coefs.last().unwrap() == 0 {
      answer_coefs.pop();
    }

    return Self::Output::new_from_coefs(answer_coefs);
  }
}

impl Neg for &Polynomial {
  type Output=Polynomial;
  fn neg(self) -> Self::Output {
    let mut answer_coefs = vec![0;self.degree()];

    for i in 0..answer_coefs.len(){
      answer_coefs[i] = -*self.coefs.get(i).unwrap();
    }
    return Self::Output::new_from_coefs(answer_coefs);
  }
}

fn compute_mult_coef(coef: usize, p1: Arc<Polynomial>, p2: Arc<Polynomial>) -> i32 {
  let start_p1_coef = if coef < p2.degree() {0} else {coef - p2.degree() + 1};
  let end_p1_coef = min(p1.degree(), coef + 1);

  (start_p1_coef..end_p1_coef).map(|i| p1.coefs[i] * p2.coefs[coef - i]).sum()
}

fn classical_mult(p1: Arc<Polynomial>, p2: Arc<Polynomial>) -> Polynomial {
  let mut coefs: Vec<i32> = (0..p1.degree() + p2.degree() - 1)
    .into_par_iter()
    .map(|i| compute_mult_coef(i, p1.clone(), p2.clone()))
    .collect();

  while coefs.len() > 1 && *coefs.last().unwrap() == 0 {
    coefs.pop();
  }

  Polynomial::new_from_coefs(coefs)
}

fn karatsuba_mult(
  p: Arc<Polynomial>, 
  q: Arc<Polynomial>,
) -> Polynomial {
  if p.degree() == 0 || q.degree() == 0{
    return Polynomial::new_from_coefs(vec![0]);
  }

  if p.degree() == 1 && q.degree() == 1 {
    return Polynomial::new_from_coefs(vec![p.coefs[0] * q.coefs[0]]);
  }

  let current_n = max(p.degree(), q.degree()) / 2;

  let p1 = Arc::new(p.get_polynomial_of_coefs(current_n, p.degree()));
  let p2 = Arc::new(p.get_polynomial_of_coefs(0, current_n));
  
  let q1 = Arc::new(q.get_polynomial_of_coefs(current_n, q.degree()));
  let q2 = Arc::new(q.get_polynomial_of_coefs(0, current_n));

  let (low_part, high_part, sum_part) = join!(
    || karatsuba_mult(p2.clone(), q2.clone()),
    || karatsuba_mult(p1.clone(), q1.clone()),
    || {
      let sum_p = Arc::new(p1.as_ref() + p2.as_ref());
      let sum_q = Arc::new(q1.as_ref() + q2.as_ref());
      karatsuba_mult(sum_p, sum_q)
    }
  );

  let mut coefs = vec![0; p.degree() + q.degree() - 1];

  for i in 0..low_part.degree() {
    if low_part.coefs[i] == 0 {
      continue;
    }
    coefs[i] += low_part.coefs[i];
  }

  for i in 0..high_part.degree() {
    if high_part.coefs[i] == 0 {
      continue;
    }
    coefs[i + 2 * current_n] += high_part.coefs[i];
  }

  let mid_part = &sum_part + &(-&low_part);
  let mid_part = &mid_part + &(-&high_part);
  for i in 0..mid_part.degree() {
    if mid_part.coefs[i] == 0 {
      continue;
    }
    coefs[i + current_n] += mid_part.coefs[i];
  }

  while coefs.len() > 1 && *coefs.last().unwrap() == 0 {
    coefs.pop();
  }

  return Polynomial::new_from_coefs(coefs);
}

fn run_method_with_rt(
  p: Arc<Polynomial>, 
  q: Arc<Polynomial>,
  multiplier: fn(Arc<Polynomial>, Arc<Polynomial>) -> Polynomial,
  pool: &mut ThreadPool,
  multiplier_name: &'static str,
  runtime_name: &'static str,
  ) -> Polynomial{
  
  let start = Instant::now();
  let result = pool.install(|| multiplier(p, q));
  
  println!("Running {multiplier_name} with {runtime_name} took {:?}", Instant::now() - start);

  return result;
}

fn main() {
  let mut args = std::env::args();

  if args.len() != 4 {
    println!("Usage cargo run N M WORKERS");
    return ;
  }

  args.next();
  
  let n = args.next().unwrap().parse::<usize>().unwrap();
  let m = args.next().unwrap().parse::<usize>().unwrap();
  let workers = args.next().unwrap().parse::<usize>().unwrap();

  let mut single_thread_pool = rayon::ThreadPoolBuilder::new().num_threads(1).build().unwrap();
  let mut multi_thread_pool = rayon::ThreadPoolBuilder::new().num_threads(workers).build().unwrap();

  let p = Arc::new(Polynomial::get_random_polynomial(n));
  let q = Arc::new(Polynomial::get_random_polynomial(m));
  let mut answers = Vec::new();
  answers.push(run_method_with_rt(p.clone(), q.clone(), classical_mult, &mut single_thread_pool, "Classical multiplication", "single threaded runtime"));
  answers.push(run_method_with_rt(p.clone(), q.clone(), classical_mult, &mut multi_thread_pool, "Classical multiplication", "multi threaded runtime"));
  answers.push(run_method_with_rt(p.clone(), q.clone(), karatsuba_mult, &mut single_thread_pool, "Karatsuba multiplication", "single threaded runtime"));
  answers.push(run_method_with_rt(p.clone(), q.clone(), karatsuba_mult, &mut multi_thread_pool, "Karatsuba multiplication", "multi threaded runtime"));

  for i in 0..answers.len() - 1 {
    if answers[i] != answers[i + 1] { 
      panic!("Sanity check failed");
    }
  }
}
