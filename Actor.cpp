#include "Actor.h"
#include "StudentWorld.h"

#include <math.h>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

////////////////////////// ACTOR IMPLEMENTATION ///////////////////////////////////////

Actor::Actor(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: GraphObject(ID, startX, startY, right, depth, 1), m_tickk(0)
{
	setWorld(ptr);

	setAlive(true);
	setifInfected(false);
	setisFlammable(false);
	setFinished(false);
	setBlock(false);
	setExit(false);
	setPenFellInPit(false);
	setBlockFlame(false);
	setLandmine(false);
	setZombie(false);
	setVaccine(false);
	
	setGoodies(false);
	setDumbZombie(false);
	setSmartZombie(false);
	setCitizen(false);
	setifCitizenInfected(false);
	setLandmineActive(false);
	setFlame(false);
	setisFlame(false);
}


// get and set functions used when looping through list of Actor pointers

// StudentWorld get pointer function to access functions in StudentWorld.cpp file
StudentWorld* Actor::getWorld() const
{
	return ptrr;
}

void Actor::setWorld(StudentWorld* pt)
{
	ptrr = pt;
}


bool Actor::getAlive() const
{
	return m_alive;
}

void Actor::setAlive(bool alive)
{
	m_alive = alive;
}

bool Actor::getifInfected() const
{
	return m_infected;
}

void Actor::setifInfected(bool infected)
{
	m_infected = infected;
}

bool Actor::getisFlammable() const
{
	return m_flame;
}

void Actor::setisFlammable(bool flame)
{
	m_flame = flame;
}


bool Actor::getFinished() const
{
	return m_finished;
}

void Actor::setFinished(bool finished)
{
	m_finished = finished;
}


bool Actor::getBlock() const
{
	return m_block;
}

void Actor::setBlock(bool block)
{
	m_block = block;
}


bool Actor::getExit() const
{
	return m_exit;
}

void Actor::setExit(bool exit)
{
	m_exit = exit;
}

bool Actor::getPenFellInPit() const
{
	return m_fellInPit;
}

void Actor::setPenFellInPit(bool fell)
{
	m_fellInPit = fell;
}

bool Actor::getActorFellInPit() const
{
	return m_afell;
}

void Actor::setActorFellInPit(bool afell)
{
	m_afell = afell;
}

bool Actor::getBlockFlame() const
{
	return m_blockFlame;
}

void Actor::setBlockFlame(bool flame)
{
	m_blockFlame = flame;
}

bool Actor::getZombie() const
{
	return m_zombie;
}

void Actor::setZombie(bool zombie)
{
	m_zombie = zombie;
}

bool Actor::getVaccine() const
{
	return m_vaccine;
}

void Actor::setVaccine(bool vaccine)
{
	m_vaccine = vaccine;
}

bool Actor::getLandmine() const
{
	return m_mine;
}

void Actor::setLandmine(bool mine)
{
	m_mine = mine;
}

bool Actor::getGoodies() const
{
	return m_goodies;
}

void Actor::setGoodies(bool goodies)
{
	m_goodies = goodies;
}

bool Actor::getPen() const
{
	return m_pen;
}

void Actor::setPen(bool pen)
{
	m_pen = pen;
}

bool Actor::getVomit() const
{
	return m_vomit;
}

void Actor::setVomit(bool vomit)
{
	m_vomit = vomit;
}

bool Actor::getPit() const
{
	return m_pit;
}

void Actor::setPit(bool pit)
{
	m_pit = pit;
}

bool Actor::getWall() const
{
	return m_wall;
}

void Actor::setWall(bool wall)
{
	m_wall = wall;
}

bool Actor::getPerson() const
{
	return m_person;
}

void Actor::setPerson(bool person)
{
	m_person = person; 
}

bool Actor::getDumbZombie() const
{
	return m_Dzomb;
}

void Actor::setDumbZombie(bool zombie)
{
	m_Dzomb = zombie;
}

bool Actor::getSmartZombie() const
{
	return m_Szomb;
}

void Actor::setSmartZombie(bool zombie)
{
	m_Szomb = zombie;
}

bool Actor::getCitizen() const
{
	return m_citizen;
}

void Actor::setCitizen(bool citizen)
{
	m_citizen = citizen; 
}

int Actor::getTickk() const
{
	return m_tickk;
}

void Actor::setTickk(int tick)
{
	m_tickk += tick;
}

bool Actor::getifCitizenInfected() const
{
	return m_Cinfected;
}

void Actor::setifCitizenInfected(bool infected)
{
	m_Cinfected = infected;
}

bool Actor::getLandmineActive() const
{
	return m_landmine;
}

void Actor::setLandmineActive(bool mine)
{
	m_landmine = mine;
}

bool Actor::getFlame() const
{
	return m_flameee;
}

void Actor::setFlame(bool flame)
{
	m_flameee = flame; 
}

bool Actor::isFlame() const
{
	return false;
}

void Actor::setisFlame(bool flame)
{
}

Actor::~Actor()
{
}


/////////////////////////// PERSON IMPLEMENTATION ///////////////////////////////

Person::Person(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Actor(ID, startX, startY, depth, ptr)
{
}

Person::~Person()
{
}


///////////////////////// PENELOPE IMPLEMENTATION /////////////////////////////////

Penelope::Penelope(int ID, double startX, double startY, int depth, StudentWorld* pt)
	: Person(ID, startX, startY, depth, pt)
{
	setWorld(pt);
	setExit(true);
	setPen(true);
	setPerson(true); 
	setisFlammable(true); 
}

void Penelope::doSomething()
{
	// checks if Penelope is currently, If not, none of the following steps should be performed  
	if (getAlive())
	{
		// check if Penelope is infected
		if (getifInfected())  
		{
			getWorld()->setInfectedCount(1);
			if (getWorld()->getInfectedCount() == 500)
			{
				setAlive(false);
				getWorld()->playSound(SOUND_PLAYER_DIE);
				return;
			}

		}

		// check if Player pressed a key
		int ch;
		if (getWorld()->getKey(ch))
		{
			//user hit a key during this tick!
			switch (ch)
			{
			case KEY_PRESS_LEFT:
				//... move Penelope to the left ...;
				setDirection(left);
				if (getWorld()->determineBounds(this))
					moveTo(getX() - 4, getY());
				break;
			case KEY_PRESS_RIGHT:
				//... move Penelope to the right ...;
				setDirection(right);
				if (getWorld()->determineBounds(this))
					moveTo(getX() + 4, getY());
				break;
			case KEY_PRESS_UP:
				//... move Penelope to the right ...;
				setDirection(up);
				if (getWorld()->determineBounds(this))
					moveTo(getX(), getY() + 4);
				break;
			case KEY_PRESS_DOWN:
				//... move Penelope to the right ...;
				setDirection(down);
				if (getWorld()->determineBounds(this))
					moveTo(getX(), getY() - 4);
				break;
			case KEY_PRESS_SPACE:
				//... add flames in front of Penelope...; 

				// If player pressed Space key and Penelope has some flame charges left,
				// then penelope will attempt to fire 3 flames in the 3 slots in front of her
				if (getWorld()->getFlameCount() > 0)
				{
					getWorld()->setFlameCount(-1);

					// Penelope will add up to three new flame objects to the game.
					// If a flame at a specific position would overlap with a wall or exit object, then
					// flame is not generated. 
					for (int i = 1; i <= 3; i++)
					{

						if (getDirection() == up)
						{
							if (getWorld()->checkFlamePos(getX(), getY() + i * SPRITE_HEIGHT))
								return;
							Flame* f = new Flame(IID_FLAME, getX(), getY() + i * SPRITE_HEIGHT, 0, getWorld());
							getWorld()->addToList(f);
							getWorld()->playSound(SOUND_PLAYER_FIRE);
						}
						if (getDirection() == down)
						{
							if (getWorld()->checkFlamePos(getX(), getY() - i * SPRITE_HEIGHT))
								return;
							Flame* f = new Flame(IID_FLAME, getX(), getY() - i * SPRITE_HEIGHT, 0, getWorld());
							getWorld()->addToList(f);
							getWorld()->playSound(SOUND_PLAYER_FIRE);
						}
						if (getDirection() == left)
						{
							if (getWorld()->checkFlamePos(getX() - i * SPRITE_WIDTH, getY()))
								return;
							Flame* f = new Flame(IID_FLAME, getX() - i * SPRITE_WIDTH, getY(), 0, getWorld());
							getWorld()->addToList(f);
							getWorld()->playSound(SOUND_PLAYER_FIRE);
						}
						if (getDirection() == right)
						{
							if (getWorld()->checkFlamePos(getX() + i * SPRITE_WIDTH, getY()))
								return;
							Flame* f = new Flame(IID_FLAME, getX() + i * SPRITE_WIDTH, getY(), 0, getWorld());
							getWorld()->addToList(f);
							getWorld()->playSound(SOUND_PLAYER_FIRE);
						}
					}

				}
				break;
			case KEY_PRESS_TAB:
			{
				// add landmine to game
				if (getWorld()->getMineCount() > 0)
				{
					Landmine* l = new Landmine(IID_LANDMINE, getX(), getY(), 1, getWorld());
					getWorld()->addToList(l); 
					getWorld()->setMineCount(-1);
				}
			}
			case KEY_PRESS_ENTER:
			{
				// Use vaccine whether or not player is infected. 
				// If player uses vaccine while infected, player is no longer infected.  
				if (getWorld()->getVaccineCount() > 0)
				{
					setifInfected(false);
					getWorld()->setInfectedCount(-getWorld()->getInfectedCount());
					getWorld()->setVaccineCount(-1);
				}
			}

			}
		}
	}
	return;
}

Penelope::~Penelope()
{
}

//////////////////////////////// CITIZEN IMPLEMENTATION ////////////////////////////////////////

Citizen::Citizen(int ID, double startX, double startY, int depth, StudentWorld* pt)
	: Person(ID, startX, startY, depth, pt), m_infected(0)
{
	setCitizen(true);
	setBlock(true);
	setisFlammable(true); 
	setActorFellInPit(true);
	setExit(true);
}

void Citizen::doSomething()
{
	// Check if Citizen is alive 
	if (getAlive()) {
		
		// Check if Citizen is infected
		if (getifCitizenInfected()) 
		{
			setCitizenInfectedCount(1);

			// If Citizen is infected and count reaches 500, 
			// Citizen is turned into a zombie 
			if (getCitizenInfectedCount() == 500)
			{
				getWorld()->citizenGotInfected(this);
				return;
				
			}

		}

		// Citizen gets paralyzed every other tick trying to figure out what to do 
		setTickk(1);
		int remainder = getTickk() % 2;
		if (remainder == 0)
			return;

		// Distance from Citizen to Penelope
		double dist_p = getWorld()->distanceToPenelope(this);
		// Distance from Citizen to nearest zombie
		double dist_z = getWorld()->distanceToNearestZombie(this);
		// Euclidean distance from Citizen to Penelope
		double eDistToPenelope = getWorld()->eDistToPenelope(this);

		// If there are no zombies near Citizen and Penelope is close to the Citizen,
		// Citizen attempts to follow Penelope
		if ( (dist_p < dist_z || dist_z == -1) && eDistToPenelope <= 80*80) {

			// If Citizen is in the same column as Penelope and is not blocked,
			// Citizen will move closer to Penelope
			if (getX() == getWorld()->getPenelope()->getX()) {
				
				double currDistFromPerToPen = abs(getWorld()->getPenelope()->getY() - getY());
				double moveDownDistFromPerToPen = abs(getWorld()->getPenelope()->getY() - (getY() - 1));
				if (moveDownDistFromPerToPen < currDistFromPerToPen) {
					setDirection(down);
					if (getWorld()->determineBounds(this)) {
						moveTo(getX(), getY() - 2);
						return;
					}
					
				}
				else {
					setDirection(up);
					if (getWorld()->determineBounds(this)) {
						moveTo(getX(), getY() + 2);
						return;
					}
				}
					
			}

			// If Citizen is in the same column as Penelope and is not blocked,
			// Citizen will move closer to Penelope
			if (getY() == getWorld()->getPenelope()->getY()) {
				double currDistFromPerToPen = abs(getWorld()->getPenelope()->getX() - getX());
				double moveLeftDistFromPerToPen = abs(getWorld()->getPenelope()->getX() - (getX() - 1));
				if (moveLeftDistFromPerToPen < currDistFromPerToPen) {
					setDirection(left);
					if (getWorld()->determineBounds(this)) {
						moveTo(getX() - 2, getY());
						return;
					}

				}
				else {
					setDirection(right);
					if (getWorld()->determineBounds(this)) {
						moveTo(getX() + 2, getY());
						return;
					}
				}
			}


			// If Citizen not on same row or column as Penelope, determine the
			// one horizontal and the one vertical direction that would get the citizen
			// closer to Penelope and choose those directions at random. 
			// If Citizen will be blocked in one direction, choose the other of the 2 directions 
			// and move the Citizen. 
			double currDistFromPerToPenHorizontal = abs(getWorld()->getPenelope()->getX() - getX());
			double currDistFromPerToPenVertical = abs(getWorld()->getPenelope()->getY() - getY());

			double moveLeftDistFromPerToPen = abs(getWorld()->getPenelope()->getX() - (getX() - 1));
			double moveRightDistFromPerToPen = abs(getWorld()->getPenelope()->getX() - (getX() + 1));
			double moveDownDistFromPerToPen = abs(getWorld()->getPenelope()->getY() - (getY() - 1));
			double moveUpDistFromPerToPen = abs(getWorld()->getPenelope()->getY() - (getY() + 1));
			
			if (moveLeftDistFromPerToPen < currDistFromPerToPenHorizontal) {
				if (moveDownDistFromPerToPen < currDistFromPerToPenVertical) {
					int direct = randInt(1, 2);
					if (direct == 1) {
						setDirection(left);
						if (getWorld()->determineBounds(this)) {
							moveTo(getX() - 2, getY());
							return;
						}
					}
					else {
						setDirection(down);
						if (getWorld()->determineBounds(this)) {
							moveTo(getX(), getY() - 2);
							return;
						}
					}
				}

				if (moveUpDistFromPerToPen < currDistFromPerToPenVertical) {
					int direct = randInt(1, 2);
					if (direct == 1) {
						setDirection(left);
						if (getWorld()->determineBounds(this)) {
							moveTo(getX() - 2, getY());
							return;
						}
					}
					else {
						setDirection(up);
						if (getWorld()->determineBounds(this)) {
							moveTo(getX(), getY() + 2);
							return;
						}
					}
				}

			}

			if (moveRightDistFromPerToPen < currDistFromPerToPenHorizontal) {
				if (moveDownDistFromPerToPen < currDistFromPerToPenVertical) {
					int direct = randInt(1, 2);
					if (direct == 1) {
						setDirection(right);
						if (getWorld()->determineBounds(this)) {
							moveTo(getX() + 2, getY());
							return;
						}
					}
					else {
						setDirection(down);
						if (getWorld()->determineBounds(this)) {
							moveTo(getX(), getY() - 2);
							return;
						}
					}
				}

				if (moveUpDistFromPerToPen < currDistFromPerToPenVertical) {
					int direct = randInt(1, 2);
					if (direct == 1) {
						setDirection(right);
						if (getWorld()->determineBounds(this)) {
							moveTo(getX() + 2, getY());
							return;
						}
					}
					else {
						setDirection(up);
						if (getWorld()->determineBounds(this)) {
							moveTo(getX(), getY() + 2);
							return;
						}
					}
				}

			}
				
	
		}

		// Otherwise, Citizen was blocked from moving in either of the 2 directions. 
		// If a zombie is near the Citizen, Citizen wants to run away. 
		Actor* ptrToZombie = getWorld()->eDistFromCitizenToZombie(this);
		double distToNeartestZombieRight = -1;
		double distToNeartestZombieDown = -1;
		double distToNeartestZombieLeft = -1;
		double distToNeartestZombieUp = -1;

		// No zombies near Citizen
		if (ptrToZombie == nullptr) {
			return;
		}
		else {
			// While determining where to move:
			// If Citizen is blocked from moving in a direction, it ignores this direction
			// Otherwise, Citizen determines distance to nearest zombie if it were to move to a new location
			// and we store this location. 
			int tempDirection = getDirection();
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					setDirection(right); 
					if (getWorld()->determineBounds(this)) {
						distToNeartestZombieRight = getWorld()->distanceToNearestZombieFromNewLocation(this, getX() + 2, getY()); 
					}
				}
				if (i == 1) {
					setDirection(down); 
					if (getWorld()->determineBounds(this)) {
						distToNeartestZombieDown = getWorld()->distanceToNearestZombieFromNewLocation(this, getX(), getY() - 2); 
					}
				}
				if (i == 2) {
					setDirection(left);
					if (getWorld()->determineBounds(this)) {
						distToNeartestZombieLeft = getWorld()->distanceToNearestZombieFromNewLocation(this, getX() - 2, getY());
					}
				}
				if (i == 3) {
					setDirection(up);
					if (getWorld()->determineBounds(this)) {
						distToNeartestZombieUp = getWorld()->distanceToNearestZombieFromNewLocation(this, getX(), getY() + 2);
					}
				}
			}
			setDirection(tempDirection);

			// None of the new movement options would allow citizen to get further away from zombies
			// so Citizen does nothing more during this tick.
			double curDistToNearestZomb = getWorld()->distanceToNearestZombie(this);
			if (distToNeartestZombieRight < curDistToNearestZomb && distToNeartestZombieDown < curDistToNearestZomb
				&& distToNeartestZombieLeft < curDistToNearestZomb && distToNeartestZombieUp < curDistToNearestZomb)
				return;
			else {

				// Otherwise, check which direction takes Citizen further away from neartest zombie and move there. 

				if (distToNeartestZombieRight > distToNeartestZombieDown && distToNeartestZombieRight > distToNeartestZombieLeft
					&& distToNeartestZombieRight > distToNeartestZombieUp) {
					setDirection(right);
					moveTo(getX() + 2, getY());
					return;
				}

				if (distToNeartestZombieDown > distToNeartestZombieRight && distToNeartestZombieDown > distToNeartestZombieLeft
					&& distToNeartestZombieDown > distToNeartestZombieUp) {
					setDirection(down);
					moveTo(getX(), getY() - 2);
					return;
				}

				if (distToNeartestZombieLeft > distToNeartestZombieDown && distToNeartestZombieLeft > distToNeartestZombieRight
					&& distToNeartestZombieLeft > distToNeartestZombieUp) {
					setDirection(left);
					moveTo(getX() - 2, getY());
					return;
				}

				if (distToNeartestZombieUp > distToNeartestZombieDown && distToNeartestZombieUp > distToNeartestZombieLeft
					&& distToNeartestZombieUp > distToNeartestZombieRight) {
					setDirection(up);
					moveTo(getX(), getY() + 2);
					return;
				}
			}


		}

	}
	// If distance to nearest zombie is more than 80 pixels, do nothing

	return; 
}

