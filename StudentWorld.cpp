#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <cmath> 
#include <iostream>
#include <sstream>
#include <iomanip> 
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
	: GameWorld(assetPath), m_vaccine(0), m_flame(0), m_mine(0), m_infected(0), m_tick(0), m_Cinfected(0)
{
}

string StudentWorld::getSLevel()
{
	return "level0" + to_string(getLevel()) + ".txt";
}


int StudentWorld::init()
{
	Level lev(assetPath());
	string levelFile = getSLevel() /*"leveltest.txt"*/;
	cerr << levelFile << endl;
	Level::LoadResult result = lev.loadLevel(levelFile);
	if (result == Level::load_fail_file_not_found)
	{
		cerr << "Cannot find " << getSLevel() << " data file" << endl;
		return GWSTATUS_PLAYER_WON;
	}

	else if (result == Level::load_fail_bad_format)
		cerr << "Your level was improperly formatted" << endl;
	else if (result == Level::load_success)
	{

		cerr << "Successfully loaded level" << endl;

		for (int i = 0; i < LEVEL_WIDTH; i++)
		{
			for (int j = 0; j < LEVEL_HEIGHT; j++)
			{
				Level::MazeEntry ge = lev.getContentsOf(i, j); // level_x=5, level_y=10

				switch (ge) // so x=80 and y=160
				{
				case Level::empty:
					break;
				case Level::player:
				{
					/*cerr << "Location " << i << ", " << j << " is where Penelope starts" << endl;*/
					p = new Penelope(IID_PLAYER, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0, this);
					break;
				}

				case Level::wall:
				{
					/*cerr << "Location " << i << ", " << j << " is where wall starts" << endl;*/
					Actor* w = new Wall(IID_WALL, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0, this);
					x.push_back(w);
					break;
				}

				case Level::exit:
				{
					/*cerr << "Location" << i << ", " << j << " is where exit starts" << endl;*/
					Actor* e = new Exit(IID_EXIT, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 1, this);
					x.push_back(e);
					break;
				}

				case Level::pit:
				{
					/*cerr << "Location" << i << ", " << j << " is where pit starts" << endl;*/
					Actor* q = new Pit(IID_PIT, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0, this);
					x.push_back(q);
					break;
				}

				case Level::vaccine_goodie:
				{
					/*cerr << "Location" << i << ", " << j << " is where vaccine starts" << endl;*/
					Actor* v = new VaccineGoodie(IID_VACCINE_GOODIE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 1, this);
					x.push_back(v);
					break;
				}
				case Level::gas_can_goodie:
				{
					/*cerr << "Location" << i << ", " << j << " is where vaccine starts" << endl;*/
					Actor* v = new GasCanGoodie(IID_GAS_CAN_GOODIE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 1, this);
					x.push_back(v);
					break;
				}
				case Level::landmine_goodie:
				{
					/*cerr << "Location" << i << ", " << j << " is where vaccine starts" << endl;*/
					Actor* v = new LandmineGoodie(IID_LANDMINE_GOODIE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 1, this);
					x.push_back(v);
					break;
				}
				case Level::dumb_zombie:
				{
					/*cerr << "Location" << i << ", " << j << " is where vaccine starts" << endl;*/
					Actor* v = new DumbZombie(IID_ZOMBIE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0, this);
					x.push_back(v);
					break;
				}
				case Level::smart_zombie:
				{
					/*cerr << "Location" << i << ", " << j << " is where vaccine starts" << endl;*/
					Actor* v = new SmartZombie(IID_ZOMBIE, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0, this); 
					x.push_back(v);
					break;
				}
				case Level::citizen:
				{
					/*cerr << "Location" << i << ", " << j << " is where vaccine starts" << endl;*/
					Actor* v = new Citizen(IID_CITIZEN, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0, this);
					x.push_back(v);
					break;
				}


				}

			}
		}

	}
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit enter.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	/*decLives();
	return GWSTATUS_PLAYER_DIED;*/

	// Have Penelope do Something 
	p->doSomething();

	// If Penelope dies, decrement her lives, reset abilities, and end current level
	if (p->getAlive() == false) {
		decLives();
		setFlameCount(-getFlameCount());
		setVaccineCount(-getVaccineCount());
		setMineCount(-getMineCount());
		setInfectedCount(-getInfectedCount());
		return GWSTATUS_PLAYER_DIED;
	}
		

	// Have each actor in the list do something 
	for (list<Actor*>::iterator it = x.begin(); it != x.end(); it++)
	{

		if ((*it)->getAlive())
		{
			(*it)->doSomething();

			// If Penelope fell in Pit, decrement lives, reset abilities and end current level
			if ((*it)->getPenFellInPit() == true)
			{
				decLives();
				setFlameCount(-getFlameCount());
				setVaccineCount(-getVaccineCount());
				setMineCount(-getMineCount());
				setInfectedCount(-getInfectedCount()); 
				return GWSTATUS_PLAYER_DIED;
			}

			// If Penelope successfully completely level, reset abilities and record 
			// successful completion of level.
			if ((*it)->getFinished() == true)
			{
				setFlameCount(-getFlameCount());
				setVaccineCount(-getVaccineCount());
				setMineCount(-getMineCount());
				setInfectedCount(-getInfectedCount()); 
				return GWSTATUS_FINISHED_LEVEL;
			}


		}
		
		// If an Actor dies in the level, remove it from the game and Actor list
		if ((*it)->getAlive() == false)
		{
			delete (*it);

			it = x.erase(it);
			if (it == x.end())
				break;
		}
	}

	// Update the Game Status Line
	ostringstream oss;
	oss.fill('0');
	oss << "Score: " << setw(6) << getScore() << "  " << "Level: " << setw(1) << getLevel() << "  " << "Lives: " << setw(1) << getLives() << "  "
		<< "Vaccines: " << setw(1) << getVaccineCount() << "  " << "Flames: " << setw(1) << getFlameCount() << "  " << "Mines: " << setw(1) << getMineCount()
		<< "  " << "Infected: " << setw(1) << getInfectedCount() << endl;
	string s = oss.str();
	setGameStatText(s);

	// Otherwise continue the game
	return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::determineBounds(Person* per) 
{
	// Check Citizen's blocking movement with Penelope and all other actors that 
	// should block Citizen from moving onto them. 
	if (per->getCitizen()) {
		if (per->getDirection() == 0)
		{
			if (abs(p->getX() - (per->getX() + SPRITE_WIDTH - 1)) < 2 && abs(per->getY() - p->getY()) < SPRITE_HEIGHT)
				return false;
		}
		if (per->getDirection() == 180)
		{
			if (abs((p->getX() + SPRITE_WIDTH - 1) - (per->getX())) < 2 && abs(per->getY() - p->getY()) < SPRITE_HEIGHT)
				return false;
		}
		if (per->getDirection() == 90)
		{
			if (abs(p->getY() - (per->getY() + SPRITE_HEIGHT - 1)) < 2 && abs(per->getX() - p->getX()) < SPRITE_WIDTH)
				return false;
		}
		if (per->getDirection() == 270)
		{
			if (abs((p->getY() + SPRITE_HEIGHT - 1) - (per->getY())) < 2 && abs(per->getX() - p->getX()) < SPRITE_WIDTH)
				return false;
		}

		list<Actor*>::iterator it = x.begin();
		for (; it != x.end(); it++)
		{
			if ((*it)->getBlock())
			{
				if (per->getDirection() == 0)
				{
					if (abs((*it)->getX() - (per->getX() + SPRITE_WIDTH - 1)) < 2 && abs(per->getY() - (*it)->getY()) < SPRITE_HEIGHT)
						return false;
				}
				if (per->getDirection() == 180)
				{
					if (abs(((*it)->getX() + SPRITE_WIDTH - 1) - (per->getX())) < 2 && abs(per->getY() - (*it)->getY()) < SPRITE_HEIGHT)
						return false;
				}
				if (per->getDirection() == 90)
				{
					if (abs((*it)->getY() - (per->getY() + SPRITE_HEIGHT - 1)) < 2 && abs(per->getX() - (*it)->getX()) < SPRITE_WIDTH)
						return false;
				}
				if (per->getDirection() == 270)
				{
					if (abs(((*it)->getY() + SPRITE_HEIGHT - 1) - (per->getY())) < 2 && abs(per->getX() - (*it)->getX()) < SPRITE_WIDTH)
						return false;
				}
			}

		}

		return true;

	}

	// Check blocking movement of Actors that are blocked from moving on Penelope
	if (per->getDirection() == 0)
	{
		if (abs(p->getX() - (per->getX() + SPRITE_WIDTH - 1)) < 4 && abs(per->getY() - p->getY()) < SPRITE_HEIGHT)
			return false;
	}
	if (per->getDirection() == 180)
	{
		if (abs((p->getX() + SPRITE_WIDTH - 1) - (per->getX())) < 4 && abs(per->getY() - p->getY()) < SPRITE_HEIGHT)
			return false;
	}
	if (per->getDirection() == 90)
	{
		if (abs(p->getY() - (per->getY() + SPRITE_HEIGHT - 1)) < 4 && abs(per->getX() - p->getX()) < SPRITE_WIDTH)
			return false;
	}
	if (per->getDirection() == 270)
	{
		if (abs((p->getY() + SPRITE_HEIGHT - 1) - (per->getY())) < 4 && abs(per->getX() - p->getX()) < SPRITE_WIDTH)
			return false;
	}

	// Check blocking movement of Actors moving onto other Actors
	list<Actor*>::iterator it = x.begin();
	for (; it != x.end(); it++)
	{
		if ((*it)->getBlock())
		{
			if (per->getDirection() == 0)
			{
				if (abs((*it)->getX() - (per->getX() + SPRITE_WIDTH - 1)) < 4 && abs(per->getY() - (*it)->getY()) < SPRITE_HEIGHT)
					return false;
			}
			if (per->getDirection() == 180)
			{
				if (abs(((*it)->getX() + SPRITE_WIDTH - 1) - (per->getX())) < 4 && abs(per->getY() - (*it)->getY()) < SPRITE_HEIGHT)
					return false;
			}
			if (per->getDirection() == 90)
			{
				if (abs((*it)->getY() - (per->getY() + SPRITE_HEIGHT - 1)) < 4 && abs(per->getX() - (*it)->getX()) < SPRITE_WIDTH)
					return false;
			}
			if (per->getDirection() == 270)
			{
				if (abs(((*it)->getY() + SPRITE_HEIGHT - 1) - (per->getY())) < 4 && abs(per->getX() - (*it)->getX()) < SPRITE_WIDTH)
					return false;
			}
		}

	}
	return true;
}

// Check if Penelope overlaps with Goodies, Exit, or Pit 
bool StudentWorld::PenOverlapsActor(Actor* a)
{

	if (((a->getX() - p->getX()) * (a->getX() - p->getX())) +
		((a->getY() - p->getY()) * (a->getY() - p->getY())) <= 10 * 10)
	{
		if (a->getGoodies()) {
			return true;
		}
		if (a->getExit()) {
			return true;
		}
		if (a->getPit()) {
			return true;
		}
	
	}

	return false;
}

// Check if Zombie or Citizen fall into Pit
bool StudentWorld::ActorOverlapsActor(Actor* a)
{

	list<Actor*>::iterator it = x.begin(); 

	for (; it != x.end(); it++)
	{

		if ((((*it)->getX() - a->getX()) * ((*it)->getX() - a->getX())) +
			(((*it)->getY() - a->getY()) * ((*it)->getY() - a->getY())) <= 10 * 10)
		{
			if ((*it)->getBlock())
			{
				if ((*it)->getCitizen()) {

					if ((*it)->getActorFellInPit()) {
						(*it)->setAlive(false);
						playSound(SOUND_CITIZEN_DIE);
						increaseScore(-1000);
						return true;
					}

				}
				if ((*it)->getZombie()) {
					if ((*it)->getActorFellInPit()) {
						(*it)->setAlive(false);
						playSound(SOUND_ZOMBIE_DIE);
						return true;
					}
				}
			}
		}
	}

	return false;
}

// Accessor method for methods in Actor.cpp to add Actors to actor list 
void StudentWorld::addToList(Actor* aptr)
{
	x.push_back(aptr);
}

// Check if flame flame is blocked from moving onto an actor. 
// (Flame is blocked by walls and exits)
bool StudentWorld::checkFlamePos(double fx, double fy)
{
	list<Actor*>::iterator it = x.begin();

	for (; it != x.end(); it++)
	{
		if ((*it)->getBlockFlame())
		{
			if ((((*it)->getX() - fx) * ((*it)->getX() - fx)) + (((*it)->getY() - (fy))
				* ((*it)->getY() - (fy))) <= 10 * 10)
				return true;

			if ((((*it)->getX() - fx) * ((*it)->getX() - fx)) + (((*it)->getY() - (fy))
				* ((*it)->getY() - (fy))) <= 10 * 10)
				return true;

			if ((((*it)->getX() - (fx)) * ((*it)->getX() - (fx))) + (((*it)->getY() - fy)
				* ((*it)->getY() - fy)) <= 10 * 10)
				return true;

			if ((((*it)->getX() - (fx)) * ((*it)->getX() - (fx))) + (((*it)->getY() - fy)
				* ((*it)->getY() - fy)) <= 10 * 10)
				return true;
		}
	}

	return false;
}

// Check if flame overlaps with various Actors in a given level
bool StudentWorld::ifFlameOverlaps(Actor* a)
{
	// If Flame overlaps with Penelope, set her status to dead
	if (((p->getX() - a->getX()) * (p->getX() - a->getX())) +
		((p->getY() - a->getY()) * (p->getY() - a->getY())) <= 10 * 10) {
		p->setAlive(false);
		playSound(SOUND_PLAYER_DIE);
	}

	list<Actor*>::iterator it = x.begin();
	for (; it != x.end(); it++)
	{

		if ((((*it)->getX() - a->getX()) * ((*it)->getX() - a->getX())) +
			(((*it)->getY() - a->getY()) * ((*it)->getY() - a->getY())) <= 10 * 10)
		{
			

			if ((*it)->getisFlammable())
			{
				// If Flame overlaps with Dumb Zombie, set its status to dead and there is a 1 in 10 chance  
				// the zombie drops a vaccine goodie 
				if ((*it)->getDumbZombie())
				{
					double xcoord = (*it)->getX();
					double ycoord = (*it)->getY();
					(*it)->setAlive(false);
					playSound(SOUND_ZOMBIE_DIE);
					increaseScore(1000);
					
					int num = 1;
					int chance = randInt(1, 10);
					if (num == chance) {
						Actor* v = new VaccineGoodie(IID_VACCINE_GOODIE, xcoord, ycoord, 1, this);
						x.push_back(v);
					}
					return true;
				}

				// If Flame overlaps with Smart Zombie, set its state to dead and update appropriate elements of game
				if ((*it)->getSmartZombie())
				{
					double xcoord = (*it)->getX();
					double ycoord = (*it)->getY();
					(*it)->setAlive(false);
					playSound(SOUND_ZOMBIE_DIE);
					increaseScore(2000);
					return true;
				}

				// If Flame overlaps with any Goodie, remove them from the game 
				// as they are no longer able to be picked up by player
				if ((*it)->getGoodies()) 
				{
					(*it)->setAlive(false);
					return true;
				}

				// If Flame overlaps Citizen, set Citizen to status dead and decrease Player's score..
				if ((*it)->getCitizen())
				{
					(*it)->setAlive(false);
					playSound(SOUND_CITIZEN_DIE);
					increaseScore(-1000);
				}

				// If Flame overlaps with Landmine, Landmine introduces Flame objects all around it 
				// and places a pit at its (x,y) coordinate
				if ((*it)->getLandmine()) {
					(*it)->setAlive(false);
					playSound(SOUND_LANDMINE_EXPLODE);
					
					Flame* n = new Flame(IID_FLAME, (*it)->getX(), (*it)->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(n);

					Flame* ne = new Flame(IID_FLAME, (*it)->getX() + SPRITE_WIDTH, (*it)->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(ne);

					Flame* e = new Flame(IID_FLAME, (*it)->getX() + SPRITE_WIDTH, (*it)->getY(), 0, this);
					x.push_back(e);

					Flame* se = new Flame(IID_FLAME, (*it)->getX() + SPRITE_WIDTH, (*it)->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(se);

					Flame* s = new Flame(IID_FLAME, (*it)->getX(), (*it)->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(s);

					Flame* sw = new Flame(IID_FLAME, (*it)->getX() - SPRITE_WIDTH, (*it)->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(sw);

					Flame* w = new Flame(IID_FLAME, (*it)->getX() - SPRITE_WIDTH, (*it)->getY(), 0, this);
					x.push_back(w);

					Flame* nw = new Flame(IID_FLAME, (*it)->getX() - SPRITE_WIDTH, (*it)->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(nw);

					
					Pit* pit = new Pit(IID_PIT, (*it)->getX(), (*it)->getY(), 0, this);
					x.push_back(pit);
				}
			}

		}
	}

	return false;
}

int StudentWorld::getVaccineCount() const
{
	return m_vaccine;
}

void StudentWorld::setVaccineCount(int vaccine)
{
	m_vaccine += vaccine;
}

int StudentWorld::getFlameCount() const
{
	return m_flame;
}

void StudentWorld::setFlameCount(int flame)
{
	m_flame += flame;
}

int StudentWorld::getMineCount() const
{
	return m_mine;
}

void StudentWorld::setMineCount(int mine)
{
	m_mine += mine;
}

int StudentWorld::getTickCounter() const
{
	return m_tick;
}

void StudentWorld::setTickCounter(int tick)
{
	m_tick += tick; 
}

int StudentWorld::getInfectedCount() const
{
	return m_infected;
}

void StudentWorld::setInfectedCount(int infected)
{
	m_infected += infected;
}

// If Zombie is facing a Person and is close to them, then Zombie will project vomit 
// and infect them. 
bool StudentWorld::checkZombieFacingPen(Person* per)
{
	if (per->getDirection() == 0)
	{
		
		if ((((per->getX() + SPRITE_WIDTH) - p->getX()) * ((per->getX() + SPRITE_WIDTH) - p->getX())) +
			((per->getY() - p->getY()) * (per->getY() - p->getY())) <= 10 * 10) {
			int num = 1;
			int chance = randInt(1, 3);
			if (chance == num) {
				Vomit* v = new Vomit(IID_VOMIT, per->getX() + SPRITE_WIDTH, per->getY(), 0, this);
				addToList(v);
				playSound(SOUND_ZOMBIE_VOMIT);
				p->setifInfected(true);
				return true;
			}
		}
			
	}
	
	if (per->getDirection() == 180)
	{
		
		if ((((per->getX() - SPRITE_WIDTH) - p->getX()) * ((per->getX() - SPRITE_WIDTH) - p->getX())) +
			((per->getY() - p->getY()) * (per->getY() - p->getY())) <= 10 * 10) {
			int num = 1;
			int chance = randInt(1, 3);
			if (chance == num) {
				Vomit* v = new Vomit(IID_VOMIT, per->getX() - SPRITE_WIDTH, per->getY(), 0, this);
				addToList(v);
				playSound(SOUND_ZOMBIE_VOMIT);
				p->setifInfected(true);
				return true;
			}
		}

	}
	
	if (per->getDirection() == 90)
	{
		
		if (((per->getX() - p->getX()) * (per->getX() - p->getX())) +
			(((per->getY() + SPRITE_WIDTH) - p->getY()) * ((per->getY() + SPRITE_WIDTH) - p->getY())) <= 10 * 10) {
			int num = 1;
			int chance = randInt(1, 3);
			if (chance == num) {
				Vomit* v = new Vomit(IID_VOMIT, per->getX(), per->getY() + SPRITE_WIDTH, 0, this);
				addToList(v);
				playSound(SOUND_ZOMBIE_VOMIT);
				p->setifInfected(true);
				return true;
			}
		}
			
	}
	
	if (per->getDirection() == 270)
	{

		if (((per->getX() - p->getX()) * (per->getX() - p->getX())) +
			(((per->getY() - SPRITE_WIDTH) - p->getY()) * ((per->getY() - SPRITE_WIDTH) - p->getY())) <= 10 * 10) {
			int num = 1;
			int chance = randInt(1, 3);
			if (chance == num) {
				Vomit* v = new Vomit(IID_VOMIT, per->getX(), per->getY() - SPRITE_WIDTH, 0, this);
				addToList(v);
				playSound(SOUND_ZOMBIE_VOMIT);
				p->setifInfected(true);
				return true;
			}
		}
			
	}

	list<Actor*>::iterator it = x.begin();
	for (; it != x.end(); it++) {
		if ((*it)->getCitizen()) {
			if (per->getDirection() == 0)
			{

				if ((((per->getX() + SPRITE_WIDTH) - (*it)->getX()) * ((per->getX() + SPRITE_WIDTH) - (*it)->getX())) +
					((per->getY() - (*it)->getY()) * (per->getY() - (*it)->getY())) <= 10 * 10) {
					int num = 1;
					int chance = randInt(1, 3);
					if (chance == num) {
						Vomit* v = new Vomit(IID_VOMIT, per->getX() + SPRITE_WIDTH, per->getY(), 0, this);
						addToList(v);
						playSound(SOUND_ZOMBIE_VOMIT);
						(*it)->setifCitizenInfected(true);
						return true;
					}
				}

			}

			if (per->getDirection() == 180)
			{

				if ((((per->getX() - SPRITE_WIDTH) - (*it)->getX()) * ((per->getX() - SPRITE_WIDTH) - (*it)->getX())) +
					((per->getY() - (*it)->getY()) * (per->getY() - (*it)->getY())) <= 10 * 10) {
					int num = 1;
					int chance = randInt(1, 3);
					if (chance == num) {
						Vomit* v = new Vomit(IID_VOMIT, per->getX() - SPRITE_WIDTH, per->getY(), 0, this);
						addToList(v);
						playSound(SOUND_ZOMBIE_VOMIT);
						(*it)->setifCitizenInfected(true);
						return true;
					}
				}

			}

			if (per->getDirection() == 90)
			{

				if (((per->getX() - (*it)->getX()) * (per->getX() - (*it)->getX())) +
					(((per->getY() + SPRITE_WIDTH) - (*it)->getY()) * ((per->getY() + SPRITE_WIDTH) - (*it)->getY())) <= 10 * 10) {
					int num = 1;
					int chance = randInt(1, 3);
					if (chance == num) {
						Vomit* v = new Vomit(IID_VOMIT, per->getX(), per->getY() + SPRITE_WIDTH, 0, this);
						addToList(v);
						playSound(SOUND_ZOMBIE_VOMIT);
						(*it)->setifCitizenInfected(true);
						return true;
					}
				}

			}

			if (per->getDirection() == 270)
			{

				if (((per->getX() - (*it)->getX()) * (per->getX() - (*it)->getX())) +
					(((per->getY() - SPRITE_WIDTH) - (*it)->getY()) * ((per->getY() - SPRITE_WIDTH) - (*it)->getY())) <= 10 * 10) {
					int num = 1;
					int chance = randInt(1, 3);
					if (chance == num) {
						Vomit* v = new Vomit(IID_VOMIT, per->getX(), per->getY() - SPRITE_WIDTH, 0, this);
						addToList(v);
						playSound(SOUND_ZOMBIE_VOMIT);
						(*it)->setifCitizenInfected(true);
						return true;
					}
				}

			}
		}
	}

	return false;
}

// Returns the Person that is closest to a particualr Smart Zombie 
Actor* StudentWorld::personClosestToSmartZomb(Actor* a)
{
	double eDistToPenelope = ((a->getX() - p->getX()) * (a->getX() - p->getX())) + ((a->getY() - p->getY()) * (a->getY() - p->getY()));
	double eDistToCitizen = -1;
	Actor* citizen = nullptr; 
	list<Actor*>::iterator it = x.begin();
	for (; it != x.end(); it++) {
		// get Euclidean distance from Zombie to Citizen and find the Citizen that is cloest to the Smart Zombie
		if ((*it)->getCitizen()) {
			double tempEDistToCitizen = ((a->getX() - (*it)->getX()) * (a->getX() - (*it)->getX())) + ((a->getY() - (*it)->getY()) * (a->getY() - (*it)->getY()));
			if (eDistToCitizen == -1) {
				eDistToCitizen = tempEDistToCitizen;
				citizen = (*it);
			}
			if (tempEDistToCitizen < eDistToCitizen) {
				eDistToCitizen = tempEDistToCitizen;
				citizen = (*it);
			}
		}
	}

	// Check if Penelope or Citizen is closet to Smart Zombie 
	if (eDistToPenelope < eDistToCitizen || citizen == nullptr)
		return p;
	else
		return citizen;
}

// If Citizen got infected and counter reached 500, then Citizen is dead and turns into a Zombie 
void StudentWorld::citizenGotInfected(Person* citizen)
{
	citizen->setAlive(false);
	playSound(SOUND_ZOMBIE_BORN);
	increaseScore(-1000);

	// There is a 7 out of 10 chance Citizen turns into a Dumb Zombie and 
	// 3 out of 10 chance it turns into a Smart Zombie
	int chooseZombieToSpawn = randInt(1, 10);
	if (chooseZombieToSpawn < 8) {
		DumbZombie* d = new DumbZombie(IID_ZOMBIE, citizen->getX(), citizen->getY(), 0, this);
		x.push_back(d);
		return;
	}
	else {
		SmartZombie* s = new SmartZombie(IID_ZOMBIE, citizen->getX(), citizen->getY(), 0, this);
		x.push_back(s);
		return;

	}

}

// Returns the distance from a Person to Penelope
double StudentWorld::distanceToPenelope(Person* per)
{
	double distance = sqrt(((p->getX() - per->getX()) * (p->getX() - per->getX())) + ((p->getY() - per->getY()) * (p->getY() - per->getY())));
	return distance; 
}

// Returns the distance to the nearest Zombie
double StudentWorld::distanceToNearestZombie(Person* per)
{
	double distance = -1;

	// Loops through Actor list and looks for Zombie and computes its distance to a given person.
	list<Actor*>::iterator it = x.begin();
	for (; it != x.end(); it++) {
		if ((*it)->getZombie()) {
			double tempDist = sqrt((((*it)->getX() - per->getX()) * ((*it)->getX() - per->getX())) + (((*it)->getY() - per->getY()) * ((*it)->getY() - per->getY())));
			// If distance to nearest Zombie has not been set yet, set it 
			if (distance == -1)
				distance = tempDist; 
			// Otherwise, compare previous nearest distance to current one and choose the new nearest distance to a Zombie 
			if (tempDist < distance)
				distance = tempDist;
		}
	}

	return distance; 
}

// Returns the Euclidean distance to Penelope
double StudentWorld::eDistToPenelope(Person* per)
{
	double eDistToPenelope = ((per->getX() - p->getX()) * (per->getX() - p->getX())) + ((per->getY() - p->getY()) * (per->getY() - p->getY()));
	return eDistToPenelope;
}

// Accessor function that returns pointer to Penelope
Penelope* StudentWorld::getPenelope()
{
	return p; 
}

// Returns pointer of Zombie who is 80 pixels or less away from a Citizen
// If no such Zombie exists, return nullptr
Actor* StudentWorld::eDistFromCitizenToZombie(Person* per)
{
	double eDist = -1;
	list<Actor*>::iterator it = x.begin();
	for (; it != x.end(); it++) {
		if ((*it)->getZombie()) {
			double tempEDist = ((per->getX() - (*it)->getX()) * (per->getX() - (*it)->getX())) + ((per->getY() - (*it)->getY()) * (per->getY() - (*it)->getY())); 
			if (tempEDist <= 80 * 80)
				return (*it);
		}
	}
	return nullptr;
}

// Returns the distance of Nearest Zombie from a new potential location that a Citizen will move to
double StudentWorld::distanceToNearestZombieFromNewLocation(Person* per, int newx, int newy)
{
	double distance = -1;
	list<Actor*>::iterator it = x.begin();
	for (; it != x.end(); it++) {
		if ((*it)->getZombie()) {
			double tempDist = sqrt((((*it)->getX() - newx) * ((*it)->getX() - newx)) + (((*it)->getY() - newy) * ((*it)->getY() - newy)));
			if (distance == -1)
				distance = tempDist;
			if (tempDist < distance)
				distance = tempDist;
		}
	}

	return distance;
}


int StudentWorld::getCitizenInfectedCount() const
{
	return m_Cinfected;
}

void StudentWorld::setCitizenInfectedCount(int infected)
{
	m_Cinfected += infected;
}

// Checks if Citizen and /or Penelope overlaps with Exit and if so,
// updates the game status accordingly
bool StudentWorld::PersonOverlapsActor(Actor* a)
{
	list<Actor*>::iterator it = x.begin();

	for (; it != x.end(); it++)
	{

		if ((((*it)->getX() - a->getX()) * ((*it)->getX() - a->getX())) +
			(((*it)->getY() - a->getY()) * ((*it)->getY() - a->getY())) <= 10 * 10)
		{
			if ((*it)->getBlock())
			{
				if ((*it)->getCitizen()) {

					if ((*it)->getExit()) {
						increaseScore(500);
						(*it)->setAlive(false);
						playSound(SOUND_CITIZEN_SAVED);
						return true;
					}

				}
			}
		}
	}

	// Check if Penelope overlaps with Exit once there are no more Citizens in the current level.
	// If so, Player successfully finished level.
	// Otherwise, continue game
	bool ifPenAndExitOverlap = ((p->getX() - a->getX()) * (p->getX() - a->getX())) + ((p->getY() - a->getY()) * (p->getY() - a->getY())) <= 10 * 10;
	if (ifPenAndExitOverlap && checkNoMoreCitizens()) { 
		a->setFinished(true); 
		playSound(SOUND_LEVEL_FINISHED); 
		return true; 
	}

	return false;
	
}

// Check if any Citizens are still in the current level
bool StudentWorld::checkNoMoreCitizens()
{
	list<Actor*>::iterator it = x.begin();
	for (; it != x.end(); it++) {
		if ((*it)->getCitizen())
			return false;
	}
	return true;
}

// Check if Penelope, Citizen or Zombie overlap with a landmine and
// update the game accordingly
bool StudentWorld::PersonOverlapsLandmine(Actor* a)
{
	if (((p->getX() - a->getX()) * (p->getX() - a->getX())) +
		((p->getY() - a->getY()) * (p->getY() - a->getY())) <= 10 * 10) {
		a->setAlive(false);
		playSound(SOUND_LANDMINE_EXPLODE);
		Flame* f = new Flame(IID_FLAME, a->getX(), a->getY(), 0, this);
		x.push_back(f); 
		
		Flame* n = new Flame(IID_FLAME, a->getX(), a->getY()+SPRITE_HEIGHT, 0, this);
		x.push_back(n);
		
		Flame* ne = new Flame(IID_FLAME, a->getX()+SPRITE_WIDTH, a->getY()+SPRITE_HEIGHT, 0, this);
		x.push_back(ne);
		
		Flame* e = new Flame(IID_FLAME, a->getX()+SPRITE_WIDTH, a->getY(), 0, this);
		x.push_back(e);
		
		Flame* se = new Flame(IID_FLAME, a->getX()+SPRITE_WIDTH, a->getY()-SPRITE_HEIGHT, 0, this);
		x.push_back(se);
		
		Flame* s = new Flame(IID_FLAME, a->getX(), a->getY()-SPRITE_HEIGHT, 0, this);
		x.push_back(s);
		
		Flame* sw = new Flame(IID_FLAME, a->getX()-SPRITE_WIDTH, a->getY()-SPRITE_HEIGHT, 0, this);
		x.push_back(sw);
		
		Flame* w = new Flame(IID_FLAME, a->getX()-SPRITE_WIDTH, a->getY(), 0, this);
		x.push_back(w);
		
		Flame* nw = new Flame(IID_FLAME, a->getX()-SPRITE_WIDTH, a->getY()+SPRITE_HEIGHT, 0, this);
		x.push_back(nw);

		Pit* pit = new Pit(IID_PIT, a->getX(), a->getY(), 0, this);
		x.push_back(pit);

	}

	list<Actor*>::iterator it = x.begin();

	for (; it != x.end(); it++)
	{

		if ((((*it)->getX() - a->getX()) * ((*it)->getX() - a->getX())) +
			(((*it)->getY() - a->getY()) * ((*it)->getY() - a->getY())) <= 10 * 10)
		{
			if ((*it)->getBlock())
			{
				if ((*it)->getCitizen()) {

					a->setAlive(false);
					playSound(SOUND_LANDMINE_EXPLODE);
					Flame* f = new Flame(IID_FLAME, a->getX(), a->getY(), 0, this);
					x.push_back(f);

					Flame* n = new Flame(IID_FLAME, a->getX(), a->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(n);

					Flame* ne = new Flame(IID_FLAME, a->getX() + SPRITE_WIDTH, a->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(ne);

					Flame* e = new Flame(IID_FLAME, a->getX() + SPRITE_WIDTH, a->getY(), 0, this);
					x.push_back(e);

					Flame* se = new Flame(IID_FLAME, a->getX() + SPRITE_WIDTH, a->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(se);

					Flame* s = new Flame(IID_FLAME, a->getX(), a->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(s);

					Flame* sw = new Flame(IID_FLAME, a->getX() - SPRITE_WIDTH, a->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(sw);

					Flame* w = new Flame(IID_FLAME, a->getX() - SPRITE_WIDTH, a->getY(), 0, this);
					x.push_back(w);

					Flame* nw = new Flame(IID_FLAME, a->getX() - SPRITE_WIDTH, a->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(nw);

					Pit* pit = new Pit(IID_PIT, a->getX(), a->getY(), 0, this);
					x.push_back(pit);

				}

				if ((*it)->getZombie()) {
					a->setAlive(false);
					playSound(SOUND_LANDMINE_EXPLODE);
					Flame* f = new Flame(IID_FLAME, a->getX(), a->getY(), 0, this);
					x.push_back(f);

					Flame* n = new Flame(IID_FLAME, a->getX(), a->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(n);

					Flame* ne = new Flame(IID_FLAME, a->getX() + SPRITE_WIDTH, a->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(ne);

					Flame* e = new Flame(IID_FLAME, a->getX() + SPRITE_WIDTH, a->getY(), 0, this);
					x.push_back(e);

					Flame* se = new Flame(IID_FLAME, a->getX() + SPRITE_WIDTH, a->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(se);

					Flame* s = new Flame(IID_FLAME, a->getX(), a->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(s);

					Flame* sw = new Flame(IID_FLAME, a->getX() - SPRITE_WIDTH, a->getY() - SPRITE_HEIGHT, 0, this);
					x.push_back(sw);

					Flame* w = new Flame(IID_FLAME, a->getX() - SPRITE_WIDTH, a->getY(), 0, this);
					x.push_back(w);

					Flame* nw = new Flame(IID_FLAME, a->getX() - SPRITE_WIDTH, a->getY() + SPRITE_HEIGHT, 0, this);
					x.push_back(nw);

					Pit* pit = new Pit(IID_PIT, a->getX(), a->getY(), 0, this);
					x.push_back(pit);
				}

				

				
			}
		}
	}
	return false;
}

// Safely deallocates pointers to all game Actors once game and/or level has ended
void StudentWorld::cleanUp()
{
	// Delete Penelope 
	if (p != nullptr)
	{
		delete p;
		p = nullptr;

		list<Actor*>::iterator it = x.begin();
		while (it != x.end())
		{
			delete (*it);
			it = x.erase(it);
		}

	}
}