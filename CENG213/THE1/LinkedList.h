#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};




template<class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    head = NULL;
    size = 0;
    *this = obj;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    /* TODO */
   
 
    if (head != NULL)
    {
        Node<T> *temp = head;
        while(temp->next != head)
        {
            Node<T> *current = temp;
            temp = temp->next;
            delete current;
        } 
        delete temp;
        head = NULL;
        size = 0;
    }
 
 
 



    
}
template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    
   
    if (this != &rhs)
    {
        this->removeAllNodes();
        
        if (rhs.head == NULL)
        {
            head = NULL;
        }
        else
        {

            head = new Node<T>(rhs.head->data);
            Node<T> *curr = head;
            Node<T> *copy = rhs.head;
            while (copy->next != rhs.head)
            {
                copy = copy->next;
                curr->next = new Node<T>(copy->data, curr, NULL);
                curr = curr->next;
                size++;
            }
            curr->next = head;
            head->prev = curr;
        }
    }
    size = rhs.size;
    return *this;
    
 
 
    
}


template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    if(head == NULL)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    
    Node<T> *temp = head;
    
    if(head == NULL)
    {
        return false;
    }
    do
    {
        if (temp == node)
        {
            return true;
        }
        temp = temp->next;
    } while (temp != head);
    
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    if(head== NULL)
    {
        return NULL;
    }
    else
    {
        return head;
    }
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    if(head== NULL)
    {
        return NULL;
    }
    else
    {
        if(head->prev != NULL)
        {
            return head->prev;
        }
        else
        {
            return head;
        }
    }   
    
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    if(head==NULL)
    {
        return NULL;
    }
    if(head!=NULL)
    {
        
        Node<T> *temp = head;
        do
        {
            if(temp->data == data)
            {
                return temp;
            }
            temp = temp->next;
            
        }while(temp != head);
        
        return NULL;        
        
    }

    
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    if(head == NULL)
    {
        return NULL;
    }
    else
    {
        Node<T> *temp = head;
        if(index>size-1 || index < 0)
        {
            return NULL;
        }
        for(int i= 0; i<index; i++)
        {
            temp = temp->next;
        }
        return temp;
    }
    
    
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    /* TODO */
    
    if(head ==NULL)
    {
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
    }
    else
    {
        Node<T> *temp = new Node<T>(data);
        temp->next = head;
        temp->prev = head->prev;
        head->prev->next = temp;
        head->prev = temp;
        
    }
    size+=1;



}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    
    if(head== NULL)
    {
        head = new Node<T>(data);
        head->next = head;
        head->prev = head;
    }
    else
    {
        Node<T> *temp = new Node<T>(data);
        temp->next = head;
        temp->prev = head->prev;
        head->prev->next= temp;
        head->prev = temp;
        head=temp;
        
    }
    size +=1;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    if(head==NULL)
    {
        return;
    }
    Node<T> *temp = head;
    do
    {
        if(temp == node)
        {
            Node<T> *after = new Node<T>(data);
            after->next = node->next;
            after->prev = node;
            node->next = after;
            after->next->prev = after;
            size++;
        }
        temp = temp->next;
        
    }while(temp != head);    


}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    
    Node<T> *temp = head;
    if(index<=size-1 && index>0)
    {
        
        for(int i= 0; i<index; i++)
        {
            temp = temp->next;
        }
        
        Node<T> *insert = new Node<T>(data);
        insert->prev = temp->prev;
        insert->next = temp;
        temp->prev->next = insert;
        temp->prev = insert;
        size+=1;
    }
    
    if(index ==0)
    {
        Node<T> *insert = new Node<T>(data);
        insert->next = head;
        insert->prev = head->prev;
        head->prev->next= insert;
        head->prev = insert;
        head=insert;
        size +=1;
    }
}
template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    Node<T> *temp = head;
    int count = 0;
    do
    {
        if(temp == node)
        {
            return count;
        }
        
        temp=temp->next;
        count +=1;
        
        
    }while(temp != head);
    
    return -1;
}


