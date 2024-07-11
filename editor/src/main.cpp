#include <iostream>

#include <zeronetics/zeronetics.h>

int main() {
    std::cout << "Zeronetics Editor " << ZEN::EngineInfo::getVersion().toSemVer() << std::endl;
}
