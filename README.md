# a-star
implementation of A-star (A*) planning algorithm  in c++

Here is the c++ code for A star I generally use in assignments. Same could also be converted into python

<br> A brief explanantion of components
<h3>Node </h3>
Basic data structure/element of the path. Currently contains 2 DoF, but could be increased, 
<br>and get getSuccs could be modified to include motion primitives and other contraints.
<br>Further the key function would need to be modified if there is change in range and number
<br> of degrees of freedoms. The heuristic function is also present and could be modified depending
<br> upon the problem.

<h3>Astar</h3>
The plannner, contains the loop, closed list, open list (the priority queue). It is a weighted Astar,
<br> by default the weight is 1.
<I>findPath</I> function contains the loop, to get to the goal.
<I>getPath</I> function builds the tree out of closed list when the goal has been reached.

<h3>main</h3>
Contains the arena specs, weight, and DoF limits. Instantiates and calls astar, to get the path.
