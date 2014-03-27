#ifndef __client1__skillList__
#define __client1__skillList__

#include <iostream>
class skillList{
public:
    skillList()
    {
        skill = "";
        skillnumber = 0;
        qsskill = "";
        
    };
    const char  *skill;
    int skillnumber;
    const char * qsskill;
    const char * sqskills(int skillnum);
    const  char * skills(int skillnum);
    int skillnums(int skillnum);
    const char * throwTX(int skillid);
    const char * skillname(int skillnum);
    const char * releaseName(int skillrelease);
};

#endif /* defined(__client1__skillList__) */
