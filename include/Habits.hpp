#pragma once

#include <string>
#include <vector>

class Habits {

    private:
    std::string habitName;

    public:
    explicit Habits();
    explicit Habits(std::string habitName);
    static const Habits brushTeeth;
    static const Habits exercise;
    static const Habits cookMeal;
    static const Habits journalling;

    void setName(std::string habitName);

    std::string getName() const;
    static std::vector<Habits> getAllHabits();

    // Equality operator for unordered_map
    bool operator==(const Habits& other) const {
        return habitName == other.habitName;
    }

};

// Custom hash function specialization for Habits
namespace std {
    template<>
    struct hash<Habits> {
        std::size_t operator()(const Habits& habit) const {
            return hash<string>()(habit.getName());
        }
    };
}
