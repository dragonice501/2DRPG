#pragma once

struct Vec2
{
    float x;
    float y;

    Vec2();
    Vec2(const float v);
    Vec2(const float x, const float y);
    
    ~Vec2() = default;

    void Add(const Vec2& v);               
    void Sub(const Vec2& v);               
    void Scale(const float n);             
    Vec2 Rotate(const float angle) const;  

    float Magnitude() const;               
    float MagnitudeSquared() const;        

    Vec2& Normalize();                     
    Vec2 UnitVector() const;               
    Vec2 Normal() const;                   

    float Dot(const Vec2& v) const;        
    float Cross(const Vec2& v) const;

    static Vec2 Lerp(const Vec2& start, const Vec2& end, float rate);

    Vec2& operator = (const Vec2& v);      
    bool operator == (const Vec2& v) const;
    bool operator != (const Vec2& v) const;
    
    Vec2 operator + (const Vec2& v) const; 
    Vec2 operator - (const Vec2& v) const; 
    Vec2 operator * (const float n) const; 
    Vec2 operator / (const float n) const; 
    Vec2 operator - ();                    

    Vec2& operator += (const Vec2& v);     
    Vec2& operator -= (const Vec2& v);     
    Vec2& operator *= (const float n);     
    Vec2& operator /= (const float n);     
};