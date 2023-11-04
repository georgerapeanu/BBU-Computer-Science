use std::ops::Index;
use std::sync::Arc;
use std::sync::mpsc;
use std::thread;
use std::time::Instant;
use threadpool::ThreadPool;
use rand;

pub struct Matrix {
  pub n: usize,
  pub m: usize,
  pub elems: Vec<i64>
}

impl Index<&'_ (usize, usize)> for Matrix {
  type Output = i64;
  fn index(self: &Self, idx: &(usize, usize)) -> &Self::Output {
    &self.elems[idx.0 * self.m + idx.1]
  }
}

impl Matrix {
  pub fn new(n: usize, m: usize) -> Self {
    Self {
      n,
      m,
      elems: (0..n*m).map(|_| rand::random::<i16>() as i64).collect()
    }
  }

  pub fn unsafe_put(self: &Self, idx: (usize, usize), value: i64) {
    let cell_ref: &i64 = &self[&idx];
    unsafe {
      let const_ptr = cell_ref as *const i64;
      let mut_ptr = const_ptr as *mut i64;
      *mut_ptr = value;
    }
  }

  pub fn sum(self: &Self) -> i64 {
    self.elems.iter().sum()
  }
}

pub fn single_cell_multiply(a: Arc<Matrix>, b: Arc<Matrix>, idx: &(usize, usize)) -> i64 {
  (0..a.m).map(|i| ((a[&(idx.0, i)] as i32) * (b[&(i, idx.1)] as i32)) as i64).sum() 
}

//instead of computing a matrix, due to huge sizes, only the sum of the elements will be computed as a checksum
pub fn multiply_range(a: Arc<Matrix>, b: Arc<Matrix>, start: (usize, usize), gap: usize, count: usize, result: Arc<Matrix>) {
  let output_m = b.m;
  let mut next_cell = start;

  for _ in 0..count {
    result.unsafe_put(next_cell, single_cell_multiply(a.clone(), b.clone(), &next_cell));
    next_cell.1 += gap;
    next_cell.0 += next_cell.1 / output_m;
    next_cell.1 %= output_m;
  }
}

fn main() {
  let mut args = std::env::args();

  if args.len() != 5 {
    println!("Usage cargo run N M P WORKERS");
    return ;
  }

  args.next();
  
  let n = args.next().unwrap().parse::<usize>().unwrap();
  let m = args.next().unwrap().parse::<usize>().unwrap();
  let p = args.next().unwrap().parse::<usize>().unwrap();
  let workers = args.next().unwrap().parse::<usize>().unwrap();

  let a = Arc::new(Matrix::new(n, m));
  let b = Arc::new(Matrix::new(m, p));

  let a_clone = a.clone();
  let b_clone = b.clone();
  let multiply_rows: Box<dyn Fn(_) -> i64> = Box::new(move |executor: Arc<dyn Fn(Box<dyn Fn() + Send>)>| -> i64 {
    let result = Arc::new(Matrix::new(a_clone.n, b_clone.m));
    let (tx, rx) = mpsc::channel();

    (0..a_clone.n).for_each(|row| {
      let a_clone = a_clone.clone();
      let b_clone = b_clone.clone();
      let result = result.clone();
      let tx = tx.clone();
      executor(
        Box::new(
          move  || {
            multiply_range(a_clone.clone(), b_clone.clone(), (row, 0), 1, b_clone.m, result.clone());
            tx.send(1).expect("Send error");
          }
        )
      );
    });
 
    rx.iter().take(a_clone.n).for_each(|_| {});
    result.sum()
  });
  
  let a_clone = a.clone();
  let b_clone = b.clone();
  let multiply_columns: Box<dyn Fn(_) -> i64> = Box::new(move |executor: Arc<dyn Fn(Box<dyn Fn() + Send>)>| -> i64 {
    let result = Arc::new(Matrix::new(a_clone.n, b_clone.m));
    let (tx, rx) = mpsc::channel();

    (0..b_clone.m).for_each(|column| {
      let a_clone = a_clone.clone();
      let b_clone = b_clone.clone();
      let result = result.clone();
      let tx = tx.clone();
      executor(
        Box::new(
          move || {
            multiply_range(a_clone.clone(), b_clone.clone(), (0, column), b_clone.m, a_clone.n, result.clone());
            tx.send(1).expect("Send error");
          }
        )
      );
    });
    
    rx.iter().take(b_clone.m).for_each(|_| {});
    result.sum()
  });

  
  let a_clone = a.clone();
  let b_clone = b.clone();
  let multiply_gap: Box<dyn Fn(_) -> i64> = Box::new(move |executor: Arc<dyn Fn(Box<dyn Fn() + Send>)>| -> i64 {
    let result = Arc::new(Matrix::new(a_clone.n, b_clone.m));
    let (tx, rx) = mpsc::channel();

    (0..workers).for_each(|id| {
      let a_clone = a_clone.clone();
      let b_clone = b_clone.clone();
      let tx = tx.clone();
      let result = result.clone();
      let start_cell = (id / b_clone.m, id % b_clone.m);
      let reps = (a_clone.n * b_clone.m - 1 - id) / workers + 1;
      executor(
        Box::new(
          move || {
            multiply_range(a_clone.clone(), b_clone.clone(), start_cell, workers, reps, result.clone());
            tx.send(1).expect("Send error");
          }
        )
      );
    });
    
    rx.iter().take(workers).for_each(|_| {});
    result.sum()
  });

  let thread_spawn_executor: Arc<dyn Fn(_)> = Arc::new(|f: Box<dyn Fn() + Send>| {
    thread::spawn(f); 
  });

  let thread_pool = ThreadPool::new(workers);
  let thread_pool_executor: Arc<dyn Fn(_)> = Arc::new(move |f: Box<dyn Fn() + Send>| {
    thread_pool.execute(f);
  });

  let multiplication_configs = vec![
    ("Row by row multiplication", multiply_rows),
    ("Column by column mulitplication", multiply_columns),
    ("Multiply with gap", multiply_gap)
  ];

  let executor_configs = vec![
    ("executed with thread_spawn_executor", thread_spawn_executor),
    ("executed with thread_pool_executor", thread_pool_executor)
  ];
 
  for (multiplication_description, multiplication_method) in multiplication_configs.iter() {
    for (executor_description, executor_method) in executor_configs.iter() {
      let start = Instant::now();
      let answer = multiplication_method(executor_method.to_owned());
      let end = Instant::now();
      let message_only_description = format!("{multiplication_description} {executor_description};");
      let message_without_time = format!("{message_only_description: <70}; Sanity check answer: {answer};");
      println!("{message_without_time: <110} Time taken: {:?}", end - start);
    }
  }
}
