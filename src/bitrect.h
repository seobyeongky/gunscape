//////////////////////////////////////////////////////////////////////////////////////////////////
//
// 파일이름: BitRect.h
//
// 내용: 비트배열을 저장하는 클래스
//
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef  __BITRECT_H__
#define  __BITRECT_H__

class BitRect
{
	const int width;
	const int height;
	int **bit_field;

	static const int int_bit;

public:
	BitRect(int width_, int height_);
	~BitRect();
	bool GetBit(int x_, int y_)
	{
		if(x_ < 0 || y_ < 0 || x_ >= width || y_ >= height)
			return false;
		return (bit_field[x_][y_/int_bit] & (1 << (y_ % int_bit))) != 0;
	}
	void SetBit(int x_, int y_)
	{
		bit_field[x_][y_/int_bit] |= 1 << (y_ % int_bit);
	}
	void UnSetBit(int x_, int y_)
	{
		bit_field[x_][y_/int_bit] &= ~(1 << (y_ % int_bit));
	}

	void AllUnset();

};



#endif // __BITRECT_H__