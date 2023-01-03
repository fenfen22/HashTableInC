#include <math.h>
#include "prime.h"

/*
we increase the size of the hash table when it goes too full. each insert and delete operation, 
we could caculate the table's load. if it gets higher or lower than certain values, we resize the bucket up or down.

up, if load > 0.7
down, if load < 0.7

we create a new hash table roughly half or twice as big as the current, and insert all non-deleted items into it.

the new array size should be a prime number.

we store a base size, and define the actual size as the first prime larger than the base size.

to size up, we doulbe the base size, and find the first larger prime;
to size down, we halve the base size, and find the next larger prime.

we use a brute-force method to find the next prime.
*/


/*
return whether x is prime or not
1 prime
0 not prime
-1 undefined (x < 2)
*/
int is_prime(const int x){
    if (x < 2)
    return -1;
    if(x < 4)
    return 1;
    if((x % 2) == 0)
    return 0;
    for(int i = 3; i <= floor(sqrt((double)x)); i += 2){
        if((x % i) == 0)
        return 0;
    }
    return 1;
}

//return the next prime after x, or x if x is prime
int next_prime(int x){
    while (is_prime(x) != 1){
        x++;
    }
    return x;
}