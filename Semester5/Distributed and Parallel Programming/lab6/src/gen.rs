use rand::prelude::*;

fn generate_graph(n: usize, m: usize) -> Vec<Vec<usize>> {
  let mut cycle: Vec<usize> = (0..n).collect();
  cycle.shuffle(&mut thread_rng());
  let mut graph = vec![Vec::new(); n];

  for i in 0..n { 
    let j = (i + 1) % n;
    graph[cycle[i]].push(cycle[j]);
  }

  for _ in n..m {
    let (x, y) = 
      loop {
        let nodes = (0..n).choose_multiple(&mut thread_rng(), 2); 
        if !graph[nodes[0]].contains(&nodes[1]) {
          break (nodes[0], nodes[1]);
        }
      }
    ;
    graph[x].push(y);
  }

  for i in 0..n {
    graph[i].reverse();
  }

  graph
}

fn main() {
  let mut args = std::env::args();

  if args.len() != 3 {
    println!("Usage cargo run N M");
    return ;
  }

  args.next();
  let n = args.next().unwrap().parse::<usize>().unwrap();
  let m = args.next().unwrap().parse::<usize>().unwrap();
  let graph = generate_graph(n, m);

  println!("{n} {m}");
  for from in 0..graph.len() {
    for to in graph[from].iter() {
      println!("{from} {to}");
    }
  }
}
