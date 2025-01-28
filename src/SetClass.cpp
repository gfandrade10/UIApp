#include "SetClass.h"
#include <cstddef>
#include <random>
#include <set>
#include <sstream>
#include <string>

NumberSequence::NumberSequence(size_t input)
: mNumOfElements(input), mSeed(mRd()) { }

std::wstring& NumberSequence::getString()
{
    return mSeqString;
}

void NumberSequence::genSequence()
{
    std::uniform_int_distribution<> generator(1,60);
    while(true)
    {
        if(mSequenceSet.size() == mNumOfElements)
            break;

        mSequenceSet.insert(generator(mSeed));
    }
}

void NumberSequence::seqToString()
{
    std::wostringstream os;
    for (const auto& it:mSequenceSet)
        os << it << L" ";
    
    auto tempString = os.str();
    tempString.pop_back();
    mSeqString.assign(tempString.begin(), tempString.end());
}


void NumberSequence::Run()
{
    genSequence();
    seqToString();
}
