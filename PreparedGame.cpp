#include "PreparedGame.h"

void PreparedGame::loadGame(std::string fileName) {
    std::cout << "PrepairedGame loadGame method" << std::endl;
    JSON gameJSON = JSON::parseFromFile(fileName);

    std::cout << "file loaded" << std::endl;

    this->setMap(new MarkedMap(gameJSON.get<std::string>("map")));

    std::cout << "map set" << std::endl;

    MarkedMap* mm = dynamic_cast<MarkedMap*>(gameMap);

    std::cout << "got map" << std::endl;

    this->putHero(Hero::parse(gameJSON.get<std::string>("hero")), mm->getHeroPosition().posx,mm->getHeroPosition().posy);

    std::cout << "put hero" << std::endl;
    
    std::vector<char> monsterChars = mm->getMonsterChars();

    std::cout << "got monsterChars" << std::endl;
    
    for (auto mc : monsterChars) {
        std::cout << "current monsterChar: " << mc << std::endl;
        std::vector<MarkedMap::unitPos> mpos = mm->getMonsterPositions(mc);

        std::cout << "got monsterpos" << std::endl;

        for (auto m : mpos) {
            std::string monsterKey = "monster-";
            monsterKey += mc;
            std::cout << "\tmonsterkey: " << monsterKey << std::endl;

            std::cout << "\tmonsterFileName: " << gameJSON.get<std::string>(monsterKey) << std::endl;
            
            Monster mcMonster = Monster::parse(gameJSON.get<std::string>(monsterKey));
            this->putMonster(mcMonster, m.posx, m.posy);

            std::cout << "\n\nDONE\n\n" << std::endl;
        }
    }

}