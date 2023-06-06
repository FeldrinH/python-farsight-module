#include <string>
#include "Farsight.h"
#include "Snapshot.h"
#include "windows.h"
#include "Offsets.h"
#include <chrono>
#include <pybind11/stl.h>

namespace py = pybind11;

Farsight f = Farsight();

py::dict makeSnapshot()
{
    if(!f.IsHooked()) {
        throw std::exception("Not hooked to League of Legends");
    }

    // Init variables and timer
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> readDuration;

    Snapshot s;

    f.CreateSnapshot(s);

    py::dict snapshot = s.ToPyDict();

    readDuration = std::chrono::high_resolution_clock::now() - start;
    s.benchmark->fullUpdateMs = readDuration.count();

    snapshot["benchmark"] = s.benchmark->ToPyDict();

    return snapshot;
}

void disconnectFromLeague()
{
    f.UnhookFromProcess();
    if (f.IsHooked()) {
        throw std::exception("Failed to unhook");
    }
}

void connectToLeague()
{
    f.HookToProcess();
}

void setOffsets(std::unordered_map<std::string, int32_t> &offsets)
{
    Offsets::GameTime = offsets["gameTime"];
    Offsets::ObjectManager = offsets["objectManager"];
    Offsets::ObjectMapCount = offsets["objectMapCount"];
    Offsets::ObjectMapRoot = offsets["objectMapRoot"];
    Offsets::ObjectMapNodeNetId = offsets["objectMapNodeNetId"];
    Offsets::ObjectMapNodeObject = offsets["objectMapNodeObject"];

    Offsets::HeroList = offsets["heroList"];
    Offsets::MinionList = offsets["minionList"];
    Offsets::TurretList = offsets["turretList"];
    Offsets::InhibitorList = offsets["inhibitorList"];

    Offsets::ObjIndex = offsets["objIndex"];
    Offsets::ObjTeam = offsets["objTeam"];
    Offsets::ObjNetworkID = offsets["objNetworkID"];
    Offsets::ObjPosition = offsets["objPosition"];
    Offsets::ObjHealth = offsets["objHealth"];
    Offsets::ObjMaxHealth = offsets["objMaxHealth"];
    Offsets::ObjMana = offsets["objMana"];
    Offsets::ObjMaxMana = offsets["objMaxMana"];
    Offsets::ObjName = offsets["objName"];
    Offsets::ObjNameLength = offsets["objNameLength"];
    Offsets::ObjLvl = offsets["objLvl"];
    Offsets::ObjExperience = offsets["objExperience"];
    Offsets::ObjCurrentGold = offsets["objCurrentGold"];
    Offsets::ObjTotalGold = offsets["objTotalGold"];
    Offsets::ObjDisplayName = offsets["objDisplayName"];
    Offsets::ObjDisplayNameLength = offsets["objDisplayNameLength"];
}

void setChampionNames(const std::vector<std::string> &championNames) {
    for (size_t i = 0; i < championNames.size(); i++) {
        std::string champion = championNames.at(i);
        Farsight::championNames.insert(champion);
    }
}

PYBIND11_MODULE(_impl, m) {
    m.attr("__name__") = "farsight._impl";
    m.def("makeSnapshot", &makeSnapshot);
    m.def("connectToLeague", &connectToLeague);
    m.def("disconnectFromLeague", &connectToLeague);
    m.def("setOffsets", &setOffsets);
    m.def("setChampionNames",&setChampionNames);
}