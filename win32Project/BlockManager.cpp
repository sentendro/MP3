#include "BlockManager.h"



BlockManager::BlockManager()
{
	block[0] = new Block("점프", "y축을 이동시킨다.");
	block[1] = new Block("a", "b");
	block[2] = new Block("a", "b");
	block[3] = new Block("a", "b");
	block[4] = new Block("a", "b");
}


BlockManager::~BlockManager()
{
}

Block* BlockManager::getBlock(int blockNum)
{
	return block[blockNum];
}
