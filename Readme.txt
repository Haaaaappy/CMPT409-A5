p10147 Highways:
Basic idea is to use Kruskal's algorithm to build a minium spanning tree on existing edges.
1. connect all existing edges in a disjoint set of cities.
2. between every two cities,  if they are not already connected, put a edge in an array of all posible edges. The weight is the Euclidean distance between two cities.
3. sort all posible edges by weight.
4. from lowest weight edges, add this edge to the graph if cities of its two ends are not connected.

p208 Firetruck:
- Data Structure:
Use 2-Dimensional vector to store adjacent list to form the graph.
Use vector<int> to store possible path.
- Algorithm:
Use DFS to find a possible path from source to the target.
While doing DFS, use BFS to prune the branch that cannot be connected to the target in the current situation. [avoid timeout]

p10054 The Necklace:
- Data Structure:
Use 2-Dimensional vector to store adjacent list to form the graph.
Use vector<int> to store possible path.
- Algorithm:
Set each color as a vertex and each bead as an edge to form an undirected graph.
First, use BFS to check whether the graph is connected. If not, some beads may be lost.
If the graph is connected, find out whether it is an Euler cycle. 
If the degree of each vertex is odd, some beads may be lost.
If the degree of each vertex is even, there is an Eular cycle. Each time remove an edge and do recursion to find out the Eular cycle.

p589 Pushing box:
- Data Structure:
    struct Point to store each step's box position, person's position, pre Point, from which direction, box step, box+person step and walkpath.
    p[40000] to store box and person to store person.
    vector<pair<int,int> > to store already shown position pair of box and person.(avoid recheck)
    vector<string> walkPath to store person's walk path.

- Algorithm:
    1. use BFS to search for the shoertest path of box.
        to check four direction if it can be pushed, to check if person can reach box opposite moving direction point.
        search all the possible shortest path to get the minimun total step one
    2. use BFS to search for the shortest path of person.
        find one shortest path to store in walkPath and index walkPathPos store in struct Point
    3. finally output the step shortest and total shortest path.