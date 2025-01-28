#ifndef SETCLASS_H
#define SETCLASS_H

#include <cstddef>
#include <random>
#include <set>
#include <string>

class NumberSequence
{
    public:
    NumberSequence(size_t input);
    NumberSequence(NumberSequence&&) = delete;
    NumberSequence(const NumberSequence&) = delete;
    NumberSequence& operator=(const NumberSequence) = delete;
    ~NumberSequence() = default;

    std::string& getString();
    void genSequence();
    void seqToString();
    void Run();

    private:
    std::random_device mRd;
    std::mt19937 mSeed;
    size_t mNumOfElements;
    std::set<size_t> mSequenceSet;
    std::string mSeqString;
};

#endif // !SETCLASS_H
