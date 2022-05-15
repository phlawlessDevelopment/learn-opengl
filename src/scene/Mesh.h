#pragma once
class QuadMesh
{
private:
    static inline float m_Positions[16] = {
                                            0.0f, 1.0f, 0.0f, 0.0f, //top left
                                            1.0f, 1.0f, 1.0f, 0.0f, //top right
                                            1.0f, 0.0f, 1.0f, 1.0f, //bot right
                                            0.0f, 0.0f, 0.0f, 1.0f, //bot left
                                           };
    static inline unsigned int m_Indicies[6] = {
         0,1,2,2,3,0,
    };
public:
    static const int PosCount = 32;
    static const int IndexCount = 6;
    static const inline float* GetPositions(){return m_Positions;}
    static const inline unsigned int* GetIndices(){return m_Indicies;}
    QuadMesh();
    ~QuadMesh();
};


