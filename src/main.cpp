//
//  main.cpp
//  PacketLossTool
//
//  Created by dongzha on 14-9-23.
//  Copyright (c) 2014年 dongzha. All rights reserved.
//


#include <iostream>
#include "SimulatePacketLoss.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    FILE* pH264File	  = NULL;
    FILE* pOutH264File	  = NULL;
    FILE* pInLossFile	  = NULL;
    FILE* pOutLossFile	  = NULL;
    SSliceLossRatioInPercent sSliceLossRatio;
    sSliceLossRatio.iSPSLossRatio = 0;
    sSliceLossRatio.iSubSPSLossRatio = 0;
    sSliceLossRatio.iPPSLossRatio = 0;
    sSliceLossRatio.iPrefixLossRatio = 0;
    sSliceLossRatio.iSVCSliceExtLossRatio = 0;
    sSliceLossRatio.iAVCISliceLossRatio = 0;
    sSliceLossRatio.iAVCPSliceLossRatio = 0;
    unsigned char* pBufInLoss = NULL;
    unsigned char* pBufInH264 = NULL;
    int iFileSizeInH264 = 0;
    int iFileSizeInLossFile = 0;
    if (argc<2) {
        fprintf (stderr, "Using following commond line: \n");
        fprintf (stderr, "1. [SimulaterFromFile testloss.cfg] PacketLossTool.exe -ib CVPCMNL1_SVA_C.264 -ob out.264 -iilosscfg testloss.cfg -ol outloss.cfg\n");
        fprintf (stderr, "2. [SimulaterFromFile testloss.cfg] PacketLossTool.exe -ib CVPCMNL1_SVA_C.264 -ob out.264 -iilosscfg testloss.cfg -iloss -1 -1 -1 -1 -1 -1 0 -ol outloss.cfg\n");
        fprintf (stderr, "where -1 specifies which type of NAL not loss and non -1 value indicates the NAL is lost according to the input file. SPS, SubSPS, PPS, Prefix, SVCSliceExt, AVCIDRSlice, AVCPSlice, respectivly.\n");
        fprintf (stderr, "3. [SimulaterFromPLR given by -iloss] PacketLossTool.exe -ib CVPCMNL1_SVA_C.264 -ob out.264 -iloss 0 0 0 0 0 0 0 -ol outloss.cfg \n");
        fprintf (stderr, "where -iloss gives the PLR of SPS, SubSPS, PPS, Prefix, SVCSliceExt, AVCIDRSlice, AVCPSlice, respectivly.\n");
    }
    for(int j = 1; j<argc; j++) {
        if(strcmp (argv[j],"-ib")==0) {
            pH264File = fopen (argv[++j], "rb");
            if (pH264File == NULL) {
                fprintf (stderr, "Can not open h264 source file, check its legal path %s related please..\n",argv[j]);
                return -1;
            } else {
                fseek (pH264File, 0L, SEEK_END);
                iFileSizeInH264 = (int) ftell (pH264File);
                pBufInH264 = new unsigned char[iFileSizeInH264+4];
                fseek (pH264File, 0L, SEEK_SET);
                if (fread (pBufInH264, 1, iFileSizeInH264, pH264File) != (unsigned int)iFileSizeInH264) {
                    fprintf (stderr, "Unable to read whole pH264File file\n");
                    fclose(pH264File);
                    return -1;
                }
            }
        }
        if(strcmp (argv[j],"-ob")==0) {
            pOutH264File = fopen (argv[++j], "wb");
            if (pOutH264File == NULL) {
                fprintf (stderr, "Can not open h264 source file to write, check its legal path %s related please..\n", argv[j]);
                return -1;
            }
        }
        if(strcmp (argv[j],"-ilosscfg")==0) {
            pInLossFile = fopen (argv[++j], "rb");
            if (pInLossFile == NULL) {
                fprintf (stderr, "Can not open input loss file, check its legal path %s related please..\n", argv[j]);
                return -1;
            } else {
                fseek (pInLossFile, 0L, SEEK_END);
                iFileSizeInLossFile = (int) ftell (pInLossFile);
                pBufInLoss = new unsigned char[iFileSizeInLossFile+4];
                fseek (pInLossFile, 0L, SEEK_SET);
                if (fread (pBufInLoss, 1, iFileSizeInLossFile, pInLossFile) != (unsigned int)iFileSizeInLossFile) {
                    fprintf (stderr, "Unable to read whole pInLossFile file\n");
                    fclose(pInLossFile);
                    return -1;
                }
            }
        }
        if(strcmp (argv[j],"-olosscfg")==0) {
            pOutLossFile = fopen (argv[++j], "wb");
            if (pOutLossFile == NULL) {
                fprintf (stderr, "Can not open output loss file, check its legal path %s related please..\n", argv[j]);
                return -1;
            }
        }
        if(strcmp (argv[j],"-iloss")==0) {
            sSliceLossRatio.iSPSLossRatio = atoi(argv[++j]);
            sSliceLossRatio.iSubSPSLossRatio = atoi(argv[++j]);
            sSliceLossRatio.iPPSLossRatio = atoi(argv[++j]);
            sSliceLossRatio.iPrefixLossRatio = atoi(argv[++j]);
            sSliceLossRatio.iSVCSliceExtLossRatio = atoi(argv[++j]);
            sSliceLossRatio.iAVCISliceLossRatio = atoi(argv[++j]);
            sSliceLossRatio.iAVCPSliceLossRatio = atoi(argv[++j]);
            fprintf (stderr, "[Input loss given by -iloss] %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",sSliceLossRatio.iSPSLossRatio/100.0, sSliceLossRatio.iSubSPSLossRatio/100.0,
                     sSliceLossRatio.iPPSLossRatio/100.0, sSliceLossRatio.iPrefixLossRatio/100.0, sSliceLossRatio.iSVCSliceExtLossRatio/100.0,
                     sSliceLossRatio.iAVCISliceLossRatio/100.0, sSliceLossRatio.iAVCPSliceLossRatio/100.0);
        }
        if(strcmp (argv[j],"-h")==0) {
            fprintf (stderr, "Using following commond line: \n");
            fprintf (stderr, "[SimulaterFromFile testloss.cfg] PacketLossTool.exe -ib CVPCMNL1_SVA_C.264 -ob out.264 -ilosscfg testloss.cfg -olosscfg outloss.cfg\n");
            fprintf (stderr, "[SimulaterFromPLR given by -iloss] PacketLossTool.exe -ib CVPCMNL1_SVA_C.264 -ob out.264 -iloss 0 0 0 0 0 0 0 -ol outloss.cfg \n");
            fprintf (stderr, "where -iloss gives the PLRs Percentage of: SPS, SubSPS, PPS, Prefix, SVCSliceExt, AVCIDRSlice, AVCPSlice, respectivly.\n");
        }
    }
    CPacketLossSimulator cPacketLoss;
    SOutBuffStatics sOutBuff;
    // simulate Loss, can use following two function to simulate slice loss
    cPacketLoss.SetLossRatio(&sSliceLossRatio);
    if (iFileSizeInLossFile>0) {
        // simulate loss according to PLR flie
        cPacketLoss.SetLossRatio(&sSliceLossRatio);
        sOutBuff = cPacketLoss.SimulateNALLoss(pBufInH264,iFileSizeInH264,pBufInLoss,iFileSizeInLossFile);
    } else {
        // set PLR
        cPacketLoss.SetLossRatio(&sSliceLossRatio);
        // simulate loss according to PLR set
        sOutBuff = cPacketLoss.SimulateNALLoss(pBufInH264,iFileSizeInH264);
    }
    // store lossy bitsream
    if (pOutH264File&&sOutBuff.len>0) {
        fwrite (sOutBuff.pBuff, 1, sOutBuff.len, pOutH264File);
    }
    // get actual Loss Status
    SLossstatusInfo sLossStatusinfo = cPacketLoss.GetLossStatus ();
    if (pOutLossFile&&sLossStatusinfo.iLossBufLen>0) {
        // store actual Loss Status to file. 1: lost, 0: remain;
        fwrite (sLossStatusinfo.pLossBuf, 1, sLossStatusinfo.iLossBufLen, pOutLossFile);
    }
    
    fprintf (stderr, "[Actual loss given by -iloss] %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n",sLossStatusinfo.fSPSLossRatio, sLossStatusinfo.fSubSPSLossRatio, sLossStatusinfo.fPPSLossRatio, sLossStatusinfo.fPrefixLossRatio, sLossStatusinfo.fSVCSliceExtLossRatio, sLossStatusinfo.fAVCISliceLossRatio, sLossStatusinfo.fAVCPSliceLossRatio);
    
    if (pH264File) {
        fclose(pH264File);
    }
    if (pOutH264File) {
        fclose(pOutH264File);
    }
    if (pInLossFile) {
        fclose(pInLossFile);
    }
    if (pOutLossFile) {
        fclose(pOutLossFile);
    }
    delete [] pBufInH264;
    delete [] pBufInLoss;
    return 0;
}
