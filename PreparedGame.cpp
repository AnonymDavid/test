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
    
    for (auto mc : monsterChars) {
        std::vector<MarkedMap::unitPos> mpos = mm->getMonsterPositions(mc);

        for (auto m : mpos) {
            std::string monsterKey = "monster-";
            monsterKey += mc;
            
            Monster mcMonster = Monster::parse(gameJSON.get<std::string>(monsterKey));
            this->putMonster(mcMonster, m.posx, m.posy);
        }
    }

}