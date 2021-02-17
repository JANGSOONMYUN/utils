#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <ctime>
#include <filesystem>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

// Create the class as public in the calibration class of unmanaged c++
// Load the class in other classes
class LogWriter {
public:
	LogWriter() {
		
		clock_t t0, t1, t_tmp;
		t0 = clock();
		t1 = clock();


		time_t lt0;
		lt0 = time(NULL);
		pTm = localtime(&lt0);
		
	}

	LogWriter(std::string path, std::string name, struct tm* pTime) {
		log_path = path;
		log_name = name;
		pTm = pTime;
	}

	~LogWriter() {
		pTm = nullptr;
		delete pTm;
	}

private:
	std::string log_path;
	std::string log_name;
	std::string log_status;
	struct tm* pTm;


public:
	void setDirPath(std::string path) {
		log_path = path;
		std::filesystem::create_directories(log_path);
	}

	void setLogName(std::string name) {
		log_name = name;
	}

	void setLogStat(std::string stat) {
		log_status = stat;
	}

	void writeLog(std::string str) {
		clock_t t0, t1, t_tmp;
		t0 = clock();
		t1 = clock();

		struct tm* pTm;
		time_t lt0;
		lt0 = time(NULL);
		pTm = localtime(&lt0);

		//std::cout << pTm->tm_year + 1900 << std::endl;
		//std::cout << pTm->tm_mon + 1 << std::endl;
		//std::cout << pTm->tm_mday << std::endl;
		//std::cout << pTm->tm_hour << std::endl;
		//std::cout << pTm->tm_min << std::endl;
		//std::cout << pTm->tm_sec << std::endl;

		std::string log_all;
		std::string log_date;
		log_date = "[" + std::to_string(pTm->tm_year + 1900) + "/" + std::to_string(pTm->tm_mon + 1) + "/" + std::to_string(pTm->tm_mday)
					+ "_" + std::to_string(pTm->tm_hour) + ":" + std::to_string(pTm->tm_min) + ":" + std::to_string(pTm->tm_sec) + "]";
		//std::cout << log_date << std::endl;
		//log_status = "[OK]";

		log_all = log_date + " " + log_status + " " + str;
		std::cout << log_all << std::endl;

		std::fstream fs_log;
		std::string file_path = log_path + "/" + std::to_string(pTm->tm_year + 1900) + "_" + std::to_string(pTm->tm_mon + 1) 
								+ "_" + std::to_string(pTm->tm_mday) + "_" + log_name + ".txt";
		fs_log.open(file_path, std::ios::app);
		fs_log << log_all << std::endl;
		fs_log.close();
	}


	void writeAnyLog(std::string str, struct tm* pTm) {
		
		std::string log_all;
		std::string log_date;
		log_date = std::to_string(pTm->tm_year + 1900) + "_" + std::to_string(pTm->tm_mon + 1) + "_" + std::to_string(pTm->tm_mday)
			+ "_" + std::to_string(pTm->tm_hour) + "_" + std::to_string(pTm->tm_min) + "_" + std::to_string(pTm->tm_sec);

		log_all = str;
		std::cout << log_all;

		std::string any_log_path = log_path + "/any";
		std::filesystem::create_directory(any_log_path);

		std::fstream fs_log;
		std::string file_path = any_log_path + "/" + log_date + "_" + log_name + ".txt";
		fs_log.open(file_path, std::ios::app);
		fs_log << log_all;
		fs_log.close();
	}

	void writeAnyLog(int log, struct tm* pTm) {
		std::string str = std::to_string(log);
		writeAnyLog(str, pTm);
	}

	void writeAnyLog(float log, struct tm* pTm) {
		std::string str = std::to_string(log);
		writeAnyLog(str, pTm);
	}

	void writeAnyLog(double log, struct tm* pTm) {
		std::string str = std::to_string(log);
		writeAnyLog(str, pTm);
	}


