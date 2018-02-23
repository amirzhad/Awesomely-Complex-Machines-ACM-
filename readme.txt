Here I explain a bit about the solotion of this problem.

In order to solve this problem, I first analyzed how a human can solve it.
I wrote 2 algorithms to solve it:

In the first algorithm:
First I compute the possible profit that a machine can produce at the end of the restruction D.
then I choose the machine which makes the most profit.
after that I chose the primary machine, I continue computing the profit of the other machines with this consideration that we
  chose current machine
and this process continues till the end of the restruction.
I thought that this method will be the best, fast and reliable. Actually, it worked for some situations, however I found a lot of
  conditions that the method computes wrongly. I tried to consider these situations but further I go, more unseen situations happens.
  
Hence, I wrote te second code.
In the second algorithm:
I covered all the possible states. This method works fine, yet takes time if the input is large. In order to make the method better,
  we need an appropriate pruning. To consider all the states, we say a machine can be chose or not. So, each machine has two states and
  if we have N machines, the number of states would be 2^N (which will be large for big N). These states will make a tree as:
                          machine1
                              x
                choose                not_choose
               machine2                machine2
                  x                        x
           choose   not_choose      choose   not_choose
                ...                       ...
                the branches(number of posible states) will be 2^N
                
I did some pruning to reduce the number of states such as deleting the machines which cost more than the budget the company has.
For the code part, I used a recursive function which calls himself 2 times and returns the max value of them. The first one assume
we chose the machine and the second one assume we did not choose the machine. At the end, the max value between choosing and not choosing 
the current machine is the answer of interest.
