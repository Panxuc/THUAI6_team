#include <array>
#include <cmath>
#include <queue>
#include <stack>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <algorithm>
#include <functional>
#include "AI.h"
#include "API.h"
#include "constants.h"
#include "Utilities.hpp"
#include "Pigeon.h"

// Ϊ����play()�ڼ�ȷ����Ϸ״̬�����£�Ϊ����ֻ��֤��Ϸ״̬�ڵ�����ط���ʱ������
extern const bool asynchronous = false;

// ѡ����Ҫ���ν�player0��player4��ְҵ�����ﶨ��

extern const std::array<THUAI6::StudentType, 4> studentType = {
	THUAI6::StudentType::StraightAStudent,
	THUAI6::StudentType::StraightAStudent,
	THUAI6::StudentType::Teacher,
	THUAI6::StudentType::Sunshine };

extern const THUAI6::TrickerType trickerType = THUAI6::TrickerType::Assassin;

//������AI.cpp�ڲ����������뺯��

/* ����״̬
sCantMove �������ã�����/ǰ��ҡ/��ҵ������
sDefault Ĭ��
sDoClassroom ȥд��ҵ/��д��ҵ
sOpenGate ȥ��У��/�ڿ�У��
sOpenChest ȥ������/�ڿ�����
sDanger Ӧ��Σ��
sRousing ����ĳ��
sEncouraging ����ĳ��
sPicking ȥ�����
���������н�ɫ�ձ�ӵ�е�״̬������״̬��Ҫ���ж��壬�����0x80��ʼ
�����˶�Ա���Զ���һ��״̬������Ӳ�գ���ʦ���Զ���һ��״̬��Ѳ�ߣ���ͼ����Ұ�ڸ��ŵ��������ȵ�
�����߼�����ÿ��AI::Play���������Ϣ������ά�ֵ�ǰ״̬����������һ��״̬��������ͼ���ģ��˼ά��
��ҪһЩ�ռ䴢���Ҫ����Ϣ�����ܻ��õ�ͨ��
������Ը�����״̬�ָ���������ȼ�������д����
*/
#define sCantMove 0x00
#define sDefault 0x10
#define sDoClassroom 0x11
#define sOpenGate 0x12
#define sOpenChest 0x13
#define sDanger 0x14
#define sRousing 0x15
#define sEncouraging 0x16
#define sPicking 0x17


void AI::play(IStudentAPI& api)
{
	static std::vector<unsigned char> Priority(9, 0U);
	static Pigeon gugu(api);
	static Utilities<IStudentAPI&> Helper(api);
	static int CurrentState = sDefault;

	// ��������
	if (this->playerID == 0)
	{
		
		if (Helper.CountNonemptyChest() >= 7) Helper.DirectOpeningChest(true);
		else if (api.GetProps().size() > 0) Helper.DirectProp(Priority, 1, 1, true);

		// ���0ִ�в���
	}
	else if (this->playerID == 1)
	{
		Helper.DirectLearning(1);
		return;
		Helper.AutoUpdate();
		while (gugu.receiveMessage()); // ����Ϣ

		std::shared_ptr<const THUAI6::Student> selfinfo = api.GetSelfInfo();
		std::vector<std::shared_ptr<const THUAI6::Tricker>> tinfo = api.GetTrickers();
		if (CurrentState != sDanger)
		{
			if (!tinfo.empty())
			{
				api.EndAllAction();
				gugu.sendTrickerInfo(0, tinfo);
				gugu.sendTrickerInfo(2, tinfo);
				gugu.sendTrickerInfo(3, tinfo);
				CurrentState = sDanger;
			}
		}
		if (CurrentState == sDefault)
		{
			if (Helper.CountFinishedClassroom() <= 7) CurrentState = sDoClassroom;
			else CurrentState = sOpenGate;
		}
		if (CurrentState == sDoClassroom)
		{
			Helper.DirectLearning(1);
			if (Helper.CountFinishedClassroom() > 7) CurrentState = sDefault;
			// ѧ���˾���
		}
		else if (CurrentState == sOpenGate)
		{
			if (!Helper.NearGate()) Helper.MoveToNearestGate(1);
			else api.StartOpenGate();
		}
		// ���1ִ�в���
	}
	else if (this->playerID == 2)
	{
		// ���2ִ�в���
	}
	else if (this->playerID == 3)
	{
		// ���3ִ�в���
	}
	//��Ȼ����д��if (this->playerID == 2||this->playerID == 3)֮��Ĳ���
	// ��������
}

void AI::play(ITrickerAPI& api)
{
	auto self = api.GetSelfInfo();
	api.PrintSelfInfo();
}