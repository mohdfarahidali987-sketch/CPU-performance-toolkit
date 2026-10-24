
#ifndef CSV_EXPORTER_HPP
#define CSV_EXPORTER_HPP

#include "BenchmarkResult.hpp"
#include <string>
#include <vector>

class CSVExporter {
public:
    bool exportResults(
        const std::vector<BenchmarkResult>& results,
        const std::string& filename
    ) const;
};

#endif
