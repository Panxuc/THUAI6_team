#include"AI.h"
#include"API.h"

class Point
{
public:
	Point(int x_ = 0, int y_ = 0) :x(x_), y(y_) {}
	Point ToAcc() { return Point(x * 1000 + 500, y * 1000 + 500); }
	Point ToNormal() { return Point(x / 1000, y / 1000); }
	int x;
	int y;
};

template<class IFooAPI>
class Utilities
{
private:
	IFooAPI API;
public:
	Utilities(IFooAPI api) : API(api) {}

	// void Update(std::string info); ���µ�ͼ��Ϣ�������ź�����У�ţ���ҪԼ��info�ĸ�ʽ
	void MoveTo(Point Dest); // ��Ŀ�ĵض�һ��
	// void MoveToAccurate(Point Dest);
	bool NearPoint(Point P, int level = 1); // level=0�жϵ�ǰ�Ƿ��ڸø����ϣ�1�ж��Ƿ��ڸ����ϻ���Χ4��2�ж��Ƿ��ڸ����ϻ���Χ8��
	void MoveToNearestGate(); // �������У���Ա߶�һ��
	bool NearGate(); // �Ѿ���У���Ա�����
	void MoveToNearestHomework(); // ���������ҵ�ķ���һ��
	bool NearHomework(); // �Ѿ�����ҵ�Ա�����
	int EstimateTime(Point Dest); // ȥĿ�ĵص�Ԥ��ʱ��
};

/* ��ϢЭ��
��Ϣͷ��info[0]��
MapUpdate ��ͼ����

TrickerInfo ��������Ϣ

NeedHelp ����֧Ԯ
	info[1-2]������
WantTool �����ȡ���ߣ�������Ҫ��������Ȼ̫Զ����ȥ�����㣩
*/
#define MapUpdate 0x01
#define TrickerInfo 0x02
#define NeedHelp 0x03
#define WantTool 0x04

/* ����״̬
CantMove �������ã�����/ǰ��ҡ/��ҵ������
Default Ĭ��
DoHomework ȥд��ҵ/��д��ҵ
OpenGate ȥ��У��/�ڿ�У��
OpenChest ȥ������/�ڿ�����
Danger Ӧ��Σ��
Rousing ����ĳ��
Encouraging ����ĳ��
Picking ȥ�����
���������н�ɫ�ձ�ӵ�е�״̬������״̬��Ҫ���ж��壬�����0x80��ʼ
�����˶�Ա���Զ���һ��״̬������Ӳ�գ���ʦ���Զ���һ��״̬��Ѳ�ߣ���ͼ����Ұ�ڸ��ŵ��������ȵ�
�����߼�����ÿ��AI::Play���������Ϣ������ά�ֵ�ǰ״̬����������һ��״̬��������ͼ���ģ��˼ά��

��ҪһЩ�ռ䴢���Ҫ����Ϣ�����ܻ��õ�ͨ��

������Ը�����״̬�ָ���������ȼ�������д����
*/
#define CantMove 0x00
#define Default 0x10
#define DoHomework 0x11
#define OpenGate 0x12
#define OpenChest 0x13
#define Danger 0x14
#define Rousing 0x15
#define Encouraging 0x16
#define Picking 0x17