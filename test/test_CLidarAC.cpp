#include "wpbh_local_planner/CLidarAC.h"

static double y_sin[180];
static double x_cos[180];
static float max_vy = 0.5;

int test[40];

CLidarAC::CLidarAC()
{
	if (test[1] == 0) {
		printf("***test_CLidarAC 1/31 has done***\n");
	}
	test[1] = test[1] + 1;

    for(int i=0;i<180;i++) 
    {
        arFrontRanges[i] = i;
		x_cos[i] = cos(i*3.14159/180);
		y_sin[i] = sin(i*3.14159/180);
        arPnt_x[i] = arFrontRanges[i] * x_cos[i];
		arPnt_y[i] = arFrontRanges[i] * y_sin[i];
        arACPnt[i] = false;
    }
	kx = 0.005;
	ky = 0.1;
	fVx = 0;
	fVy = 0;
    nLeftIndex = nRightIndex = -1;
    nBlobDist = 5;
    nIgnDist = 22;
    nACWidth = 30;
	nACDist = 100;
}

CLidarAC::~CLidarAC()
{
}

static int CalDist(int inX1, int inY1, int inX2, int inY2)
{
	if (test[2] == 0) {
		printf("***test_CLidarAC 2/31 has done***\n");
	}
	test[2] = test[2] + 1;

    int res = sqrt((inX1-inX2)*(inX1-inX2) + (inY1-inY2)*(inY1-inY2));
    return res;
}

int CLidarAC::GetMinIndex(int inBeginIndex, int inEndIndex)
{
	if (test[3] == 0) {
		printf("***test_CLidarAC 3/31 has done***\n");
	}
	test[3] = test[3] + 1;

    int res = inBeginIndex;
    int nMinDist = arFrontRanges[inBeginIndex];
    for(int i=inBeginIndex+1;i<inEndIndex;i++) 
    {
        if(arACPnt[i] == true && arFrontRanges[i] < nMinDist)
        {
			if (test[4] == 0) {
				printf("***test_CLidarAC 4/31 has done***\n");
			}
			test[4] = test[4] + 1;

            nMinDist = arFrontRanges[i];
            res = i;
        }
    }
    return res;
}

void CLidarAC::SetRanges(float* inData)
{
	if (test[5] == 0) {
		printf("***test_CLidarAC 5/31 has done***\n");
	}
	test[5] = test[5] + 1;

    for(int i=0;i<180;i++)
    {
        arFrontRanges[i] = inData[270-i];
        arPnt_x[i] = arFrontRanges[i] * x_cos[i];
		arPnt_y[i] = arFrontRanges[i] * y_sin[i];
    }
}

