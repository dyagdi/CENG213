#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
    // TODO
     
    if(tabs.isEmpty() == false)
    {
        return  (tabs.getNodeAtIndex(activeTab))->data;
    }
    else
    {
        activeTab = 0;
        return Tab();
    }
    
    
}

bool Window::isEmpty() const {
    // TODO
    
    if(tabs.isEmpty() == true)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
}

void Window::newTab(const Tab &tab) {
    // TODO
    if(tabs.isEmpty() == false)
    {
        
        if(tabs.getSize() == 1 && tabs.getFirstNode()->data == Tab() )
        {
            
            tabs.append(tab);
            activeTab += 1;
            
        }
        else
        {
            tabs.insertAfterNode(tab, tabs.getNodeAtIndex(activeTab)); ////??????????
            activeTab +=1;
        }
    }
    else if(tabs.isEmpty() == true)
    {
        tabs.prepend(tab);
        activeTab = 0;
    }
    
    
}

void Window::closeTab() 
{
    // TODO
    
   
    if(tabs.getSize() != 0)
    {
        if(activeTab == tabs.getSize()-1 && tabs.getSize() != 1)
        {
            tabs.removeNodeAtIndex(activeTab);
            activeTab =tabs.getSize()-1;
        }
        
        else if(activeTab == tabs.getSize()-1 && tabs.getSize() == 1)
        {
            tabs.removeNodeAtIndex(activeTab);
            activeTab = -1;
        } 
       else
        {
            
            tabs.removeNodeAtIndex(activeTab);
            
        }
    }
    
    else if(tabs.getSize() == 0)
    {
        tabs.removeAllNodes();
        activeTab = -1;
    }
    
    
}

void Window::moveActiveTabTo(int index) {
    // TODO
    if(index < tabs.getSize()-1)
    {
        tabs.moveToIndex(activeTab, index);
        activeTab = index; 
    }
    if(index>= tabs.getSize()-1)
    {
        index = tabs.getSize() -1; ////??????
        tabs.moveToIndex(activeTab, index);
        activeTab = (tabs.getSize())-1; 
    }
    
}

void Window::changeActiveTabTo(int index) {
    // TODO
    
    if(index<= (tabs.getSize())-1 && index >=0)
    {
        if(tabs.isEmpty() == false)
        {
            activeTab = index; 
        }
        
    }
    
    
}

void Window::addTab(Node<Tab> &tab) {
    // TODO
    /////düzelt!!!!
    
  
    if(tabs.isEmpty() == true)
    {
        tabs.append(tab.data);
        activeTab = 0;
    }
    else
    {
        tabs.append(tab.data);
        
    }
 
 
 
 
   
    
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}

