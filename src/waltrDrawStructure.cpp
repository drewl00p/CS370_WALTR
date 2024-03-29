#include <stack>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>

#include <iostream>
#include "tigr.h"
#include "waltrDrawStructure.hpp"

/*
The user will create an object with a constructor overload which will visualize the
passed data structure.
INPUT: A data stucture, currently STL arrays, C-Style arrays, Vectors, Stacks, and Queues.
*/

/*
C-Style array constructor overload
INPUT: Pointer to C-Style Array, Size of array
*/
Waltr::Waltr(const int* c_array, int c_size) {
	logVector(toVector(c_array, c_array + c_size));
}

/*
Vector constructor overload
INPUT: Pointer to vector
*/
Waltr::Waltr(const std::vector<int> vector) {
    logVector(vector);
}

/*
Stack constructor overload
INPUT: Pointer to stack
*/
Waltr::Waltr(const std::stack<int> stack) {
	logStack(stack);
}

/*
Queue constructor overload
INPUT: Pointer to queue
*/
Waltr::Waltr(const std::queue<int> queue) {
	logQueue(queue);
}

/*
Stores a copy of the vectors current contents
*/
void Waltr::logVector(std::vector<int> vector) {
    vector_log.push_back(vector);
}

/*
Stores a copy of the stacks current contents
*/
void Waltr::logStack(std::stack<int> stack) {
    stack_log.push_back(stack);
}

/*
Stores a copy of the queues current contents
*/
void Waltr::logQueue(std::queue<int> queue) {
    queue_log.push_back(queue);
}

/*
Converts array to vector.
*/
std::vector<int> Waltr::toVector(const int* begin, const int* end) {
	std::vector<int> vector;

    for(int*i = (int*)begin; i < end; i++) {
		vector.push_back(*i);
	}

    return vector;
}

/*
Prints vector, used for testing
*/
void Waltr::printVector(std::vector<int> vector) {
	for(auto x: vector) {
		std::cout<<x<<" ";
	}
}

/*
Prints stack, used for testing
*/
void Waltr::printStack(std::stack<int> stack) {
	while(!stack.empty()) {
		std::cout<<stack.top()<<" ";
		stack.pop();
	}
}

/*
Prints queue used for testing
*/
void Waltr::printQueue(std::queue<int> queue) {
	while(!queue.empty()) {
		std::cout<<queue.front()<<" ";
		queue.pop();
	}
}

/*
Prints vector log, used for testing
*/
void Waltr::printVectorLog() {
	for(auto vec: vector_log) {
        for(auto x: vec) {
		    std::cout<<x<<" ";
	    }
        std::cout<<std::endl;
	}
}

/*
Prints vector log, used for testing
*/
void Waltr::printStackLog() {
	for(auto stack: stack_log) {
        std::cout<<stack.top()<<" ";
        stack.pop();
    }
    std::cout<<std::endl;
}

/*
Prints vector log, used for testing
*/
void Waltr::printQueueLog() {
	for(auto queue: queue_log) {
        std::cout<<queue.front()<<" ";
        queue.pop();
	}
        std::cout<<std::endl;
}

//help screens


void Waltr::drawVHelp() {
    //help screen
    tigrPrint(current_screen, tfont, 5, 5, tigrRGB(0,255,0), "Help Screen");
    
    tigrPrint(current_screen, tfont, 25, 225, tigrRGB(255,0,0), "Press the Left or Right arrow keys to return");
    
    tigrPrint(current_screen, tfont, 10, 30, tigrRGB(0,200,100), "Press the Left and Right arrow keys to ");
    tigrPrint(current_screen, tfont, 10, 45, tigrRGB(0,200,100), "scroll through indices. ");
    
    tigrPrint(current_screen, tfont, 10, 80, tigrRGB(0,200,100), "Press the Up and Down arrow keys To ");
    tigrPrint(current_screen, tfont, 10, 95, tigrRGB(0,200,100), "change between instances.");

    tigrPrint(current_screen, tfont, 10, 130, tigrRGB(0,200,100), "Press the Z and X to move between ");
    tigrPrint(current_screen, tfont, 10, 145, tigrRGB(0,200,100), "indices in groups of 10.");

}


