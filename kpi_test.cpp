#include"kpi_database_manager.h"

int main()
{
  do{
    KPIDatabaseManager kpi_manager;
    if(!kpi_manager.GetKPIMap("root","root","odb_test"))
      {
	std::cout<<"Get KPI map failed!"<<std::endl;
	break;
      }
    kpi_manager.InitDatabaseInfo(5,20,"root","root","odb_test");
    kpi_manager.SetInsertTableName("KPI_VALUE");//设置表名
    while(1){
      std::cout<<"输入KPI英文名及其对应的value :"<<std::endl;
      std::string kpi_english;
      std::cin>>kpi_english;
      std::string value;
      std::cin>>value;
      std::string kpi;
      if((kpi=kpi_manager.FindKPIColumn(kpi_english))==""){
	std::cout<<"没有找到对应的kpi"<<std::endl;
	continue;
      }
      std::string sql=kpi_manager.GenerateSQL(kpi,value);
      if(!kpi_manager.ExecuSQL(sql))
	std::cout<<"ExecuSQL failed"<<std::endl;
    }
  }while(0);

  return 0;
}
