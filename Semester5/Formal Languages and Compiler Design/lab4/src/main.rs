use std::fs;
use std::env;
use std::fmt::Display;

use finite_automaton::FiniteAutomaton;
use symbol_table::SymbolTable;

pub mod finite_automaton;
pub mod symbol_table;

pub fn print_usage() {
    println!("Usage: cargo run TOKENS.IN PROGRAM.CRS");
    println!("Alternative usage: cargo run describe automaton");
}

#[derive(Debug)]
enum PIFEntry {
  Reserved(usize),
  Identifier(usize),
  Constant(usize)
}

pub fn main() {

  let mut args = env::args();

  if args.len() == 1 {
    println!("Usage: cargo run TOKENS.IN PROGRAM.CRS");
    print_usage();  
    return ;
  }
  
  let fa = FiniteAutomaton::new("FA.in".to_string());

  args.next();

  let first_arg = args.next().unwrap();

  if first_arg == "describe" {
    let to_describe = args.next();
    if to_describe.is_none() {
      print_usage();  
    }
    match to_describe.unwrap().as_str() {
      "automaton" => {dbg!(fa);},
      _ => print_usage()
    }
    return ;
  } 

  let mut reserved_tokens_vector: Vec<String> = fs::read_to_string(first_arg).unwrap().split('\n')
    .map(|x| x.trim().to_string())
    .filter(|x| x.len() > 0)
    .collect(); 

  reserved_tokens_vector.push("\n".to_string());
  reserved_tokens_vector.push(" ".to_string());

  let mut st = SymbolTable::new(None);
  let mut pif: Vec<(String, PIFEntry)> = Vec::new();

  let separators = vec!["+","-","*","/","%","=","!","<",">","!","&","|","{","}","(",")",";","'","\"",":",".",","," ","[","]", "==", "<=", ">=", "!="];

  let mut token_number = 0;
  let program: String = fs::read_to_string(args.next().unwrap()).unwrap()
    .split("\n")
    .map(|x| x.trim())
    .map(|x| x[0..x.find("//").unwrap_or(x.len())].to_string())
    .filter(|x| x.len() > 0)
    .map(|x| x.to_string())
    .reduce(|x, y| x + &y)
    .unwrap();

  println!("Program: {program}");


  let mut index = 0;
  while index < program.len() {
    while index < program.len() && program[index..index + 1].starts_with(" ") {
      index += 1;
    }
    if index >= program.len() {
      break;
    }

    token_number += 1;
    // Match reserved tokens
    let mut found = false;
    let mut current_token = 0;
    for token in reserved_tokens_vector.iter() {
      if index + token.len() <= program.len() && (&program[index..index + token.len()] == token.as_str()) {
        if separators.contains(&token.as_str()) {
          pif.push((token.clone(), PIFEntry::Reserved(current_token)));
          index += token.len();
          found = true;
          break;
        }
        if index + token.len() == program.len() || separators.contains(&&program[index + token.len()..=index + token.len()]) {
          pif.push((token.clone(), PIFEntry::Reserved(current_token)));
          index += token.len();
          found = true;
          break;
        }
      }
      current_token += 1;
    }

    if found {
      continue;
    }
    let token = fa.get_next_accepted(&program[index..program.len()]).expect(format!("Lexical error for token number {token_number}").as_str()).to_string();
    if !(program.len() == index + token.len() || separators.contains(&&program[index + token.len()..=index + token.len()])) {
      panic!("Lexical error for token number {token_number}");
    }

    index += token.len();
    if st.get(token.clone()).is_none() {
      st.insert(token.clone());
    }
    
    let id = st.get(token.clone());
    if (token.bytes().next().unwrap() >= b'0' && token.bytes().next().unwrap() <= b'9') || token.bytes().next().unwrap() == b'"' || token.bytes().next().unwrap() == b'[' {
      pif.push((token, PIFEntry::Constant(id.unwrap())));
    } else {
      pif.push((token, PIFEntry::Identifier(id.unwrap())));
    }
  };

  println!("PIF.out");
  pif.iter().for_each(|x| println!("{}: {:?}", x.0, x.1));
  
  println!("ST.out");
  st.iter().for_each(|x| println!("{}: {}", x.0, x.1))
}
