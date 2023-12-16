use std::{sync::{Arc, atomic::{AtomicBool, self}, Mutex}, io};
use rayon::prelude::*;

fn solve(graph: &Vec<Vec<usize>>, current_prefix: &mut Vec<usize>, max_depth: usize, found: Arc<AtomicBool>, answer: Arc<Mutex<Vec<usize>>> ) {
  if found.load(atomic::Ordering::SeqCst) {
    return;
  }
  
  if current_prefix.len() == graph.len() {
    if graph[*current_prefix.last().unwrap()].contains(&current_prefix[0]) {
      found.store(true, atomic::Ordering::SeqCst);
      *answer.lock().unwrap() = current_prefix.clone();
      println!("Found, other threads should stop soon");
    }
    return ;
  }
  
  if current_prefix.len() <= max_depth {
    graph[*current_prefix.last().unwrap()].par_iter()
    .filter(|x| !current_prefix.contains(x))
    .for_each(|neighbor| {
      let mut prefix = current_prefix.clone();
      prefix.push(*neighbor);
      solve(graph, &mut prefix, max_depth, found.clone(), answer.clone());
    })
  } else {
    for neighbor in graph[*current_prefix.last().unwrap()].iter() {
      if !current_prefix.contains(neighbor) {
        current_prefix.push(*neighbor);
        solve(graph, current_prefix, max_depth, found.clone(), answer.clone());
        current_prefix.pop();
      }
    }
  }
}

fn main() {
  let mut args = std::env::args();

  if args.len() != 3 {
    println!("Usage cargo run MAX_DEPTH WORKERS");
    return ;
  }

  args.next();
  let max_depth = args.next().unwrap().parse::<usize>().unwrap();
  let workers = args.next().unwrap().parse::<usize>().unwrap();
  let pool = rayon::ThreadPoolBuilder::new().num_threads(workers).build().unwrap();

  let input_lines = io::stdin()
    .lines()
    .map(|x| 
         x.expect("Input error")
          .split(" ")
          .map(|x| x.parse::<usize>().expect("Input error"))
          .collect()
  ).collect::<Vec<Vec<usize>>>();
  let (n, m) = (input_lines[0][0], input_lines[0][1]);
  let mut graph = vec![Vec::new(); n];
  for i in 1..=m { 
    let from = input_lines[i][0];
    let to = input_lines[i][1];
    graph[from].push(to);
  }

  pool.install(|| {
    let mut prefix = vec![0];
    let answer = Arc::new(Mutex::new(Vec::new()));
    let found = Arc::new(AtomicBool::new(false));
    solve(&graph, &mut prefix, max_depth, found.clone(), answer.clone());
    if found.load(atomic::Ordering::SeqCst) {
      print!("Found hamiltonian cycle ");
      for elem in answer.lock().unwrap().iter() {
        print!("{} ", *elem);
      }
      println!("");
    } else {
      println!("No hamiltonian cycle found");
    }
  });

}
