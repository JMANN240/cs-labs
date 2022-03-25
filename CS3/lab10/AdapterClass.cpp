// figures: class adapter pattern
// Mikhail Nesterenko
// 2/16/2014

#include <iostream>

using std::cout; using std::cin; using std::endl;

// base interface
class Figure {
public:
   virtual void draw()=0;
   virtual void resize(int newSize)=0; // Pure virtual function for resizing
   virtual ~Figure(){}
};

// adaptee/implementer
class LegacyRectangle{
public:
   LegacyRectangle(int topLeftX, 
		   int topLeftY, 
		   int bottomRightX, 
		   int bottomRightY): 
      topLeftX_(topLeftX), 
      topLeftY_(topLeftY), 
      bottomRightX_(bottomRightX), 
      bottomRightY_(bottomRightY){}

   void oldDraw(){
      for(int i=0; i < bottomRightY_; ++i){
	 for(int j=0; j < bottomRightX_; ++j)
	    if(i >= topLeftY_  && j >= topLeftX_ )
	       cout << '*';
	    else
	       cout << ' ';
	 cout << endl;
      }
   }

   void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
       topLeftX_ = topLeftX; // Set all of the new coordinates
       topLeftY_ = topLeftY;
       bottomRightX_ = bottomRightX;
       bottomRightY_ = bottomRightY;
   }

   int getTopLeftX() { return topLeftX_; } // Just some basic getters
   int getTopLeftY() { return topLeftY_; }
   int getBottomRightX() { return bottomRightX_; }
   int getBottomRightY() { return bottomRightY_; }
// defining top/left and bottom/right coordinates 
private: 
   int topLeftX_;
   int topLeftY_;
   int bottomRightX_;
   int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter: public Figure, 
		     private LegacyRectangle {
public:
   SquareAdapter(int size): LegacyRectangle(0,0,size,size) {};
   
   void draw() override {
      oldDraw();
   }

   int size() { // We know that the size is set to both of the bottomRight coords, so either would work
       return getBottomRightX();
   }

   void resize(int newSize) override { // Uses LegacyRectanle::move() in resize
       move(0, 0, newSize, newSize);
   }
};


int main(){
    int size;
    std::cout << "Please enter a size of a square: ";
    std::cin >> size;
    Figure *square = new SquareAdapter(size);
    square->draw();
    std::cout << "Please enter a new size: ";
    std::cin >> size;
    square->resize(size);
    square->draw();
}
