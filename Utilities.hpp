#ifndef _UTILITIES_H
#define _UTILITIES_H

#include "API.h"
#include "AI.h"
#include<stack>

class Point
{
public:
	Point(int x_ = 0, int y_ = 0) :x(x_), y(y_) {}
//	Point ToAcc() { return Point(x * 1000 + 500, y * 1000 + 500); }
//	Point ToNormal() { return Point(x / 1000, y / 1000); }
	int x;
	int y;
};
class Node :public Point
{
public:
	Node(int x_ = 0, int y_ = 0, int px_ = 0, int py_ = 0,
		float fc_ = FLT_MAX, float gc_ = FLT_MAX, float hc_ = FLT_MAX)
		:Point(x_, y_), parentX(px_), parentY(py_), fCost(fc_), gCost(gc_), hCost(hc_) {};
	Node(Point p, int px_ = 0, int py_ = 0,
		float fc_ = FLT_MAX, float gc_ = FLT_MAX, float hc_ = FLT_MAX)
		:Point(p), parentX(px_), parentY(py_), fCost(fc_), gCost(gc_), hCost(hc_) {};
	int parentX;
	int parentY;
	float fCost;
	float gCost;
	float hCost;
};

template<typename IFooAPI>
class Utilities
{
private:
	unsigned char Map[50][50];
	unsigned char Access[50][50];
	std::vector<Point> Classroom;
	std::vector<Point> Gate;
	std::vector<Point> OpenGate;
	std::vector<Point> Chest;
	std::vector<Point> Door;

	bool IsValidWithoutWindows(int x, int y);
	bool IsValidWithWindows(int x, int y);
	bool IsDestination(int x, int y, Node dest);
	double CalculateH(int x, int y, Node dest);
	std::vector<Node> MakePath(std::array<std::array<Node, 50>, 50> map, Node dest);
	std::vector<Node> AStarWithoutWindows(Node src, Node dest);
	std::vector<Node> AStarWithWindows(Node src, Node dest);

	const IFooAPI& API;
	Point TEMP;
	std::vector<THUAI6::PropType> Inventory;
	int cntFinishedClassroom, LastUpdateTime;
	const int UpdateInterval = 1000;
	bool ClassroomState[50][50], ChestState[50][50];

	void InitMap(IStudentAPI& api);

public:
	Utilities(IFooAPI api);

	// void Update(Point Door, bool State);			//���µ�ͼ��Ϣ�������ź�����У�ţ���ҪԼ��info�ĸ�ʽ
	void UpdateClassroom();
	void UpdateGate();
	void UpdateChest();
	void UpdateDoor();
	void AutoUpdate(); // TODO: �Զ����£���鸽���ĸ�����û�к���֪��һ�µģ�����о͸��²��ҹ㲥

	void MoveTo(Point Dest, bool WithWindows);		// ��Ŀ�ĵض�һ��
	void MoveToNearestClassroom(bool WithWindows);	// ���������ҵ�ķ���һ��
	void MoveToNearestGate(bool WithWindows);		// �������У���Ա߶�һ��
	void MoveToNearestChest(bool WithWindows);		// ����������ӵķ���һ��
	bool NearPoint(Point P, int level = 1);         // level=0�жϵ�ǰ�Ƿ��ڸø����ϣ�1�ж��Ƿ��ڸ����ϻ���Χ4��2�ж��Ƿ��ڸ����ϻ���Χ8��
	bool NearClassroom();							// �Ѿ�����ҵ�Ա�����
	bool NearGate();								// �Ѿ���У���Ա�����
	bool NearChest();								// �Ѿ��������Ա�����
	void DirectLearning(bool WithWindows);			// ǰ���������ҵ��ѧϰ
	void DirectOpeningChest(bool WithWindows);		// ǰ����������Ӳ�����
	void DirectProp(std::vector<unsigned char>Priority, int DistanceInfluence, int PropInfluence, bool WithWindows);		// ����ʹ�õ���

	int EstimateTime(Point Dest);					// ȥĿ�ĵص�Ԥ��ʱ��
	bool IsViewable(Point Src, Point Dest, int ViewRange);			// �ж�����λ���Ƿ����
	int CountFinishedClassroom() const;
	int CountNonemptyChest() const; // TODO: ��δʵ��

	void AssassinDefaultAttack(int rank);	// �̿���ͨ����
	bool AssassinDefaultAttackOver(int rank);
};

#include "UtilitiesBasic.hpp"
#include "UtilitiesAttack.hpp"
#include "UtilitiesAStar.hpp"

#endif
