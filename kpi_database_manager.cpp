#include"kpi_database_manager.h"
bool KPIDatabaseManager::GetKPIMap(const std::string& username,const std::string& password,const std::string& database)
{
  bool ret=true;
  try{
    std::auto_ptr<odb::database> db (new odb::mysql::database (username,password,database));
	typedef odb::query<KPIView> query;
	typedef odb::result<KPIView> result;
	
	odb::transaction t (db->begin ());
	// t.tracer (stderr_tracer);
	result r1(db->query<KPIView>());
	for (result::iterator i (r1.begin ()); i != r1.end (); ++i)
	    kpi_map_.insert(make_pair(i->kpi_english_name,i->kpi_index));	
	t.commit ();
  }
  catch(...){
    ret=false;
  }
  return ret;
}

void KPIDatabaseManager::SetInsertTableName(const std::string& table_name)
{
  table_name_=table_name;
}

const std::string& KPIDatabaseManager::FindKPIColumn(const std::string& kpi_english_name)
{
  auto pos=kpi_map_.find(kpi_english_name);
  if(pos!=kpi_map_.end())
    return pos->second;
  else
    return "";
}

std::string KPIDatabaseManager::GenerateSQL(const std::string& columns,const std::string& values)
{
  std::string sql="INSERT INTO "+table_name_+" ("+columns+") values ("+values+")";
  return sql;
}

bool KPIDatabaseManager::ExecuSQL(const std::string& strSQL)
{
  bool ret=true;
  if(!odb::transaction::has_current()){
    try{
      odb::transaction t (db_shared_ptr_->begin ());
      db_shared_ptr_->execute (strSQL);
      t.commit ();
    }
    catch(...){
      ret=false;
    }
  }
  return ret;
}

bool KPIDatabaseManager::InitDatabaseInfo(int min,int max,const std::string& username,const std::string&password,const std::string& database)
{
  std::auto_ptr<odb::mysql::connection_factory> connection_pool__ptr(new odb::mysql::connection_pool_factory (max,min,true));
  db_shared_ptr_=std::shared_ptr<odb::database>(new odb::mysql::database (username,password,database,"",0,0,"",0,connection_pool__ptr));
}
