//
// Created by F.B.W on 2019-04-13.
//

#ifndef ARDUWATCH_TIMEZONES_H
#define ARDUWATCH_TIMEZONES_H

//15deg intervals
//We are between +7.5 & -7.5 of 105deg W
// IF W then (+7.5,-7.5] if E then [-7.5,+7.5)
//TZ range if 180 deg E & W
// -12 on W, + 12 on E

/*Adjustments*/
#define UTC_0 0
#define UTC_15 1
#define UTC_30 2
#define UTC_45 3
#define UTC_60 4
#define UTC_75 5
#define UTC_90 6
#define UTC_105 7
#define UTC_120 8
#define UTC_135 9
#define UTC_150 10
#define UTC_165 11
#define UTC_180 12

/*Bounds*/
#define TZ_WIDTH 7.5f

#define UTC_0_L (0f - TZ_WIDTH)
#define UTC_0_H (0f + TZ_WIDTH)
#define UTC_15_L (15.0f - TZ_WIDTH)
#define UTC_15_H (15.0f + TZ_WIDTH)
#define UTC_30_L (30.0f - TZ_WIDTH)
#define UTC_30_H (30.0f + TZ_WIDTH)
#define UTC_45_L (45.0f - TZ_WIDTH)
#define UTC_45_H (45.0f + TZ_WIDTH)
#define UTC_60_L (60.0f - TZ_WIDTH)
#define UTC_60_H (60.0f + TZ_WIDTH)
#define UTC_75_L (75.0f - TZ_WIDTH)
#define UTC_75_H (75.0f + TZ_WIDTH)
#define UTC_90_L (90.0f - TZ_WIDTH)
#define UTC_90_H (90.0f + TZ_WIDTH)
#define UTC_105_L (105.0f - TZ_WIDTH)
#define UTC_105_H (105.0f + TZ_WIDTH)
#define UTC_120_L (120.0f - TZ_WIDTH)
#define UTC_120_H (120.0f + TZ_WIDTH)
#define UTC_135_L (135.0f - TZ_WIDTH)
#define UTC_135_H (135.0f + TZ_WIDTH)
#define UTC_150_L (150.0f - TZ_WIDTH)
#define UTC_150_H (150.0f + TZ_WIDTH)
#define UTC_165_L (165.0f - TZ_WIDTH)
#define UTC_165_H (165.0f + TZ_WIDTH)
#define UTC_180_L (180.0f - TZ_WIDTH)
#define UTC_180_H (180.0f + TZ_WIDTH)

#endif //ARDUWATCH_TIMEZONES_H
