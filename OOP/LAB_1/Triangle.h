#pragma once

class Triangle {
private:
    int a, b, c;
public:
    void SetABC(int a, int b, int c);
    void PrintTriangle();
    bool IsTriangle();
    bool Is90();
};
