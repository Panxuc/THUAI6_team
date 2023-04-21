#ifndef _PIGEON_H
#define _PIGEON_H

#include "API.h"
#include "AI.h"

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

class Encoder
{
private:
	static const int MaxLength = 255;
	char msg[MaxLength];
	int Pointer;
public:
	Encoder();
	void SetHeader(char header);
	template<typename T>
	void PushInfo(T info);
	std::string ToString();
};

class Decoder
{
private:
	std::string msg;
	int Pointer;
public:
	Decoder(std::string code);
	template<typename T>
	T ReadInfo();
};

class Pigeon
{
private:
	IStudentAPI& API;
public:
	Pigeon(IStudentAPI& api);
};

#endif