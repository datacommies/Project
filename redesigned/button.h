typedef struct Button {
   Button()
   {
       static int idcounter = 1;
       ++idcounter;

       id = idcounter;
   }
   sf::RectangleShape rect;
   int id;
   bool operator== (Button & right) {
      return (id == right.id);
   }

   bool operator< (const Button & right) const {
      return (id - right.id);
   }
};