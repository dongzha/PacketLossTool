PacketLossTool
==============

used to simulate packet loss
Using following commond line:
1. [SimulaterFromFile testloss.cfg] PacketLossTool.exe -ib CVPCMNL1_SVA_C.264 -ob out.264 -ilosscfg testloss.cfg -olosscfg outloss.cfg
2. [SimulaterFromFile testloss.cfg] PacketLossTool.exe -ib CVPCMNL1_SVA_C.264 -ob out.264 -ilosscfg testloss.cfg -iloss -1 -1 -1 -1 -1 -1 0 -olosscfg outloss.cfg
    where -1 specifies which type of NAL not loss and non -1 value indicates the NAL is lost according to the input file. SPS, SubSPS, PPS, Prefix, SVCSliceExt, AVCIDRSlice, AVCPSlice, respectivly.
3. [SimulaterFromPLR given by -iloss] PacketLossTool.exe -ib CVPCMNL1_SVA_C.264 -ob out.264 -iloss 0 0 0 0 0 0 0 -olosscfg outloss.cfg
    where -iloss gives the PLR of SPS, SubSPS, PPS, Prefix, SVCSliceExt, AVCIDRSlice, AVCPSlice, respectivly.
