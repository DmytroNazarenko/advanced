#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
typedef long long ll;


void input(int &n, int &m, int &d, std::vector<int> &l) {
    std::cin >> m >> d >> n;
    for (int counter = 0; counter < n; ++counter) {
        int _k;
        std::cin >> _k;
        l.push_back(_k);
    }
}

int maxPeopleCount[110][310][310];

int findMaxPeopleCount(int people, int buses, int busCapacity, std::vector<int> peopleVolumes) {
    maxPeopleCount[0][0][0] = 0;
    for (int filledBusesCount = 0; filledBusesCount < buses; ++filledBusesCount) {
        for (int analyzedPeopleCount = 0; analyzedPeopleCount <= people; ++analyzedPeopleCount) {
            if (filledBusesCount != 0)
                maxPeopleCount[filledBusesCount][analyzedPeopleCount][0] =
                maxPeopleCount[filledBusesCount - 1][analyzedPeopleCount][busCapacity];
            else
                maxPeopleCount[filledBusesCount][analyzedPeopleCount][0] = 0;
            for (int usedVolumeInBus = 1; usedVolumeInBus <= busCapacity; ++usedVolumeInBus) {
                maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus] =
                    maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus - 1];
                if (analyzedPeopleCount > 0)
                    maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus] =
                    std::max(maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus],
                        maxPeopleCount[filledBusesCount][analyzedPeopleCount - 1][usedVolumeInBus]);

                if (analyzedPeopleCount > 0 && usedVolumeInBus >= peopleVolumes[analyzedPeopleCount - 1])
                    maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus] =
                    std::max(maxPeopleCount[filledBusesCount][analyzedPeopleCount][usedVolumeInBus],
                        maxPeopleCount[filledBusesCount][analyzedPeopleCount - 1][usedVolumeInBus
                        - peopleVolumes[analyzedPeopleCount - 1]] + 1);
            }
        }
    }
    return  maxPeopleCount[buses - 1][people][busCapacity];
}

int main()
{
    std::vector<int> L;
    int N, M, D;
    input(N, M, D, L);
    std::cout << findMaxPeopleCount(N, M, D, L);
}
