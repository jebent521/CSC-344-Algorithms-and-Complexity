# Exercise Set 5
## 5.1: Grouping Anagrams
![Output](./Anagrams/Screenshot%202024-10-24%20222526.png)

## 5.2: Comparing Hash Methods
> When is open addressing preferred over chaining with regard to
> collision resolution? What about vice-versa?
>
> You may use ChatGPT to help with this. If you do, read over the
> output, confirm that it is (most likely) correct by corroborating
> its output with what you find on google.  Then, write a brief
> summary of what you found in your own words.  Lastly, find a
> specific instance or application in the “real-world” where
> open-addressing is better than chaining, and vice versa.

**Open addressing** is preferred over chaining when memory
efficiency and speed of access are crucial, since the data is stored
directly in the table, as opposed to being encapsulated in 
linked-list nodes referenced by pointers.
- An example would be in **solid-state drives** (SSD's), where memory
  efficiency and speed of access are very important. Open addressing
  is used here to maximize performance and minimize additional memory
  usage.

**Chaining** is preferred over open addressing when there is a high 
load factor, frequent collisions, and when the datatset grows
unpredictably. Rehashing is a lot simpler of a process when using
separate chaining. You don't have to worry about "tombstone" markers
caused as you would with open addressing. Insertion is constant-time,
and searching and deleting are $O(n)$ time. It's also much simpler to
implement than open addressing.
- An example would be **managing user sessions** on high-traffic
  web servers. They frequently need to scale up or down at 
  unpredictable intervals, depending on how much traffic is happening
  at once. The time complexity of chaining increases linearly with 
  the load factor, even as it approaches 100%, whereas open 
  addressing grows exponentially as it appreaches 100%.
- Another example would be finding anagrams in a list of strings, in 
  which collisions are meaningful.

## 5.3:  What Are Hash Tables Used For IRL?
> Use ChatGPT or any other resource you like to research 7 
> real-world use cases for hash tables.  Write a short paragraph in 
> your own words detailing how each works.  Make sure that you 
> understand every word you write down (look up words you don’t 
> know).

1. **Database Indexing**: Databases hash primary keys and ID's of 
   entries so that when a user makes a query by ID or primary key,
   the database can make a constant-time lookup. On insertion, the
   database hashes the ID and inserts the entry accordingly. On 
   searching and deletion, the database finds the entry based on the 
   result of the hash function.
2. **Caching**: When a computer saves something for quick access 
   (i.e. caches it in memory), it will make a hash of that object
   so that it can make a constant-time lookup when it needs it. Items
   that might be cached include images, scripts, and URLs.
3. **Symbol Table in Compilers/Interpreters**: When a compiler or 
   interpreter reads a program, it saves all the symbols (variable,
   function, class, etc. definitions) into a hash table, where the
   hash function's input is the symbol's name. The data stored in the
   table is other important data about the symbol, such as its type
   and scope. Using a hash table allows for constant-time lookup of
   symbols at compile time.
4. **Routers**: Routers use hash tables to speed up networks by 
   hashing their connections for constant-time lookups of destination
   IP addresses. This method avoids having to iteratively search 
   through the route table, which would slow down networks.
5. **DNS Resolution**: Similarly to the previous example, hash tables
   are used to associate domain names to their IP addresses. They do 
   so by computing an entry's location based on its domain name. When
   the table is queried to resolve a name to its IP address, it 
   hashes the requested name and returns the IP address stored at 
   that location.
6. **Load Balancing**: Load balancers hash users' session ID's to 
   quickly and assign them to their corresponding servers. As 
   requests come in, the load balancer routes them to the proper 
   server such that the same session ID always maps to the same 
   server.
7. **Content Addressable Storage Systems**: CAS's store data at 
   locations based on the output of thier hashes (they're 
   essentially big hash tables). This allows for quick lookup based
   on their content.