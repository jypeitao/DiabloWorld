
#include "skillList.h"
//双枪之伤 2
//双镰之伤 2
//双戟之伤 2
//双斧之伤 2
//双刃之伤 2
//声东击西 2
//美人计 2
//万里冰封 2---
const char * skillList::skills(int skillnum){
    
    switch (skillnum) {
        case 100001:
            //遇神诛神
            skill="yszs";
            break;
        case 100002:
            //地利人和
            skill="dlrh";
            break;
        case 100003:
            //太极八卦阵
            skill="tjbgz";
            break;
        case 100004:
            //迷烟阵
            skill="myz";
            break;
        case 100005:
            //醉醒技
            skill="xsj";
            break;
        case 100006:
            //偷袭
            skill="tx";
            break;
        case 100007:
            //天公怒
            skill="tgn";
            break;
        case 100008:
            //诈降
            skill="zhxj";
            break;
        case 100010:
            skill="ln";
            break;
            //        case 50008:
            //            //劝降
            //            break;
        case 100011:
            //双枪之伤 2
            skill="sqzs";
            break;
        case 100012:
            //双镰之伤 2
            skill="slzs";
            break;
        case 100013:
            //双戟之伤 2
            skill="sjzs";
            break;
        case 100014:
            //双斧之伤 2
            skill="sfzs";
            break;
        case 100015:
            //双刃之伤 2
            skill="srzs";
            break;
        case 100016:
            //乱刀斩
            skill="ldz";
            break;
        case 100017:
            //声东击西 2
            skill="sdjx";
            break;
        case 100018:
            //邪风阵
            skill="xfz";
            break;
        case 100019:
            //困兽斗
            skill="kszd";
            break;
        case 100020:
            //天雷阵
            skill="tgn";
            break;
        case 100022:
            //美人计 2
            skill="mrj";
            break;
        case 100024:
            //狮子吼
            skill="szh";
            break;
        case 100025:
            //野火燎原
            skill="yhly";
            break;
        case 100026:
            //万里冰封 2
            skill="wlbf";
            break;
        case 100027:
            
            //黄雀阵
            skill="hqz";
            break;
        case 100028:
            //水击三千里
            skill="sjsql";
            break;
        case 100029:
            //破军计
            skill="pjj";
            break;
            //        case 210101:
            //            //诈降计
            //            skill="sq";
            //            break;
        case 100030:
            //屈兵计
            skill="qbj";
            break;
        case 100031:
            skill="ggjs";
            break;
        default:
            skill="tx";
            break;
    }
    return skill;
}
const char * skillList::sqskills(int skillnum){
    switch (skillnum) {
        case 100011:
            //双枪之伤
            break;
        case 100012:
            //双廉之伤
            break;
        case 100013:
            //双戟之伤
            break;
        case 100014:
            //双斧之伤
            break;
        case 100015:
            //双刃之伤
            break;
        case 100031:
            //滚滚巨石
            break;
        case 100022:
            //美人计
            break;
        case 100017:
            //声东击西
            break;
        case 100026:
            //万里冰封
            break;
        default:
            qsskill="";
            // this->skillnums(skillnum);
            break;
    }
    return NULL;
}
const char * skillList::releaseName(int skillrelease){
    const char * names;
    switch (skillrelease) {
        case 61:
            names="you";
            
            break;
        case 62:
            names="qs_tjbgz";
            break;
        case 64:
            names="mou";
            break;
        case 65:
            names="zhou";
            break;
        case 66:
            names="qs_sqzs";
            break;
        case 67:
            names="qs_slzs";
            break;
        case 68:
            names="qs_sjzs";
            break;
        case 69:
            names="qs_sfzs";
            break;
        case 70:
            names="qs_srzs";
            break;
        default:
            
            break;
    }
    return names;
}
int skillList::skillnums(int skillnum){
    switch (skillnum) {
        case 100001:
            //遇神诛神
            skillnumber=12;
            break;
        case 100002:
            //地利人和
            skillnumber=6;
            break;
        case 100003:
            //太极八卦阵
            skillnumber=12;
            break;
        case 100004:
            //迷烟阵
            skillnumber=10;
            break;
        case 100005:
            //醉醒技
            skillnumber=10;
            break;
        case 100006:
            //偷袭
            skillnumber=8;//12
            break;
        case 100007:
            //天公怒
            skillnumber=6;//9
            break;
            //        case 50007:
            //            //诈降
            //            skillnumber=9;
            //            break;
            //        case 50008:
            //            //劝降
            //            break;
        case 100011:
            //双枪之伤 2
            skillnumber=9;
            break;
        case 100012:
            //双镰之伤 2
            skillnumber=9;
            break;
        case 100013:
            //双戟之伤 2
            skillnumber=9;
            break;
        case 100014:
            //双斧之伤 2
            skillnumber=9;
            break;
        case 100015:
            //双刃之伤 2
            skillnumber=9;
            break;
        case 100016:
            //乱刀斩
            skillnumber=5;
            break;
        case 100017:
            //声东击西 2
            skillnumber=9;
            break;
        case 100018:
            //邪风阵
            skillnumber=6;
            break;
        case 100019:
            //困兽斗
            skillnumber=6;
            break;
        case 100020:
            //天雷阵
            skillnumber=6;
            break;
        case 100022:
            //美人计 2
            skillnumber=9;
            break;
        case 100024:
            //狮子吼
            skillnumber=6;
            break;
        case 100025:
            //野火燎原
            skillnumber=6;
            break;
        case 100026:
            //万里冰封 2
            skillnumber=9;
            break;
        case 100027:
            
            //黄雀阵
            skillnumber=6;
            break;
        case 100028:
            //水击三千里
            skillnumber=6;
            break;
        case 100029:
            //破军计
            skillnumber=5;
            break;
            //        case 210101:
            //            //诈降计
            //            skill="sq";
            //            break;
        case 100031:
            //屈兵计
            skillnumber=4;
            break;
        default:
            skill="0";
            break;
    }
    return skillnumber;
}


