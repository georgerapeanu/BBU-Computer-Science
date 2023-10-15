use std::sync::{Arc, Mutex, MutexGuard};
use std::collections::HashMap;
use std::sync::atomic::{AtomicU32, Ordering};
use std::time::Duration;
use std::thread::{self, JoinHandle};

// having from and to be option allows for minting and burning money
#[derive(Clone)]
pub struct TransferLog {
  pub id: u32,
  pub from: Option<usize>,
  pub to: Option<usize>,
  pub amount: u32,
}

impl TransferLog {
  pub fn new(from: Option<usize>, to: Option<usize>, amount: u32) -> Self {
    static NEXT_ID: AtomicU32 = AtomicU32::new(0);
    let id = NEXT_ID.fetch_add(1, Ordering::Relaxed);
    Self {
      id,
      from,
      to,
      amount
    }
  }
}

pub struct Account {
  pub balance: u32,
  pub logs: HashMap<u32, TransferLog>,
}

impl Account {
  pub fn new(initial_balance: u32) -> Self {
    Self {
      balance: initial_balance,
      logs: HashMap::new()
    }
  }
}

pub struct AccountWithId {
  pub id: usize,
  pub account: Mutex<Account>
}

impl AccountWithId {
  pub fn new(id: usize, account: Mutex<Account>) -> Self {
    Self {
      id,
      account
    }
  }
}

pub struct LockedAccount<'a> {
  pub id: usize,
  pub account: MutexGuard<'a, Account>
}

impl<'a> LockedAccount<'a> {
  pub fn new(account: &'a AccountWithId) -> Self {
    Self{
      id: account.id,
      account: account.account.lock().unwrap()
    }
  }
}

pub fn lock_multiple_accounts<'a>(accounts: Vec<&'a AccountWithId>) -> Vec<LockedAccount<'a>> {
  let mut order = (0..accounts.len()).collect::<Vec<usize>>();
  order.sort_by(
      |x, y| {
        accounts[*x].id.cmp(&accounts[*y].id)
    });

  let mut locked_accounts: Vec<Option<LockedAccount<'a>>> = Vec::new();

  for _ in 0..accounts.len() {
    locked_accounts.push(None);
  }

  order.into_iter()
    .for_each(|idx| {
      locked_accounts[idx] = Some(LockedAccount::new(accounts[idx]))
  });

  locked_accounts
    .into_iter()
    .map(Option::unwrap)
    .collect()
}

pub fn transfer(a: &AccountWithId, b: &AccountWithId, amount: u32) {
  if a.id == b.id {
    return ;
  }
  
  let mut guards = lock_multiple_accounts(vec![a, b]);
  
  if guards[0].account.balance < amount {
    return 
  }
  
  guards[0].account.balance -= amount;
  guards[1].account.balance += amount;

  let log = TransferLog::new(Some(a.id), Some(b.id), amount);
  guards[0].account.logs.insert(log.id, log.clone());
  guards[1].account.logs.insert(log.id, log);
}

pub fn mint(a: &AccountWithId, amount: u32) {
  let mut guards = lock_multiple_accounts(vec![a]);

  guards[0].account.balance += amount;
  let log = TransferLog::new(None, Some(a.id), amount);
  guards[0].account.logs.insert(log.id, log);
}

pub fn sanity_check(accounts: Arc<Vec<AccountWithId> >) {
  let mut account_refs: Vec<&AccountWithId> = Vec::new();

  for elem in accounts.iter() {
    account_refs.push(&elem);
  }
  
  let guards = lock_multiple_accounts(account_refs);
  
  for i in 0..guards.len() {
    let mut balance = 0;
    let mut keys = guards[i].account.logs.keys().map(|x| *x).collect::<Vec<u32>>();
    keys.sort();
    for pos in keys {
      let id = pos;
      let log = guards[i].account.logs.get(&pos).unwrap();
      if let Some(from) = log.from {
        if from == guards[i].id {
          assert!(balance >= log.amount, "Error: Transaction with amount greater than balance succeded");
          balance -= log.amount;
          if let Some(to) = log.to {
            assert!(guards[to].account.logs.contains_key(&id), "Error: Receiver of transaction doesn't contain log");
          }
        }
      }

      if let Some(to) = log.to {
        if to == guards[i].id {
          balance += log.amount;
          if let Some(from) = log.from {
            assert!(guards[from].account.logs.contains_key(&id), "Error: Sender of transaction doesn't contain log");
          }
        }
      }
    }
    assert!(balance == guards[i].account.balance, "Error: Sanity checked balance differs from actual balance");
  }

  println!("Sanity check passed!");
}

fn main() {
  let mut args = std::env::args();

  if args.len() != 4 {
    println!("Usage: cargo run ACCOUNTS TRANSFERS_PER_THREAD THREADS");
    return;
  }

  args.next();
  let account_number = args.next().unwrap().parse::<usize>().expect("Invalid ACCOUNTS number");
  let transfers_per_thread = args.next().unwrap().parse::<usize>().expect("Invalid TRANSFERS_PER_THREAD number");
  let threads = args.next().unwrap().parse::<usize>().expect("Invalid THREADS number");

  assert!(account_number > 1, "There should be at least 2 accounts");

  let accounts: Vec<AccountWithId> = (0..account_number).map(|i| AccountWithId::new(i, Mutex::new(Account::new(0)))).collect();

  accounts.iter().for_each(|x| mint(&x, rand::random::<u32>() / (account_number as u32)));
  
  let accounts_arc = Arc::new(accounts);

  let mut handles: Vec<JoinHandle<()>> = Vec::new();

  for _ in 0..threads {
    let local_arc = accounts_arc.clone();
    handles.push(thread::spawn(move || {
      for _ in 0..transfers_per_thread {
        let first_account: &AccountWithId = &local_arc[rand::random::<usize>() % local_arc.len()]; 
        let second_account: &AccountWithId = &local_arc[rand::random::<usize>() % local_arc.len()]; 
        let amount = rand::random::<u16>() as u32;

        transfer(first_account, second_account, amount);
      }
    }));
  }

  handles.push(thread::spawn(move || {
    thread::sleep(Duration::from_secs(1));
    sanity_check(accounts_arc.clone());
  }));

  for handle in handles.into_iter() {
    let _ = handle.join();
  }
}