Citizen::~Citizen() 
{
}

int Citizen::getCitizenInfectedCount() const
{
	return m_infected;
}

void Citizen::setCitizenInfectedCount(int infected)
{
	m_infected += infected;
}


///////////////////////////// ZOMBIE IMPLEMENTATION //////////////////////////////////////

Zombie::Zombie(int ID, double startX, double startY, int depth, StudentWorld* pt)
	: Person(ID, startX, startY, depth, pt)
{
	setActorFellInPit(true);
	setZombie(true);
	setBlock(true);
	setisFlammable(true);

	
}

void Zombie::doSomething()
{
	
}

Zombie::~Zombie()
{
}


/////////////////////////// DUMB ZOMBIE IMPLEMENTATION ///////////////////////////////////////

DumbZombie::DumbZombie(int ID, double startX, double startY, int depth, StudentWorld* pt)  
	: Zombie(ID, startX, startY, depth, pt), m_movePlan(0)
{	
	setDumbZombie(true);
}

void DumbZombie::doSomething()
{
	// Check if zombie is alive
	if (getAlive())
	{
		// Zombie becomes paralyzed every other tick
		setTickk(1);
		int remainder = getTickk() % 2;
		if (remainder == 0)
			return;

		// Check if zombie needs new movement plan because current plan is at 0
		if (getMovePlan() == 0)
		{
			// Pick a random movement plan distance from 3-10 inclusive 
			setMovePlan(randInt(3, 10));
			// Set random direction for zombie
			int dir = randInt(1, 4);
			if (dir == 1)
				setDirection(0);
			else if (dir == 2)
				setDirection(90);
			else if (dir == 3)
				setDirection(180);
			else if (dir == 4)
				setDirection(270);
		}
		else
		{
			// If current movement plan is not 0 yet, check if a Person (Penelope, Citizen)
			// is front of the zombie and if so, project vomit onto them
			// In addition, zombie will move 1 pixel in the directrion it is facing 
			// but if it is blocked, reset movement plan. 

			if (getDirection() == 0)
			{
				getWorld()->checkZombieFacingPen(this);

				if (getWorld()->determineBounds(this))
					moveTo(getX() + 1, getY());
				else {
					setMovePlan(0);
					return;
				}
			}
			
			if (getDirection() == 90)
			{
				getWorld()->checkZombieFacingPen(this);

				if (getWorld()->determineBounds(this))
					moveTo(getX(), getY() + 1);
				else {
					setMovePlan(0);
					return;
				}
			}
			
			if (getDirection() == 180)
			{
				getWorld()->checkZombieFacingPen(this);

				if (getWorld()->determineBounds(this))
					moveTo(getX() - 1, getY());
				else {
					setMovePlan(0);
					return;
				}
			}
			
			if (getDirection() == 270)
			{
				getWorld()->checkZombieFacingPen(this);

				if (getWorld()->determineBounds(this))
					moveTo(getX(), getY() - 1);
				else {
					setMovePlan(0);
					return;
				}
			}
		}
		// Once Zombie has moved, decrement movement plan distance
		setMovePlan(getMovePlan() - 1);
	}
	return;

}

