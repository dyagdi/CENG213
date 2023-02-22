#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
    struct HeapElement constr; 
    elements.push_back(constr);
    count = 0;
   
   
   
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:

    for(int i = 1; i< elements.size(); i++)
    {
        
        if(elements[i].uniqueId == uniqueId)
        {
            return false; 
           
        }

    }

    elements[0].uniqueId = uniqueId;
    elements[0].weight = weight;
    
    if((count + 1) == ( elements.size()))
    {
        elements.resize((elements.size( )*2) + 1);
    }
   
    // Percolate up
    int hole = ++count;
    for( ; elements[0].weight < elements[hole/2].weight; hole /= 2 )
    {
        elements[hole] = elements[hole/2];
        
    }
        
    elements[hole]= elements[0];
 
    
    
    return true;
    
    
    
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    
     if(count ==0)
     {
         return false;
     }
        
    outUniqueId = elements[1].uniqueId; 
    outWeight = elements[1].weight;
    
    elements[1] = elements[count];
    count--;
    
    int hole = 1;
    
    int child;
    struct HeapElement hole_element;
    
    hole_element.weight = elements[hole].weight;
    hole_element.uniqueId = elements[hole].uniqueId;
    
    double temp = elements[hole].weight;
    int id = elements[hole].uniqueId;
    
    for( ; hole*2 <= count; hole = child) {
        child = hole * 2;
        if(child != count && elements[child + 1].weight < elements[child].weight)
        {
            child++;
        }
            
        if(elements[child].weight < hole_element.weight)
        {
            elements[hole].uniqueId = elements[child].uniqueId;
            elements[hole].weight = elements[child].weight;
       
        }
            
        else
        {
            break;
        }
            
    }
    elements[hole].weight = hole_element.weight;
    elements[hole].uniqueId = hole_element.uniqueId;
    
    
    return true;
    
}
void BinaryHeap::heapify_down(int hole) {
    // Internal method to percolate down in the heap.
    // hole is the index at which the percolate begins.
    int child;
    struct HeapElement hole_element;
   // hole_element = elements[hole];
    hole_element.weight = elements[hole].weight;
    hole_element.uniqueId = elements[hole].uniqueId;
    
    double temp = elements[hole].weight;
    int id = elements[hole].uniqueId;
    
    for( ; hole*2 <= count; hole = child) {
        child = hole * 2;
        if(child != count && elements[child + 1].weight < elements[child].weight)
        {
            child++;
        }
            
        if(elements[child].weight < elements[hole].weight)
        {
           
            elements.at(hole).weight = elements.at(child).weight;
            elements.at(hole).uniqueId = elements.at(child).uniqueId;
       
       
        }
            
        else
        {
            break;
        }
            
    }
    elements[hole].weight = hole_element.weight;
    elements[hole].uniqueId = hole_element.uniqueId;
}

void BinaryHeap::buildHeap()
{
    
    for(int i = count/2; i > 0; i-- )
    {
        heapify_down(i);
    }
        
}
bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    
    int flag = 0;
    
    if (flag ==0)
    {
        for(int i = 1; i<= count; i++)
        {
        
            if(elements[i].uniqueId == uniqueId)
            {
                flag = 1;
           
            }

        }
    }
    
    if(flag ==1)
    {
        for(int i = 1; i<= count ; i++)
        {
            if(elements[i].uniqueId == uniqueId)
            {
                elements[i].weight = newWeight;
            }
        }
    
        buildHeap();
    }
    
    
    if(flag == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return count;
}
