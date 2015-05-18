#pragma once


class scope
{
public:

    scope(){}

    scope(int _bufferLen)
    {
        bufferLen = _bufferLen;
        buffer.resize(bufferLen,0);
    }

    void setup(int _bufferLen)
    {
        bufferLen = _bufferLen;
        buffer.resize(bufferLen,0);
    }

    void add(float value)
    {
        buffer.push_back( value );

        if( buffer.size() >= bufferLen )
            buffer.erase(buffer.begin(), buffer.begin()+1);

    }

    void draw(int width, int height)
    {
        ofBeginShape();

        for (unsigned int i = 0; i < bufferLen; i++){
            float x =  ofMap(i, 0, bufferLen, 0, width, true);
            ofVertex(x, (1-buffer[i])*height);
        }

        ofEndShape(false);

    }

   unsigned int bufferLen;

   vector<float> buffer;



};