DumbZombie::~DumbZombie()
{
}

int DumbZombie::getMovePlan() const
{
	return m_movePlan;
}

void DumbZombie::setMovePlan(int move)
{
	m_movePlan = move;
}

///////////////////////////// SMART ZOMBIE IMPLEMENTATION /////////////////////////////////////

SmartZombie::SmartZombie(int ID, double startX, double startY, int depth, StudentWorld* pt)
	: Zombie(ID, startX, startY, depth, pt), m_movePlan(0)
{
	setSmartZombie(true);
}

void SmartZombie::doSomething()
{
	// Check if zombie is alive 
	if (getAlive()) {

		// Zombie paralyzed every other tick
		setTickk(1);
		int remainder = getTickk() % 2;
		if (remainder == 0)
			return;
		
		// Check if movement plan is 0
		if (getMovePlan() == 0)
		{
			// Set movement plan to random distance and select the Person closest to Zombie.
			setMovePlan(randInt(3, 10));
			Actor* person = getWorld()->personClosestToSmartZomb(this);
			double distFromZombToPerson = sqrt(((getX() - person->getX()) * (getX() - person->getX())) + ((getY() - person->getY()) * (getY() - person->getY())));
			
			// If distance to nearest Person is more than 80 pixels, choose random direction
			if (distFromZombToPerson > 80) {
				int dir = randInt(1, 4);
				if (dir == 1)
					setDirection(0);
				else if (dir == 2)
					setDirection(90);
				else if (dir == 3)
					setDirection(180);
				else if (dir == 4)
					setDirection(270);
			}
			else {
				// Otherwise, nearest Person is less than or equal 80 pixels away 
				// so choose direction that will cause Zombie to get closer to Person.  
				
				// If Zombie and Person are on the same row or column, choose (only) direction 
				// that gets Zombie closer to Person.
				if (getX() == person->getX()) {
					double currDistFromZToP = abs(person->getY() - getY());
					double moveDownDistFromZToP = abs(person->getY() - (getY() - 1));
					if (moveDownDistFromZToP < currDistFromZToP)
						setDirection(down);
					else
						setDirection(up);
				}
				else if (getY() == person->getY()) {
					double currDistFromZToP = abs(person->getX() - getX());
					double moveLeftDistFromZToP = abs(person->getX() - (getX() - 1));
					if (moveLeftDistFromZToP < currDistFromZToP)
						setDirection(left);
					else
						setDirection(right);
				}
				
				// Z and Person not on same column or row, so choose randomly between 2 directions (horizonal & vertical)
				else {
					
					// Checking the sign of difference between Zombie and Person's horizontal and vertical 
					// distance to determine what 2 directions zombie will choose to get closer to Person. 

					if ((person->getX() - getX() > 0) && (person->getY() - getY() > 0)) {
						int direct = randInt(1, 2);
						if (direct == 1)
							setDirection(right);
						else
							setDirection(up);
					}
					if ((person->getX() - getX() < 0) && (person->getY() - getY() < 0)) {
						int direct = randInt(1, 2);
						if (direct == 1)
							setDirection(left);
						else
							setDirection(down);

					}
					if ((person->getX() - getX() > 0) && (person->getY() - getY() < 0)) {
						int direct = randInt(1, 2);
						if (direct == 1)
							setDirection(right);
						else
							setDirection(down);
					}
					if ((person->getX() - getX() < 0) && (person->getY() - getY() > 0)) {
						int direct = randInt(1, 2); 
						if (direct == 1)
							setDirection(left);
						else
							setDirection(up);
					}
				}

			}
		}
		else
		{
			// Zombie must check if Person is in front of it in direction it is facing. 
			// If so, just as for Dumb Zombie, Smart Zombie will project vomit if there is
			// a Person. 
			// In addition, Zombie will move in the direction it is facing unless blocked. 

			if (getDirection() == 0)
			{
				getWorld()->checkZombieFacingPen(this);

				if (getWorld()->determineBounds(this))
					moveTo(getX() + 1, getY());
				else {
					setMovePlan(0);
					return;
				}
			}                             

			if (getDirection() == 90)
			{
				getWorld()->checkZombieFacingPen(this);

				if (getWorld()->determineBounds(this))
					moveTo(getX(), getY() + 1);
				else {
					setMovePlan(0);
					return;
				}
			}

			if (getDirection() == 180)
			{
				getWorld()->checkZombieFacingPen(this);

				if (getWorld()->determineBounds(this))
					moveTo(getX() - 1, getY());
				else {
					setMovePlan(0);
					return;
				}
			}

			if (getDirection() == 270)
			{
				getWorld()->checkZombieFacingPen(this);

				if (getWorld()->determineBounds(this))
					moveTo(getX(), getY() - 1);
				else {
					setMovePlan(0);
					return;
				}
			}
		}

		// Decrement movement plan distance once Zombie has moved. 
		setMovePlan(getMovePlan() - 1);

	}
	return;
}

