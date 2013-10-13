//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: coord_def.h
//
// 내용: 좌표처리
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __COORD_DEF_H__
#define  __COORD_DEF_H__


struct coord_def
{
    float x;
    float y;

    explicit coord_def( float x_in = 0, float y_in = 0 ) : x(x_in), y(y_in) { }

    void set(float xi, float yi)
    {
        x = xi;
        y = yi;
    }

    void reset()
    {
        set(0, 0);
    }

    int distance_from(const coord_def &b) const;

    bool operator == (const coord_def &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator != (const coord_def &other) const
    {
        return !operator == (other);
    }

    bool operator <  (const coord_def &other) const
    {
        return (x < other.x) || (x == other.x && y < other.y);
    }

    bool operator >  (const coord_def &other) const
    {
        return (x > other.x) || (x == other.x && y > other.y);
    }

    const coord_def &operator += (const coord_def &other)
    {
        x += other.x;
        y += other.y;
        return (*this);
    }

    const coord_def &operator += (float offset)
    {
        x += offset;
        y += offset;
        return (*this);
    }

    const coord_def &operator -= (const coord_def &other)
    {
        x -= other.x;
        y -= other.y;
        return (*this);
    }

    const coord_def &operator -= (float offset)
    {
        x -= offset;
        y -= offset;
        return (*this);
    }

    const coord_def &operator /= (const coord_def &other)
    {
        x /= other.x;
        y /= other.y;
        return (*this);
    }

    const coord_def &operator /= (float div)
    {
        x /= div;
        y /= div;
        return (*this);
    }

    const coord_def &operator *= (const coord_def &other)
    {
        x *= other.x;
        y *= other.y;
        return (*this);
    }

    const coord_def &operator *= (float mul)
    {
        x *= mul;
        y *= mul;
        return (*this);
    }

    coord_def operator + (const coord_def &other) const
    {
        coord_def copy = *this;
        return (copy += other);
    }

    coord_def operator + (float other) const
    {
        coord_def copy = *this;
        return (copy += other);
    }

    coord_def operator - (const coord_def &other) const
    {
        coord_def copy = *this;
        return (copy -= other);
    }

    coord_def operator -() const
    {
        return (coord_def(0, 0) - *this);
    }

    coord_def operator - (float other) const
    {
        coord_def copy = *this;
        return (copy -= other);
    }

    coord_def operator / (const coord_def &other) const
    {
        coord_def copy = *this;
        return (copy /= other);
    }

    coord_def operator / (float div) const
    {
        coord_def copy = *this;
        return (copy /= div);
    }

    coord_def operator * (const coord_def &other) const
    {
        coord_def copy = *this;
        return (copy *= other);
    }

    coord_def operator * (float mul) const
    {
        coord_def copy = *this;
        return (copy *= mul);
    }

    float abs() const
    {
        return (x * x + y * y);
    }


    bool origin() const
    {
        return (!x && !y);
    }

    bool zero() const
    {
        return origin();
    }

    bool equals(const float xi, const float yi) const
    {
        return (xi == x && yi == y);
    }
};


float distan_coord(const coord_def& a, const coord_def& b);


float GetAngleToTarget(coord_def start, coord_def target);
float GetAngleToTarget180(coord_def start, coord_def target);



#endif // __COORD_DEF_H__