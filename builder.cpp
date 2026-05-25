#include <iostream>

class Character {
private:
    std::string weapon;
    std::string armor;
public:
    void setWeapon(const std::string& w) { weapon = w; }
    void setArmor(const std::string& a) { armor = a; }

    void show() const {
        std::cout << "Weapon: " << weapon << ", Armor: " << armor << std::endl;
    }
};

class CharacterBuilder {
public:
    virtual ~CharacterBuilder() = default;
    virtual void buildWeapon() = 0;
    virtual void buildArmor() = 0;
    virtual std::shared_ptr<Character> getCharacter() = 0;
};

class SwordsmanBuilder : public CharacterBuilder {
private:
    std::shared_ptr<Character> character;
public:
    SwordsmanBuilder() {
        character = std::make_shared<Character>();
    }

    void buildWeapon() override {
        character->setWeapon("Sword");
        std::cout << "Build weapon:Sword\n";
    }

    void buildArmor() override {
        character->setArmor("Armor");
        std::cout << "Build armor:Armor\n";
    }

    std::shared_ptr<Character> getCharacter() override {
        return character;
    }
};

class CharacterDirector {
private:
    std::shared_ptr<CharacterBuilder> builder;
public:
    CharacterDirector(std::shared_ptr<CharacterBuilder> b) : builder(b) {}

    void createCharacter() {
        builder->buildWeapon();
        builder->buildArmor();
    }
};

int main() {
    auto builder = std::make_shared<SwordsmanBuilder>();
    CharacterDirector director(builder);

    director.createCharacter();
    auto character = builder->getCharacter();
    character->show();
}

