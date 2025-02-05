#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QPushButton"
#include "QString"
#include "string.h"
#include "stack"
#include <QMouseEvent>
#include <QTextStream>
#include <stdio.h>
#include <QStack>
#include <QPainter>
#include <QTextBrowser>
#include <QDialog>
#include <QTime>
#include <QInputDialog>
#include <qmath.h>

//节点个数为318个，这里要根据实际图像的情况来调整，对应下面的ludian数组下表上限
#define VN 318
//节点之间的直接能连线个数，对应下面的e数组上限，后面会用这来计算marix距离
#define EN 422



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("1345");
    this->setWindowFlags(Qt::FramelessWindowHint);
    size=25;
    vn=VN;
    en=EN;
    flag=0;
    lujing=0;

    jianzhu_cnt=0;
    jianzhu_flag=0;

    move_flag=0;


    //功能按钮坐标
    gongneng_x[0] = 500, gongneng_y[0] = 290;
    gongneng_x[1] = 500, gongneng_y[1] = 320;
    gongneng_x[2] = 500, gongneng_y[2] = 350;
    gongneng_x[3] = 500, gongneng_y[3] = 380;
    gongneng_x[5] = 500, gongneng_y[5] = 410;
    gongneng_x[6] = 500, gongneng_y[6] = 440;
 

    //添加建筑按钮
    addjianzhu_button=new QPushButton(this);
    connect(addjianzhu_button,SIGNAL(clicked()),this,SLOT(addjianzhu()));
    addjianzhu_button->setText("添加建筑");
    addjianzhu_button->setGeometry(gongneng_x[0],gongneng_y[0],gongneng_sizex,gongneng_sizey);

    //改变路径宽度按钮
    pathwidth_button=new QPushButton(this);
    connect(pathwidth_button,SIGNAL(clicked()),this,SLOT(changepathwidth()));
    pathwidth_button->setText("路径宽度");
    pathwidth_button->setGeometry(gongneng_x[1],gongneng_y[1],gongneng_sizex,gongneng_sizey);


    //路径颜色按钮
    pathcolor_button=new QPushButton(this);
    connect(pathcolor_button,SIGNAL(clicked()),this,SLOT(changepathcolor()));
    pathcolor_button->setText("更换颜色");
    pathcolor_button->setGeometry(gongneng_x[2],gongneng_y[2],gongneng_sizex,gongneng_sizey);


    //操作说明按钮
    shuoming_button=new QPushButton(this);
    connect(shuoming_button,SIGNAL(clicked()),this,SLOT(shuoming()));
    shuoming_button->setText("操作说明");
    shuoming_button->setGeometry(gongneng_x[3],gongneng_y[3],gongneng_sizex,gongneng_sizey);

    //关于按钮
    about_button=new QPushButton(this);
    connect(about_button,SIGNAL(clicked()),this,SLOT(aboutme()));
    about_button->setText("关于");
    about_button->setGeometry(gongneng_x[5],gongneng_y[5],gongneng_sizex,gongneng_sizey);


    //关闭按钮
    close_button=new QPushButton(this);
    connect(close_button,SIGNAL(clicked()),this,SLOT(closehanshu()));
    close_button->setText("退出");
    close_button->setGeometry(gongneng_x[6],gongneng_y[6],gongneng_sizex,gongneng_sizey);

    //本程序选择了318个关键节点，所以必须根据实际图像把坐标定位好
    ludian_x[0] = 572, ludian_y[0] = 104;
    ludian_x[1] = 521, ludian_y[1] = 104;
    ludian_x[2] = 525, ludian_y[2] = 45;
    ludian_x[3] = 470, ludian_y[3] = 104;
    ludian_x[4] = 451, ludian_y[4] = 106;
    ludian_x[5] = 469, ludian_y[5] = 45;
    ludian_x[6] = 462, ludian_y[6] = 45;
    ludian_x[7] = 461, ludian_y[7] = 17;
    ludian_x[8] = 522, ludian_y[8] = 16;
    ludian_x[9] = 408, ludian_y[9] = 31;
    ludian_x[10] = 408, ludian_y[10] = 44;
    ludian_x[11] = 408, ludian_y[11] = 83;
    ludian_x[12] = 408, ludian_y[12] = 105;
    ludian_x[13] = 408, ludian_y[13] = 117;
    ludian_x[14] = 408, ludian_y[14] = 145;
    ludian_x[15] = 409, ludian_y[15] = 169;
    ludian_x[16] = 409, ludian_y[16] = 212;
    ludian_x[17] = 406, ludian_y[17] = 249;
    ludian_x[18] = 452, ludian_y[18] = 150;
    ludian_x[19] = 521, ludian_y[19] = 212;
    ludian_x[20] = 580, ludian_y[20] = 209;
    ludian_x[21] = 445, ludian_y[21] = 293;
    ludian_x[22] = 456, ludian_y[22] = 306;
    ludian_x[23] = 449, ludian_y[23] = 350;
    ludian_x[24] = 326, ludian_y[24] = 348;
    ludian_x[25] = 326, ludian_y[25] = 405;
    ludian_x[26] = 325, ludian_y[26] = 336;
    ludian_x[27] = 367, ludian_y[27] = 285;
    ludian_x[28] = 375, ludian_y[28] = 278;
    ludian_x[29] = 348, ludian_y[29] = 261;
    ludian_x[30] = 354, ludian_y[30] = 212;
    ludian_x[31] = 362, ludian_y[31] = 175;
    ludian_x[32] = 298, ludian_y[32] = 404;
    ludian_x[33] = 294, ludian_y[33] = 404;
    ludian_x[34] = 265, ludian_y[34] = 404;
    ludian_x[35] = 265, ludian_y[35] = 353;
    ludian_x[36] = 265, ludian_y[36] = 337;
    ludian_x[37] = 214, ludian_y[37] = 275;
    ludian_x[38] = 227, ludian_y[38] = 261;
    ludian_x[39] = 279, ludian_y[39] = 261;
    ludian_x[40] = 292, ludian_y[40] = 261;
    ludian_x[41] = 307, ludian_y[41] = 261;
    ludian_x[42] = 306, ludian_y[42] = 212;
    ludian_x[43] = 292, ludian_y[43] = 212;
    ludian_x[44] = 279, ludian_y[44] = 212;
    ludian_x[45] = 278, ludian_y[45] = 171;
    ludian_x[46] = 278, ludian_y[46] = 143;
    ludian_x[47] = 278, ludian_y[47] = 167;
    ludian_x[48] = 305, ludian_y[48] = 166;
    ludian_x[49] = 306, ludian_y[49] = 172;
    ludian_x[50] = 316, ludian_y[50] = 171;
    ludian_x[51] = 316, ludian_y[51] = 166;
    ludian_x[52] = 342, ludian_y[52] = 166;
    ludian_x[53] = 316, ludian_y[53] = 150;
    ludian_x[54] = 340, ludian_y[54] = 132;
    ludian_x[55] = 374, ludian_y[55] = 133;
    ludian_x[56] = 376, ludian_y[56] = 127;
    ludian_x[57] = 352, ludian_y[57] = 106;
    ludian_x[58] = 344, ludian_y[58] = 107;
    ludian_x[59] = 345, ludian_y[59] = 81;
    ludian_x[60] = 345, ludian_y[60] = 78;
    ludian_x[61] = 345, ludian_y[61] = 57;
    ludian_x[62] = 395, ludian_y[62] = 57;
    ludian_x[63] = 345, ludian_y[63] = 31;
    ludian_x[64] = 268, ludian_y[64] = 37;
    ludian_x[65] = 180, ludian_y[65] = 30;
    ludian_x[66] = 276, ludian_y[66] = 87;
    ludian_x[67] = 296, ludian_y[67] = 94;
    ludian_x[68] = 262, ludian_y[68] = 115;
    ludian_x[69] = 294, ludian_y[69] = 131;
    ludian_x[70] = 272, ludian_y[70] = 146;
    ludian_x[71] = 247, ludian_y[71] = 90;
    ludian_x[72] = 236, ludian_y[72] = 84;
    ludian_x[73] = 190, ludian_y[73] = 111;
    ludian_x[74] = 204, ludian_y[74] = 141;
    ludian_x[75] = 228, ludian_y[75] = 159;
    ludian_x[76] = 220, ludian_y[76] = 158;
    ludian_x[77] = 228, ludian_y[77] = 171;
    ludian_x[78] = 226, ludian_y[78] = 215;
    ludian_x[79] = 178, ludian_y[79] = 61;
    ludian_x[80] = 179, ludian_y[80] = 111;
    ludian_x[81] = 179, ludian_y[81] = 158;
    ludian_x[82] = 179, ludian_y[82] = 165;
    ludian_x[83] = 181, ludian_y[83] = 213;
    ludian_x[84] = 181, ludian_y[84] = 244;
    ludian_x[85] = 193, ludian_y[85] = 260;
    ludian_x[86] = 170, ludian_y[86] = 260;
    ludian_x[87] = 188, ludian_y[87] = 320;
    ludian_x[88] = 188, ludian_y[88] = 328;
    ludian_x[89] = 225, ludian_y[89] = 328;
    ludian_x[90] = 188, ludian_y[90] = 353;
    ludian_x[91] = 189, ludian_y[91] = 405;
    ludian_x[92] = 179, ludian_y[92] = 405;
    ludian_x[93] = 177, ludian_y[93] = 447;
    ludian_x[94] = 121, ludian_y[94] = 450;
    ludian_x[95] = 122, ludian_y[95] = 416;
    ludian_x[96] = 122, ludian_y[96] = 406;
    ludian_x[97] = 122, ludian_y[97] = 354;
    ludian_x[98] = 122, ludian_y[98] = 320;
    ludian_x[99] = 122, ludian_y[99] = 260;
    ludian_x[100] = 121, ludian_y[100] = 225;
    ludian_x[101] = 120, ludian_y[101] = 201;
    ludian_x[102] = 119, ludian_y[102] = 166;
    ludian_x[103] = 104, ludian_y[103] = 165;
    ludian_x[104] = 104, ludian_y[104] = 113;
    ludian_x[105] = 129, ludian_y[105] = 111;
    ludian_x[106] = 129, ludian_y[106] = 90;
    ludian_x[107] = 160, ludian_y[107] = 90;
    ludian_x[108] = 83, ludian_y[108] = 166;
    ludian_x[109] = 82, ludian_y[109] = 192;
    ludian_x[110] = 82, ludian_y[110] = 200;
    ludian_x[111] = 81, ludian_y[111] = 224;
    ludian_x[112] = 81, ludian_y[112] = 235;
    ludian_x[113] = 80, ludian_y[113] = 260;
    ludian_x[114] = 47, ludian_y[114] = 168;
    ludian_x[115] = 35, ludian_y[115] = 192;
    ludian_x[116] = 69, ludian_y[116] = 193;
    ludian_x[117] = 72, ludian_y[117] = 199;
    ludian_x[118] = 72, ludian_y[118] = 219;
    ludian_x[119] = 34, ludian_y[119] = 222;
    ludian_x[120] = 34, ludian_y[120] = 235;
    ludian_x[121] = 39, ludian_y[121] = 261;
    ludian_x[122] = 88, ludian_y[122] = 355;
    ludian_x[123] = 88, ludian_y[123] = 392;
    ludian_x[124] = 88, ludian_y[124] = 403;
    ludian_x[125] = 36, ludian_y[125] = 393;
    ludian_x[126] = 36, ludian_y[126] = 457;

    ludian_x[127]=359,ludian_y[127]=117;//56-57
    ludian_x[128]=365,ludian_y[128]=123;

    ludian_x[129]=367,ludian_y[129]=82;//59-11
    ludian_x[130]=390,ludian_y[130]=82;

    ludian_x[131]=368,ludian_y[131]=57;//61-62

    ludian_x[132] = 368, ludian_y[132] = 30;//63-9
    ludian_x[133]=390,ludian_y[133]=30;

    ludian_x[134]=406,ludian_y[134]=510;//9up

    ludian_x[135]=129,ludian_y[135]=69;//106-79
    ludian_x[136]=132,ludian_y[136]=62;

    ludian_x[137]=83,ludian_y[137]=115;//104-114
    ludian_x[138]=69,ludian_y[138]=114;
    ludian_x[139]=48,ludian_y[139]=143;
    ludian_x[140]=44,ludian_y[140]=162;

    ludian_x[141]=41,ludian_y[141]=174;//114-115
    ludian_x[142]=36,ludian_y[142]=182;

    ludian_x[143]=34,ludian_y[143]=250;//120-121
    ludian_x[144]=40,ludian_y[144]=255;

    ludian_x[145]=29,ludian_y[145]=262;//121left

    ludian_x[146]=191,ludian_y[146]=305;//87-37

    ludian_x[147]=237,ludian_y[147]=293;//37-36
    ludian_x[148]=258,ludian_y[148]=313;

    ludian_x[149]=36,ludian_y[149]=358;//125-122
    ludian_x[150]=40,ludian_y[150]=355;

    ludian_x[151]=41,ludian_y[151]=461;//126-94
    ludian_x[152]=109,ludian_y[152]=461;
    ludian_x[153]=119,ludian_y[153]=456;

    ludian_x[154]=89,ludian_y[154]=410;//124-95
    ludian_x[155]=92,ludian_y[155]=415;

    ludian_x[156]=185,ludian_y[156]=28;//65-64
    ludian_x[157]=256,ludian_y[157]=28;

    ludian_x[158]=201,ludian_y[158]=108;//73-72
    ludian_x[159]=214,ludian_y[159]=102;
    ludian_x[160]=228,ludian_y[160]=91;

    ludian_x[161]=263,ludian_y[161]=82;//71-66

    ludian_x[162]=288,ludian_y[162]=72;//66-60

    ludian_x[163]=319,ludian_y[163]=92;//67-58

    ludian_x[164]=288,ludian_y[164]=31;//64-63

    ludian_x[165]=290,ludian_y[165]=107;//68-67

    ludian_x[166]=242,ludian_y[166]=158;//75-70
    ludian_x[167]=256,ludian_y[167]=155;
    ludian_x[168]=261,ludian_y[168]=154;

    ludian_x[169]=261,ludian_y[169]=106;//71-68

    ludian_x[170]=263,ludian_y[170]=126;//68-70

    ludian_x[171]=301,ludian_y[171]=137;//69-53
    ludian_x[172]=308,ludian_y[172]=139;

    ludian_x[173]=329,ludian_y[173]=134;//53-58

    ludian_x[174]=307,ludian_y[174]=119;//69-58
    ludian_x[175]=324,ludian_y[175]=110;

    ludian_x[176]=356,ludian_y[176]=238;//30-29

    ludian_x[177]=360,ludian_y[177]=262;//29-28
    ludian_x[178]=366,ludian_y[178]=266;

    ludian_x[179]=410,ludian_y[179]=235;//16-17

    ludian_x[180]=330,ludian_y[180]=319;//26-27
    ludian_x[181]=356,ludian_y[181]=294;

    ludian_x[182]=384,ludian_y[182]=296;//27-21
    ludian_x[183]=391,ludian_y[183]=298;
    ludian_x[184]=409,ludian_y[184]=301;
    ludian_x[185]=434,ludian_y[185]=296;

    ludian_x[186]=449,ludian_y[186]=369;//23-25
    ludian_x[187]=448,ludian_y[187]=389;
    ludian_x[188]=444,ludian_y[188]=397;
    ludian_x[189]= 432,ludian_y[189]= 403;
    ludian_x[190]=395,ludian_y[190]=404;

    ludian_x[191]=256,ludian_y[191]=210;//34left

    ludian_x[192]=349,ludian_y[192]=160;//52-15
    ludian_x[193]=358,ludian_y[193]=156;
    ludian_x[194]=372,ludian_y[194]=162;
    ludian_x[195]=375,ludian_y[195]=169;
    ludian_x[196]=393,ludian_y[196]=169;

    ludian_x[197]=526,ludian_y[197]=81;//2-1

    ludian_x[198]=583,ludian_y[198]=105;

    ludian_x[199] = 521, ludian_y[199] = 111;//1-19
    ludian_x[200] = 521, ludian_y[200] = 118;
    ludian_x[201] = 521, ludian_y[201] = 125;
    ludian_x[202] = 521, ludian_y[202] = 132;
    ludian_x[203] = 521, ludian_y[203] = 139;
    ludian_x[204] = 521, ludian_y[204] = 146;
    ludian_x[205] = 521, ludian_y[205] = 153;
    ludian_x[206] = 521, ludian_y[206] = 160;
    ludian_x[207] = 521, ludian_y[207] = 167;
    ludian_x[208] = 521, ludian_y[208] = 174;
    ludian_x[209] = 521, ludian_y[209] = 181;
    ludian_x[210] = 521, ludian_y[210] = 188;
    ludian_x[211] = 521, ludian_y[211] = 195;
    ludian_x[212] = 521, ludian_y[212] = 205;

    ludian_x[213] = 527, ludian_y[213] = 215;
    ludian_x[214] = 535, ludian_y[214] = 215;
    ludian_x[215] = 542, ludian_y[215] = 215;
    ludian_x[216] = 548, ludian_y[216] = 215;
    ludian_x[217] = 554, ludian_y[217] = 215;
    ludian_x[218] = 560, ludian_y[218] = 215;
    ludian_x[219] = 566, ludian_y[219] = 215;
    ludian_x[220] = 572, ludian_y[220] = 214;

    ludian_x[221] = 521, ludian_y[221] = 227;
    ludian_x[222] = 521, ludian_y[222] = 236;
    ludian_x[223] = 521, ludian_y[223] = 243;
    ludian_x[224] = 520, ludian_y[224] = 250;
    ludian_x[225] = 519, ludian_y[225] = 256;
    ludian_x[226] = 518, ludian_y[226] = 259;
    ludian_x[227] = 517, ludian_y[227] = 261;
    ludian_x[228] = 514, ludian_y[228] = 266;
    ludian_x[229] = 513, ludian_y[229] = 268;
    ludian_x[230] = 510, ludian_y[230] = 270;
    ludian_x[231] = 504, ludian_y[231] = 275;
    ludian_x[232] = 497, ludian_y[232] = 279;
    ludian_x[233] = 493, ludian_y[233] = 281;
    ludian_x[234] = 485, ludian_y[234] = 284;
    ludian_x[235] = 480, ludian_y[235] = 287;
    ludian_x[236] = 477, ludian_y[236] = 288;
    ludian_x[237] = 474, ludian_y[237] = 290;
    ludian_x[238] = 468, ludian_y[238] = 294;
    ludian_x[239] = 463, ludian_y[239] = 299;
    ludian_x[240] = 460, ludian_y[240] = 302;

    ludian_x[241] = 575, ludian_y[241] = 112;
    ludian_x[242] = 579, ludian_y[242] = 121;
    ludian_x[243] = 580, ludian_y[243] = 136;
    ludian_x[244] = 580, ludian_y[244] = 150;
    ludian_x[245] = 581, ludian_y[245] = 160;
    ludian_x[246] = 581, ludian_y[246] = 178;
    ludian_x[247] = 581, ludian_y[247] = 183;
    ludian_x[248] = 581, ludian_y[248] = 188;

  /*  ludian_x[249]=265,ludian_y[249]=265;
    ludian_x[250]=264,ludian_y[250]=282;
    ludian_x[251]=265,ludian_y[251]=299;
    ludian_x[252]=265,ludian_y[252]=316;
    ludian_x[253]=265,ludian_y[253]=333;
    ludian_x[254]=266,ludian_y[254]=349;
    ludian_x[255]=264,ludian_y[255]=366;
    ludian_x[256]=263,ludian_y[256]=381;
    ludian_x[257]=263,ludian_y[257]=398;
    ludian_x[258]=105,ludian_y[258]=350;
    ludian_x[259]=118,ludian_y[259]=352;
    ludian_x[260]=147,ludian_y[260]=350;
    ludian_x[261]=164,ludian_y[261]=351;
    ludian_x[262]=180,ludian_y[262]=349;
    ludian_x[263]=190,ludian_y[263]=348;
    ludian_x[264]=217,ludian_y[264]=351;
    ludian_x[265]=233,ludian_y[265]=351;
    ludian_x[266]=250,ludian_y[266]=351;
    ludian_x[267]=282,ludian_y[267]=349;
    ludian_x[268]=299,ludian_y[268]=349;
    ludian_x[269]=315,ludian_y[269]=347;
    ludian_x[270]=235,ludian_y[270]=234;
    ludian_x[271]=249,ludian_y[271]=234;
    ludian_x[272]=282,ludian_y[272]=234;
    ludian_x[273]=297,ludian_y[273]=233;
    ludian_x[274]=312,ludian_y[274]=232;
    ludian_x[275]=324,ludian_y[275]=234;
    ludian_x[276]=145,ludian_y[276]=415;
    ludian_x[277]=161,ludian_y[277]=413;
    ludian_x[278]=176,ludian_y[278]=416;
    ludian_x[279]=208,ludian_y[279]=413;
    ludian_x[280]=224,ludian_y[280]=411;
    ludian_x[281]=240,ludian_y[281]=410;
    ludian_x[282]=257,ludian_y[282]=411;
    ludian_x[283]=273,ludian_y[283]=411;
    ludian_x[284]=290,ludian_y[284]=410;
    ludian_x[285]=306,ludian_y[285]=411;
    ludian_x[286]=318,ludian_y[286]=411;
    ludian_x[287]=126,ludian_y[287]=173;
    ludian_x[288]=111,ludian_y[288]=166;
    ludian_x[289]=104,ludian_y[289]=151;
    ludian_x[290]=104,ludian_y[290]=134;
    ludian_x[291]=106,ludian_y[291]=118;
    ludian_x[292]=112,ludian_y[292]=102;
    ludian_x[293]=122,ludian_y[293]=90;
    ludian_x[294]=134,ludian_y[294]=76;
    ludian_x[295]=148,ludian_y[295]=66;
    ludian_x[296]=162,ludian_y[296]=61;
    ludian_x[297]=175,ludian_y[297]=48;
    ludian_x[298]=177,ludian_y[298]=58;
    ludian_x[299]=192,ludian_y[299]=48;
    ludian_x[300]=208,ludian_y[300]=48;
    ludian_x[301]=192,ludian_y[301]=62;
    ludian_x[302]=207,ludian_y[302]=62;
    ludian_x[303]=220,ludian_y[303]=49;
    ludian_x[304]=212,ludian_y[304]=75;
    ludian_x[305]=219,ludian_y[305]=89;
    ludian_x[306]=223,ludian_y[306]=105;
    ludian_x[307]=227,ludian_y[307]=120;
    ludian_x[308]=219,ludian_y[308]=134;
    ludian_x[309]=208,ludian_y[309]=148;
    ludian_x[310]=196,ludian_y[310]=159;
    ludian_x[311]=182,ludian_y[311]=169;
    ludian_x[312]=165,ludian_y[312]=175;
    ludian_x[313]=419,ludian_y[313]=420;
    ludian_x[314]=436,ludian_y[314]=422;
    ludian_x[315]=453,ludian_y[315]=423;
    ludian_x[316]=469,ludian_y[316]=422;
    ludian_x[317]=480,ludian_y[317]=426;*/


    for(int i=0;i<VN;i++){
        buttons_x[i]=ludian_x[i]-xx_yuan/40/2;
        buttons_y[i]=ludian_y[i]-xx_yuan/40/2;

        buttons_x_yuan[i]=buttons_x[i];
        buttons_y_yuan[i]=buttons_y[i];
    }



    v[0].x=500,v[0].y=360;
    v[1].x=490,v[1].y=347;
    v[2].x=524,v[2].y=334;
    v[3].x=560,v[3].y=312;
    v[4].x=564,v[4].y=353;
    v[5].x=561,v[5].y=386;
    v[6].x=522,v[6].y=374;
    v[7].x=490,v[7].y=378;
    v[8].x=489,v[8].y=424;
    v[9].x=488,v[9].y=444;
    v[10].x=542,v[10].y=445;
    v[11].x=548,v[11].y=434;
    v[12].x=550,v[12].y=403;

    for(int i=0;i<VN;i++)
        v_yuan[i].x=v[i].x,v_yuan[i].y=v[i].y;

    for(int i=0;i<VN;i++)
        delete(buttons[i]);

    for(int i=0;i<VN;i++){
        MainWindow::buttons[i] = new QPushButton (this);
        connect(buttons[i], SIGNAL(clicked()), this, SLOT(buttonClick()));

    }

    size=xx/40;
    for(int i=0;i<VN;i++){
        buttons[i]->setGeometry(buttons_x[i],buttons_y[i], size, size);
     // buttons[i]->setText(QString::number(i));
        buttons[i]->setObjectName(QString::number(i));

      buttons[i]->setFlat(true);
      buttons[i]->setStyleSheet("QPushButton{border:none;}");//设置没有按下的特效

      buttons[i]->show();
    }

    edge_cnt=0;//边计数，临时
    edge_s=-1,edge_e=-1;//临时
    edge_flag=0;

    //这里代表饿e数组代表具体的边，每条边编号就是下标，编号越多，说明越精细，
    //所以可以根据具体的图来调整数目。这里有422条边（e[421]）
    //边对应的值有2个，开始和结束节点的编号，本程序有318个节点
    //所以313个节点的具体定位最关键，他对应的具体坐标是ludian[i]
    e[0].s = 42, e[0].e = 43;
    e[1].s = 43, e[1].e = 44;
    e[2].s = 44, e[2].e =45;
    e[3].s = 45, e[3].e = 47;
    e[4].s = 47, e[4].e = 46;
    e[5].s = 47, e[5].e = 48;
    e[6].s = 48, e[6].e = 49;
    e[7].s = 49, e[7].e = 50;
    e[8].s = 50, e[8].e = 51;
    e[9].s = 51, e[9].e = 52;
    e[10].s = 52, e[10].e = 54;
    e[11].s = 51, e[11].e = 53;
    e[12].s = 42, e[12].e = 49;
    e[13].s = 54, e[13].e = 58;
    e[14].s = 58, e[14].e = 57;
    e[15].s = 57, e[15].e = 127;//56-57
    e[16].s = 56, e[16].e = 55;
    e[17].s = 55, e[17].e = 54;
    e[18].s = 56, e[18].e = 13;
    e[19].s = 13, e[19].e = 12;
    e[20].s = 12, e[20].e = 11;
    e[21].s = 11, e[21].e = 10;

    e[22].s = 10, e[22].e = 9;
    e[23].s = 58, e[23].e = 59;
    e[24].s = 59, e[24].e = 60;
    e[25].s =60, e[25].e = 61;
    e[26].s = 61, e[26].e = 63;

    e[27].s = 55, e[27].e = 14;
    e[28].s = 13, e[28].e = 14;
    e[29].s = 14, e[29].e = 15;
    e[30].s = 15, e[30].e = 16;

    e[31].s = 127, e[31].e = 128;//56-57
    e[32].s = 128, e[32].e = 56;

    e[33].s = 59, e[33].e = 129;//59-11
    e[34].s = 129, e[34].e = 130;
    e[35].s = 130, e[35].e = 11;

    e[36].s = 61, e[36].e = 131;//61-62
    e[37].s=131,e[37].e=62;

    e[38].s=63,e[38].e=132;
    e[39].s=132,e[39].e=133;
    e[40].s=133,e[40].e=9;

    e[41].s=9,e[41].e=134;

    e[42].s=10,e[42].e=6;
    e[43].s=6,e[43].e=5;
    e[44].s=5,e[44].e=7;
    e[45].s=7,e[45].e=8;
    e[46].s=8,e[46].e=2;
    e[47].s=5,e[47].e=2;
    e[48].s=5,e[48].e=3;
    e[49].s=3,e[49].e=4;
    e[50].s=12,e[50].e=4;
    e[51].s=4,e[51].e=18;
    e[52].s=3,e[52].e=1;
    e[53].s=1,e[53].e=0;

    e[54].s=16,e[54].e=30;
    e[55].s=30,e[55].e=31;
    e[56].s=30,e[56].e=42;
    e[57].s=42,e[57].e=41;
    e[58].s=41,e[58].e=40;
    e[59].s=40,e[59].e=39;
    e[60].s=40,e[60].e=43;
    e[61].s=39,e[61].e=44;
    e[62].s=29,e[62].e=43;
    e[63].s=39,e[63].e=38;
    e[64].s=38,e[64].e=37;
    e[65].s=37,e[65].e=85;
    e[66].s=85,e[66].e=84;
    e[67].s=84,e[67].e=86;
    e[68].s=85,e[68].e=86;
    e[69].s=84,e[69].e=83;
    e[70].s=83,e[70].e=82;
    e[71].s=82,e[71].e=81;
    e[72].s=76,e[72].e=81;
    e[73].s=76,e[73].e=75;
    e[74].s=75,e[74].e=77;
    e[75].s=77,e[75].e=78;
    e[76].s=83,e[76].e=78;
    e[77].s=78,e[77].e=38;
    e[78].s=74,e[78].e=76;
    e[79].s=81,e[79].e=80;
    e[80].s=80,e[80].e=73;
    e[81].s=73,e[81].e=74;
    e[82].s=86,e[82].e=99;
    e[83].s=99,e[83].e=100;
    e[84].s=100,e[84].e=101;
    e[85].s=101,e[85].e=102;
    e[86].s=102,e[86].e=103;
    e[87].s=103,e[87].e=108;
    e[88].s=108,e[88].e=109;
    e[89].s=109,e[89].e=110;
    e[90].s=110,e[90].e=111;
    e[91].s=110,e[91].e=101;
    e[92].s=111,e[92].e=100;
    e[93].s=111,e[93].e=112;
    e[94].s=112,e[94].e=113;
    e[95].s=113,e[95].e=99;
    e[96].s=113,e[96].e=121;
    e[97].s=111,e[97].e=118;
    e[98].s=118,e[98].e=117;
    e[99].s=110,e[99].e=117;
    e[100].s=116,e[100].e=117;
    e[101].s=116,e[101].e=109;
    e[102].s=115,e[102].e=116;
    e[103].s=108,e[103].e=114;
    e[104].s=118,e[104].e=119;
    e[105].s=112,e[105].e=120;
    e[106].s=115,e[106].e=119;
    e[107].s=119,e[107].e=120;

    e[108].s=103,e[108].e=104;
    e[109].s=104,e[109].e=105;
    e[110].s=105,e[110].e=106;
    e[111].s=106,e[111].e=107;
    e[112].s=105,e[112].e=80;

    e[113].s=82,e[113].e=102;

    e[114].s=80,e[114].e=79;
    e[115].s=79,e[115].e=65;

    e[116].s=45,e[116].e=77;

    e[117].s=106,e[117].e=135;//106-79
    e[118].s=135,e[118].e=136;
    e[119].s=136,e[119].e=79;

    e[120].s=104,e[120].e=137;//104-114
    e[121].s=137,e[121].e=138;
    e[122].s=138,e[122].e=139;
    e[123].s=139,e[123].e=140;
    e[124].s=140,e[124].e=114;

    e[125].s=114,e[125].e=141;//114-115
    e[126].s=141,e[126].e=142;
    e[127].s=142,e[127].e=115;

    e[128].s=120,e[128].e=143;//120-121
    e[129].s=143,e[129].e=144;
    e[130].s=144,e[130].e=121;

    e[131].s=121,e[131].e=145;

    e[132].s=99,e[132].e=98;
    e[133].s=98,e[133].e=97;
    e[134].s=97,e[134].e=122;
    e[135].s=122,e[135].e=123;
    e[136].s=123,e[136].e=124;
    e[137].s=124,e[137].e=96;
    e[138].s=123,e[138].e=125;
    e[139].s=96,e[139].e=95;
    e[140].s=96,e[140].e=97;
    e[141].s=98,e[141].e=87;
    e[142].s=87,e[142].e=88;
    e[143].s=88,e[143].e=89;
    e[144].s=88,e[144].e=90;
    e[145].s=90,e[145].e=91;
    e[146].s=91,e[146].e=92;
    e[147].s=92,e[147].e=93;
    e[148].s=93,e[148].e=94;
    e[149].s=94,e[149].e=95;
    e[150].s=92,e[150].e=96;
    e[151].s=90,e[151].e=35;
    e[152].s=35,e[152].e=36;
    e[153].s=35,e[153].e=34;
    e[154].s=34,e[154].e=33;
    e[155].s=33,e[155].e=32;
    e[156].s=32,e[156].e=25;
    e[157].s=25,e[157].e=24;
    e[158].s=24,e[158].e=26;
    e[159].s=26,e[159].e=36;
    e[160].s=91,e[160].e=34;
    e[161].s=24,e[161].e=23;

    e[162].s=87,e[162].e=146;//87-37
    e[163].s=146,e[163].e=37;

    e[164].s=37,e[164].e=147;//37-36
    e[165].s=147,e[165].e=148;
    e[166].s=148,e[166].e=36;

    e[167].s=125,e[167].e=149;//125-122
    e[168].s=149,e[168].e=150;
    e[169].s=150,e[169].e=122;

    e[170].s=125,e[170].e=126;

    e[171].s=126,e[171].e=151;//126-94
    e[172].s=151,e[172].e=152;
    e[173].s=152,e[173].e=153;
    e[174].s=153,e[174].e=94;

    e[175].s=124,e[175].e=154;//124-95
    e[176].s=154,e[176].e=155;
    e[177].s=155,e[177].e=95;

    e[178].s=65,e[178].e=156;//65-64
    e[179].s=156,e[179].e=157;
    e[180].s=157,e[180].e=64;

    e[181].s=73,e[181].e=158;//73-72
    e[182].s=158,e[182].e=159;
    e[183].s=159,e[183].e=160;
    e[184].s=160,e[184].e=72;

    e[185].s=72,e[185].e=64;
    e[186].s=72,e[186].e=71;
    e[187].s=74,e[187].e=68;

    e[188].s=71,e[188].e=161;//71-66
    e[189].s=161,e[189].e=66;

    e[190].s=66,e[190].e=67;

    e[191].s=66,e[191].e=162;//66-60
    e[192].s=162,e[192].e=60;

    e[193].s=67,e[193].e=163;//67-58
    e[194].s=163,e[194].e=58;

    e[195].s=64,e[195].e=164;//64-63
    e[196].s=164,e[196].e=63;

    e[197].s=68,e[197].e=165;//68-67
    e[198].s=165,e[198].e=67;

     e[199].s=57,e[199].e=12;

    e[200].s=75,e[200].e=166;//75-70
    e[201].s=166,e[201].e=167;
    e[202].s=167,e[202].e=168;
    e[203].s=168,e[203].e=70;

    e[204].s=71,e[204].e=169;//71-68
    e[205].s=169,e[205].e=68;

    e[206].s=70,e[206].e=46;
    e[207].s=46,e[207].e=69;

    e[208].s=68,e[208].e=170;//68-70
    e[209].s=170,e[209].e=70;

    e[210].s=69,e[210].e=171;//69-53
    e[211].s=171,e[211].e=172;
    e[212].s=172,e[212].e=53;

    e[213].s=53,e[213].e=173;//53-54
    e[214].s=173,e[214].e=54;

    e[215].s=69,e[215].e=174;//69-58
    e[216].s=174,e[216].e=175;
    e[217].s=175,e[217].e=58;

    e[218].s=30,e[218].e=176;//30-29
    e[219].s=176,e[219].e=29;

    e[220].s=29,e[220].e=177;//29-28
    e[221].s=177,e[221].e=178;
    e[222].s=178,e[222].e=28;

    e[223].s=27,e[223].e=28;
    e[224].s=17,e[224].e=21;
    e[225].s=21,e[225].e=22;
    e[226].s=22,e[226].e=23;
    e[227].s=28,e[227].e=17;

    e[228].s=16,e[228].e=179;//16-17
    e[229].s=179,e[229].e=17;

    e[230].s=26,e[230].e=180;//26-27
    e[231].s=180,e[231].e=181;
    e[232].s=181,e[232].e=27;

    e[233].s=27,e[233].e=182;//27-21
    e[234].s=182,e[234].e=183;
    e[235].s=183,e[235].e=184;
    e[236].s=184,e[236].e=185;
    e[237].s=185,e[237].e=21;

    e[238].s=23,e[238].e=186;//23-25
    e[239].s=186,e[239].e=187;
    e[240].s=187,e[240].e=188;
    e[241].s=188,e[241].e=189;
    e[242].s=189,e[242].e=190;
    e[243].s=190,e[243].e=25;

    e[244].s=34,e[244].e=191;

    e[245].s=52,e[245].e=192;//52-15
    e[246].s=192,e[246].e=193;
    e[247].s=193,e[247].e=194;
    e[248].s=194,e[248].e=195;
    e[249].s=195,e[249].e=196;
    e[250].s=196,e[250].e=15;

    e[251].s=2,e[251].e=197;//2-1
    e[252].s=197,e[252].e=1;

    e[253].s=0,e[253].e=198;

    e[254].s=1,e[254].e=199;//1-19
    e[255].s=199,e[255].e=200;
    e[256].s=200,e[256].e=201;
    e[257].s=201,e[257].e=202;
    e[258].s=202,e[258].e=203;
    e[259].s=203,e[259].e=204;
    e[260].s=204,e[260].e=205;
    e[261].s=205,e[261].e=206;
    e[262].s=206,e[262].e=207;
    e[263].s=207,e[263].e=208;
    e[264].s=208,e[264].e=209;
    e[265].s=209,e[265].e=210;
    e[266].s=210,e[266].e=211;
    e[267].s=211,e[267].e=212;
    e[268].s=212,e[268].e=19;

    e[269].s=19,e[269].e=213;//19-20
    e[270].s=213,e[270].e=214;
    e[271].s=214,e[271].e=215;
    e[272].s=215,e[272].e=216;
    e[273].s=216,e[273].e=217;
    e[274].s=217,e[274].e=218;
    e[275].s=218,e[275].e=219;
    e[276].s=219,e[276].e=220;
    e[277].s=220,e[277].e=20;

    e[278].s=19,e[278].e=221;//19-22
    e[279].s=221,e[279].e=222;
    e[280].s=222,e[280].e=223;
    e[281].s=223,e[281].e=224;
    e[282].s=224,e[282].e=225;
    e[283].s=225,e[283].e=226;
    e[284].s=226,e[284].e=227;
    e[285].s=227,e[285].e=228;
    e[286].s=228,e[286].e=229;
    e[287].s=229,e[287].e=230;
    e[288].s=230,e[288].e=231;
    e[289].s=231,e[289].e=232;
    e[290].s=232,e[290].e=233;
    e[291].s=233,e[291].e=234;
    e[292].s=234,e[292].e=235;
    e[293].s=235,e[293].e=236;
    e[294].s=236,e[294].e=237;
    e[295].s=237,e[295].e=238;
    e[296].s=236,e[296].e=239;
    e[297].s=239,e[297].e=240;
    e[298].s=240,e[298].e=22;

    e[299].s=0,e[299].e=241;//0-20
    e[300].s=241,e[300].e=242;
    e[301].s=242,e[301].e=243;
    e[302].s=243,e[302].e=244;
    e[303].s=244,e[303].e=245;
    e[304].s=245,e[304].e=246;
    e[305].s=246,e[305].e=247;
    e[306].s=247,e[306].e=248;
    e[307].s=248,e[307].e=20;

  /*  e[308].s=117,e[308].e=118;
    e[309].s=118,e[309].e=119;
    e[310].s=119,e[310].e=120;
    e[311].s=120,e[311].e=121;
    e[312].s=125,e[312].e=117;
    e[313].s=125,e[313].e=116;
    e[314].s=107,e[314].e=102;
    e[315].s=107,e[315].e=101;
    e[316].s=107,e[316].e=108;
    e[317].s=108,e[317].e=109;
    e[318].s=109,e[318].e=110;
    e[319].s=110,e[319].e=111;
    e[320].s=111,e[320].e=154;
    e[321].s=154,e[321].e=155;
    e[322].s=155,e[322].e=158;
    e[323].s=158,e[323].e=159;
    e[324].s=159,e[324].e=168;
    e[325].s=159,e[325].e=169;
    e[326].s=157,e[326].e=158;
    e[327].s=157,e[327].e=155;
    e[328].s=157,e[328].e=154;
    e[329].s=157,e[329].e=111;
    e[330].s=157,e[330].e=156;
    e[331].s=156,e[331].e=153;
    e[332].s=156,e[332].e=155;
    e[333].s=156,e[333].e=154;
    e[334].s=156,e[334].e=111;
    e[335].s=156,e[335].e=158;
    e[336].s=156,e[336].e=153;
    e[337].s=153,e[337].e=155;
    e[338].s=153,e[338].e=154;
    e[339].s=153,e[339].e=111;
    e[340].s=151,e[340].e=157;
    e[341].s=151,e[341].e=156;
    e[342].s=151,e[342].e=153;
    e[343].s=152,e[343].e=153;
    e[344].s=152,e[344].e=156;
    e[345].s=152,e[345].e=157;
    e[346].s=152,e[346].e=151;
    e[347].s=149,e[347].e=151;
    e[348].s=149,e[348].e=152;
    e[349].s=149,e[349].e=150;
    e[350].s=150,e[350].e=152;
    e[351].s=150,e[351].e=151;
    e[352].s=147,e[352].e=149;
    e[353].s=147,e[353].e=150;
    e[354].s=147,e[354].e=148;
    e[355].s=148,e[355].e=149;
    e[356].s=148,e[356].e=150;
    e[357].s=145,e[357].e=147;
    e[358].s=145,e[358].e=148;
    e[359].s=146,e[359].e=147;
    e[360].s=146,e[360].e=148;
    e[361].s=146,e[361].e=145;
    e[362].s=313,e[362].e=146;
    e[363].s=313,e[363].e=314;
    e[364].s=314,e[364].e=315;
    e[365].s=315,e[365].e=316;
    e[366].s=316,e[366].e=317;
    e[367].s=317,e[367].e=115;
    e[368].s=317,e[368].e=116;
    e[369].s=144,e[369].e=145;
    e[370].s=144,e[370].e=146;
    e[371].s=144,e[371].e=142;
    e[372].s=144,e[372].e=143;
    e[373].s=143,e[373].e=141;
    e[374].s=142,e[374].e=140;
    e[375].s=177,e[375].e=176;
    e[376].s=177,e[376].e=178;
    e[377].s=178,e[377].e=140;
    e[378].s=140,e[378].e=138;
    e[379].s=138,e[379].e=139;
    e[380].s=139,e[380].e=141;
    e[381].s=140,e[381].e=138;
    e[382].s=138,e[382].e=139;
    e[383].s=139,e[383].e=141;
    e[384].s=136,e[384].e=138;
    e[385].s=136,e[385].e=139;
    e[386].s=137,e[386].e=138;
    e[387].s=137,e[387].e=139;
    e[388].s=137,e[388].e=136;
    e[389].s=136,e[389].e=132;
    e[390].s=136,e[390].e=133;
    e[391].s=136,e[391].e=134;
    e[392].s=136,e[392].e=137;
    e[393].s=137,e[393].e=132;
    e[394].s=137,e[394].e=133;
    e[395].s=137,e[395].e=134;
    e[396].s=137,e[396].e=135;
    e[397].s=209,e[397].e=210;
    e[398].s=210,e[398].e=131;
    e[399].s=131,e[399].e=130;
    e[400].s=130,e[400].e=129;
    e[401].s=129,e[401].e=128;
    e[402].s=128,e[402].e=124;
    e[403].s=124,e[403].e=123;
    e[404].s=123,e[404].e=122;
    e[405].s=122,e[405].e=121;
    e[406].s=131,e[406].e=132;
    e[407].s=131,e[407].e=133;
    e[408].s=131,e[408].e=134;
    e[409].s=131,e[409].e=135;
    e[410].s=130,e[410].e=132;
    e[411].s=130,e[411].e=133;
    e[412].s=130,e[412].e=134;
    e[413].s=130,e[413].e=135;
    e[414].s=129,e[414].e=132;
    e[415].s=129,e[415].e=133;
    e[416].s=129,e[416].e=134;
    e[417].s=129,e[417].e=135;
    e[418].s=128,e[418].e=132;
    e[419].s=128,e[419].e=133;
    e[420].s=128,e[420].e=134;
    e[421].s=128,e[421].e=135;*/

 /*   //建立建筑物坐标，size，button
    jianzhu[ 0 ].x= 242 ,jianzhu[ 0 ].y= 63 ;
    jianzhu[ 0 ].x2= 291 ,jianzhu[ 0 ].y2= 140 ;
    jianzhu[ 1 ].x= 220 ,jianzhu[ 1 ].y= 148 ;
    jianzhu[ 1 ].x2= 291 ,jianzhu[ 1 ].y2= 176 ;
    jianzhu[ 2 ].x= 304 ,jianzhu[ 2 ].y= 81 ;
    jianzhu[ 2 ].x2= 342 ,jianzhu[ 2 ].y2= 177 ;
    jianzhu[ 3 ].x= 349 ,jianzhu[ 3 ].y= 81 ;
    jianzhu[ 3 ].x2= 387 ,jianzhu[ 3 ].y2= 175 ;
    jianzhu[ 4 ].x= 394 ,jianzhu[ 4 ].y= 63 ;
    jianzhu[ 4 ].x2= 426 ,jianzhu[ 4 ].y2= 176 ;
    jianzhu[ 5 ].x= 453 ,jianzhu[ 5 ].y= 64 ;
    jianzhu[ 5 ].x2= 484 ,jianzhu[ 5 ].y2= 85 ;
    jianzhu[ 6 ].x= 602 ,jianzhu[ 6 ].y= 100 ;
    jianzhu[ 6 ].x2= 688 ,jianzhu[ 6 ].y2= 148 ;
    jianzhu[ 7 ].x= 650 ,jianzhu[ 7 ].y= 166 ;
    jianzhu[ 7 ].x2= 693 ,jianzhu[ 7 ].y2= 201 ;
    jianzhu[ 8 ].x= 93 ,jianzhu[ 8 ].y= 202 ;
    jianzhu[ 8 ].x2= 133 ,jianzhu[ 8 ].y2= 223 ;
    jianzhu[ 9 ].x= 102 ,jianzhu[ 9 ].y= 273 ;
    jianzhu[ 9 ].x2= 124 ,jianzhu[ 9 ].y2= 326 ;
    jianzhu[ 10 ].x= 166 ,jianzhu[ 10 ].y= 195 ;
    jianzhu[ 10 ].x2= 201 ,jianzhu[ 10 ].y2= 213 ;
    jianzhu[ 11 ].x= 172 ,jianzhu[ 11 ].y= 219 ;
    jianzhu[ 11 ].x2= 208 ,jianzhu[ 11 ].y2= 238 ;
    jianzhu[ 12 ].x= 155 ,jianzhu[ 12 ].y= 247 ;
    jianzhu[ 12 ].x2= 191 ,jianzhu[ 12 ].y2= 264 ;
    jianzhu[ 13 ].x= 165 ,jianzhu[ 13 ].y= 270 ;
    jianzhu[ 13 ].x2= 197 ,jianzhu[ 13 ].y2= 288 ;
    jianzhu[ 14 ].x= 150 ,jianzhu[ 14 ].y= 298 ;
    jianzhu[ 14 ].x2= 185 ,jianzhu[ 14 ].y2= 317 ;
    jianzhu[ 15 ].x= 154 ,jianzhu[ 15 ].y= 322 ;
    jianzhu[ 15 ].x2= 188 ,jianzhu[ 15 ].y2= 339 ;
    jianzhu[ 16 ].x= 144 ,jianzhu[ 16 ].y= 361 ;
    jianzhu[ 16 ].x2= 187 ,jianzhu[ 16 ].y2= 377 ;
    jianzhu[ 17 ].x= 139 ,jianzhu[ 17 ].y= 384 ;
    jianzhu[ 17 ].x2= 180 ,jianzhu[ 17 ].y2= 400 ;
    jianzhu[ 18 ].x= 272 ,jianzhu[ 18 ].y= 356 ;
    jianzhu[ 18 ].x2= 320 ,jianzhu[ 18 ].y2= 375 ;
    jianzhu[ 19 ].x= 272 ,jianzhu[ 19 ].y= 382 ;
    jianzhu[ 19 ].x2= 322 ,jianzhu[ 19 ].y2= 400 ;
    jianzhu[ 20 ].x= 229 ,jianzhu[ 20 ].y= 197 ;
    jianzhu[ 20 ].x2= 257 ,jianzhu[ 20 ].y2= 222 ;
    jianzhu[ 21 ].x= 313 ,jianzhu[ 21 ].y= 244 ;
    jianzhu[ 21 ].x2= 324 ,jianzhu[ 21 ].y2= 269 ;
    jianzhu[ 22 ].x= 313 ,jianzhu[ 22 ].y= 277 ;
    jianzhu[ 22 ].x2= 325 ,jianzhu[ 22 ].y2= 302 ;
    jianzhu[ 23 ].x= 313 ,jianzhu[ 23 ].y= 311 ;
    jianzhu[ 23 ].x2= 325 ,jianzhu[ 23 ].y2= 334 ;
    jianzhu[ 24 ].x= 273 ,jianzhu[ 24 ].y= 243 ;
    jianzhu[ 24 ].x2= 302 ,jianzhu[ 24 ].y2= 255 ;
    jianzhu[ 25 ].x= 273 ,jianzhu[ 25 ].y= 260 ;
    jianzhu[ 25 ].x2= 303 ,jianzhu[ 25 ].y2= 272 ;
    jianzhu[ 26 ].x= 273 ,jianzhu[ 26 ].y= 276 ;
    jianzhu[ 26 ].x2= 303 ,jianzhu[ 26 ].y2= 288 ;
    jianzhu[ 27 ].x= 273 ,jianzhu[ 27 ].y= 293 ;
    jianzhu[ 27 ].x2= 302 ,jianzhu[ 27 ].y2= 306 ;
    jianzhu[ 28 ].x= 273 ,jianzhu[ 28 ].y= 312 ;
    jianzhu[ 28 ].x2= 303 ,jianzhu[ 28 ].y2= 323 ;
    jianzhu[ 29 ].x= 273 ,jianzhu[ 29 ].y= 328 ;
    jianzhu[ 29 ].x2= 303 ,jianzhu[ 29 ].y2= 339 ;
    jianzhu[ 30 ].x= 223 ,jianzhu[ 30 ].y= 247 ;
    jianzhu[ 30 ].x2= 252 ,jianzhu[ 30 ].y2= 303 ;
    jianzhu[ 31 ].x= 218 ,jianzhu[ 31 ].y= 310 ;
    jianzhu[ 31 ].x2= 249 ,jianzhu[ 31 ].y2= 342 ;
    jianzhu[ 32 ].x= 210 ,jianzhu[ 32 ].y= 356 ;
    jianzhu[ 32 ].x2= 255 ,jianzhu[ 32 ].y2= 402 ;
    jianzhu[ 33 ].x= 272 ,jianzhu[ 33 ].y= 192 ;
    jianzhu[ 33 ].x2= 291 ,jianzhu[ 33 ].y2= 199 ;
    jianzhu[ 34 ].x= 271 ,jianzhu[ 34 ].y= 202 ;
    jianzhu[ 34 ].x2= 295 ,jianzhu[ 34 ].y2= 224 ;
    jianzhu[ 35 ].x= 306 ,jianzhu[ 35 ].y= 200 ;
    jianzhu[ 35 ].x2= 326 ,jianzhu[ 35 ].y2= 223 ;
    jianzhu[ 36 ].x= 137 ,jianzhu[ 36 ].y= 421 ;
    jianzhu[ 36 ].x2= 175 ,jianzhu[ 36 ].y2= 437 ;
    jianzhu[ 37 ].x= 132 ,jianzhu[ 37 ].y= 441 ;
    jianzhu[ 37 ].x2= 173 ,jianzhu[ 37 ].y2= 457 ;
    jianzhu[ 38 ].x= 200 ,jianzhu[ 38 ].y= 419 ;
    jianzhu[ 38 ].x2= 317 ,jianzhu[ 38 ].y2= 458 ;
    jianzhu[ 39 ].x= 125 ,jianzhu[ 39 ].y= 475 ;
    jianzhu[ 39 ].x2= 163 ,jianzhu[ 39 ].y2= 509 ;
    jianzhu[ 40 ].x= 169 ,jianzhu[ 40 ].y= 475 ;
    jianzhu[ 40 ].x2= 206 ,jianzhu[ 40 ].y2= 510 ;
    jianzhu[ 41 ].x= 214 ,jianzhu[ 41 ].y= 475 ;
    jianzhu[ 41 ].x2= 251 ,jianzhu[ 41 ].y2= 509 ;
    jianzhu[ 42 ].x= 259 ,jianzhu[ 42 ].y= 475 ;
    jianzhu[ 42 ].x2= 295 ,jianzhu[ 42 ].y2= 510 ;
    jianzhu[ 43 ].x= 309 ,jianzhu[ 43 ].y= 476 ;
    jianzhu[ 43 ].x2= 367 ,jianzhu[ 43 ].y2= 506 ;
    jianzhu[ 44 ].x= 343 ,jianzhu[ 44 ].y= 357 ;
    jianzhu[ 44 ].x2= 369 ,jianzhu[ 44 ].y2= 447 ;
    jianzhu[ 45 ].x= 353 ,jianzhu[ 45 ].y= 195 ;
    jianzhu[ 45 ].x2= 435 ,jianzhu[ 45 ].y2= 216 ;
    jianzhu[ 46 ].x= 353 ,jianzhu[ 46 ].y= 227 ;
    jianzhu[ 46 ].x2= 386 ,jianzhu[ 46 ].y2= 246 ;
    jianzhu[ 47 ].x= 392 ,jianzhu[ 47 ].y= 226 ;
    jianzhu[ 47 ].x2= 436 ,jianzhu[ 47 ].y2= 248 ;
    jianzhu[ 48 ].x= 353 ,jianzhu[ 48 ].y= 249 ;
    jianzhu[ 48 ].x2= 368 ,jianzhu[ 48 ].y2= 292 ;
    jianzhu[ 49 ].x= 372 ,jianzhu[ 49 ].y= 251 ;
    jianzhu[ 49 ].x2= 398 ,jianzhu[ 49 ].y2= 290 ;
    jianzhu[ 50 ].x= 507 ,jianzhu[ 50 ].y= 225 ;
    jianzhu[ 50 ].x2= 611 ,jianzhu[ 50 ].y2= 247 ;
    jianzhu[ 51 ].x= 509 ,jianzhu[ 51 ].y= 167 ;
    jianzhu[ 51 ].x2= 556 ,jianzhu[ 51 ].y2= 218 ;
    jianzhu[ 52 ].x= 424 ,jianzhu[ 52 ].y= 356 ;
    jianzhu[ 52 ].x= 475 ,jianzhu[ 52 ].y= 414 ;
    jianzhu[ 52 ].x2= 425 ,jianzhu[ 52 ].y2= 430 ;
    jianzhu[ 53 ].x= 424 ,jianzhu[ 53 ].y= 448 ;
    jianzhu[ 53 ].x2= 474 ,jianzhu[ 53 ].y2= 506 ;
    jianzhu[ 54 ].x= 383 ,jianzhu[ 54 ].y= 438 ;
    jianzhu[ 54 ].x2= 400 ,jianzhu[ 54 ].y2= 462 ;
    jianzhu[ 55 ].x= 501 ,jianzhu[ 55 ].y= 398 ;
    jianzhu[ 55 ].x2= 540 ,jianzhu[ 55 ].y2= 434 ;
    jianzhu[ 56 ].x= 498 ,jianzhu[ 56 ].y= 453 ;
    jianzhu[ 56 ].x2= 541 ,jianzhu[ 56 ].y2= 482 ;
    jianzhu[ 57 ].x= 497 ,jianzhu[ 57 ].y= 493 ;
    jianzhu[ 57 ].x2= 540 ,jianzhu[ 57 ].y2= 517 ;
    jianzhu[ 58 ].x= 560 ,jianzhu[ 58 ].y= 410 ;
    jianzhu[ 58 ].x2= 603 ,jianzhu[ 58 ].y2= 426 ;
    jianzhu[ 59 ].x= 561 ,jianzhu[ 59 ].y= 430 ;
    jianzhu[ 59 ].x2= 604 ,jianzhu[ 59 ].y2= 443 ;
    jianzhu[ 60 ].x= 561 ,jianzhu[ 60 ].y= 449 ;
    jianzhu[ 60 ].x2= 604 ,jianzhu[ 60 ].y2= 461 ;
    jianzhu[ 61 ].x= 559 ,jianzhu[ 61 ].y= 476 ;
    jianzhu[ 61 ].x2= 606 ,jianzhu[ 61 ].y2= 490 ;
    jianzhu[ 62 ].x= 558 ,jianzhu[ 62 ].y= 494 ;
    jianzhu[ 62 ].x2= 608 ,jianzhu[ 62 ].y2= 518 ;*/

    for(int i=0;i<JN;i++){
        jianzhu[i].x-=3;
        jianzhu[i].y-=2;
        jianzhu[i].y2+=5;
        jianzhu[i].x2+=5;
    }

