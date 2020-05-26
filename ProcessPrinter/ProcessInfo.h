#pragma once
#include <string>
#include <windows.h>

/*————————————————
版权声明：本文为CSDN博主「陈乐乐happy」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https ://blog.csdn.net/weixin_39139505/article/details/90295704*/

struct ProcessInfo {
public:
	bool operator<(const ProcessInfo& pro);
	bool operator<=(const ProcessInfo& pro);
	bool operator>(const ProcessInfo& pro);
	bool operator>=(const ProcessInfo& pro);
	bool operator==(const ProcessInfo& pro);
public:
	std::string process_id;	//进程 id
	std::string process_name;  //程序名
	int memory_usage;	//内存使用情况
	std::string elapsed_time;	//持续时间
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

