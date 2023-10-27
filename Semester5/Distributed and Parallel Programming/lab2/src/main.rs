use std::sync::{Arc, Mutex, Condvar, atomic::AtomicUsize};
use std::thread;
use std::time::Instant;

struct FixedSizeQueue {
  size: usize,
  head: usize,
  elements: Vec<i64>
}

impl FixedSizeQueue {
  pub fn new(capacity: usize) -> Self {
    Self {
      size: 0,
      head: 0,
      elements: vec![0; capacity]
    }
  }

  pub fn push(self: &mut Self, element: i64) -> bool {
    let capacity = self.elements.len();

    if self.size == capacity { 
       return false;
    }

    self.elements[(self.head + self.size) % capacity] = element;
    self.size += 1;

    return true;
  }

  pub fn pop(self: &mut Self) -> Option<i64> {
    if self.size == 0 {
      return None;
    }
    
    let element = self.elements[self.head];

    self.size -= 1;
    self.head = (self.head + 1) % self.elements.len();

    return Some(element);
  }
}

//The task queue
struct TaskQueue {
  queue: Mutex<FixedSizeQueue>,
  producer_cond_var: Condvar,
  consumer_cond_var: Condvar,
  producers: AtomicUsize,
  consumers: AtomicUsize
}

impl TaskQueue {
  pub fn new(capacity: usize) -> Self {
    Self {
      queue: Mutex::new(FixedSizeQueue::new(capacity)),
      producer_cond_var: Condvar::new(),
      consumer_cond_var: Condvar::new(),
      producers: AtomicUsize::from(0),
      consumers: AtomicUsize::from(0)
    }
  }
}

// ProducerTaskQueue, corresponding to the producer thread
struct ProducerTaskQueue {
  task_queue: Arc<TaskQueue>
}

impl ProducerTaskQueue {
  pub fn new(task_queue: Arc<TaskQueue>) -> Self {
    task_queue.producers.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
    Self {
      task_queue
    }
  }

  // push function, that attempts to push an element to the queue. 
  // If queue is full, it waits
  // If no consumers are present on the queue after an unsucesfull push, it panics
  pub fn push(self: &mut Self, element: i64) {
    let mut lock = self.task_queue.queue.lock().unwrap();
    
    while !lock.push(element) {
      assert!(self.task_queue.consumers.load(std::sync::atomic::Ordering::Acquire) > 0, "No consumers are there to read a full queue");
      lock = self.task_queue.producer_cond_var.wait(lock).unwrap();
    }
    self.task_queue.consumer_cond_var.notify_one();
  }
}

impl Drop for ProducerTaskQueue {
  fn drop(self: &mut Self) {
    self.task_queue.producers.fetch_sub(1, std::sync::atomic::Ordering::Acquire);
    self.task_queue.consumer_cond_var.notify_all();
  }
}

// ConsumerTaskQueue, corresponding to the consumer thread
struct ConsumerTaskQueue {
  task_queue: Arc<TaskQueue>
}

impl ConsumerTaskQueue {
  pub fn new(task_queue: Arc<TaskQueue>) -> Self {
    task_queue.consumers.fetch_add(1, std::sync::atomic::Ordering::Relaxed);
    Self {
      task_queue
    }
  }

  // push function, that retrieves an element of the queue and returns it as a Some type
  // If queue is empty, it waits
  // If no producers are present on the queue after an unsucesfull pop, it returns None 
  pub fn pop(self: &mut Self) -> Option<i64>{
    let mut lock = self.task_queue.queue.lock().unwrap();

    let element = loop{
      let element = lock.pop();
      if element != None {
        break element;
      }
      if self.task_queue.producers.load(std::sync::atomic::Ordering::Acquire) == 0 {
        break element;
      }
      lock = self.task_queue.consumer_cond_var.wait(lock).unwrap();
    };
    self.task_queue.producer_cond_var.notify_one();
    return element;
  }
}

impl Drop for ConsumerTaskQueue {
  fn drop(self: &mut Self) {
    self.task_queue.consumers.fetch_sub(1, std::sync::atomic::Ordering::Acquire);
    self.task_queue.producer_cond_var.notify_all();
  }
}

pub fn generate_vector(size: usize) -> Vec<i16> {
  (0..size).map(|_| rand::random::<i16>()).collect()
}

fn main() {
  let mut args = std::env::args();

  if args.len() != 3 {
    println!("Usage: cargo run ELEMENNTS_IN_VECTOR QUEUE_CAPACITY");
    return;
  }

  args.next();
  let elements_in_vector = args.next().unwrap().parse::<usize>().expect("Invalid ELEMENTS_IN_VECTOR number");
  let queue_capacity = args.next().unwrap().parse::<usize>().expect("Invalid QUEUE_CAPACITY number");


  let a = generate_vector(elements_in_vector);
  let b = generate_vector(elements_in_vector);

  let before_sanity_check_instant = Instant::now();
  let sanity_check_sum: i64 = (0..elements_in_vector).map(|i| (a[i] as i64) * (b[i] as i64)).sum();
  let sanity_check_duration = before_sanity_check_instant.elapsed();

  let task_queue = Arc::new(TaskQueue::new(queue_capacity));
  let mut producer_queue = ProducerTaskQueue::new(task_queue.clone());
  let mut consumer_queue = ConsumerTaskQueue::new(task_queue.clone());

  let before_threads_instant = Instant::now();

  let producer_handle = thread::spawn(move || {
    for i in 0..elements_in_vector {
      producer_queue.push((a[i] as i64) * (b[i] as i64));
    }
  });
  
  let consumer_handle = thread::spawn(move || {
    let mut sum: i64 = 0;

    loop {
      let element = consumer_queue.pop();

      if element == None {
        break;
      }

      sum += element.unwrap();
    }

    return sum;
  });

  let _ = producer_handle.join();
  let sum = consumer_handle.join().unwrap();
  
  let threads_duration = before_threads_instant.elapsed();

  println!("Sum given by threads is {sum}; Time taken {threads_duration:?}");
  println!("Sanity check sum is {sanity_check_sum}; Time taken {sanity_check_duration:?}");
}
