/*
 * @Description:
 * @Version: 2.0
 * @Author: Feng Chao
 * @Date: 2021-10-15 13:44:42
 * @LastEditors: Feng Chao
 * @LastEditTime: 2021-11-06 14:00:53
 */
#ifndef _PARAMREAD_H
#define _PARAMREAD_H

#define BUFFSIZE 8192

#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <QDebug>
#include <QReadWriteLock>
typedef struct
{
    int freq;
    int gain;
} FreqCorInfo;

typedef struct
{
    int freq;
    int gain;
    int isuse;
    int num;
} FreqInfo;

int getfreqinfo(char *fileName, struct Freq_info *freqinfos);
int GetIniKeyString(char *, const char *, const char *, const char *);
int GetIniKeyFloatArray(const char *, const char *, float *, int, const char *);
int GetIniKeyIntArray(const char *, const char *, int *, int, const char *);
long long GetIniKeyInt(const char *, const char *, const char *);
float GetIniKeyFloat(const char *, const char *, const char *);
int update_param_key(const char *fileName, const char *key, const char *data);
long GetFileRefreshTime(const char *FilePath);
int PutIniKeyInt(const char *title, const char *key, int val, const char *filename);
int getfreqlist(char *FreqListPath, FreqCorInfo *freq_tab);
int getfreqlist(const char *FreqListPath, std::vector<FreqInfo> &vec_scan, bool with_notuse = true);

std::string getLogFileName(char *logPath, int save_day, char *file_prefix, char *file_suffix);
int saveLog(char* file_path, char* file_prefix, std::string data, char* file_suffix, int saveDate);
std::vector<int> returnAllFiles(char *logPath, char *mate_str, char *str);
#endif
