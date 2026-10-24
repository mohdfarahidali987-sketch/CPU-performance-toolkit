
#include "CSVExporter.hpp"

#include <fstream>

bool CSVExporter::exportResults(
    const std::vector<BenchmarkResult>& results,
    const std::string& filename
) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    file << "Mode,Iterations,Threads,TimeMs,Checksum\n";

    for (const auto& result : results) {
        file << result.getMode() << ','
             << result.getIterations() << ','
             << result.getThreadCount() << ','
             << result.getExecutionTimeMs() << ','
             << result.getChecksum() << '\n';
    }

    return file.good();
}
