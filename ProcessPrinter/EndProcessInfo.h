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
	std::string process_id;	//进程 id
	std::string process_name;  //进程名
	std::string elapsed_time;	//持续时间
	std::string end_time;	//结束时间
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
