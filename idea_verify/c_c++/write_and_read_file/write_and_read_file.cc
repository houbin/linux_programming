#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <iostream>

using namespace std;

typedef struct _JVS_FILE_HEADER_EX
{
uint8_t ucHeader[3];//结构体识别码，设置为‘J','F','H'
uint8_t ucVersion;//结构体版本号，当前版本为1
uint16_t wDeviceType;//设备类型

uint16_t wVideoCodecID;//视频编码类型
uint16_t wVideoDataType;//数æ®类型
uint16_t wVideoFormat;//视频模式
uint16_t wVideoWidth;//视频宽
uint16_t wVideoHeight;//视频高
uint16_t wFrameRateNum;//帧率分子
uint16_t wFrameRateDen;//帧率分母

uint16_t wAudioCodecID;//音频编码格式
uint16_t wVideoHeightwAudioSampleRate;//音频采样率
uint16_t wAudioChannels;//音é¢声道数
uint16_t wAudioBits;//音频采样位数

uint32_t dwRecFileTotalFrames;//录像总帧数
uint16_t wRecFileType;//录像类型

uint8_t ucReserved[30];//è·全部置0

} JVS_FILE_HEADER_EX;

int main()
{
    JVS_FILE_HEADER_EX *header;

    int size = sizeof(JVS_FILE_HEADER_EX);

    header = (JVS_FILE_HEADER_EX*)malloc(size);
    memset(header, 0, size);
    header->ucVersion = 3;
    header->wDeviceType = 5;
    header->wVideoCodecID = 123;
    header->wVideoDataType = 789;
    header->wVideoFormat = 456;
    header->wVideoWidth = 789;
    header->wVideoHeight = 123;

    cout << "size is " << size << endl;
    cout << endl;

    int fd;
    fd = open("data.txt", O_RDWR);
    assert(fd >= 0);

    int ret = write(fd, header, size);
    cout << "write header to file, size is " << size << ", ret is " << ret << endl;

    close(fd);

    fd = open("data.txt", O_RDONLY);
    assert(fd >= 0);
    
    char temp[1024];
    memset(temp, 0, 1024);

    ret = read(fd, temp, 1024);

    cout << "read ret is " << ret << endl;

    JVS_FILE_HEADER_EX *read_header = (JVS_FILE_HEADER_EX *)temp;

    printf("header_version is %d", header->ucVersion);
    cout << "read header, version is " << header->ucVersion << ", device type is " << header->wDeviceType
     << ", video code id is " << header->wVideoCodecID << ", video data type is " << header->wVideoDataType
     << ", video format is " << header->wVideoFormat << ", video width is " << header->wVideoWidth
     << ", video height is " << header->wVideoHeight << endl;

     close(fd);

    return 0;
}
