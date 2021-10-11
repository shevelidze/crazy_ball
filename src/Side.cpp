#include "Side.hpp"

namespace cbg
{
    Side::Side(const bool &topBlock, const bool &rightBlock, const bool &bottomBlock, const bool &leftBlock)
    {
        this->bottomBlock = bottomBlock;
        this->topBlock = topBlock;
        this->rightBlock = rightBlock;
        this->leftBlock = leftBlock;
    }
    bool Side::operator==(const Side &a) const
    {
        return a.topBlock == this->topBlock &&
               a.rightBlock == this->rightBlock &&
               a.bottomBlock == this->bottomBlock &&
               a.leftBlock == this->leftBlock;
    }
    bool Side::operator!=(const Side &a) const
    {
        return !(*this == a);
    }
    Side Side::operator=(const Side &a)
    {
        this->topBlock = a.topBlock;
        this->rightBlock = a.rightBlock;
        this->bottomBlock = a.bottomBlock;
        this->leftBlock = a.leftBlock;
        return *this;
    }
    Side Side::getInverted() const
    {
        Side inverted = *this;
        std::swap(inverted.topBlock, inverted.bottomBlock);
        std::swap(inverted.leftBlock, inverted.rightBlock);
        return inverted;
    }

}