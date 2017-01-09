#include <iostream>
#include <algorithm>
#include <vector>


void input(std::istream &inputStream, int &people, int &buses, int &busCapacity, std::vector<int> &volumes) {
    inputStream >> buses >> busCapacity >> people;
    volumes.resize(people);
    for (int counter = 0; counter < people; ++counter) {
        inputStream >> volumes[counter];
    }
}

void output(std::ostream &outputStream, const int &answer) {
    outputStream << answer;
}


int findMaxPeopleCount(const int people, const int buses, const int busCapacity, const std::vector<int> peopleVolumes) {

    std::vector<std::vector<std::vector<int> > > maxPeopleCount(buses + 1, std::vector<std::vector<int> >(people + 1, std::vector<int>(busCapacity + 1)));

    maxPeopleCount[0][0][0] = 0;
    for (int filledBusesCount = 0; filledBusesCount < buses; ++filledBusesCount) {
        for (int analyzedPeopleCount = 0; analyzedPeopleCount <= people; ++analyzedPeopleCount) {
            if (filledBusesCount != 0) {
                maxPeopleCount[filledBusesCount][analyzedPeopleCount][0] =
                    maxPeopleCount[filledBusesCount - 1][analyzedPeopleCount][busCapacity];
            } else {
                maxPeopleCount[filledBusesCount][analyzedPeopleCount][0] = 0;
            }
            for (int usedVolumeInBus = 1; usedVolumeInBus <= busCapacity; ++usedVolumeInBus) {
                maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus] =
                    maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus - 1];
                if (analyzedPeopleCount > 0) {
                    maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus] =
                        std::max(maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus],
                            maxPeopleCount[filledBusesCount][analyzedPeopleCount - 1][usedVolumeInBus]
                                );
                }
                if (analyzedPeopleCount > 0 && usedVolumeInBus >= peopleVolumes[analyzedPeopleCount - 1]) {
                    maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus] =
                        std::max(maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus],
                            maxPeopleCount[
                                filledBusesCount
                            ][
                                analyzedPeopleCount - 1
                            ][
                                usedVolumeInBus - peopleVolumes[analyzedPeopleCount - 1]
                            ] + 1
                                );
                }
            }
        }
    }
    return  maxPeopleCount[buses - 1][people][busCapacity];
}

int main()
{
    std::vector<int> peopleVolumes;
    int peopleCount, busCount, busCapacity;
    input(std::cin, peopleCount, busCount, busCapacity, peopleVolumes);
    int answer = findMaxPeopleCount(peopleCount, busCount, busCapacity, peopleVolumes);
    output(std::cout, answer);
}
