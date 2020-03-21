//
// Created by root on 21.03.20.
//

#ifndef GAMEOFLIFE_RINGBUFFER_H
#define GAMEOFLIFE_RINGBUFFER_H


class RingBuffer {
public:

    RingBuffer(unsigned maxSize)
    {
       count = 0;
       MaxSize = maxSize;
    }
    void add(float elem) {
        if ( count == MaxSize)
        {
            count = 0;

        }
        buffer[count] = elem;
        count++;

    }

    void clearBuffer() {
        for (int i = 0;i<MaxSize;i++)
        {
            buffer[i] = 0;
        }
    }
    float * getBufferArray()
    {
        return buffer;
    }

private:
    unsigned MaxSize;
    float buffer[100] = {0};
    unsigned count;


};


#endif //GAMEOFLIFE_RINGBUFFER_H
