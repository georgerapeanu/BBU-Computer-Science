### Goal

Create two threads, a producer and a consumer, with the producer feeding the consumer.

Requirement: Compute the scalar product of two vectors.

Create two threads. The first thread (producer) will compute the products of pairs of elements - one from each vector - and will feed the second thread. The second thread (consumer) will sum up the products computed by the first one. The two threads will behind synchronized with a condition variable and a mutex. The consumer will be cleared to use each product as soon as it is computed by the producer thread.

#### Benchmarks:

| Number of elements | Queue capacity | Single thread | Producer-Consumer threads |
| :----------------: | :------------: | :-----------: | :-----------------------: |
|        100         |        1       |      389ns    |          1.54ms           |
|        100         |       100      |      350ns    |        709.38µs           |
|       10000        |        1       |    11.95µs    |        116.88ms           |
|       10000        |       100      |    11.72µs    |         48.88ms           |
|       10000        |      10000     |    11.71µs    |         41.64ms           |
|      1000000       |        1       |     1.09ms    |          9.98s            |
|      1000000       |       100      |     1.08ms    |          4.17s            |
|      1000000       |      10000     |     1.18ms    |          4.16s            |
|      1000000       |     1000000    |     1.63ms    |          3.86s            |
