### Rust implementation of a symbol table

This is a rust implementation of a symbol table. It is implemented using double hashing.

Functons `hash1`, `hash2`, and `hash_at_pos` are internal and are used in order to be able to determine the place where a value might be inserted.

Function `internal_insert` is to be called internally, and receives a (key, value) item. It checks the hash for space, and if there is none, it rehashes everything using another helper function `rehash`, and then proceeds with probing in order to determine where to insert the current (key, value) pair.

Function `insert` is used to insert a new symbol in the symbol table. An id is automatically assigned to it.

Function `get` returns an optional, which is either `Some(id)` if the symbol exists in the table, or `None` if it doesn't.

#### Example of usage
![./example.png]()