const char * skillList::skillname(int skillnum){
    switch (skillnum) {
        case 100001:
            //遇神诛神
            skill="name_yszs.png";
            break;
        case 100002:
            //地利人和
            skill="name_dlrh.png";
            break;
        case 100003:
            //太极八卦阵
            skill="name_tjbg.png";
            break;
        case 100004:
            //迷烟阵
            skill="name_myz.png";
            break;
        case 100005:
            //醉醒技
            skill="name_zxj.png";
            break;
        case 100006:
            //偷袭
            skill="name_tx.png";
            break;
        case 100007:
            //天公怒
            skill="name_tgn.png";
            break;
        case 50007:
            //诈降
            skill="name_zhxj.png";
            break;
            //        case 50008:
            //            //劝降
            //            break;
        case 100011:
            //双枪之伤 2
            skill="name_sqzs.png";
            break;
        case 100012:
            //双镰之伤 2
            skill="name_slzs.png";
            break;
        case 100013:
            //双戟之伤 2
            skill="name_sjzs.png";
            break;
        case 100014:
            //双斧之伤 2
            skill="name_sfzs.png";
            break;
        case 100015:
            //双刃之伤 2
            skill="name_srzs.png";
            break;
        case 100016:
            //乱刀斩
            skill="name_ldz.png";
            break;
        case 100017:
            //声东击西 2
            skill="name_sdjx.png";
            break;
        case 100018:
            //邪风阵
            skill="name_xfz.png";
            break;
        case 100019:
            //困兽斗
            skill="name_kszd.png";
            break;
        case 100020:
            //天雷阵
            skill="name_tgn.png";
            break;
        case 100022:
            //美人计 2
            skill="name_mrj.png";
            break;
        case 100024:
            //狮子吼
            skill="name_szh.png";
            break;
        case 100025:
            //野火燎原
            skill="name_yhly.png";
            break;
        case 100026:
            //万里冰封 2
            skill="name_wlbf.png";
            break;
        case 100027:
            
            //黄雀阵
            skill="name_hqz.png";
            break;
        case 100028:
            //水击三千里
            skill="name_sjsql.png";
            break;
        case 100029:
            //破军计
            skill="name_pjj.png";
            break;
            //        case 210101:
            //            //诈降计
            //            skill="sq";
            //            break;
        case 100031:
            //屈兵计
            skill="name_qbj.png";
            break;
        default:
            skill="name_tx.png";
            break;
    }
    return skill;
}
const char * skillList::throwTX(int skillid){
    const char * skillname;
    switch (skillid) {
        case 50:
            skillname="tx";
            break;
        case 51:
            skillname="tgn";
            break;
        case 52:
            skillname="zhxj";
            
            break;
        case 53:
            skillname="sqzs";
            
            break;
        case 54:
            skillname="slzs";
            break;
        case 55:
            skillname="sjzs";
            break;
        case 56:
            skillname="sfzs";
            break;
        case 57:
            skillname="srzs";
            break;
        case 58:
            skillname="sdjx";
            break;
        case 59:
            skillname="xfz";
            break;
        case 60:
            skillname="mrj";
            break;
        case 61:
            skillname="szh";
            break;
        case  62:
            skillname="wlbf";
            break;
        case 63:
            skillname="hqz";
            break;
        case 64:
            skillname="sjsql";
            break;
        case 65:
            skillname="pjj";
            break;
        case 66:
            skillname="qbj";
            break;
        default:
            skillname="";
            break;
    }
}