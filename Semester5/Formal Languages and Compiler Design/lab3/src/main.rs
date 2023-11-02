use std::collections::HashSet;
use std::fs;
use std::env;
use regex::Regex;

use symbol_table::SymbolTable;

pub mod symbol_table;

pub fn main() {

  let mut args = env::args();

  if args.len() != 3 {
    println!("Usage: cargo run TOKENS.IN PROGRAM.CRS");
    return ;
  }

  args.next();
  let mut reserved_tokens_vector: Vec<String> = fs::read_to_string(args.next().unwrap()).unwrap().split('\n')
    .map(|x| x.trim().to_string())
    .filter(|x| x.len() > 0)
    .collect(); 

  reserved_tokens_vector.push("\n".to_string());
  reserved_tokens_vector.push(" ".to_string());

  let mut st = SymbolTable::new(None);
  let mut pif: Vec<(String, Option<usize>)> = Vec::new();

  let separators_regex_string = "([+]|[-]|[*]|[/]|[%]|==|!=|<|<=|>|>=|=|[!]|[&][&]|[|][|]|[{]|[}]|[(]|[)]|;|,|[']|[\"]|[:]|[.]|[,]|$|[ ])";
  let int_constant_regex = Regex::new(&(r"^(0|([+-]?[1-9][0-9]*))".to_owned() + separators_regex_string)).unwrap();
  let string_constant_regex = Regex::new(&("^(\"[^\"]*\")".to_owned() + separators_regex_string)).unwrap();
  let float_constant_regex = Regex::new(&(r"^(0|([+-]?[1-9][0-9]*)([.][0-9]*)?)".to_owned() + separators_regex_string)).unwrap();
  let bool_constant_regex = Regex::new(&(r"^((true)|(false))".to_owned() + separators_regex_string)).unwrap();
  let identifier_regex = Regex::new(&(r"^(([a-zA-Z]|[_])[0-9a-zA-Z_]*)".to_owned() + separators_regex_string)).unwrap();

  let regexes = [int_constant_regex, string_constant_regex, float_constant_regex, bool_constant_regex, identifier_regex];

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
    for token in reserved_tokens_vector.iter() {
      if index + token.len() <= program.len() && (&program[index..index + token.len()] == token.as_str()) {
        pif.push((token.clone(), None));
        index += token.len();
        found = true;
        break;
      }
    }

    if found {
      continue;
    }
    
    let token: String = regexes.iter()
      .map(|re| re.captures(&program[index..program.len()]))
      .filter(|x| x.is_some())
      .map(|x| x.unwrap()[1].to_string())
      .nth(0)
      .expect(format!("Lexical error for token number {token_number} \"{}\"", &program[index..program.len()]).as_str());
    
    index += token.len();
    if st.get(token.clone()).is_none() {
      st.insert(token.clone());
    }
    
    let id = st.get(token.clone());
    pif.push((token, id));
  };

  println!("PIF.out");
  pif.iter().for_each(|x| println!("{}: {}", x.0, if x.1.is_none() {"-".to_string()} else { x.1.unwrap().to_string() }));
  
  println!("ST.out");
  st.iter().for_each(|x| println!("{}: {}", x.0, x.1))
}
