#include "witness.hpp"	
namespace KBEngine{	


//-------------------------------------------------------------------------------------
Witness::Witness()
{
}

//-------------------------------------------------------------------------------------
Witness::~Witness()
{
}

//-------------------------------------------------------------------------------------
static ObjectPool<Witness> _g_objPool;
ObjectPool<Witness>& Witness::ObjPool()
{
	return _g_objPool;
}

//-------------------------------------------------------------------------------------
void Witness::onReclaimObject()
{
}

//-------------------------------------------------------------------------------------
}
