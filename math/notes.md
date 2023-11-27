## GCD SUM of pairs from 1 to n
a lemma: if d is  a divisor of i then phi(i/d) numbers less than i where their gcd is divisor
### PROOF: 
Proof: We can see an example which certainly generalizes. Say, n=12 and we want to compute the number of numbers i <= 12 so that gcd(i,12)=3. Let's do it by hand first. These i are 3,9. Now, we compute it by logic.

First off, any such i must be divisible by 3. So, assume i=3j. Then gcd(12,3j)=3*gcd(j,4). Now, if gcd(4,j) is greater than 1, then our desired gcd will be greater than 3. Therefore, we must have gcd(4,j)=1. How many such j are there? Phi(4). So, the number of such i is the number of such j, i.e. Phi(4)=Phi(12/3). You can check it with other examples. And generally, it follows that for a divisor d, we would have such Phi(n/d) numbers.