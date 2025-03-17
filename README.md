# Graph-project
This project was developed during the second semester of university studies. It analyzes given graphs and computes various properties, including:  
- Listing all the vertices of the graph with their neighbors
- Degree sequence – lists the degrees of all vertices.
- Number of connected components – determines how many separate subgraphs exist.
- Bipartiteness check – verifies whether the graph is bipartite.
- Vertex coloring using different algorithms:
  *Greedy algorithm in order of vertex indices.
  *LF method (Largest First) – processes vertices in descending order of degree, breaking ties using vertex indices.
- Number of edges in the graph complement – computes edges that are missing to form a complete graph.
  
## **Input Format**
The first line contains an integer 
**𝑘**
k, the number of graphs.  
The following lines contain 
**𝑘**
sets of graph data.  
Each set starts with an integer 
**𝑛**
(number of vertices), followed by adjacency lists for each vertex.  
Each adjacency list contains:
An integer 
**s** – the number of neighbors.
**s** integers – identifiers of adjacent vertices (values range from 
1 to 
**𝑛**).  
## **Example Input:**
1  
4 1 2 1 1 1 4 1 3  

## **Example Output:**
This is your graph 1:  
1 : 2  
2 : 1  
3 : 4  
4 : 3  

Gradual sequence : 1 1 1 1  
Number of cohesion : 2  
Is bipartiteness : T  
Vertices colours using greedy algorithm : 1 2 1 2  
Vertices colours using LF algorithm : 1 2 1 2  
The number of the graph complement's edges : 4  

## **Usage**  
This tool can be used to analyze graph structures, test algorithms on different graph instances, and study various graph-theoretical properties efficiently.
