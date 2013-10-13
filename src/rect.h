//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: rect.h
//
// 내용: 사각형 반복자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __RECT_H__
#define  __RECT_H__

typedef struct coord_int
{
	int x;
	int y;

explicit coord_int( int x_in = 0, int y_in = 0 ) : x(x_in), y(y_in) { }

    void set(int xi, int yi)
    {
        x = xi;
        y = yi;
    }

    void reset()
    {
        set(0, 0);
    }

    int distance_from(const coord_int &b) const;

    bool operator == (const coord_int &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator != (const coord_int &other) const
    {
        return !operator == (other);
    }

    bool operator <  (const coord_int &other) const
    {
        return (x < other.x) || (x == other.x && y < other.y);
    }

    bool operator >  (const coord_int &other) const
    {
        return (x > other.x) || (x == other.x && y > other.y);
    }

    const coord_int &operator += (const coord_int &other)
    {
        x += other.x;
        y += other.y;
        return (*this);
    }

    const coord_int &operator += (int offset)
    {
        x += offset;
        y += offset;
        return (*this);
    }

    const coord_int &operator -= (const coord_int &other)
    {
        x -= other.x;
        y -= other.y;
        return (*this);
    }

    const coord_int &operator -= (int offset)
    {
        x -= offset;
        y -= offset;
        return (*this);
    }

    const coord_int &operator /= (int div)
    {
        x /= div;
        y /= div;
        return (*this);
    }

    const coord_int &operator *= (int mul)
    {
        x *= mul;
        y *= mul;
        return (*this);
    }

    coord_int operator + (const coord_int &other) const
    {
        coord_int copy = *this;
        return (copy += other);
    }

    coord_int operator + (int other) const
    {
        coord_int copy = *this;
        return (copy += other);
    }

    coord_int operator - (const coord_int &other) const
    {
        coord_int copy = *this;
        return (copy -= other);
    }

    coord_int operator -() const
    {
        return (coord_int(0, 0) - *this);
    }

    coord_int operator - (int other) const
    {
        coord_int copy = *this;
        return (copy -= other);
    }

    coord_int operator / (int div) const
    {
        coord_int copy = *this;
        return (copy /= div);
    }

    coord_int operator * (int mul) const
    {
        coord_int copy = *this;
        return (copy *= mul);
    }

    int abs() const
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

    bool equals(const int xi, const int yi) const
    {
        return (xi == x && yi == y);
    }
}coord_int;


class rect_iterator //원하는 사각형을 출력한다.
{
	coord_int start;
	coord_int current;
	int x_size;
	int y_size;

public:
	rect_iterator(const coord_int &start_, int x_size, int y_size);
	coord_int rect_iterator::operator *() const;
	const coord_int* rect_iterator::operator->() const;
	rect_iterator& operator ++ ();
	rect_iterator operator ++ (int);
	bool end();
	bool isdiagonal();
};



#endif // __RECT_H__