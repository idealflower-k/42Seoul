#include "utils.hpp"

const char* logTimeFormat::accessTimeFormat = "[%d/%b/%Y %H:%M:%S] ";
const char* logTimeFormat::errorTimeFormat = " %Y/%m/%d %H:%M:%S ";
const char* logTimeFormat::systemTimeFormat = " %a, %d %b %Y %H:%M:%S ";
const char* logTimeFormat::GMTtimeFormat = "%a, %d %b %Y %H:%M:%S GMT";
const char* logTimeFormat::UTCtimeFormat = "%Y-%m-%dT%H:%M:%SZ";
const char* logTimeFormat::dirListFormat = "%d-%b-%Y %H:%M";

namespace utils {

	std::string itos(const int& num) {
		std::ostringstream os;
		os << num;
		return os.str();
	}

	std::string lltos(const long long& num) {
		std::ostringstream os;
		os << num;
		return os.str();
	}

	extern unsigned int stringToDecimal(const std::string& value) {
		if (value.empty()) {
			throw std::runtime_error("error: empty string");
		}

		char unit = value[value.size() - 1];
		std::string numberPart = value;

		// 단위 검사
		if (isdigit(unit) == false) {
			numberPart = value.substr(0, value.size() - 1);
			switch (unit) {
				case 'm':
				case 'M':
					return atoi(numberPart.c_str()) * 1048576;
				case 'k':
				case 'K':
					return atoi(numberPart.c_str()) * 1024;
				default:
					throw std::runtime_error("error: invalid unit");
			}
		}
		return atoi(value.c_str());
	}

	std::string getCurTime(const char* format) {
		const std::time_t t = std::time(NULL);
		const std::tm* localTime = std::localtime(&t);

		char buf[FT];
		std::strftime(buf, sizeof(buf), format, localTime);

		return std::string(buf);
	}

	std::string formatTime(const std::time_t t, const char* format) {
		const std::tm* localTime = std::localtime(&t);

		char buf[FT];
		std::strftime(buf, sizeof(buf), format, localTime);

		return std::string(buf);
	}

	unsigned int stoui(const std::string s) {
		if (s == "")
			return 0;
		unsigned int i;
		std::istringstream(s) >> i;
		return i;
	}

	std::vector<std::string> split(std::string input, const std::string& delimiter) {
		std::vector<std::string> rv;
		size_t pos = 0;
		std::string token;
		while ((pos = input.find(delimiter)) != std::string::npos) {
			token = input.substr(0, pos);
			rv.push_back(token);
			input.erase(0, pos + delimiter.length());
		}
		if (input.size() > 0)
			rv.push_back(input);
		return rv;
	}

	std::string join(std::vector<std::string>& elems, std::string delim) {
		std::stringstream ss;
		std::vector<std::string>::iterator it = elems.begin();

		ss << *it++;
		while (it != elems.end())
			ss << delim << *it++;
		return ss.str();
	}

	std::string trim(const std::string& source) {
		std::string s(source);
		s.erase(0, s.find_first_not_of(" \n\r\t"));
		s.erase(s.find_last_not_of(" \n\r\t") + 1);
		return s;
	}

	fd_t makeFd(const char* path, const char* option) {
		FILE* file = fopen(path, option);
		if (file == NULL)
			return FD_ERROR;
		const fd_t fileFd = fileno(file);
		return (fileFd);
	}

	std::string generateRandomString() {
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		std::string randomString;
		std::srand(static_cast<unsigned int>(std::time(NULL)));

		for (int i = 0; i < 32; ++i) {
			randomString += alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		return randomString;
	}

	std::string removeSubstring(const std::string& mainStr, const std::string& substr) {
		std::string result = mainStr;
		size_t pos = result.find(substr);

		// 만약 substr이 mainStr 안에 있다면 해당 부분 제거
		if (pos != std::string::npos) {
			result.erase(pos, substr.length());
		}

		return result;
	}

	std::string generateRandomHexColor() {
		std::string hexColor = "#";

		// srand를 호출하여 시드를 설정합니다.
		std::srand(static_cast<unsigned int>(std::time(NULL)));

		// 6번 반복하여 6자리의 랜덤한 Hex 값을 생성합니다.
		for (int i = 0; i < 6; ++i) {
			int randomValue = std::rand() % 16;	 // 0부터 15 사이의 값
			char hexDigit = randomValue < 10 ? '0' + randomValue : 'A' + (randomValue - 10);
			hexColor += hexDigit;
		}

		return hexColor;
	}

}  // namespace utils