bool CLidarAC::OutLine()
{
	if (test[6] == 0) {
		printf("***test_CLidarAC 6/31 has done***\n");
	}
	test[6] = test[6] + 1;

    bool res = true;
    // 有效障碍点
    for(int i=0;i<180;i++) 
    {
        arACPnt[i] = false;
        if(arFrontRanges[i] > nIgnDist )
        {
			if (test[7] == 0) {
				printf("***test_CLidarAC 7/31 has done***\n");
			}
			test[7] = test[7] + 1;

            if(
                arPnt_x[i] > -nACWidth &&
                arPnt_x[i] < nACWidth &&
                arPnt_y[i] > 0 &&
                arPnt_y[i] < nACDist
            )
            {
				if (test[8] == 0) {
					printf("***test_CLidarAC 8/31 has done***\n");
				}
				test[8] = test[8] + 1;

                arACPnt[i] = true;
            }
        }
    }

    // 连通检测
    bool bBlobStart = false;
    int nBeginIndex = 0;
    int nEndIndex = 0;
    int nLastRange = 0;
    arBlobIndex.clear();
    for(int i=0;i<180;i++) 
    {
        if(arACPnt[i] == true)
        {
			if (test[9] == 0) {
				printf("***test_CLidarAC 9/31 has done***\n");
			}
			test[9] = test[9] + 1;

            if(bBlobStart == false)
            {
				if (test[10] == 0) {
					printf("***test_CLidarAC 10/31 has done***\n");
				}
				test[10] = test[10] + 1;

                nBeginIndex = i;
                bBlobStart = true;
            }
            else
            {
				if (test[11] == 0) {
					printf("***test_CLidarAC 11/31 has done***\n");
				}
				test[11] = test[11] + 1;

                if(abs(arFrontRanges[i] - nLastRange) > nBlobDist)
                {
					if (test[12] == 0) {
						printf("***test_CLidarAC 12/31 has done***\n");
					}
					test[12] = test[12] + 1;

                    nEndIndex = i-1;
                    if(nEndIndex > nBeginIndex)
                    {
						if (test[13] == 0) {
							printf("***test_CLidarAC 13/31 has done***\n");
						}
						test[13] = test[13] + 1;

                        int nMinIndex = GetMinIndex(nBeginIndex , nEndIndex);
                        arBlobIndex.push_back(nMinIndex);
                    }
                    nBeginIndex = i;
                }
            }
            nLastRange = arFrontRanges[i];
        }
        else
        {
			if (test[14] == 0) {
				printf("***test_CLidarAC 14/31 has done***\n");
			}
			test[14] = test[14] + 1;

            if(bBlobStart == true)
            {
				if (test[15] == 0) {
					printf("***test_CLidarAC 15/31 has done***\n");
				}
				test[15] = test[15] + 1;

                bBlobStart= false;
                nEndIndex = i-1;
                if(nEndIndex > nBeginIndex)
                {
					if (test[16] == 0) {
						printf("***test_CLidarAC 16/31 has done***\n");
					}
					test[16] = test[16] + 1;

                    int nMinIndex = GetMinIndex(nBeginIndex , nEndIndex);
                    arBlobIndex.push_back(nMinIndex);
                }
            }
        }
    }

    //左右
    nLeftIndex = nRightIndex = -1;
    int nMinLeft = 1000;
    int nMinRight = 1000;
    int nBlobNum = arBlobIndex.size();
    for(int i=0;i<nBlobNum;i++)
    {
        if(arBlobIndex[i] < 90)
        {
			if (test[17] == 0) {
				printf("***test_CLidarAC 17/31 has done***\n");
			}
			test[17] = test[17] + 1;

            if(arFrontRanges[arBlobIndex[i]] < nMinLeft)
            {
				if (test[18] == 0) {
					printf("***test_CLidarAC 18/31 has done***\n");
				}
				test[18] = test[18] + 1;

                nMinLeft = arFrontRanges[arBlobIndex[i]];
                nLeftIndex = arBlobIndex[i];
            }
        }
        else
        {
			if (test[19] == 0) {
				printf("***test_CLidarAC 19/31 has done***\n");
			}
			test[19] = test[19] + 1;

            if(arFrontRanges[arBlobIndex[i]] < nMinRight)
            {
				if (test[20] == 0) {
					printf("***test_CLidarAC 20/31 has done***\n");
				}
				test[20] = test[20] + 1;

                nMinRight = arFrontRanges[arBlobIndex[i]];
                nRightIndex = arBlobIndex[i];
            }
        }
    }

    // 速度
    if(nLeftIndex < 0 && nRightIndex < 0)
    {
		if (test[21] == 0) {
			printf("***test_CLidarAC 21/31 has done***\n");
		}
		test[21] = test[21] + 1;

        fVx = fVy = 0;
    }
    else
    {
		if (test[22] == 0) {
			printf("***test_CLidarAC 22/31 has done***\n");
		}
		test[22] = test[22] + 1;

        int nMinX = nACDist;
        if(nLeftIndex >= 0 )
        {
			if (test[23] == 0) {
				printf("***test_CLidarAC 23/31 has done***\n");
			}
			test[23] = test[23] + 1;

            if(arPnt_y[nLeftIndex] < nMinX)
            {
				if (test[24] == 0) {
					printf("***test_CLidarAC 24/31 has done***\n");
				}
				test[24] = test[24] + 1;

                nMinX = arPnt_y[nLeftIndex];
            }
        }
         if(nRightIndex >= 0 )
        {
			 if (test[25] == 0) {
				 printf("***test_CLidarAC 25/31 has done***\n");
			 }
			 test[25] = test[25] + 1;

            if(arPnt_y[nRightIndex] < nMinX)
            {
				if (test[26] == 0) {
					printf("***test_CLidarAC 26/31 has done***\n");
				}
				test[26] = test[26] + 1;
                nMinX = arPnt_y[nRightIndex];
            }
        }
        fVx = -(nACDist - nMinX)*kx;
        if(nMinX < 40)
        {
			if (test[27] == 0) {
				printf("***test_CLidarAC 27/31 has done***\n");
			}
			test[27] = test[27] + 1;

            res = false;
        }

        float tmpLeftV = 0;
        float tmpRightV = 0;
        if(nLeftIndex >= 0 )
        {
			if (test[28] == 0) {
				printf("***test_CLidarAC 28/31 has done***\n");
			}
			test[28] = test[28] + 1;

            tmpLeftV = (arPnt_x[nLeftIndex] + nACWidth) * ky / arPnt_y[nLeftIndex];
        }
        if(nRightIndex >= 0 )
        {
			if (test[29] == 0) {
				printf("***test_CLidarAC 29/31 has done***\n");
			}
			test[29] = test[29] + 1;

            tmpRightV = -(nACWidth - arPnt_x[nRightIndex]) * ky / arPnt_y[nRightIndex];
        }
        fVy = tmpLeftV + tmpRightV;
        if(fVy < -max_vy)
        {
			if (test[30] == 0) {
				printf("***test_CLidarAC 30/31 has done***\n");
			}
			test[30] = test[30] + 1;

            fVy = -max_vy;
        }
        if(fVy > max_vy)
        {
			if (test[31] == 0) {
				printf("***test_CLidarAC 31/31 has done***\n");
			}
			test[31] = test[31] + 1;

            fVy = max_vy;
        }
    }

    return res;
}