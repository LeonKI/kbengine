#include "baseapp.hpp"
#include "backup_sender.hpp"
#include "server/serverconfig.hpp"

namespace KBEngine{	
float backupPeriod = 0.0;

//-------------------------------------------------------------------------------------
BackupSender::BackupSender():
backupEntityIDs_(),
backupRemainder_(0.f)
{
}

//-------------------------------------------------------------------------------------
BackupSender::~BackupSender()
{
	backupEntityIDs_.clear();
}

//-------------------------------------------------------------------------------------
void BackupSender::tick()
{
	int32 periodInTicks = secondsToTicks(ServerConfig::getSingleton().getBaseApp().backupPeriod, 0);
	if (periodInTicks == 0)
		return;

	// ����Ա��ݵ�entity��һ�·�������
	// ����㷨����������д�ı������ڻ����tick������ ÿ��tick����һ����entity
	float numToBackUpFloat = float(Baseapp::getSingleton().pEntities()->size()) / periodInTicks + backupRemainder_;

	// ���α��ݵ�����
	int numToBackUp = int(numToBackUpFloat);

	// ��������ȵ��µ���ʧ����
	backupRemainder_ = numToBackUpFloat - numToBackUp;

	// ������ݱ���û�������������²���һ���µ�
	if (backupEntityIDs_.empty())
	{
		this->createBackupTable();
	}

	Mercury::Bundle bundle;
	while((numToBackUp > 0) && !backupEntityIDs_.empty())
	{
		Base * pBase = Baseapp::getSingleton().findEntity(backupEntityIDs_.back());
		backupEntityIDs_.pop_back();
		
		MemoryStream* s = MemoryStream::ObjPool().createObject();
		if (pBase && backup(*pBase, *s))
		{
			--numToBackUp;
			bundle.append(*s);
		}
		MemoryStream::ObjPool().reclaimObject(s);
	}
}

//-------------------------------------------------------------------------------------
bool BackupSender::backup(Base& base, MemoryStream& s)
{
	// ���￪ʼ����Ҫ���ݵ�����д����
	base.writeBackupData(&s);
	return true;
}

//-------------------------------------------------------------------------------------
void BackupSender::createBackupTable()
{
	backupEntityIDs_.clear();

	Entities<Base>::ENTITYS_MAP::const_iterator iter = Baseapp::getSingleton().pEntities()->getEntities().begin();

	for(; iter != Baseapp::getSingleton().pEntities()->getEntities().end(); iter++)
	{
		backupEntityIDs_.push_back(iter->first);
	}

	// ���һ������
	std::random_shuffle(backupEntityIDs_.begin(), backupEntityIDs_.end());
}

}