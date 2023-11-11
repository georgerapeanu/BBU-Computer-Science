use std::{collections::{HashMap, HashSet}, fs::read_to_string};
use std::fmt::Debug;

#[derive(Debug)]
pub struct FiniteAutomaton {
  transitions: HashMap<(String, u8), String>,
  initial_state: String,
  final_states: HashSet<String>
}

impl FiniteAutomaton {
  pub fn new(file: String) -> Self {
    let file_as_string = read_to_string(file).expect("File error occurred");
    let mut lines = file_as_string
      .lines()
      .map(String::from)
      .map(|x| x.trim().to_string())
      .filter(|x| !x.is_empty());

    let initial_state = lines.next().expect("Initial state expected").to_string();
    let final_states = HashSet::from_iter(
      lines.next().expect("Final states expected").split(' ').map(String::from)
    );

    let mut transitions: HashMap<(String, u8), String > = HashMap::new();

    lines.for_each( |line| {
      let (from, mut rest) = line.split_once(" ").expect("Invalid input");
      let rest_optional = rest.split_once(" ");
      let to;

      if rest_optional.is_none() {
        to = rest;
        rest = "";
      } else {
        (to, rest) = rest_optional.unwrap();
      }

      rest = rest.trim_end_matches("\n");
      let bytes: Vec<u8> = if !rest.is_empty() {
        rest.bytes().collect()
      } else {
        (0..=255)
          .filter(|x| !transitions.contains_key(&(from.to_string(), *x)))
          .collect()
      };
      bytes.iter()
        .for_each(|x| {
          if transitions.contains_key(&(from.to_string(), *x)) {
            panic!("FiniteAutomaton is not deterministic");
          }
          transitions.insert((from.to_string(), *x), to.to_string());
        });
    });
    
    Self {
      transitions,
      initial_state,
      final_states    
    }
  }

  pub fn get_next_accepted<'a>(self: &Self, s: &'a str) -> Option<&'a str>{
    let mut state = self.initial_state.clone();
    let mut s_bytes = s.bytes();
    let length = s_bytes.len();

    for i in 0..length {
      let current = s_bytes.next().unwrap();

      if let Some(next_state)=self.transitions.get(&(state.clone(), current)) {
        state = next_state.clone();
      } else if i != 0 && self.final_states.contains(&state){
        return Some(&s[0..i]);
      } else {
        return None;
      }
    }

    if self.final_states.contains(&state) {
      Some(s)
    } else {
      None
    }
  }

}
