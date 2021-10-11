#ifndef SIDE_H
#define SIDE_H
#pragma once

#include <utility>


namespace cbg
{
	class Side
	{
	private:
		bool topBlock, rightBlock, bottomBlock, leftBlock;

	public:
		Side(const bool &topBlock, const bool &rightBlock, const bool &bottomBlock, const bool &leftBlock);
		bool operator==(const Side &a) const;
		bool operator!=(const Side &a) const;
		Side operator=(const Side &a);
		Side getInverted() const;
	};
}
#endif