void Waltr::drawQSHelp() {
    //help screen
    tigrPrint(current_screen, tfont, 5, 5, tigrRGB(0,255,0), "Help Screen");
    
    tigrPrint(current_screen, tfont, 25, 225, tigrRGB(255,0,0), "Press the Up or Down arrow keys to return");
    
    tigrPrint(current_screen, tfont, 10, 80, tigrRGB(0,200,100), "Press the Left and Right arrow keys to");
    tigrPrint(current_screen, tfont, 10, 95, tigrRGB(0,200,100), "change between instances.");
    
    tigrPrint(current_screen, tfont, 10, 30, tigrRGB(0,200,100), "Press the Up and Down arrow keys ");
    tigrPrint(current_screen, tfont, 10, 45, tigrRGB(0,200,100), "to scroll through indices.");
    
}

void Waltr::drawVector() {
    
    help_screen_open = false;
    
    bufferX = 90;
    bufferY = 210;

    //get the amount of elements in the vector
    size = vector_log[vector_index].size();
    coords.resize(size);

    //scale the vector so it fits on screen
    boxSize = 12;
    
    tigrPrint(current_screen, tfont, 200, 30, tigrRGB(50,200,200), "Your vector!");

    tigrPrint(current_screen, tfont, 10, 230, tigrRGB(50,50,200), "Press 'H' for help screen");
    
    tigrPrint(current_screen, tfont, 30, 30, tigrRGB(50,50,200), "Logged instance: %d / %d", vector_index+1, vector_log.size());
    if (vector_log[vector_index].empty()) {
        tigrPrint(current_screen, tfont, 30, screenY/2, tigrRGB(50,50,200), "Vector is empty!");
    } else {

        page_index = item_index / 10;

       for(int i=page_index*10; i < (i % 10 ? size: 10 + page_index*10) ; i++) {
            tigrRect(current_screen, bufferX - 5, bufferY, boxSize, boxSize, tigrRGB(0,0,0));
            tigrFillRect(current_screen, bufferX - 5, bufferY, boxSize, boxSize, tigrRGB(0, 50, 0));
            tigrPrint(current_screen, tfont, bufferX - 3, bufferY - 15, tigrRGB(60, 0, 0), "%d", i);
            coords[(i-page_index*10) % 10] = bufferX;
            bufferX = bufferX + boxSize + 4;
        }
        //current index cant be larger than size of vector
            if (item_index >= vector_log[vector_index].size() - 1) {
                item_index = vector_log[vector_index].size() - 1;
        }

        tigrPrint(current_screen, tfont, screenX/2 + 30, screenY/2 - 30, tigrRGB(255,0,0), "Index: %d", item_index);
        tigrPrint(current_screen, tfont, screenX/2 + 30, screenY/2 - 10, tigrRGB(255,0,0), "Type: %s", typeid(item_index).name());
        tigrFillRect(current_screen, screenX/2 - 40, screenY/2 - 40, 50, 50, tigrRGB(38, 252, 66));
        tigrPrint(current_screen, tfont, screenX/2 - 30, screenY/2 - 30, tigrRGB(255,0,0), "%d", vector_log[vector_index][item_index]);

        tigrFillRect(current_screen, coords[(item_index-page_index*10) % 10] - 7, bufferY-2, boxSize+4, boxSize+4, tigrRGB(0, 200, 0));
        tigrPrint(current_screen, tfont, coords[(item_index-page_index*10) % 10] - 3, bufferY - 15, tigrRGB(255, 0, 0), "%d", item_index);
    }
}

