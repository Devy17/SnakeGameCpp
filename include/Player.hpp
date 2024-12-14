#ifndef PLAYER_H
#define PLAYER_H

class Player {
    private:
        COORD head;
        int length;
        COORD body[1024];
        

    public:
        COORD GetHead();
        int GetLength();
        void AddPoint();
        void Move();
        
}; 

#endif