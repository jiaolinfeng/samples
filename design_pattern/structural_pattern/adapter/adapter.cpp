/**
 * @file adapter.cpp
 * @brief adapter
 * @author JiaoLinfeng, jiaolinfeng@esunny.cc
 * @version 1.0
 * @date 2017-10-25
 */

#include <assert.h>
#include <iostream>
#include <memory>

class Armor
{
public:
    virtual ~Armor() {}

    virtual void work()
    {
        std::cout << "Normal armor protects hero from physical attack!"
                  << std::endl;
    }
};

class Hero
{
public:
    void wear(Armor *armor)
    {
        armor->work();
    }
};

class MagicArmor
{
public:
    void protectPhysicalAttack()
    {
        std::cout <<"New armor protects hero from physical attack!" <<std::endl;
    }

    void protectMagicAttack()
    {
        std::cout <<"New armor protects hero from magic attack!"<< std::endl;
    }
};

class MagicArmorAdapter : public Armor
{
public:
    MagicArmorAdapter(MagicArmor *armor) : magic_armor_(armor)
    {

    }

    virtual ~MagicArmorAdapter()
    {
    }

    virtual void work() override
    {
        magic_armor_->protectPhysicalAttack();
        magic_armor_->protectMagicAttack();
    }
private:
    MagicArmor *magic_armor_;
};

int main()
{
    std::shared_ptr<Hero> p_hero(new(std::nothrow) Hero);
    assert(p_hero.get());
    std::shared_ptr<Armor> p_armor(new(std::nothrow) Armor);
    assert(p_armor.get());
    p_hero->wear(p_armor.get());

    std::shared_ptr<MagicArmor> p_magic_armor(new(std::nothrow) MagicArmor);
    assert(p_magic_armor.get());
    std::shared_ptr<MagicArmorAdapter> p_magic_armor_adapter(new(std::nothrow)
        MagicArmorAdapter(p_magic_armor.get()));
    assert(p_magic_armor_adapter.get());
    p_hero->wear(p_magic_armor_adapter.get());

    return 0;
}