void Waltr::drawQueue() {
    std::queue<int> queue = queue_log[queue_index];
    bufferX = 15;
    bufferY = 30;
    help_screen_open = false;

    size = queue.size();

    coords.resize(size);
    
    tigrPrint(current_screen, tfont, 200, 30, tigrRGB(50,200,200), "Your queue!");
    tigrPrint(current_screen, tfont, 10, 230, tigrRGB(50,50,200), "Press 'H' for help screen");

    boxSize = 12;
    tigrPrint(current_screen, tfont, 30, screenY - 30, tigrRGB(50,50,200), "Logged instance: %d / %d", queue_index+1, queue_log.size());
    if(queue.empty()) {
        tigrPrint(current_screen, tfont, 30, screenY/2, tigrRGB(50,50,200), "Queue is empty!");
    } else {

        page_index = item_index / 10;

        for (int i = page_index*10; i < (i % 10 ? size: 10 + page_index*10); i++) {
            tigrRect(current_screen, bufferX, bufferY, 50, boxSize, tigrRGB(0,0,0));
            tigrFillRect(current_screen, bufferX, bufferY, 50, boxSize, tigrRGB(0, 50, 0)); // prints boxes
            tigrPrint(current_screen, tfont, bufferX + 55, bufferY + 2, tigrRGB(60, 0 , 0), "%d", i); // prints indices
            
            queue.pop(); // pops through set to print each box
            
            coords[(i-page_index*10) % 10] = bufferY;
            bufferY += boxSize; // ensures that coordinates line up with box dimensions
        }

        queue = queue_log[queue_index];
        
        //current index cant be larger than size of queue
        if (item_index >= queue.size() - 1) {
            item_index = queue.size() - 1;
        }
        
        //we dont want to/cant pop a 0 size queue
        if (item_index != 0) {
            for (int i = 0; i < item_index;i++) {
                queue.pop();
            }
            
            tigrFillRect(current_screen, bufferX, coords[(item_index-page_index*10) % 10], 50, boxSize, tigrRGB(0, 200, 0)); // prints boxes
            tigrPrint(current_screen, tfont, bufferX + 55, coords[(item_index-page_index*10) % 10] + 2, tigrRGB(255, 0 , 0), "%d", item_index); // prints indices
            
        }

        tigrPrint(current_screen, tfont, screenX/2 + 10, screenY/2 - 40, tigrRGB(255,0,0), "Index: %d", item_index); // prints index
        tigrPrint(current_screen, tfont, screenX/2 + 10, screenY/2 - 20, tigrRGB(255,0,0), "Type: %s", typeid(queue.front()).name()); 
        // prints data type
        
        tigrRect(current_screen, screenX/2 - 50, screenY/2 - 40, 50, 50, tigrRGB(0,0,0));
        tigrFillRect(current_screen, screenX/2 - 50, screenY/2 - 40, 50, 50, tigrRGB(38, 252, 66));
        tigrPrint(current_screen, tfont, screenX/2 - 40, screenY/2 - 30, tigrRGB(255,0,0), "%d", queue.front()); // prints green box with data in it
        
        tigrFillRect(current_screen, bufferX, coords[(item_index-page_index*10) % 10], 50, boxSize, tigrRGB(0, 200, 0));
        tigrPrint(current_screen, tfont, bufferX + 55, coords[(item_index-page_index*10) % 10] + 2, tigrRGB(255, 0, 0), "%d", item_index);

    }
}

void Waltr::drawStack() {
    std::stack<int> stack = stack_log[stack_index];
    bufferX = 15;
    bufferY = 30;
    help_screen_open = false;

    size = stack.size();

    coords.resize(size);
    
    tigrPrint(current_screen, tfont, 10, 230, tigrRGB(50,50,200), "Press 'H' for help screen");

    tigrPrint(current_screen, tfont, 200, 30, tigrRGB(50,200,200), "Your stack!");

    boxSize = 12;
    tigrPrint(current_screen, tfont, 30, screenY - 30, tigrRGB(50,50,200), "Logged instance: %d / %d", stack_index+1, stack_log.size());
    if(stack.empty()) {
        tigrPrint(current_screen, tfont, 30, screenY/2, tigrRGB(50,50,200), "Stack is empty!");
    } else {

        page_index = item_index / 10;

        for(int i=page_index*10; i < (i % 10 ? size: 10 + page_index*10) ; i++) {
            tigrRect(current_screen, bufferX, bufferY, 50, boxSize, tigrRGB(0,0,0));
            tigrFillRect(current_screen, bufferX, bufferY, 50, boxSize, tigrRGB(0, 50, 0)); // prints boxes
            tigrPrint(current_screen, tfont, bufferX + 55, bufferY + 2, tigrRGB(60, 0 , 0), "%d", i); // prints indices

            stack.pop();

            coords[(i-page_index*10) % 10] = bufferY;
            bufferY += boxSize; // ensures that coordinates line up with box dimensions
        }

        stack = stack_log[stack_index];

        if (item_index >= stack.size() - 1) {
            item_index = stack.size() - 1;
        }

        if (item_index != 0) {
            for (int i = 0; i < item_index; i++) {
                stack.pop();
            }
        }

        tigrPrint(current_screen, tfont, screenX/2 + 10, screenY/2 - 40, tigrRGB(255,0,0), "Index: %d", item_index); // prints index
        tigrPrint(current_screen, tfont, screenX/2 + 10, screenY/2 - 20, tigrRGB(255,0,0), "Type: %s", typeid(stack.top()).name()); 
        // prints data type
        
        tigrRect(current_screen, screenX/2 - 50, screenY/2 - 40, 50, 50, tigrRGB(0,0,0));
        tigrFillRect(current_screen, screenX/2 - 50, screenY/2 - 40, 50, 50, tigrRGB(38, 252, 66));
        tigrPrint(current_screen, tfont, screenX/2 - 40, screenY/2 - 30, tigrRGB(255,0,0), "%d", stack.top()); // prints green box with data in it
        
        tigrFillRect(current_screen, bufferX, coords[(item_index-page_index*10) % 10], 50, boxSize, tigrRGB(0, 200, 0));
        tigrPrint(current_screen, tfont, bufferX + 55, coords[(item_index-page_index*10) % 10] + 2, tigrRGB(255, 0, 0), "%d", item_index);

    }
}

