The solution is using a heap-based bfs traversal which picks which cities to visit according to maximum current profit. 
It also prunes the cities being visited again if the current profit from those cities is less than what we previously got.

## A major assumption:
### If our destination is city 'B', we can visit it but not count it in the final profit. i.e.: deduct only travel cost from A to B and do not pay the visit cost for B because we are ending there and don't need its reward. This will also be considered valid and can be the final result [with final profit being profit of previous city.

## Some minor assumptions:
### there is no negative weight road/city
### there is no self loop [CITY_A -> CITY_A is not present in the graph]
### there is no repeating road in input
