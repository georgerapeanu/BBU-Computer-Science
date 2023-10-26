
// Double hashing open addressing
struct SymbolTable {
  hash: Vec<Option<(String, usize)>>,
  __size: usize
}

impl SymbolTable {
  pub fn new(capacity: Option<usize>) -> Self {
    let cap = match capacity {
      None => 8,
      Some(c) => c
    };
    Self{
      hash: vec![None; cap],
      __size: 0
    }
  }

  pub fn hash1(self: &Self, key: &String) -> usize {
    key.chars().map(|x| (x as usize)).reduce(|x, y| (((x as u64) * 31 + (y as u64)) % (self.hash.len() as u64)) as usize).unwrap()
  }
  
  pub fn hash2(self: &Self, key: &String) -> usize {
    (2 * key.chars().map(|x| (x as usize)).reduce(|x, y| (((x as u64) * 49 + (y as u64)) % (self.hash.len() as u64)) as usize).unwrap() + 1) % self.hash.len()
  }

  pub fn hash_at_pos(self: &Self, key: &String, pos: usize) -> usize {
    (((self.hash1(key) as u64) + (self.hash2(key) as u64) * (pos as u64)) % (self.hash.len() as u64)) as usize
  }

  fn internal_insert(self: &mut Self, item: (String, usize)) {
    if self.hash.len() == self.__size {
      self.rehash();
    }
    let mut pos = 0;

    loop {
      let hash_pos = self.hash_at_pos(&item.0, pos);
      if self.hash[hash_pos] == None {
        self.hash[hash_pos] = Some(item);
        self.__size += 1;
        break;
      }
      pos += 1;
    }
  }

  fn rehash(self: &mut Self) {
    let mut new_st = SymbolTable::new(Some(self.hash.len() * 2));

    self.hash.iter().for_each(|x| new_st.internal_insert(x.clone().unwrap()));
    self.hash = new_st.hash;
  }

  pub fn insert(self: &mut Self, key: String) {
    self.internal_insert((key, self.__size));
  }

  pub fn get(self: & Self, key: String) -> Option<usize> {
    let mut pos = 0;

    loop {
      let hash_pos = self.hash_at_pos(&key, pos);
      if self.hash[hash_pos] == None {
        return None
      } else if let Some(current_item) = &self.hash[hash_pos] {
        if current_item.0 == key {
          return Some(current_item.1); 
        }
      }
      pos += 1;
    }    
  }
}



fn main() {
    let mut st = SymbolTable::new(None);

    st.insert("a".into());
    st.insert("b".into());
    st.insert("d".into());
    st.insert("c".into());
    st.insert("1".into());

    println!("{:?}", st.get("a".into()));
    println!("{:?}", st.get("b".into()));
    println!("{:?}", st.get("c".into()));
    println!("{:?}", st.get("d".into()));
    println!("{:?}", st.get("e".into()));
    println!("{:?}", st.get("1".into()));
}