void Waltr::openVectorWindow() {
    //Order of vectors displayed may need to be flipped
    //tigrClear(screen, tigrRGB(0,0,0));
    
    
    current_screen = tigrWindow(screenX, screenY, (char*)"Your Vector!", 0);
    
    //Used to iterate over vector log
    vector_index = 0;

    //Used to iterate through current vector
    item_index = 0;

    //Used to iterate through pages
    page_index = 0;

    //sort box dimensions
    int sortboxWidth = 45;
    int sortboxHeight = 20;
    int sortboxX = 260;

    //prints initial vector and instance number
    drawVector();
    tigrUpdate(current_screen);
    while (!tigrClosed(current_screen) && !tigrKeyDown(current_screen, TK_ESCAPE)) {
        if (tigrKeyDown(current_screen, TK_UP)  && vector_index < vector_log.size()-1) {
            vector_index++;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVector();
        }
        if (tigrKeyDown(current_screen, TK_DOWN) && vector_index > 0) {
            vector_index--;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVector();
        }

        if (tigrKeyDown(current_screen, TK_RIGHT) && item_index < vector_log[vector_index].size()-1) {
            item_index++;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVector();
        }

        if (tigrKeyDown(current_screen, TK_LEFT) && item_index > 0) {
            item_index--;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVector();
        }
        
        if (tigrKeyDown(current_screen, 'Z') && page_index > 0 ) {
            page_index--;
            item_index = page_index*10;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVector();
        }

        if (tigrKeyDown(current_screen, 'X') && page_index + 1 <= vector_log[vector_index].size() / 10) {
            page_index++;
            item_index = page_index*10;
            if (item_index == vector_log[vector_index].size())
                { 
                    item_index--;   
                }
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVector();
        }

        if (tigrKeyDown(current_screen, 'H') && help_screen_open == false) {
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVHelp();
            help_screen_open = true;
        }

        tigrMouse(current_screen, &mouseX, &mouseY, &buttons); // get mouse coordinates
        for(int i=page_index*10; i < (size < 10 ? size: 10 + page_index*10) ; i++) { // test if mouse coordinates are within array boxes
            if(mouseX > coords[(i-page_index*10) % 10] - 7 && mouseX < (coords[(i-page_index*10) % 10] + boxSize) - 7 && mouseY > bufferY && mouseY < (bufferY+boxSize)) {
                if(buttons & 1) { // if mouse button clicked
                    item_index = i;
                    tigrClear(current_screen,tigrRGB(0,0,0));
                    drawVector();
                }
            }
        }
        
        //when instance is not empty
        if(vector_index > 0 && help_screen_open == false) {
            tigrPrint(current_screen, tfont, 265, 150, tigrRGB(255,0,0), "Sort: " );
            tigrFillRect(current_screen, sortboxX, 170, 45, sortboxHeight, tigrRGB(38,252,66));
            tigrPrint(current_screen, tfont, (260+5), (170+4), tigrRGB(255,0,0), "Asc");
            tigrFillRect(current_screen, sortboxX, 195, 45, sortboxHeight, tigrRGB(38,252,66));
            tigrPrint(current_screen, tfont, (260+5), (195+7), tigrRGB(255,0,0), "Desc");
            if(mouseX > sortboxX && mouseX < (sortboxX + sortboxWidth) && mouseY > 170 && mouseY < (170 + sortboxHeight)){
                if(buttons & 1){
                    tigrFillRect(current_screen, sortboxX, 170, 45, sortboxHeight, tigrRGB(0,0,255));
                    //tigrClear(current_screen, tigrRGB(0,0,0));
                    std::sort(vector_log[vector_index].begin(), vector_log[vector_index].end());
                    drawVector();
                }
            }
            if(mouseX > sortboxX && mouseX < (sortboxX + sortboxWidth) && mouseY > 195 && mouseY < (195 + sortboxHeight)){
                if(buttons & 1){
                    tigrFillRect(current_screen, sortboxX, 195, 45, sortboxHeight, tigrRGB(0,0,255));
                    //tigrClear(current_screen, tigrRGB(0,0,0));
                    std::sort(vector_log[vector_index].rbegin(), vector_log[vector_index].rend());
                    drawVector();
                }
            }
        }

        //sort box dimensions
        int sortboxWidth = 45;
        int sortboxHeight = 20;
        int sortboxX = 260;

        //if on last instance
        if(vector_index == (vector_log.size()-1)){
            tigrPrint(current_screen, tfont, 265, 150, tigrRGB(255,0,0), "Sort: " );
            tigrFillRect(current_screen, sortboxX, 170, 45, sortboxHeight, tigrRGB(38,252,66));
            tigrPrint(current_screen, tfont, (260+5), (170+4), tigrRGB(255,0,0), "Up");
            tigrFillRect(current_screen, sortboxX, 195, 45, sortboxHeight, tigrRGB(38,252,66));
            tigrPrint(current_screen, tfont, (260+5), (195+7), tigrRGB(255,0,0), "Down");
            if(mouseX > sortboxX && mouseX < (sortboxX + sortboxWidth) && mouseY > 170 && mouseY < (170 + sortboxHeight)){
                if(buttons & 1){
                    tigrFillRect(current_screen, sortboxX, 170, 45, sortboxHeight, tigrRGB(0,0,255));
                    tigrClear(current_screen, tigrRGB(0,0,0));
                    std::sort(vector_log[vector_index].begin(), vector_log[vector_index].end());
                    drawVector();
                }
            }
            if(mouseX > sortboxX && mouseX < (sortboxX + sortboxWidth) && mouseY > 195 && mouseY < (195 + sortboxHeight)){
                if(buttons & 1){
                    tigrFillRect(current_screen, sortboxX, 195, 45, sortboxHeight, tigrRGB(0,0,255));
                    tigrClear(current_screen, tigrRGB(0,0,0));
                    std::sort(vector_log[vector_index].rbegin(), vector_log[vector_index].rend());
                    drawVector();
                }
            }
        }




        tigrUpdate(current_screen);
    }
    tigrFree(current_screen);
}

