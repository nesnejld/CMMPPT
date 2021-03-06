#ifndef IDNUMBER_H
#define IDNUMBER_H

// Identification numbers for classes that inherit from SCECollectable

// These should only be used by classes to implement isA.  These numbers
// are here to prevent two classes from using the same number.  If you
// need a classes number, you should use the isA method on an instance
// of the class


typedef unsigned short isAReturnType;
 
// These definitions follow the pattern used by Rogue Wave
#define __LGFRITEM		     0x2500
#define __LGFRPART		     0x2501
#define __LGFRDEMAND		     0x2502
#define __LGFRDEMANDPERIODPAIR	     0x2503


#define __LGFRITEMTIMEVECPAIRFLOAT   0x2504
#define __LGFRDESCRIPTORSCHEDULEPAIRFLOAT 0x2505
#define __LGFRSCHEDULEDESCRIPTOR     0x2506

#define __LGFRCOLLECTABLEFLOAT       0x2507
#define __LGFRSORTEDVECTORENHANCED   0x2508

// These definitions are used to identify a Comparison Strategy 
#define __LGFRPAIRCOMPAREFLOAT                                0x2600
#define __LGFRTIMEVECELEMENTPAIRCOMPAREFLOAT                  0x2601
#define __LGFRPARTCATEGORYPAIRCOMPAREFLOAT                    0x2602
#define __LGFRDEMANDPARTNAMEPAIRCOMPARE                       0x2603
#define __LGFRDEMANDPRIORITYPAIRCOMPARE                       0x2604
#define __LGFRDEMANDVOLUMETIMESGROSSREVENUEPAIRCOMPARE        0x2605
#define __LGFRDEMANDBACKLOGTIMESGROSSREVENUEPAIRCOMPARE       0x2606
#define __LGFRCRITICALLISTPAIRCOMPARE                         0x2607
#define __LGFRSCHEDULESENSITIVEPAIRCOMPARE                    0x2608
#define __LGFRSETOFPARTSSENSITIVEPAIRCOMPARE                  0x2609
// For ROCH Iman
#define __LGFRPARTEXCESSSUPPLYCOSTPAIRCOMPAREFLOAT            0x2680
#define __LGFRPARTTIMEVECPAIRCOMPAREFLOAT                     0x2681
#define __LGFRDEMANDTIMEVECPAIRCOMPAREFLOAT                   0x2682

// These definitions are used to identify a Schedule Strategy 
#define __LGFRSUPPLYSCHEDULESTRATEGY                         0x2700
#define __LGFRPRODUCTIONSCHEDULESTRATEGY                     0x2701
#define __LGFRCRITICALPARTSCHEDULESTRATEGY                   0x2702
#define __LGFRFOCUSSEDSHORTAGESCHEDULESCHEDULESTRATEGY       0x2703
#define __LGFREXCESSSCHEDULESTRATEGY                         0x2704
#define __LGFRREQUIREMENTSCHEDULESTRATEGY                    0x2705
#define __LGFRPARTSCHEDULESENSITIVESCHEDULESTRATEGY          0x2706
#define __LGFRCUMTIMEVECPARTSCHEDULESTRATEGY                 0x2707
#define __LGFRCUMDEMANDSPARTSCHEDULESTRATEGY                 0x2708
#define __LGFRCYCLETIMESCHEDULESTRATEGY                      0x2709
#define __LGFRTWOSCHEDULEDELTAPARTSCHEDULESTRATEGY           0x270A
#define __LGFRAPPLYOFFSETSCHEDULESTRATEGY                    0x270B
#define __LGFRSUPPLYSCHEDULESTRATEGYFORATP                   0x270C
#define __LGFRSTOCKSCHEDULESTRATEGY                          0x270D
#define __LGFRSCRAPSCHEDULESTRATEGY                          0x270E
#define __LGFRUSAGESCHEDULESTRATEGY                          0x2710
#define __LGFRCUMTIMEVECPARTSCHEDULESTRATEGYFORATP           0x2711
#define __LGFRCUMDEMANDSPARTSCHEDULESTRATEGYFORATP           0x2712
#define __LGFRFOCUSSEDSHORTAGESCHEDULESCHEDULESTRATEGYFORATP 0x2713
#define __LGFRFROZENZONESCHEDULESTRATEGY                     0x2714
#define __LGFRPARTSUMMARYSCHEDULESTRATEGY                    0x2715
#define __LGFRPARTSCHEDULETIMESCOSTSCHEDULESTRATEGY          0x2716
#define __LGFRCOMPOUNDINTERESTSCHEDULESTRATEGY               0x2717
#define __LGFRCMRPREQUIREMENTSCHEDULESTRATEGY                0x2718
#define __LGFRFOCUSSEDSHORTAGESCHEDULEPRODUCTIONSCHEDULESTRATEGY 0x2719
#define __LGFRMRPCONSVOLSCHEDULESTRATEGY                     0x271A
#define __LGFRFULLYEXPLODEDMRPCONSVOLSCHEDULESTRATEGY        0x271B

