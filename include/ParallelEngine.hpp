
#ifndef PARALLEL_ENGINE_HPP
#define PARALLEL_ENGINE_HPP

#include <cstdint>

class ParallelEngine {
private:
    unsigned int threadCount;

    std::uint64_t calculateWork(
        std::uint64_t start,
        std::uint64_t end
    ) const;

public:
    explicit ParallelEngine(unsigned int threadCount);

    std::uint64_t run(std::uint64_t iterations) const;
};

#endif
