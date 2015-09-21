#pragma once
#include <iostream>
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/mysql/database.hxx>
#include "kpi_view.h"
#include "kpi_view-odb.hxx"
#include<map>
#include <odb/mysql/connection-factory.hxx>
#include<memory>
class KPIDatabaseManager{
public:
  //	bool init();
	bool GetKPIMap(const std::string& username,const std::string& password,const std::string& database);//获取kpi映射信息
	void SetInsertTableName(const std::string& table_name);//设置待插入数据表信息
	const std::string& FindKPIColumn(const std::string& kpi_english_name);
	std::string GenerateSQL(const std::string& columns,const std::string& values);//生成SQL语句
	bool ExecuSQL(const std::string& strSQL);//执行SQL语句
	bool InitDatabaseInfo(int min,int max,const std::string& username,const std::string&password,const std::string& database);
private:
	std::map<std::string,std::string> kpi_map_;
	std::string table_name_;
	std::shared_ptr<odb::database> db_shared_ptr_;
	//shared_ptr<odb::mysql::connection_factory> connection_pool_shared_ptr_;
};

