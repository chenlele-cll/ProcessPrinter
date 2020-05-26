#pragma once
#include <string>
#include <windows.h>

/*��������������������������������
��Ȩ����������ΪCSDN������������happy����ԭ�����£���ѭ CC 4.0 BY - SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https ://blog.csdn.net/weixin_39139505/article/details/90295704*/

struct ProcessInfo {
public:
	bool operator<(const ProcessInfo& pro);
	bool operator<=(const ProcessInfo& pro);
	bool operator>(const ProcessInfo& pro);
	bool operator>=(const ProcessInfo& pro);
	bool operator==(const ProcessInfo& pro);
public:
	std::string process_id;	//���� id
	std::string process_name;  //������
	int memory_usage;	//�ڴ�ʹ�����
	std::string elapsed_time;	//����ʱ��
};

bool ProcessInfo::operator<(const ProcessInfo& pro) {
	return this->memory_usage < pro.memory_usage;
}

bool ProcessInfo::operator>(const ProcessInfo& pro) {
	return this->memory_usage > pro.memory_usage;
}

bool ProcessInfo::operator<=(const ProcessInfo& pro) {
	return this->memory_usage <= pro.memory_usage;
}

bool ProcessInfo::operator>=(const ProcessInfo& pro) {
	return this->memory_usage >= pro.memory_usage;
}

bool ProcessInfo::operator==(const ProcessInfo& pro) {
	return this->memory_usage == pro.memory_usage;
}

