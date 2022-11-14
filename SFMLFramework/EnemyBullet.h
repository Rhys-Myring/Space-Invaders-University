#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "Bullet.h"

//-----------------------------------------------------
// Class	:	EnemyBullet
// Purpose	:	To manage an enemy bullet object
// Usage	:	EnemyBullet enemyBullet;
//				EnemyBullet.update( deltaTime );
// See also	:	Bullet
//-----------------------------------------------------
class EnemyBullet : public Bullet
{
private:

public:
	// Constructor
	EnemyBullet();

	// Destructor
	~EnemyBullet();
};

#endif  // !ENEMYBULLET_H