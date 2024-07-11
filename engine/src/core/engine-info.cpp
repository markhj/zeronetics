#include "zeronetics/core/engine-info.h"

ZEN::Version ZEN::EngineInfo::getVersion() {
    return {0, 1, 0, ZEN::Version::Preview{"alpha", 2}};
}
