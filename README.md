The Final solution is using a heap-based bfs traversal which picks which cities to visit according to maximum current reward. 
It also prunes the cities being visited again if the current reward from those cities is less than what we've previously got.

Initially I thought of using the dfs approach and it would have worked if the graph did not contain cycles. The logic to handle state of the problem with multiple cycles is better handled with bfs approach using a queue.

## A major assumption:
### If our destination is city 'B', we can visit it but not count it in the final reward. i.e.: deduct only travel cost from A to B and do not pay the visit cost for B because we are ending there and don't need its reward. This will also be considered valid and can be the final result [with final reward being reward of previous city.

## Some minor assumptions:
### the graph can have multiple cycles
### the road is uni-directional (i.e. we can travel from A to B but not from B to A, if not explicitly mentioned)
### we can travel to a city multiple times (if there's a cycle) to get maximum reward, as long as we have the necessary remainingTime
### there is no negative weight road/city
### there is no self loop (CITY_A -> CITY_A is not present in the graph)
### there is no repeating road[edge] in input
