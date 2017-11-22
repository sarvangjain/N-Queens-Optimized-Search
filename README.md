# N-Queens-Optimized-Search
This project implements optimized versions of BFS, DFS and Simulated Annealing for a N-Queens like problem.
The problem is similar to N-queens and uses the concept of Lizards instead of Queens, with a catch, some cases might have trees which can prevent the Lizards from attacking each other. The detailed project description is a below:-

You are a zookeeper in the reptile house. One of your rare South Pacific Tufted Wizzo lizards
(Tufticus Wizzocus) has just had several babies. Your job is to find a place to put each baby lizard
in a nursery.
However, there is a catch, the baby lizards have very long tongues. A baby lizard can shoot out
its tongue and eat any other baby lizard before you have time to save it. As such, you want to
make sure that no baby lizard can eat another baby lizard in the nursery (burp).
For each baby lizard, you can place them in one spot on a grid. From there, they can shoot out
their tongue up, down, left, right and diagonally as well. Their tongues are very long and can
reach to the edge of the nursery from any location.

In addition to baby lizards, your nursery may have some trees planted in it. Your lizards cannot
shoot their tongues through the trees nor can you move a lizard into the same place as a tree. As
such, a tree will block any lizard from eating another lizard if it is in the path. Additionally, the
tree will block you from moving the lizard to that location.

### Input: 
The file input.txt in the current directory of your program will be formatted as follows:
- First line: instruction of which algorithm to use: BFS, DFS or SA
- Second line: strictly positive 32-bit integer n, the width and height of the square nursery
- Third line: strictly positive 32-bit integer p, the number of baby lizards
- Next n lines: the n x n nursery, one file line per nursery row (to show you where the trees are).
It will have a 0 where there is nothing, and a 2 where there is a tree.
So for instance, an input file arranged (but with no lizards yet) and requesting you
to use the DFS algorithm to place 8 lizards in the 8x8 nursery would look like:

DFS

8

8

00000000

00000000

00000000

00002000

00000000

00000200

00000000

00000000

## Output: 
The file output.txt which your program creates in the current directory should be
formatted as follows:
- First line: OK or FAIL, indicating whether a solution was found or not.
- If FAIL, any following lines are ignored.
- Next n lines: the n x n nursery, one line in the file per nursery row, including the baby lizards
and trees. It will have a 0 where there is nothing, a 1 where you placed a baby
lizard, and a 2 where there is a tree.
For example, a correct output.txt for the above sample input.txt is:

OK

00000100

10000000

00001000

01002001

00000000

00100200

00000010

00010000