//  jianzhu[1].x=50,jianzhu[1].y=100,...

    for(int i=0;i<JN;i++){
        jianzhu[i].sizex=jianzhu[i].x2-jianzhu[i].x,jianzhu[i].sizey=jianzhu[i].y2-jianzhu[i].y;
        jianzhu[i].button=new QPushButton(this);
        jianzhu[i].button->setObjectName(QString::number(i));
      //jianzhu[i].button->setText(QString::number(i)); //最后需要注释
        connect(jianzhu[i].button, SIGNAL(clicked()), this, SLOT(jianzhuClick()));
        jianzhu[i].button->setGeometry(jianzhu[i].x,jianzhu[i].y,jianzhu[i].sizex,jianzhu[i].sizey);

        jianzhu[i].button->setStyleSheet("QPushButton{border:none;}");

        jianzhu[i].button->setFlat(true);
        jianzhu[i].button->show();
    }

    g.n=vn;
    g.e=en;
    //初始化，整个校园的路的关键节点2点节点长度为0
    //特别注意，实际很多两点之间是无法连接的，有边的才能连接
    for(int i=0;i<vn;i++)
        for(int j=0;j<vn;j++)
            g.matrix[i][j]=0;
    //建立图matrix中两点（边的开始点和结束点，就是2点有连线的才计算），这里用e[i]表示代表有边的
    //
    for(int i=0;i<EN;i++) //距离建图,通过勾股定理计算2点的距离，存放在二维数组中，而且是正反向
        g.matrix[e[i].s][e[i].e]=
                g.matrix[e[i].e][e[i].s]=sqrt(
                (ludian_x[e[i].s]-ludian_x[e[i].e])
                *(ludian_x[e[i].s]-ludian_x[e[i].e])+(ludian_y[e[i].s]-ludian_y[e[i].e])
                *(ludian_y[e[i].s]-ludian_y[e[i].e]));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    /*加载背景图*/
    QPixmap pixmap_yuantu(":/beijing/yuanjiaobiaoti.png");
    pixmap_yuantu = pixmap_yuantu.scaled(xx_yuan,yy_yuan);

  //  if(hualujing[2]==-1&&hualujing[1]!=-1)
   //     lujing=0;

    if (lujing==1)//需要绘制路径，延时绘制
    {

        QPainter llpainter(&pixmap_yuantu);
        llpainter.setRenderHint(QPainter::Antialiasing);
        if(color_flag==1)      llpainter.setPen(QPen(Qt::red,path_width,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
        else if(color_flag==2) llpainter.setPen(QPen(Qt::blue,path_width,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
        else if(color_flag==3) llpainter.setPen(QPen(Qt::darkCyan,path_width,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
        else if(color_flag==4) llpainter.setPen(QPen(Qt::green,path_width,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));
        else if(color_flag==0) llpainter.setPen(QPen(Qt::darkMagenta,path_width,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin));

        for (int i=1;hualujing[i]!=-1;i++)
        {
           llpainter.drawLine(ludian_x[hualujing[i-1]], ludian_y[hualujing[i-1]], ludian_x[hualujing[i]], ludian_y[hualujing[i]]);
        }

   //     //圆形测试
    //    llpainter.setPen(QPen(Qt::blue,16,Qt::SolidLine));
    //    llpainter.drawEllipse(20,20,40,40);

       llpainter.end();
       QPixmap pixmap = pixmap_yuantu.scaled(xx,yy);
       QPainter painter(this);
       painter.drawPixmap(0, 0, pixmap);

    }
    else if(lujing ==0){   //不需要绘制路径
        QPixmap pixmap = pixmap_yuantu.scaled(xx,yy);
        QPainter painter(this);
        painter.drawPixmap(0, 0, pixmap);
    }
    update();
}


void MainWindow::DijkstraPath(int v0)   //v0表示源顶点
{
    int i,j,k;
    bool visited[VN];
    for(i=0;i<g.n;i++)     //初始化
     {
        if(g.matrix[v0][i]>0&&i!=v0)
        {
            dist[i]=g.matrix[v0][i];
            path[i]=v0;     //path记录最短路径上从v0到i的前一个顶点
         }
        else
        {
            dist[i]=INT_MAX;    //若i不与v0直接相邻，则权值置为无穷大
            path[i]=-1;
        }
        visited[i]=false;
        path[v0]=v0;
        dist[v0]=0;
    }
    visited[v0]=true;
    for(i=1;i<g.n;i++)     //循环扩展n-1次
     {
        int min=INT_MAX;
        int u;
        for(j=0;j<g.n;j++)    //寻找未被扩展的权值最小的顶点
         {
            if(visited[j]==false&&dist[j]<min)
            {
                min=dist[j];
                u=j;
            }
        }
        visited[u]=true;
        for(k=0;k<g.n;k++)   //更新dist数组的值和路径的值
         {
            if(visited[k]==false&&g.matrix[u][k]>0&&min+g.matrix[u][k]<dist[k])
            {
                dist[k]=min+g.matrix[u][k];
                path[k]=u;
            }
        }
    }
    qDebug()<<"最短路径已经找到！";
}

//显示v0到v之间的路径，用颜色标注
void MainWindow::showPath(int v,int v0)   //v是终点
{
    for(int i=0;i<VN;i++)
        hualujing[i]=-1;
    int cnt=0;

    QTextStream cout(stdout,  QIODevice::WriteOnly);
    QStack<int> s;
    int u=v;
    while(v!=v0)
    {
        s.push(v);
        v=path[v];
    }
    s.push(v);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        hualujing[cnt++]=s.top();
        s.pop();
    }

}


void MainWindow::wheelEvent(QWheelEvent *event)
 {

     if(event->delta()>0){
         //新建的建筑
         for(int i=0;i<newjianzhu_cnt;i++)
         {
             newjianzhu_x[i]*=1.1;
             newjianzhu_y[i]*=1.1;
             newjianzhu_x2[i]*=1.1;
             newjianzhu_y2[i]*=1.1;
             double newjianzhu_sizex=newjianzhu_x2[i]-newjianzhu_x[i];
             double newjianzhu_sizey=newjianzhu_y2[i]-newjianzhu_y[i];
             newjianzhu_button[i]->setGeometry(newjianzhu_x[i],newjianzhu_y[i],newjianzhu_sizex,newjianzhu_sizey);
         }

         //功能按钮
         gongneng_sizex*=1.1;
         gongneng_sizey*=1.1;
         for(int i=0;i<7;i++)
         {
             gongneng_x[i]*=1.1;
             gongneng_y[i]*=1.1;
         }
          addjianzhu_button->setGeometry(gongneng_x[0],gongneng_y[0],gongneng_sizex,gongneng_sizey);
          pathwidth_button->setGeometry(gongneng_x[1],gongneng_y[1],gongneng_sizex,gongneng_sizey);
          pathcolor_button->setGeometry(gongneng_x[2],gongneng_y[2],gongneng_sizex,gongneng_sizey);
          shuoming_button->setGeometry(gongneng_x[3],gongneng_y[3],gongneng_sizex,gongneng_sizey);
          about_button->setGeometry(gongneng_x[5],gongneng_y[5],gongneng_sizex,gongneng_sizey);
          close_button->setGeometry(gongneng_x[6],gongneng_y[6],gongneng_sizex,gongneng_sizey);



         //建立建筑坐标
         for(int i=0;i<JN;i++){
//           delete jianzhu[i].buttton;
//           jianzhu[i].button=new QPushButton; //可以不要吗？
//           jianzhu[i].button->setObjectName(QString::number(i)); //可以不要吗？
//           jianzhu[i].button->setText(QString::number(i)); //最后需要注释 //可以不要吗？
//           connect(jianzhu[i].buttton, SIGNAL(clicked()), this, SLOT(jianzhuClick()));
             jianzhu[i].x=jianzhu[i].x*1.1;
             jianzhu[i].y=jianzhu[i].y*1.1;
             jianzhu[i].sizex=jianzhu[i].sizex*1.1;
             jianzhu[i].sizey=jianzhu[i].sizey*1.1;
             jianzhu[i].button->setGeometry(jianzhu[i].x,jianzhu[i].y,jianzhu[i].sizex,jianzhu[i].sizey);
     //      jianzhu[i].button->setStyleSheet("QPushButton{border:none;}");
     //      jianzhu[i].button->setFlat(true);
             jianzhu[i].button->show();
         }

         for(int i=0;i<VN;i++)
             delete(buttons[i]);
         for(int i=0;i<VN;i++){
             MainWindow::buttons[i] = new QPushButton (this);
             connect(buttons[i], SIGNAL(clicked()), this, SLOT(buttonClick()));
         }
         xx=xx*1.1; //窗口缩放所用坐标
         yy=yy*1.1;
         size=xx/40;
         this->resize( QSize( xx, yy));
         for(int i=0;i<VN;i++){
             buttons_x[i]=buttons_x[i]*1.1;
             buttons_y[i]=buttons_y[i]*1.1;
             buttons[i]->setGeometry(buttons_x[i],buttons_y[i], size, size);
            // buttons[i]->setText(QString::number(i));
             buttons[i]->setObjectName(QString::number(i));
             buttons[i]->setFlat(true);
             buttons[i]->setStyleSheet("QPushButton{border:none;}");//设置按下无效果
             buttons[i]->show();
         }

     }

     else if(event->delta()<0){


         //新建的建筑
         qDebug()<<newjianzhu_cnt;
         for(int i=0;i<newjianzhu_cnt;i++)
         {
             newjianzhu_x[i]*=0.9;
             newjianzhu_y[i]*=0.9;
             newjianzhu_x2[i]*=0.9;
             newjianzhu_y2[i]*=0.9;
             double newjianzhu_sizex=newjianzhu_x2[i]-newjianzhu_x[i];
             double newjianzhu_sizey=newjianzhu_y2[i]-newjianzhu_y[i];
             newjianzhu_button[i]->setGeometry(newjianzhu_x[i],newjianzhu_y[i],newjianzhu_sizex,newjianzhu_sizey);
         }


         //功能按钮
         gongneng_sizex*=0.9;
         gongneng_sizey*=0.9;
         for(int i=0;i<7;i++)
         {
             gongneng_x[i]*=0.9;
             gongneng_y[i]*=0.9;
         }
          addjianzhu_button->setGeometry(gongneng_x[0],gongneng_y[0],gongneng_sizex,gongneng_sizey);
          pathwidth_button->setGeometry(gongneng_x[1],gongneng_y[1],gongneng_sizex,gongneng_sizey);
          pathcolor_button->setGeometry(gongneng_x[2],gongneng_y[2],gongneng_sizex,gongneng_sizey);
          shuoming_button->setGeometry(gongneng_x[3],gongneng_y[3],gongneng_sizex,gongneng_sizey);
          about_button->setGeometry(gongneng_x[5],gongneng_y[5],gongneng_sizex,gongneng_sizey);
          close_button->setGeometry(gongneng_x[6],gongneng_y[6],gongneng_sizex,gongneng_sizey);



         xx=xx*0.9;
         yy=yy*0.9;
         size=xx/40;
         for(int i=0;i<VN;i++)
             delete(buttons[i]);

         for(int i=0;i<VN;i++){
             MainWindow::buttons[i] = new QPushButton (this);
             connect(buttons[i], SIGNAL(clicked()), this, SLOT(buttonClick()));
         }

         this->resize( QSize( xx, yy ));

         for(int i=0;i<JN;i++){
//           delete jianzhu[i].buttton;
//           jianzhu[i].button=new QPushButton; //可以不要吗？
//           jianzhu[i].button->setObjectName(QString::number(i)); //可以不要吗？
//           jianzhu[i].button->setText(QString::number(i)); //最后需要注释 //可以不要吗？
//           connect(jianzhu[i].buttton, SIGNAL(clicked()), this, SLOT(jianzhuClick()));
             jianzhu[i].x=jianzhu[i].x*0.9;
             jianzhu[i].y=jianzhu[i].y*0.9;
             jianzhu[i].sizex=jianzhu[i].sizex*0.9;
             jianzhu[i].sizey=jianzhu[i].sizey*0.9;
             jianzhu[i].button->setGeometry(jianzhu[i].x,jianzhu[i].y,jianzhu[i].sizex,jianzhu[i].sizey);
     //      jianzhu[i].button->setStyleSheet("QPushButton{border:none;}");
     //      jianzhu[i].button->setFlat(true);
             jianzhu[i].button->show();
         }

         for(int i=0;i<VN;i++){

             buttons_x[i]=buttons_x[i]*0.9;
             buttons_y[i]=buttons_y[i]*0.9;

             buttons[i]->setGeometry(buttons_x[i],buttons_y[i], size, size);
            // buttons[i]->setText(QString::number(i));
             buttons[i]->setObjectName(QString::number(i));
           buttons[i]->setFlat(true);
           buttons[i]->setStyleSheet("QPushButton{border:none;}");
             buttons[i]->show();
         }

     }
     event->accept();      //接收该事件
 }

void MainWindow::mousePressEvent(QMouseEvent *e){

//    QPushButton *test=new QPushButton(this);
//    test->setGeometry(e->x(),e->y(),30,30);
//    test->show();
//    qDebug()<<e->x()<<e->y();

    if(jianzhu_flag==1){
        newjianzhu_x[newjianzhu_cnt]=e->x();
        newjianzhu_y[newjianzhu_cnt]=e->y();
        jianzhu_flag=2;
    }
    else if(jianzhu_flag==2)
    {
        newjianzhu_x2[newjianzhu_cnt]=e->x();
        newjianzhu_y2[newjianzhu_cnt]=e->y();
        jianzhu_flag=3;
    }
    else if(jianzhu_flag==3){
        if(e->x()>newjianzhu_x[newjianzhu_cnt]&&e->x()<newjianzhu_x2[newjianzhu_cnt]&&
                e->y()>newjianzhu_y[newjianzhu_cnt]&&e->y()<newjianzhu_y2[newjianzhu_cnt])
            addjianzhu();
    }
    if(e->button()==Qt::RightButton){
        move_flag=1;
        double x=e->pos().x();
        double y=e->pos().y();
        last=e->globalPos();
    }
    else if(e->button()==Qt::LeftButton){
            move_flag=0;
            if(flag==0)
                flag=1;
            else if(flag==1)
                flag=0;
    }

}


//void MainWindow::deleteButton(){//删除按钮
//    huitu_button_cnt--;
//    delete huitu_button[huitu_button_cnt];
//}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
        if(move_flag==1){
            int dx=e->globalX()-last.x();
            int dy=e->globalY()-last.y();
            last=e->globalPos();
            move(x()+dx,y()+dy);
        }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e){

    if(e->button()==Qt::LeftButton){
        move_flag=0;
    }
    if(move_flag==1){
        int dx=e->globalX()-last.x();
        int dy=e->globalY()-last.y();
        move(x()+dx,y()+dy);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


//鼠标左键单机，判断第一次单机为flag==0，此时为起点，flag==1；第二次单击为终点后，并flag==0
//lujing为找到的路径数目，单击第一次为0，单击第二次找到路径
//这里为了拿到坐标点，鼠标单击后显示位置，在debug里会显示位置
void MainWindow::buttonClick(){
   //dis处理
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    //拿到对应的节点顺序号
    int i=clickedButton->objectName().toInt();
    //技巧：在debug窗口中打印坐标，并利用数据写入到程序中
    qDebug()<<"当前鼠标单击的坐标："<<clickedButton->pos();
   
    qDebug()<<i;
    if(flag==0){
        qDebug()<<"起点";
        v0=i;
        DijkstraPath(i);
        lujing=0;
        flag=1;//

    }
    else if(flag==1){
        qDebug()<<"终点";
        int ve=i;
        showPath(ve,v0);
        lujing=1;
        flag=0;
    }
}

void MainWindow::sleep(unsigned int msec){
    QTime reachTime =QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void MainWindow::closehanshu(){
    close();
}

void MainWindow::changepathcolor(){
    color_flag++;
    color_flag=color_flag%5;
}

void MainWindow::shuoming(){

//    QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    QMessageBox *shuoming_message=new QMessageBox(this);
//    shuoming_message->information(NULL,"操作说明","左键第一次单击选择起点\n"
//                                              "左键第二次单击选择终点\n"
//                                              "鼠标右键按住可拖动地图\n"
//                                              "滚轮滑动对地图进行缩放",QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes);
    shuoming_message->setWindowTitle("操作说明");
    shuoming_message->setText("请在图中白色道路区域选择起终点\n"
                              "左键第一次单击选择起点\n"
                              "左键第二次单击选择终点\n"
                              "鼠标右键按住可拖动地图\n"
                              "滚轮滑动对地图进行缩放");
    shuoming_message->exec();
}

void MainWindow::aboutme(){
    QMessageBox *about_message=new QMessageBox(this);
    about_message->setWindowTitle("关于");
    about_message->setText("作者 杨婧蕙、孔雯、李闽榕\n"
                           "电子邮箱：1339179387@qq.com\n"
                           "河海大学常州校区");
    about_message->exec();
}
void MainWindow::changepathwidth(){
    QInputDialog *staturelabel=new QInputDialog(this);
    bool isOK;
//  QString　text　=staturelabel->getText(NULL,"Input　Dialog","Please　input　your　comment",QLineEdit::Normal,"your　comment",&isOK);
    QString text="12";
    text=staturelabel->getText(NULL,"改变路径宽度","请输入路径宽度（1-9之间）",QLineEdit::Normal,"4",&isOK);
    if(text=="1"||text=="2"||text=="3"||text=="4"||text=="5"||text=="6"||text=="7"||text=="8"||text=="9")
    {
        QMessageBox *width_warnning=new QMessageBox(this);
        width_warnning->setWindowTitle("提示");
        width_warnning->setText("路径宽度修改成功!");
        path_width=text.toInt();
        width_warnning->show();
    }
    else {
        QMessageBox *width_warnning=new QMessageBox(this);
        width_warnning->setWindowTitle("警告");
        width_warnning->setText("请输入合法路径宽度!(7-15之间)");
        width_warnning->show();
    }


}

void MainWindow::addjianzhu(){
    if(jianzhu_flag==3){
        newjianzhu_button[newjianzhu_cnt]=new QPushButton(this);
        newjianzhu_button[newjianzhu_cnt]->setStyleSheet("QPushButton{border:none;}");
        newjianzhu_button[newjianzhu_cnt]->setObjectName(QString::number(newjianzhu_cnt));
        connect(newjianzhu_button[newjianzhu_cnt],SIGNAL(clicked()),this,SLOT(jianzhuxinxi()));

//        connect
        QInputDialog *newjianzhu_input=new QInputDialog(this);
        bool isOK;
        QString text="建筑名称";
        text=newjianzhu_input->getText(NULL,"添加名称","请输入建筑名称",QLineEdit::Normal,"建筑名称",&isOK);

        QString xinxi="建筑信息";
        newjianzhu_text[newjianzhu_cnt]=newjianzhu_input->getText(NULL,"添加信息","请输入建筑相关信息",QLineEdit::Normal,"建筑信息",&isOK);

        newjianzhu_button[newjianzhu_cnt]->setText(text);
        newjianzhu_button[newjianzhu_cnt]->setGeometry(newjianzhu_x[newjianzhu_cnt],newjianzhu_y[newjianzhu_cnt],
                                                               newjianzhu_x2[newjianzhu_cnt]-newjianzhu_x[newjianzhu_cnt],newjianzhu_y2[newjianzhu_cnt]-newjianzhu_y[newjianzhu_cnt]);
        newjianzhu_button[newjianzhu_cnt]->setFlat(true);
        newjianzhu_button[newjianzhu_cnt]->show();

        newjianzhu_cnt++;
        jianzhu_flag=0;
        }

    else{
        jianzhu_flag=1;
        QMessageBox *addjianzhu_message=new QMessageBox(this);
        addjianzhu_message->setWindowTitle("添加建筑");
        addjianzhu_message->setText("下面请使用鼠标右键在地图上点击待添加建筑的左上角和右下角以确定建筑位置，然后使用右键点击待添加建筑的中心以添加建筑的相关信息");
        addjianzhu_message->exec();
    }

}
void MainWindow::jianzhuxinxi(){
    QMessageBox *jianzhu_message=new QMessageBox(this);
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    int i=clickedButton->objectName().toInt();
    jianzhu_message->setText(newjianzhu_text[i]);
    jianzhu_message->setWindowTitle("建筑信息");
    jianzhu_message->exec();

}
