#pragma once
#include<string>
#pragma db view table("KPI")
struct KPIView
{
#pragma db column("kpi_english_name") type("text")
std::string kpi_english_name;
//#pragma db column("kpi_chinese_name") type("text")
//std::string kpi_chinese_name;
#pragma db column("kpi_index") type("text")
std::string kpi_index;
};
