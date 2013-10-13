//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: rect.cpp
//
// 내용: 사각형 반복자
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "rect.h"
#include <algorithm>



rect_iterator::rect_iterator(const coord_int &start_, int x_size_, int y_size_):
start(start_),current(start_.x-x_size_,start_.y-y_size_),x_size(x_size_),y_size(y_size_)
{}
coord_int rect_iterator::operator *() const
{
    return current;
}
const coord_int* rect_iterator::operator->() const
{
    return &current;
}
rect_iterator& rect_iterator::operator ++()
{
	current.x++;
	if(current.x>start.x+x_size)
	{
		current.x = start.x-x_size;
		current.y++;		
	}
    return *this;
}
rect_iterator rect_iterator::operator++( int dummy )
{
    const rect_iterator copy = *this;
    ++(*this);
    return (copy);
}
bool rect_iterator::end()
{
	return (current.y>start.y+y_size);
}
bool rect_iterator::isdiagonal()
{
	return (current.x != start.x && current.y != start.y);
}	

