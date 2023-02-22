#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    // TODO:
    
    
    vertices.resize(vertexPositions.size());
    Vertex new_vertex;
    for(int i=0;i<vertices.size(); i++)
    {
       
        new_vertex.position3D = vertexPositions[i];
        new_vertex.id = i;
        vertices[i] = new_vertex;
    }
    
    adjList.resize(vertexPositions.size());
    
  
    
    for(int i = 0; i < vertices.size(); i++)
    {
        adjList[i].push_front(&vertices[i]);
    }
    
    for (int i = 0; i < edges.size(); i++) 
    {
        if (edges[i].vertexId0 == edges[i].vertexId1) 
		{
			continue;
		}
		adjList[edges[i].vertexId0].push_back(&(vertices[edges[i].vertexId1]));
		
		adjList[edges[i].vertexId1].push_back(&(vertices[edges[i].vertexId0]));
	}
    
    
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    
    double sum = 0;
    
    int number_of_vertices = TotalVertexCount();
    std::list<Vertex*>::const_iterator current;
    std::list<Vertex*>::const_iterator next;
    for(int i = 0; i< number_of_vertices; i++)
    {
        current = adjList[i].begin();
       
        
        for(next = ++adjList[i].begin(); next != adjList[i].end(); next++)
        {
            sum += sqrt(pow(((*current)->position3D.x - (*next)->position3D.x), 2) + pow(((*current)->position3D.y - (*next)->position3D.y), 2)+ pow(((*current)->position3D.z - (*next)->position3D.z), 2));
            
        }
        
    }
     
    ////bak/////////////????????????????
    
    
    double a = sum/ (2*TotalEdgeCount());
    return a;
    
    
    
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    
    return (double) TotalEdgeCount()/TotalVertexCount();
    
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    
    return vertices.size();
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    int sum = 0;
  
    
    for (int i = 0 ; i < adjList.size() ; i++)
    {
        
        sum += adjList[i].size()-1;
    }
  
    
    return sum/2;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
   
    int sum = 0;
    int flag = -1;
   
    
    for(int i = 0; i< adjList.size(); i++)
    {
       
        
        if((adjList[i].front())->id == vertexId )
        {
            sum += adjList[i].size();
        }
        
    }
    if(sum == 0)
    {
        return -1;
    }
    else
    {
        return sum-1;
    }
    
   
 
    
 
   
   
    
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    // TODO:
   
    if(vertexId <vertices.size() && vertexId>=0)
    {
        
        
        if(adjList[vertexId].size() != 1)
        {
            std::list<Vertex*>::const_iterator current;
            for(current = ++adjList[vertexId].begin() ; current != adjList[vertexId].end() ; current++)
            {
                outVertexIds.push_back((*current)->id) ;
            }
        }
        else
        {
            return;
        }
        
    }
    else
    {
        return;
    }

    
}

double MeshGraph::find_distance(Double3 left, Double3 right) const
{
    double sum = 0;
    sum += sqrt(pow((left.x - right.x), 2) + pow((left.y - right.y), 2)+ pow((left.z - right.z), 2));
    return sum;
}

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    // TODO:
    
     
 if(vertexIdFrom >=0 && vertexIdFrom< vertices.size())
 {
    if(vertexIdTo >=0 && vertexIdTo< vertices.size())
    {
        
        outputColorAllVertex.resize(vertices.size());
        for(int i = 0; i<vertices.size(); i++)
        {
            outputColorAllVertex[i].r = 0;
            outputColorAllVertex[i].g = 0;
            outputColorAllVertex[i].b = 0;
        }
        
        BinaryHeap binheap;
        
        for(int i = 0; i < vertices.size(); i++)
        {
            binheap.Add(vertices[i].id, pow(2,64));
        }
        binheap.ChangePriority(vertexIdFrom, 0);
        
        std::vector<double> distance;
        std::vector<int> prev;
        
        distance.resize(vertices.size());
        prev.resize(vertices.size());
        
        for(int i = 0; i < vertices.size(); i++)
        {
            distance[i] = pow(2,64);
        }
        
        distance[vertexIdFrom] = 0;
        int outId;
        double outW;
        while(binheap.HeapSize()!= 0)
        {
            binheap.PopHeap(outId, outW);
            
            std::list<Vertex*>::const_iterator current;
            
            for(current = adjList[outId].begin(); current!= adjList[outId].end(); current++)
            {
                double curr_distance = find_distance(vertices[outId].position3D, (*current)->position3D) + distance[outId]; 
                
                
                if(curr_distance < distance[(*current)->id] )
                {
                   distance[(*current)->id] = curr_distance; 
                   prev[(*current)->id] = outId;
                   binheap.ChangePriority((*current)->id, curr_distance);
                }
                
                
            }
            
            
        }
        
        for(int current = vertexIdTo ; current != vertexIdFrom ; current = prev[current])
        {
            
            outputColorAllVertex[current] = color;

            
        }
        
        outputColorAllVertex[vertexIdFrom] = color;
        
        
        
        
        
        
        
    }
 }
    
    
    
    
}





