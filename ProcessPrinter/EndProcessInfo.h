#pragma once

#include <string>

struct EndProcessInfo{
public:
	bool operator<(const EndProcessInfo& pro);
	bool operator<=(const EndProcessInfo& pro);
	bool operator>(const EndProcessInfo& pro);
	bool operator>=(const EndProcessInfo& pro);
	bool operator==(const EndProcessInfo& pro);
public:
	std::string process_id;	//���� id
	std::string process_name;  //������
	std::string elapsed_time;	//����ʱ��
	std::string end_time;	//����ʱ��
};

bool EndProcessInfo::operator<(const EndProcessInfo& pro) {
	return this->end_time < pro.end_time;
}

bool EndProcessInfo::operator>(const EndProcessInfo& pro) {
	return this->end_time > pro.end_time;
}

bool EndProcessInfo::operator<=(const EndProcessInfo& pro) {
	return this->end_time <= pro.end_time;
}

bool EndProcessInfo::operator>=(const EndProcessInfo& pro) {
	return this->end_time >= pro.end_time;
}

bool EndProcessInfo::operator==(const EndProcessInfo& pro) {
	return this->end_time == pro.end_time;
}