#define __LGFRDEMANDVOLUMESCHEDULESTRATEGY                   0x2780
#define __LGFRSHIPMENTSCHEDULESTRATEGY                       0x2781
#define __LGFRBACKLOGSCHEDULESTRATEGY                        0x2782
#define __LGFRDEMANDSCHEDULESENSITIVESCHEDULESTRATEGY        0x2783
#define __LGFRCUMTIMEVECDEMANDSCHEDULESTRATEGY               0x2784
#define __LGFRDEMANDVOLUMESCHEDULESTRATEGYFORATP             0x2785
#define __LGFRSHIPMENTSCHEDULESTRATEGYFORATP                 0x2786
#define __LGFRBACKLOGSCHEDULESTRATEGYFORATP                  0x2787
#define __LGFRPRIORITYSCHEDULESTRATEGYFORATP		     0x2788
#define __LGFRCUMTIMEVECDEMANDSCHEDULESTRATEGYFORATP         0x2789
#define __LGFRPRIORITYSCHEDULESTRATEGY                       0x278A
#define __LGFROBJ1SHIPREWARDSCHEDULESTRATEGY                 0x278B
#define __LGFRDEMANDSUMMARYSCHEDULESTRATEGY                  0x278C
#define __LGFRSHIPSOFTLOWERBOUNDSCHEDULESTRATEGY             0x278D
// For ROCH Iman
#define __LGFRONHANDSCHEDULESTRATEGY                         0x27C0
#define __LGFRUSAGECOSTSCHEDULESTRATEGY                      0x27C1
#define __LGFRSUMCOSTSCHEDULESTRATEGY		             0x27C2
#define __LGFRPARTSUMMARYDOLLARIZEDSCHEDULESTRATEGY          0x27C3
#define __LGFRDOLLARIZEDTOTALSSCHEDULESTRATEGY		     0x27C4
#define __LGFRSUPPLYUSAGECOSTSCHEDULESTRATEGY                0x27C5
#define __LGFRSUPPLYUSAGESCHEDULESTRATEGY                    0x27C6
#define __LGFRREALSOMEPLANNEDSCHEDULESTRATEGY                0X27C7

// These definitions are used to identify a Filter Strategy 
#define __LGFRFILTERSTRATEGY                                 0x2800
#define __LGFRZEROTIMEVECFILTERSTRATEGY                      0x2801
#define __LGFRDEMANDNAMEFILTERSTRATEGY                       0x2802
#define __LGFRPARTNAMEFILTERSTRATEGY                         0x2803
#define __LGFRSCHEDULESENSITIVEFILTERSTRATEGY                0x2804
#define __LGFRANDFILTERSTRATEGY                              0x2805
#define __LGFRORFILTERSTRATEGY                               0x2806
#define __LGFRNOTFILTERSTRATEGY                              0x2807
#define __LGFRNUMBEROFBOMENTRIESFILTERSTRATEGY               0x2808
#define __LGFRSETOFPARTSFILTERSTRATEGY                       0x2809
#define __LGFRPARTCATEGORYFILTERSTRATEGY                     0x2810
#define __LGFRSCENARIOSENSITIVEFILTERSTRATEGY			0x2811

// These definitions are used to identify the Algorithm Class of an object 
#define __LGFRFOCUSSEDSHORTAGESCHEDULECONTROL                0x2900
#define __LGFRIMPLODE                                        0x2901
#define __LGFREXPLODE                                        0x2902
#define __LGFRUSERINPUTMODIFICATION                          0x2903