	void writeAnyLog(std::string str) {

		std::string log_all;
		std::string log_date;
		log_date = std::to_string(pTm->tm_year + 1900) + "_" + std::to_string(pTm->tm_mon + 1) + "_" + std::to_string(pTm->tm_mday)
			+ "_" + std::to_string(pTm->tm_hour) + "_" + std::to_string(pTm->tm_min) + "_" + std::to_string(pTm->tm_sec);

		log_all = str;
		std::cout << log_all;

		std::string any_log_path = log_path + "/any";
		std::filesystem::create_directory(any_log_path);

		std::fstream fs_log;
		std::string file_path = any_log_path + "/" + log_date + "_" + log_name + ".txt";
		fs_log.open(file_path, std::ios::app);
		fs_log << log_all;
		fs_log.close();
	}
	void writeAnyLog(int log) {
		std::string str = std::to_string(log);
		writeAnyLog(str);
	}

	void writeAnyLog(float log) {
		std::string str = std::to_string(log);
		writeAnyLog(str);
	}

	void writeAnyLog(double log) {
		std::string str = std::to_string(log);
		writeAnyLog(str);
	}

	void writeAnyLog(cv::Mat log) {
		std::string log_date;
		log_date = std::to_string(pTm->tm_year + 1900) + "_" + std::to_string(pTm->tm_mon + 1) + "_" + std::to_string(pTm->tm_mday)
			+ "_" + std::to_string(pTm->tm_hour) + "_" + std::to_string(pTm->tm_min) + "_" + std::to_string(pTm->tm_sec);

		std::cout << log;

		std::string any_log_path = log_path + "/any";
		std::filesystem::create_directory(any_log_path);

		std::string file_path = any_log_path + "/" + log_date + "_" + log_name + ".txt";

		cv::FileStorage fs_cv;
		fs_cv.open(file_path, cv::FileStorage::APPEND);
		fs_cv << "mat" << log;
		fs_cv.release();
	}

	void writeLineChange() {
		writeAnyLog("\n");
	}

};




void main() {
	LogWriter lw;
	lw.setDirPath("./");
	lw.setLogName("robot_log");
	lw.setLogStat("[OK]");
	lw.writeLog("robot");


	LogWriter lw_system;
	lw_system.setDirPath("./");
	lw_system.setLogName("system_log");
	lw_system.setLogStat("[OK]");
	lw_system.writeLog("system");

	LogWriter lw_detection;
	lw_detection.setDirPath("./");
	lw_detection.setLogName("detect_log");
	lw_detection.setLogStat("[OK]");
	lw_detection.writeLog("detection");



	clock_t t0, t1, t_tmp;
	t0 = clock();
	t1 = clock();

	struct tm* pTm;
	time_t lt0;
	lt0 = time(NULL);
	pTm = localtime(&lt0);

	lw.writeAnyLog("lllllll", pTm);
	lw.writeAnyLog("_lllllll", pTm);
	lw.writeAnyLog("lllllll\n", pTm);
	lw.writeAnyLog("lllllll\n", pTm);

	lw.writeAnyLog("lllllll\n", pTm);
	lw.writeAnyLog("lllllll\n", pTm);
	lw.writeAnyLog("lllllll\n", pTm);



	cv::Mat cv_mat = cv_mat.eye(4, 4, CV_16U);

	LogWriter lw_any;
	lw_any.setDirPath("./");
	lw_any.setLogName("any_log");
	lw_any.setLogStat("[OK]");
	lw_any.writeAnyLog("sdasdqq"); lw_any.writeLineChange();
	lw_any.writeAnyLog("sdasdqq\n");
	lw_any.writeAnyLog("sdasdqq\n");
	lw_any.writeAnyLog(cv_mat);
	lw_any.writeAnyLog(1234);
	lw_any.writeLineChange();
	lw_any.writeAnyLog(44.31241232313);

}