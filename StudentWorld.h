#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h" 
#include "Level.h"
#include <string>
#include <list> 
#include <vector> 
#include <algorithm>
using namespace std;


class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	string getSLevel();
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	virtual ~StudentWorld() { cleanUp(); }
	bool determineBounds(Person* per);
	bool PenOverlapsActor(Actor* a);
	bool ActorOverlapsActor(Actor* a); 
	void addToList(Actor* aptr);
	bool checkFlamePos(double fx, double fy);
	bool ifFlameOverlaps(Actor* a);
	int getVaccineCount() const;
	void setVaccineCount(int vaccine);
	int getFlameCount() const;
	void setFlameCount(int flame);
	int getMineCount() const;
	void setMineCount(int mine);
	int getTickCounter() const;
	void setTickCounter(int tick);
	int  getInfectedCount() const;
	void setInfectedCount(int infected);

	bool checkZombieFacingPen(Person* per);
	Actor* personClosestToSmartZomb(Actor* a);
	void citizenGotInfected(Person* citizen);
	double distanceToPenelope(Person* per);
	double distanceToNearestZombie(Person* per);
	double eDistToPenelope(Person* per);
	Penelope* getPenelope(); 
	Actor* eDistFromCitizenToZombie(Person* per);
	double distanceToNearestZombieFromNewLocation(Person* per, int newx, int newy);
	int  getCitizenInfectedCount() const;
	void setCitizenInfectedCount(int infected);
	bool PersonOverlapsActor(Actor* a);
	bool checkNoMoreCitizens();
	bool PersonOverlapsLandmine(Actor* a); 


private:
	int m_vaccine;
	int m_flame;
	int m_mine;
	int m_infected;
	int m_tick;
	int m_move;
	Penelope* p;
	list <Actor*> x;

	int counter = 0;
	int m_Cinfected;
};

#endif // STUDENTWORLD_H_
