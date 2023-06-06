#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>

#include "unit/GameObject.h"
#include "Benchmarks.h"

namespace py = pybind11;

struct Snapshot
{
    std::vector<std::shared_ptr<GameObject>> champions;
    std::vector<std::shared_ptr<GameObject>> jungle;
    std::vector<std::shared_ptr<GameObject>> turrets;
    std::vector<std::shared_ptr<GameObject>> inhibitors;
    std::vector<std::shared_ptr<GameObject>> other;

    std::string nextDragonType;

    std::map<int, std::shared_ptr<GameObject>> objectMap;
    std::map<short, int> indexToNetId;

    std::set<int> updatedObjects;

    float gameTime = 0.f;

    std::unique_ptr<ReadBenchmark> benchmark = std::unique_ptr<ReadBenchmark>(new ReadBenchmark());

    py::dict ToPyDict()
    {
        py::dict obj;

        py::list champions(this->champions.size());
        for (int i = 0; i < this->champions.size(); i++)
        {
            champions[i] = this->champions[i]->ToPyDict();
        }
        obj["champions"] = champions;

        py::list jungle(this->jungle.size());
        for (int i = 0; i < this->jungle.size(); i++)
        {
            jungle[i] = this->jungle[i]->ToPyDict();
        }
        obj["jungle"] = jungle;

        py::list turrets(this->turrets.size());
        for (int i = 0; i < this->turrets.size(); i++)
        {
            turrets[i] = this->turrets[i]->ToPyDict();
        }
        obj["turrets"] = turrets;

        py::list inhibitors(this->inhibitors.size());
        for (int i = 0; i < this->inhibitors.size(); i++)
        {
            inhibitors[i] = this->inhibitors[i]->ToPyDict();
        }
        obj["inhibitors"] = inhibitors;

        py::list other(this->other.size());
        for (int i = 0; i < this->other.size(); i++)
        {
            other[i] = this->other[i]->ToPyDict();
        }
        obj["other"] = other;

        obj["gameTime"] = py::float_(this->gameTime);

        obj["nextDragonType"] = py::str(this->nextDragonType);
        return obj;
    }
};

struct ChampionSnapshot
{
    std::vector<std::shared_ptr<GameObject>> champions;

    float gameTime = 0.f;

    std::unique_ptr<ReadBenchmark> benchmark = std::unique_ptr<ReadBenchmark>(new ReadBenchmark());
};