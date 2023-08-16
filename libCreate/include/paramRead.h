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
#pragma pack(1)
typedef struct
{
    int isuse;
    int freq;
    int gain;
    float band_width;
    float samp_freq;
    int type; // 0是wifi频点，1是正常频点
} FreqCorInfo;

typedef struct
{
    int freq;
    int gain;
    int isuse;
    int num;
} FreqInfo;
#pragma pack()

int getfreqinfo(char *fileName, struct Freq_info *freqinfos);
int GetIniKeyString(char *, const char *, const char *, const char *);
int GetIniKeyFloatArray(const char *, const char *, float *, int, const char *);
int GetIniKeyIntArray(const char *, const char *, int *, int, const char *);
long long GetIniKeyInt(const char *, const char *, const char *);
float GetIniKeyFloat(const char *, const char *, const char *);
int update_param_key(const char *fileName, const char *key, const char *data);
long GetFileRefreshTime(char *FilePath);
int PutIniKeyInt(const char *title, const char *key, int val, const char *filename);
int getfreqlist(char *FreqListPath, FreqCorInfo *freq_tab);
int getfreqlist(char *FreqListPath, std::vector<FreqInfo> &vec_scan, bool with_notuse = true);
#endif