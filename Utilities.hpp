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

	// void Update(Point Door, bool State);			//更新地图信息，比如门和隐藏校门，需要约定info的格式
	void UpdateClassroom();
	void UpdateGate();
	void UpdateChest();
	void UpdateDoor();
	void AutoUpdate(); // TODO: 自动更新，检查附近的格子有没有和已知不一致的，如果有就更新并且广播

	void MoveTo(Point Dest, bool WithWindows);		// 往目的地动一动
	void MoveToNearestClassroom(bool WithWindows);	// 往最近的作业的方向动一动
	void MoveToNearestGate(bool WithWindows);		// 往最近的校门旁边动一动
	void MoveToNearestChest(bool WithWindows);		// 往最近的箱子的方向动一动
	bool NearPoint(Point P, int level = 1);         // level=0判断当前是否在该格子上，1判断是否在格子上或周围4格，2判断是否在格子上或周围8格
	bool NearClassroom();							// 已经在作业旁边了吗？
	bool NearGate();								// 已经在校门旁边了吗？
	bool NearChest();								// 已经在箱子旁边了吗？
	void DirectLearning(bool WithWindows);			// 前往最近的作业并学习
	void DirectOpeningChest(bool WithWindows);		// 前往最近的箱子并开箱
	void DirectProp(std::vector<unsigned char>Priority, int DistanceInfluence, int PropInfluence, bool WithWindows);		// 捡与使用道具

	int EstimateTime(Point Dest);					// 去目的地的预估时间
	bool IsViewable(Point Src, Point Dest, int ViewRange);			// 判断两个位置是否可视
	int CountFinishedClassroom() const;
	int CountNonemptyChest() const; // TODO: 暂未实现

	void AssassinDefaultAttack(int rank);	// 刺客普通攻击
	bool AssassinDefaultAttackOver(int rank);
};

#include "UtilitiesBasic.hpp"
#include "UtilitiesAttack.hpp"
#include "UtilitiesAStar.hpp"

#endif