template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex) 
{
    /* TODO */
    /*if(currentIndex == newIndex)
    {
        return;
    }
    if(currentIndex <= size-1 && newIndex>=0)
    {
        
        if(head != NULL)
        {
            
            if(newIndex < size-1)
            {
                
                if(currentIndex == 0)
                {
                    Node<T> *temp = head;
                    Node<T> *curr = head;
                    
                    

                    for(int i =0; i<currentIndex ; i++)
                    {
                        temp = temp->next;
                    }
                    
                    for(int j = 0; j< newIndex; j++)
                    {
                        curr = curr->next;
                    }
                    if(newIndex - currentIndex != 1)
                    {
                    
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                        
                        temp->next = curr->next;
                        curr->next->prev = temp;
                        curr->next = temp;
                        temp->prev = curr;
                        
                        head = head->next;
                        return;
                        
                        /*temp->next->prev = temp->prev;
                    	temp->prev->next = temp->next;
                    	temp->next = curr->next;
                    	temp->prev = curr;
                    	curr->next = temp;
                    
                    	temp->next->prev = temp;  
                    	           
                    }

                    
                    else
                    {
                    	
                    		if(newIndex == 1)
                            {
                                head = head->next;
                                temp->prev->next = head;
                                head->prev = temp->prev;
                                head->next->prev = temp;
                                temp->prev = head;
                                temp->next = head->next;
                                head->next = temp;
                                return;

                            
                            }
                    		temp->next->prev = temp->prev;
                    		temp->prev->next = temp->next;
                    		temp->next = curr->next;
                    		temp->prev = curr;
                    		curr->next = temp;
                    		temp->next->prev = temp;
                    		head = curr;
                    	
                    }

                    
                }
                if(newIndex == 0)
                {
                    Node<T> *temp = head;
                    Node<T> *curr = head;
                    
                    for(int i =0; i<currentIndex ; i++)
                    {
                        temp = temp->next;
                    }
                    
                    for(int j = 0; j< newIndex; j++)
                    {
                        curr = curr->next;
                    }
                    
                    if(currentIndex-newIndex != 1){
                        
                       if(currentIndex != size -1)
                       {
                       
                        temp->next->prev = temp->prev;
                        temp->prev->next = temp->next;
                  /*      temp->next = curr->next;
                        temp->prev = curr;
                        curr->next = temp;
                        temp->next->prev = temp;
                        head = temp; */
                        /*temp->next = curr;
                        temp->prev = curr->prev;
                        curr->prev = temp;
                        temp->prev->next = temp;
                        head = temp;
                        }
                        else
                        {
                        	head = temp;
                        
                        }
                        
                        
                        
                        
                    }
                    else
                    {
                        if(size != 2)
                        {
		                temp->prev = curr->prev;
		                temp->prev->next = temp;
		                curr->next = temp->next;
		                curr->prev = temp ;
		                temp->next = curr;
		                curr->next->prev = curr;
		                head = temp;
		         }
		         else
		         {
		         	head = temp;
		         
		         
		         }
		         
                    }
                    
                    
                }
                else
                {
                    
                    Node<T> *temp = head;
                    Node<T> *curr = head;
                    
                    for(int i =0; i<currentIndex ; i++)
                    {
                        temp = temp->next;
                    }
                    
                    for(int j = 0; j< newIndex; j++)
                    {
                        curr = curr->next;
                    }
                    if(currentIndex<newIndex)
                    {
                        if(newIndex-currentIndex != 1) ////???
                        {
                        
		                temp->next->prev = temp->prev;
		                temp->prev->next = temp->next;
		                temp->next = curr->next;
		                temp->prev = curr;
		                curr->next = temp;
		                temp->next->prev = temp;
		         }
		         else
		         {
		         	////bak
		         		temp->next->prev = temp->prev;
		                	temp->prev->next = temp->next;
		                	temp->next = curr->next;
		                	temp->prev = curr;
		                	curr->next = temp;
		                	temp->next->prev = temp;
		         	
		         	
		         	
		         	
		         }
		         
		         
                    }
                    else
                    {
                    	
                    	
                        temp->next->prev = temp->prev;
                        temp->prev->next = temp->next;
                        temp->next = curr;
                        temp->prev = curr->prev;
                        curr->prev = temp;
                        temp->prev->next = temp;
                        
                       
                    }
                    
                }
            }
            else
            {
                newIndex = size-1;
                
                if(currentIndex == 0)
                {
                    
                   /* Node<T> *temp = head;
                    Node<T> *curr = head;
                    
                    for(int i =0; i<currentIndex ; i++)
                    {
                        temp = temp->next;
                    }
                    
                    for(int j = 0; j< newIndex; j++)
                    {
                        curr = curr->next;
                    }
                    */
                    
                    /*head= head->next;
                }
                
                else
                {
                    
                    Node<T> *temp = head;
                    Node<T> *curr = head;
                    
                    for(int i =0; i<currentIndex ; i++)
                    {
                        temp = temp->next;
                    }
                    
                    for(int j = 0; j< newIndex; j++)
                    {
                        curr = curr->next;
                    }
                    if(newIndex-currentIndex == 1)
                    {
                        temp->next->prev = temp->prev;
                        temp->prev->next = curr;
                        temp->next = curr->next;
                        temp->prev = curr;
                        curr->next = temp;
                        temp->next->prev = temp;
                    }
                    else
                    {
                        temp->next->prev = temp->prev;
                        temp->prev->next = temp->next;
                        temp->next = curr->next;
                        temp->prev = curr;
                        curr->next = temp;
                        temp->next->prev = temp;
                       
                    }
                        
                }               
            }
        
        }
        
    }*/


    if((currentIndex <= size-1) && (currentIndex >= 0))
    {
        if(currentIndex != newIndex)
        {
            if(newIndex >= 0)
            {
                if(newIndex < size)
                {
                    Node<T>* temp = head;
                    Node<T>* curr = head;
                    Node<T>* p;
                    Node<T>* a;

                    for(int i = 0; i< currentIndex; i++)
                    {                
                        temp = temp->next;

                    }

                    for(int j = 0; j< newIndex; j++)
                    {
                        curr = curr->next;
 
                    }
                    if(currentIndex>newIndex)
                    {
                        if(currentIndex == size-1 && newIndex == 0)
                        {
                            head = temp;
                        }
                        else if(currentIndex != size-1 && newIndex == 0)
                        {
                            a = temp->prev;
                            p = curr->prev;
                            a->next = temp->next;
                            temp->next->prev = a;
                            p->next = temp;
                            temp->prev = p;
                            temp->next = curr;
                            curr->prev = temp;
                            head = temp;
                        }
                        else
                        {
                            a = temp->prev;
                            p = curr->prev;
                            a->next = temp->next;
                            temp->next->prev = a;
                            p->next = temp;
                            temp->prev = p;
                            temp->next = curr;
                            curr->prev = temp;
                        }
                    }
                    else
                    {
                        if(currentIndex == 0 && newIndex != size-1)
                        {
                            head = head->next;
                            a = temp->prev;
                            p= curr->next;
                            a->next = temp->next;
                            temp->next->prev = a;
                            curr->next = temp;
                            temp->prev = curr;
                            temp->next = p;
                            p->prev = temp;
                        }
                        else if(currentIndex == 0 && newIndex == size-1)
                        {
                            head = head->next;
                        }
                        else
                        {
                            a = temp->prev;
                            p = curr->next;
                            a->next = temp->next;
                            temp->next->prev = a;
                            curr->next = temp;
                            temp->prev = curr;
                            temp->next = p;
                            p->prev = temp;   
                        }
                    }
                }
                else
                {
                    Node<T>* temp = head;
                    Node<T>* last = head;

                    for(int i = 0; i< currentIndex; i++)
                    {
                        temp = temp->next;
                    }
                    while(last->next != head)
                    {
                        last = last->next;
                    }
                    if(temp == head)
                    {
                        head=head->next;
                    }
                    else if(temp != head && currentIndex != size-1)
                    {

                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                        last->next = temp;
                        temp->prev = last;
                        temp->next = head;
                        head->prev = temp;
                    }
                }
            }
        }
    }

}