void Waltr::openQueueWindow() {
    //Order of vectors displayed may need to be flipped
    //tigrClear(screen, tigrRGB(0,0,0));
    
    current_screen = tigrWindow(screenX, screenY, (char*)"Your Queue!", 0);
    
    //Used to iterate through current vector
    item_index = 0;

    //Used to iterate through queue instances
    queue_index = 0;

    //Used to iterate through pages
    page_index = 0;

    //prints initial vector and instance number
    drawQueue();
    tigrUpdate(current_screen);
    while (!tigrClosed(current_screen) && !tigrKeyDown(current_screen, TK_ESCAPE)) {
        if (tigrKeyDown(current_screen, TK_RIGHT)  && queue_index < queue_log.size()-1) {
            queue_index++;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawQueue();
        }
        if (tigrKeyDown(current_screen, TK_LEFT) && queue_index > 0) {
            queue_index--;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawQueue();
        }
        if (tigrKeyDown(current_screen, TK_DOWN) && item_index < queue_log[queue_index].size()-1) {
            item_index++;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawQueue();
        }
        if (tigrKeyDown(current_screen, TK_UP) && item_index > 0) {
            item_index--;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawQueue();
        }
        
        if (tigrKeyDown(current_screen, 'Z') && page_index > 0 ) {
            page_index--;
            item_index = page_index*10;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawQueue();
        }
        
        if (tigrKeyDown(current_screen, 'X') && page_index + 1 <= queue_log[queue_index].size() / 10) {
            page_index++;
            item_index = page_index*10;
            if (item_index == queue_log[queue_index].size())
                {       
                    item_index--;   
                }
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawQueue();
        }

        if (tigrKeyDown(current_screen, 'H') && help_screen_open == false) {
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVHelp();
            help_screen_open = true;
        }
        
        tigrMouse(current_screen, &mouseX, &mouseY, &buttons); // get mouse coordinates
        for(int i=page_index*10; i < (size < 10 ? size: 10 + page_index*10) ; i++) { // test if mouse coordinates are within array boxes
            if (mouseX > bufferX && mouseX < (bufferX + 50) && mouseY > coords[(i-page_index*10) % 10] && mouseY < (coords[(i-page_index*10) % 10]+boxSize)) {
                if(buttons & 1) { // if mouse button clicked
                    item_index = i;
                    tigrClear(current_screen,tigrRGB(0,0,0));
                    drawQueue();
                }
            }
        }

        tigrUpdate(current_screen);
    }
    tigrFree(current_screen);
}

