#include "Browser.h"

/* your browser implementation here */


Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    // TODO
    windows.prepend(Window());
}

void Browser::closeWindow() {
    // TODO
    
    windows.removeNode(windows.getFirstNode());
    
}

void Browser::switchToWindow(int index) {
    // TODO
   windows.moveToIndex(index, 0); 
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    // TODO
    
    to.newTab(from.getActiveTab());
    from.closeTab(); 
}


void Browser::mergeWindows(Window &window1, Window &window2) {
    // TODO
   while(window2.isEmpty() == false)
   {
        window2.changeActiveTabTo(0);
        window1.newTab(window2.getActiveTab());
        
        window2.closeTab();
    
   }
    
}

void Browser::mergeAllWindows() {
    // TODO
    
        int i = 1;
        while( i < windows.getSize())
        {
            mergeWindows(windows.getFirstNode() -> data, windows.getNodeAtIndex(i)->data);
            i++;
        }
        
}

void Browser::closeAllWindows() {
    // TODO
    
    windows.removeAllNodes();
    
}

void Browser::closeEmptyWindows() {
    // TODO
    int i =0;
    while(i<windows.getSize())
    {
        if(windows.getNodeAtIndex(i)->data.isEmpty() == true) 
        {
           windows.removeNode(windows.getNodeAtIndex(i));
        }
        else
        {
            i++;
        }
    }
        
       
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}