void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    // TODO:
    outputColorAllVertex.resize(vertices.size());

        
    BinaryHeap bfsheap;
    

    bfsheap.Add(vertexId, 0);
    
    std::vector<int> visited;
    
    visited.resize(vertices.size());
    std::vector<int> prev;
    prev.resize(vertices.size());
        
    
    for(int i = 0; i< vertices.size();i++)
    {
        visited[i] = 0;
    }
    
    visited[vertexId] = 1;
    int outId;
    double outW;
    int a =1;
    while(bfsheap.HeapSize() != 0)
    {
        bfsheap.PopHeap(outId, outW);
        
        std::list<Vertex*>::const_iterator current;
            
        for(current = adjList[outId].begin(); current!= adjList[outId].end(); current++)
        {
            
            if(visited[(*current)->id] == 0)
            {
                visited[(*current)->id] = 1;
                prev[(*current)->id] = outId;
                
                bfsheap.Add((*current)->id , a);
                //strictly increase 10 olur mu tekrar  bak
                a+=10;
            }
            
            
        }
        
        
        
        
    }
    
    double sum_distance;
    
    std::vector<int> index ;
    std::vector<double> sumw ;
    for(int i = 0 ; i<prev.size() ; i++)
    {
        if(visited[i] != 0)
        {
            
            
            int depth = 0;
            int current = i;
            int temp ;
            int new_temp;
            sum_distance= 0;
            
            for(int j = 0; j<maxDepth; j++ )
            {
                
                
                if(current == vertexId && depth < maxDepth)
                {
                    continue;
                }
                temp = current;
                current = prev[current];
                new_temp = current;
                depth +=1;
                sum_distance += find_distance(vertices[temp].position3D, vertices[new_temp].position3D);
                
            } 
            if(current == vertexId)
            {
                index.push_back(i);
                sumw.push_back(sum_distance);
                
              
            }
            
        }
            
    }
    
    std::vector<int>::iterator current;   
    std::vector<double>::iterator sum_iter = sumw.begin();
        
    for(current = index.begin(); current!=index.end(); current++)
    {
      
        if(type == FILTER_GAUSSIAN)
        {
            outputColorAllVertex[*current].r = color.r * std::exp(-(pow(*sum_iter, 2))/ pow(alpha, 2));
            outputColorAllVertex[*current].g = color.g * std::exp(-(pow(*sum_iter, 2))/ pow(alpha, 2));
            outputColorAllVertex[*current].b = color.b * std::exp(-(pow(*sum_iter, 2))/ pow(alpha, 2));
        }
        if(type == FILTER_BOX)
        {
            if(*sum_iter <= alpha && *sum_iter >= -alpha)
            {
                outputColorAllVertex[*current] = color;
            }
            else
            {
                outputColorAllVertex[*current].r = 0;
                outputColorAllVertex[*current].g = 0;
                outputColorAllVertex[*current].b = 0;
            }
        }
                
        sum_iter++;
        
        
        
    }
    
    
    
    
    
    
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    // TODO:
    
if(vertexId>=0 && vertexId < vertices.size())
{
    outputColorAllVertex.resize(vertices.size());

        
    BinaryHeap bfsheap;
    

    bfsheap.Add(vertexId, 0);
    
    std::vector<int> visited;
    
    visited.resize(vertices.size());
    std::vector<int> prev;
    prev.resize(vertices.size());
        
    
    for(int i = 0; i< vertices.size();i++)
    {
        visited[i] = 0;
    }
    
    visited[vertexId] = 1;
    int outId;
    double outW;
    int a =1;
    while(bfsheap.HeapSize() != 0)
    {
        bfsheap.PopHeap(outId, outW);
        
        std::list<Vertex*>::const_iterator current;
            
        for(current = adjList[outId].begin(); current!= adjList[outId].end(); current++)
        {
            
            if(visited[(*current)->id] == 0)
            {
                visited[(*current)->id] = 1;
                prev[(*current)->id] = outId;
                
                bfsheap.Add((*current)->id , a);
                a+=10;
            }
            
            
        }
        
        
        
        
    }
    
  std::vector<int> index ;
    for(int i = 0 ; i<prev.size() ; i++)
    {
        if(visited[i] != 0)
        {
            int depth = 0;
            int current = i;
            
            for(int j = 0; j<maxDepth; j++ )
            {
                
                
                if(current == vertexId && depth < maxDepth)
                {
                    continue;
                }
                current = prev[current];
                depth +=1;
                
            } 
            if(current == vertexId)
            {
                index.push_back(i);
                
            }
            
        }
            
    }
    std::vector<int>::iterator current;    
        
    for(current = index.begin(); current!=index.end(); current++)
    {
        double distance = find_distance(vertices[*current].position3D, vertices[vertexId].position3D);
                
                if(type == FILTER_GAUSSIAN)
                {
                    outputColorAllVertex[*current].r = (unsigned char) color.r * std::exp(-(pow(distance, 2))/ pow(alpha, 2));
                    outputColorAllVertex[*current].g = (unsigned char) color.g * std::exp(-(pow(distance, 2))/ pow(alpha, 2));
                    outputColorAllVertex[*current].b = (unsigned char) color.b * std::exp(-(pow(distance, 2))/ pow(alpha, 2));
                }
                if(type == FILTER_BOX)
                {
                    if(distance <= alpha && distance >= -alpha)
                    {
                        outputColorAllVertex[*current] = color;
                    }
                    else
                    {
                        outputColorAllVertex[*current].r = 0;
                        outputColorAllVertex[*current].g = 0;
                        outputColorAllVertex[*current].b = 0;
                    }
                }
        
        
        
    }
    
        
}
    

    
    
    
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}