SmartZombie::~SmartZombie()
{
}

int SmartZombie::getMovePlan() const
{
	return m_movePlan;
}

void SmartZombie::setMovePlan(int move)
{
	m_movePlan = move;
}



////////////////////////// WALL IMPLEMENTATION /////////////////////////////////

Wall::Wall(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Actor(ID, startX, startY, depth, ptr)
{
	setBlock(true);
	setBlockFlame(true);
}

void Wall::doSomething()
{
}

Wall::~Wall()
{
}


//////////////////////// EXIT IMPLEMENTATION /////////////////////////////////

Exit::Exit(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Actor(ID, startX, startY, depth, ptr)
{
	setBlock(false);
	setBlockFlame(true);
	setExit(true);
}

void Exit::doSomething()
{
	// Check if Citizen(s) or Penelope overlap with Exit
	if (getWorld()->PersonOverlapsActor(this)) 
	{
		
	}
}

Exit::~Exit()
{
}

/////////////////////////// STATIONARY IMPLEMENTATION ////////////////////////////////

Stationary::Stationary(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Actor(ID, startX, startY, depth, ptr)
{

}

Stationary::~Stationary()
{
}


/////////////////////////// PIT IMPLEMENTATION /////////////////////////////////

Pit::Pit(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Stationary(ID, startX, startY, depth, ptr)
{
	setPit(true);
}

void Pit::doSomething()
{
	// Check if Penelope falls in Pit
	if (getWorld()->PenOverlapsActor(this))
	{
		setPenFellInPit(true);
		getWorld()->playSound(SOUND_PLAYER_DIE);
	}

	// Check if Smart Zombie, Dumb Zombie, or Citizen fall in Pit
	getWorld()->ActorOverlapsActor(this);

}

Pit::~Pit()
{
}

/////////////////////////////////// MINE IMPLEMENTATION ///////////////////////////////////

Landmine::Landmine(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Stationary(ID, startX, startY, depth, ptr), m_safetyTick(0)
{
	setLandmine(true);
	setisFlammable(true);
}

void Landmine::doSomething()
{
	// Check if landmine has been placed by player
	if (getAlive())
	{
		// If landmine is active, check if Person overlaps wit it 
		if (getLandmineActive()) {
			getWorld()->PersonOverlapsLandmine(this);
		}

		// Set safety tick counter to 1 once landmine is placed by player
		// and once counter reaches 50, set Landmine in 'active' state. 
		setSafetyTick(1);
		if (getSafetyTick() == 50)
		{
			
			setLandmineActive(true); 
			return;
			
		}
		

	}
	return;
}

Landmine::~Landmine()
{
}

int Landmine::getSafetyTick() const
{
	return m_safetyTick;
}

void Landmine::setSafetyTick(int tick)
{
	m_safetyTick += tick;
}


////////////////////////// GOODIES IMPLEMENTATION ////////////////////////////////////

Goodies::Goodies(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Actor(ID, startX, startY, depth, ptr)
{
	setisFlammable(true);
	setGoodies(true);
}

Goodies::~Goodies()
{
}


///////////////////////////// VACCINE IMPLEMENTATION ///////////////////////////////

VaccineGoodie::VaccineGoodie(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Goodies(ID, startX, startY, depth, ptr)
{
	setVaccine(true);
}

void VaccineGoodie::doSomething()
{
	// Check if vaccine goodie is currently in the level
	if (getAlive() == false)
	{

		return;
	}

	else
	{
		// Check if player picked up vaccine goodie
		if (getWorld()->PenOverlapsActor(this))
		{

			getWorld()->increaseScore(50);
			setAlive(false);
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->setVaccineCount(1);
		}

	}
}

VaccineGoodie::~VaccineGoodie()
{
}

///////////////////////////// GASCAN IMPLEMENTATION /////////////////////////////////////////

GasCanGoodie::GasCanGoodie(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Goodies(ID, startX, startY, depth, ptr)
{
}

void GasCanGoodie::doSomething()
{
	// Check if Gascan Goodie is in the level
	if (getAlive() == false)
		return;
	else
	{
		// Check if Penelope picks up Gascan Goodie
		if (getWorld()->PenOverlapsActor(this))
		{
			getWorld()->increaseScore(50);
			setAlive(false);
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->setFlameCount(5);
		}

	}

}

GasCanGoodie::~GasCanGoodie()
{
}

//////////////////////////////// LANDMINEGOODIE IMPLEMENTATION ////////////////////////////////

LandmineGoodie::LandmineGoodie(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Goodies(ID, startX, startY, depth, ptr)
{
}

void LandmineGoodie::doSomething()
{
	// Check if Landmine Goodie is in the level
	if (getAlive() == false)
		return;
	else
	{
		// Check if Penelope picks up Landmine Goodie
		if (getWorld()->PenOverlapsActor(this))
		{
			getWorld()->increaseScore(50);
			setAlive(false);
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->setMineCount(2);
		}
	}

}

LandmineGoodie::~LandmineGoodie()
{
}

//////////////////////////////// PROJECTILE IMPLEMENTATION /////////////////////////////////////

Projectile::Projectile(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Actor(ID, startX, startY, depth, ptr), m_tick(0)
{

}

Projectile::~Projectile()
{

}

int Projectile::getTick() const
{
	return m_tick;
}

void Projectile::setTick(int tick)
{
	m_tick += tick;
}

///////////////////////////////////  FLAME IMPLEMENTATION ////////////////////////////////////

Flame::Flame(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Projectile(ID, startX, startY, depth, ptr)
{
	setisFlame(true);   
	setFlame(true);
}

void Flame::doSomething()
{
	// Check if flame has been projected by either player or Landmine
	if (getAlive() == false)
	{
		return;
	}
	else
	{
		// Flame only lasts for 2 ticks 
		setTick(1);
		if (getTick() == 2)
		{
			setAlive(false);
			return;
		}
		// Check if Flame overlaps with Goodies, Persons, or Zombies 
		getWorld()->ifFlameOverlaps(this);

	}
}

Flame::~Flame()
{

}

////////////////////////////// VOMIT IMPLENTATION /////////////////////////////////////////////////

Vomit::Vomit(int ID, double startX, double startY, int depth, StudentWorld* ptr)
	: Projectile(ID, startX, startY, depth, ptr)
{
	setVomit(true);
	setisFlammable(false);
}

void Vomit::doSomething()
{
	// Check if zombie projected vomit
	if (getAlive() == false)
		return;
	else 
	{
		// Vomit only lasts for 2 ticks just like flame projectiles
		setTick(1);
		if (getTick() == 2)
		{
			setAlive(false);
			return;
		}
	}
}

Vomit::~Vomit()
{
}
