#pragma once

class RenderContext
{
public:
	void SetData()
	{

	}

	bool operator<(RenderContext rhs)
	{
		return _bitfield < rhs._bitfield;
	}

	bool operator>(RenderContext rhs)
	{
		return _bitfield > rhs._bitfield;
	}

private:
	uint64_t _bitfield;
};