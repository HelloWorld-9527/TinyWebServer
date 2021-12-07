
#include <iostream>
#include <chrono>

#include "../log/log.h"

/*
 * -c，关闭日志，默认打开
 * 0，打开日志
 * 1，关闭日志
 */
int m_close_log;

/*
 * -l，选择日志写入方式，默认同步写入
 * 0，同步写入
 * 1，异步写入
 */
int m_log_write;

void log_init(char *log_name_postfix)
{
    if (0 == m_close_log)
    {
        //初始化日志
        if (1 == m_log_write)
            Log::get_instance()->init(log_name_postfix, m_close_log, 2000, 800000, 800);
        else
            Log::get_instance()->init(log_name_postfix, m_close_log, 2000, 800000, 0);
    }
}

void sync_log_test()
{
    //初始化
    m_close_log = 0; // 打开日志
    m_log_write = 0; // 同步写入
    char log_name_postfix[20] = "./syncLog.log";
    log_init(log_name_postfix);

    LOG_ERROR("-- start!");

    const int count = 1000000;
    auto start = std::chrono::system_clock::now(); // 开始计时
    
    for (int index = 0; index < count; index++) { // 写日志
        LOG_INFO("%d hello world", index);
    }
    auto end = std::chrono::system_clock::now(); // 结束计时
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // 耗时
    LOG_INFO("%d 次运行耗时 %d", count, duration.count());
    std::cout << count << "次运行耗时" << duration.count() << "us" << std::endl;
}

void asyn_log_test()
{
    //初始化
    m_close_log = 0; // 打开日志
    m_log_write = 1; // 异步写入
    char log_name_postfix[20] = "./asynLog.log";
    log_init(log_name_postfix);

    LOG_ERROR("-- start!");

    const int count = 1000000;
    auto start = std::chrono::system_clock::now(); // 开始计时
    
    for (int index = 0; index < count; index++) { // 写日志
        LOG_INFO("%d hello world", index);
    }
    auto end = std::chrono::system_clock::now(); // 结束计时
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // 耗时
    LOG_INFO("%d 次运行耗时 %d", count, duration.count());
    std::cout << count << "次运行耗时" << duration.count() << "us" << std::endl;
}

int main(int argc, char *argv[])
{
    // sync_log_test();
    asyn_log_test();

}