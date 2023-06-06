#pragma once
#include <pybind11/pybind11.h>

struct ReadBenchmark
{
    float readObjectsMs;
    float fullUpdateMs;


    inline py::dict ToPyDict()
    {
        py::dict obj;
        obj["readObjectsMs"] = readObjectsMs;
        obj["fullUpdateMs"] = fullUpdateMs;
        return obj;
    }
};