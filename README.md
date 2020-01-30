# HW4GalEndAmit

the work program was split between us the mission.
Gal work on the Search,Searchable file that include all the algorithem and solving the probleam, 
Amit work on the server and get the problem fron client. Together we make the object adapter and connect the parts.

# boot.cpp Main
main can get port as parameter or using 5600 by defalut.

# server_side.h - server_side namespase
5 interface- server, clientHandler, cacheManager, clientHandlerFactory, solver.

# boot.h
Implemenation for all the interface above for as progrem needed.

# file cache Manager:
every solution has file as cache, and program store in map 5 last solution to get them in O(1).

# MytestClient Handler:
create client handler by factory design pattern. Has handle client function that searce solution in cache or solve the problem.
client handler has solver object(object adapter), that run the search.

# serial Server:
every client that connect handling by queue (LIFO). A thread accept the client and enter thier
client socket the queue. main thread send to handle client the top of the client queue.

# parallel server:
every client that accept solved by open new thread with clientHandle func.

# Object adapter:
has the Astar search and connect between the server and the solving problem ways.(SOLID)
Astar doent "lose" to BestFirstSearch at our study but we still use it.

# search:
For solving "the shortest path - in matrix" , we used "Bridge" design pattern, that return "soution", by two parameters given, Searcher & Searchable.
Searcher:
An Intrface of algorithem that solve every problem that  can be represent as matrix, and the goal is to find the shortest way. Given "start" & "end points, find and return the solution for the shortest way.
SearcherAbs:
The algorithems we used, have few functions and fields in common, so we used that abstract class to share code.
BFS, DFS,AStar,BestFirstSearch:
All are very popular ways of searching. Inherites from "searcherAbs". We implemented them to find solutions.

# searchable: 
The "problem" that we want to solve(by the searcher).
Given matrix, (as text), splits the rows and the columns into a 2d array, has the functions to "return suppressors" for every point int the matrix.
And functiona for Return "start" & "end" points.