void Waltr::openStackWindow() {
    //Order of vectors displayed may need to be flipped
    //tigrClear(screen, tigrRGB(0,0,0));
    
    current_screen = tigrWindow(screenX, screenY, (char*)"Your Stack!", 0);
    
    //Used to iterate through current vector
    item_index = 0;

    //Used to iterate through stack instances
    stack_index = 0;

    //Used to iterate through pages
    page_index = 0;

    //prints initial vector and instance number
    drawStack();
    tigrUpdate(current_screen);
    while (!tigrClosed(current_screen) && !tigrKeyDown(current_screen, TK_ESCAPE)) {
        if (tigrKeyDown(current_screen, TK_RIGHT)  && stack_index < stack_log.size()-1) {
            stack_index++;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawStack();
        }
        if (tigrKeyDown(current_screen, TK_LEFT) && stack_index > 0) {
            stack_index--;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawStack();
        }
        if (tigrKeyDown(current_screen, TK_DOWN) && item_index < stack_log[stack_index].size()-1) {
            item_index++;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawStack();
        }
        if (tigrKeyDown(current_screen, TK_UP) && item_index > 0) {
            item_index--;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawStack();
        }
        
        if (tigrKeyDown(current_screen, 'Z') && page_index > 0 ) {
            page_index--;
            item_index = page_index*10;
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawStack();
        }

         if (tigrKeyDown(current_screen, 'H') && help_screen_open == false) {
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawVHelp();
            help_screen_open = true;
        }
        
        if (tigrKeyDown(current_screen, 'X') && page_index + 1 <= stack_log[stack_index].size() / 10) {
            page_index++;
            item_index = page_index*10;
            if (item_index == stack_log[stack_index].size())
                {
                    item_index--;   
                }
            tigrClear(current_screen,tigrRGB(0,0,0));
            drawStack();
        }

        tigrMouse(current_screen, &mouseX, &mouseY, &buttons); // get mouse coordinates
        for(int i=page_index*10; i < (size < 10 ? size: 10 + page_index*10) ; i++) { // test if mouse coordinates are within array boxes
            if (mouseX > bufferX && mouseX < (bufferX + 50) && mouseY > coords[(i-page_index*10) % 10] && mouseY < (coords[(i-page_index*10) % 10]+boxSize)) {
                if(buttons & 1) { // if mouse button clicked
                    item_index = i;
                    tigrClear(current_screen,tigrRGB(0,0,0));
                    drawStack();
                }
            }
        }
        
        tigrUpdate(current_screen);
    }
    tigrFree(current_screen);
}

/*void sortVecUp(){
    logVector(std::sort(vec))

}*/





Waltr::~Waltr() {
    if (!vector_log.empty()) {
        openVectorWindow(); 
        //openVectorWindowMouse();   
    }
    if (!stack_log.empty()) {
        openStackWindow();
    }
    if (!queue_log.empty()) {
        openQueueWindow();
    }
}