// These definitions are used to identify the TimeVecCompare Class of an object 
#define __LGFRTIMEVECCOMPAREFLOAT                            0x2A00
#define __LGFRMAXIMUMELEMENTTIMEVECCOMPAREFLOAT              0x2A01

// These definitions are used to identify Part Attributes
#define __LGFRCONSTRAINED                                    0x2B00
#define __LGFRCYCLETIME                                      0x2B01
#define __LGFROBJ1PRODCOST                                   0x2B02
#define __LGFROBJ1SCRAPCOST                                  0x2B03
#define __LGFROBJ1STOCKCOST                                  0x2B04
#define __LGFRPRODBOUNDS                                     0x2B05
#define __LGFRSTOCKBOUNDS                                    0x2B06
#define __LGFRSUPPLYVOL                                      0x2B07
#define __LGFRUNITCOST                                       0x2B08
#define __LGFRYIELD                                          0x2B09
#define __LGFRPROCCOST                                       0x2B0A
#define __LGFRPROCLEADTIME                                   0x2B0B
#define __LGFRMINLOTSIZE                                     0x2B0C

// These definitions are used to identify Demand Attributes
#define __LGFRGROSSREV                                       0x2C00
#define __LGFRDEMANDVOL                                      0x2C01
#define __LGFROBJ1CUMSHIPREWARD                              0x2C02
#define __LGFROBJ1SHIPREWARD                                 0x2C03
#define __LGFRPRIORITY                                       0x2C04
#define __LGFRCUMSHIPBOUNDS                                  0x2C05

// These definitions are used to identify DataInterfaces

#define __LGFRDATAINTERFACE				     0x2D00
#define __LGFRDATAINTERFACESPECIALPURPOSEFROMFILE  	          0x2D01
#define __LGFRDATAINTERFACEIMPLEMENTATIONFROMMAPICS                0x2D02
#define __LGFRDATAINTERFACEIMPLEMENTATIONPERFECTWORLDCMRP           0x2D03
#define __LGFRDATAINTERFACEIMPLEMENTATIONPERFECTWORLDATP            0x2D04
#define __LGFRDATAINTERFACEIMPLEMENTATIONFROMWITDATAFILE            0x2D05
#define __LGFRDATAINTERFACEIMPLEMENTATIONFROMWITRUN                0x2D06
#define __LGFRDATAINTERFACEIMPLEMENTATION                        0x2D07
#define __LGFRDATAINTERFACEIMPLEMENTATIONVOLKSWAGENCMRP	            0x2D08
#define __LGFRDATAINTERFACEIMPLEMENTATIONFROMCMRPFILES              0x2D09
#define __LGFRDATAINTERFACEIMPLEMENTATIONFROMSCEFILES             0x2D10
#define __LGFRKEY                                          0x2D11
#define __LGFRDATAINTERFACEABSTRACT			       0X2D12
#define __LGFRDATAINTERFACESPECIALPURPOSE                       0X2D13
#define __LGFRDATAINTERFACEESSENTIALS                          0X2D14
#define __LGFRDATAINTERFACEESSENTIALSFROMSCENARIO                 0X2D15
#define __LGFRDATAINTERFACEIMPLEMENTATIONFORROCH                0x2D16


// These definitions are used to identify scenarios
#define __LGFRSCENARIO                                       0x2E00
#define __LGFRSCENARIOFORCMRP                                0x2E01
#define __LGFRSCENARIOFORATP                                 0x2E02
#define __LGFRTESTSCENARIO                                   0x2E03
#define __LGFRSCENARIOFORDIFTESTING                          0x2E04
#define __LGFRSCENARIOFORSCE                                 0x2E05
#define __LGFRSCENARIOFORIMAN                                0x2E06
// For ROCH Xman
#define __LGFRSCENARIOFORXMAN				     0x2E07	
#define __LGFRSCENARIOFORSMAN				     0x2E08	


// These definitions are used to indentify schedule smart pointer collectables
#define __LGFRSORTINGDEMANDSCHEDULEFLOATSMARTPOINTERCOLLECTABLE 0x2F00
#define __LGFRSORTINGPARTSCHEDULEFLOATSMARTPOINTERCOLLECTABLE 0x2F01

#endif
