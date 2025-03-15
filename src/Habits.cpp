#include "Habits.hpp"

Habits::Habits(std::string habitName) {
    this->habitName = habitName;
}

std::string Habits::getName() {

    return this->habitName;
}

std::vector<Habits> Habits::getAllHabits() {
    std::vector<Habits> allHabits;
    allHabits.push_back(brushTeeth);
    allHabits.push_back(exercise);
    allHabits.push_back(cookMeal);
    allHabits.push_back(noPhone);

    return allHabits;
    
}

//initialise habits
const Habits Habits::brushTeeth("brushTeeth");
const Habits Habits::exercise("exercise");
const Habits Habits::cookMeal("cookMeal");
const Habits Habits::noPhone("noPhone");
