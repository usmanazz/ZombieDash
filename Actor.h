#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


///////////////////// Class Prototypes ///////////////////////////
class StudentWorld;
class GameWorld;

////////////////////////////// ACTOR Base Class /////////////////////////
class Actor : public GraphObject
{
public:
	Actor(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething() = 0;
	virtual ~Actor();
	StudentWorld* getWorld() const;
	void setWorld(StudentWorld* pt);
	bool getAlive() const; //
	void setAlive(bool alive);
	bool getifInfected() const; //
	void setifInfected(bool infected);
	bool getisFlammable() const; //
	void setisFlammable(bool flame);
	bool getFinished() const; //
	void setFinished(bool finished);
	bool getBlock() const; //
	void setBlock(bool block);
	bool getExit() const; //
	void setExit(bool exit);
	bool getPenFellInPit() const; //
	void setPenFellInPit(bool fell);
	bool getActorFellInPit() const; //
	void setActorFellInPit(bool afell);
	bool getBlockFlame() const; // 
	void setBlockFlame(bool flame);
	bool getZombie() const;
	void setZombie(bool zombie);
	bool getVaccine() const;
	void setVaccine(bool vaccine);
	bool getLandmine() const;
	void setLandmine(bool mine);

	bool getGoodies() const;
	void setGoodies(bool goodies);
	bool getPen() const;
	void setPen(bool pen);
	bool getVomit() const;
	void setVomit(bool vomit);
	bool getPit() const;
	void setPit(bool pit);
	bool getWall() const;
	void setWall(bool wall);
	bool getPerson() const;
	void setPerson(bool person);
	bool getDumbZombie() const;
	void setDumbZombie(bool zombie);
	bool getSmartZombie() const;
	void setSmartZombie(bool zombie);
	bool getCitizen() const;
	void setCitizen(bool citizen);
	int getTickk() const;
	void setTickk(int tick);
	bool getifCitizenInfected() const; //
	void setifCitizenInfected(bool infected);
	bool getLandmineActive() const;
	void setLandmineActive(bool mine);
	bool getFlame() const;
	void setFlame(bool flame);
	bool isFlame() const;
	void setisFlame(bool flame);


private:
	StudentWorld* ptrr;
	bool m_finished;
	bool m_alive;
	bool m_infected;
	bool m_flame;
	bool m_block;
	bool m_exit;
	bool m_fellInPit;
	bool m_blockFlame;
	bool m_flameCanDestroy;
	bool m_zombie;
	bool m_vaccine;
	bool m_mine;

	bool m_goodies;
	bool m_afell;
	bool m_pen;
	bool m_vomit;
	bool m_pit;
	bool m_wall;
	bool m_person;
	bool m_Dzomb;
	bool m_Szomb;
	bool m_citizen;
	int m_tickk;
	bool m_Cinfected;
	bool m_landmine;
	bool m_flameee;
	bool m_isFlame;

};

////////////////////////// Actor Derived Class //////////////////////////
class Wall : public Actor
{
public:
	Wall(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~Wall();
};


class Exit : public Actor
{
public:
	Exit(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~Exit();
private:
};

////////////////////////////// PERSON Base Class ///////////////////////////
class Person : public Actor
{
public:
	Person(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething() = 0;
	virtual ~Person();
private:
};

//////////////////////////// Person Derived Class ////////////////////////
class Penelope : public Person
{
public:
	Penelope(int ID, double startX, double startY, int depth, StudentWorld* pt);
	virtual void doSomething();
	virtual ~Penelope();
private:
};

class Citizen : public Person
{
public: 
	Citizen(int ID, double startX, double startY, int depth, StudentWorld* pt);
	virtual void doSomething();
	virtual ~Citizen(); 
	int  getCitizenInfectedCount() const;
	void setCitizenInfectedCount(int infected);
private:
	int m_infected;
};

/////////////////////////////// ZOMBIE Base Class ////////////////////////////////
class Zombie : public Person
{
public:
	Zombie(int ID, double startX, double startY, int depth, StudentWorld* pt);
	virtual void doSomething();
	virtual ~Zombie();
private:
};


//////////////////////////// Zombie Derived Class ///////////////////////////// 
class DumbZombie : public Zombie
{
public:
	DumbZombie(int ID, double startX, double startY, int depth, StudentWorld* pt);
	virtual void doSomething();
	virtual ~DumbZombie();
	virtual int getMovePlan() const;
	virtual void setMovePlan(int move);
private:
	int m_movePlan;
};

class SmartZombie : public Zombie
{
public:
	SmartZombie(int ID, double startX, double startY, int depth, StudentWorld* pt);
	virtual void doSomething();
	virtual ~SmartZombie();
	virtual int getMovePlan() const;
	virtual void setMovePlan(int move);
private:
	int m_movePlan;
};


//////////////////////////// STATIONARY Base Class /////////////////////////
class Stationary : public Actor
{
public:
	Stationary(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething() = 0;
	virtual ~Stationary();
};

//////////////////////// Stationary Derived Class /////////////////////////
class Pit : public Stationary
{
public:
	Pit(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~Pit();
private:
	int counter = 0;

};

class Landmine : public Stationary
{
public:
	Landmine(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~Landmine();
	int getSafetyTick() const;
	void setSafetyTick(int tick);
private:
	int m_safetyTick;
};

////////////////////// GOODIES Base Class ///////////////////////////////
class Goodies : public Actor
{
public:
	Goodies(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething() = 0;
	virtual ~Goodies();
private:

};

////////////////////// Goodies Dervied Class //////////////////////////
class VaccineGoodie : public Goodies
{
public:
	VaccineGoodie(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~VaccineGoodie();
private:
};

class GasCanGoodie : public Goodies
{
public:
	GasCanGoodie(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~GasCanGoodie();
};

class LandmineGoodie : public Goodies
{
public:
	LandmineGoodie(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~LandmineGoodie();
};

/////////////////////////////// PROJECTILE class /////////////////////////////////////
class Projectile : public Actor
{
public:
	Projectile(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething() = 0;
	virtual ~Projectile();
	int getTick() const;
	void setTick(int tick);
private:
	int m_tick;


};

///////////////////////// Projectile Derived class ////////////////////////////////
class Flame : public Projectile
{
public:
	Flame(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~Flame();
};


class Vomit : public Projectile
{
public:
	Vomit(int ID, double startX, double startY, int depth, StudentWorld* ptr);
	virtual void doSomething();
	virtual ~Vomit();
};

#endif // ACTOR_H_

