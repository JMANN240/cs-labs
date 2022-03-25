// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
   Fill(char fillChar):fillChar_(fillChar){}
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char fillChar_;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char fillChar):Fill(fillChar){}
   char getBorder() override {return fillChar_;}
   char getInternal() override {return ' ';}
   ~Hollow(){}
};



// another concrete body
class Filled: public Fill {
public:
   Filled(char fillChar):Fill(fillChar){}
   char getBorder() override {return fillChar_;}
   char getInternal() override {return fillChar_;}
   ~Filled(){}
};

class EnhancedFilled: public Filled {
public:
   EnhancedFilled(char fillChar, char borderChar):Filled(fillChar), borderChar_(borderChar){}
   char getInternal() override {return borderChar_;}
   ~EnhancedFilled(){}
private:
   char borderChar_;
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw()=0;
   virtual void changeFill(Fill* const newFill) { fill_ = newFill; }
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};


void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
   if(i==0 || j==0 || i==size_-1 || j==size_-1 )
      cout << fill_ -> getBorder();
   else
      cout << fill_ -> getInternal();
      cout << endl;
   }
}


int main(){
   Fill* starFilled = new Filled('*');
   Fill* starHollow = new Hollow('*');
   Fill* starBarEnhancedFilled = new EnhancedFilled('*', '|');
   Figure *userBox = new Square(10, starFilled); 
   cout << "Star Filled" << endl;
   userBox -> draw();
   cout << endl;
   userBox -> changeFill(starHollow);
   cout << "Star Hollow" << endl;
   userBox -> draw();
   cout << endl;
   userBox -> changeFill(starBarEnhancedFilled);
   cout << "Star Border with Bar Fill" << endl;
   userBox -> draw();
   cout << endl;
}
