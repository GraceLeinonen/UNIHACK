#pragma once

#include <string>
#include <vector>

class Habits {

    private:
    std::string habitName;

    public:
    explicit Habits(std::string habitName);
    static const Habits brushTeeth;
    static const Habits exercise;
    static const Habits cookMeal;
    static const Habits noPhone;

    std::string getName();
    static std::vector<Habits> getAllHabits();

};

