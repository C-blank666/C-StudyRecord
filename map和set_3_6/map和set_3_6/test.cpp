//#include <iostream>
//#include <map>
//#include <string>
//#include <cctype>
//#include <sstream>
//
//// 辅助函数：清洗单词（转为小写，移除非字母字符）
//std::string clean_word(const std::string& word) {
//	std::string cleaned;
//	for (char c : word) {
//		if (std::isalpha(c)) {
//			cleaned += std::tolower(c);
//		}
//	}
//	return cleaned;
//}
//
//int main() {
//	std::map<std::string, int> word_counts;
//	std::string line;
//
//	// 读取输入文本
//	std::cout << "请输入文本（Ctrl+Z结束输入）：" << std::endl;
//	while (std::getline(std::cin, line)) {
//		std::istringstream iss(line);
//		std::string word;
//		while (iss >> word) {
//			// 清洗单词
//			std::string cleaned = clean_word(word);
//			if (!cleaned.empty()) {
//				word_counts[cleaned]++;
//				// 任务1：统计单词频率（使用operator[]）
//				// [补充代码]
//
//			}
//		}
//	}
//
//	// 任务2：拷贝并修改次数（使用拷贝构造函数）
//	std::map<std::string, int> doubled_counts(word_counts);
//	for (auto& [word, count] : doubled_counts) {
//		// [补充代码：仅翻倍次数>1的单词]
//		if (count > 1) count *= 2;
//
//	}
//
//	// 任务3：删除次数≤2的单词（使用erase和迭代器）
//	auto it = doubled_counts.begin();
//	while (it != doubled_counts.end()) {
//		// [补充代码：条件判断并删除]
//		if (it->second <= 2) {
//			auto tmp = it;
//			++it;
//			doubled_counts.erase(tmp->first);
//		}
//		else ++it;
//	}
//
//	// 任务4：输出结果（使用迭代器）
//	std::cout << "\n最终统计结果：" << std::endl;
//	for (const auto e : doubled_counts) {
//		std::cout << e.first << ":"<<e.second;
//	}
//
//	return 0;
//}