template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    /* TODO */
  
    if (containsNode(node))
    {
        if (size == 1)
        {
            delete node;
            size--;
            head = NULL;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            if (node == head)
            {
                head = node->next;
            }
            delete node;
            size--;
        }
    }
    
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    /* TODO */
    
     Node<T> *curr = head;
     
     
    if(head != NULL) 
    {
        do
        {
            if (curr->data == data)
            {
                
                if(size==1)
                {
                    head = NULL;
                    size--;
                }
                else
                {
                    Node<T> *temp = curr;
                    
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    
                    if(temp==head)
                    {
                        head= temp->next;
                    }
                    curr = curr->next;
                    delete temp;
                    size--;
                }
                
            }
            else
            {
                curr = curr->next;
            }
    
        } while (curr != head); 
    }

   
    
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    
    
    if(size != 0)
    {
        Node<T> *temp = head;
        if(index > 0 && index < size)
        {
            
            
                for(int i = 0; i<index; i++)
                {
                    temp = temp->next;
                }
                
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                size-=1;
            
            
            
        }
        if(index == 0 && size != 1)
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            head = temp->next;
            delete temp;
            size--;
        }
        else if(index ==0 && size ==1)
        {
            
               
                delete temp;
                head = NULL;
                size = 0;
            
        }
        
        
    }
   
    
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    /* TODO */
    
    Node<T> *current = head;
    if (current != NULL)
    {
        do
        {
            Node<T> *temp = current;
            current = current->next;
            delete temp;
        } while (current != head);
        size = 0;
    }
    head = NULL;
 
    
}
template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}



#endif //LINKEDLIST_H
