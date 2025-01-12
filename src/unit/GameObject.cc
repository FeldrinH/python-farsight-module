#include "GameObject.h"
#include "../Utils.h"
#include "../Farsight.h"
#include "../Offsets.h"
#include <vector>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

namespace py = pybind11;

BYTE GameObject::buff[GameObject::sizeBuff] = {};
BYTE GameObject::buffDeep[GameObject::sizeBuffDeep] = {};

bool GameObject::IsEqualTo(const GameObject &other) const
{
    return this->objectIndex == other.objectIndex;
}

bool GameObject::IsNotEqualTo(const GameObject &other) const
{
    return this->objectIndex != other.objectIndex;
}

void GameObject::LoadFromMemory(DWORD64 base, HANDLE hProcess, bool deepLoad)
{
    baseAddress = base;
    Memory::Read(hProcess, base, buff, sizeBuff);

    memcpy(&networkId, &buff[Offsets::ObjNetworkID], sizeof(DWORD));
    memcpy(&objectIndex, &buff[Offsets::ObjIndex], sizeof(short));
    memcpy(&team, &buff[Offsets::ObjTeam], sizeof(short));
    memcpy(&position, &buff[Offsets::ObjPosition], sizeof(float) * 3);
    memcpy(&health, &buff[Offsets::ObjHealth], sizeof(float));
    memcpy(&maxHealth, &buff[Offsets::ObjMaxHealth], sizeof(float));
    memcpy(&mana, &buff[Offsets::ObjMana], sizeof(float));
    memcpy(&maxMana, &buff[Offsets::ObjMaxMana], sizeof(float));

    isAlive = health > 0;

    if (deepLoad)
    {
        int nameLength = Memory::ReadDWORD64FromBuffer(buff, Offsets::ObjNameLength);

        if (nameLength <= 0 || nameLength > 100) {}
        else if (nameLength < 16)
        {
            name.resize(nameLength);
            memcpy(name.data(), &buff[Offsets::ObjName], nameLength);
        }
        else
        {
            char nameBuff[50];
            Memory::Read(hProcess, Memory::ReadDWORD64FromBuffer(buff, Offsets::ObjName), nameBuff, 50);
            name.resize(nameLength);
            memcpy(name.data(), &nameBuff[0], nameLength);
        }

        int displayNameLength = Memory::ReadDWORD64FromBuffer(buff, Offsets::ObjDisplayNameLength);

        if (displayNameLength < 16)
        {
            displayName.resize(displayNameLength);
            memcpy(displayName.data(), &buff[Offsets::ObjDisplayName], displayNameLength);
        }
        else
        {
            char displayNameBuff[50];
            Memory::Read(hProcess, Memory::ReadDWORD64FromBuffer(buff, Offsets::ObjDisplayName), displayNameBuff, 50);
            displayName.resize(displayNameLength);
            memcpy(displayName.data(), &displayNameBuff[0], displayNameLength);
        }
    }
}

void GameObject::LoadChampionData()
{
    isChampion = true;
    memcpy(&experience, &buff[Offsets::ObjExperience], sizeof(float));
    memcpy(&level, &buff[Offsets::ObjLvl], sizeof(int));
    memcpy(&currentGold, &buff[Offsets::ObjCurrentGold], sizeof(float));
    memcpy(&totalGold, &buff[Offsets::ObjTotalGold], sizeof(float));
}

bool GameObject::IsChampion()
{
    return isChampion;
}

py::dict GameObject::ToPyDict()
{
    py::dict obj;
    obj["name"] = PyUnicode_DecodeUTF8(name.data(), name.size(), "replace");
    obj["displayName"] = PyUnicode_DecodeUTF8(displayName.data(), displayName.size(), "replace");
    obj["networkId"] = networkId;
    obj["objectIndex"] = objectIndex;
    py::tuple jsPosition = py::make_tuple(
        position[0],
        position[1],
        position[2]
    );
    obj["position"] = jsPosition;
    obj["team"] = team;
    obj["isAlive"] = isAlive;
    obj["health"] = health;
    obj["maxHealth"] = maxHealth;
    obj["mana"] = mana;
    obj["maxMana"] = maxMana;

    if (!isChampion)
        return obj;

    obj["currentGold"] = currentGold;
    obj["totalGold"] = totalGold;
    obj["experience"] = experience;
    obj["level"] = level;

    return obj;
}